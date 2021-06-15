
#include "main.h"
#include "Func_texture.h"
#define _USE_MATH_DEFINES 
#include "math.h"
#include "boss.h"
#include "boss_AI.h"
#include "UI_Boss.h"


//*****************************************************************************
// CONST�ϐ�
//*****************************************************************************

//�{�X�̐ݒ�
const int c_Tex_Divide= 2;
const float BOSS_WIDTH = 160.0f;
const float BOSS_HEIGHT = 80.0f;
const float BOSS_DMGHIT_MUTEKITIME = 0.01f;// �G�l�~�[�̃_���[�W�q�b�g���̖��G����
const float BOSS_DMGHIT_TIME = 0.5f;	// �G�l�~�[�̃_���[�W�q�b�g���̋�������


enum TextureType {
	NORMAL,
	LEFT,
	RIGHT,
	TYPE_MAX
};

const Texture_DATA c_InitTexture[B_MAX_ENEMYTYPE] =
{
	{
		(char *)"TEXTURE/Stg_main/Boss/fighter.tga"
		,NULL
		,NULL
		,D3DXVECTOR3(SCREEN_GAME_WIDTH / 2, SCREEN_GAME_HEIGHT / 4 * 3, 0.0f)	//�����ł͎g��Ȃ�
		,BOSS_WIDTH
		,BOSS_HEIGHT
		,true
		,0
		,0
		,true
		,c_Tex_Divide
		,c_Tex_Divide
		,0
		,true
		,D3DXVECTOR4(255, 255, 255, 255)
	},
	{
		(char *)"TEXTURE/Stg_main/Boss/B_LASER.png"
		,NULL
		,NULL
		,D3DXVECTOR3(SCREEN_GAME_WIDTH / 2, SCREEN_GAME_HEIGHT / 4 * 3, 0.0f)	//�����ł͎g��Ȃ�
		,BOSS_WIDTH
		,BOSS_HEIGHT
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
		(char *)"TEXTURE/Stg_main/Boss/B_FINAL.png"
		,NULL
		,NULL
		,D3DXVECTOR3(SCREEN_GAME_WIDTH / 2, SCREEN_GAME_HEIGHT / 4 * 3, 0.0f)	//�����ł͎g��Ȃ�
		,BOSS_WIDTH
		,BOSS_HEIGHT
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
// �O���[�o���ϐ�
//*****************************************************************************
static LPDIRECT3DTEXTURE9		g_pD3DTexture = NULL;		// �e�N�X�`���ւ̃|�C���^

static VERTEX_2D g_PolygonVertex[B_MAX_ENEMYTYPE][4];	//���_�f�[�^
static Texture_DATA g_texture[B_MAX_ENEMYTYPE];
static ENEMY g_Boss;					//�{�X�f�[�^

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
static void EnemyDamageState(ENEMY* enemy);

//�{�X�̏o���J�n���ԁA�o���ꏊ�A�ړ������̐ݒ�z��
ENEMY tblBoss[B_MAX_ENEMYTYPE] = {
	{
		 D3DXVECTOR3(SCREEN_GAME_WIDTH / 2, -SCREEN_GAME_HEIGHT / 10, 0.0f)
		, D3DXVECTOR3(0,+1.0f,0) //�ړ�����
		,0 //����(��)
		,B_FIGHTER
		,c_Tex_Divide
		,c_Tex_Divide
		,NORMAL		//TEXTURE
		,D3DXVECTOR3(200.0f,100.0f,0)//SIZE
		,100	//Hp
		,1	//Power
		,20	//Power
		,ENEMY_STATE_NORMAL	//�G�̏��
		,0					//��Ԍo�ߎ���	
		,BOSS_STATE_APPEAR1	//�G��AI
		,0					//AI�̏�Ԍo�ߎ���	
		,false
		,B_FIGHTER			//�G�̃^�C�v
		,5					//�e�̎ˏo���o
		,0
		,0
		,2.5f		//�e�̃X�s�[�h
		,0.0f		
		,0.0f		//�ړ��p�x
		,0.0f		//�ˏo�p�x
		,false		//�G�̖��G�t���O
		,0.0f		//�G�̖��G����
	}
	,
	{
		D3DXVECTOR3(SCREEN_GAME_WIDTH / 2, -SCREEN_GAME_HEIGHT / 10, 0.0f)
		, D3DXVECTOR3(0,+1.0f,0) //�ړ�����
		,0 //����(��)
		,B_LASER
		,NON_DIVIDE
		,NON_DIVIDE
		,NON_DIVIDE_TEXTURENUMBER
		,D3DXVECTOR3(100.0f,100.0f,0)//SIZE
		,100	//Hp
		,2	//Power
		,40	//Power
		,ENEMY_STATE_NORMAL	//�G�̏��
		,0					//��Ԍo�ߎ���	
		,BOSS_STATE_APPEAR1	//�G��AI
		,0					//AI�̏�Ԍo�ߎ���	
		,false
		,B_LASER			//�G�̃^�C�v
		,5					//�e�̎ˏo���o
		,0
		,0
		,2.5f		//�e�̃X�s�[�h
		,0.0f
		,0.0f		//�ړ��p�x
		,0.0f		//�ˏo�p�x
		,false		//�G�̖��G�t���O
		,0.0f		//�G�̖��G����
	},
	{
		D3DXVECTOR3(SCREEN_GAME_WIDTH / 2, -SCREEN_GAME_HEIGHT / 10, 0.0f)
		, D3DXVECTOR3(0,+1.0f,0) //�ړ�����
		,0 //����(��)
		,B_FINAL
		,NON_DIVIDE
		,NON_DIVIDE
		,NON_DIVIDE_TEXTURENUMBER
		,D3DXVECTOR3(100.0f,100.0f,0)//SIZE
		,100	//Hp
		,1	//Power
		,100	//Power
		,ENEMY_STATE_NORMAL	//�G�̏��
		,0					//��Ԍo�ߎ���	
		,BOSS_STATE_APPEAR1	//�G��AI
		,0					//AI�̏�Ԍo�ߎ���	
		,false
		,B_FINAL			//�G�̃^�C�v
		,5					//�e�̎ˏo���o
		,0
		,0
		,2.5f		//�e�̃X�s�[�h
		,0.0f
		,0.0f		//�ړ��p�x
		,0.0f		//�ˏo�p�x
		,false		//�G�̖��G�t���O
		,0.0f		//�G�̖��G����
	}
};

static VERTEX_2D g_Vertex[B_MAX_ENEMYTYPE][4];


void InitBoss()
{
	g_Boss = tblBoss[0];
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int i = 0; i < B_MAX_ENEMYTYPE; i++)
	{
		SetTextureDATA
		(
			pDevice,
			g_PolygonVertex[i],
			&g_texture[i],
			&c_InitTexture[i]
		);
	}
	
}


void UninitBoss()
{
	for (int i = 0; i < B_MAX_ENEMYTYPE; i++)
	{
		UnLoadTextureDATA(&g_texture[i]);
	}
}


void UpdateBoss()
{
	for (int i = 0; i < B_MAX_ENEMYTYPE; i++)
	{
		//�L���t���O��ON����Ȃ���Ή������Ȃ�
		if (g_Boss.isEnable == false)
			continue;
		Boss_AI_Update(&g_Boss);

		//�G�̏�Ԃɂ�苓���̈ꎞ�I�ȕύX
		switch (g_Boss.State)
		{
		case ENEMY_STATE_NORMAL:
			break;
		case ENEMY_STATE_DAMAGE:
			EnemyDamageState(&g_Boss);
			break;
		default:
			break;
		}		
		//���G���Ԃ��v�����A���Ԃ𒴂�����OFF�ɂ���
		if (g_Boss.Enemy_Mutekiflg) {
			g_Boss.Muteki_time += 1.0f / 120.0f;
			if (g_Boss.Muteki_time>BOSS_DMGHIT_MUTEKITIME) {
				g_Boss.Muteki_time = 0;
				g_Boss.Enemy_Mutekiflg = false;
			}
		}

	}
}


void DrawBoss()
{

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int i = 0; i < B_MAX_ENEMYTYPE; i++)
	{
		//�L���t���O��ON����Ȃ���Ή������Ȃ�
		if (g_Boss.isEnable == false)
			continue;
		//ENEMY�f�[�^���e�N�X�`���[�Ɋi�[����
		int textureType = g_Boss.int1;

		if (!g_texture[textureType].IsEnable)
			continue;

		g_texture[textureType].Pos = g_Boss.pos;
		g_texture[textureType].Angle = g_Boss.Rotation;
		g_texture[textureType].Size_x = g_Boss.size.x;
		g_texture[textureType].Size_y = g_Boss.size.y;

		DrawTextureDATA(
			pDevice,
			&g_texture[textureType]
		);
	}

}

