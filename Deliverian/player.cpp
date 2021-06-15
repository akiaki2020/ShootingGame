//=============================================================================
//
// プレイヤー処理 [Player.cpp]
// Author : 秋本
//スコアやHPといったシステムもこちらに格納
//=============================================================================
#include "main.h"
#include "input.h"
#include "player.h"
#include "Sound.h"
#include "Func_texture.h"
#include "game.h"
#include "bullet.h"
#include "bulletsight.h"
#include "Blade.h"
#include "UI_Life.h"
#define _USE_MATH_DEFINES 
#include "math.h"
#ifdef _DEBUG
#include "scene.h"
#include "fade.h"
#endif


//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_PLAYER_SIZE_X	(40)	// テクスチャサイズ
#define TEXTURE_PLAYER_SIZE_Y	(40)	// 
#define PLAYER_SIZE_X	(24)	// プレイヤーサイズ
#define PLAYER_SIZE_Y	(24)	// プレイヤーサイズ
//戦闘機用
#define TEXTURE_PATTERN_DIVIDE_X	1	// アニメパターンのテクスチャ内分割数（X)
#define TEXTURE_PATTERN_DIVIDE_Y	1	// アニメパターンのテクスチャ内分割数（Y)

#define ANIM_PATTERN_NUM			(3)	// アニメーションパターン数

#define TIME_ANIMATION				(4)	// アニメーションの切り替わるカウント

#define PLAYER_FIRST_HP				3// プレイヤーの最初のHP
#define PLAYER_FIRST_SCORE			0// プレイヤーの最初のSCORE
#define PLAYER_FIRST_POWER			2// プレイヤーの最初のPOWER
#define PLAYER_BLADE_RELOADTIME		(1)// プレイヤーの剣の力の倍率

#define PLAYER_DMGHIT_MUTEKITIME	1// プレイヤーのダメージヒット時の無敵時間


#define	RADIUS_MIN				(50.0f)							// ポリゴンの半径最小値
#define	RADIUS_MAX				(300.0f)						// ポリゴンの半径最大値
#define	VALUE_ROTATION			(D3DX_PI * 0.01f)				// ポリゴンの回転量
#define	VALUE_SCALE				(2.0f)							// ポリゴンのスケール変化量

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void DiePlayer(void);					//プレイヤーのHPが亡くなった処理
void PlayerMutekiState(void);			//プレイヤーが無敵時の処理
void TenmetuPlayerTexture(int EffectOnOff);		//プレイヤーの点滅処理

//*****************************************************************************
// グローバル変数
//*****************************************************************************
static LPDIRECT3DTEXTURE9		g_pD3DTexture = NULL;		// テクスチャへのポインタ

static VERTEX_2D				g_vertexWk[NUM_VERTEX];		// 頂点情報格納ワーク

PLAYER_DATA player;							//プレイヤーデータ

int						g_nCountAnim;						// アニメーションカウント
int						g_nPatternAnim;						// アニメーションパターンナンバー

enum
{
	TEXTURE_PLAYER,		// title
	TEXTURE_TURRET,		// result
	TEXTURE_MAX,
};

static VERTEX_2D g_ResultVertex[TEXTURE_MAX][4];

static Texture_DATA g_Result_InitTexture[] =
{
	{
	(char *)"TEXTURE/Stg_main/Player/tankbase_04.png"
	//(char *)"TEXTURE/Stg_main/Shoot/bullet2.tga"
	,NULL
	,NULL
	,D3DXVECTOR3(SCREEN_GAME_WIDTH / 2, SCREEN_GAME_HEIGHT / 4 * 3, 0.0f)
	,TEXTURE_PLAYER_SIZE_X
	,TEXTURE_PLAYER_SIZE_Y
	,true
	,0
	,0
	,false
	,NON_DIVIDE
	,NON_DIVIDE
	,NON_DIVIDE_TEXTURENUMBER
	,false
	,D3DXVECTOR4(255, 255, 255, 255)
	},

	{
	(char *)"TEXTURE/Stg_main/Player/tankcannon-01a.png"
	,NULL
	,NULL
	,D3DXVECTOR3(SCREEN_GAME_WIDTH / 2, SCREEN_GAME_HEIGHT / 4 * 3, 0.0f)
	,TEXTURE_PLAYER_SIZE_X
	,TEXTURE_PLAYER_SIZE_Y
	,true
	,0
	,0
	,true
	,NON_DIVIDE
	,NON_DIVIDE
	,NON_DIVIDE_TEXTURENUMBER
	,false
	,D3DXVECTOR4(255, 255, 255, 255)
	},
};


