
#include "main.h"
#include "Func_texture.h"
#define _USE_MATH_DEFINES 
#include "math.h"
#include "enemy_laser.h"
#include "input.h"
#include "texture.h"
#include "table.h"


//*****************************************************************************
// CONST変数
//*****************************************************************************



const Texture_DATA c_InitTexture[MAX_LASER_TYPE] =
{
	{
		(char *)"TEXTURE/Stg_main/Shoot/bullet2.tga"
		,NULL
		,NULL
		,D3DXVECTOR3(
			SCREEN_GAME_WIDTH / 2,
			SCREEN_GAME_HEIGHT / 4 * 3,
			0.0f)	//ここでは使わない
		,LASER_WIDTH
		,LASER_WIDTH
		,true
		,0
		,0
		,true
		,NON_DIVIDE
		,NON_DIVIDE
		,NON_DIVIDE_TEXTURENUMBER
		,false
		,D3DXVECTOR4(255, 255, 255, 255)
	},
};

//*****************************************************************************
// グローバル変数
//*****************************************************************************

LASER Laser[MAX_LASER];

static VERTEX_2D g_PolygonVertex[MAX_LASER_TYPE][4];	//頂点データ
static unsigned int g_Texture;			//テクスチャデータ
static Texture_DATA g_texture[MAX_LASER_TYPE];

void InitEnemyLaser()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (int i = 0; i < MAX_LASER_TYPE; i++)
	{
		SetTextureDATA(
			pDevice,
			g_PolygonVertex[i]
			, &g_texture[i]
			, &c_InitTexture[i]);
	}
	for (int i = 0; i < MAX_LASER; i++)
	{
		Laser[i].isEnable = false;
	}
}


void UninitEnemyLaser()
{
	for (int i = 0; i < MAX_LASER_TYPE; i++)
	{
		UnLoadTextureDATA(&g_texture[i]);
	}
	
}


void UpdateEnemyLaser()
{
	for (int i = 0; i < MAX_LASER; i++)
	{
		//有効フラグがONじゃなければ何もしない
		if (Laser[i].isEnable == false)
			continue;

		//座標を更新する
		Laser[i].pos += Laser[i].dir;
		
		//レーザー発射終了フラグが有効化したら
		//スタート地点を動かす
		if (Laser[i].isEnd ==true)
			Laser[i].s_pos += Laser[i].dir;

		//特定の長さまで行ったら伸びる処理は終了となる
		D3DXVECTOR3 tempVec3 = Laser[i].pos - Laser[i].s_pos;
		float tempflt = D3DXVec3Length(&tempVec3);

		if (tempflt > Laser[i].Nagasa)
		{
			Laser[i].isEnd = true;
		}


		//弾が画面から出て行ってしまったら
		//有効フラグを落とす
		if (Laser[i].s_pos.x > SCREEN_GAME_WIDTH)
			Laser[i].isEnable = false;
		if (Laser[i].s_pos.x < 0)
			Laser[i].isEnable = false;
		if (Laser[i].s_pos.y > SCREEN_GAME_HEIGHT)
			Laser[i].isEnable = false;
		if (Laser[i].s_pos.y < 0)
			Laser[i].isEnable = false;


	}
}


void DrawEnemyLaser()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int i = 0; i < MAX_LASER; i++)
	{
		//有効フラグがONじゃなければ何もしない
		if (Laser[i].isEnable == false)
			continue;

		//レーザータイプを格納する
		int textureType = Laser[i].texType;

		//伸びの処理
		g_texture[textureType].Pos = Laser[i].pos;
		g_texture[textureType].Size_x = Laser[i].Futosa;
		g_texture[textureType].BaseAngle = 
			atan2f(g_texture[textureType].Size_y, g_texture[textureType].Size_x);
		g_texture[textureType].Angle = Laser[i].Rotation;

		SetVertexVeticalSpread(g_texture[textureType].Vertex,
			Laser[i].s_pos,	//スタートポジション
			g_texture[textureType].Pos,//伸びポジション
			g_texture[textureType].Size_x,
			g_texture[textureType].Size_y,
			g_texture[textureType].BaseAngle,
			g_texture[textureType].Angle);
			
		//テクスチャー座標のセット
		SetTexture(g_texture[textureType].Vertex,
			g_texture[textureType].Divide_x,
			g_texture[textureType].Divide_y);

		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);
		// テクスチャの設定
		pDevice->SetTexture(0, g_texture[textureType].pD3DTexture);
		// ポリゴンの描画
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_PLAYER, g_texture[textureType].Vertex, sizeof(VERTEX_2D));
		
	}
}


//有効フラグを渡す
bool GetIsEnableEnemyLaser(int index)
{
	return Laser[index].isEnable;
}


//ENEMYのGetter
LASER* GetEnemyLaser() {
	return (Laser);
}



void DestroyEnemyLaser(int index) {

	Laser[index].isEnable = false;
}

void EndEnemyLaser(int index) {

	Laser[index].isEnd = true;
}

//弾の射出処理
LASER* SetEnemyLaser(D3DXVECTOR3 pos, int affiliation, int color
					, float Futosa, float nagasa, int power, D3DXVECTOR3 dir)
{
	for (int i = 0; i < MAX_LASER; i++)
	{
		//弾の配列から空きを探す
		//現在使っている領域だった場合は
		//何もしないでスルーする
		if (Laser[i].isEnable == true)
			continue;

		
		Laser[i].texType = LASER1;
		Laser[i].Affiliation = affiliation;
		Laser[i].power = power;

		Laser[i].s_pos = pos;
		//自機前方に出す
		Laser[i].s_pos.x += dir.x*50.0f;
		Laser[i].s_pos.y += dir.y*50.0f;


		Laser[i].pos = Laser[i].s_pos;
		Laser[i].Futosa = Futosa;
		Laser[i].Nagasa = nagasa;
		Laser[i].isEnd = false;

		Laser[i].dir = dir;
		Laser[i].Rotation =	atan2f(dir.y, dir.x) + (M_PI / 2);
		//移動方向にスピードを掛ける
		Laser[i].dir *= LASER_SPPED;

		//有効フラグをONにする
		Laser[i].isEnable = true;
		return &Laser[i];
		break;
	}
}
