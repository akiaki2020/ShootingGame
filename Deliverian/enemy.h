//=============================================================================
//
// �v���C���[���� [Enemy.h]
// Author : 
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_


#define MAX_ENEMY		100		//�G�̍ő吔
#define NUM_ENEMY		2		//


//�G�l�~�[�\����
typedef struct
{
	D3DXVECTOR3	pos;			//�ʒu���(���S�_�ɂ��邱��)
	D3DXVECTOR3	dir;			//�ړ�����
	float		Rotation;		//����
	int AI_type;					//�G�̃^�C�v(���AI)
	int TextureDivide_x;		// �A�j���p�^�[���̃e�N�X�`�����������iX)
	int TextureDivide_y;		// �A�j���p�^�[���̃e�N�X�`�����������iY)
	int TextureDivide_Type;		//�e�N�`���[�̕������̉����ڂ�
	D3DXVECTOR3 size;			//��ʂ̃T�C�Y
	int Hp;
	int	Power;
	int	  Score;				//���j���̉��Z�X�R�A
	int State;					//���
	float State_time;			//��Ԍo�ߎ���	
	int AI_State;				//AI�̏��
	float	AI_State_time;		//AI�̏�Ԍo�ߎ���	
	bool	isEnable;		//�L���t���O
	int	  int1;				//�e�N�X�`���[�^�C�v	
	int	  int2;				//BOSS��bulletCount�Ƃ��Ĉ���	
	int	  int3;
	int	  int4;
	float BulletSpeed;			//�e�̃X�s�[�h
	float flt2;					
	float flt3;					//3�ϐ��@BOSS�͈ړ��p�x�ƈ���
	float flt4;					//4�ϐ��@BOSS�͎ˏo�p�x�ƈ���
	bool	Enemy_Mutekiflg;	//�G�̖��G�t���O
	float	Muteki_time;		//�G�̖��G����
	D3DXVECTOR3	EffectPos;		//�G�t�F�N�g���̈ړ�
}ENEMY;

//�G�̃^�C�v
enum EnemyType {
	FIGHTER,
	SHOT_FIGHTER,
	DAKOU_FIGHTER,
	BIG_FIGHTER,
	GO_FIGHTER,
	MAX_ENEMYTYPE
};

//�G�̏��
enum ENEMY_STATE
{
	ENEMY_STATE_NORMAL,
	ENEMY_STATE_DAMAGE,
	ENEMY_STATE_MAX
};

void InitEnemy();
void UninitEnemy();
void UpdateEnemy();
void DrawEnemy();

void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 dir,int EnemyType);
ENEMY& GetEnemyTbl(int index);

bool GetIsEnableEnemy(int index);
ENEMY* GetEnemy();

void EnemyFireBullet(ENEMY* enemy);
void PlusEnemyHp(ENEMY* enemy, int PlusHp);
void ChangeEnemyState(ENEMY* enemy, int targetstate);
void SetBossDate(ENEMY& enemy);


#endif
