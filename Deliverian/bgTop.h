//=============================================================================
//
// �w�i���� [bgTop.h]
// Author : 
//
//=============================================================================

#include "stage.h"
#ifndef _BGTOP_H_
#define _BGTOP_H_
// �}�N����`
#define TEXTURE_BG_SIZE_X	(512)	// �e�N�X�`���T�C�Y
#define TEXTURE_BG_SIZE_Y	(512)	// 
#define TEXTURE_BG_SKYSEA 3			//SKY�p�̑��e�N�X�`��

//�A�j���[�V����
#define TEXTURE_BG_DIVIDE_X	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_BG_DIVIDE_Y	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define TEXTURE_BG_SCROLLPAGECOUNT 2	// �A�j���[�V�����̐؂�ւ��J�E���g


#define ANIM_BG_NUM			(3)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION_BG				(4)	// �A�j���[�V�����̐؂�ւ��J�E���g

//***************************BG**************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitBgTop();
void UninitBgTop();
void UpdateBgTop();
void DrawBgTop();
//STAGE.CPP�̂ݎg�p
void Bg_SetTextureEnable(STAGE_TYPE index);

#endif

