//インクルードする際はMAIN.hを一番上にすること
#include "Enemy_AI.h"
#include "player.h"
#define _USE_MATH_DEFINES 
#include "math.h"

#define FIRSTACTIVE_RANGE		100		//敵のAI起動範囲
#define FIRSTWAIT_TIME		(0.5f)		//敵のAI待ち時間
#define ENEMY_SEARCH_RADIUS		(200.0f)//敵のＡＩ視覚範囲
#define ENEMY_SEARCH_ANGLE      (0.85f) //敵のＡＩ視角
#define BACKSPEED		(0.5)		//敵のAIのバックスピード
#define CHARGESPEED		(10)		//敵のAIの突進スピード
#define CHARGE_TIME		(0.3)		//敵のAIの突進時間
#define ENEMY_STOPRANGE		(40)		//敵のAIの突進場外判定
#define ENEMY_BULLETINTERVAL	30		//敵のAIの突進場外判定
#define ENEMY_BULLET_TIME		(2)		//敵のAIの弾射出時間


void DicideEnemyState(ENEMY* enemy, int pattern);

//ENEMY.CPPの
void Enemy_AI_Update(ENEMY* enemy) {
	ENEMY originalEnemyData = *enemy;
	ENEMY returnEnemyData;

	//ランダムの決定
	//unsigned int    now = (unsigned int)time(0);
	//srand(now);
	float temprand;

	D3DXVECTOR3 tempdir ;

	//WAIT_ROTATIONで使用
	//プレイヤーの座標を取得する
	D3DXVECTOR3 pl_pos ;

	//敵とプレイヤーの距離を計算する
	D3DXVECTOR3 vLen ;
	float length ;


	switch(enemy->AI_State) {
		//最初の入場
	case 	GO_DIRECT:		//移動向きに移動
		enemy->pos += enemy->dir;
		//向きを格納する
		enemy->Rotation = atan2f(enemy->dir.y, enemy->dir.x) + (M_PI / 2);

		//AI起動範囲まで来たらWAITする
		if (enemy->pos.y > FIRSTACTIVE_RANGE//↓方向
			&&  enemy->dir.y>0)
			DicideEnemyState(enemy,0);
		//AI起動範囲まで来たらWAITする
		if (enemy->pos.y < SCREEN_GAME_HEIGHT - FIRSTACTIVE_RANGE//↑方向
			&& enemy->dir.y<0)
			DicideEnemyState(enemy, 0);
		//AI起動範囲まで来たらWAITする
		if (enemy->pos.x > FIRSTACTIVE_RANGE//→方向
			&& enemy->dir.x>0)
			DicideEnemyState(enemy, 0);
		//AI起動範囲まで来たらWAITする
		if (enemy->pos.x < SCREEN_GAME_WIDTH - FIRSTACTIVE_RANGE//←方向
			&& enemy->dir.x<0)
			DicideEnemyState(enemy, 0);
		break;

	case	WAIT_DIRECT:	//移動向きを維持し待機
		enemy->AI_State_time += 1.0f / 120.0f;
		if (enemy->AI_State_time >FIRSTWAIT_TIME) {
			enemy->AI_State_time =0;
			DicideEnemyState(enemy, 0);
		}
		break;


	//攻撃モード準備
	case	WAIT_ROTAION:	//その場を維持し、向きを変更
							//プレイヤーの方角を向くようにする

		enemy->Rotation += 0.03f;
		enemy->AI_State_time += 1.0f / 120.0f;

		tempdir= D3DXVECTOR3(sinf(enemy->Rotation), -cosf(enemy->Rotation), 0);
		//プレイヤーの座標を取得する
		pl_pos = D3DXVECTOR3(GetPlayer()->pos.x, GetPlayer()->pos.y, GetPlayer()->pos.z);

		//敵とプレイヤーの距離を計算する
		vLen = enemy->pos - pl_pos;
		length = D3DXVec3Length(&vLen);

		//判定する距離の中に入っているかをチェックする
		if (length < ENEMY_SEARCH_RADIUS)
		{
			//敵から見てプレイヤーの座標への方向ベクトルを作る
			D3DXVECTOR3 pl_dir = pl_pos - enemy->pos;
			D3DXVec3Normalize(&pl_dir, &pl_dir);

			//敵の向きとプレイヤ座標への方向ベクトルで内積を取る
			float dot = D3DXVec3Dot(&tempdir, &pl_dir);

			//判定する角度内に入っているかをチェックする
			if (dot > ENEMY_SEARCH_ANGLE)
			{
				//判定に通ればプレイヤー発見ステートに移行する
				enemy->AI_State_time = 0;
				DicideEnemyState(enemy, 0);
			}
		}
		break;

	case	CHARGE_BACK:	//向きを維持し,バックする
							//必ず突進する
		enemy->AI_State_time += 1.0f / 120.0f;
		enemy->pos.x -= sinf(enemy->Rotation)*BACKSPEED;
		//上下反転しているため
		enemy->pos.y += cosf(enemy->Rotation)*BACKSPEED;
		if (enemy->AI_State_time >FIRSTWAIT_TIME) {
			enemy->AI_State_time = 0;
			DicideEnemyState(enemy, 0);
		}
		break;

	case	CHARGE:			//移動方向の向きに突進
							//範囲外にぶつかった時はSIOP
							//自動で止まった時は再度回転
		enemy->AI_State_time += 1.0f / 120.0f;
		enemy->pos.x += sinf(enemy->Rotation)*CHARGESPEED;
		//上下反転しているため
		enemy->pos.y -= cosf(enemy->Rotation)*CHARGESPEED;
		
		//移動方向を入れる下のWAIT判定のため
		enemy->dir = D3DXVECTOR3(sinf(enemy->Rotation), -cosf(enemy->Rotation),0);

		//画面外まで来たらWAITする
		if (enemy->pos.y < ENEMY_STOPRANGE//↓方向
			&&  enemy->dir.y<0)
		{
			enemy->AI_State_time = 0;
			DicideEnemyState(enemy, 0);
		}
		//有効フラグを落とす
		if (enemy->pos.y > SCREEN_GAME_HEIGHT - ENEMY_STOPRANGE//↑方向
			&& enemy->dir.y>0)
		{
			enemy->AI_State_time = 0;
			DicideEnemyState(enemy, 0);
		}
		//有効フラグを落とす
		if (enemy->pos.x < ENEMY_STOPRANGE//→方向
			&& enemy->dir.x<0)
		{
			enemy->AI_State_time = 0;
			DicideEnemyState(enemy, 0);
		}
		//有効フラグを落とす
		if (enemy->pos.x > SCREEN_GAME_WIDTH -ENEMY_STOPRANGE //←方向
			&& enemy->dir.x>0)
		{
			enemy->AI_State_time = 0;
			DicideEnemyState(enemy, 0);
		}

		if (enemy->AI_State_time >CHARGE_TIME) {
			enemy->AI_State_time = 0;
			DicideEnemyState(enemy, 1);
		}
		break;

	case	ROTATION_SHOT:	//向きを変更しながらショット
		enemy->Rotation += 0.03f;
		enemy->AI_State_time += 1.0f / 120.0f;

		if (int(enemy->AI_State_time * 100) % ENEMY_BULLETINTERVAL == 0) {
			EnemyFireBullet(enemy);
		}

		if (enemy->AI_State_time > ENEMY_BULLET_TIME) {
			enemy->AI_State_time = 0;
			DicideEnemyState(enemy, 0);
		}
		break;

	case	SHOT_ONE:		//ショットを打つ
		enemy->AI_State_time += 1.0f / 120.0f;
		if (int(enemy->AI_State_time *100)% ENEMY_BULLETINTERVAL ==0) {
			EnemyFireBullet(enemy);
		}	
		if (enemy->AI_State_time > ENEMY_BULLET_TIME) {
			enemy->AI_State_time = 0;
			DicideEnemyState(enemy, 0);
		}

		break;
	case	DAKOU_DIRECT:			//向きを維持しながら蛇行
		enemy->AI_State_time += 1.0f / 120.0f;

		enemy->pos.x += sinf(enemy->Rotation);
		enemy->pos.x = enemy->pos.x+ cosf(enemy->Rotation)*sinf(enemy->AI_State_time *10) * 2;

		//上下反転しているため
		enemy->pos.y -= cosf(enemy->Rotation);
		enemy->pos.y = enemy->pos.y + sinf(enemy->Rotation)*sinf(enemy->AI_State_time * 10) * 2;

		//移動方向を入れる下のWAIT判定のため
		enemy->dir = D3DXVECTOR3(sinf(enemy->Rotation), -cosf(enemy->Rotation), 0);

		//画面外まで来たらWAITする
		if (enemy->pos.y < ENEMY_STOPRANGE//↓方向
			&&  enemy->dir.y < 0)
		{
			enemy->AI_State_time = 0;
			DicideEnemyState(enemy, 0);
		}
		//有効フラグを落とす
		if (enemy->pos.y > SCREEN_GAME_HEIGHT - ENEMY_STOPRANGE//↑方向
			&& enemy->dir.y > 0)
		{
			enemy->AI_State_time = 0;
			DicideEnemyState(enemy, 0);
		}
		//有効フラグを落とす
		if (enemy->pos.x < ENEMY_STOPRANGE//→方向
			&& enemy->dir.x < 0)
		{
			enemy->AI_State_time = 0;
			DicideEnemyState(enemy, 0);
		}
		//有効フラグを落とす
		if (enemy->pos.x > SCREEN_GAME_WIDTH - ENEMY_STOPRANGE //←方向
			&& enemy->dir.x > 0)
		{
			enemy->AI_State_time = 0;
			DicideEnemyState(enemy, 0);
		}

		if (enemy->AI_State_time *6 > (M_PI)*2) {
			enemy->AI_State_time = 0;
			DicideEnemyState(enemy, 1);
		}
		break;
	case GO_Straight:
		enemy->pos += enemy->dir*2;
		break;
	case	AISTATE_MAX:			//本来あり得ない
		break;
	
		default:
			break;
	
	}

	
}

