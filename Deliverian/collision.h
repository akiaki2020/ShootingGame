//=====================================================================================
//
// �����蔻�菈�� [collision.h]
// Author : �H�{
//�ڐG����ƁA�ڐG��ǂ̊֐����ĂԂ��L�q
//game.cpp�̂݃C���N���[�h�����
//=============================================================================

#pragma once
#include "main.h"

typedef struct
{
	float cx, cy;	//���S���W
	float r;		//���a

}CIRCLE;


typedef struct
{
	float x, y;		//�n�_���W
	float ex, ey;	//�x�N�g�������i�I�_�j
	float r;		//���a

}CAPSULE;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

void HitCheck(void);
