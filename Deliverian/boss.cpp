
#include "main.h"
#include "Func_texture.h"
#define _USE_MATH_DEFINES 
#include "math.h"
#include "boss.h"
#include "boss_AI.h"
#include "UI_Boss.h"


//*****************************************************************************
// CONST変数
//*****************************************************************************

//ボスの設定
const int c_Tex_Divide= 2;
const float BOSS_WIDTH = 160.0f;
const float BOSS_HEIGHT = 80.0f;
const float BOSS_DMGHIT_MUTEKITIME = 0.01f;// エネミーのダメージヒット時の無敵時間
const float BOSS_DMGHIT_TIME = 0.5f;	// エネミーのダメージヒット時の挙動時間


enum TextureType {
	NORMAL,
	LEFT,
	RIGHT,
	TYPE_MAX
};

const Texture_DATA c_InitTexture[B_MAX_ENEMYTYPE] =
{
	{
		(char *)"TEXTURE/Stg_main/Boss/fighter.tga"
		,NULL
		,NULL
		,D3DXVECTOR3(SCREEN_GAME_WIDTH / 2, SCREEN_GAME_HEIGHT / 4 * 3, 0.0f)	//ここでは使わない
		,BOSS_WIDTH
		,BOSS_HEIGHT
		,true
		,0
		,0
		,true
		,c_Tex_Divide
		,c_Tex_Divide
		,0
		,true
		,D3DXVECTOR4(255, 255, 255, 255)
	},
	{
		(char *)"TEXTURE/Stg_main/Boss/B_LASER.png"
		,NULL
		,NULL
		,D3DXVECTOR3(SCREEN_GAME_WIDTH / 2, SCREEN_GAME_HEIGHT / 4 * 3, 0.0f)	//ここでは使わない
		,BOSS_WIDTH
		,BOSS_HEIGHT
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
	{
		(char *)"TEXTURE/Stg_main/Boss/B_FINAL.png"
		,NULL
		,NULL
		,D3DXVECTOR3(SCREEN_GAME_WIDTH / 2, SCREEN_GAME_HEIGHT / 4 * 3, 0.0f)	//ここでは使わない
		,BOSS_WIDTH
		,BOSS_HEIGHT
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
static LPDIRECT3DTEXTURE9		g_pD3DTexture = NULL;		// テクスチャへのポインタ

static VERTEX_2D g_PolygonVertex[B_MAX_ENEMYTYPE][4];	//頂点データ
static Texture_DATA g_texture[B_MAX_ENEMYTYPE];
static ENEMY g_Boss;					//ボスデータ

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
static void EnemyDamageState(ENEMY* enemy);

//ボスの出現開始時間、出現場所、移動方向の設定配列
ENEMY tblBoss[B_MAX_ENEMYTYPE] = {
	{
		 D3DXVECTOR3(SCREEN_GAME_WIDTH / 2, -SCREEN_GAME_HEIGHT / 10, 0.0f)
		, D3DXVECTOR3(0,+1.0f,0) //移動方向
		,0 //向き(仮)
		,B_FIGHTER
		,c_Tex_Divide
		,c_Tex_Divide
		,NORMAL		//TEXTURE
		,D3DXVECTOR3(200.0f,100.0f,0)//SIZE
		,100	//Hp
		,1	//Power
		,20	//Power
		,ENEMY_STATE_NORMAL	//敵の状態
		,0					//状態経過時間	
		,BOSS_STATE_APPEAR1	//敵のAI
		,0					//AIの状態経過時間	
		,false
		,B_FIGHTER			//敵のタイプ
		,5					//弾の射出感覚
		,0
		,0
		,2.5f		//弾のスピード
		,0.0f		
		,0.0f		//移動角度
		,0.0f		//射出角度
		,false		//敵の無敵フラグ
		,0.0f		//敵の無敵時間
	}
	,
	{
		D3DXVECTOR3(SCREEN_GAME_WIDTH / 2, -SCREEN_GAME_HEIGHT / 10, 0.0f)
		, D3DXVECTOR3(0,+1.0f,0) //移動方向
		,0 //向き(仮)
		,B_LASER
		,NON_DIVIDE
		,NON_DIVIDE
		,NON_DIVIDE_TEXTURENUMBER
		,D3DXVECTOR3(100.0f,100.0f,0)//SIZE
		,100	//Hp
		,2	//Power
		,40	//Power
		,ENEMY_STATE_NORMAL	//敵の状態
		,0					//状態経過時間	
		,BOSS_STATE_APPEAR1	//敵のAI
		,0					//AIの状態経過時間	
		,false
		,B_LASER			//敵のタイプ
		,5					//弾の射出感覚
		,0
		,0
		,2.5f		//弾のスピード
		,0.0f
		,0.0f		//移動角度
		,0.0f		//射出角度
		,false		//敵の無敵フラグ
		,0.0f		//敵の無敵時間
	},
	{
		D3DXVECTOR3(SCREEN_GAME_WIDTH / 2, -SCREEN_GAME_HEIGHT / 10, 0.0f)
		, D3DXVECTOR3(0,+1.0f,0) //移動方向
		,0 //向き(仮)
		,B_FINAL
		,NON_DIVIDE
		,NON_DIVIDE
		,NON_DIVIDE_TEXTURENUMBER
		,D3DXVECTOR3(100.0f,100.0f,0)//SIZE
		,100	//Hp
		,1	//Power
		,100	//Power
		,ENEMY_STATE_NORMAL	//敵の状態
		,0					//状態経過時間	
		,BOSS_STATE_APPEAR1	//敵のAI
		,0					//AIの状態経過時間	
		,false
		,B_FINAL			//敵のタイプ
		,5					//弾の射出感覚
		,0
		,0
		,2.5f		//弾のスピード
		,0.0f
		,0.0f		//移動角度
		,0.0f		//射出角度
		,false		//敵の無敵フラグ
		,0.0f		//敵の無敵時間
	}
};

static VERTEX_2D g_Vertex[B_MAX_ENEMYTYPE][4];


void InitBoss()
{
	g_Boss = tblBoss[0];
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int i = 0; i < B_MAX_ENEMYTYPE; i++)
	{
		SetTextureDATA
		(
			pDevice,
			g_PolygonVertex[i],
			&g_texture[i],
			&c_InitTexture[i]
		);
	}
	
}


void UninitBoss()
{
	for (int i = 0; i < B_MAX_ENEMYTYPE; i++)
	{
		UnLoadTextureDATA(&g_texture[i]);
	}
}


void UpdateBoss()
{
	for (int i = 0; i < B_MAX_ENEMYTYPE; i++)
	{
		//有効フラグがONじゃなければ何もしない
		if (g_Boss.isEnable == false)
			continue;
		Boss_AI_Update(&g_Boss);

		//敵の状態により挙動の一時的な変更
		switch (g_Boss.State)
		{
		case ENEMY_STATE_NORMAL:
			break;
		case ENEMY_STATE_DAMAGE:
			EnemyDamageState(&g_Boss);
			break;
		default:
			break;
		}		
		//無敵時間を計測し、時間を超えたらOFFにする
		if (g_Boss.Enemy_Mutekiflg) {
			g_Boss.Muteki_time += 1.0f / 120.0f;
			if (g_Boss.Muteki_time>BOSS_DMGHIT_MUTEKITIME) {
				g_Boss.Muteki_time = 0;
				g_Boss.Enemy_Mutekiflg = false;
			}
		}

	}
}


void DrawBoss()
{

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int i = 0; i < B_MAX_ENEMYTYPE; i++)
	{
		//有効フラグがONじゃなければ何もしない
		if (g_Boss.isEnable == false)
			continue;
		//ENEMYデータをテクスチャーに格納する
		int textureType = g_Boss.int1;

		if (!g_texture[textureType].IsEnable)
			continue;

		g_texture[textureType].Pos = g_Boss.pos;
		g_texture[textureType].Angle = g_Boss.Rotation;
		g_texture[textureType].Size_x = g_Boss.size.x;
		g_texture[textureType].Size_y = g_Boss.size.y;

		DrawTextureDATA(
			pDevice,
			&g_texture[textureType]
		);
	}

}

void SetBoss(int BossType)
{
	g_Boss = tblBoss[BossType];

	g_Boss.pos.x = SCREEN_GAME_WIDTH/2;
	g_Boss.pos.y = -32.0f;

	//移動方向を決める
	g_Boss.dir.x = 0.0f;
	g_Boss.dir.y = 0.5f;
	//HP設定
	//BOSSの状態
	g_Boss.State = BOSS_STATE_APPEAR1;
	//有効化フラグをONにする
	g_Boss.isEnable = true;

	//lifeの出現をONにする
	Ui_Boss_SetTextureEnable();
	SetBossLifeData(g_Boss.Hp);
	SetBossDate(g_Boss);
}

//EMITTER使用版 ADD
void SetBoss(D3DXVECTOR3 pos, D3DXVECTOR3 dir,int BossType)
{
	if (g_Boss.isEnable == false)
	{
		//ランダムで表示位置を決める
		g_Boss.pos = pos;

		//移動方向を決める
		g_Boss.dir = dir;

		//HP設定
		g_Boss.Hp = 200;
		//有効化フラグをONにする
		g_Boss.isEnable = true;

	}
}


//有効フラグを渡す
bool GetIsEnableBoss()
{
	return g_Boss.isEnable;
}

/*↓この関数内でのみ使用*/
//BossのGetter
ENEMY* GetBoss() {
	return (&g_Boss);
}


void EnemyDamageState(ENEMY* enemy) {
	enemy->State_time += 1 / 60.0f;

	if (enemy->State_time > BOSS_DMGHIT_TIME)
	{
		enemy->State_time = 0;
		enemy->State = ENEMY_STATE_NORMAL;
	}
}