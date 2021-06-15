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

	float flame;//出現フレーム
	D3DXVECTOR3 pos;//発生位置
	D3DXVECTOR3 dir;//移動方向
	int EnemyType;//敵の種類
	int EmitType;//出現方法

}ENEMYEMIT_T;



//void InitEnemyEmitter();
//void UpdateEnemyEmitter();
void EnemyEmitter(D3DXVECTOR3 pos, D3DXVECTOR3 dir, int EnemyType, D3DXVECTOR3 size, int Emitt_type);
void EnemyEmitter(D3DXVECTOR3 pos, D3DXVECTOR3 dir, int EnemyType, int Emitt_type);
