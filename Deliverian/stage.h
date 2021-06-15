//=============================================================================
//
// 処理 [stage.h]
// Author : 
//
//=============================================================================
#pragma once

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define STAGE_NAME					32	//ステージのマックス名
#define STAGE_MAX_ENEMYGROUP		999	//ステージの最大敵グループの出現数

enum STAGE_TYPE
{
	SKY,
	SPACE,
	ASTEROID,
	MAX_STAGE_TYPE
};

typedef struct
{
	enum STAGE_TYPE stage_type;		//ステージのタイプ
	float flame;				//経過フレーム
	int	  EnemyPop;				//敵の出現数
	float NormalEndflame;		//終了フレーム
	enum BOSS_TYPE boss_type;
	char	StageName[STAGE_NAME];

	int	  int1;				//ハイスコア	
	int	  int2;
	int	  int3;
	int	  int4;

	float flt1;					//1変数
	float flt2;					//2変数
	float flt3;					//3変数
	float flt4;					//4変数
}STAGE;


//***************************BG**************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitStage();
void SetStage(STAGE_TYPE stagetype);

void UpdateStage();

void SetStageHighScore(int stage_type, int HighScore);

STAGE GetStageData(int stage_type);

//以下はUi.cppのみ使用すること
float GetStagetime();
STAGE GetCurrentStageData();
