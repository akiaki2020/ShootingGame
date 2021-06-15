#include "main.h"
#include "Func_texture.h"
#include "Blade.h"

//*****************************************************************************
// CONST変数
//*****************************************************************************

#define BLADE_APPEARTIME		(1.0)		//BLADEの出現時間

const static Texture_DATA c_InitTexture[] =
{
	{
		(char *)"TEXTURE/Stg_main/Shoot/10.png"
		,NULL
		,NULL
		,D3DXVECTOR3(SCREEN_GAME_WIDTH / 2, 
			SCREEN_GAME_HEIGHT / 4 * 3, 0.0f)	//ここでは使わない
		,32
		,32
		,false
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

enum
{
	TEXTURE_BLADE,
	TEXTURE_BLADE_MAX,
};
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
//void MakeVertexBlade(int index,int affiliation);
//void SetTextureBlade(int index);	// 
//void SetVertexBlade(int index);					// 頂点の計算処理
//

//*****************************************************************************
// グローバル変数
//*****************************************************************************

BLADE Blade[MAX_BLADE];					//弾のデータ

static VERTEX_2D g_PolygonVertex[TEXTURE_BLADE_MAX][4];	//頂点データ
static Texture_DATA g_Texture[TEXTURE_BLADE_MAX];			//テクスチャデータ


//所属
static enum Affiliation {
	PLAYER,
	ENEMY,
	Affiliation_MAX
};

void InitBlade()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int i = 0; i < MAX_BLADE; i++)
	{
		Blade[i].pos.x = 0;
		Blade[i].pos.y = 0;

		//有効フラグをOFFにする
		Blade[i].isEnable = false;
	}	


	//テクスチャデータの初期化
	for (int i = 0; i < TEXTURE_BLADE_MAX; i++)
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


void UninitBlade()
{
	for (int i = 0; i < TEXTURE_BLADE_MAX; i++)
	{
		UnLoadTextureDATA(&g_Texture[i]);
	}

}


void UpdateBlade()
{
	for (int i = 0; i < MAX_BLADE; i++)
	{
		//有効フラグがONじゃなければ何もしない
		if (Blade[i].isEnable == false)
			continue;

		Blade[i].State_time += 1.0f/120.0f;
		if (Blade[i].State_time>BLADE_APPEARTIME) {
			Blade[i].isEnable = false;
		}

		//弾が画面から出て行ってしまったら
		//有効フラグを落とす
		if (Blade[i].pos.y < 0)
			Blade[i].isEnable = false;
		//有効フラグを落とす
		if (Blade[i].pos.y > SCREEN_GAME_HEIGHT - BLADE_HEIGHT)
			Blade[i].isEnable = false;
		//有効フラグを落とす
		if (Blade[i].pos.x < 0)
			Blade[i].isEnable = false;
		//有効フラグを落とす
		if (Blade[i].pos.x > SCREEN_GAME_WIDTH - BLADE_WIDTH)
			Blade[i].isEnable = false;
	}
}
void DrawBlade()
{

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	for (int i = 0; i < MAX_BLADE; i++)
	{
		//有効フラグがONじゃなければ何もしない
		if (Blade[i].isEnable == false)
			continue;

		//一回転する角度計算は内積は向かない
		//※基礎角度（θ）を計算する
		float baseAngle;	//基礎角度
		baseAngle = atan2f(BLADE_HEIGHT, BLADE_WIDTH);

		//一定時間立つと消える処理
		switch (Blade[i].Affiliation)
		{
		case PLAYERS_BLADE:
			//頂点座標の設定
			//通常	
			MakeVertex(g_Texture[TEXTURE_BLADE].Vertex,
				D3DXVECTOR4(255, 255, 255, 255- Blade[i].State_time/BLADE_APPEARTIME*230));
			break;
		case ENEMYS_BLADE:
			//頂点座標の設定
			//赤色・・デキナイカラとりあえず半透明
			MakeVertex(g_Texture[TEXTURE_BLADE].Vertex, D3DXVECTOR4(255, 0, 0, 140));
			break;
		default:
			MakeVertex(g_Texture[TEXTURE_BLADE].Vertex, D3DXVECTOR4(255, 255, 255, 255));
			break;
		}

		//頂点座標セット
		SetVertex(g_Texture[TEXTURE_BLADE].Vertex
			, Blade[i].pos
			, BLADE_WIDTH
			, BLADE_HEIGHT
			, baseAngle
			,Blade[i].Rotation);

		//テクスチャー座標のセット
		SetTexture(g_Texture[TEXTURE_BLADE].Vertex,
			Blade[i].TextureDivide_x,
			Blade[i].TextureDivide_y,
			Blade[i].TextureType);

		// テクスチャの設定
		pDevice->SetTexture(0, g_Texture[TEXTURE_BLADE].pD3DTexture);
		// ポリゴンの描画
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_BLADE, g_Texture[TEXTURE_BLADE].Vertex, sizeof(VERTEX_2D));
		
	}
}

//有効フラグを渡す
bool GetIsEnableBlade(int index)
{
	return Blade[index].isEnable;
}


//ENEMYのGetter
BLADE* GetBlade() {
	return (&Blade[0]);
}

//弾の射出処理
void SetBlade(
	D3DXVECTOR3 pos,
	D3DXVECTOR3 velovity,
	float Rotaion,
	float speed,
	int affiliation)	//プレイヤーか敵か
{
	for (int i = 0; i < MAX_BLADE; i++) {
		//弾の配列から空きを探す
		//現在使っている領域だった場合は
		//何もしないでスルーする
		if (Blade[i].isEnable == true)
			continue;

		//テクスチャーをセット
		Blade[i].TextureDivide_x = 1;
		Blade[i].TextureDivide_y = 1;
		Blade[i].TextureType = 0;
		//発射する位置をセット
		Blade[i].pos.x = pos.x;
		Blade[i].pos.y = pos.y;

		//飛んでいく方向をセット
		Blade[i].dir = velovity;
		//移動方向にスピードを掛ける
		Blade[i].dir *= speed;

		//プレイヤーの場所に＋向きを足す
		Blade[i].pos += Blade[i].dir;

		//振る向きを入れる
		Blade[i].Rotation = Rotaion;

		//敵か味方の弾どちらか決める
		Blade[i].Affiliation = affiliation;

		//ステートを決める
		Blade[i].State = 0;
		Blade[i].State_time= 0.0f;

		//有効フラグをONにする
		Blade[i].isEnable = true;

		//弾を１つセットしたら終了する
		break;
	}
}


//以下関数はBladeの中のみ