//ENEMYのTYPEとStateによって次のステートを決定する
//第二引数は基本は0
//ステートごとにパターン分岐したいときは使う(整数)
void DicideEnemyState(ENEMY* enemy,int pattern) {

	switch (enemy->AI_type)
	{
	case FIGHTER:
		switch (enemy->AI_State)
		{
			case 	GO_DIRECT:
				enemy->AI_State = WAIT_DIRECT;
				break;
			case	WAIT_DIRECT:
				enemy->AI_State = WAIT_ROTAION;
				break;
				//攻撃モード準備
			case	WAIT_ROTAION:
				enemy->AI_State = CHARGE_BACK;
				break;
			case	CHARGE_BACK:
				enemy->AI_State = CHARGE;
				//enemy->State = CHARGE;
				break;
			case	CHARGE:
				if (pattern==0) {
					enemy->AI_State = WAIT_DIRECT;
				}else
				{
					enemy->AI_State = WAIT_ROTAION;
				}				
				break;
			//↓は何もしない
			default:
				break;
		}
		break;
	case SHOT_FIGHTER:
		switch (enemy->AI_State)
		{
		case 	GO_DIRECT:
			enemy->AI_State = WAIT_DIRECT;
			break;
		case	WAIT_DIRECT:
			enemy->AI_State = WAIT_ROTAION;
			break;
			//攻撃モード準備
		case	WAIT_ROTAION:
			enemy->AI_State = ROTATION_SHOT;
			break;
		case	ROTATION_SHOT:	//向きを変更しながらショット
			enemy->AI_State = SHOT_ONE;
			break;
		case	SHOT_ONE:		//ショットを打つ
			enemy->AI_State = WAIT_DIRECT;
			break;
		default:
			break;
		}
	case DAKOU_FIGHTER:
		switch (enemy->AI_State)
		{
		case 	GO_DIRECT:
			enemy->AI_State = WAIT_DIRECT;
			break;
		case	WAIT_DIRECT:
			enemy->AI_State = WAIT_ROTAION;
			break;
			//攻撃モード準備
		case	WAIT_ROTAION:
			enemy->AI_State = CHARGE_BACK;
			break;
		case	CHARGE_BACK:
			enemy->AI_State = DAKOU_DIRECT;
			//enemy->State = CHARGE;
			break;
		case	DAKOU_DIRECT:			//向きを維持しながら蛇行
			if (pattern == 0) {
				enemy->AI_State = WAIT_DIRECT;
			}
			else
			{
				enemy->AI_State = WAIT_ROTAION;
			}
			break;
		default:
			break;
		}
		break;
	case GO_FIGHTER: //まっすぐ突っ込むだけ
		switch (enemy->AI_State)
		{
		case 	GO_DIRECT:
			enemy->AI_State = GO_Straight;
			break;
		case 	GO_Straight:
			enemy->AI_State = GO_Straight;
			break;
		default:
			break;
		}
		break;

	default:
		break;
	}
}