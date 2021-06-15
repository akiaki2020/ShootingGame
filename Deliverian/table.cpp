//
//#include "main.h"
//#include "table.h"
//
//
////アニメーションパターンテーブル
//static nn::math::VEC2 ANIM_PATTERN[4][4][3] = {
//	{//水色
//		{//下向き
//			nn::math::VEC2(0.0f, 0.0f),
//			nn::math::VEC2(0.125f, 0.0f),
//			nn::math::VEC2(0.25f, 0.0f),
//		},
//		{//左向き
//			nn::math::VEC2(0.0f, 0.125f),
//			nn::math::VEC2(0.125f, 0.125f),
//			nn::math::VEC2(0.25f, 0.125f),
//		},
//		{//右向き
//			nn::math::VEC2(0.0f, 0.25f),
//			nn::math::VEC2(0.125f, 0.25f),
//			nn::math::VEC2(0.25f, 0.25f),
//		},
//		{//上向き
//			nn::math::VEC2(0.0f, 0.375f),
//			nn::math::VEC2(0.125f, 0.375f),
//			nn::math::VEC2(0.25f, 0.375f),
//		},
//	},
//	{//赤色
//		{//下向き
//			nn::math::VEC2(0.375f, 0.0f),
//			nn::math::VEC2(0.5f, 0.0f),
//			nn::math::VEC2(0.625f, 0.0f),
//		},
//		{//左向き
//			nn::math::VEC2(0.375f, 0.125f),
//			nn::math::VEC2(0.5f, 0.125f),
//			nn::math::VEC2(0.625f, 0.125f),
//		},
//		{//右向き
//			nn::math::VEC2(0.375f, 0.25f),
//			nn::math::VEC2(0.5f, 0.25f),
//			nn::math::VEC2(0.625f, 0.25f),
//		},
//		{//上向き
//			nn::math::VEC2(0.375f, 0.375f),
//			nn::math::VEC2(0.5f, 0.375f),
//			nn::math::VEC2(0.625f, 0.375f),
//		},
//	},
//	{//青色
//		{//下向き
//			nn::math::VEC2(0.0f, 0.5f),
//			nn::math::VEC2(0.125f, 0.5f),
//			nn::math::VEC2(0.25f, 0.5f),
//		},
//		{//左向き
//			nn::math::VEC2(0.0f, 0.625f),
//			nn::math::VEC2(0.125f, 0.625f),
//			nn::math::VEC2(0.25f, 0.625f),
//		},
//		{//右向き
//			nn::math::VEC2(0.0f, 0.75f),
//			nn::math::VEC2(0.125f, 0.75f),
//			nn::math::VEC2(0.25f, 0.75f),
//		},
//		{//上向き
//			nn::math::VEC2(0.0f, 0.875f),
//			nn::math::VEC2(0.125f, 0.875f),
//			nn::math::VEC2(0.25f, 0.875f),
//		},
//	},
//	{//緑色
//		{//下向き
//			nn::math::VEC2(0.375f, 0.5f),
//			nn::math::VEC2(0.5f, 0.5f),
//			nn::math::VEC2(0.625f, 0.5f),
//		},
//		{//左向き
//			nn::math::VEC2(0.375f, 0.625f),
//			nn::math::VEC2(0.5f, 0.625f),
//			nn::math::VEC2(0.625f, 0.625f),
//		},
//		{//右向き
//			nn::math::VEC2(0.375f, 0.75f),
//			nn::math::VEC2(0.5f, 0.75f),
//			nn::math::VEC2(0.625f, 0.75f),
//		},
//		{//上向き
//			nn::math::VEC2(0.375f, 0.875f),
//			nn::math::VEC2(0.5f, 0.875f),
//			nn::math::VEC2(0.625f, 0.875f),
//		},
//	},
//};
//
//nn::math::VEC2 GetAnimeTable(int color, int muki, int pattern)
//{
//	return ANIM_PATTERN[color][muki][pattern];
//}
