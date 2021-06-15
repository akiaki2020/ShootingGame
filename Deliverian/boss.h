//=============================================================================
//
// boss�̏��� [BOSS.h]
// Author : 
//
//=============================================================================
#include "enemy.h"

#pragma once


//}BOSS;

//�{�X�̃^�C�v
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
//�����֐����ňႤ�����������I�[�o�[���[�h�Ƃ����B ADD
//�ǂ����SetEnemy���g�p�\
void SetBoss(D3DXVECTOR3 pos, D3DXVECTOR3 dir, int BossType);

bool GetIsEnableBoss();
ENEMY* GetBoss();
