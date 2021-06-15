#pragma once

#define LASER_WIDTH	(32)	//�G�e�̉���
#define LASER_HEIGHT	(32)	//�G�e�̉���
#define MAX_LASER		100		//�G�e�̍ő吔
#define LASER_SPPED 2;

//�G�l�~�[�\����
typedef struct
{
	D3DXVECTOR3	pos;			//�ʒu���(�I�_)
	D3DXVECTOR3	dir;			//�ړ�����
	D3DXVECTOR3	s_pos;			//�n�_
	float		Rotation;		//����
	//�搶��CAPSEL�ϐ������ē����蔻��Ƃ���
	int texType;				//�e�N�X�`���[�̃^�C�v
	float	Futosa;					//����
	float	Nagasa;					//����
	int				Affiliation;	//�G�����@
	int				color;			
	int				power;			//power
	bool			isEnd;		//���[�U�[���ˏI���t���O
	bool			isEnable;		//�L���t���O
}LASER;

//�{�X�̃^�C�v
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

//�e�̎ˏo����
LASER* SetEnemyLaser(D3DXVECTOR3 pos, int affiliation,int color
	, float Futosa, float nagasa, int power, D3DXVECTOR3 dir);