static Texture_DATA g_Result_texture[TEXTURE_MAX];

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		//初期化
		g_Result_texture[i] =
			g_Result_InitTexture[i];
		
		//初期角度の格納
		g_Result_texture[i].BaseAngle =
			atan2f(g_Result_texture[i].Size_y, g_Result_texture[i].Size_x);

		//頂点座標の設定
		MakeVertex(g_ResultVertex[i]);

		SetTexture(g_ResultVertex[i],
			TEXTURE_PATTERN_DIVIDE_X,
			TEXTURE_PATTERN_DIVIDE_Y);

		//場所決定
		SetVertex(g_ResultVertex[i],
			g_Result_texture[i].Pos,
			g_Result_texture[i].Size_x,
			g_Result_texture[i].Size_y);

		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,		// デバイスのポインタ
			g_Result_texture[i].Path,				// ファイルの名前
			&g_Result_texture[i].pD3DTexture);					// 読み込むメモリのポインタ
		//頂点座標情報を格納
		g_Result_texture[i].Vertex = g_ResultVertex[i];

	}

	player.pos = D3DXVECTOR3(SCREEN_GAME_WIDTH / 2, 
		SCREEN_GAME_HEIGHT / 4 * 3, 0.0f);

	player.Rotation = 0;
	player.size = D3DXVECTOR3(PLAYER_SIZE_X,
		PLAYER_SIZE_Y, 0.0f);
	player.Score = PLAYER_FIRST_SCORE;
	player.Hp = PLAYER_FIRST_HP;
	player.Power = PLAYER_FIRST_POWER;
	player.State = PLAYER_STATE_NORMAL;
	player.State_time = 0;
	player.BulletReloadflg = false;
	player.BulletReload_time = 0;
	player.isEnable = true;

	g_nCountAnim = 0;
	g_nPatternAnim = 0;

	Ui_Life_Set(player.Hp);
	Ui_Score_Set(player.Score);
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPlayer(void)
{
	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		if (g_Result_texture[i].pD3DTexture != NULL)
		{	// テクスチャの開放
			g_Result_texture[i].pD3DTexture->Release();
			g_Result_texture[i].pD3DTexture = NULL;
		}
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdatePlayer(void)
{
	// アニメーション
	g_nCountAnim++;

	//マウスの動く値
	D3DXVECTOR3	Mouse_Move;
	Mouse_Move = D3DXVECTOR3(0,0,0);

	//一時的な動く値
	D3DXVECTOR3	Move_pos;
	Move_pos = D3DXVECTOR3(0, 0, 0);

	//照準から向きを取得
	D3DXVECTOR3 dirBulletSightTemp;
	//float tempRotaion;
	BULLETSIGHT *BulletSightTemp;
	BulletSightTemp = GetBulletSight();
	dirBulletSightTemp = BulletSightTemp->pos - player.pos;
	dirBulletSightTemp = Vec3Normalize(&dirBulletSightTemp);
	player.Rotation = atan2f(dirBulletSightTemp.y, dirBulletSightTemp.x) + (M_PI / 2);


	// アニメーションWaitチェック
	if( ( g_nCountAnim % TIME_ANIMATION ) == 0 )
	{
		// パターンの切り替え
		g_nPatternAnim = ( g_nPatternAnim + 1 ) % ANIM_PATTERN_NUM;

		// テクスチャ座標を設定
		//SetTexturePlayer(g_nPatternAnim, player.charaType, player.muki);
	}

	//カーソルキーの↑が入力された時の処理
	if (GetKeyboardPress(DIK_UP) || GetKeyboardPress(DIK_W))
	{
		Move_pos.y -= 1.0f;
		//player.muki = UP;

	}
	//カーソルキーの↓が入力された時の処理
	if (GetKeyboardPress(DIK_DOWN) || GetKeyboardPress(DIK_S))
	{
		Move_pos.y += 1.0f;
		//player.muki = DOWN;
	
	}
	//カーソルキーの→が入力された時の処理
	if (GetKeyboardPress(DIK_RIGHT) || GetKeyboardPress(DIK_D))
	{
		Move_pos.x += 1.0f;
		//player.muki = RIGHT;

	}
	//カーソルキーの←が入力された時の処理
	if (GetKeyboardPress(DIK_LEFT) || GetKeyboardPress(DIK_A))
	{
		Move_pos.x -= 1.0f;
		//player.muki = LEFT;

	}


	//場外判定
	//有効フラグを落とす
	//↑判定
	if (player.pos.y < 0+ TEXTURE_PLAYER_SIZE_Y / 2 && Move_pos.y < 0)
	{
		Move_pos.y = 0;
		player.pos.y = 0 + TEXTURE_PLAYER_SIZE_Y / 2;
	}
	//有効フラグを落とす
	if (player.pos.y > SCREEN_GAME_HEIGHT- TEXTURE_PLAYER_SIZE_Y / 2 && Move_pos.y>0)
	{
		Move_pos.y = 0;
		player.pos.y = SCREEN_GAME_HEIGHT - TEXTURE_PLAYER_SIZE_Y / 2;
	}
	//有効フラグを落とす
	if (player.pos.x < 0+ TEXTURE_PLAYER_SIZE_X / 2 && Move_pos.x < 0)
	{
		Move_pos.x = 0;
		player.pos.x = 0 + TEXTURE_PLAYER_SIZE_X / 2;
	}
	//有効フラグを落とす
	if (player.pos.x > SCREEN_GAME_WIDTH- TEXTURE_PLAYER_SIZE_X / 2 && Move_pos.x>0)
	{
		Move_pos.x = 0;
		player.pos.x = SCREEN_GAME_WIDTH - TEXTURE_PLAYER_SIZE_X / 2;
	}

	player.pos += Move_pos;




#ifdef _DEBUG
	//test用
	if (GetKeyboardPress(DIK_Z))
	{
		Fade(SCENE_INDEX_RESULT);
	}
#endif


	//標準の移動
	if (GetMouseX !=0) {
		Mouse_Move.x = (float)GetMouseX();
	}

	if (GetMouseX != 0) {
		Mouse_Move.y = (float)GetMouseY();
	}
	BulletMove(Mouse_Move);
	   
	//玉の射出
	if (IsMouseLeftTriggered()) {
		PlaySound(SOUND_LABEL_SE_shot000);
		SetBullet(player.pos, dirBulletSightTemp,5.0f, PLAYERS_BULLET);
	}

	//近接
	if (player.BulletReloadflg)
	{
		player.BulletReload_time += 1.0f / 120.0f;
		if (player.BulletReload_time>= PLAYER_BLADE_RELOADTIME)
		{
			player.BulletReload_time = 0.0f;
			player.BulletReloadflg = false;
		}
	}

	if (IsMouseRightTriggered()&&!player.BulletReloadflg) {
		player.BulletReloadflg = true;
		D3DXVECTOR3 tempVec3 = 
			D3DXVECTOR3(g_Result_texture[TEXTURE_TURRET].Size_x / 2, g_Result_texture[TEXTURE_TURRET].Size_y / 2, 0);
		double TempLen = D3DXVec3Length(&tempVec3);

		PlaySound(SOUND_LABEL_SE_shot001);
		SetBlade(player.pos, dirBulletSightTemp, player.Rotation,
			TempLen, PLAYERS_BLADE);
	}

	//近接終わり

	switch (player.State)
	{
	case PLAYER_STATE_NORMAL:
		break;
	case PLAYER_STATE_MUTEKI:
		PlayerMutekiState();
		break;

	default:
		break;
	}

		
	//SetVertexPlayer();	// 頂点の計算処理
	//テクチャーに場所を入れる
	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		g_Result_texture[i].Pos = player.pos;
		g_Result_texture[i].Angle = player.Rotation;
	}

	UpdateBulletSight();//照準の処理
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawPlayer(void)
{
	if (!player.isEnable)
		return;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		if (!g_Result_texture[i].IsEnable)
			continue;
		//頂点座標セット
		if (g_Result_texture[i].IsEnableRotation) 
		{
			SetVertex(g_Result_texture[i].Vertex, g_Result_texture[i].Pos,
				g_Result_texture[i].Size_x, g_Result_texture[i].Size_y,
				g_Result_texture[i].BaseAngle, g_Result_texture[i].Angle);
		}
		else 
		{
			SetVertex(g_ResultVertex[i],
				g_Result_texture[i].Pos,
				g_Result_texture[i].Size_x,
				g_Result_texture[i].Size_y);
		
		}
		//テクスチャー座標のセット
		SetTexture(g_Result_texture[i].Vertex,
			g_Result_texture[i].Divide_x,
			g_Result_texture[i].Divide_y,
			g_Result_texture[i].TextureNumber);
		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);
		// テクスチャの設定
		pDevice->SetTexture(0, g_Result_texture[i].pD3DTexture);
		// ポリゴンの描画
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_PLAYER, g_Result_texture[i].Vertex, sizeof(VERTEX_2D));
	}

}

