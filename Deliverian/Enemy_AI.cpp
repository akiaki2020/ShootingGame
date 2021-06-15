//�C���N���[�h����ۂ�MAIN.h����ԏ�ɂ��邱��
#include "Enemy_AI.h"
#include "player.h"
#define _USE_MATH_DEFINES 
#include "math.h"

#define FIRSTACTIVE_RANGE		100		//�G��AI�N���͈�
#define FIRSTWAIT_TIME		(0.5f)		//�G��AI�҂�����
#define ENEMY_SEARCH_RADIUS		(200.0f)//�G�̂`�h���o�͈�
#define ENEMY_SEARCH_ANGLE      (0.85f) //�G�̂`�h���p
#define BACKSPEED		(0.5)		//�G��AI�̃o�b�N�X�s�[�h
#define CHARGESPEED		(10)		//�G��AI�̓ːi�X�s�[�h
#define CHARGE_TIME		(0.3)		//�G��AI�̓ːi����
#define ENEMY_STOPRANGE		(40)		//�G��AI�̓ːi��O����
#define ENEMY_BULLETINTERVAL	30		//�G��AI�̓ːi��O����
#define ENEMY_BULLET_TIME		(2)		//�G��AI�̒e�ˏo����


void DicideEnemyState(ENEMY* enemy, int pattern);

