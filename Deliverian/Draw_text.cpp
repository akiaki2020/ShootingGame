//=============================================================================
//
// テキスト処理 [Draw_text.cpp]
//
//=============================================================================
#include "Draw_text.h"

//*****************************************************************************
// パラメータ構造体定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************
static LPDIRECT3DDEVICE9		g_pD3DDevice = NULL;		// Deviceオブジェクト(描画に必要)
static LPD3DXFONT g_pFont = NULL;


//=============================================================================
// 初期化処理
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
// 終了処理
//=============================================================================
void UninitText(void)
{
	g_pFont->Release();
}


//=============================================================================
// 文字描画処理
//=============================================================================
void Drawtextfnc(void)
{
	RECT rect = { 100, 0, SCREEN_GAME_WIDTH, SCREEN_GAME_HEIGHT };
	TCHAR str[256];

	//_t
	wsprintf(str, _T("time:"));

	// テキスト描画
	g_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
}


void Drawtextfnc(char* drawText)
{
	RECT rect = { 200, 30, SCREEN_GAME_WIDTH, SCREEN_GAME_HEIGHT };

	// テキスト描画
	g_pFont->DrawText(NULL, drawText, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
}

//位置指定
void Drawtextfnc(char* drawText, RECT rect)
{
	// テキスト描画
	g_pFont->DrawText(NULL, drawText, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
}

//位置・色指定
void Drawtextfnc(char* drawText, RECT rect, D3DXVECTOR4 color)
{
	// テキスト描画
	g_pFont->DrawText(NULL, drawText, -1, &rect, DT_LEFT, D3DCOLOR_ARGB((int)color.x, (int)color.y, (int)color.z, (int)color.w));
}