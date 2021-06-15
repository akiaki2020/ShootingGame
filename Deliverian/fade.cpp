
#include "main.h"
#include "Func_texture.h"
#include "fade.h"
#include "scene.h"
#include "sound.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define FVF_FADE_VERTEX (D3DFVF_XYZRHW|D3DFVF_DIFFUSE)
#define FADE_SPEED (120) //大きくなるほどフェード時間が長くなる
#define TEXTURE_FADE_SAMPLE00	_T("TEXTURE/white.tga")	// サンプル用画像

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

static LPDIRECT3DTEXTURE9		g_pD3DTexture = NULL;		// テクスチャへのポインタ

static VERTEX_2D g_FadeTopVertex[4];//画面フェード用頂点
static D3DXVECTOR3 g_FadePosition;//ポジション

//フェード状態
enum FADE_STATE
{
	FADE_STATE_NONE,
	FADE_STATE_IN,
	FADE_STATE_OUT
};

FADE_STATE	g_FadeState;		//フェードの状態
SCENE_INDEX	g_FadeNextState;	//フェードアウト後に移行するシーン
float		g_FadeAlpha;		//現在のアルファ値


unsigned int g_FadeTexture;		//フェード用テクスチャ

typedef struct FadeVertex_tag
{
	D3DXVECTOR4 position;
	D3DCOLOR color;
} FadeVertex;


static D3DXCOLOR g_FadeColor(0.0f, 0.0f, 0.0f, 1.0f);
static float g_Alpha = 0.0f;
static float g_AddAlpha = 0.0f;


void InitFade()
{

	g_FadeState = FADE_STATE_NONE;
	g_FadeNextState = SCENE_INDEX_MAX;
	g_FadeAlpha = 0.0f;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	g_FadePosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//頂点座標の設定
	MakeVertex(g_FadeTopVertex);
	SetTexture(g_FadeTopVertex,
		TEXTURE_FADE_DIVIDE_X,
		TEXTURE_FADE_DIVIDE_Y);

	SetVertex(g_FadeTopVertex,
		g_FadePosition,
		SCREEN_WIDTH,
		SCREEN_HEIGHT );
	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,		// デバイスのポインタ
		TEXTURE_FADE_SAMPLE00,				// ファイルの名前
		&g_pD3DTexture);					// 読み込むメモリのポインタ


}



void UninitFade()
{
	if (g_pD3DTexture != NULL)
	{	// テクスチャの開放
		g_pD3DTexture->Release();
		g_pD3DTexture = NULL;
	}
}


void UpdateFade()
{
	//フェードアウト中
	if (g_FadeState == FADE_STATE_OUT)
	{

		//アルファ値が1.0を超えたら
		if (g_FadeAlpha >= 1.0f)
		{
			//シーンを切り替えてフェードインに移行する
			g_FadeAlpha = 1.0f;
			g_FadeState = FADE_STATE_IN;
			GetMasteringVoice()->SetVolume(1.0 - g_FadeAlpha);
			Scene_Change(g_FadeNextState);

		}
		GetMasteringVoice()->SetVolume(1.0 - g_FadeAlpha);
		//アルファ値を増加させる
		g_FadeAlpha += 1.0f / FADE_SPEED;

	}//フェードイン中
	else if (g_FadeState == FADE_STATE_IN)
	{
		//アルファ値がゼロより小さくなったら
		if (g_FadeAlpha <= 0.0f)
		{
			//フェードを終了させる
			g_FadeAlpha = 0.0f;
			GetMasteringVoice()->SetVolume(1.0 - g_FadeAlpha);
			g_FadeState = FADE_STATE_NONE;
		}
		GetMasteringVoice()->SetVolume(1.0 - g_FadeAlpha);
		//アルファ値を減少させる
		g_FadeAlpha -= 1.0f / FADE_SPEED;
	}
}



void DrawFade()
{
	//フェードが終了しているなら何もしない
	if (g_FadeState == FADE_STATE_NONE)
		return;

	g_FadeColor.a = g_FadeAlpha;
	D3DCOLOR c = g_FadeColor;

	FadeVertex v[] = {
	{ D3DXVECTOR4(0.0f,          0.0f, 0.0f, 1.0f), c },
	{ D3DXVECTOR4(SCREEN_WIDTH,          0.0f, 0.0f, 1.0f), c },
	{ D3DXVECTOR4(0.0f, SCREEN_HEIGHT, 0.0f, 1.0f), c },
	{ D3DXVECTOR4(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 1.0f), c },
	};

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetFVF(FVF_FADE_VERTEX);
	pDevice->SetTexture(0, NULL);
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(FadeVertex));
}




//フェード処理
void Fade(SCENE_INDEX nextScene)
{
	//フェードアウト後に移行するシーン
	g_FadeNextState = nextScene;
	//フェードアウトスタート
	g_FadeState = FADE_STATE_OUT;
}