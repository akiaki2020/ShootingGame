//
//#include "main.h"
//#include "table.h"
//
//
////�A�j���[�V�����p�^�[���e�[�u��
//static nn::math::VEC2 ANIM_PATTERN[4][4][3] = {
//	{//���F
//		{//������
//			nn::math::VEC2(0.0f, 0.0f),
//			nn::math::VEC2(0.125f, 0.0f),
//			nn::math::VEC2(0.25f, 0.0f),
//		},
//		{//������
//			nn::math::VEC2(0.0f, 0.125f),
//			nn::math::VEC2(0.125f, 0.125f),
//			nn::math::VEC2(0.25f, 0.125f),
//		},
//		{//�E����
//			nn::math::VEC2(0.0f, 0.25f),
//			nn::math::VEC2(0.125f, 0.25f),
//			nn::math::VEC2(0.25f, 0.25f),
//		},
//		{//�����
//			nn::math::VEC2(0.0f, 0.375f),
//			nn::math::VEC2(0.125f, 0.375f),
//			nn::math::VEC2(0.25f, 0.375f),
//		},
//	},
//	{//�ԐF
//		{//������
//			nn::math::VEC2(0.375f, 0.0f),
//			nn::math::VEC2(0.5f, 0.0f),
//			nn::math::VEC2(0.625f, 0.0f),
//		},
//		{//������
//			nn::math::VEC2(0.375f, 0.125f),
//			nn::math::VEC2(0.5f, 0.125f),
//			nn::math::VEC2(0.625f, 0.125f),
//		},
//		{//�E����
//			nn::math::VEC2(0.375f, 0.25f),
//			nn::math::VEC2(0.5f, 0.25f),
//			nn::math::VEC2(0.625f, 0.25f),
//		},
//		{//�����
//			nn::math::VEC2(0.375f, 0.375f),
//			nn::math::VEC2(0.5f, 0.375f),
//			nn::math::VEC2(0.625f, 0.375f),
//		},
//	},
//	{//�F
//		{//������
//			nn::math::VEC2(0.0f, 0.5f),
//			nn::math::VEC2(0.125f, 0.5f),
//			nn::math::VEC2(0.25f, 0.5f),
//		},
//		{//������
//			nn::math::VEC2(0.0f, 0.625f),
//			nn::math::VEC2(0.125f, 0.625f),
//			nn::math::VEC2(0.25f, 0.625f),
//		},
//		{//�E����
//			nn::math::VEC2(0.0f, 0.75f),
//			nn::math::VEC2(0.125f, 0.75f),
//			nn::math::VEC2(0.25f, 0.75f),
//		},
//		{//�����
//			nn::math::VEC2(0.0f, 0.875f),
//			nn::math::VEC2(0.125f, 0.875f),
//			nn::math::VEC2(0.25f, 0.875f),
//		},
//	},
//	{//�ΐF
//		{//������
//			nn::math::VEC2(0.375f, 0.5f),
//			nn::math::VEC2(0.5f, 0.5f),
//			nn::math::VEC2(0.625f, 0.5f),
//		},
//		{//������
//			nn::math::VEC2(0.375f, 0.625f),
//			nn::math::VEC2(0.5f, 0.625f),
//			nn::math::VEC2(0.625f, 0.625f),
//		},
//		{//�E����
//			nn::math::VEC2(0.375f, 0.75f),
//			nn::math::VEC2(0.5f, 0.75f),
//			nn::math::VEC2(0.625f, 0.75f),
//		},
//		{//�����
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
