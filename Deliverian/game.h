#pragma once

void Game_Initialize();
void Game_Finalize();
void Game_Update();
void Game_Draw();

void DrawTime();


enum PHASE_GAME
{
	PHASE_GAME_INIT,
	PHASE_GAME_NORMAL,//
	PHASE_GAME_BOSS, //ボスフェーズの追加
	PHASE_GAME_STAGE_CLEAR,
	PHASE_GAME_END,	//ゲームオーバー

	PHASE_INDEX_MAX
};

int GetGamePhase();
void SetGamePhase(PHASE_GAME);

void SetGameStage(int);
int GetGameStage(void);

void UnSetBGMStage();
void SetBGMStage(int soundIndex);
