
//=============================================================================
//
// �e�̏��� [buleet.h]
//
//=============================================================================

#ifndef _BULLET_H_
#define _BULLET_H_

#define TEXTURE_GAME_Bullet00	_T("TEXTURE/bullet.tga")	// �T���v���p�摜
#define BULLET_WIDTH	(32)	//�G�̉���
#define BULLET_HEIGHT	(32)	//�G�̉���

//�ʗp
#define TEXTURE_PATTERN_BULLET_X	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_BULLET_Y	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iY)

#define MAX_BULLET		1000		//�e�̍ő吔
#define NUM_BULLET		2		//�e�̍ő吔


//Bullet�\����
typedef struct
{
	D3DXVECTOR3	pos;			//�ʒu���@���S�_
	D3DXVECTOR3	dir;			//�ړ�����
	float	Rotation;			//����

	D3DXVECTOR3 size;			//��ʂ̃T�C�Y
	int	Affiliation;			//����
	int power;					//�З�
	int type;					//�e�N�X�`���[�^�C�v
	bool			isEnable;		//�L���t���O
}BULLET;

enum AFFILIATIONofBULLET
{
	PLAYERS_BULLET,
	ENEMYS_BULLET,
	AFFILIATION_MAX
};

void InitBullet();
void UninitBullet();
void UpdateBullet();
void DrawBullet();

bool GetIsEnableBullet(int index);
BULLET* GetBullet();

//�e�̎ˏo����
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 velocity,float speed, int affiliation);
//�e�̎ˏo����
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 velocity, float speed, int affiliation,int power);

#endif
