//#include <math.h>
#include "Func_texture.h"
#define _USE_MATH_DEFINES 
#include "math.h"

float g_th=0.0f;

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertex(VERTEX_2D *g_vertexWk)
{
	// rhwの設定
	g_vertexWk[0].rhw = 1.0f;
	g_vertexWk[1].rhw = 1.0f;
	g_vertexWk[2].rhw = 1.0f;
	g_vertexWk[3].rhw = 1.0f;

	// 反射光の設定
	g_vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	return S_OK;
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertex(VERTEX_2D *g_vertexWk, D3DXVECTOR4 color)
{
	// rhwの設定
	g_vertexWk[0].rhw = 1.0f;
	g_vertexWk[1].rhw = 1.0f;
	g_vertexWk[2].rhw = 1.0f;
	g_vertexWk[3].rhw = 1.0f;

	// 反射光の設定
	g_vertexWk[0].diffuse = D3DCOLOR_RGBA((int)color.x, (int)color.y, (int)color.z, (int)color.w);
	g_vertexWk[1].diffuse = D3DCOLOR_RGBA((int)color.x, (int)color.y, (int)color.z, (int)color.w);
	g_vertexWk[2].diffuse = D3DCOLOR_RGBA((int)color.x, (int)color.y, (int)color.z, (int)color.w);
	g_vertexWk[3].diffuse = D3DCOLOR_RGBA((int)color.x, (int)color.y, (int)color.z, (int)color.w);

	return S_OK;
}




//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTexture(VERTEX_2D *g_vertexWk,
	int Texture_Divide_x,
	int Texture_Divide_y)
{
	int x = 0;
	int y = 0;
	// テクスチャ座標の設定
	float sizeX = 1.0f / Texture_Divide_x;
	float sizeY = 1.0f / Texture_Divide_y;

	g_vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	g_vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	g_vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	g_vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
}
//=============================================================================
// テクスチャ座標の設定PNGの特定のファイルを使う場合
//左上のTEXTURE：Texture_Number＝0
//=============================================================================
void SetTexture(VERTEX_2D *g_vertexWk,
	int Texture_Divide_x,
	int Texture_Divide_y,
	int Texture_Number)
{
	int x = 0;
	int y = 0;
	// テクスチャ座標の設定
	float sizeX = 1.0f / Texture_Divide_x;
	float sizeY = 1.0f / Texture_Divide_y;
	x = Texture_Number % Texture_Divide_x;
	y = Texture_Number / Texture_Divide_x;
	g_vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	g_vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	g_vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	g_vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
}
//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertex(VERTEX_2D *g_vertexWk,
	D3DXVECTOR3 pos,
	float Texture_Size_x,
	float Texture_Size_y)
{
	// 頂点座標の設定
	g_vertexWk[0].vtx = D3DXVECTOR3(pos.x - Texture_Size_x/2, pos.y - Texture_Size_y/2, pos.z);
	g_vertexWk[1].vtx = D3DXVECTOR3(pos.x + Texture_Size_x / 2, pos.y - Texture_Size_y / 2, pos.z);
	g_vertexWk[2].vtx = D3DXVECTOR3(pos.x - Texture_Size_x / 2, pos.y + Texture_Size_y / 2, pos.z);
	g_vertexWk[3].vtx = D3DXVECTOR3(pos.x + Texture_Size_x / 2, pos.y + Texture_Size_y / 2, pos.z);
}
//=============================================================================
// 頂点座標の設定 ２点で伸び縮する場合　//扱いが特殊現状はUIのみ使う
										//縦のみ
//=============================================================================

void SetVertexVeticalSpread(VERTEX_2D *g_vertexWk,
	D3DXVECTOR3 Spos,	//スタートポジション
	D3DXVECTOR3 Epos,	//伸びポジション
	float Texture_Size_x)
{
	// 頂点座標の設定
	g_vertexWk[0].vtx = D3DXVECTOR3(Spos.x - Texture_Size_x / 2, Spos.y, Spos.z);
	g_vertexWk[1].vtx = D3DXVECTOR3(Spos.x + Texture_Size_x / 2, Spos.y, Spos.z);
	g_vertexWk[2].vtx = D3DXVECTOR3(Epos.x - Texture_Size_x / 2, Epos.y, Spos.z);
	g_vertexWk[3].vtx = D3DXVECTOR3(Epos.x + Texture_Size_x / 2, Epos.y, Spos.z);
}

