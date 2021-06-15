#pragma once

#define LASER_WIDTH	(32)	//敵弾の横幅
#define LASER_HEIGHT	(32)	//敵弾の横幅
#define MAX_LASER		100		//敵弾の最大数
#define LASER_SPPED 2;

//エネミー構造体
typedef struct
{
	D3DXVECTOR3	pos;			//位置情報(終点)
	D3DXVECTOR3	dir;			//移動方向
	D3DXVECTOR3	s_pos;			//始点
	float		Rotation;		//向き
	//先生はCAPSEL変数を入れて当たり判定とした
	int texType;				//テクスチャーのタイプ
	float	Futosa;					//太さ
	float	Nagasa;					//太さ
	int				Affiliation;	//敵か自機
	int				color;			
	int				power;			//power
	bool			isEnd;		//レーザー発射終了フラグ
	bool			isEnable;		//有効フラグ
}LASER;

//ボスのタイプ
enum LASER_TYPE {
	LASER1,
	MAX_LASER_TYPE
};


void InitEnemyLaser();
void UninitEnemyLaser();
void UpdateEnemyLaser();
void DrawEnemyLaser();

void DestroyEnemyLaser(int);

void EndEnemyLaser(int);


bool GetIsEnableEnemyLaser(int index);
LASER* GetEnemyLaser();

//弾の射出処理
LASER* SetEnemyLaser(D3DXVECTOR3 pos, int affiliation,int color
	, float Futosa, float nagasa, int power, D3DXVECTOR3 dir);
