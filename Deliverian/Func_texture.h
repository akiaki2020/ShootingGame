//=============================================================================
//
// 共通処理 [Func_texture.h]
// Author : 
//
//=============================================================================

#pragma once
#include"main.h"
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertex(VERTEX_2D*);

HRESULT MakeVertex(VERTEX_2D*, D3DXVECTOR4 color);

void SetTexture(VERTEX_2D*,
				int Texture_Divide_x,
				int Texture_Divide_y);

//オーバーロード、テクチャーが分割している場合
void SetTexture(VERTEX_2D*,
	int Texture_Divide_x,
	int Texture_Divide_y,
	int Texture_Number);	//何分割目を使うか

void SetVertex(VERTEX_2D*,
					D3DXVECTOR3 pos,
					float Texture_Size_x,
					float Texture_Size_y);

//オーバーロード、方向を付け加える場合
void SetVertex(VERTEX_2D*,
	D3DXVECTOR3 pos,
	float Texture_Size_x,
	float Texture_Size_y,
	float baseAngle,
	float rotation
	);

//縦に伸び縮する
void SetVertexVeticalSpread(VERTEX_2D *g_vertexWk,
	D3DXVECTOR3 Spos,	//スタートポジション
	D3DXVECTOR3 Epos,	//伸びポジション
	float Texture_Size_x);

//縦に伸び縮する
void SetHorizoneVeticalSpread(VERTEX_2D *g_vertexWk,
	D3DXVECTOR3 Spos,	//スタートポジション
	D3DXVECTOR3 Epos,	//伸びるサイズ
	float Texture_Size_y);

//方向付き
void SetVertexVeticalSpread(VERTEX_2D *g_vertexWk,
	D3DXVECTOR3 Spos,	//スタートポジション
	D3DXVECTOR3 Epos,	//伸びポジション
	float Texture_Size_x, //太さ
	float Texture_Size_y,
	float baseAngle,
	float rotation);


//ベクトルの正規化
D3DXVECTOR3 Vec3Normalize(D3DXVECTOR3 *pV);

//2つのベクトルから角度を求める
double AngleOf2Vector(D3DXVECTOR3 A, D3DXVECTOR3 B);

//テクスチャーデータのセット
void SetTextureDATA(
	LPDIRECT3DDEVICE9 pDevice,
	VERTEX_2D *g_vertexWk,
	Texture_DATA *texture,		//セットするテクスチャーデータ
	const Texture_DATA *InitTexture	//セットする値
	);

//テクスチャーデータのアンロード
void UnLoadTextureDATA(
	Texture_DATA *texture		//アンロードするテクスチャーデータ
);


//テクスチャーデータの描画
void DrawTextureDATA(
	LPDIRECT3DDEVICE9 pDevice,
	Texture_DATA *texture		//Drawするテクスチャーデータ
);