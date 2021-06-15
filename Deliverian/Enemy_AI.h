#pragma once
#include "Main.h"
#include "Enemy.h"

enum ENEMY_AISTATE {
	//警戒モード
	GO_DIRECT,		//移動向きに移動
	WAIT_DIRECT,	//移動向きを維持し待機
	//攻撃モード
	WAIT_ROTAION,	//その場を維持し、向きを変更
	CHARGE_BACK,	//向きを維持し,バックする
	CHARGE,			//移動方向の向きに突進
	ROTATION_SHOT,	//向きを変更しながらショット
	SHOT_ONE,		//ショットを打つ
	DAKOU_DIRECT,			//向きを維持しながら蛇行
	GO_Straight,			//まっすぐ突っ込みステージ外に出る

	AISTATE_MAX


};



//ENEMYのアップデートのみ使用
void Enemy_AI_Update(ENEMY* enemy);