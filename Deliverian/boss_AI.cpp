//�C���N���[�h����ۂ�MAIN.h����ԏ�ɂ��邱��
#include "boss_AI.h"
#include "player.h"
#define _USE_MATH_DEFINES 
#include "math.h"
#include "bullet.h"
#include "enemy_laser.h"

const float BOSS_SHOT_WIDTHGAP = 40.0f;
const float BOSS_BULLETSPEED = 2.0f;	//�e�ۂ̑��x
const float BOSS_RapidFIRESPEED = 3.0f;	//���[�U�[�̔��ˊԊu�̑��x
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

//�ȉ��e�X�e�[�^�X���̍s��
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

//�eAI�s���Ŏg�����i
bool GO_DOWN(ENEMY* boss);
bool GO_UP(ENEMY* boss);
bool TURN_LEFT(ENEMY* boss, D3DXVECTOR3 motoDir);
bool TURN_RIGHT(ENEMY* boss, D3DXVECTOR3 motoDir);

//ENEMY.CPP��
void Boss_AI_Update(ENEMY* boss) {
	ENEMY originalbossData = *boss;
	ENEMY returnEnemyData;

	//�����_���̌���
	temprand=rand();

	D3DXVECTOR3 tempdir ;

	//WAIT_ROTATION�Ŏg�p
	//�v���C���[�̍��W���擾����
	D3DXVECTOR3 pl_pos ;

	//�G�ƃv���C���[�̋������v�Z����
	D3DXVECTOR3 vLen ;
	float length ;

	switch(boss->AI_State) {
		//�ŏ��̓���
	case 	BOSS_STATE_APPEAR1:		//�ړ������Ɉړ�
		APPEAR1(boss);
		break;
	case	BOSS_STATE_WATE1:	//�ړ��������ێ����ҋ@
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
		//���̏�ō��E��]�����[�U�[�𔭎�
	case	BOSS_STATE_LASER1:	//���̏���ێ����A������ύX
		BOSS_LASER1(boss);
		break;
		//���̏�ō��E��]�����[�U�[�𔭎�
	case	BOSS_STATE_LASER2:	//���̏���ێ����A������ύX
		BOSS_LASER2(boss);
		break;
	case 	BOSS_GO_LEFT:		//�������ɕ��s�ړ�
		GO_LEFT(boss);
		break;
	case 	BOSS_GO_CENTER:		//�������ɕ��s�ړ�
		GO_CENTER(boss);
		break;
	case 	BOSS_GO_RIGHT:		//�������ɕ��s�ړ�
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


//ENEMY��TYPE��State�ɂ���Ď��̃X�e�[�g�����肷��
//�������͊�{��0
//�X�e�[�g���ƂɃp�^�[�����򂵂����Ƃ��͎g��(����)
void DicidebossState(ENEMY* boss,int pattern) {
	//�{�X�̏�����
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
		1,		//����
		0,		//color
		50.0f,	//hutosa
		50.0f, //nagasa
		1,		//power
		tempdir);
}

void FireLaser(ENEMY* boss, D3DXVECTOR3 tempdir,float hutosa, float nagasa)
{
	g_bossLaser = SetEnemyLaser(boss->pos,
		1,		//����
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
	//�������i�[����
	boss->Rotation = atan2f(boss->dir.y, boss->dir.x) + (M_PI / 2);
	//����̂�
	g_bossLaser = NULL;
	g_Stateflg1 = false;
	g_Last_MoveAi = BOSS_STATE_APPEAR1;
	//2�b��Ɏ��̃X�e�[�g�ɍs��
	if (boss->pos.y >= SCREEN_GAME_HEIGHT / 5)
	{
		DicidebossState(boss, 0);
	}
}


void WATE1(ENEMY* boss)
{
	boss->flt3 += 0.25f;
	//�U���̂悤�ȏ���������
	boss->pos.x += cos(boss->flt3)*1.0f;
	boss->AI_State_time++;

	//2�b��Ɏ��̃X�e�[�g�ɍs��
	if (boss->AI_State_time >= 120)
	{
		DicidebossState(boss, 0);
	}
}

//����������
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
	//2�b��Ɏ��̃X�e�[�g�ɍs��
	if (boss->AI_State_time >= 560)
	{
		DicidebossState(boss, 0);
	}
}

//�S��������
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
	//2�b��Ɏ��̃X�e�[�g�ɍs��
	if (boss->AI_State_time >= 120)
	{		
		DicidebossState(boss, 0);
	}

}