//ENEMY.CPP��
void Enemy_AI_Update(ENEMY* enemy) {
	ENEMY originalEnemyData = *enemy;
	ENEMY returnEnemyData;

	//�����_���̌���
	//unsigned int    now = (unsigned int)time(0);
	//srand(now);
	float temprand;

	D3DXVECTOR3 tempdir ;

	//WAIT_ROTATION�Ŏg�p
	//�v���C���[�̍��W���擾����
	D3DXVECTOR3 pl_pos ;

	//�G�ƃv���C���[�̋������v�Z����
	D3DXVECTOR3 vLen ;
	float length ;


	switch(enemy->AI_State) {
		//�ŏ��̓���
	case 	GO_DIRECT:		//�ړ������Ɉړ�
		enemy->pos += enemy->dir;
		//�������i�[����
		enemy->Rotation = atan2f(enemy->dir.y, enemy->dir.x) + (M_PI / 2);

		//AI�N���͈͂܂ŗ�����WAIT����
		if (enemy->pos.y > FIRSTACTIVE_RANGE//������
			&&  enemy->dir.y>0)
			DicideEnemyState(enemy,0);
		//AI�N���͈͂܂ŗ�����WAIT����
		if (enemy->pos.y < SCREEN_GAME_HEIGHT - FIRSTACTIVE_RANGE//������
			&& enemy->dir.y<0)
			DicideEnemyState(enemy, 0);
		//AI�N���͈͂܂ŗ�����WAIT����
		if (enemy->pos.x > FIRSTACTIVE_RANGE//������
			&& enemy->dir.x>0)
			DicideEnemyState(enemy, 0);
		//AI�N���͈͂܂ŗ�����WAIT����
		if (enemy->pos.x < SCREEN_GAME_WIDTH - FIRSTACTIVE_RANGE//������
			&& enemy->dir.x<0)
			DicideEnemyState(enemy, 0);
		break;

	case	WAIT_DIRECT:	//�ړ��������ێ����ҋ@
		enemy->AI_State_time += 1.0f / 120.0f;
		if (enemy->AI_State_time >FIRSTWAIT_TIME) {
			enemy->AI_State_time =0;
			DicideEnemyState(enemy, 0);
		}
		break;


	//�U�����[�h����
	case	WAIT_ROTAION:	//���̏���ێ����A������ύX
							//�v���C���[�̕��p�������悤�ɂ���

		enemy->Rotation += 0.03f;
		enemy->AI_State_time += 1.0f / 120.0f;

		tempdir= D3DXVECTOR3(sinf(enemy->Rotation), -cosf(enemy->Rotation), 0);
		//�v���C���[�̍��W���擾����
		pl_pos = D3DXVECTOR3(GetPlayer()->pos.x, GetPlayer()->pos.y, GetPlayer()->pos.z);

		//�G�ƃv���C���[�̋������v�Z����
		vLen = enemy->pos - pl_pos;
		length = D3DXVec3Length(&vLen);

		//���肷�鋗���̒��ɓ����Ă��邩���`�F�b�N����
		if (length < ENEMY_SEARCH_RADIUS)
		{
			//�G���猩�ăv���C���[�̍��W�ւ̕����x�N�g�������
			D3DXVECTOR3 pl_dir = pl_pos - enemy->pos;
			D3DXVec3Normalize(&pl_dir, &pl_dir);

			//�G�̌����ƃv���C�����W�ւ̕����x�N�g���œ��ς����
			float dot = D3DXVec3Dot(&tempdir, &pl_dir);

			//���肷��p�x���ɓ����Ă��邩���`�F�b�N����
			if (dot > ENEMY_SEARCH_ANGLE)
			{
				//����ɒʂ�΃v���C���[�����X�e�[�g�Ɉڍs����
				enemy->AI_State_time = 0;
				DicideEnemyState(enemy, 0);
			}
		}
		break;

	case	CHARGE_BACK:	//�������ێ���,�o�b�N����
							//�K���ːi����
		enemy->AI_State_time += 1.0f / 120.0f;
		enemy->pos.x -= sinf(enemy->Rotation)*BACKSPEED;
		//�㉺���]���Ă��邽��
		enemy->pos.y += cosf(enemy->Rotation)*BACKSPEED;
		if (enemy->AI_State_time >FIRSTWAIT_TIME) {
			enemy->AI_State_time = 0;
			DicideEnemyState(enemy, 0);
		}
		break;

	case	CHARGE:			//�ړ������̌����ɓːi
							//�͈͊O�ɂԂ���������SIOP
							//�����Ŏ~�܂������͍ēx��]
		enemy->AI_State_time += 1.0f / 120.0f;
		enemy->pos.x += sinf(enemy->Rotation)*CHARGESPEED;
		//�㉺���]���Ă��邽��
		enemy->pos.y -= cosf(enemy->Rotation)*CHARGESPEED;
		
		//�ړ����������鉺��WAIT����̂���
		enemy->dir = D3DXVECTOR3(sinf(enemy->Rotation), -cosf(enemy->Rotation),0);

		//��ʊO�܂ŗ�����WAIT����
		if (enemy->pos.y < ENEMY_STOPRANGE//������
			&&  enemy->dir.y<0)
		{
			enemy->AI_State_time = 0;
			DicideEnemyState(enemy, 0);
		}
		//�L���t���O�𗎂Ƃ�
		if (enemy->pos.y > SCREEN_GAME_HEIGHT - ENEMY_STOPRANGE//������
			&& enemy->dir.y>0)
		{
			enemy->AI_State_time = 0;
			DicideEnemyState(enemy, 0);
		}
		//�L���t���O�𗎂Ƃ�
		if (enemy->pos.x < ENEMY_STOPRANGE//������
			&& enemy->dir.x<0)
		{
			enemy->AI_State_time = 0;
			DicideEnemyState(enemy, 0);
		}
		//�L���t���O�𗎂Ƃ�
		if (enemy->pos.x > SCREEN_GAME_WIDTH -ENEMY_STOPRANGE //������
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

	case	ROTATION_SHOT:	//������ύX���Ȃ���V���b�g
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

	case	SHOT_ONE:		//�V���b�g��ł�
		enemy->AI_State_time += 1.0f / 120.0f;
		if (int(enemy->AI_State_time *100)% ENEMY_BULLETINTERVAL ==0) {
			EnemyFireBullet(enemy);
		}	
		if (enemy->AI_State_time > ENEMY_BULLET_TIME) {
			enemy->AI_State_time = 0;
			DicideEnemyState(enemy, 0);
		}

		break;
	case	DAKOU_DIRECT:			//�������ێ����Ȃ���֍s
		enemy->AI_State_time += 1.0f / 120.0f;

		enemy->pos.x += sinf(enemy->Rotation);
		enemy->pos.x = enemy->pos.x+ cosf(enemy->Rotation)*sinf(enemy->AI_State_time *10) * 2;

		//�㉺���]���Ă��邽��
		enemy->pos.y -= cosf(enemy->Rotation);
		enemy->pos.y = enemy->pos.y + sinf(enemy->Rotation)*sinf(enemy->AI_State_time * 10) * 2;

		//�ړ����������鉺��WAIT����̂���
		enemy->dir = D3DXVECTOR3(sinf(enemy->Rotation), -cosf(enemy->Rotation), 0);

		//��ʊO�܂ŗ�����WAIT����
		if (enemy->pos.y < ENEMY_STOPRANGE//������
			&&  enemy->dir.y < 0)
		{
			enemy->AI_State_time = 0;
			DicideEnemyState(enemy, 0);
		}
		//�L���t���O�𗎂Ƃ�
		if (enemy->pos.y > SCREEN_GAME_HEIGHT - ENEMY_STOPRANGE//������
			&& enemy->dir.y > 0)
		{
			enemy->AI_State_time = 0;
			DicideEnemyState(enemy, 0);
		}
		//�L���t���O�𗎂Ƃ�
		if (enemy->pos.x < ENEMY_STOPRANGE//������
			&& enemy->dir.x < 0)
		{
			enemy->AI_State_time = 0;
			DicideEnemyState(enemy, 0);
		}
		//�L���t���O�𗎂Ƃ�
		if (enemy->pos.x > SCREEN_GAME_WIDTH - ENEMY_STOPRANGE //������
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
	case	AISTATE_MAX:			//�{�����蓾�Ȃ�
		break;
	
		default:
			break;
	
	}

	
}

//ENEMY��TYPE��State�ɂ���Ď��̃X�e�[�g�����肷��
//�������͊�{��0
//�X�e�[�g���ƂɃp�^�[�����򂵂����Ƃ��͎g��(����)
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
				//�U�����[�h����
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
			//���͉������Ȃ�
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
			//�U�����[�h����
		case	WAIT_ROTAION:
			enemy->AI_State = ROTATION_SHOT;
			break;
		case	ROTATION_SHOT:	//������ύX���Ȃ���V���b�g
			enemy->AI_State = SHOT_ONE;
			break;
		case	SHOT_ONE:		//�V���b�g��ł�
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
			//�U�����[�h����
		case	WAIT_ROTAION:
			enemy->AI_State = CHARGE_BACK;
			break;
		case	CHARGE_BACK:
			enemy->AI_State = DAKOU_DIRECT;
			//enemy->State = CHARGE;
			break;
		case	DAKOU_DIRECT:			//�������ێ����Ȃ���֍s
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
	case GO_FIGHTER: //�܂������˂����ނ���
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