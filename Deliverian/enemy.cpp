

#include "main.h"
#include "Func_texture.h"
#include "enemy.h"
#include "Enemy_Ai.h"
#include "player.h"
#include "Sound.h"
#include "bullet.h"
#include "UI_Boss.h"
#include "explosion.h"
#define _USE_MATH_DEFINES 
#include "math.h"

//*****************************************************************************
// CONST変数
//*****************************************************************************


#define WALK_WAIT_FRAME		10		//アニメーション切り替えウエイト
#define WALK_PATTERN_MAX	3		//アニメーションパターン数
#define DISAPPEAR_RANGE		200		//敵の消失範囲
#define ENEMY_DMGHIT_TIME	(0.5)// エネミーのダメージヒット時の時間
#define ENEMY_DMGHIT_MUTEKITIME	(0.2)// エネミーのダメージヒット時の無敵時間

const static Texture_DATA c_InitTexture[] =
{
	{
		(char *)"TEXTURE/Stg_main/Enemy/darkgrey_02.png"
		,NULL
	,NULL
	,D3DXVECTOR3(SCREEN_GAME_WIDTH / 2, SCREEN_GAME_HEIGHT / 4 * 3, 0.0f)	//ここでは使わない
	,32
	,32
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
		(char *)"TEXTURE/Stg_main/Enemy/darkgrey_01.png"
		,NULL
	,NULL
	,D3DXVECTOR3(SCREEN_GAME_WIDTH / 2, SCREEN_GAME_HEIGHT / 4 * 3, 0.0f)
	,64
	,64
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
		(char *)"TEXTURE/Stg_main/Enemy/9.png"
		,NULL
	,NULL
	,D3DXVECTOR3(SCREEN_GAME_WIDTH / 2, SCREEN_GAME_HEIGHT / 4 * 3, 0.0f)
	,64
	,64
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
// プロトタイプ宣言
//*****************************************************************************
void DieEnemy(ENEMY* enemy);
void EnemyDamageState(ENEMY* enemy);
void BreEnemyPos(ENEMY* enemy, int EffectOnOff);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
static ENEMY g_Enemy[MAX_ENEMY];					//エネミーデータ
enum TextureType {
	NORMAL,
	LEFT,
	RIGHT,
	TYPE_MAX
};
enum
{
	TEXTURE_ENEMY_FIGHTER,		
	TEXTURE_ENEMY_SHOT_FIGHTER,	
	TEXTURE_ENEMY_DAKOU_FIGHTER,
	TEXTURE_ENEMY_MAX,
};
static VERTEX_2D g_PolygonVertex[TEXTURE_ENEMY_MAX][4];//頂点データ
static Texture_DATA g_Texture[TEXTURE_ENEMY_MAX];

static ENEMY* g_Boss;	//参照用

//敵の出現開始時間、出現場所、移動方向の設定配列
ENEMY tblEnemy[MAX_ENEMYTYPE] = {
	//Fighter
	//場所				,移動方向				向き	
	{ D3DXVECTOR3( 0,0,0 ), D3DXVECTOR3(0,0,0),0.0f
	,FIGHTER
	,2,2,NORMAL		//TEXTURE
	,D3DXVECTOR3(40.0f,40.0f,0)//SIZE
	,3	//Hp
	,1	//Power
	,1	//Score
	,ENEMY_STATE_NORMAL	//敵の状態
	,0	//ステート時間
	,GO_DIRECT			//敵のAI
	,0	//ステート時間
	,false
	,TEXTURE_ENEMY_FIGHTER	//敵のタイプ
	,0
	,0
	,0
	,2.5f		//弾のスピード
	,0.0f
	,0.0f
	,0.0f
	,false	//敵の無敵フラグ
	,0.0f	//敵の無敵時間
	},
	//SHOT_FIGHTER
	{ D3DXVECTOR3( 0,0,0 ), D3DXVECTOR3(0,0,0),0.0f
	,SHOT_FIGHTER
	,2,2,NORMAL		//TEXTURE
	,D3DXVECTOR3(40.0f,40.0f,0)//SIZE
	,3	//Hp
	,1	//Power
	,2	//Score
	,ENEMY_STATE_NORMAL	//敵の状態
	,0	//ステート時間
	,GO_DIRECT			//敵のAI
	,0	//ステート時間
	,false
	,TEXTURE_ENEMY_SHOT_FIGHTER
	,0
	,0
	,0
	,2.5f		//弾のスピード
	,0.0f
	,0.0f
	,0.0f	
	,false	//敵の無敵フラグ
	,0.0f	//敵の無敵時間
	},
	//DAKOU_FIGHTER
	{ D3DXVECTOR3(0,0,0), D3DXVECTOR3(0,0,0),0.0f
	,DAKOU_FIGHTER
	,2,2,NORMAL		//TEXTURE
	,D3DXVECTOR3(64.0f,64.0f,0)//SIZE
	,3	//Hp
	,1	//Power
	,4	//Score
	,ENEMY_STATE_NORMAL	//敵の状態
	,0	//ステート時間
	,GO_DIRECT			//敵のAI
	,0	//ステート時間
	,false
	,TEXTURE_ENEMY_DAKOU_FIGHTER
	,0
	,0
	,0
	,2.5f		//弾のスピード
	,0.0f
	,0.0f
	,0.0f
	,false	//敵の無敵フラグ
	,0.0f	//敵の無敵時間
	},
	//BIG_FIGHTER
	{ D3DXVECTOR3(0,0,0), D3DXVECTOR3(0,0,0),0.0f
	,BIG_FIGHTER
	,2,2,NORMAL		//TEXTURE
	,D3DXVECTOR3(100.0f,100.0f,0)//SIZE
	,4	//Hp
	,2	//Power
	,5	//Score
	,ENEMY_STATE_NORMAL	//敵の状態
	,0	//ステート時間
	,GO_DIRECT			//敵のAI
	,0	//ステート時間
	,false
	,TEXTURE_ENEMY_FIGHTER	//敵のタイプ
	,0
	,0
	,0
	,2.5f		//弾のスピード
	,0.0f
	,0.0f
	,0.0f
	,false	//敵の無敵フラグ
	,0.0f	//敵の無敵時間
	},
	//GO__FIGHTER
	{ D3DXVECTOR3(0,0,0), D3DXVECTOR3(0,0,0),0.0f
	,GO_FIGHTER
	,2,2,NORMAL		//TEXTURE
	,D3DXVECTOR3(40.0f,40.0f,0)//SIZE
	,3	//Hp
	,1	//Power
	,1	//Score
	,ENEMY_STATE_NORMAL	//敵の状態
	,0	//ステート時間
	,GO_DIRECT			//敵のAI
	,0	//ステート時間
	,false
	,TEXTURE_ENEMY_FIGHTER	//敵のタイプ
	,0
	,0
	,0
	,2.5f		//弾のスピード
	,0.0f
	,0.0f
	,0.0f
	,false	//敵の無敵フラグ
	,0.0f	//敵の無敵時間
	},
};

void InitEnemy()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//シード値の設定　※シード値には現在時刻のミリSecを使用
	//g_rnd.SetSeed(nn::fnd::DateTime::GetNow().GetMilliSecond());
	for (int i = 0; i < MAX_ENEMY; i++)
	{
		////有効フラグをOFFする
		g_Enemy[i].isEnable = false;
		//すべてFighter型にする
		g_Enemy[i] = tblEnemy[0];

	}

	//テクスチャデータの初期化
	for (int i = 0; i < TEXTURE_ENEMY_MAX; i++)
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


void UninitEnemy()
{
	for (int i = 0; i < TEXTURE_ENEMY_MAX; i++)
	{
		UnLoadTextureDATA(&g_Texture[i]);
	}
}


void UpdateEnemy()
{
	for (int i = 0; i < MAX_ENEMY; i++)
	{
		//有効フラグがONじゃなければ何もしない
		if (g_Enemy[i].isEnable == false)
			continue;

		//Enemy_Aiから取得
		Enemy_AI_Update(&g_Enemy[i]);


		//敵が画面外＋設定範囲から出て行ってしまったら
		//有効フラグを落とす
		if (g_Enemy[i].pos.y < 0- DISAPPEAR_RANGE)
			g_Enemy[i].isEnable = false;
		//有効フラグを落とす
		if (g_Enemy[i].pos.y > SCREEN_HEIGHT+ DISAPPEAR_RANGE)
			g_Enemy[i].isEnable = false;
		//有効フラグを落とす
		if (g_Enemy[i].pos.x < 0- DISAPPEAR_RANGE)
			g_Enemy[i].isEnable = false;
		//有効フラグを落とす
		if (g_Enemy[i].pos.x > SCREEN_WIDTH + DISAPPEAR_RANGE)
			g_Enemy[i].isEnable = false;

		//敵の状態により挙動の一時的な変更
		switch (g_Enemy[i].State)
		{
		case ENEMY_STATE_NORMAL:
			break;
		case ENEMY_STATE_DAMAGE:
			EnemyDamageState(&g_Enemy[i]);
			break;
		default:
			break;
		}
		g_Enemy[i].pos = g_Enemy[i].pos + g_Enemy[i].EffectPos;

		//無敵時間を計測し、時間を超えたらOFFにする
		if (g_Enemy[i].Enemy_Mutekiflg) {
			g_Enemy[i].Muteki_time += 1.0f / 120.0f;
			if (g_Enemy[i].Muteki_time>ENEMY_DMGHIT_MUTEKITIME) {
				g_Enemy[i].Muteki_time = 0;
				g_Enemy[i].Enemy_Mutekiflg = false;
			}
		}

	}
}


void DrawEnemy()
{

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int i = 0; i < MAX_ENEMY; i++)
	{
		//有効フラグがONじゃなければ何もしない
		if (g_Enemy[i].isEnable == false)
			continue;

		//ENEMYデータをテクスチャーに格納する
		int textureType = g_Enemy[i].int1;
		g_Texture[textureType].Pos = g_Enemy[i].pos;
		g_Texture[textureType].Angle = g_Enemy[i].Rotation;
		g_Texture[textureType].Size_x = g_Enemy[i].size.x;
		g_Texture[textureType].Size_y = g_Enemy[i].size.y;

		DrawTextureDATA(
			pDevice,
			&g_Texture[textureType]
		);
	}
}

void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 dir, int EnemyType) 
{
	for (int i = 0; i < MAX_ENEMY; i++)
	{
		if (g_Enemy[i].isEnable == false)
		{
			//敵のタイプを格納する
			g_Enemy[i]= tblEnemy[EnemyType];

			g_Enemy[i].AI_State = ENEMY_STATE_NORMAL;
			g_Enemy[i].State = GO_DIRECT;
			//表示位置を決める
			g_Enemy[i].pos = pos;
			//移動方向を決める
			g_Enemy[i].dir = dir;
			//有効化フラグをONにする
			g_Enemy[i].isEnable = true;
			g_Enemy[i].Muteki_time = 0;
			g_Enemy[i].Enemy_Mutekiflg = false;
			//１匹セットしたら終了する
			break;
		}
	}
}

