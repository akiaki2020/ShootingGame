//=============================================================================
//
// �Ó] [fade.h]
// Author : 
//
//=============================================================================
#include "scene.h"
#pragma once
// �}�N����`
#define TEXTURE_FADE_SIZE_X	(512)	// �e�N�X�`���T�C�Y
#define TEXTURE_FADE_SIZE_Y	(512)	// 
//�A�j���[�V����
#define TEXTURE_FADE_DIVIDE_X	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_FADE_DIVIDE_Y	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_BG_NUM			(1)	// �A�j���[�V�����p�^�[����
//***************************BG**************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

void InitFade();
void UninitFade();
void UpdateFade();
void DrawFade();

void Fade(SCENE_INDEX nextScene);