//=============================================================================
// 頂点座標の設定 ２点で伸び縮する場合　//扱いが特殊現状はUIのみ使う
//縦のみ
//=============================================================================

void SetHorizoneVeticalSpread(VERTEX_2D *g_vertexWk,
	D3DXVECTOR3 Spos,	//スタートポジション
	D3DXVECTOR3 Epos,	
	float Texture_Size_y)
{
	// 頂点座標の設定
	g_vertexWk[0].vtx = D3DXVECTOR3(Spos.x, Spos.y - Texture_Size_y / 2, Spos.z);
	g_vertexWk[1].vtx = D3DXVECTOR3(Epos.x, Spos.y - Texture_Size_y / 2, Spos.z);
	g_vertexWk[2].vtx = D3DXVECTOR3(Spos.x, Epos.y + Texture_Size_y / 2, Spos.z);
	g_vertexWk[3].vtx = D3DXVECTOR3(Epos.x, Epos.y + Texture_Size_y / 2, Spos.z);
}

//=============================================================================
// 頂点座標の設定	方向を付け加える場合
//=============================================================================
void SetVertex(VERTEX_2D *g_vertexWk,
	D3DXVECTOR3 pos,
	float Texture_Size_x,
	float Texture_Size_y,
	float baseAngle,
	float rotation)
{
	D3DXVECTOR3 tempVec3= D3DXVECTOR3(Texture_Size_x / 2, Texture_Size_y / 2, 0);

	double TempLen= D3DXVec3Length(&tempVec3);

	D3DXVECTOR3 TempD3 = D3DXVECTOR3(0, 0, 0);
	D3DXVECTOR3 MoveD3 = D3DXVECTOR3(0, 0, 0);

	//////三角関数の加法定理
	TempD3.x = pos.x - cosf(baseAngle+ rotation) *TempLen;
	TempD3.y = pos.y - sinf(baseAngle + rotation) * TempLen;
	g_vertexWk[0].vtx = D3DXVECTOR3(TempD3.x, TempD3.y, pos.z);

	TempD3.x = pos.x + cosf(baseAngle - rotation) * TempLen;
	TempD3.y = pos.y - sinf(baseAngle - rotation) * TempLen;
	g_vertexWk[1].vtx = D3DXVECTOR3(TempD3.x, TempD3.y, pos.z) ;
	
	TempD3.x = pos.x - cosf(baseAngle - rotation) * TempLen;
	TempD3.y = pos.y + sinf(baseAngle - rotation) * TempLen;
	g_vertexWk[2].vtx = D3DXVECTOR3(TempD3.x, TempD3.y, pos.z) ;

	TempD3.x = pos.x + cosf(baseAngle + rotation) * TempLen;
	TempD3.y = pos.y + sinf(baseAngle + rotation) * TempLen;
	g_vertexWk[3].vtx = D3DXVECTOR3(TempD3.x, TempD3.y, pos.z) ;

	}


//=============================================================================
// 頂点座標の設定	方向を付け加える場合 ２点で伸び縮する場合
//=============================================================================
void SetVertexVeticalSpread(VERTEX_2D *g_vertexWk,
	D3DXVECTOR3 Spos,	//スタートポジション
	D3DXVECTOR3 Epos,	//伸びポジション
	float Texture_Size_x, //太さ
	float Texture_Size_y,
	float baseAngle,
	float rotation)
{



	D3DXVECTOR3 tempVec3 = D3DXVECTOR3(Texture_Size_x / 2, Texture_Size_y / 2, 0);

	double TempLen = D3DXVec3Length(&tempVec3);

	D3DXVECTOR3 TempD3 = D3DXVECTOR3(0, 0, 0);
	D3DXVECTOR3 MoveD3 = D3DXVECTOR3(0, 0, 0);

	//////三角関数の加法定理
	
	TempD3.x = Epos.x - cosf(baseAngle + rotation) * TempLen;
	TempD3.y = Epos.y - sinf(baseAngle + rotation) * TempLen;
	g_vertexWk[0].vtx = D3DXVECTOR3(TempD3.x, TempD3.y, Spos.z);

	TempD3.x = Epos.x + cosf(baseAngle - rotation) * TempLen;
	TempD3.y = Epos.y - sinf(baseAngle - rotation) * TempLen;
	g_vertexWk[1].vtx = D3DXVECTOR3(TempD3.x, TempD3.y, Spos.z);

	TempD3.x = Spos.x - cosf(baseAngle - rotation) * TempLen;
	TempD3.y = Spos.y + sinf(baseAngle - rotation) * TempLen;
	g_vertexWk[2].vtx = D3DXVECTOR3(TempD3.x, TempD3.y, Epos.z);

	TempD3.x = Spos.x + cosf(baseAngle + rotation) * TempLen;
	TempD3.y = Spos.y + sinf(baseAngle + rotation) * TempLen;
	g_vertexWk[3].vtx = D3DXVECTOR3(TempD3.x, TempD3.y, Epos.z);

}




