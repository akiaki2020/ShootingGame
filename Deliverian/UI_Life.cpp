#include "UI_Life.h"
#include "Func_texture.h"
#include "scene.h"
#include "player.h"
#include "game.h"
#include "stage.h"//�w�b�_�[��enum�擾�̂���
#include "Draw_text.h"


#define TEXTURE_TITLE_PUSH_ANIME_TIME	(0.05)	// �A�j���p�^�[���̃e�N�X�`���̕ω�����
#define TEXTURE_TITLE_PUSH_ANIME_LIMIT	4	// �A�j���p�^�[���̃e�N�X�`���̕ω����
#define Life_POS_X SCREEN_GAME_WIDTH+SCREEN_WIDTH /10
#define Life_POS_Y SCREEN_HEIGHT / 8 * 7
#define Life_SIZE_X (SCREEN_WIDTH-SCREEN_GAME_WIDTH)/4*3

//�����o�ϐ��̂悤�Ȃ���
static VERTEX_2D g_Ui_Life_Vertex[ENUM_TEXTURE_UI_LIFE_MAX][4];

static float g_Title_Push_Time;			//�\���e�N�X�`���[�v�Z�p
static unsigned int g_Title_Push_Number;	//�\���e�N�X�`���[�ʒu

static int g_UI_Life;
static int g_UI_Score;


const Texture_DATA g_Ui_Life_InitTexture[ENUM_TEXTURE_UI_LIFE_MAX] =
{
	{
	(char *)"TEXTURE/Ui/Pilot.tga"
	,NULL
	,NULL
	,D3DXVECTOR3(Life_POS_X,
		Life_POS_Y, 0.0f)
	,Life_SIZE_X
	,Life_SIZE_X
	,true
	},
	{
	(char *)"TEXTURE/Ui/pilot_filter.tga"
	,NULL
	,NULL
	,D3DXVECTOR3(Life_POS_X,
		Life_POS_Y, 0.0f)
	,Life_SIZE_X
	,Life_SIZE_X
	,true
	},
	{
		(char *)"TEXTURE/Ui/Signal_lost.tga"
		,NULL
		,NULL
		,D3DXVECTOR3(Life_POS_X,
			Life_POS_Y, 0.0f)
		,Life_SIZE_X
		,Life_SIZE_X
		,false
		,0
		,0
		,false
		,TEXTURE_UI_life_Signal_DIVIDE_X
		,TEXTURE_UI_life_Signal_DIVIDE_Y
		,0
		,true
		,D3DXVECTOR4(255, 255, 255, 255)
	},
};

static Texture_DATA g_Ui_Life_texture[ENUM_TEXTURE_UI_LIFE_MAX];

//SideGage�̏I�[�ʒu
static D3DXVECTOR3 g_GreenBarEpos;

void Ui_Life_Initialize(void)
{
	g_UI_Life = 0;
	g_UI_Score = 0;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int i = 0; i < ENUM_TEXTURE_UI_LIFE_MAX; i++)
	{
		//�\��������
		g_Ui_Life_texture[i] =
			g_Ui_Life_InitTexture[i];
		//���_���W�̐ݒ�
		if (i != ENUM_TEXTURE_UI_LIFE_Filter)
		{
			MakeVertex(g_Ui_Life_Vertex[i]);
		}
		else
		{
			MakeVertex(g_Ui_Life_Vertex[i]
				, D3DXVECTOR4(0, 0, 0, 120));
		}
		

		SetTexture(g_Ui_Life_Vertex[i],
			TEXTURE_UI_DIVIDE_X,
			TEXTURE_UI_DIVIDE_Y);

		//�ꏊ����
		SetVertex(g_Ui_Life_Vertex[i],
			g_Ui_Life_texture[i].Pos,
			g_Ui_Life_texture[i].Size_x,
			g_Ui_Life_texture[i].Size_y);

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
			g_Ui_Life_texture[i].Path,				// �t�@�C���̖��O
			&g_Ui_Life_texture[i].pD3DTexture);					// �ǂݍ��ރ������̃|�C���^

		g_Ui_Life_texture[i].Vertex = g_Ui_Life_Vertex[i];
	}
}

