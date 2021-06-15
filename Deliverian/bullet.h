
//=============================================================================
//
// 弾の処理 [buleet.h]
//
//=============================================================================

#ifndef _BULLET_H_
#define _BULLET_H_

#define TEXTURE_GAME_Bullet00	_T("TEXTURE/bullet.tga")	// サンプル用画像
#define BULLET_WIDTH	(32)	//敵の横幅
#define BULLET_HEIGHT	(32)	//敵の横幅

//玉用
#define TEXTURE_PATTERN_BULLET_X	(1)	// アニメパターンのテクスチャ内分割数（X)
#define TEXTURE_PATTERN_BULLET_Y	(1)	// アニメパターンのテクスチャ内分割数（Y)

#define MAX_BULLET		1000		//弾の最大数
#define NUM_BULLET		2		//弾の最大数


//Bullet構造体
typedef struct
{
	D3DXVECTOR3	pos;			//位置情報　中心点
	D3DXVECTOR3	dir;			//移動方向
	float	Rotation;			//向き

	D3DXVECTOR3 size;			//画面のサイズ
	int	Affiliation;			//所属
	int power;					//威力
	int type;					//テクスチャータイプ
	bool			isEnable;		//有効フラグ
}BULLET;

enum AFFILIATIONofBULLET
{
	PLAYERS_BULLET,
	ENEMYS_BULLET,
	AFFILIATION_MAX
};

void InitBullet();
void UninitBullet();
void UpdateBullet();
void DrawBullet();

bool GetIsEnableBullet(int index);
BULLET* GetBullet();

//弾の射出処理
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 velocity,float speed, int affiliation);
//弾の射出処理
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 velocity, float speed, int affiliation,int power);

#endif
