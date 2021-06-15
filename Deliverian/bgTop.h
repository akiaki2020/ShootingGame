//=============================================================================
//
// 背景処理 [bgTop.h]
// Author : 
//
//=============================================================================

#include "stage.h"
#ifndef _BGTOP_H_
#define _BGTOP_H_
// マクロ定義
#define TEXTURE_BG_SIZE_X	(512)	// テクスチャサイズ
#define TEXTURE_BG_SIZE_Y	(512)	// 
#define TEXTURE_BG_SKYSEA 3			//SKY用の第二テクスチャ

//アニメーション
#define TEXTURE_BG_DIVIDE_X	(1)	// アニメパターンのテクスチャ内分割数（X)
#define TEXTURE_BG_DIVIDE_Y	(1)	// アニメパターンのテクスチャ内分割数（Y)
#define TEXTURE_BG_SCROLLPAGECOUNT 2	// アニメーションの切り替わるカウント


#define ANIM_BG_NUM			(3)	// アニメーションパターン数
#define TIME_ANIMATION_BG				(4)	// アニメーションの切り替わるカウント

//***************************BG**************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitBgTop();
void UninitBgTop();
void UpdateBgTop();
void DrawBgTop();
//STAGE.CPPのみ使用
void Bg_SetTextureEnable(STAGE_TYPE index);

#endif

