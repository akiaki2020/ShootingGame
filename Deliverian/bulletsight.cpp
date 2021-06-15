
#include "main.h"
#include "Func_texture.h"
#include "bulletsight.h"

//*****************************************************************************
// CONST変数
//*****************************************************************************
#define BULLETSIGHT_WIDTH	(32)	
#define BULLETSIGHT_HEIGHT	(32)	

#define MAX_BULLETSIGHT		1		
#define NUM_BULLETSIGHT		2		

const static Texture_DATA c_InitTexture[] =
{
	{
		(char *)"TEXTURE/Stg_main/Player/target_player.png"
		,NULL
		,NULL
		,D3DXVECTOR3
		(SCREEN_GAME_WIDTH / 2, SCREEN_GAME_HEIGHT / 4 * 3, 0.0f)	//ここでは使わない
		,BULLETSIGHT_WIDTH
		,BULLETSIGHT_HEIGHT
		,true
		,0
		,0
		,true
		,NON_DIVIDE
		,NON_DIVIDE
		,NON_DIVIDE_TEXTURENUMBER
		,false
		,D3DXVECTOR4(128, 255, 128, 255)
	},
};

enum
{
	TEXTURE_bulletsight,
	TEXTURE_bulletsight_MAX,
};
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************

BULLETSIGHT BulletSight[MAX_BULLETSIGHT];					//弾のデータ

static VERTEX_2D g_PolygonVertex[TEXTURE_bulletsight_MAX][4];//頂点データ
static Texture_DATA g_Texture[TEXTURE_bulletsight_MAX];

void InitBulletSight()
{

	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	for (int i = 0; i < MAX_BULLETSIGHT; i++)
	{
		BulletSight[i].pos.x = SCREEN_GAME_WIDTH / 2;
		BulletSight[i].pos.y = SCREEN_GAME_HEIGHT /2;

		//有効フラグをONにする
		BulletSight[i].isEnable = TRUE;
		// 頂点情報の作成
	}
	//テクスチャデータの初期化
	for (int i = 0; i < TEXTURE_bulletsight_MAX; i++)
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


void UninitBulletSight()
{
	for (int i = 0; i < TEXTURE_bulletsight_MAX; i++)
	{
		UnLoadTextureDATA(&g_Texture[i]);
	}
}


void UpdateBulletSight()
{
	for (int i = 0; i < MAX_BULLETSIGHT; i++)
	{
		//有効フラグがONじゃなければ何もしない
		if (BulletSight[i].isEnable == false)
			continue;

		//座標を更新する
		BulletSight[i].pos += BulletSight[i].dir;

		//弾場外判定
		if (BulletSight[i].pos.y < 0 + BULLETSIGHT_HEIGHT / 2)
			BulletSight[i].pos.y = BULLETSIGHT_HEIGHT / 2;
		if (BulletSight[i].pos.y > SCREEN_HEIGHT- BULLETSIGHT_HEIGHT/2)
			BulletSight[i].pos.y = SCREEN_HEIGHT - BULLETSIGHT_HEIGHT/2;
		if (BulletSight[i].pos.x < 0+ BULLETSIGHT_WIDTH/2)
			BulletSight[i].pos.x = BULLETSIGHT_WIDTH / 2;
		if (BulletSight[i].pos.x > SCREEN_GAME_WIDTH - BULLETSIGHT_WIDTH/2)
			BulletSight[i].pos.x = SCREEN_GAME_WIDTH - BULLETSIGHT_WIDTH/2;
	}
}


void DrawBulletSight()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (int i = 0; i < MAX_BULLETSIGHT; i++)
	{
		//有効フラグがONじゃなければ何もしない
		if (BulletSight[i].isEnable == false)
			continue;
		g_Texture[TEXTURE_bulletsight].Pos = BulletSight[i].pos;

		DrawTextureDATA(
			pDevice,
			&g_Texture[TEXTURE_bulletsight]
		);
	}
}


//有効フラグを渡す
bool GetIsEnableBulletSight(int index)
{
	return BulletSight[index].isEnable;
}


//ENEMYのGetter
BULLETSIGHT* GetBulletSight() {
	return (&BulletSight[0]);
}


//ENEMYのGetter
void BulletMove(D3DXVECTOR3 pos) {
	for (int i = 0; i < MAX_BULLETSIGHT; i++)
	{
		//有効フラグがONじゃなければ何もしない
		if (BulletSight[i].isEnable == false)
			continue;

		BulletSight[i].pos += pos;

	}
}

//弾の射出処理
void SetBulletSight(D3DXVECTOR3 pos,
	D3DXVECTOR3 velovity)
{
	for (int i = 0; i < MAX_BULLETSIGHT; i++) {
		//弾の配列から空きを探す
		//現在使っている領域だった場合は
		//何もしないでスルーする
		if (BulletSight[i].isEnable == true)
			continue;

		//発射する位置をセット
		BulletSight[i].pos.x = pos.x;
		BulletSight[i].pos.y = pos.y;

		//飛んでいく方向をセット
		BulletSight[i].dir = velovity;

		//移動方向にスピードを掛ける
		BulletSight[i].dir *= 1;

		//有効フラグをONにする
		BulletSight[i].isEnable = true;

		//弾を１つセットしたら終了する
		break;
	}
}
