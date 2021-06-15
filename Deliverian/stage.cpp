
#include "main.h"
#include "ReadCsv.h"
#include "Draw_text.h"
#include "Enemy.h"
#include "EnemyEmitter.h"
#include "Boss.h"
#include "game.h"
#include "stage.h"
#include "bgtop.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define STAGE_FOLDER "stage\\"
#define STAGE_1_TEXTFILENAME "SKY"
#define STAGE_2_TEXTFILENAME "SPACE"
#define STAGE_3_TEXTFILENAME "ASTEROID"
#define STAGE_DATASIZE 2000

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void ImportStageDataTable(FILE *fp, int stage_type);
bool EndCheckBoss();



//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static LPD3DXFONT	g_pD3DXFont = NULL;			// �t�H���g�ւ̃|�C���^

static LPDIRECT3DDEVICE9		g_pD3DDevice = NULL;		// Device�I�u�W�F�N�g(�`��ɕK�v)

static STAGE g_stage;//���݂̃X�e�[�W
static float g_StageFrame;//�o�߃t���[����
static int g_Firstframe;//�ŏ��̌v������

static int g_Phase;

static boolean g_Bossflg;//BOSS�o���t���O
static int g_EmitCount;//�o���J�E���^
static int g_LimitEmitCount;//�o�����~�b�g

//�e�X�e�[�W�̗v�f�����Ă���
STAGE tblStage[MAX_STAGE_TYPE] = {
	//SKY
	{ 
		SKY,		//�X�e�[�W�̃^�C�v
		0.0f,		//�o�߃t���[��			
		60,			//�G�̏o����
		30.0f,	//�I���t���[��
	//	5.0f,	//�I���t���[���@�e�X�g�p
		B_FIGHTER,		//�{�X��
		//0,		//�{�X��
		"first",	//�X�e�[�W��
		0,		//�n�C�X�R�A
		0,		//
		0,		//
		0,		//
		0.0f,		//1�ϐ�
		0.0f,		//2�ϐ�
		0.0f,		//2�ϐ�
		0.0f,		//2�ϐ�
	},
	//SPACE
	{
		SPACE,		//�X�e�[�W�̃^�C�v
		0.0f,		//�o�߃t���[��
		200,			//�G�̏o����
		30.0f,		//�I���t���[��
		//5.0f,	//�I���t���[���@�e�X�g�p
		B_LASER,		//�{�X��
		//0,		//�{�X��
		"SPACE",	//�X�e�[�W��
		0,		//�n�C�X�R�A
		0,		//
		0,		//
		0,		//
		0.0f,		//1�ϐ�
		0.0f,		//2�ϐ�
		0.0f,		//2�ϐ�
		0.0f,		//2�ϐ�
	},
	//ASTEROID
	{
		ASTEROID,		//�X�e�[�W�̃^�C�v
		0.0f,		//�o�߃t���[��
		300,			//�G�̏o����
		40.0f,		//�I���t���[��
		//5.0f,	//�I���t���[���@�e�X�g�p
		B_FINAL,		//�{�X��
		//0,		//�{�X��
		"ASTEROID",	//�X�e�[�W��
		0,		//�n�C�X�R�A
		0,		//
		0,		//
		0,		//
		0.0f,		//1�ϐ�
		0.0f,		//2�ϐ�
		0.0f,		//2�ϐ�
		0.0f,		//2�ϐ�
	},
};

//�G�̏o���J�n���ԁA�o���ꏊ�A�ړ������̐ݒ�z��
ENEMYEMIT_T tblEnemy[STAGE_MAX_ENEMYGROUP]= {};

