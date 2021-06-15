#include "input.h"
#include "Func_texture.h"
#include "sound.h"
#include "scene.h"
#include "result.h"
#include "Draw_text.h"
#include "fade.h"
#include "player.h"
#include "game.h"
#include "stage.h"//�w�b�_�[��enum�擾�̂���

//*****************************************************************************
// CONST�ϐ�
//*****************************************************************************

//�e�N�X�`���[�̐ݒ�
enum
{
	TEXTURE_BG,			
	TEXTURE_PAPER,		
	TEXTURE_HANKO,		
	TEXTURE_LIGHT,		
	TEXTURE_PUSHENTER,	
	TEXTURE_PUSHNEXT,	
	TEXTURE_MAX,
};





enum RESULT_STATE {
	PAPER_APEAEAR,
	SCORE_APEAEAR,
	HANKO_WAIT,
	HANKO_PUSH,
	HANKO_PUSED,
	RESULT_MAX
};

const static Texture_DATA c_InitTexture[] =
{
	{
		(char *)"TEXTURE/Result/Result_bk.tga"
		,NULL
		,NULL
		,D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f)
		,SCREEN_WIDTH
		,SCREEN_HEIGHT
		,true
		,0
		,0
		,true
		,NON_DIVIDE
		,NON_DIVIDE
		,NON_DIVIDE_TEXTURENUMBER
		,false
		,D3DXVECTOR4(255, 255, 255, 255)
	},
	{
		(char *)"TEXTURE/Result/result_paper.tga"
		,NULL
		,NULL
		,D3DXVECTOR3(SCREEN_WIDTH / 2, -TEXTURE_RESULT_PAPER_SIZE_Y, 0)
		,TEXTURE_RESULT_PAPER_SIZE_X
		,TEXTURE_RESULT_PAPER_SIZE_Y
		,true
		,0
		,0
		,true
		,NON_DIVIDE
		,NON_DIVIDE
		,NON_DIVIDE_TEXTURENUMBER
		,false
		,D3DXVECTOR4(255, 255, 255, 255)
	},
	{
		(char *)"TEXTURE/Result/hannko.tga"
		,NULL
		,NULL
		,D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f)
		,220
		,80
		,false
		,0
		,0
		,true
		,NON_DIVIDE
		,NON_DIVIDE
		,NON_DIVIDE_TEXTURENUMBER
		,false
		,D3DXVECTOR4(255, 255, 255, 255)
	},
	{
		(char *)"TEXTURE/Result/light.tga"
		,NULL
		,NULL
		,D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f)
		,SCREEN_WIDTH
		,SCREEN_HEIGHT
		,false
		,0
		,0
		,true
		,NON_DIVIDE
		,NON_DIVIDE
		,NON_DIVIDE_TEXTURENUMBER
		,false
		,D3DXVECTOR4(255, 255, 255, 255)
	},
	{
		(char *)"TEXTURE/Result/Push_ENTER.png"
		,NULL
		,NULL
		, D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4 * 3, 0.0f)
		,TEXTURE_RESULT_PUSH_SIZE_X
		,TEXTURE_RESULT_PUSH_SIZE_Y
		,false
		,0
		,0
		,true
		,NON_DIVIDE
		,NON_DIVIDE
		,NON_DIVIDE_TEXTURENUMBER
		,false
		,D3DXVECTOR4(255, 255, 255, 255)
	},
	{
		(char *)"TEXTURE/Result/Push_ENTER_NEXT_STAGE.png"
		,NULL
		,NULL
		, D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 8 * 7, 0.0f)
		,TEXTURE_RESULT_NEXT_SIZE_X
		,TEXTURE_RESULT_NEXT_SIZE_Y
		,false
		,0
		,0
		,true
		,NON_DIVIDE
		,NON_DIVIDE
		,NON_DIVIDE_TEXTURENUMBER
		,false
		,D3DXVECTOR4(255, 255, 255, 255)
	},
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void CheckAchieveHighScore();

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

