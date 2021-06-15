//インクルードする際はMAIN.hを一番上にすること
#include "boss_AI.h"
#include "player.h"
#define _USE_MATH_DEFINES 
#include "math.h"
#include "bullet.h"
#include "enemy_laser.h"

const float BOSS_SHOT_WIDTHGAP = 40.0f;
const float BOSS_BULLETSPEED = 2.0f;	//弾丸の速度
const float BOSS_RapidFIRESPEED = 3.0f;	//レーザーの発射間隔の速度
const float BOSS_ROTATESPEED = 0.05;	
const float BOSS_MOVESPEED = SCREEN_GAME_WIDTH*0.001f;

LASER* g_bossLaser;
bool  g_Stateflg1;
int  g_Last_MoveAi;
float temprand = 0.0f;

void DicidebossState(ENEMY* enemy, int pattern);
void FireLaser(ENEMY* boss, D3DXVECTOR3 tempdir);
void FireLaser(ENEMY* boss, D3DXVECTOR3 tempdir, float hutosa, float nagasa);
void FireBullet(ENEMY* boss, D3DXVECTOR3 temppos, D3DXVECTOR3 tempdir);
int RandamMoveAI();

//以下各ステータス化の行動
void APPEAR1(ENEMY* boss);
void WATE1(ENEMY* boss);
void FIRE1(ENEMY* boss);
void FIRE2(ENEMY* boss);
void FIRE3(ENEMY* boss);
void FIRE4(ENEMY* boss);
void FIRE5(ENEMY* boss);
void BOSS_LASER1(ENEMY* boss);
void BOSS_LASER2(ENEMY* boss);
void GO_LEFT(ENEMY* boss);
void GO_CENTER(ENEMY* boss);
void GO_RIGHT(ENEMY* boss);
void LEFTSIDE_ATTACK_DOWN(ENEMY* boss);
void LEFTSIDE_ATTACK_UP(ENEMY* boss);
void RIGHTSIDE_ATTACK_DOWN(ENEMY* boss);
void RIGHTSIDE_ATTACK_UP(ENEMY* boss);

//各AI行動で使う部品
bool GO_DOWN(ENEMY* boss);
bool GO_UP(ENEMY* boss);
bool TURN_LEFT(ENEMY* boss, D3DXVECTOR3 motoDir);
bool TURN_RIGHT(ENEMY* boss, D3DXVECTOR3 motoDir);

//ENEMY.CPPの
void Boss_AI_Update(ENEMY* boss) {
	ENEMY originalbossData = *boss;
	ENEMY returnEnemyData;

	//ランダムの決定
	temprand=rand();

	D3DXVECTOR3 tempdir ;

	//WAIT_ROTATIONで使用
	//プレイヤーの座標を取得する
	D3DXVECTOR3 pl_pos ;

	//敵とプレイヤーの距離を計算する
	D3DXVECTOR3 vLen ;
	float length ;

	switch(boss->AI_State) {
		//最初の入場
	case 	BOSS_STATE_APPEAR1:		//移動向きに移動
		APPEAR1(boss);
		break;
	case	BOSS_STATE_WATE1:	//移動向きを維持し待機
		WATE1(boss);
		break;

	case	BOSS_STATE_FIRE1:	
		FIRE1(boss);
		break;
	case	BOSS_STATE_FIRE2:
		FIRE2(boss);
		break;
	case	BOSS_STATE_FIRE3:
		FIRE3(boss);
		break;
		//その場で左右回転しレーザーを発射
	case	BOSS_STATE_LASER1:	//その場を維持し、向きを変更
		BOSS_LASER1(boss);
		break;
		//その場で左右回転しレーザーを発射
	case	BOSS_STATE_LASER2:	//その場を維持し、向きを変更
		BOSS_LASER2(boss);
		break;
	case 	BOSS_GO_LEFT:		//左向きに平行移動
		GO_LEFT(boss);
		break;
	case 	BOSS_GO_CENTER:		//左向きに平行移動
		GO_CENTER(boss);
		break;
	case 	BOSS_GO_RIGHT:		//左向きに平行移動
		GO_RIGHT(boss);
		break;
	case 	BOSS_LEFTSIDE_ATTACK_DOWN:		
		LEFTSIDE_ATTACK_DOWN(boss);
		break;
	case 	BOSS_LEFTSIDE_ATTACK_UP:		
		LEFTSIDE_ATTACK_UP(boss);
		break;
	case 	BOSS_RIGHTSIDE_ATTACK_DOWN:		
		RIGHTSIDE_ATTACK_DOWN(boss);
		break;
	case 	BOSS_RIGHTSIDE_ATTACK_UP:		
		RIGHTSIDE_ATTACK_UP(boss);
		break;

		break;
		default:
			break;
	}
}