//有効フラグを渡す
bool GetIsEnableEnemy(int index)
{
	return g_Enemy[index].isEnable;
}

//ENEMYtblのGetter
ENEMY& GetEnemyTbl(int index) {
	return tblEnemy[index];
}


//ENEMYのGetter
ENEMY* GetEnemy() {
	return (&g_Enemy[0]);
}

void EnemyFireBullet(ENEMY* enemy) {

	D3DXVECTOR3 tempdir= D3DXVECTOR3(0,0,0);
	//移動方向を入れる下のWAIT判定のため
	tempdir = D3DXVECTOR3(sinf(enemy->Rotation), -cosf(enemy->Rotation), 0);
	SetBullet(enemy->pos, tempdir, enemy->BulletSpeed,ENEMYS_BULLET);
}

// EnemyのHpを変える処理
void PlusEnemyHp(ENEMY* enemy,int PlusHp) {

	//無敵状態ならHPは減らない
	if (enemy->Enemy_Mutekiflg&& PlusHp<0) {
		return;
	}
	//ダメージなら
	if (PlusHp<0)PlaySound(SOUND_LABEL_SE_Enemyhit000);

	enemy->Hp += PlusHp;
	enemy->Enemy_Mutekiflg = true;
	
	//Bossならライフ反映
	if (g_Boss == enemy)
	{
		UpdateBossLifeData(enemy->Hp);
	}

	//Hpが0になったとき
	if (enemy->Hp <= 0) 
	{
		DieEnemy(enemy);
	}
}

