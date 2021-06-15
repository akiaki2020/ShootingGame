#include "UI_Draw.h"
#include "UI_Life.h"
#include "UI_Boss.h"
#include "Func_texture.h"
#include "scene.h"
#include "player.h"
#include "game.h"
#include "stage.h"//ヘッダーのenum取得のため

static VERTEX_2D g_UiVertex[ENUM_TEXTURE_UI_MAX][4];


static Texture_DATA g_Ui_InitTexture[] =
{
	{
	(char *)"TEXTURE/Ui/Gage_Red.tga"
	,NULL
	,NULL
	,D3DXVECTOR3(SIDEGAGE_POS_X,
		SIDEGAGE_POS_Y, 0.0f)
	,SIDEGAGE_SIZE_X
	,SIDEGAGE_SIZE_Y
	,true
	},
	{
	(char *)"TEXTURE/Ui/Gage_green.tga"
	,NULL
	,NULL
	,D3DXVECTOR3(SIDEGAGE_POS_X, 
		SIDEGAGE_POS_Y+ SIDEGAGE_SIZE_Y/2, 0.0f)
	,SIDEGAGE_SIZE_X
	,0					//最初の長さは0
	,true
	},
	{
	(char *)"TEXTURE/Ui/Gage_base.tga"
	,NULL
	,NULL
	,D3DXVECTOR3(SIDEGAGE_POS_X,
		SIDEGAGE_POS_Y, 0.0f)
	,SIDEGAGE_SIZE_X
	,SIDEGAGE_SIZE_Y
	,true
	},	
	{
		(char *)"TEXTURE/Ui/GAME OVER.png"
		,NULL
		,NULL
		,D3DXVECTOR3(SCREEN_GAME_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f)
		,300
		,80
		,false
	},
	{
		(char *)"TEXTURE/Ui/RETURN.png"
		,NULL
		,NULL
		,D3DXVECTOR3(SCREEN_GAME_WIDTH / 2, SCREEN_HEIGHT / 2 + SCREEN_HEIGHT / 6, 0.0f)
		,500
		,80
		,false
	},
	{
		(char *)"TEXTURE/Ui/STAGE_CLEAR!.png"
		,NULL
		,NULL
		,D3DXVECTOR3(SCREEN_GAME_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f)
		,300
		,80
		,false
	},
	{
		(char *)"TEXTURE/Ui/GOTORESULT.png"
		,NULL
		,NULL
		,D3DXVECTOR3(SCREEN_GAME_WIDTH / 2, SCREEN_HEIGHT / 2 + SCREEN_HEIGHT / 6, 0.0f)
		,350
		,40
		,false
	},
	{
		(char *)"TEXTURE/Ui/GOAL.png"
		,NULL
		,NULL
		,D3DXVECTOR3(SCREEN_GAME_WIDTH + SCREEN_WIDTH / 9,
			SIDEGAGE_POS_Y - SIDEGAGE_SIZE_Y / 2, 0.0f)
		,SIDEGAGE_MOZISIZE_X
		,SIDEGAGE_MOZISIZE_Y
		,true
	},
	{
		(char *)"TEXTURE/Ui/START.png"
		,NULL
		,NULL
		,D3DXVECTOR3(SCREEN_GAME_WIDTH + SCREEN_WIDTH / 9,
			SIDEGAGE_POS_Y+ SIDEGAGE_SIZE_Y/2, 0.0f)
		,SIDEGAGE_MOZISIZE_X
		,SIDEGAGE_MOZISIZE_Y
		,true
	},
};
static Texture_DATA g_Ui_texture[ENUM_TEXTURE_UI_MAX];

//SideGageの終端位置
static D3DXVECTOR3 g_GreenBarEpos;

void Ui_Initialize(void)
{

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int i = 0; i < ENUM_TEXTURE_UI_MAX; i++)
	{
		//表示初期化
		g_Ui_texture[i] =
			g_Ui_InitTexture[i];
		//頂点座標の設定
		MakeVertex(g_UiVertex[i]);

		SetTexture(g_UiVertex[i],
			TEXTURE_UI_DIVIDE_X,
			TEXTURE_UI_DIVIDE_Y);

		//場所決定
		SetVertex(g_UiVertex[i],
			g_Ui_texture[i].Pos,
			g_Ui_texture[i].Size_x,
			g_Ui_texture[i].Size_y);

		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,		// デバイスのポインタ
			g_Ui_texture[i].Path,				// ファイルの名前
			&g_Ui_texture[i].pD3DTexture);					// 読み込むメモリのポインタ
	}
	g_GreenBarEpos = g_Ui_texture[ENUM_TEXTURE_UI_GAGEGREEN].Pos;
	Ui_Life_Initialize();
	Ui_Boss_Initialize();
}

void Ui_Finalize(void)
{
	Ui_Boss_Finalize();
	Ui_Life_Finalize();
	for (int i = 0; i < ENUM_TEXTURE_UI_MAX; i++)
	{
		if (g_Ui_texture[i].pD3DTexture != NULL)
		{	// テクスチャの開放
			g_Ui_texture[i].pD3DTexture->Release();
			g_Ui_texture[i].pD3DTexture = NULL;
		}
	}
}

void Ui_Update(void)
{
	float StageLimitTime = GetCurrentStageData().NormalEndflame;
	float StageTime= GetStagetime();

	if (StageTime<StageLimitTime)
	{
		//時間が０秒を考慮する
		if (StageTime>0) {
			g_GreenBarEpos.y
				= g_Ui_texture[ENUM_TEXTURE_UI_GAGEGREEN].Pos.y
				- (StageTime / StageLimitTime * g_Ui_texture[ENUM_TEXTURE_UI_GAGERED].Size_y);
		}
		else
		{
			g_GreenBarEpos.y
				= g_Ui_texture[ENUM_TEXTURE_UI_GAGEGREEN].Pos.y;
		}
	
	}
	Ui_Life_Update();
}

void Ui_Draw(void)
{

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int i = 0; i < ENUM_TEXTURE_UI_MAX; i++)
	{
		if (!g_Ui_texture[i].IsEnable)
			continue;

		if (i == ENUM_TEXTURE_UI_GAGEGREEN) 
		{
			//GreenGageのみ特殊な場所決定（可変）
			SetVertexVeticalSpread(g_UiVertex[i],
				g_Ui_texture[i].Pos,	//スタートポジション
				g_GreenBarEpos,//伸びポジション
				g_Ui_texture[i].Size_x);		
		}
		else 
		{
			//場所決定
			SetVertex(g_UiVertex[i],
				g_Ui_texture[i].Pos,
				g_Ui_texture[i].Size_x,
				g_Ui_texture[i].Size_y);
		}

		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);
		// テクスチャの設定
		pDevice->SetTexture(0, g_Ui_texture[i].pD3DTexture);
		// ポリゴンの描画

		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_PLAYER, g_UiVertex[i], sizeof(VERTEX_2D));
	}
	//ポートレート兼＋ライフ
	Ui_Life_Draw();
	Ui_Boss_Draw();
}

void Ui_SetTextureEnable(UI_TEXTURE index) {
	g_Ui_texture[index].IsEnable=true;
}

//*****************************************************************************
// ここから下はこの関数のみで使われる関数
//*****************************************************************************