//ENEMYのTYPEとStateによって次のステートを決定する
//第二引数は基本は0
//ステートごとにパターン分岐したいときは使う(整数)
void DicidebossState(ENEMY* boss,int pattern) {
	//ボスの初期化
	boss->int2 = 0;
	boss->flt3 = 0.0f;
	boss->flt4 = 0.0f;
	boss->AI_State_time = 0.0f;
	g_Stateflg1 = false;

	switch (boss->AI_type)
	{
	case B_FIGHTER:
		switch (boss->AI_State)
		{
			case 	BOSS_STATE_APPEAR1:
				boss->AI_State = BOSS_STATE_WATE1;
				break;
			case	BOSS_STATE_WATE1:
				boss->AI_State = BOSS_STATE_FIRE3;
				break;

			case	BOSS_STATE_FIRE1:
				if (g_Last_MoveAi == BOSS_STATE_APPEAR1) {
					g_Last_MoveAi = boss->AI_State = BOSS_GO_LEFT;
				}
				else if(g_Last_MoveAi == BOSS_GO_LEFT)
				{
					g_Last_MoveAi = boss->AI_State = BOSS_GO_CENTER;

				}
				else if (g_Last_MoveAi == BOSS_GO_CENTER)
				{
					g_Last_MoveAi = boss->AI_State = RandamMoveAI();
				}
				else if (g_Last_MoveAi == BOSS_GO_RIGHT)
				{
					g_Last_MoveAi = boss->AI_State = BOSS_GO_CENTER;

				}
				break;
			case	BOSS_STATE_FIRE2:
				boss->AI_State = BOSS_STATE_FIRE1;
				break;
			case	BOSS_STATE_FIRE3:
				boss->AI_State = BOSS_STATE_FIRE1;
				break;
			case	BOSS_GO_LEFT:	
				boss->AI_State = BOSS_STATE_WATE1;
				break;
			case	BOSS_GO_CENTER:		
				boss->AI_State = BOSS_STATE_WATE1;
				break;
			case	BOSS_GO_RIGHT:			
				boss->AI_State = BOSS_STATE_WATE1;
				break;
			default:
				break;
		}
		break;
	case B_LASER:
		switch (boss->AI_State)
		{
		case 	BOSS_STATE_APPEAR1:
			boss->AI_State = BOSS_STATE_WATE1;
			break;
		case	BOSS_STATE_WATE1:
			boss->AI_State = BOSS_STATE_LASER1;
			break;
		case	BOSS_STATE_LASER1:			
			boss->AI_State = BOSS_STATE_LASER2;
			break;
		case	BOSS_STATE_LASER2:			
			if (g_Last_MoveAi == BOSS_STATE_APPEAR1) {
				g_Last_MoveAi = boss->AI_State = BOSS_GO_LEFT;
			}
			else if (g_Last_MoveAi == BOSS_GO_LEFT)
			{
				g_Last_MoveAi = boss->AI_State = BOSS_GO_CENTER;

			}
			else if (g_Last_MoveAi == BOSS_GO_CENTER)
			{
				g_Last_MoveAi = boss->AI_State = RandamMoveAI();
			}
			else if (g_Last_MoveAi == BOSS_GO_RIGHT)
			{
				g_Last_MoveAi = boss->AI_State = BOSS_GO_CENTER;

			}
			break;
		case	BOSS_GO_LEFT:	
			boss->AI_State = BOSS_STATE_WATE1;
			break;
		case	BOSS_GO_CENTER:		
			boss->AI_State = BOSS_STATE_WATE1;
			break;
		case	BOSS_GO_RIGHT:			
			boss->AI_State = BOSS_STATE_WATE1;
			break;
		default:
			break;
		}
		break;
	case B_FINAL:
		switch (boss->AI_State)
		{
		case 	BOSS_STATE_APPEAR1:
			boss->AI_State = BOSS_GO_LEFT;
			break;
		case	BOSS_STATE_WATE1:
			boss->AI_State = BOSS_STATE_FIRE3;
			break;
		case	BOSS_STATE_FIRE3:
			if (g_Last_MoveAi == BOSS_GO_LEFT)
			{
				boss->AI_State = BOSS_GO_RIGHT;
			}
			else if (g_Last_MoveAi == BOSS_GO_RIGHT)
			{
				boss->AI_State = BOSS_GO_LEFT;

			}
			break;
		case	BOSS_GO_LEFT:
			boss->AI_State = BOSS_LEFTSIDE_ATTACK_DOWN;
			//boss->AI_State = BOSS_STATE_WATE1;
			g_Last_MoveAi =  BOSS_GO_LEFT;
			break;
		case	BOSS_GO_CENTER:
			boss->AI_State = BOSS_STATE_WATE1;
			break;
		case	BOSS_GO_RIGHT:
			boss->AI_State = BOSS_RIGHTSIDE_ATTACK_DOWN;
			g_Last_MoveAi = BOSS_GO_RIGHT;
			break;
		case	BOSS_RIGHTSIDE_ATTACK_DOWN:
			boss->AI_State = BOSS_RIGHTSIDE_ATTACK_UP;
			break;
		case	BOSS_RIGHTSIDE_ATTACK_UP:
			boss->AI_State = BOSS_GO_CENTER;
			break;
		case	BOSS_LEFTSIDE_ATTACK_DOWN:
			boss->AI_State = BOSS_LEFTSIDE_ATTACK_UP;
			break;
		case	BOSS_LEFTSIDE_ATTACK_UP:
			boss->AI_State = BOSS_GO_CENTER;
			break;
		default:
			break;
		}
		break;


	default:
		break;
	}
	/*
	if (boss->AI_type == B_FINAL)
	{
		if (boss->AI_State == BOSS_GO_LEFT)
			boss->AI_State = BOSS_STATE_WATE1;
	}
	*/
}

