
#include "main.h"
#include "Func_texture.h"
#include "bgtop.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

static LPDIRECT3DTEXTURE9		g_pD3DTexture = NULL;		// �e�N�X�`���ւ̃|�C���^

static VERTEX_2D g_BgTopVertex[4];
unsigned int g_BgTopTexture;
static D3DXVECTOR3 g_BgTopPosition[2];
static float g_Texture_Sabun;

//3�����z��͂܂����C������c�v�C��
static VERTEX_2D g_BgVertex[TEXTURE_BG_SCROLLPAGECOUNT][MAX_STAGE_TYPE+1][4];

const Texture_DATA g_Bg_InitTexture[] =
{
	{
		(char *)"TEXTURE/Bg/sky.tga"
		,NULL
		,NULL
		,D3DXVECTOR3(SCREEN_GAME_WIDTH / 2, SCREEN_GAME_HEIGHT / 2, 0.0f)
		,SCREEN_GAME_WIDTH
		,SCREEN_GAME_HEIGHT
		,false
	},
	{
		(char *)"TEXTURE/Bg/Space.png"
		,NULL
		,NULL
		,D3DXVECTOR3(SCREEN_GAME_WIDTH / 2, SCREEN_GAME_HEIGHT / 2, 0.0f)
		,SCREEN_GAME_WIDTH
		,SCREEN_GAME_HEIGHT
		,false
	},
	{
		(char *)"TEXTURE/Bg/Asteroid.png"
		,NULL
		,NULL
		,D3DXVECTOR3(SCREEN_GAME_WIDTH / 2, SCREEN_GAME_HEIGHT / 2, 0.0f)
		,SCREEN_GAME_WIDTH
		,SCREEN_GAME_HEIGHT
		,false
	},
	{
		(char *)"TEXTURE/Bg/sea.tga"
		,NULL
		,NULL
		,D3DXVECTOR3(SCREEN_GAME_WIDTH / 2, SCREEN_GAME_HEIGHT / 2, 0.0f)
		,SCREEN_GAME_WIDTH
		,SCREEN_GAME_HEIGHT
		,false
	},
};

//�X�N���[���p�ɓ񖇗p�ӂ���
static Texture_DATA g_Bg_texture[TEXTURE_BG_SCROLLPAGECOUNT][MAX_STAGE_TYPE+1];


void InitBgTop()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int i = 0; i < MAX_STAGE_TYPE+1; i++)
	{
		for (int iScroll = 0; iScroll < TEXTURE_BG_SCROLLPAGECOUNT; iScroll++)
		{
			//�\��������
			g_Bg_texture[0][i] =
				g_Bg_InitTexture[i];
			//���_���W�̐ݒ�
			MakeVertex(g_BgVertex[iScroll][i]);

			SetTexture(g_BgVertex[iScroll][i],
				TEXTURE_BG_DIVIDE_X,
				TEXTURE_BG_DIVIDE_Y);

			//�ꏊ����
			SetVertex(g_BgVertex[iScroll][i],
				g_Bg_texture[0][i].Pos,
				g_Bg_texture[0][i].Size_x,
				g_Bg_texture[0][i].Size_y);

			// �e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
				g_Bg_texture[0][i].Path,				// �t�@�C���̖��O
				&g_Bg_texture[0][i].pD3DTexture);					// �ǂݍ��ރ������̃|�C���^

																		//�񖇖ڂɑ}��
			g_Bg_texture[1][i] = g_Bg_texture[0][i];
			g_Bg_texture[1][i].Pos = D3DXVECTOR3(SCREEN_GAME_WIDTH / 2, SCREEN_GAME_HEIGHT + SCREEN_GAME_HEIGHT / 2, 0.0f);

		}
	}
}



void UninitBgTop()
{
	for (int i = 0; i < MAX_STAGE_TYPE+1; i++)
	{
		if (g_Bg_texture[0][i].pD3DTexture != NULL)
		{	// �e�N�X�`���̊J��
			g_Bg_texture[0][i].pD3DTexture->Release();
			g_Bg_texture[0][i].pD3DTexture = NULL;
			g_Bg_texture[1][i].pD3DTexture = NULL;
		}
	}
}

//�Q���̃e�N�X�`���[���X�N���[�����邱�Ƃŗ��̊����o��
void UpdateBgTop()
{


	for (int i = 0; i < MAX_STAGE_TYPE; i++)
	{
		for (int iScroll = 0; iScroll < TEXTURE_BG_SCROLLPAGECOUNT; iScroll++)
		{
			if (!g_Bg_texture[iScroll][i].IsEnable)
				continue;

			//g_BgTopPosition[0].y -= 8.0f;
			g_Bg_texture[iScroll][i].Pos.y -= 8.0f;
			if (g_Bg_texture[iScroll][i].Pos.y
				<= -SCREEN_GAME_HEIGHT + SCREEN_GAME_HEIGHT / 2)
			{
				g_Bg_texture[iScroll][i].Pos.y = SCREEN_GAME_HEIGHT + SCREEN_GAME_HEIGHT / 2;
			}
		}
		
	}
}



void DrawBgTop()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (int i = 0; i < MAX_STAGE_TYPE; i++)
	{
		for (int iScroll = 0; iScroll < TEXTURE_BG_SCROLLPAGECOUNT; iScroll++)
		{
			if (!g_Bg_texture[iScroll][i].IsEnable)
				continue;

			if (i == 0)
			{
				//�ꏊ����
				SetVertex(g_BgVertex[iScroll][TEXTURE_BG_SKYSEA],
					g_Bg_texture[iScroll][TEXTURE_BG_SKYSEA].Pos,
					g_Bg_texture[iScroll][TEXTURE_BG_SKYSEA].Size_x,
					g_Bg_texture[iScroll][TEXTURE_BG_SKYSEA].Size_y);

				// ���_�t�H�[�}�b�g�̐ݒ�
				pDevice->SetFVF(FVF_VERTEX_2D);
				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_Bg_texture[iScroll][TEXTURE_BG_SKYSEA].pD3DTexture);
				// �|���S���̕`��
				pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_PLAYER, g_BgVertex[iScroll][TEXTURE_BG_SKYSEA], sizeof(VERTEX_2D));

			}
			//�ꏊ����
			SetVertex(g_BgVertex[iScroll][i],
				g_Bg_texture[iScroll][i].Pos,
				g_Bg_texture[iScroll][i].Size_x,
				g_Bg_texture[iScroll][i].Size_y);

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_2D);
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_Bg_texture[iScroll][i].pD3DTexture);
			// �|���S���̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_PLAYER, g_BgVertex[iScroll][i], sizeof(VERTEX_2D));

		}
	}
}

//STAGE.CPP�̂ݎg�p
void Bg_SetTextureEnable(STAGE_TYPE index) {

	for (int iScroll = 0; iScroll < TEXTURE_BG_SCROLLPAGECOUNT; iScroll++)
	{
		g_Bg_texture[iScroll][index].IsEnable = true;
		if(index== SKY)g_Bg_texture[iScroll][TEXTURE_BG_SKYSEA].IsEnable = true;
	}

}

//*****************************************************************************
// �������牺�͂��̊֐��݂̂Ŏg����֐�
//*****************************************************************************
