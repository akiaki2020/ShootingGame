#pragma once


#define ENEMY_BULLET_WIDTH	(32)	//�G�e�̉���
#define ENEMY_BULLET_HEIGHT	(32)	//�G�e�̉���

#define ENEMY_MAX_BULLET		100		//�G�e�̍ő吔

#define ENEMY_BULLET_SPPED 2;

//�G�l�~�[�\����
typedef struct
{
	nn::math::VEC2	pos;			//�ʒu���
	nn::math::VEC2	dir;			//�ړ�����
	int				muki;			//����
	int				color;
	bool			isEnable;		//�L���t���O
}ENEMY_BULLET;

void InitEnemy_Bullet();
void UninitEnemy_Bullet();
void UpdateEnemy_Bullet();
void DrawEnemy_Bullet();

int* GET_ENEMYBULLET_absorb_check();
void DestroyEnemyBULLET(int);

bool GetIsEnableEnemy_Bullet(int index);
ENEMY_BULLET* GetEnemy_Bullet();

//�e�̎ˏo����
void SetEnemy_Bullet(nn::math::VEC2 player_pos, int muki,int color);
