
#include "main.h"
#include "Func_texture.h"
#include "bgBlack.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

static LPDIRECT3DTEXTURE9		g_pD3DTexture = NULL;		// テクスチャへのポインタ


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

//スクロール用に二枚用意する
static Texture_DATA g_BgBlack_texture[1];


void InitBgBlack()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//表示初期化
	g_BgBlack_texture[0] =
		g_BgBlack_InitTexture[0];
	//頂点座標の設定
	MakeVertex(g_BgBlackVertex[0]);

	SetTexture(g_BgBlackVertex[0],
		TEXTURE_BG_DIVIDE_X,
		TEXTURE_BG_DIVIDE_Y);

	//場所決定
	SetVertex(g_BgBlackVertex[0],
		g_BgBlack_texture[0].Pos,
		g_BgBlack_texture[0].Size_x,
		g_BgBlack_texture[0].Size_y);

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,		// デバイスのポインタ
		g_BgBlack_texture[0].Path,				// ファイルの名前
		&g_BgBlack_texture[0].pD3DTexture);					// 読み込むメモリのポインタ


}



void UninitBgBlack()
{
	if (g_BgBlack_texture[0].pD3DTexture != NULL)
	{	// テクスチャの開放
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

	//場所決定
	SetVertex(g_BgBlackVertex[0],
		g_BgBlack_texture[0].Pos,
		g_BgBlack_texture[0].Size_x,
		g_BgBlack_texture[0].Size_y);

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	// テクスチャの設定
	pDevice->SetTexture(0, g_BgBlack_texture[0].pD3DTexture);
	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_PLAYER, g_BgBlackVertex[0], sizeof(VERTEX_2D));

}



//*****************************************************************************
// ここから下はこの関数のみで使われる関数
//*****************************************************************************