void FireLaser(ENEMY* boss, D3DXVECTOR3 tempdir)
{
	g_bossLaser =SetEnemyLaser(boss->pos,
		1,		//所属
		0,		//color
		50.0f,	//hutosa
		50.0f, //nagasa
		1,		//power
		tempdir);
}

void FireLaser(ENEMY* boss, D3DXVECTOR3 tempdir,float hutosa, float nagasa)
{
	g_bossLaser = SetEnemyLaser(boss->pos,
		1,		//所属
		0,		//color
		hutosa,	//hutosa
		nagasa, //nagasa
		1,		//power
		tempdir);
}

void FireBullet(ENEMY* boss, D3DXVECTOR3 tempPos, D3DXVECTOR3 tempdir)
{
	SetBullet(
		tempPos,
		tempdir,
		BOSS_BULLETSPEED,
		ENEMYS_BULLET);
}

int RandamMoveAI() 
{
	int ReturnState = BOSS_STATE_WATE1;
	int tempState = (int)temprand % 2;
	switch (tempState)
	{
	case 0:
		ReturnState = BOSS_GO_LEFT;
		break;
	case 1:
		ReturnState = BOSS_GO_RIGHT;
		break;
	default:
		break;
	}
	return ReturnState;
}


void APPEAR1(ENEMY* boss)
{
	boss->pos += boss->dir;
	//向きを格納する
	boss->Rotation = atan2f(boss->dir.y, boss->dir.x) + (M_PI / 2);
	//初回のみ
	g_bossLaser = NULL;
	g_Stateflg1 = false;
	g_Last_MoveAi = BOSS_STATE_APPEAR1;
	//2秒後に次のステートに行く
	if (boss->pos.y >= SCREEN_GAME_HEIGHT / 5)
	{
		DicidebossState(boss, 0);
	}
}


void WATE1(ENEMY* boss)
{
	boss->flt3 += 0.25f;
	//振動のような処理をつける
	boss->pos.x += cos(boss->flt3)*1.0f;
	boss->AI_State_time++;

	//2秒後に次のステートに行く
	if (boss->AI_State_time >= 120)
	{
		DicidebossState(boss, 0);
	}
}

//↓方向発射
void FIRE1(ENEMY* boss)
{
	if (boss->int2 == 10)
	{
		D3DXVECTOR3 tempPos;
		D3DXVECTOR3 tempdir = D3DXVECTOR3(0.0f, 5.0f, 0.0f);
		for (int i = -2; i < 3; i++)
		{
			tempPos = boss->pos;
			tempPos.x += BOSS_SHOT_WIDTHGAP * i;
			FireBullet(boss, tempPos, tempdir);
		}
		boss->int2 = 0;
	}
	boss->int2++;
	boss->AI_State_time++;
	//2秒後に次のステートに行く
	if (boss->AI_State_time >= 560)
	{
		DicidebossState(boss, 0);
	}
}

//全方向発射
void FIRE2(ENEMY* boss)
{
	if (boss->int2 == 10)
	{
		for (int i = 0; i < 16; i++)
		{
			D3DXVECTOR3 velocity;
			velocity.x = cos(2.0f*M_PI*i / 16.0f)*4.0;
			velocity.y = sin(2.0f*M_PI*i / 16.0f) *4.0;
			velocity.z = 0.0f;
			FireBullet(boss,boss->pos, velocity);
		}

		boss->int2 = 0;
	}
	boss->int2++;

	boss->AI_State_time++;
	//2秒後に次のステートに行く
	if (boss->AI_State_time >= 120)
	{		
		DicidebossState(boss, 0);
	}

}

