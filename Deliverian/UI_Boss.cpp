#include "UI_Boss.h"
#include "Func_texture.h"
#include "scene.h"
#include "game.h"
#include "stage.h"//�w�b�_�[��enum�擾�̂���

// �}�N����`
#define TEXTURE_UI_DIVIDE_X	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_UI_DIVIDE_Y	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define BOSSGAGE_POS_X SCREEN_GAME_WIDTH / 2
#define BOSSGAGE_POS_Y (40)
#define BOSSGAGE_SIZE_X (SCREEN_GAME_WIDTH-50)
#define BOSSGAGE_SIZE_Y (20)
#define MOZI_SIZE_X (80)
#define MOZI_SIZE_Y (20)
#define MOZI_POS_X (BOSSGAGE_POS_X-BOSSGAGE_SIZE_X/2+MOZI_SIZE_X/2)
#define MOZI_POS_Y (BOSSGAGE_POS_Y-BOSSGAGE_SIZE_Y/2-MOZI_SIZE_Y)


//*****************************************************************************
// CONST�ϐ�
//*****************************************************************************


enum UI_TEXTURE
{
	ENUM_TEXTURE_UI_BOSS_TEXT,
	ENUM_TEXTURE_UI_BOSS_HPBG,
	ENUM_TEXTURE_UI_BOSS_HPBAR,
	ENUM_TEXTURE_UI_BOSS_HPLINE,
	ENUM_TEXTURE_UI_BOSS_MAX,
};



static Texture_DATA c_InitTexture[] =
{
	{
		(char *)"TEXTURE/Ui/Boss.png"
		,NULL
		,NULL
		,D3DXVECTOR3(MOZI_POS_X,MOZI_POS_Y, 0.0f)
		,MOZI_SIZE_X
		,MOZI_SIZE_Y
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
		(char *)"TEXTURE/Ui/HealthBar_back.png"
		,NULL
		,NULL
		,D3DXVECTOR3(BOSSGAGE_POS_X,
			BOSSGAGE_POS_Y, 0.0f)
		,BOSSGAGE_SIZE_X
		,BOSSGAGE_SIZE_Y
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
		(char *)"TEXTURE/Ui/HealthBarBase.png"
		,NULL
		,NULL
		,D3DXVECTOR3(BOSSGAGE_POS_X - BOSSGAGE_SIZE_X / 2,
			BOSSGAGE_POS_Y, 0.0f)	//�n�_�̈ʒu
		,BOSSGAGE_SIZE_X		//�ŏ��̒�����0
		,BOSSGAGE_SIZE_Y	
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
		(char *)"TEXTURE/Ui/HealthBarBase_Line.png"
		,NULL
		,NULL
		,D3DXVECTOR3(BOSSGAGE_POS_X,
			BOSSGAGE_POS_Y, 0.0f)
		,BOSSGAGE_SIZE_X
		,BOSSGAGE_SIZE_Y
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
// �O���[�o���ϐ�
//*****************************************************************************
static VERTEX_2D g_PolygonVertex[ENUM_TEXTURE_UI_BOSS_MAX][4];
static Texture_DATA g_texture[ENUM_TEXTURE_UI_BOSS_MAX];

//SideGage�̏I�[�ʒu
static D3DXVECTOR3 g_HelthBarEpos;
static int g_HelthBoss;
static int g_MaxHelthBoss;



void Ui_Boss_Initialize(void)
{

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (int i = 0; i < ENUM_TEXTURE_UI_BOSS_MAX; i++)
	{
		SetTextureDATA
		(
			pDevice,
			g_PolygonVertex[i],
			&g_texture[i],
			&c_InitTexture[i]
		);
	}
	g_HelthBarEpos = g_texture[ENUM_TEXTURE_UI_BOSS_HPBAR].Pos;
	g_MaxHelthBoss=g_HelthBoss = 0;

}

void Ui_Boss_Finalize(void)
{
	for (int i = 0; i < ENUM_TEXTURE_UI_BOSS_MAX; i++)
	{
		UnLoadTextureDATA(&g_texture[i]);
	}
}

void Ui_Boss_Update(void)
{

}

void Ui_Boss_Draw(void)
{

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int i = 0; i < ENUM_TEXTURE_UI_BOSS_MAX; i++)
	{
		if (!g_texture[i].IsEnable)
			continue;

		if (i == ENUM_TEXTURE_UI_BOSS_HPBAR)
		{
			D3DXVECTOR3 Epos = g_texture[i].Pos;
			Epos.x += g_texture[i].Size_x;
			//GreenGage�̂ݓ���ȏꏊ����i�ρj
			SetHorizoneVeticalSpread(g_texture[i].Vertex,
				g_texture[i].Pos,	//�X�^�[�g�|�W�V����
				Epos,				//�L�у|�W�V����
				g_texture[i].Size_y);
		}
		else
		{
			//�ꏊ����
			SetVertex(g_texture[i].Vertex,
				g_texture[i].Pos,
				g_texture[i].Size_x,
				g_texture[i].Size_y);
		}

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);
		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_texture[i].pD3DTexture);
		// �|���S���̕`��

		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_PLAYER, g_texture[i].Vertex, sizeof(VERTEX_2D));

	}

}

void Ui_Boss_SetTextureEnable() 
{
	for (int i = 0; i < ENUM_TEXTURE_UI_BOSS_MAX; i++)
	{
		g_texture[i].IsEnable = true;
	}
}

void SetBossLifeData(int HP)
{
	g_MaxHelthBoss = g_HelthBoss = HP;

}

void UpdateBossLifeData(int HP)
{
	g_HelthBoss = HP;

	//HP�o�[�̒����v�Z
	if (g_HelthBoss <= 0)
	{
		g_texture[ENUM_TEXTURE_UI_BOSS_HPBAR].Size_x = 0;
	}
	else
	{
		float tempflt = (float)g_HelthBoss / (float)g_MaxHelthBoss;
		g_texture[ENUM_TEXTURE_UI_BOSS_HPBAR].Size_x = BOSSGAGE_SIZE_X * tempflt;
	}
}

//*****************************************************************************
// �������牺�͂��̊֐��݂̂Ŏg����֐�
//*****************************************************************************