//PLAYERのGetter
PLAYER_DATA* GetPlayer() {
	return (&player);
}

// PLAYERのScoreを変える処理
void PlusPlayerScore(int PlusScore) {

	//プレイヤーのScoreが0以下にはならない
	if (PlusScore < 0 && player.Score == 0)
		return;
	player.Score += PlusScore;
	Ui_Score_Set(player.Score);
}

// PLAYERのHpを変える処理
void PlusPlayerHp(int PlusHp) {
	
	player.Hp += PlusHp;
	//UIにライフを反映させる
	Ui_Life_Set(player.Hp);
	//ダメージなら
	if (PlusHp<0)PlaySound(SOUND_LABEL_SE_DAMAGE000);
	//プレイヤーのHpが0になったとき
	if (player.Hp<=0) {
		DiePlayer();
	}
}

// PLAYERの状態を変える処理
void ChangePlayerState(PLAYER_STATE targetstate) {
	player.State = targetstate;
}

void DiePlayer() {
	player.isEnable = false;
	PlaySound(SOUND_LABEL_SE_PLAYERDIE);
	SetGamePhase(PHASE_GAME_END);
}

void PlayerMutekiState() {
	player.State_time += 1 / 60.0f;

	if (int(player.State_time*1000) % 4 == 0) {
		TenmetuPlayerTexture(0);
	}
	
	if (player.State_time > PLAYER_DMGHIT_MUTEKITIME)
	{
		TenmetuPlayerTexture(1);
		player.State_time = 0;
		player.State = PLAYER_STATE_NORMAL;
	}
}

