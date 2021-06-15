//=============================================================================
//
// Mainヘッダー [main.h]
// Author : 
//
//=============================================================================
#ifndef _MAIN_H_
#define _MAIN_H_

#define _CRT_SECURE_NO_WARNINGS			// scanf のwarning防止

#include "windows.h"
#include "d3dx9.h"
#include <tchar.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DIRECTINPUT_VERSION 0x0800		// 警告対処
#include "dinput.h"
#include "mmsystem.h"

#if 1	// [ここを"0"にした場合、"構成プロパティ" -> "リンカ" -> "入力" -> "追加の依存ファイル"に対象ライブラリを設定する]
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "winmm.lib")
#endif

#define SCREEN_GAME_WIDTH	(500)			// UI分縮めたウインドウの幅
#define SCREEN_GAME_HEIGHT	(480)			// UI分縮めたウインドウの高さ
#define SCREEN_WIDTH	(640)				// ウインドウの幅
#define SCREEN_HEIGHT	(480)				// ウインドウの高さ
#define SCREEN_CENTER_X	(SCREEN_WIDTH / 2)	// ウインドウの中心Ｘ座標
#define SCREEN_CENTER_Y	(SCREEN_HEIGHT / 2)	// ウインドウの中心Ｙ座標

#define NON_DIVIDE 1//テクスチャー分割がないとき
#define NON_DIVIDE_TEXTURENUMBER 0//↑を使用した際のテクスチャー番号



#define	NUM_VERTEX		(4)					// 頂点数
#define	NUM_PLAYER		(2)					// ポリゴン数

// 頂点フォーマット( 頂点座標[2D] / 反射光 / テクスチャ座標 )
#define	FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)

// 上記頂点フォーマットに合わせた構造体を定義
typedef struct
{
	D3DXVECTOR3 vtx;		// 頂点座標
	float rhw;				// テクスチャのパースペクティブコレクト用
	D3DCOLOR diffuse;		// 反射光
	D3DXVECTOR2 tex;		// テクスチャ座標
} VERTEX_2D;

//テクスチャ用の構造体
typedef struct
{
	char * Path;		// 格納場所
	LPDIRECT3DTEXTURE9 pD3DTexture;//テクスチャ格納場所
	VERTEX_2D* Vertex;//頂点座標
	D3DXVECTOR3 Pos;	//場所
	float Size_x;				// サイズX
	float Size_y;			// サイズY
	bool IsEnable;			//表示
	float Angle;			//角度
	float BaseAngle;	//初期角度
	bool IsEnableRotation; //回転して出すか
	int Divide_x;			//分割数_x
	int Divide_y;			//分割数_y
	int TextureNumber;		//テクスチャー番号	
	bool IsEnableDivide;	//テクスチャが分割されているか？
	D3DXVECTOR4 Color;//テクスチャーカラー

} Texture_DATA;




LPDIRECT3DDEVICE9 GetDevice(void);		// デバイス取得関数


#endif