//螺旋発射
void FIRE3(ENEMY* boss)
{
	if (boss->int2 == 10)
	{
		//螺旋
		boss->flt4 += 0.1f;
		if ((int)(boss->flt4 * 10) % 4 == 0) 
		{
			D3DXVECTOR3 Velocity;
			Velocity.x = cos(boss->flt4)*1.0;
			Velocity.y = sin(boss->flt4)*1.0;
			Velocity.z = 0;
			FireBullet(boss, boss->pos, Velocity);
		}

		boss->int2 = 0;
	}
	boss->int2++;

	boss->AI_State_time++;
	//2秒後に次のステートに行く
	//if (boss->AI_State_time >= 1000)
	if (boss->flt4 >= M_PI * 2)
	{
		//ボスの初期化
		DicidebossState(boss, 0);
	}

}
//void FIRE4(ENEMY* boss);
//void FIRE5(ENEMY* boss);

//左右に旋回しレーザーを出す	
void BOSS_LASER1(ENEMY* boss)
{
	D3DXVECTOR3 tempdir;
	//向きを格納する
	if (!g_Stateflg1)
	{
		//左旋回
		boss->Rotation = boss->Rotation + sin(boss->flt3)*BOSS_ROTATESPEED;
	}
	else
	{
		//右旋回
		boss->Rotation = boss->Rotation - sin(boss->flt3)*BOSS_ROTATESPEED;
	}
	//左旋回がすべて終わったら右旋回
	if (boss->flt3>M_PI * 2)
	{
		g_Stateflg1 = true;
	}

	tempdir = D3DXVECTOR3(0, 0, 0);
	tempdir = D3DXVECTOR3(sinf(boss->Rotation), -cosf(boss->Rotation), 0);

	if(boss->int2>30)
	{
		FireLaser(boss, tempdir);
		boss->int2 = 0;
	}

	boss->int2++;
	boss->AI_State_time++;
	boss->flt3 += 0.05f;
	//2秒後に次のステートに行く
	//if (boss->AI_State_time >= 120)
	if (boss->flt3>M_PI * 4)
	{
		//↓向きを格納する
		boss->Rotation = atan2f(boss->dir.y, boss->dir.x) + (M_PI / 2);
		DicidebossState(boss, 0);
	}


}

//↓方向にレーザーを出す
void BOSS_LASER2(ENEMY* boss)
{
	if (boss->int2 == 10)
	{
		FireLaser(boss, D3DXVECTOR3(0.0f, 1.0f,0.0f), 100.0f, 100.0f);
		boss->int2 = 0;
	}
	boss->int2++;
	boss->AI_State_time++;
	//2秒後に次のステートに行く
	if (boss->AI_State_time >= 240)
	{
		DicidebossState(boss, 0);
	}
}
void GO_LEFT(ENEMY* boss)
{
	boss->pos.x -= BOSS_MOVESPEED;
	if (boss->pos.x <= SCREEN_GAME_WIDTH / 5)
	{
		DicidebossState(boss, 0);
	}
}
void GO_CENTER(ENEMY* boss)
{

	if (boss->pos.x < SCREEN_GAME_WIDTH / 2)
	{
		boss->pos.x += BOSS_MOVESPEED;
	}
	else
	{
		boss->pos.x -= BOSS_MOVESPEED;
	}

	//2秒後に次のステートに行く
	if (boss->pos.x >= SCREEN_GAME_WIDTH / 2 - BOSS_MOVESPEED
		&& boss->pos.x <= SCREEN_GAME_WIDTH / 2 + BOSS_MOVESPEED)
	{
		DicidebossState(boss, 0);
	}

}
void GO_RIGHT(ENEMY* boss) 
{

	boss->pos.x += BOSS_MOVESPEED;
	//2秒後に次のステートに行く
	if (boss->pos.x >= SCREEN_GAME_WIDTH / 5 * 4)
	{
		DicidebossState(boss, 0);
	}
}