//*****************************************************************************
// ここから下はplayer.cppのみで使われる関数
//*****************************************************************************

//=============================================================================
//プレイヤーの点滅処理

//ON=0 OFF=1
//=============================================================================
void TenmetuPlayerTexture(int EffectOnOff) {

	switch (EffectOnOff)
	{
	case 0:
		for (int i = 0; i < TEXTURE_MAX; i++)
		{
			//プレイヤーが表示されている時
			if (g_Result_texture[i].Vertex->diffuse == D3DCOLOR_RGBA(255, 255, 255, 255))
			{
				g_Result_texture[i].Vertex->diffuse = D3DCOLOR_RGBA(255, 255, 255, 0);
				(g_Result_texture[i].Vertex+1)->diffuse = D3DCOLOR_RGBA(255, 255, 255, 0);
				(g_Result_texture[i].Vertex+2)->diffuse = D3DCOLOR_RGBA(255, 255, 255, 0);
				(g_Result_texture[i].Vertex+3)->diffuse = D3DCOLOR_RGBA(255, 255, 255, 0);
				continue;
			}
			else
			//プレイヤーが表示されてないとき
			//if ((g_Result_texture[i].Vertex)->diffuse == D3DCOLOR_RGBA(255, 255, 255, 0))
			{
				(g_Result_texture[i].Vertex)->diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
				(g_Result_texture[i].Vertex+1)->diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
				(g_Result_texture[i].Vertex+2)->diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
				(g_Result_texture[i].Vertex+3)->diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
				continue;
			}

		}

		break;
	case 1:
		for (int i = 0; i < TEXTURE_MAX; i++)
		{
			//プレイヤーを表示する時
			(g_Result_texture[i].Vertex)->diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
			(g_Result_texture[i].Vertex+1)->diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
			(g_Result_texture[i].Vertex+2)->diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
			(g_Result_texture[i].Vertex+3)->diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		}
		break;
	default:
		break;

	}
}
