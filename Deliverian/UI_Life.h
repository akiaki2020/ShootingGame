//=============================================================================
//
// ライフ画面表示処理 [UI_LIFE.h]
// Author : 
//
//=============================================================================
#pragma once
// マクロ定義
#define TEXTURE_UI_DIVIDE_X	(1)	// アニメパターンのテクスチャ内分割数（X)
#define TEXTURE_UI_DIVIDE_Y	(1)	// アニメパターンのテクスチャ内分割数（Y)
#define TEXTURE_UI_life_Signal_DIVIDE_X	(2)	// アニメパターンのテクスチャ内分割数（X)
#define TEXTURE_UI_life_Signal_DIVIDE_Y	(2)	// アニメパターンのテクスチャ内分割数（Y)


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