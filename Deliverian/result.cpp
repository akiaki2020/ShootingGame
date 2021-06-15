#include "input.h"
#include "Func_texture.h"
#include "sound.h"
#include "scene.h"
#include "result.h"
#include "Draw_text.h"
#include "fade.h"
#include "player.h"
#include "game.h"
#include "stage.h"//ヘッダーのenum取得のため

//*****************************************************************************
// CONST変数
//*****************************************************************************

//テクスチャーの設定
enum
{
	TEXTURE_BG,			
	TEXTURE_PAPER,		
	TEXTURE_HANKO,		
	TEXTURE_LIGHT,		
	TEXTURE_PUSHENTER,	
	TEXTURE_PUSHNEXT,	
	TEXTURE_MAX,
};





enum RESULT_STATE {
	PAPER_APEAEAR,
	SCORE_APEAEAR,
	HANKO_WAIT,
	HANKO_PUSH,
	HANKO_PUSED,
	RESULT_MAX
};

const static Texture_DATA c_InitTexture[] =
{
	{
		(char *)"TEXTURE/Result/Result_bk.tga"
		,NULL
		,NULL
		,D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f)
		,SCREEN_WIDTH
		,SCREEN_HEIGHT
		,true
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
		(char *)"TEXTURE/Result/result_paper.tga"
		,NULL
		,NULL
		,D3DXVECTOR3(SCREEN_WIDTH / 2, -TEXTURE_RESULT_PAPER_SIZE_Y, 0)
		,TEXTURE_RESULT_PAPER_SIZE_X
		,TEXTURE_RESULT_PAPER_SIZE_Y
		,true
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
		(char *)"TEXTURE/Result/hannko.tga"
		,NULL
		,NULL
		,D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f)
		,220
		,80
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
		(char *)"TEXTURE/Result/light.tga"
		,NULL
		,NULL
		,D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f)
		,SCREEN_WIDTH
		,SCREEN_HEIGHT
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
		(char *)"TEXTURE/Result/Push_ENTER.png"
		,NULL
		,NULL
		, D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4 * 3, 0.0f)
		,TEXTURE_RESULT_PUSH_SIZE_X
		,TEXTURE_RESULT_PUSH_SIZE_Y
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
		(char *)"TEXTURE/Result/Push_ENTER_NEXT_STAGE.png"
		,NULL
		,NULL
		, D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 8 * 7, 0.0f)
		,TEXTURE_RESULT_NEXT_SIZE_X
		,TEXTURE_RESULT_NEXT_SIZE_Y
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
// プロトタイプ宣言
//*****************************************************************************
void CheckAchieveHighScore();

//*****************************************************************************
// グローバル変数
//*****************************************************************************

static VERTEX_2D g_PolygonVertex[TEXTURE_MAX][4];
static Texture_DATA g_Texture[TEXTURE_MAX];

static D3DXVECTOR4 CharaColor; //表示文字色

RESULT_STATE g_ResultState;
//ステートが変わるごとに0にする
float g_ResultStateTime;

static int g_CurrentScore;
static int g_HighScore=0;
static STAGE g_CurrentStageData;
//フラグ
static bool g_AchieveHighScore;		//ハイスコア達成
static bool g_LastStageflg;	//ラストステージフラグ
static bool g_StateUseflg;//STATEが使うフラグ、各ステートが始まる前にfalseにする
static bool g_BottunFlg;


void Result_Initialize(void)
{
	g_ResultState = PAPER_APEAEAR;
	//文字の色決定：黒
	CharaColor = D3DXVECTOR4(255, 0, 0, 0);
	//ハイスコアの初期化
	g_CurrentScore = 0;
	//フラグ初期化
	g_AchieveHighScore = false;
	g_LastStageflg = false;
	g_StateUseflg = false;
	g_BottunFlg = true;
	g_ResultStateTime = 0;

	//ステージのデータを取得する
	g_CurrentStageData = GetStageData(GetGameStage());

	//ユーザーの現在のスコアがハイスコアかチェック
	CheckAchieveHighScore();

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int i = 0; i < TEXTURE_MAX; i++)
	{
	
		SetTextureDATA
		(
			pDevice,
			g_PolygonVertex[i],
			&g_Texture[i],
			&c_InitTexture[i]
		);

	}
	//BGMの生成
	PlaySound(SOUND_LABEL_BGM_result);
	PlaySound(SOUND_LABEL_SE_RESULT_PAPER);

	//ゲームのステージ数をチェックし最大なら次のステージに進まない
	int tempstage;
	tempstage = GetGameStage() + 1;
	if (tempstage == MAX_STAGE_TYPE) {
		g_LastStageflg = true;
	}

}

void Result_Finalize(void)
{
	StopSound(SOUND_LABEL_BGM_result);
	g_LastStageflg = false;
	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		UnLoadTextureDATA(&g_Texture[i]);
		/*
		if (g_Result_texture[i].pD3DTexture != NULL)
		{	// テクスチャの開放
			g_Result_texture[i].pD3DTexture->Release();
			g_Result_texture[i].pD3DTexture = NULL;
		}
		*/
	}
}

