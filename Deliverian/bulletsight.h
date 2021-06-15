
//=============================================================================
//
// 弾の処理 [bulletsight.h]
//
//=============================================================================

#ifndef _BULLETSIGHT_H_
#define _BULLETSIGHT_H_

//BulletSight構造体
typedef struct
{
	D3DXVECTOR3	pos;			//位置情報中心点
	D3DXVECTOR3	dir;			//移動方向
	int	muki;			//向き
	int	Affiliation;	//所属
	bool			isEnable;		//有効フラグ
}BULLETSIGHT;



void InitBulletSight();
void UninitBulletSight();
void UpdateBulletSight();
void DrawBulletSight();
void BulletMove(D3DXVECTOR3 pos);

bool GetIsEnableBulletSight(int index);
BULLETSIGHT* GetBulletSight();

//弾の射出処理
void SetBulletSight(D3DXVECTOR3 pos, D3DXVECTOR3 velocity);

#endif
