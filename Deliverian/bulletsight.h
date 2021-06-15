
//=============================================================================
//
// �e�̏��� [bulletsight.h]
//
//=============================================================================

#ifndef _BULLETSIGHT_H_
#define _BULLETSIGHT_H_

//BulletSight�\����
typedef struct
{
	D3DXVECTOR3	pos;			//�ʒu��񒆐S�_
	D3DXVECTOR3	dir;			//�ړ�����
	int	muki;			//����
	int	Affiliation;	//����
	bool			isEnable;		//�L���t���O
}BULLETSIGHT;



void InitBulletSight();
void UninitBulletSight();
void UpdateBulletSight();
void DrawBulletSight();
void BulletMove(D3DXVECTOR3 pos);

bool GetIsEnableBulletSight(int index);
BULLETSIGHT* GetBulletSight();

//�e�̎ˏo����
void SetBulletSight(D3DXVECTOR3 pos, D3DXVECTOR3 velocity);

#endif