void Result_Update(void)
{
	switch (g_ResultState)
	{
	case PAPER_APEAEAR:
		g_Texture[TEXTURE_PAPER].Pos.y += 3.0f;
		if (g_Texture[TEXTURE_PAPER].Pos.y>SCREEN_HEIGHT/2)
		{
			g_StateUseflg = false;
			g_ResultStateTime = 0;
			g_ResultState = HANKO_WAIT;
		}
		break;
	case HANKO_WAIT:
		if (!g_StateUseflg)
		{
			PlaySound(SOUND_LABEL_SE_RESULT_HANKObf);
			g_StateUseflg = true;
		}
		g_ResultStateTime += 1.0f / 120.0f;
		if (g_ResultStateTime>1.0f) {
			g_ResultStateTime = 0;
			g_StateUseflg = false;
			g_ResultState = HANKO_PUSH;
		}
		break;
	case HANKO_PUSH:
		if (!g_StateUseflg)
		{
			g_Texture[TEXTURE_PUSHENTER].IsEnable = true;
			//ハンコの位置を再設定する
			g_Texture[TEXTURE_HANKO].Pos = g_Texture[TEXTURE_PAPER].Pos;
			g_Texture[TEXTURE_HANKO].Pos.x += TEXTURE_RESULT_PAPER_SIZE_X / 24*7;
			g_Texture[TEXTURE_HANKO].Pos.y += TEXTURE_RESULT_PAPER_SIZE_Y / 16*1.3f;
			g_StateUseflg = true;
		}

		if (GetKeyboardTrigger(DIK_RETURN)) {
			PlaySound(SOUND_LABEL_SE_RESULT_HANKOafter);	
			g_Texture[TEXTURE_HANKO].IsEnable = true;
			g_Texture[TEXTURE_PUSHENTER].IsEnable = false;
			g_StateUseflg = false;
			g_ResultState = HANKO_PUSED;
		}
		break;
	case HANKO_PUSED:
		if (!g_StateUseflg)
		{
			g_Texture[TEXTURE_PUSHNEXT].IsEnable = true;
			g_StateUseflg = true;
		}
		//ラストステージじゃないなら
		if (!g_LastStageflg)
		{
			//次のステージへ行く
			if (GetKeyboardTrigger(DIK_RETURN)&& g_BottunFlg) {
				PlaySound(SOUND_LABEL_SE_titlebutton);

				SetGameStage(GetGameStage() + 1);
				Fade(SCENE_INDEX_GAME);
				g_BottunFlg = false;
			}
			//タイトルに戻る
			if (GetKeyboardTrigger(DIK_BACK) && g_BottunFlg) {
				PlaySound(SOUND_LABEL_SE_titlebutton);
				SetGameStage(0);
				Fade(SCENE_INDEX_TITLE);
				g_BottunFlg = false;
			}
		}
		else 
		{//タイトルに戻る
			if (GetKeyboardTrigger(DIK_RETURN) && g_BottunFlg)
			{
				PlaySound(SOUND_LABEL_SE_titlebutton);
				SetGameStage(0);
				Fade(SCENE_INDEX_TITLE);
				g_BottunFlg = false;
			}
		}	
		break;
	case RESULT_MAX:
		break;
	default:
		break;
	}
}

void Result_Draw(void)
{

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		if (!g_Texture[i].IsEnable)
			continue;
		//場所決定
		
		
		DrawTextureDATA(
			pDevice,
			&g_Texture[i]
		);
	}

	//文字の描画
	TCHAR str[256];
	RECT rect = 
		{ g_Texture[TEXTURE_PAPER].Pos.x - TEXTURE_RESULT_PAPER_SIZE_X/24*8, 
		g_Texture[TEXTURE_PAPER].Pos.y+ TEXTURE_RESULT_PAPER_SIZE_Y/32*3,
		SCREEN_WIDTH, 
		SCREEN_HEIGHT };
	//Scoreの描画
	wsprintf(str, _T("%d\n"), g_CurrentScore);
	Drawtextfnc(str, rect, CharaColor);
	//ハイスコアおめでとうの描写
	if (g_AchieveHighScore) {
		////HighScoreの描画
	}	
	//文字の格納終わり
}

void SetCurrentGameScore(int currentScore) {
	g_CurrentScore = currentScore;
}

//*****************************************************************************
// ここから下はこの関数のみで使われる関数
//*****************************************************************************
//ハイスコアの格納とハイスコアか
void CheckAchieveHighScore() {
	PLAYER_DATA *player = GetPlayer();
	g_CurrentScore = player->Score;


	if (g_CurrentScore> g_CurrentStageData.int1) {

		g_CurrentStageData.int1 = g_CurrentScore;
		SetStageHighScore(GetGameStage(), g_CurrentScore);

		g_AchieveHighScore = true;
	}
	return;
}