void Ui_Life_Finalize(void)
{
	for (int i = 0; i < ENUM_TEXTURE_UI_LIFE_MAX; i++)
	{
		if (g_Ui_Life_texture[i].pD3DTexture != NULL)
		{	// �e�N�X�`���̊J��
			g_Ui_Life_texture[i].pD3DTexture->Release();
			g_Ui_Life_texture[i].pD3DTexture = NULL;
		}
	}
}

void Ui_Life_Update(void)
{
	g_Title_Push_Time += 1.0f / 120.0f;
	if (g_Title_Push_Time>TEXTURE_TITLE_PUSH_ANIME_TIME)
	{
		g_Title_Push_Time = 0.0f;
		g_Ui_Life_texture[ENUM_TEXTURE_UI_LIFE_Signal].TextureNumber += 1;
		if (g_Ui_Life_texture[ENUM_TEXTURE_UI_LIFE_Signal].TextureNumber>TEXTURE_TITLE_PUSH_ANIME_LIMIT)
		{
			g_Ui_Life_texture[ENUM_TEXTURE_UI_LIFE_Signal].TextureNumber = 0;
		}

		SetTexture(g_Ui_Life_texture[ENUM_TEXTURE_UI_LIFE_Signal].Vertex,
			g_Ui_Life_texture[ENUM_TEXTURE_UI_LIFE_Signal].Divide_x,
			g_Ui_Life_texture[ENUM_TEXTURE_UI_LIFE_Signal].Divide_y
			, g_Ui_Life_texture[ENUM_TEXTURE_UI_LIFE_Signal].TextureNumber);
	}

}

void Ui_Life_Draw(void)
{

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int i = 0; i < ENUM_TEXTURE_UI_LIFE_MAX; i++)
	{
		if (!g_Ui_Life_texture[i].IsEnable)
			continue;

		
		//�ꏊ����
		SetVertex(g_Ui_Life_Vertex[i],
			g_Ui_Life_texture[i].Pos,
			g_Ui_Life_texture[i].Size_x,
			g_Ui_Life_texture[i].Size_y);
		

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);
		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_Ui_Life_texture[i].pD3DTexture);
		// �|���S���̕`��

		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_PLAYER, g_Ui_Life_Vertex[i], sizeof(VERTEX_2D));
	}



	//�e�L�X�g�`�揈���F�v���C���[�֘A

	TCHAR str[256];
	RECT rect = { SCREEN_GAME_WIDTH+ Life_SIZE_X/10, Life_POS_Y- 80, SCREEN_GAME_WIDTH + 100, SCREEN_GAME_HEIGHT };

	//HP�̕`��0�ȉ��̂Ȃ�0�ƕ\������
	if (g_UI_Life<0)
	{
		wsprintf(str, _T("HP:%d\n"), 0);
	}
	else
	{
		wsprintf(str, _T("HP:%d\n"), g_UI_Life);
	}
	
	Drawtextfnc(str, rect);

	//Score�̕`��
	rect = { SCREEN_GAME_WIDTH+Life_SIZE_X / 10, Life_POS_Y- 120, SCREEN_GAME_WIDTH+100, SCREEN_GAME_HEIGHT };
	wsprintf(str, _T("SCORE:\n%d\n"), g_UI_Score);
	Drawtextfnc(str, rect);
}

void Ui_Life_Set(int Hp)
{
	//UI�Ƀ��C�t�𔽉f������
	g_UI_Life = Hp;
	if (g_UI_Life > 2)
	{
		MakeVertex(g_Ui_Life_Vertex[ENUM_TEXTURE_UI_LIFE_Filter]);
	}
	//���F
	else if (g_UI_Life ==2)
	{
		MakeVertex(g_Ui_Life_Vertex[ENUM_TEXTURE_UI_LIFE_Filter]
			, D3DXVECTOR4(255, 255, 0, 255));
	}
	//��
	else if (g_UI_Life == 1)
	{
		MakeVertex(g_Ui_Life_Vertex[ENUM_TEXTURE_UI_LIFE_Filter]
			, D3DXVECTOR4(255, 0, 0, 255));
	}
	else if (g_UI_Life < 1)
	{
		g_Ui_Life_texture[ENUM_TEXTURE_UI_LIFE_Signal].IsEnable = true;
	}
}

void Ui_Score_Set(int Score)
{
	g_UI_Score = Score;
}

//*****************************************************************************
// �������牺�͂��̊֐��݂̂Ŏg����֐�
//*****************************************************************************
