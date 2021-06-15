#pragma once


#define ENEMY_BULLET_WIDTH	(32)	//敵弾の横幅
#define ENEMY_BULLET_HEIGHT	(32)	//敵弾の横幅

#define ENEMY_MAX_BULLET		100		//敵弾の最大数

#define ENEMY_BULLET_SPPED 2;

//エネミー構造体
typedef struct
{
	nn::math::VEC2	pos;			//位置情報
	nn::math::VEC2	dir;			//移動方向
	int				muki;			//向き
	int				color;
	bool			isEnable;		//有効フラグ
}ENEMY_BULLET;

void InitEnemy_Bullet();
void UninitEnemy_Bullet();
void UpdateEnemy_Bullet();
void DrawEnemy_Bullet();

int* GET_ENEMYBULLET_absorb_check();
void DestroyEnemyBULLET(int);

bool GetIsEnableEnemy_Bullet(int index);
ENEMY_BULLET* GetEnemy_Bullet();

//弾の射出処理
void SetEnemy_Bullet(nn::math::VEC2 player_pos, int muki,int color);
