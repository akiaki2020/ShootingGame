

#include "main.h"
#include "Func_texture.h"
#include "enemy.h"
#include "Enemy_Ai.h"
#include "player.h"
#include "Sound.h"
#include "bullet.h"
#include "UI_Boss.h"
#include "explosion.h"
#define _USE_MATH_DEFINES 
#include "math.h"

//*****************************************************************************
// CONST�ϐ�
//*****************************************************************************


#define WALK_WAIT_FRAME		10		//�A�j���[�V�����؂�ւ��E�G�C�g
#define WALK_PATTERN_MAX	3		//�A�j���[�V�����p�^�[����
#define DISAPPEAR_RANGE		200		//�G�̏����͈�
#define ENEMY_DMGHIT_TIME	(0.5)// �G�l�~�[�̃_���[�W�q�b�g���̎���
#define ENEMY_DMGHIT_MUTEKITIME	(0.2)// �G�l�~�[�̃_���[�W�q�b�g���̖��G����

const static Texture_DATA c_InitTexture[] =
{
	{
		(char *)"TEXTURE/Stg_main/Enemy/darkgrey_02.png"
		,NULL
	,NULL
	,D3DXVECTOR3(SCREEN_GAME_WIDTH / 2, SCREEN_GAME_HEIGHT / 4 * 3, 0.0f)	//�����ł͎g��Ȃ�
	,32
	,32
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
		(char *)"TEXTURE/Stg_main/Enemy/darkgrey_01.png"
		,NULL
	,NULL
	,D3DXVECTOR3(SCREEN_GAME_WIDTH / 2, SCREEN_GAME_HEIGHT / 4 * 3, 0.0f)
	,64
	,64
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
		(char *)"TEXTURE/Stg_main/Enemy/9.png"
		,NULL
	,NULL
	,D3DXVECTOR3(SCREEN_GAME_WIDTH / 2, SCREEN_GAME_HEIGHT / 4 * 3, 0.0f)
	,64
	,64
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
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void DieEnemy(ENEMY* enemy);
void EnemyDamageState(ENEMY* enemy);
void BreEnemyPos(ENEMY* enemy, int EffectOnOff);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static ENEMY g_Enemy[MAX_ENEMY];					//�G�l�~�[�f�[�^
enum TextureType {
	NORMAL,
	LEFT,
	RIGHT,
	TYPE_MAX
};
enum
{
	TEXTURE_ENEMY_FIGHTER,		
	TEXTURE_ENEMY_SHOT_FIGHTER,	
	TEXTURE_ENEMY_DAKOU_FIGHTER,
	TEXTURE_ENEMY_MAX,
};
static VERTEX_2D g_PolygonVertex[TEXTURE_ENEMY_MAX][4];//���_�f�[�^
static Texture_DATA g_Texture[TEXTURE_ENEMY_MAX];

static ENEMY* g_Boss;	//�Q�Ɨp

//�G�̏o���J�n���ԁA�o���ꏊ�A�ړ������̐ݒ�z��
ENEMY tblEnemy[MAX_ENEMYTYPE] = {
	//Fighter
	//�ꏊ				,�ړ�����				����	
	{ D3DXVECTOR3( 0,0,0 ), D3DXVECTOR3(0,0,0),0.0f
	,FIGHTER
	,2,2,NORMAL		//TEXTURE
	,D3DXVECTOR3(40.0f,40.0f,0)//SIZE
	,3	//Hp
	,1	//Power
	,1	//Score
	,ENEMY_STATE_NORMAL	//�G�̏��
	,0	//�X�e�[�g����
	,GO_DIRECT			//�G��AI
	,0	//�X�e�[�g����
	,false
	,TEXTURE_ENEMY_FIGHTER	//�G�̃^�C�v
	,0
	,0
	,0
	,2.5f		//�e�̃X�s�[�h
	,0.0f
	,0.0f
	,0.0f
	,false	//�G�̖��G�t���O
	,0.0f	//�G�̖��G����
	},
	//SHOT_FIGHTER
	{ D3DXVECTOR3( 0,0,0 ), D3DXVECTOR3(0,0,0),0.0f
	,SHOT_FIGHTER
	,2,2,NORMAL		//TEXTURE
	,D3DXVECTOR3(40.0f,40.0f,0)//SIZE
	,3	//Hp
	,1	//Power
	,2	//Score
	,ENEMY_STATE_NORMAL	//�G�̏��
	,0	//�X�e�[�g����
	,GO_DIRECT			//�G��AI
	,0	//�X�e�[�g����
	,false
	,TEXTURE_ENEMY_SHOT_FIGHTER
	,0
	,0
	,0
	,2.5f		//�e�̃X�s�[�h
	,0.0f
	,0.0f
	,0.0f	
	,false	//�G�̖��G�t���O
	,0.0f	//�G�̖��G����
	},
	//DAKOU_FIGHTER
	{ D3DXVECTOR3(0,0,0), D3DXVECTOR3(0,0,0),0.0f
	,DAKOU_FIGHTER
	,2,2,NORMAL		//TEXTURE
	,D3DXVECTOR3(64.0f,64.0f,0)//SIZE
	,3	//Hp
	,1	//Power
	,4	//Score
	,ENEMY_STATE_NORMAL	//�G�̏��
	,0	//�X�e�[�g����
	,GO_DIRECT			//�G��AI
	,0	//�X�e�[�g����
	,false
	,TEXTURE_ENEMY_DAKOU_FIGHTER
	,0
	,0
	,0
	,2.5f		//�e�̃X�s�[�h
	,0.0f
	,0.0f
	,0.0f
	,false	//�G�̖��G�t���O
	,0.0f	//�G�̖��G����
	},
	//BIG_FIGHTER
	{ D3DXVECTOR3(0,0,0), D3DXVECTOR3(0,0,0),0.0f
	,BIG_FIGHTER
	,2,2,NORMAL		//TEXTURE
	,D3DXVECTOR3(100.0f,100.0f,0)//SIZE
	,4	//Hp
	,2	//Power
	,5	//Score
	,ENEMY_STATE_NORMAL	//�G�̏��
	,0	//�X�e�[�g����
	,GO_DIRECT			//�G��AI
	,0	//�X�e�[�g����
	,false
	,TEXTURE_ENEMY_FIGHTER	//�G�̃^�C�v
	,0
	,0
	,0
	,2.5f		//�e�̃X�s�[�h
	,0.0f
	,0.0f
	,0.0f
	,false	//�G�̖��G�t���O
	,0.0f	//�G�̖��G����
	},
	//GO__FIGHTER
	{ D3DXVECTOR3(0,0,0), D3DXVECTOR3(0,0,0),0.0f
	,GO_FIGHTER
	,2,2,NORMAL		//TEXTURE
	,D3DXVECTOR3(40.0f,40.0f,0)//SIZE
	,3	//Hp
	,1	//Power
	,1	//Score
	,ENEMY_STATE_NORMAL	//�G�̏��
	,0	//�X�e�[�g����
	,GO_DIRECT			//�G��AI
	,0	//�X�e�[�g����
	,false
	,TEXTURE_ENEMY_FIGHTER	//�G�̃^�C�v
	,0
	,0
	,0
	,2.5f		//�e�̃X�s�[�h
	,0.0f
	,0.0f
	,0.0f
	,false	//�G�̖��G�t���O
	,0.0f	//�G�̖��G����
	},
};

void InitEnemy()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�V�[�h�l�̐ݒ�@���V�[�h�l�ɂ͌��ݎ����̃~��Sec���g�p
	//g_rnd.SetSeed(nn::fnd::DateTime::GetNow().GetMilliSecond());
	for (int i = 0; i < MAX_ENEMY; i++)
	{
		////�L���t���O��OFF����
		g_Enemy[i].isEnable = false;
		//���ׂ�Fighter�^�ɂ���
		g_Enemy[i] = tblEnemy[0];

	}

	//�e�N�X�`���f�[�^�̏�����
	for (int i = 0; i < TEXTURE_ENEMY_MAX; i++)
	{
		SetTextureDATA
		(
			pDevice,
			g_PolygonVertex[i],
			&g_Texture[i],
			&c_InitTexture[i]
		);
	}

}


void UninitEnemy()
{
	for (int i = 0; i < TEXTURE_ENEMY_MAX; i++)
	{
		UnLoadTextureDATA(&g_Texture[i]);
	}
}


void UpdateEnemy()
{
	for (int i = 0; i < MAX_ENEMY; i++)
	{
		//�L���t���O��ON����Ȃ���Ή������Ȃ�
		if (g_Enemy[i].isEnable == false)
			continue;

		//Enemy_Ai����擾
		Enemy_AI_Update(&g_Enemy[i]);


		//�G����ʊO�{�ݒ�͈͂���o�čs���Ă��܂�����
		//�L���t���O�𗎂Ƃ�
		if (g_Enemy[i].pos.y < 0- DISAPPEAR_RANGE)
			g_Enemy[i].isEnable = false;
		//�L���t���O�𗎂Ƃ�
		if (g_Enemy[i].pos.y > SCREEN_HEIGHT+ DISAPPEAR_RANGE)
			g_Enemy[i].isEnable = false;
		//�L���t���O�𗎂Ƃ�
		if (g_Enemy[i].pos.x < 0- DISAPPEAR_RANGE)
			g_Enemy[i].isEnable = false;
		//�L���t���O�𗎂Ƃ�
		if (g_Enemy[i].pos.x > SCREEN_WIDTH + DISAPPEAR_RANGE)
			g_Enemy[i].isEnable = false;

		//�G�̏�Ԃɂ�苓���̈ꎞ�I�ȕύX
		switch (g_Enemy[i].State)
		{
		case ENEMY_STATE_NORMAL:
			break;
		case ENEMY_STATE_DAMAGE:
			EnemyDamageState(&g_Enemy[i]);
			break;
		default:
			break;
		}
		g_Enemy[i].pos = g_Enemy[i].pos + g_Enemy[i].EffectPos;

		//���G���Ԃ��v�����A���Ԃ𒴂�����OFF�ɂ���
		if (g_Enemy[i].Enemy_Mutekiflg) {
			g_Enemy[i].Muteki_time += 1.0f / 120.0f;
			if (g_Enemy[i].Muteki_time>ENEMY_DMGHIT_MUTEKITIME) {
				g_Enemy[i].Muteki_time = 0;
				g_Enemy[i].Enemy_Mutekiflg = false;
			}
		}

	}
}


void DrawEnemy()
{

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int i = 0; i < MAX_ENEMY; i++)
	{
		//�L���t���O��ON����Ȃ���Ή������Ȃ�
		if (g_Enemy[i].isEnable == false)
			continue;

		//ENEMY�f�[�^���e�N�X�`���[�Ɋi�[����
		int textureType = g_Enemy[i].int1;
		g_Texture[textureType].Pos = g_Enemy[i].pos;
		g_Texture[textureType].Angle = g_Enemy[i].Rotation;
		g_Texture[textureType].Size_x = g_Enemy[i].size.x;
		g_Texture[textureType].Size_y = g_Enemy[i].size.y;

		DrawTextureDATA(
			pDevice,
			&g_Texture[textureType]
		);
	}
}

void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 dir, int EnemyType) 
{
	for (int i = 0; i < MAX_ENEMY; i++)
	{
		if (g_Enemy[i].isEnable == false)
		{
			//�G�̃^�C�v���i�[����
			g_Enemy[i]= tblEnemy[EnemyType];

			g_Enemy[i].AI_State = ENEMY_STATE_NORMAL;
			g_Enemy[i].State = GO_DIRECT;
			//�\���ʒu�����߂�
			g_Enemy[i].pos = pos;
			//�ړ����������߂�
			g_Enemy[i].dir = dir;
			//�L�����t���O��ON�ɂ���
			g_Enemy[i].isEnable = true;
			g_Enemy[i].Muteki_time = 0;
			g_Enemy[i].Enemy_Mutekiflg = false;
			//�P�C�Z�b�g������I������
			break;
		}
	}
}

//�L���t���O��n��
bool GetIsEnableEnemy(int index)
{
	return g_Enemy[index].isEnable;
}

//ENEMYtbl��Getter
ENEMY& GetEnemyTbl(int index) {
	return tblEnemy[index];
}


//ENEMY��Getter
ENEMY* GetEnemy() {
	return (&g_Enemy[0]);
}

void EnemyFireBullet(ENEMY* enemy) {

	D3DXVECTOR3 tempdir= D3DXVECTOR3(0,0,0);
	//�ړ����������鉺��WAIT����̂���
	tempdir = D3DXVECTOR3(sinf(enemy->Rotation), -cosf(enemy->Rotation), 0);
	SetBullet(enemy->pos, tempdir, enemy->BulletSpeed,ENEMYS_BULLET);
}

// Enemy��Hp��ς��鏈��
void PlusEnemyHp(ENEMY* enemy,int PlusHp) {

	//���G��ԂȂ�HP�͌���Ȃ�
	if (enemy->Enemy_Mutekiflg&& PlusHp<0) {
		return;
	}
	//�_���[�W�Ȃ�
	if (PlusHp<0)PlaySound(SOUND_LABEL_SE_Enemyhit000);

	enemy->Hp += PlusHp;
	enemy->Enemy_Mutekiflg = true;
	
	//Boss�Ȃ烉�C�t���f
	if (g_Boss == enemy)
	{
		UpdateBossLifeData(enemy->Hp);
	}

	//Hp��0�ɂȂ����Ƃ�
	if (enemy->Hp <= 0) 
	{
		DieEnemy(enemy);
	}
}

// Enemy�̏�Ԃ�ς��鏈��
void ChangeEnemyState(ENEMY* enemy, int targetstate) {

	if (enemy->isEnable == false)
	{
		return;
	}
	enemy->State = targetstate;
}

void SetBossDate(ENEMY& enemy) 
{
	g_Boss = &enemy;
}

void DieEnemy(ENEMY* enemy) {
	PlaySound(SOUND_LABEL_SE_EnemyDie000);
	SetExplosion(enemy->pos);
	PlusPlayerScore(enemy->Score);
	enemy->isEnable = false;
}

void EnemyDamageState(ENEMY* enemy) {
	enemy->State_time += 1 / 60.0f;

	if (int(enemy->State_time * 1000) % 4 == 0) {
		BreEnemyPos(enemy,0);
	}

	if (int(enemy->State_time * 1000) % 4 == 2) {
		BreEnemyPos(enemy, 1);
	}

	if (enemy->State_time > ENEMY_DMGHIT_TIME)
	{
		BreEnemyPos(enemy, 2);
		enemy->State_time = 0;
		enemy->State = ENEMY_STATE_NORMAL;
	}
}

void BreEnemyPos(ENEMY* enemy,int EffectOnOff) {

	switch (EffectOnOff)
	{
	case 0:
		//�v���C���[���\������Ă��鎞
		enemy->EffectPos.x = cosf(rand())* -5;
		enemy->EffectPos.y = sinf(rand())* -5;

		break;
	case 1:
		enemy->EffectPos.x = cosf(rand())* 5;
		enemy->EffectPos.y = sinf(rand())* 5;

		break;

	case 2:
		//�v���C���[��\�����鎞
		enemy->EffectPos.x = 0.0f;
		enemy->EffectPos.y=  0.0f;
		break;
	default:
		break;

	}
}
