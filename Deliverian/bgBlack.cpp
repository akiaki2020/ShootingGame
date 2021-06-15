
#include "main.h"
#include "Func_texture.h"
#include "bgBlack.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

static LPDIRECT3DTEXTURE9		g_pD3DTexture = NULL;		// �e�N�X�`���ւ̃|�C���^


static VERTEX_2D g_BgBlackVertex[1][4];

const Texture_DATA g_BgBlack_InitTexture[] =
{
	{
		(char *)"TEXTURE/Bg/Black.tga"
		,NULL
		,NULL
		,D3DXVECTOR3(SCREEN_GAME_WIDTH+(SCREEN_WIDTH - SCREEN_GAME_WIDTH)/2
			, SCREEN_HEIGHT / 2, 0.0f)
		,SCREEN_WIDTH- SCREEN_GAME_WIDTH
		,SCREEN_HEIGHT
		,true
	},
};

//�X�N���[���p�ɓ񖇗p�ӂ���
static Texture_DATA g_BgBlack_texture[1];


void InitBgBlack()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�\��������
	g_BgBlack_texture[0] =
		g_BgBlack_InitTexture[0];
	//���_���W�̐ݒ�
	MakeVertex(g_BgBlackVertex[0]);

	SetTexture(g_BgBlackVertex[0],
		TEXTURE_BG_DIVIDE_X,
		TEXTURE_BG_DIVIDE_Y);

	//�ꏊ����
	SetVertex(g_BgBlackVertex[0],
		g_BgBlack_texture[0].Pos,
		g_BgBlack_texture[0].Size_x,
		g_BgBlack_texture[0].Size_y);

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
		g_BgBlack_texture[0].Path,				// �t�@�C���̖��O
		&g_BgBlack_texture[0].pD3DTexture);					// �ǂݍ��ރ������̃|�C���^


}



void UninitBgBlack()
{
	if (g_BgBlack_texture[0].pD3DTexture != NULL)
	{	// �e�N�X�`���̊J��
		g_BgBlack_texture[0].pD3DTexture->Release();
		g_BgBlack_texture[0].pD3DTexture = NULL;
		g_BgBlack_texture[1].pD3DTexture = NULL;
	}

}

void DrawBgBlack()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	if (!g_BgBlack_texture[0].IsEnable)
		return;

	//�ꏊ����
	SetVertex(g_BgBlackVertex[0],
		g_BgBlack_texture[0].Pos,
		g_BgBlack_texture[0].Size_x,
		g_BgBlack_texture[0].Size_y);

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_BgBlack_texture[0].pD3DTexture);
	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_PLAYER, g_BgBlackVertex[0], sizeof(VERTEX_2D));

}



//*****************************************************************************
// �������牺�͂��̊֐��݂̂Ŏg����֐�
//*****************************************************************************
