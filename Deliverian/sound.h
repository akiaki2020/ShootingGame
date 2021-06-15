//=============================================================================
//
// サウンド処理 [sound.h]
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include <windows.h>
#include "xaudio2.h"						// サウンド処理で必要

//*****************************************************************************
// サウンドファイル
//*****************************************************************************
enum 
{
	SOUND_LABEL_BGM_title,		// title
	SOUND_LABEL_BGM_result,		// result
	SOUND_LABEL_BGM_sample000,	// BGM0
	SOUND_LABEL_BGM_sample001,	// BGM1
	SOUND_LABEL_BGM_sample002,	// BGM2
	SOUND_LABEL_BGM_PLAYERDIE,	// BGM2
	SOUND_LABEL_SE_titlebutton,	// titleボタンオン
	SOUND_LABEL_SE_bomb000,		// 爆発音
	SOUND_LABEL_SE_DAMAGE000,	// 
	SOUND_LABEL_SE_PLAYERDIE,	//
	SOUND_LABEL_SE_defend001,	// 
	SOUND_LABEL_SE_Enemyhit000,		// 
	SOUND_LABEL_SE_EnemyDie000,		// 

	SOUND_LABEL_SE_laser000,	// 
	SOUND_LABEL_SE_lockon000,	// 
	SOUND_LABEL_SE_shot000,		// 
	SOUND_LABEL_SE_shot001,		// 
	SOUND_LABEL_SE_RESULT_PAPER,		// 
	SOUND_LABEL_SE_RESULT_PEN,		// 
	SOUND_LABEL_SE_RESULT_HANKObf,		// 
	SOUND_LABEL_SE_RESULT_HANKOafter,		// 
	SOUND_LABEL_MAX,
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
bool InitSound(HWND hWnd);
void UninitSound(void);
void PlaySound(int label);
void StopSound(int label);
void StopSound(void);
void StopandRewindSound(int label);

IXAudio2MasteringVoice *GetMasteringVoice(void);

#endif
