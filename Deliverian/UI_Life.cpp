#include "UI_Life.h"
#include "Func_texture.h"
#include "scene.h"
#include "player.h"
#include "game.h"
#include "stage.h"//ヘッダーのenum取得のため
#include "Draw_text.h"


#define TEXTURE_TITLE_PUSH_ANIME_TIME	(0.05)	// アニメパターンのテクスチャの変化時間
#define TEXTURE_TITLE_PUSH_ANIME_LIMIT	4	// アニメパターンのテクスチャの変化上限
#define Life_POS_X SCREEN_GAME_WIDTH+SCREEN_WIDTH /10
#define Life_POS_Y SCREEN_HEIGHT / 8 * 7
#define Life_SIZE_X (SCREEN_WIDTH-SCREEN_GAME_WIDTH)/4*3

//メンバ変数のようなもの
static VERTEX_2D g_Ui_Life_Vertex[ENUM_TEXTURE_UI_LIFE_MAX][4];

static float g_Title_Push_Time;			//表示テクスチャー計算用
static unsigned int g_Title_Push_Number;	//表示テクスチャー位置

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

//SideGageの終端位置
static D3DXVECTOR3 g_GreenBarEpos;

void Ui_Life_Initialize(void)
{
	g_UI_Life = 0;
	g_UI_Score = 0;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int i = 0; i < ENUM_TEXTURE_UI_LIFE_MAX; i++)
	{
		//表示初期化
		g_Ui_Life_texture[i] =
			g_Ui_Life_InitTexture[i];
		//頂点座標の設定
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

		//場所決定
		SetVertex(g_Ui_Life_Vertex[i],
			g_Ui_Life_texture[i].Pos,
			g_Ui_Life_texture[i].Size_x,
			g_Ui_Life_texture[i].Size_y);

		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,		// デバイスのポインタ
			g_Ui_Life_texture[i].Path,				// ファイルの名前
			&g_Ui_Life_texture[i].pD3DTexture);					// 読み込むメモリのポインタ

		g_Ui_Life_texture[i].Vertex = g_Ui_Life_Vertex[i];
	}
}

void Ui_Life_Finalize(void)
{
	for (int i = 0; i < ENUM_TEXTURE_UI_LIFE_MAX; i++)
	{
		if (g_Ui_Life_texture[i].pD3DTexture != NULL)
		{	// テクスチャの開放
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

		
		//場所決定
		SetVertex(g_Ui_Life_Vertex[i],
			g_Ui_Life_texture[i].Pos,
			g_Ui_Life_texture[i].Size_x,
			g_Ui_Life_texture[i].Size_y);
		

		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);
		// テクスチャの設定
		pDevice->SetTexture(0, g_Ui_Life_texture[i].pD3DTexture);
		// ポリゴンの描画

		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_PLAYER, g_Ui_Life_Vertex[i], sizeof(VERTEX_2D));
	}



	//テキスト描画処理：プレイヤー関連

	TCHAR str[256];
	RECT rect = { SCREEN_GAME_WIDTH+ Life_SIZE_X/10, Life_POS_Y- 80, SCREEN_GAME_WIDTH + 100, SCREEN_GAME_HEIGHT };

	//HPの描画0以下のなら0と表示する
	if (g_UI_Life<0)
	{
		wsprintf(str, _T("HP:%d\n"), 0);
	}
	else
	{
		wsprintf(str, _T("HP:%d\n"), g_UI_Life);
	}
	
	Drawtextfnc(str, rect);

	//Scoreの描画
	rect = { SCREEN_GAME_WIDTH+Life_SIZE_X / 10, Life_POS_Y- 120, SCREEN_GAME_WIDTH+100, SCREEN_GAME_HEIGHT };
	wsprintf(str, _T("SCORE:\n%d\n"), g_UI_Score);
	Drawtextfnc(str, rect);
}

void Ui_Life_Set(int Hp)
{
	//UIにライフを反映させる
	g_UI_Life = Hp;
	if (g_UI_Life > 2)
	{
		MakeVertex(g_Ui_Life_Vertex[ENUM_TEXTURE_UI_LIFE_Filter]);
	}
	//黄色
	else if (g_UI_Life ==2)
	{
		MakeVertex(g_Ui_Life_Vertex[ENUM_TEXTURE_UI_LIFE_Filter]
			, D3DXVECTOR4(255, 255, 0, 255));
	}
	//赤
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
// ここから下はこの関数のみで使われる関数
//*****************************************************************************
