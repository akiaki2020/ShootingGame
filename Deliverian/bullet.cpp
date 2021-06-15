#include "main.h"
#define _USE_MATH_DEFINES 
#include "math.h"
#include "Func_texture.h"
#include "bullet.h"

//*****************************************************************************
// CONST変数
//*****************************************************************************

const static Texture_DATA c_InitTexture[] =
{
	{
	(char *)"TEXTURE/bullet.tga"
	,NULL
	,NULL
	,D3DXVECTOR3(SCREEN_GAME_WIDTH / 2, SCREEN_GAME_HEIGHT / 4 * 3, 0.0f)	//ここでは使わない
	,BULLET_WIDTH
	,BULLET_HEIGHT
	,true
	,0
	,0
	,false
	,NON_DIVIDE
	,NON_DIVIDE
	,NON_DIVIDE_TEXTURENUMBER
	,false
	,D3DXVECTOR4(255, 255, 255, 255)
	},
};

enum TextureType {
	NORMAL,
	TYPE_MAX
};

//所属
static enum Affiliation {
	PLAYER,
	ENEMY,
	Affiliation_MAX
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexBullet(BULLET* bullet);

//*****************************************************************************
// グローバル変数
//*****************************************************************************

BULLET bullet[MAX_BULLET];					//弾のデータ

static LPDIRECT3DTEXTURE9		g_pD3DTexture = NULL;		// テクスチャへのポインタ
static VERTEX_2D g_PolygonVertex[TYPE_MAX][4];//頂点データ
static Texture_DATA g_Texture[TYPE_MAX];

void InitBullet()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int i = 0; i < MAX_BULLET; i++)
	{
		bullet[i].pos.x = 0;
		bullet[i].pos.y = 0;
		bullet[i].size.x = BULLET_WIDTH;
		bullet[i].size.y = BULLET_HEIGHT;
		bullet[i].size.z = 0;
		bullet[i].type = NORMAL;

		bullet[i].power = 1;
		//有効フラグをOFFにする
		bullet[i].isEnable = false;
	}

	//テクスチャデータの初期化
	for (int i = 0; i < TYPE_MAX; i++)
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


void UninitBullet()
{
	//UninitInput();
	for (int i = 0; i < TYPE_MAX; i++)
	{
		UnLoadTextureDATA(&g_Texture[i]);
	}
}


void UpdateBullet()
{
	for (int i = 0; i < MAX_BULLET; i++)
	{
		//有効フラグがONじゃなければ何もしない
		if (bullet[i].isEnable == false)
			continue;

		//座標を更新する
		bullet[i].pos += bullet[i].dir;
		//向きを格納する
		bullet[i].Rotation = atan2f(bullet[i].dir.y, bullet[i].dir.x) + (M_PI / 2);

		//弾が画面から出て行ってしまったら
		//有効フラグを落とす
		if (bullet[i].pos.y < 0- BULLET_HEIGHT/2)
			bullet[i].isEnable = false;
		//有効フラグを落とす
		if (bullet[i].pos.y > SCREEN_HEIGHT + BULLET_HEIGHT/2)
			bullet[i].isEnable = false;
		//有効フラグを落とす
		if (bullet[i].pos.x < 0 - BULLET_WIDTH / 2)
			bullet[i].isEnable = false;
		//有効フラグを落とす
		if (bullet[i].pos.x > SCREEN_WIDTH + BULLET_WIDTH/2)
			bullet[i].isEnable = false;
	}
}


void DrawBullet()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);


	for (int i = 0; i < MAX_BULLET; i++)
	{
		//有効フラグがONじゃなければ何もしない
		if (bullet[i].isEnable == false)
			continue;

		int textureType = bullet[i].type;
		g_Texture[textureType].Pos = bullet[i].pos;
		g_Texture[textureType].Angle = bullet[i].Rotation;
		g_Texture[textureType].Size_x= bullet[i].size.x;
		g_Texture[textureType].Size_y = bullet[i].size.y;
		MakeVertexBullet(&bullet[i]);

		DrawTextureDATA(
			pDevice,
			&g_Texture[textureType]
		);
	}
}


//有効フラグを渡す
bool GetIsEnableBullet(int index)
{
	return bullet[index].isEnable;
}


//ENEMYのGetter
BULLET* GetBullet() {
	return (&bullet[0]);
}

//弾の射出処理
void SetBullet(
	D3DXVECTOR3 pos,
	D3DXVECTOR3 velovity,
	float speed,
	int affiliation)	//プレイヤーか敵か
{
	for (int i = 0; i < MAX_BULLET; i++) {
		//弾の配列から空きを探す
		//現在使っている領域だった場合は
		//何もしないでスルーする
		if (bullet[i].isEnable == true)
			continue;

		//発射する位置をセット
		bullet[i].pos.x = pos.x;
		bullet[i].pos.y = pos.y;

		//飛んでいく方向をセット
		bullet[i].dir = velovity;
		//移動方向にスピードを掛ける
		bullet[i].dir *= speed;

		//敵か味方の弾どちらか決める
		bullet[i].Affiliation = affiliation;
		bullet[i].power = 1;

		//有効フラグをONにする
		bullet[i].isEnable = true;
		//弾を１つセットしたら終了する
		break;
	}
}


//弾の射出処理
void SetBullet(
	D3DXVECTOR3 pos,
	D3DXVECTOR3 velovity,
	float speed,
	int affiliation,
	int power)	//プレイヤーか敵か
{
	for (int i = 0; i < MAX_BULLET; i++) {
		//弾の配列から空きを探す
		//現在使っている領域だった場合は
		//何もしないでスルーする
		if (bullet[i].isEnable == true)
			continue;

		//発射する位置をセット
		bullet[i].pos.x = pos.x;
		bullet[i].pos.y = pos.y;

		//飛んでいく方向をセット
		bullet[i].dir = velovity;
		//移動方向にスピードを掛ける
		bullet[i].dir *= speed;

		//敵か味方の弾どちらか決める
		bullet[i].Affiliation = affiliation;
		bullet[i].power = power;

		//有効フラグをONにする
		bullet[i].isEnable = true;

		//弾を１つセットしたら終了する
		break;
	}
}


//以下関数はBULLETの中のみ

//=============================================================================
// 頂点の作成
//=============================================================================
void MakeVertexBullet(BULLET* bullet)
{
	int textureType = bullet->type;
	// 反射光の設定
	switch (bullet->Affiliation)
	{
	case PLAYERS_BULLET://	デフォルト
		g_Texture[textureType].Color = D3DXVECTOR4(255, 255, 255, 255);
		break;
	case ENEMYS_BULLET://赤
		g_Texture[textureType].Color = D3DXVECTOR4(255, 0, 0, 255);
		break;
	default:
		break;
	}
}

