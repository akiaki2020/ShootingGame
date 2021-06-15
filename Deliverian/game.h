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
	PHASE_GAME_BOSS, //�{�X�t�F�[�Y�̒ǉ�
	PHASE_GAME_STAGE_CLEAR,
	PHASE_GAME_END,	//�Q�[���I�[�o�[

	PHASE_INDEX_MAX
};

int GetGamePhase();
void SetGamePhase(PHASE_GAME);

void SetGameStage(int);
int GetGameStage(void);

void UnSetBGMStage();
void SetBGMStage(int soundIndex);