void LEFTSIDE_ATTACK_DOWN(ENEMY* boss)
{
	//最初に左回転する終わったら括弧の行動
	if (TURN_RIGHT(boss, D3DXVECTOR3(0, 1, 0)))
	{
		if (boss->int2 == 50)
		{
			D3DXVECTOR3 tempPos;
			D3DXVECTOR3 tempdir;
			tempdir = D3DXVECTOR3(0, 0, 0);
			tempdir = D3DXVECTOR3(sinf(boss->Rotation), -cosf(boss->Rotation), 0);
			tempPos = boss->pos;
			FireBullet(boss, tempPos, tempdir);
			boss->int2 = 0;
		}
		boss->int2++;
		boss->AI_State_time++;

		//下に行き終わったら次のステートへ
		if (GO_DOWN(boss))
		{
			DicidebossState(boss, 0);
		}
	}

}
void LEFTSIDE_ATTACK_UP(ENEMY* boss) 
{
	//上に行き終わったら括弧の行動
	if (GO_UP(boss))
	{
		if (boss->int2 == 20)
		{
			D3DXVECTOR3 tempPos;
			D3DXVECTOR3 tempdir;
			tempdir = D3DXVECTOR3(0, 0, 0);
			tempdir = D3DXVECTOR3(sinf(boss->Rotation), -cosf(boss->Rotation), 0);
			tempPos = boss->pos;
			FireBullet(boss, tempPos, tempdir);
			boss->int2 = 0;
		}
		boss->int2++;
		boss->AI_State_time++;

		//左回転する次のステートへ
		if (TURN_LEFT(boss, D3DXVECTOR3(1, 0, 0)))
		{
			DicidebossState(boss, 0);
		}
	}
}
void RIGHTSIDE_ATTACK_DOWN(ENEMY* boss)
{
	//最初に左回転する終わったら括弧の行動
	if (TURN_LEFT(boss, D3DXVECTOR3(0,1,0)))
	{
		if (boss->int2 == 50)
		{
			D3DXVECTOR3 tempPos;
			D3DXVECTOR3 tempdir;
			tempdir = D3DXVECTOR3(0, 0, 0);
			tempdir = D3DXVECTOR3(sinf(boss->Rotation), -cosf(boss->Rotation), 0);
			tempPos = boss->pos;
			FireBullet(boss, tempPos, tempdir);
			boss->int2 = 0;
		}
		boss->int2++;
		boss->AI_State_time++;

		//下に行き終わったら次のステートへ
		if (GO_DOWN(boss))
		{
			DicidebossState(boss, 0);
		}
	}


}
void RIGHTSIDE_ATTACK_UP(ENEMY* boss)
{
	//上に行き終わったら括弧の行動
	if (GO_UP(boss))
	{
		if (boss->int2 == 20)
		{
			D3DXVECTOR3 tempPos;
			D3DXVECTOR3 tempdir;
			tempdir = D3DXVECTOR3(0, 0, 0);
			tempdir = D3DXVECTOR3(sinf(boss->Rotation), -cosf(boss->Rotation), 0);
			tempPos = boss->pos;
			FireBullet(boss, tempPos, tempdir);
			boss->int2 = 0;
		}
		boss->int2++;
		boss->AI_State_time++;

		//左回転する次のステートへ
		if (TURN_RIGHT(boss, D3DXVECTOR3(-1,0,0)))
		{
			DicidebossState(boss, 0);
		}
	}
}

//↓各行動で使う部品
//特定の行動をしたらTRUE
bool GO_DOWN(ENEMY* boss)
{	
	if (boss->pos.y <= SCREEN_GAME_HEIGHT / 5*4)
	{
		boss->pos.y += BOSS_MOVESPEED;
		return false;
	}
	return true;
}
bool GO_UP(ENEMY* boss) 
{
	if (boss->pos.y >= SCREEN_GAME_HEIGHT / 5)
	{
		boss->pos.y -= BOSS_MOVESPEED;
		return false;
	}
	return true;
}

bool TURN_LEFT(ENEMY* boss, D3DXVECTOR3 motoDir)
{

	//向きを格納する
	if (boss->flt3<=M_PI /2)
	{
		boss->flt3 += 0.015f;
		if (boss->flt3 >= M_PI / 2)boss->flt3 = M_PI / 2;
		//左旋回
		boss->Rotation = atan2f(motoDir.y, motoDir.x) + (M_PI / 2) + boss->flt3;
		return false;
	}
	return true;
}

//右に90度回転
bool TURN_RIGHT(ENEMY* boss, D3DXVECTOR3 motoDir)
{
	//向きを格納する
	if (boss->flt3 <= M_PI /2)
	{
		boss->flt3 += 0.015f;
		if (boss->flt3 >= M_PI / 2)boss->flt3 = M_PI / 2;
		//右旋回
		boss->Rotation = atan2f(motoDir.y, motoDir.x) + (M_PI / 2) - boss->flt3;
		return false;
	}
	return true;
}