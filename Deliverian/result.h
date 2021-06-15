#pragma once
// マクロ定義

#define TEXTURE_RESULT_MAX	(5)	// テクスチャーの数


//アニメーション
#define TEXTURE_RESULT_DIVIDE_X	(1)	// アニメパターンのテクスチャ内分割数（X)
#define TEXTURE_RESULT_DIVIDE_Y	(1)	// アニメパターンのテクスチャ内分割数（Y)
#define ANIM_RESULT_NUM			(3)	// アニメーションパターン数

#define TEXTURE_RESULT_PAPER_SIZE_X	(600)	// 
#define TEXTURE_RESULT_PAPER_SIZE_Y	(400)	// 

#define TEXTURE_RESULT_PUSH_SIZE_X	(200)// 
#define TEXTURE_RESULT_PUSH_SIZE_Y	(50)	// 
#define TEXTURE_RESULT_NEXT_SIZE_X	(400)// 
#define TEXTURE_RESULT_NEXT_SIZE_Y	(50)	// 
#define TEXTURE_RESULT_POS_Y	(30)	// アニメパターンのテクスチャ内分割数（Y)
#define TEXTURE_RESULT_POS_X	(50)	// アニメパターンのテクスチャ内分割数（Y)


#define TEXTURE_RESULT_PUSH_ANIME_TIME	(0.05)	// アニメパターンのテクスチャの変化時間
#define TEXTURE_RESULT_PUSH_ANIME_LIMIT	9	// アニメパターンのテクスチャの変化上限


void Result_Initialize(void);
void Result_Finalize(void);
void Result_Update(void);
void Result_Draw(void);
