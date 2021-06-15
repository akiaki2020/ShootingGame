
//=============================================================================
//
// �ߐڂ̏��� [Blade.h]
//
//=============================================================================

#ifndef _BLADE_H_
#define _BLADE_H_

#define BLADE_HEIGHT	(64)	//���̉���
#define BLADE_WIDTH	(64)	//���̉���
#define BLADE_LENGTH	(55)//���̒���
#define BLADE_ANGLE		(0.70f)//���̂ӂ蕝

#define MAX_BLADE		50		//�e�̍ő吔
#define NUM_BLADE		2		//�e�̍ő吔

//Blade�\����
typedef struct
{
	D3DXVECTOR3	pos;			//�ʒu���
	D3DXVECTOR3	dir;			//�ړ�����
	float	Rotation;		//����
	int TextureDivide_x;		// �A�j���p�^�[���̃e�N�X�`�����������iX)
	int TextureDivide_y;		// �A�j���p�^�[���̃e�N�X�`�����������iY)
	int TextureType;			//�e�N�`���[�̃^�C�v
	int	Affiliation;	//����
	int State;					//���
	float State_time;			//��Ԍo�ߎ���	

	bool			isEnable;		//�L���t���O
}BLADE;

enum AFFILIATIONofBLADE
{
	PLAYERS_BLADE,
	ENEMYS_BLADE,
	AFFILIATION_BLADE_MAX
};

void InitBlade();
void UninitBlade();
void UpdateBlade();
void DrawBlade();

bool GetIsEnableBlade(int index);
BLADE* GetBlade();

//�e�̎ˏo����
void SetBlade(D3DXVECTOR3 pos, D3DXVECTOR3 velocity, float Rotaion, float speed, int affiliation);

#endif
