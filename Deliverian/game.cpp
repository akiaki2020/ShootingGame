
#include "main.h"
#include "game.h"
#include "input.h"
#include "UI_Draw.h"
#include "fade.h"
#include "player.h"
#include "bulletsight.h"
#include "enemy.h"
#include "stage.h"
#include "boss.h" //Enemyのコピーなので直下に配置
#include "bullet.h"
#include "Blade.h"


#include "enemy_laser.h"
#include "bgTop.h"
#include "bgBlack.h"
#include "explosion.h"
#include "collision.h"

#include "sound.h"

void initGameBGM();
//*****************************************************************************
// グローバル変数:
//*****************************************************************************
//音楽用
static int g_BGM;

//最初のステージの場合フラグ
static bool g_FirstInit_flg=true;

static PHASE_GAME g_Phase;
static STAGE_TYPE g_Stage;


void Game_Initialize()
{
	//BGM初期化
	g_BGM = -1;

	//初回ステージ生成はSKY
	if (g_FirstInit_flg) {
		SetGameStage(SKY);		
		g_FirstInit_flg = false;
	}
	Ui_Initialize();
	InitPlayer();
	InitBulletSight();
	InitEnemy();
	InitBoss();
	InitBlade();
	InitBullet();
	InitEnemyLaser();
	InitBgTop();
	InitBgBlack();

	InitStage();
	SetStage(g_Stage);
	InitExplosion();
	initGameBGM();
	g_Phase = PHASE_GAME_INIT;
	
}


void Game_Finalize()
{
	Ui_Finalize();
	UninitBoss();
	UninitBgTop();
	UninitBgBlack();
	UninitBulletSight();
	UninitPlayer();
	UninitEnemy();
	UninitBullet();
	UninitBlade();
	UninitExplosion();
	UninitEnemyLaser();
	//UninitEnemyEmitter();//ADD
	//サウンドの終了処理
	UnSetBGMStage();
	StopSound();//音を全て止める

}


void Game_Update()
{
	Ui_Update();
	switch (g_Phase)
	{
	case PHASE_GAME_INIT:
		g_Phase = PHASE_GAME_NORMAL;
		break;
	case PHASE_GAME_NORMAL:

		UpdateBgTop();
		UpdateStage();
		UpdatePlayer();
		UpdateEnemy();
		UpdateBullet();
		UpdateBlade();
		UpdateExplosion();


		//全てのアップデート処理が終わったら当たり判定処理を行う
		HitCheck();
		break;

	case PHASE_GAME_BOSS:
		UpdateBgTop();
		UpdateStage();
		UpdatePlayer();
		UpdateEnemy();
		UpdateBoss();
		UpdateBullet();
		UpdateBlade();
		UpdateEnemyLaser();
		UpdateExplosion();
		////全てのアップデート処理が終わったら当たり判定処理を行う
		HitCheck();
		break;

	case PHASE_GAME_STAGE_CLEAR:
		UpdateBgTop();
		UpdateStage();
		UpdatePlayer();
		UpdateBullet();
		UpdateBlade();
		UpdateEnemyLaser();
		UpdateExplosion();
		//リザルト画面に行く
		if (GetKeyboardTrigger(DIK_RETURN)) {
			PlaySound(SOUND_LABEL_SE_titlebutton);
			Fade(SCENE_INDEX_RESULT);
		}		
		break;
	case PHASE_GAME_END:
		UpdateBgTop();
		UpdateStage();
		UpdateEnemy();
		UpdateBullet();
		UpdateBlade();
		UpdateExplosion();

		//タイトルに戻る
		if (GetKeyboardTrigger(DIK_RETURN)) {
			PlaySound(SOUND_LABEL_SE_titlebutton);
			SetGameStage(SKY);
			Fade(SCENE_INDEX_TITLE);
		}
		break;
	}
}


void Game_Draw()
{
	DrawBgTop();
	DrawPlayer();
	DrawEnemy();
	DrawBoss();
	DrawBullet();
	DrawBlade();
	DrawEnemyLaser();
	DrawExplosion();

	DrawBgBlack();

	DrawBulletSight();
	Ui_Draw();
}




int GetGamePhase()
{
	return g_Phase;
}

void SetGamePhase(PHASE_GAME phase)
{
	g_Phase= phase;
	switch (g_Phase)
	{
	case PHASE_GAME_INIT:
		break;
	case PHASE_GAME_NORMAL:
		break;
	case PHASE_GAME_BOSS:
		break;
	case PHASE_GAME_STAGE_CLEAR:
		Ui_SetTextureEnable(ENUM_TEXTURE_UI_CLEAR);
		Ui_SetTextureEnable(ENUM_TEXTURE_UI_GOTORESULT);
		break;
	case PHASE_GAME_END:
		Ui_SetTextureEnable(ENUM_TEXTURE_UI_GAMEOVER);
		Ui_SetTextureEnable(ENUM_TEXTURE_UI_RETURN);
		UnSetBGMStage();
		SetBGMStage(SOUND_LABEL_BGM_PLAYERDIE);
		break;
	case PHASE_INDEX_MAX:
		break;
	default:
		break;
	}
	

}


void SetGameStage(int StageIndex)
{
	switch (StageIndex)
	{
	case SKY:
		g_Stage = SKY;
		break;
	case SPACE:
		g_Stage = SPACE;
		break;
	case ASTEROID:
		g_Stage = ASTEROID;
		break;
	default:
		break;
	}
	

}

int GetGameStage()
{
	return g_Stage;

}
//外部では使わない
//現状BGMを決めるのみ
void initGameBGM()
{
	switch (g_Stage)
	{
	case SKY:
		SetBGMStage(SOUND_LABEL_BGM_sample000);
		break;
	case SPACE:
		SetBGMStage(SOUND_LABEL_BGM_sample001);
		break;
	case ASTEROID:
		SetBGMStage(SOUND_LABEL_BGM_sample002);
		break;
	default:
		break;
	}
}


//BGM関連ややこしい…後でどうにかする
void UnSetBGMStage()
{
	//BGMがながされてないなら行わない
	if (g_BGM == -1)return;
	StopSound(g_BGM);
	g_BGM = -1;
}

void SetBGMStage(int soundIndex) 
{	
	if (g_BGM != -1) return;
	PlaySound(soundIndex);
	g_BGM = soundIndex;
}