void SetBoss(int BossType)
{
	g_Boss = tblBoss[BossType];

	g_Boss.pos.x = SCREEN_GAME_WIDTH/2;
	g_Boss.pos.y = -32.0f;

	//�ړ����������߂�
	g_Boss.dir.x = 0.0f;
	g_Boss.dir.y = 0.5f;
	//HP�ݒ�
	//BOSS�̏��
	g_Boss.State = BOSS_STATE_APPEAR1;
	//�L�����t���O��ON�ɂ���
	g_Boss.isEnable = true;

	//life�̏o����ON�ɂ���
	Ui_Boss_SetTextureEnable();
	SetBossLifeData(g_Boss.Hp);
	SetBossDate(g_Boss);
}

//EMITTER�g�p�� ADD
void SetBoss(D3DXVECTOR3 pos, D3DXVECTOR3 dir,int BossType)
{
	if (g_Boss.isEnable == false)
	{
		//�����_���ŕ\���ʒu�����߂�
		g_Boss.pos = pos;

		//�ړ����������߂�
		g_Boss.dir = dir;

		//HP�ݒ�
		g_Boss.Hp = 200;
		//�L�����t���O��ON�ɂ���
		g_Boss.isEnable = true;

	}
}


//�L���t���O��n��
bool GetIsEnableBoss()
{
	return g_Boss.isEnable;
}

/*�����̊֐����ł̂ݎg�p*/
//Boss��Getter
ENEMY* GetBoss() {
	return (&g_Boss);
}


void EnemyDamageState(ENEMY* enemy) {
	enemy->State_time += 1 / 60.0f;

	if (enemy->State_time > BOSS_DMGHIT_TIME)
	{
		enemy->State_time = 0;
		enemy->State = ENEMY_STATE_NORMAL;
	}
}