#pragma once

enum EMITT_TYPE {
	ONE,
	DOUBLE_HOLIZNE,
	DOUBLE_VERTICAL,
	THREE_HOLIZNE,
	THREE_VERTICAL,
	THREE_TRIANGLE,
	THREE_TRIANGLE_R,
	FOUR_HOLIZNE,
	FOUR_VERTICAL,
	PENTA,
	CIRCLE,
	MAX_EMITT_TYPE
};

typedef struct
{

	float flame;//�o���t���[��
	D3DXVECTOR3 pos;//�����ʒu
	D3DXVECTOR3 dir;//�ړ�����
	int EnemyType;//�G�̎��
	int EmitType;//�o�����@

}ENEMYEMIT_T;



//void InitEnemyEmitter();
//void UpdateEnemyEmitter();
void EnemyEmitter(D3DXVECTOR3 pos, D3DXVECTOR3 dir, int EnemyType, D3DXVECTOR3 size, int Emitt_type);
void EnemyEmitter(D3DXVECTOR3 pos, D3DXVECTOR3 dir, int EnemyType, int Emitt_type);
