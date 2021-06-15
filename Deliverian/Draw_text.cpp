//=============================================================================
//
// �e�L�X�g���� [Draw_text.cpp]
//
//=============================================================================
#include "Draw_text.h"

//*****************************************************************************
// �p�����[�^�\���̒�`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static LPDIRECT3DDEVICE9		g_pD3DDevice = NULL;		// Device�I�u�W�F�N�g(�`��ɕK�v)
static LPD3DXFONT g_pFont = NULL;


//=============================================================================
// ����������
//=============================================================================
void InitText()
{
	g_pD3DDevice = GetDevice();

	D3DXCreateFont(
		g_pD3DDevice,
		20,
		10,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		"Times New Roman",
		&g_pFont
	);

}

//=============================================================================
// �I������
//=============================================================================
void UninitText(void)
{
	g_pFont->Release();
}


//=============================================================================
// �����`�揈��
//=============================================================================
void Drawtextfnc(void)
{
	RECT rect = { 100, 0, SCREEN_GAME_WIDTH, SCREEN_GAME_HEIGHT };
	TCHAR str[256];

	//_t
	wsprintf(str, _T("time:"));

	// �e�L�X�g�`��
	g_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
}


void Drawtextfnc(char* drawText)
{
	RECT rect = { 200, 30, SCREEN_GAME_WIDTH, SCREEN_GAME_HEIGHT };

	// �e�L�X�g�`��
	g_pFont->DrawText(NULL, drawText, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
}

//�ʒu�w��
void Drawtextfnc(char* drawText, RECT rect)
{
	// �e�L�X�g�`��
	g_pFont->DrawText(NULL, drawText, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
}

//�ʒu�E�F�w��
void Drawtextfnc(char* drawText, RECT rect, D3DXVECTOR4 color)
{
	// �e�L�X�g�`��
	g_pFont->DrawText(NULL, drawText, -1, &rect, DT_LEFT, D3DCOLOR_ARGB((int)color.x, (int)color.y, (int)color.z, (int)color.w));
}