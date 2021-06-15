
#include "main.h"
#include "game.h"
#include "input.h"
#include "UI_Draw.h"
#include "fade.h"
#include "player.h"
#include "bulletsight.h"
#include "enemy.h"
#include "stage.h"
#include "boss.h" //Enemy�̃R�s�[�Ȃ̂Œ����ɔz�u
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
// �O���[�o���ϐ�:
//*****************************************************************************
//���y�p
static int g_BGM;

//�ŏ��̃X�e�[�W�̏ꍇ�t���O
static bool g_FirstInit_flg=true;

static PHASE_GAME g_Phase;
static STAGE_TYPE g_Stage;


void Game_Initialize()
{
	//BGM������
	g_BGM = -1;

	//����X�e�[�W������SKY
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
	//�T�E���h�̏I������
	UnSetBGMStage();
	StopSound();//����S�Ď~�߂�

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


		//�S�ẴA�b�v�f�[�g�������I������瓖���蔻�菈�����s��
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
		////�S�ẴA�b�v�f�[�g�������I������瓖���蔻�菈�����s��
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
		//���U���g��ʂɍs��
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

		//�^�C�g���ɖ߂�
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
//�O���ł͎g��Ȃ�
//����BGM�����߂�̂�
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


//BGM�֘A��₱�����c��łǂ��ɂ�����
void UnSetBGMStage()
{
	//BGM���Ȃ�����ĂȂ��Ȃ�s��Ȃ�
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

