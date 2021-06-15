
#include "main.h"
#include "ReadCsv.h"
#include "Draw_text.h"
#include "Enemy.h"
#include "EnemyEmitter.h"
#include "Boss.h"
#include "game.h"
#include "stage.h"
#include "bgtop.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define STAGE_FOLDER "stage\\"
#define STAGE_1_TEXTFILENAME "SKY"
#define STAGE_2_TEXTFILENAME "SPACE"
#define STAGE_3_TEXTFILENAME "ASTEROID"
#define STAGE_DATASIZE 2000

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void ImportStageDataTable(FILE *fp, int stage_type);
bool EndCheckBoss();



//*****************************************************************************
// グローバル変数
//*****************************************************************************
static LPD3DXFONT	g_pD3DXFont = NULL;			// フォントへのポインタ

static LPDIRECT3DDEVICE9		g_pD3DDevice = NULL;		// Deviceオブジェクト(描画に必要)

static STAGE g_stage;//現在のステージ
static float g_StageFrame;//経過フレーム数
static int g_Firstframe;//最初の計測時間

static int g_Phase;

static boolean g_Bossflg;//BOSS出現フラグ
static int g_EmitCount;//出現カウンタ
static int g_LimitEmitCount;//出現リミット

//各ステージの要素を入れている
STAGE tblStage[MAX_STAGE_TYPE] = {
	//SKY
	{ 
		SKY,		//ステージのタイプ
		0.0f,		//経過フレーム			
		60,			//敵の出現数
		30.0f,	//終了フレーム
	//	5.0f,	//終了フレーム　テスト用
		B_FIGHTER,		//ボス名
		//0,		//ボス名
		"first",	//ステージ名
		0,		//ハイスコア
		0,		//
		0,		//
		0,		//
		0.0f,		//1変数
		0.0f,		//2変数
		0.0f,		//2変数
		0.0f,		//2変数
	},
	//SPACE
	{
		SPACE,		//ステージのタイプ
		0.0f,		//経過フレーム
		200,			//敵の出現数
		30.0f,		//終了フレーム
		//5.0f,	//終了フレーム　テスト用
		B_LASER,		//ボス名
		//0,		//ボス名
		"SPACE",	//ステージ名
		0,		//ハイスコア
		0,		//
		0,		//
		0,		//
		0.0f,		//1変数
		0.0f,		//2変数
		0.0f,		//2変数
		0.0f,		//2変数
	},
	//ASTEROID
	{
		ASTEROID,		//ステージのタイプ
		0.0f,		//経過フレーム
		300,			//敵の出現数
		40.0f,		//終了フレーム
		//5.0f,	//終了フレーム　テスト用
		B_FINAL,		//ボス名
		//0,		//ボス名
		"ASTEROID",	//ステージ名
		0,		//ハイスコア
		0,		//
		0,		//
		0,		//
		0.0f,		//1変数
		0.0f,		//2変数
		0.0f,		//2変数
		0.0f,		//2変数
	},
};

//敵の出現開始時間、出現場所、移動方向の設定配列
ENEMYEMIT_T tblEnemy[STAGE_MAX_ENEMYGROUP]= {};