//��������
void FIRE3(ENEMY* boss)
{
	if (boss->int2 == 10)
	{
		//����
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
	//2�b��Ɏ��̃X�e�[�g�ɍs��
	//if (boss->AI_State_time >= 1000)
	if (boss->flt4 >= M_PI * 2)
	{
		//�{�X�̏�����
		DicidebossState(boss, 0);
	}

}
//void FIRE4(ENEMY* boss);
//void FIRE5(ENEMY* boss);

//���E�ɐ��񂵃��[�U�[���o��	
void BOSS_LASER1(ENEMY* boss)
{
	D3DXVECTOR3 tempdir;
	//�������i�[����
	if (!g_Stateflg1)
	{
		//������
		boss->Rotation = boss->Rotation + sin(boss->flt3)*BOSS_ROTATESPEED;
	}
	else
	{
		//�E����
		boss->Rotation = boss->Rotation - sin(boss->flt3)*BOSS_ROTATESPEED;
	}
	//�����񂪂��ׂďI�������E����
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
	//2�b��Ɏ��̃X�e�[�g�ɍs��
	//if (boss->AI_State_time >= 120)
	if (boss->flt3>M_PI * 4)
	{
		//���������i�[����
		boss->Rotation = atan2f(boss->dir.y, boss->dir.x) + (M_PI / 2);
		DicidebossState(boss, 0);
	}


}

//�������Ƀ��[�U�[���o��
void BOSS_LASER2(ENEMY* boss)
{
	if (boss->int2 == 10)
	{
		FireLaser(boss, D3DXVECTOR3(0.0f, 1.0f,0.0f), 100.0f, 100.0f);
		boss->int2 = 0;
	}
	boss->int2++;
	boss->AI_State_time++;
	//2�b��Ɏ��̃X�e�[�g�ɍs��
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

	//2�b��Ɏ��̃X�e�[�g�ɍs��
	if (boss->pos.x >= SCREEN_GAME_WIDTH / 2 - BOSS_MOVESPEED
		&& boss->pos.x <= SCREEN_GAME_WIDTH / 2 + BOSS_MOVESPEED)
	{
		DicidebossState(boss, 0);
	}

}
void GO_RIGHT(ENEMY* boss) 
{

	boss->pos.x += BOSS_MOVESPEED;
	//2�b��Ɏ��̃X�e�[�g�ɍs��
	if (boss->pos.x >= SCREEN_GAME_WIDTH / 5 * 4)
	{
		DicidebossState(boss, 0);
	}
}

void LEFTSIDE_ATTACK_DOWN(ENEMY* boss)
{
	//�ŏ��ɍ���]����I������犇�ʂ̍s��
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

		//���ɍs���I������玟�̃X�e�[�g��
		if (GO_DOWN(boss))
		{
			DicidebossState(boss, 0);
		}
	}

}
void LEFTSIDE_ATTACK_UP(ENEMY* boss) 
{
	//��ɍs���I������犇�ʂ̍s��
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

		//����]���鎟�̃X�e�[�g��
		if (TURN_LEFT(boss, D3DXVECTOR3(1, 0, 0)))
		{
			DicidebossState(boss, 0);
		}
	}
}
void RIGHTSIDE_ATTACK_DOWN(ENEMY* boss)
{
	//�ŏ��ɍ���]����I������犇�ʂ̍s��
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

		//���ɍs���I������玟�̃X�e�[�g��
		if (GO_DOWN(boss))
		{
			DicidebossState(boss, 0);
		}
	}


}
void RIGHTSIDE_ATTACK_UP(ENEMY* boss)
{
	//��ɍs���I������犇�ʂ̍s��
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

		//����]���鎟�̃X�e�[�g��
		if (TURN_RIGHT(boss, D3DXVECTOR3(-1,0,0)))
		{
			DicidebossState(boss, 0);
		}
	}
}

//���e�s���Ŏg�����i
//����̍s����������TRUE
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

	//�������i�[����
	if (boss->flt3<=M_PI /2)
	{
		boss->flt3 += 0.015f;
		if (boss->flt3 >= M_PI / 2)boss->flt3 = M_PI / 2;
		//������
		boss->Rotation = atan2f(motoDir.y, motoDir.x) + (M_PI / 2) + boss->flt3;
		return false;
	}
	return true;
}

//�E��90�x��]
bool TURN_RIGHT(ENEMY* boss, D3DXVECTOR3 motoDir)
{
	//�������i�[����
	if (boss->flt3 <= M_PI /2)
	{
		boss->flt3 += 0.015f;
		if (boss->flt3 >= M_PI / 2)boss->flt3 = M_PI / 2;
		//�E����
		boss->Rotation = atan2f(motoDir.y, motoDir.x) + (M_PI / 2) - boss->flt3;
		return false;
	}
	return true;
}