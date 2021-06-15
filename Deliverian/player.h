//=============================================================================
//
// プレイヤー処理 [Player.h]
// Author : 
//スコアやHPといったシステムもこちらに格納
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_


#define PLAYER_BLADE_BAIRITU		(2)// プレイヤーの剣の力の倍率

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);

//プレイヤー状態
enum PLAYER_STATE
{
	PLAYER_STATE_NORMAL,
	PLAYER_STATE_MUTEKI,
	PLAYER_STATE_MAX
};


//プレイヤー構造体
typedef struct
{
	D3DXVECTOR3	pos;	//位置情報:中心点
	float		Rotation;		//向き
	int		walkFrame;		//アニメーション切り替えウエイトのカウンタ
	int		walkPattern;	//アニメーションパターン
	D3DXVECTOR3 size;			//画面のサイズ
	int		Score;
	int		Hp;	
	int		Power;
	PLAYER_STATE State;
	float	State_time;		//ステートの持続時間
	bool	BulletReloadflg;		//ステートの持続時間
	float	BulletReload_time;		//ステートの持続時間
	bool	isEnable;
}PLAYER_DATA;

PLAYER_DATA *GetPlayer();
void PlusPlayerHp(int PlusHp);
void PlusPlayerScore(int PlusHp);
void ChangePlayerState(PLAYER_STATE targetstate);
#endif
