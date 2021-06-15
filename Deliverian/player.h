//=============================================================================
//
// �v���C���[���� [Player.h]
// Author : 
//�X�R�A��HP�Ƃ������V�X�e����������Ɋi�[
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_


#define PLAYER_BLADE_BAIRITU		(2)// �v���C���[�̌��̗͂̔{��

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);

//�v���C���[���
enum PLAYER_STATE
{
	PLAYER_STATE_NORMAL,
	PLAYER_STATE_MUTEKI,
	PLAYER_STATE_MAX
};


//�v���C���[�\����
typedef struct
{
	D3DXVECTOR3	pos;	//�ʒu���:���S�_
	float		Rotation;		//����
	int		walkFrame;		//�A�j���[�V�����؂�ւ��E�G�C�g�̃J�E���^
	int		walkPattern;	//�A�j���[�V�����p�^�[��
	D3DXVECTOR3 size;			//��ʂ̃T�C�Y
	int		Score;
	int		Hp;	
	int		Power;
	PLAYER_STATE State;
	float	State_time;		//�X�e�[�g�̎�������
	bool	BulletReloadflg;		//�X�e�[�g�̎�������
	float	BulletReload_time;		//�X�e�[�g�̎�������
	bool	isEnable;
}PLAYER_DATA;

PLAYER_DATA *GetPlayer();
void PlusPlayerHp(int PlusHp);
void PlusPlayerScore(int PlusHp);
void ChangePlayerState(PLAYER_STATE targetstate);
#endif