//２つのベクトルABのなす角度θを求める
double AngleOf2Vector(D3DXVECTOR3 A, D3DXVECTOR3 B)
{
	//　※ベクトルの長さが0だと答えが出ませんので注意してください。

	//ベクトルAとBの長さを計算する
	double length_A = D3DXVec3Length(&A);
	double length_B = D3DXVec3Length(&B);

	//内積とベクトル長さを使ってcosθを求める
	double cos_sita = D3DXVec3Dot(&A, &B) / (length_A * length_B);

	//cosθからθを求める
	double sita = acos(cos_sita);

	//ラジアンでなく0～180の角度でほしい場合はコメント外す
	//sita = sita * 180.0 / PI;

	return sita;
}
D3DXVECTOR3 Vec3Normalize(D3DXVECTOR3 *pV)
{
	double len;
	double x, y, z;

	x = (double)(pV->x);
	y = (double)(pV->y);
	z = (double)(pV->z);
	len = sqrt(x * x + y * y + z * z);

	if (len < (1e-6)) return D3DXVECTOR3(0, 0, 0);

	len = 1.0 / len;
	x *= len;
	y *= len;
	z *= len;
	return D3DXVECTOR3((float)x, (float)y, (float)z);
}


//各関数Init時に使用
void SetTextureDATA(
	LPDIRECT3DDEVICE9 pDevice,
	VERTEX_2D *g_vertexWk,
	Texture_DATA *texture,		//セットするテクスチャーデータ
	const Texture_DATA *InitTexture	//セットする値
	)
{
	//初期化
	*texture =
		*InitTexture;

	//初期角度の格納
	texture->BaseAngle =
		atan2f(texture->Size_y, texture->Size_x);

	//頂点座標の設定
	MakeVertex(g_vertexWk);

	if (texture->IsEnableDivide)
	{
		SetTexture(g_vertexWk,
			texture->Divide_x,
			texture->Divide_y,
			texture->TextureNumber);
	}
	else
	{
		SetTexture(g_vertexWk,
			texture->Divide_x,
			texture->Divide_y);
	}


	//場所決定
	SetVertex(g_vertexWk,
		texture->Pos,
		texture->Size_x,
		texture->Size_y);

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,		// デバイスのポインタ
		texture->Path,				// ファイルの名前
		&texture->pD3DTexture);					// 読み込むメモリのポインタ
															//頂点座標情報を格納
	texture->Vertex = g_vertexWk;
}

//各関数UnInit時に使用
void UnLoadTextureDATA(
	Texture_DATA *texture		//アンロードするテクスチャーデータ
	)
{
	if (texture->pD3DTexture != NULL)
	{	// テクスチャの開放
		texture->pD3DTexture->Release();
		texture->pD3DTexture = NULL;
	}
}


//各関数Draw時に使用
void DrawTextureDATA(
	LPDIRECT3DDEVICE9 pDevice,
	Texture_DATA *texture		//Drawするテクスチャーデータ
	)
{
	//有効フラグがONじゃなければ何もしない
	if (texture->IsEnable == false)
		return;

	//初期角度の格納
	texture->BaseAngle =atan2f(texture->Size_y, texture->Size_x);
	//色設定
	MakeVertex(texture->Vertex, texture->Color);

	//頂点座標セット
	if (texture->IsEnableRotation)
	{
		SetVertex(texture->Vertex,
			texture->Pos,
			texture->Size_x,
			texture->Size_y,
			texture->BaseAngle,
			texture->Angle);

	}
	else
	{
		SetVertex(texture->Vertex,
			texture->Pos,
			texture->Size_x,
			texture->Size_y);
	}

	if (texture->IsEnableDivide)
	{
		SetTexture(texture->Vertex,
			texture->Divide_x,
			texture->Divide_y,
			texture->TextureNumber);
	}
	else
	{
		SetTexture(texture->Vertex,
			texture->Divide_x,
			texture->Divide_y);
	}

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	// テクスチャの設定
	pDevice->SetTexture(0, texture->pD3DTexture);
	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_PLAYER, texture->Vertex, sizeof(VERTEX_2D));

}