static VERTEX_2D g_PolygonVertex[TEXTURE_MAX][4];
static Texture_DATA g_Texture[TEXTURE_MAX];

static D3DXVECTOR4 CharaColor; //�\�������F

RESULT_STATE g_ResultState;
//�X�e�[�g���ς�邲�Ƃ�0�ɂ���
float g_ResultStateTime;

static int g_CurrentScore;
static int g_HighScore=0;
static STAGE g_CurrentStageData;
//�t���O
static bool g_AchieveHighScore;		//�n�C�X�R�A�B��
static bool g_LastStageflg;	//���X�g�X�e�[�W�t���O
static bool g_StateUseflg;//STATE���g���t���O�A�e�X�e�[�g���n�܂�O��false�ɂ���
static bool g_BottunFlg;


void Result_Initialize(void)
{
	g_ResultState = PAPER_APEAEAR;
	//�����̐F����F��
	CharaColor = D3DXVECTOR4(255, 0, 0, 0);
	//�n�C�X�R�A�̏�����
	g_CurrentScore = 0;
	//�t���O������
	g_AchieveHighScore = false;
	g_LastStageflg = false;
	g_StateUseflg = false;
	g_BottunFlg = true;
	g_ResultStateTime = 0;

	//�X�e�[�W�̃f�[�^���擾����
	g_CurrentStageData = GetStageData(GetGameStage());

	//���[�U�[�̌��݂̃X�R�A���n�C�X�R�A���`�F�b�N
	CheckAchieveHighScore();

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int i = 0; i < TEXTURE_MAX; i++)
	{
	
		SetTextureDATA
		(
			pDevice,
			g_PolygonVertex[i],
			&g_Texture[i],
			&c_InitTexture[i]
		);

	}
	//BGM�̐���
	PlaySound(SOUND_LABEL_BGM_result);
	PlaySound(SOUND_LABEL_SE_RESULT_PAPER);

	//�Q�[���̃X�e�[�W�����`�F�b�N���ő�Ȃ玟�̃X�e�[�W�ɐi�܂Ȃ�
	int tempstage;
	tempstage = GetGameStage() + 1;
	if (tempstage == MAX_STAGE_TYPE) {
		g_LastStageflg = true;
	}

}

void Result_Finalize(void)
{
	StopSound(SOUND_LABEL_BGM_result);
	g_LastStageflg = false;
	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		UnLoadTextureDATA(&g_Texture[i]);
		/*
		if (g_Result_texture[i].pD3DTexture != NULL)
		{	// �e�N�X�`���̊J��
			g_Result_texture[i].pD3DTexture->Release();
			g_Result_texture[i].pD3DTexture = NULL;
		}
		*/
	}
}

