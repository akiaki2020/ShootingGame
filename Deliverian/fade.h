//=============================================================================
//
// 暗転 [fade.h]
// Author : 
//
//=============================================================================
#include "scene.h"
#pragma once
// マクロ定義
#define TEXTURE_FADE_SIZE_X	(512)	// テクスチャサイズ
#define TEXTURE_FADE_SIZE_Y	(512)	// 
//アニメーション
#define TEXTURE_FADE_DIVIDE_X	(1)	// アニメパターンのテクスチャ内分割数（X)
#define TEXTURE_FADE_DIVIDE_Y	(1)	// アニメパターンのテクスチャ内分割数（Y)
#define ANIM_BG_NUM			(1)	// アニメーションパターン数
//***************************BG**************************************************
// プロトタイプ宣言
//*****************************************************************************

void InitFade();
void UninitFade();
void UpdateFade();
void DrawFade();

void Fade(SCENE_INDEX nextScene);
