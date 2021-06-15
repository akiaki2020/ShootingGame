//=============================================================================
//
// サウンド処理 [sound.h]
//
//=============================================================================
#ifndef _DRAW_TEXT_H_
#define _DRAW_TEXT_H_

#include "main.h"						// サウンド処理で必要




void InitText(void);
void UninitText(void);
//void Drawtextfnc(void);
void Drawtextfnc(char* drawText);
void Drawtextfnc(char* drawText,RECT rect);
void Drawtextfnc(char* drawText, RECT rect, D3DXVECTOR4 color);

#endif
