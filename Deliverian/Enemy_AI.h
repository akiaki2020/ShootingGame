#pragma once
#include "Main.h"
#include "Enemy.h"

enum ENEMY_AISTATE {
	//�x�����[�h
	GO_DIRECT,		//�ړ������Ɉړ�
	WAIT_DIRECT,	//�ړ��������ێ����ҋ@
	//�U�����[�h
	WAIT_ROTAION,	//���̏���ێ����A������ύX
	CHARGE_BACK,	//�������ێ���,�o�b�N����
	CHARGE,			//�ړ������̌����ɓːi
	ROTATION_SHOT,	//������ύX���Ȃ���V���b�g
	SHOT_ONE,		//�V���b�g��ł�
	DAKOU_DIRECT,			//�������ێ����Ȃ���֍s
	GO_Straight,			//�܂������˂����݃X�e�[�W�O�ɏo��

	AISTATE_MAX


};



//ENEMY�̃A�b�v�f�[�g�̂ݎg�p
void Enemy_AI_Update(ENEMY* enemy);