#pragma once
#include "Main.h"
#include "Boss.h"

//ボスの挙動
enum BOSS_STATE
{
	BOSS_STATE_APPEAR1,
	BOSS_STATE_WATE1,
	BOSS_STATE_FIRE1,
	BOSS_STATE_FIRE2,
	BOSS_STATE_FIRE3,
	BOSS_STATE_FIRE4,
	BOSS_STATE_FIRE5,
	BOSS_STATE_LASER1,
	BOSS_STATE_LASER2,
	BOSS_GO_LEFT,
	BOSS_GO_CENTER,
	BOSS_GO_RIGHT,
	BOSS_LEFTSIDE_ATTACK_DOWN,
	BOSS_LEFTSIDE_ATTACK_UP,
	BOSS_RIGHTSIDE_ATTACK_DOWN,
	BOSS_RIGHTSIDE_ATTACK_UP,
};



//ENEMYのアップデートのみ使用
void Boss_AI_Update(ENEMY* boss);