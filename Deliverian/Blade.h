
//=============================================================================
//
// 近接の処理 [Blade.h]
//
//=============================================================================

#ifndef _BLADE_H_
#define _BLADE_H_

#define BLADE_HEIGHT	(64)	//剣の横幅
#define BLADE_WIDTH	(64)	//剣の横幅
#define BLADE_LENGTH	(55)//剣の長さ
#define BLADE_ANGLE		(0.70f)//剣のふり幅

#define MAX_BLADE		50		//弾の最大数
#define NUM_BLADE		2		//弾の最大数

//Blade構造体
typedef struct
{
	D3DXVECTOR3	pos;			//位置情報
	D3DXVECTOR3	dir;			//移動方向
	float	Rotation;		//向き
	int TextureDivide_x;		// アニメパターンのテクスチャ内分割数（X)
	int TextureDivide_y;		// アニメパターンのテクスチャ内分割数（Y)
	int TextureType;			//テクチャーのタイプ
	int	Affiliation;	//所属
	int State;					//状態
	float State_time;			//状態経過時間	

	bool			isEnable;		//有効フラグ
}BLADE;

enum AFFILIATIONofBLADE
{
	PLAYERS_BLADE,
	ENEMYS_BLADE,
	AFFILIATION_BLADE_MAX
};

void InitBlade();
void UninitBlade();
void UpdateBlade();
void DrawBlade();

bool GetIsEnableBlade(int index);
BLADE* GetBlade();

//弾の射出処理
void SetBlade(D3DXVECTOR3 pos, D3DXVECTOR3 velocity, float Rotaion, float speed, int affiliation);

#endif
