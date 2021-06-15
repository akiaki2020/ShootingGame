//=============================================================================
//
// プレイヤー処理 [Enemy.h]
// Author : 
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_


#define MAX_ENEMY		100		//敵の最大数
#define NUM_ENEMY		2		//


//エネミー構造体
typedef struct
{
	D3DXVECTOR3	pos;			//位置情報(中心点にすること)
	D3DXVECTOR3	dir;			//移動方向
	float		Rotation;		//向き
	int AI_type;					//敵のタイプ(主にAI)
	int TextureDivide_x;		// アニメパターンのテクスチャ内分割数（X)
	int TextureDivide_y;		// アニメパターンのテクスチャ内分割数（Y)
	int TextureDivide_Type;		//テクチャーの分割時の何枚目か
	D3DXVECTOR3 size;			//画面のサイズ
	int Hp;
	int	Power;
	int	  Score;				//撃破時の加算スコア
	int State;					//状態
	float State_time;			//状態経過時間	
	int AI_State;				//AIの状態
	float	AI_State_time;		//AIの状態経過時間	
	bool	isEnable;		//有効フラグ
	int	  int1;				//テクスチャータイプ	
	int	  int2;				//BOSSはbulletCountとして扱う	
	int	  int3;
	int	  int4;
	float BulletSpeed;			//弾のスピード
	float flt2;					
	float flt3;					//3変数　BOSSは移動角度と扱う
	float flt4;					//4変数　BOSSは射出角度と扱う
	bool	Enemy_Mutekiflg;	//敵の無敵フラグ
	float	Muteki_time;		//敵の無敵時間
	D3DXVECTOR3	EffectPos;		//エフェクト時の移動
}ENEMY;

//敵のタイプ
enum EnemyType {
	FIGHTER,
	SHOT_FIGHTER,
	DAKOU_FIGHTER,
	BIG_FIGHTER,
	GO_FIGHTER,
	MAX_ENEMYTYPE
};

//敵の状態
enum ENEMY_STATE
{
	ENEMY_STATE_NORMAL,
	ENEMY_STATE_DAMAGE,
	ENEMY_STATE_MAX
};

void InitEnemy();
void UninitEnemy();
void UpdateEnemy();
void DrawEnemy();

void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 dir,int EnemyType);
ENEMY& GetEnemyTbl(int index);

bool GetIsEnableEnemy(int index);
ENEMY* GetEnemy();

void EnemyFireBullet(ENEMY* enemy);
void PlusEnemyHp(ENEMY* enemy, int PlusHp);
void ChangeEnemyState(ENEMY* enemy, int targetstate);
void SetBossDate(ENEMY& enemy);


#endif