void Result_Update(void)
{
	switch (g_ResultState)
	{
	case PAPER_APEAEAR:
		g_Texture[TEXTURE_PAPER].Pos.y += 3.0f;
		if (g_Texture[TEXTURE_PAPER].Pos.y>SCREEN_HEIGHT/2)
		{
			g_StateUseflg = false;
			g_ResultStateTime = 0;
			g_ResultState = HANKO_WAIT;
		}
		break;
	case HANKO_WAIT:
		if (!g_StateUseflg)
		{
			PlaySound(SOUND_LABEL_SE_RESULT_HANKObf);
			g_StateUseflg = true;
		}
		g_ResultStateTime += 1.0f / 120.0f;
		if (g_ResultStateTime>1.0f) {
			g_ResultStateTime = 0;
			g_StateUseflg = false;
			g_ResultState = HANKO_PUSH;
		}
		break;
	case HANKO_PUSH:
		if (!g_StateUseflg)
		{
			g_Texture[TEXTURE_PUSHENTER].IsEnable = true;
			//�n���R�̈ʒu���Đݒ肷��
			g_Texture[TEXTURE_HANKO].Pos = g_Texture[TEXTURE_PAPER].Pos;
			g_Texture[TEXTURE_HANKO].Pos.x += TEXTURE_RESULT_PAPER_SIZE_X / 24*7;
			g_Texture[TEXTURE_HANKO].Pos.y += TEXTURE_RESULT_PAPER_SIZE_Y / 16*1.3f;
			g_StateUseflg = true;
		}

		if (GetKeyboardTrigger(DIK_RETURN)) {
			PlaySound(SOUND_LABEL_SE_RESULT_HANKOafter);	
			g_Texture[TEXTURE_HANKO].IsEnable = true;
			g_Texture[TEXTURE_PUSHENTER].IsEnable = false;
			g_StateUseflg = false;
			g_ResultState = HANKO_PUSED;
		}
		break;
	case HANKO_PUSED:
		if (!g_StateUseflg)
		{
			g_Texture[TEXTURE_PUSHNEXT].IsEnable = true;
			g_StateUseflg = true;
		}
		//���X�g�X�e�[�W����Ȃ��Ȃ�
		if (!g_LastStageflg)
		{
			//���̃X�e�[�W�֍s��
			if (GetKeyboardTrigger(DIK_RETURN)&& g_BottunFlg) {
				PlaySound(SOUND_LABEL_SE_titlebutton);

				SetGameStage(GetGameStage() + 1);
				Fade(SCENE_INDEX_GAME);
				g_BottunFlg = false;
			}
			//�^�C�g���ɖ߂�
			if (GetKeyboardTrigger(DIK_BACK) && g_BottunFlg) {
				PlaySound(SOUND_LABEL_SE_titlebutton);
				SetGameStage(0);
				Fade(SCENE_INDEX_TITLE);
				g_BottunFlg = false;
			}
		}
		else 
		{//�^�C�g���ɖ߂�
			if (GetKeyboardTrigger(DIK_RETURN) && g_BottunFlg)
			{
				PlaySound(SOUND_LABEL_SE_titlebutton);
				SetGameStage(0);
				Fade(SCENE_INDEX_TITLE);
				g_BottunFlg = false;
			}
		}	
		break;
	case RESULT_MAX:
		break;
	default:
		break;
	}
}

void Result_Draw(void)
{

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		if (!g_Texture[i].IsEnable)
			continue;
		//�ꏊ����
		
		
		DrawTextureDATA(
			pDevice,
			&g_Texture[i]
		);
	}

	//�����̕`��
	TCHAR str[256];
	RECT rect = 
		{ g_Texture[TEXTURE_PAPER].Pos.x - TEXTURE_RESULT_PAPER_SIZE_X/24*8, 
		g_Texture[TEXTURE_PAPER].Pos.y+ TEXTURE_RESULT_PAPER_SIZE_Y/32*3,
		SCREEN_WIDTH, 
		SCREEN_HEIGHT };
	//Score�̕`��
	wsprintf(str, _T("%d\n"), g_CurrentScore);
	Drawtextfnc(str, rect, CharaColor);
	//�n�C�X�R�A���߂łƂ��̕`��
	if (g_AchieveHighScore) {
		////HighScore�̕`��
	}	
	//�����̊i�[�I���
}

void SetCurrentGameScore(int currentScore) {
	g_CurrentScore = currentScore;
}

//*****************************************************************************
// �������牺�͂��̊֐��݂̂Ŏg����֐�
//*****************************************************************************
//�n�C�X�R�A�̊i�[�ƃn�C�X�R�A��
void CheckAchieveHighScore() {
	PLAYER_DATA *player = GetPlayer();
	g_CurrentScore = player->Score;


	if (g_CurrentScore> g_CurrentStageData.int1) {

		g_CurrentStageData.int1 = g_CurrentScore;
		SetStageHighScore(GetGameStage(), g_CurrentScore);

		g_AchieveHighScore = true;
	}
	return;
}