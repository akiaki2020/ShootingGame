#pragma once
// �}�N����`
#define TEXTURE_UI_DIVIDE_X	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_UI_DIVIDE_Y	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define SIDEGAGE_POS_X SCREEN_GAME_WIDTH+SCREEN_WIDTH / 36
#define SIDEGAGE_POS_Y SCREEN_HEIGHT / 8*3
#define SIDEGAGE_SIZE_X (60)
#define SIDEGAGE_SIZE_Y (200)
#define SIDEGAGE_MOZISIZE_X (80)
#define SIDEGAGE_MOZISIZE_Y (20)

enum UI_TEXTURE
{	
	ENUM_TEXTURE_UI_GAGERED,
	ENUM_TEXTURE_UI_GAGEGREEN,
	ENUM_TEXTURE_UI_GAGEBASE,
	ENUM_TEXTURE_UI_GAMEOVER,
	ENUM_TEXTURE_UI_RETURN,
	ENUM_TEXTURE_UI_CLEAR,
	ENUM_TEXTURE_UI_GOTORESULT,
	ENUM_TEXTURE_UI_START,
	ENUM_TEXTURE_UI_GOAL,
	ENUM_TEXTURE_UI_MAX,
};

void Ui_Initialize(void);
void Ui_Finalize(void);
void Ui_Update(void);
void Ui_Draw(void);
void Ui_SetTextureEnable(UI_TEXTURE index);