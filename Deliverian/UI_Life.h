//=============================================================================
//
// ���C�t��ʕ\������ [UI_LIFE.h]
// Author : 
//
//=============================================================================
#pragma once
// �}�N����`
#define TEXTURE_UI_DIVIDE_X	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_UI_DIVIDE_Y	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define TEXTURE_UI_life_Signal_DIVIDE_X	(2)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_UI_life_Signal_DIVIDE_Y	(2)	// �A�j���p�^�[���̃e�N�X�`�����������iY)


enum UI_LIFE_TEXTURE
{
	ENUM_TEXTURE_UI_LIFE_PORTRAIT,
	ENUM_TEXTURE_UI_LIFE_Filter,
	ENUM_TEXTURE_UI_LIFE_Signal,
	ENUM_TEXTURE_UI_LIFE_MAX,
};

void Ui_Life_Initialize(void);
void Ui_Life_Finalize(void);
void Ui_Life_Update(void);
void Ui_Life_Draw(void);

void Ui_Life_Set(int Hp);
void Ui_Score_Set(int Score);