void InitStage()
{
	//����������
	g_EmitCount = 0;
	g_StageFrame = 0;
	g_Firstframe = time(NULL);
	g_Bossflg = false;
	tblEnemy[STAGE_MAX_ENEMYGROUP] = {};
	//�e�[�u���̗v�f���̌v�Z
	//�\���̔z��̃T�C�Y/�\���̂̃T�C�Y�Ōv�Z
	//g_TableSize = sizeof(tblEnemy) / sizeof(ENEMYEMIT_T);
	g_pD3DDevice = GetDevice();

	D3DXCreateFont(g_pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Terminal"), &g_pD3DXFont);
}

//game.cpp���Ăяo���ȊO�g��Ȃ�
void SetStage(STAGE_TYPE stagetype)
{
	FILE *fp=NULL;

	//����������
	g_EmitCount = 0;
	g_LimitEmitCount=0;
	g_StageFrame = 0;
	//�e�[�u�����e����
	g_stage = tblStage[stagetype];

	//�X�e�[�W�f�[�^��CSV����ǂݍ���
	char fileName[2000];
	char fileStageEnemyData[STAGE_DATASIZE];
	
	fileName[0]='\0';
	fileStageEnemyData[0] = '\0';
	
	//
	strcpy(fileName, CSV_FOLDER);
	strcat(fileName, STAGE_FOLDER);

	switch (stagetype)
	{
	case SKY:		
		strcat(fileName, STAGE_1_TEXTFILENAME);
		break;
	case SPACE:
		strcat(fileName, STAGE_2_TEXTFILENAME);
		break;
	case ASTEROID:
		strcat(fileName, STAGE_3_TEXTFILENAME);
		break;
	case MAX_STAGE_TYPE:
		break;
	default:
		break;
	}
	fp= ReadCsv(fileName);
	ImportStageDataTable(fp, stagetype);
	fclose(fp); // �t�@�C�������
	//�w�i�̐ݒ�
	Bg_SetTextureEnable(stagetype);
	//�e�[�u���̗v�f���̌v�Z
	//�\���̔z��̃T�C�Y/�\���̂̃T�C�Y�Ōv�Z
	//g_TableSize = g_stage.EnemyPop;
	g_StageFrame = 0;


}

void UpdateStage() {
	g_Phase = GetGamePhase();
	g_StageFrame +=1.0f/60;

	//�G���t�F�[�Y
	if (g_Phase== PHASE_GAME_NORMAL) {

		//g_EmitCount���ݒ�z��̗v�f���𒴂�������s���Ȃ��悤�ɂ���
		if (g_EmitCount < g_LimitEmitCount) {
			//�o�ߎ��ԂƏo���t���[�����r���A�o�ߎ��Ԃ�������ΓG�����I
			if (g_StageFrame > tblEnemy[g_EmitCount].flame) {
				//�G�𔭐�������
				EnemyEmitter(
					tblEnemy[g_EmitCount].pos,
					tblEnemy[g_EmitCount].dir,
					tblEnemy[g_EmitCount].EnemyType,
					tblEnemy[g_EmitCount].EmitType
				);
				g_EmitCount++;
			}
		}
		//STAGE���ԏI����
		if (g_StageFrame >= tblStage[g_stage.stage_type].NormalEndflame)
		{
			SetGamePhase(PHASE_GAME_BOSS);
			g_Bossflg = true;
		}
	}

	if (g_Phase == PHASE_GAME_BOSS) {

		//�ŏ��Ƀ{�X���o��������
		if (g_Bossflg) {
			SetBoss(tblStage[g_stage.stage_type].boss_type);
			g_Bossflg = false;
		}
		//�Q�[���N���A�����������Ă�����Q�[���N���A�t�F�[�Y�ֈڍs����
		if (EndCheckBoss()) {
			SetGamePhase(PHASE_GAME_STAGE_CLEAR);
		}

	}


}

bool EndCheckBoss()
{
	ENEMY* pBoss = GetBoss();
	if (pBoss->Hp <= 0)
	{
		return true;
	}
	return false;
}


void ImportStageDataTable(FILE *fp, int stagetype) {
	int ret=0;
	float flame=0;
	float pos[3];
	float dir[3];
	int Enemy[2];
	int rowCount=0;
	//�f�[�^�ǂݍ���
	while 
		(
			(ret = 
				fscanf(fp, "%f,%f,%f,%f,%f,%f,%f,%d,%d,", &flame, &pos[0], &pos[1], &pos[2], &dir[0], &dir[1], &dir[2], &Enemy[0], &Enemy[1])
			) 
			!= EOF
		) 
	{
		//�G�̏o�������ɂ���Ĉʒu�𒲐�����


		//���������̒���
		if (dir[0] > 0) {
			pos[0] = -10.0f;
		}
		else if(dir[0] < 0) {
			pos[0] = SCREEN_GAME_WIDTH +10.0f;
		}
		//���������̒���
		if (dir[1] > 0) {
			pos[1] = -10.0f;
		}
		else if(dir[1] < 0) {
			pos[1] = SCREEN_HEIGHT + 10.0f;
		}

		tblEnemy[rowCount] = { flame,D3DXVECTOR3(pos[0],pos[1],pos[2]), D3DXVECTOR3(dir[0],dir[1],dir[2]),Enemy[0],Enemy[1] };
			rowCount++;
			g_LimitEmitCount++;
	}
}

void SetStageHighScore(int stage_type,int HighScore) {
	tblStage[stage_type].int1 = HighScore;
}

STAGE GetStageData(int stage_type) {
	return tblStage[stage_type];
}

float GetStagetime() {
	return g_StageFrame;
}

STAGE GetCurrentStageData() {
	return g_stage;
}