// Enemyの状態を変える処理
void ChangeEnemyState(ENEMY* enemy, int targetstate) {

	if (enemy->isEnable == false)
	{
		return;
	}
	enemy->State = targetstate;
}

void SetBossDate(ENEMY& enemy) 
{
	g_Boss = &enemy;
}

void DieEnemy(ENEMY* enemy) {
	PlaySound(SOUND_LABEL_SE_EnemyDie000);
	SetExplosion(enemy->pos);
	PlusPlayerScore(enemy->Score);
	enemy->isEnable = false;
}

void EnemyDamageState(ENEMY* enemy) {
	enemy->State_time += 1 / 60.0f;

	if (int(enemy->State_time * 1000) % 4 == 0) {
		BreEnemyPos(enemy,0);
	}

	if (int(enemy->State_time * 1000) % 4 == 2) {
		BreEnemyPos(enemy, 1);
	}

	if (enemy->State_time > ENEMY_DMGHIT_TIME)
	{
		BreEnemyPos(enemy, 2);
		enemy->State_time = 0;
		enemy->State = ENEMY_STATE_NORMAL;
	}
}

void BreEnemyPos(ENEMY* enemy,int EffectOnOff) {

	switch (EffectOnOff)
	{
	case 0:
		//プレイヤーが表示されている時
		enemy->EffectPos.x = cosf(rand())* -5;
		enemy->EffectPos.y = sinf(rand())* -5;

		break;
	case 1:
		enemy->EffectPos.x = cosf(rand())* 5;
		enemy->EffectPos.y = sinf(rand())* 5;

		break;

	case 2:
		//プレイヤーを表示する時
		enemy->EffectPos.x = 0.0f;
		enemy->EffectPos.y=  0.0f;
		break;
	default:
		break;

	}
}
