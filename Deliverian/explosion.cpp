
#include "main.h"
#include "Func_texture.h"

#include "explosion.h"
#define _USE_MATH_DEFINES 
#include "math.h"

#define EXPLOSION_MAX 1000
#define PI 3.141592f

#define EXPLOSION_DIVIDE_X 5
#define EXPLOSION_DIVIDE_Y 5
#define EXPLOSION_FIRST 0

struct EXPLOSION
{
	bool			Enable;
	float			Alpha;
	D3DXVECTOR3	Position;
	float			g_th;
	float			Ran;
	D3DXVECTOR3 size;

	float			Rotation;
	float			RotationSpeed;
	int				type;
	int				TextureNumber;;
};

enum
{
	TEXTURE_EXPLODE,
	TEXTURE_EXPLODE_MAX,
};

//*****************************************************************************
// グローバル変数
//*****************************************************************************

EXPLOSION g_Explosion[EXPLOSION_MAX];					//エネミーデータ

static VERTEX_2D g_PolygonVertex[TEXTURE_EXPLODE_MAX][4];

const static Texture_DATA c_InitTexture[] =
{
	{
	(char *)"TEXTURE/Stg_main/Explosion/explosion.tga"
	,NULL
	,NULL
	,D3DXVECTOR3(SCREEN_GAME_WIDTH / 2, SCREEN_GAME_HEIGHT / 4 * 3, 0.0f)	//ここでは使わない
	,32
	,32
	,true
	,0
	,0
	,true
	,EXPLOSION_DIVIDE_X
	,EXPLOSION_DIVIDE_Y
	,EXPLOSION_FIRST
	,true
	,D3DXVECTOR4(255, 255, 255, 255)
	},
};


static Texture_DATA g_Texture[TEXTURE_EXPLODE_MAX];


void InitExplosion()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	for (int i = 0; i < EXPLOSION_MAX; i++)
	{
		g_Explosion[i].Enable = false;
		g_Explosion[i].g_th = 0.0f;
		g_Explosion[i].Ran = 0.0f;
		g_Explosion[i].size.x = 64;
		g_Explosion[i].size.y = 64;
		g_Explosion[i].size.z= 0.0f;
		g_Explosion[i].type = TEXTURE_EXPLODE;
		g_Explosion[i].TextureNumber = EXPLOSION_FIRST;
	}

	//テクスチャデータの初期化
	for (int i = 0; i < TEXTURE_EXPLODE_MAX; i++)
	{
		SetTextureDATA
		(
			pDevice,
			g_PolygonVertex[i],
			&g_Texture[i],
			&c_InitTexture[i]
		);
	}

}



void UninitExplosion()
{
	for (int i = 0; i < TEXTURE_EXPLODE_MAX; i++)
	{

		UnLoadTextureDATA(&g_Texture[i]);
	}
}


void UpdateExplosion()
{

	for (int i = 0; i < EXPLOSION_MAX; i++)
	{
		if (!g_Explosion[i].Enable)
			continue;
		g_Explosion[i].g_th+=1.0f/120.0f;

		if (int(g_Explosion[i].g_th*1000)%3 ==0)
		{
			g_Explosion[i].TextureNumber++;
		}
		////完全に透明になったら処理を終了する。
		if (g_Explosion[i].g_th > 0.7f)
		{
			g_Explosion[i].Enable = false;
		}
	}
}


void DrawExplosion()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	for (int i = 0; i < EXPLOSION_MAX; i++)
	{
		//有効フラグがONじゃなければ何もしない
		if (g_Explosion[i].Enable == false)
			continue;

		//ENEMYデータをテクスチャーに格納する
		int textureType = g_Explosion[i].type;
		g_Texture[textureType].Pos = g_Explosion[i].Position;
		g_Texture[textureType].Angle = g_Explosion[i].Rotation;
		g_Texture[textureType].Size_x = g_Explosion[i].size.x;
		g_Texture[textureType].Size_y = g_Explosion[i].size.y;
		g_Texture[textureType].TextureNumber=g_Explosion[i].TextureNumber;
		
		DrawTextureDATA(
			pDevice,
			&g_Texture[textureType]
		);
	}
}


void SetExplosion(D3DXVECTOR3 Position)
{
	for (int i = 0; i < EXPLOSION_MAX; i++)
	{
		if (!g_Explosion[i].Enable)
		{
			g_Explosion[i].g_th = 0;
			g_Explosion[i].Position = Position;
			g_Explosion[i].TextureNumber = 0;
			g_Explosion[i].Alpha = 1.0f;
			g_Explosion[i].Enable = true;
			return;
		}
	}
}