void InitStage()
{
	//初期化処理
	g_EmitCount = 0;
	g_StageFrame = 0;
	g_Firstframe = time(NULL);
	g_Bossflg = false;
	tblEnemy[STAGE_MAX_ENEMYGROUP] = {};
	//テーブルの要素数の計算
	//構造体配列のサイズ/構造体のサイズで計算
	//g_TableSize = sizeof(tblEnemy) / sizeof(ENEMYEMIT_T);
	g_pD3DDevice = GetDevice();

	D3DXCreateFont(g_pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Terminal"), &g_pD3DXFont);
}

//game.cppが呼び出す以外使わない
void SetStage(STAGE_TYPE stagetype)
{
	FILE *fp=NULL;

	//初期化処理
	g_EmitCount = 0;
	g_LimitEmitCount=0;
	g_StageFrame = 0;
	//テーブル内容を代入
	g_stage = tblStage[stagetype];

	//ステージデータをCSVから読み込む
	char fileName[2000];
	char fileStageEnemyData[STAGE_DATASIZE];
	
	fileName[0]='\0';
	fileStageEnemyData[0] = '\0';
	
	//
	strcpy(fileName, CSV_FOLDER);
	strcat(fileName, STAGE_FOLDER);

	switch (stagetype)
	{
	case SKY:		
		strcat(fileName, STAGE_1_TEXTFILENAME);
		break;
	case SPACE:
		strcat(fileName, STAGE_2_TEXTFILENAME);
		break;
	case ASTEROID:
		strcat(fileName, STAGE_3_TEXTFILENAME);
		break;
	case MAX_STAGE_TYPE:
		break;
	default:
		break;
	}
	fp= ReadCsv(fileName);
	ImportStageDataTable(fp, stagetype);
	fclose(fp); // ファイルを閉じる
	//背景の設定
	Bg_SetTextureEnable(stagetype);
	//テーブルの要素数の計算
	//構造体配列のサイズ/構造体のサイズで計算
	//g_TableSize = g_stage.EnemyPop;
	g_StageFrame = 0;


}

void UpdateStage() {
	g_Phase = GetGamePhase();
	g_StageFrame +=1.0f/60;

	//雑魚フェーズ
	if (g_Phase== PHASE_GAME_NORMAL) {

		//g_EmitCountが設定配列の要素数を超えたら実行しないようにする
		if (g_EmitCount < g_LimitEmitCount) {
			//経過時間と出現フレームを比較し、経過時間が多ければ敵発生！
			if (g_StageFrame > tblEnemy[g_EmitCount].flame) {
				//敵を発生させる
				EnemyEmitter(
					tblEnemy[g_EmitCount].pos,
					tblEnemy[g_EmitCount].dir,
					tblEnemy[g_EmitCount].EnemyType,
					tblEnemy[g_EmitCount].EmitType
				);
				g_EmitCount++;
			}
		}
		//STAGE時間終了時
		if (g_StageFrame >= tblStage[g_stage.stage_type].NormalEndflame)
		{
			SetGamePhase(PHASE_GAME_BOSS);
			g_Bossflg = true;
		}
	}

	if (g_Phase == PHASE_GAME_BOSS) {

		//最初にボスを出現させる
		if (g_Bossflg) {
			SetBoss(tblStage[g_stage.stage_type].boss_type);
			g_Bossflg = false;
		}
		//ゲームクリア条件が揃っていたらゲームクリアフェーズへ移行する
		if (EndCheckBoss()) {
			SetGamePhase(PHASE_GAME_STAGE_CLEAR);
		}

	}


}

bool EndCheckBoss()
{
	ENEMY* pBoss = GetBoss();
	if (pBoss->Hp <= 0)
	{
		return true;
	}
	return false;
}


void ImportStageDataTable(FILE *fp, int stagetype) {
	int ret=0;
	float flame=0;
	float pos[3];
	float dir[3];
	int Enemy[2];
	int rowCount=0;
	//データ読み込み
	while 
		(
			(ret = 
				fscanf(fp, "%f,%f,%f,%f,%f,%f,%f,%d,%d,", &flame, &pos[0], &pos[1], &pos[2], &dir[0], &dir[1], &dir[2], &Enemy[0], &Enemy[1])
			) 
			!= EOF
		) 
	{
		//敵の出現方向によって位置を調整する


		//水平方向の調整
		if (dir[0] > 0) {
			pos[0] = -10.0f;
		}
		else if(dir[0] < 0) {
			pos[0] = SCREEN_GAME_WIDTH +10.0f;
		}
		//垂直方向の調整
		if (dir[1] > 0) {
			pos[1] = -10.0f;
		}
		else if(dir[1] < 0) {
			pos[1] = SCREEN_HEIGHT + 10.0f;
		}

		tblEnemy[rowCount] = { flame,D3DXVECTOR3(pos[0],pos[1],pos[2]), D3DXVECTOR3(dir[0],dir[1],dir[2]),Enemy[0],Enemy[1] };
			rowCount++;
			g_LimitEmitCount++;
	}
}

void SetStageHighScore(int stage_type,int HighScore) {
	tblStage[stage_type].int1 = HighScore;
}

STAGE GetStageData(int stage_type) {
	return tblStage[stage_type];
}

float GetStagetime() {
	return g_StageFrame;
}

STAGE GetCurrentStageData() {
	return g_stage;
}