//=============================================================================
//
// bossの処理 [BOSS.h]
// Author : 
//
//=============================================================================
#include "enemy.h"

#pragma once


//}BOSS;

//ボスのタイプ
enum BOSS_TYPE {
	B_FIGHTER,
	B_LASER,
	B_FINAL,
	B_MAX_ENEMYTYPE
};

void InitBoss();
void UninitBoss();
void UpdateBoss();
void DrawBoss();
void SetBoss(int BossType);
//同じ関数名で違う引数を持つ→オーバーロードという。 ADD
//どちらのSetEnemyも使用可能
void SetBoss(D3DXVECTOR3 pos, D3DXVECTOR3 dir, int BossType);

bool GetIsEnableBoss();
ENEMY* GetBoss();
