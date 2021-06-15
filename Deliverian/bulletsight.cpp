
#include "main.h"
#include "Func_texture.h"
#include "bulletsight.h"

//*****************************************************************************
// CONST�ϐ�
//*****************************************************************************
#define BULLETSIGHT_WIDTH	(32)	
#define BULLETSIGHT_HEIGHT	(32)	

#define MAX_BULLETSIGHT		1		
#define NUM_BULLETSIGHT		2		

const static Texture_DATA c_InitTexture[] =
{
	{
		(char *)"TEXTURE/Stg_main/Player/target_player.png"
		,NULL
		,NULL
		,D3DXVECTOR3
		(SCREEN_GAME_WIDTH / 2, SCREEN_GAME_HEIGHT / 4 * 3, 0.0f)	//�����ł͎g��Ȃ�
		,BULLETSIGHT_WIDTH
		,BULLETSIGHT_HEIGHT
		,true
		,0
		,0
		,true
		,NON_DIVIDE
		,NON_DIVIDE
		,NON_DIVIDE_TEXTURENUMBER
		,false
		,D3DXVECTOR4(128, 255, 128, 255)
	},
};

enum
{
	TEXTURE_bulletsight,
	TEXTURE_bulletsight_MAX,
};
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

BULLETSIGHT BulletSight[MAX_BULLETSIGHT];					//�e�̃f�[�^

static VERTEX_2D g_PolygonVertex[TEXTURE_bulletsight_MAX][4];//���_�f�[�^
static Texture_DATA g_Texture[TEXTURE_bulletsight_MAX];

void InitBulletSight()
{

	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	for (int i = 0; i < MAX_BULLETSIGHT; i++)
	{
		BulletSight[i].pos.x = SCREEN_GAME_WIDTH / 2;
		BulletSight[i].pos.y = SCREEN_GAME_HEIGHT /2;

		//�L���t���O��ON�ɂ���
		BulletSight[i].isEnable = TRUE;
		// ���_���̍쐬
	}
	//�e�N�X�`���f�[�^�̏�����
	for (int i = 0; i < TEXTURE_bulletsight_MAX; i++)
	{
		SetTextureDATA
		(
			pDevice,
			g_PolygonVertex[i],
			&g_Texture[i],
			&c_InitTexture[i]
		);
	}
}


void UninitBulletSight()
{
	for (int i = 0; i < TEXTURE_bulletsight_MAX; i++)
	{
		UnLoadTextureDATA(&g_Texture[i]);
	}
}


void UpdateBulletSight()
{
	for (int i = 0; i < MAX_BULLETSIGHT; i++)
	{
		//�L���t���O��ON����Ȃ���Ή������Ȃ�
		if (BulletSight[i].isEnable == false)
			continue;

		//���W���X�V����
		BulletSight[i].pos += BulletSight[i].dir;

		//�e��O����
		if (BulletSight[i].pos.y < 0 + BULLETSIGHT_HEIGHT / 2)
			BulletSight[i].pos.y = BULLETSIGHT_HEIGHT / 2;
		if (BulletSight[i].pos.y > SCREEN_HEIGHT- BULLETSIGHT_HEIGHT/2)
			BulletSight[i].pos.y = SCREEN_HEIGHT - BULLETSIGHT_HEIGHT/2;
		if (BulletSight[i].pos.x < 0+ BULLETSIGHT_WIDTH/2)
			BulletSight[i].pos.x = BULLETSIGHT_WIDTH / 2;
		if (BulletSight[i].pos.x > SCREEN_GAME_WIDTH - BULLETSIGHT_WIDTH/2)
			BulletSight[i].pos.x = SCREEN_GAME_WIDTH - BULLETSIGHT_WIDTH/2;
	}
}


void DrawBulletSight()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (int i = 0; i < MAX_BULLETSIGHT; i++)
	{
		//�L���t���O��ON����Ȃ���Ή������Ȃ�
		if (BulletSight[i].isEnable == false)
			continue;
		g_Texture[TEXTURE_bulletsight].Pos = BulletSight[i].pos;

		DrawTextureDATA(
			pDevice,
			&g_Texture[TEXTURE_bulletsight]
		);
	}
}


//�L���t���O��n��
bool GetIsEnableBulletSight(int index)
{
	return BulletSight[index].isEnable;
}


//ENEMY��Getter
BULLETSIGHT* GetBulletSight() {
	return (&BulletSight[0]);
}


//ENEMY��Getter
void BulletMove(D3DXVECTOR3 pos) {
	for (int i = 0; i < MAX_BULLETSIGHT; i++)
	{
		//�L���t���O��ON����Ȃ���Ή������Ȃ�
		if (BulletSight[i].isEnable == false)
			continue;

		BulletSight[i].pos += pos;

	}
}

//�e�̎ˏo����
void SetBulletSight(D3DXVECTOR3 pos,
	D3DXVECTOR3 velovity)
{
	for (int i = 0; i < MAX_BULLETSIGHT; i++) {
		//�e�̔z�񂩂�󂫂�T��
		//���ݎg���Ă���̈悾�����ꍇ��
		//�������Ȃ��ŃX���[����
		if (BulletSight[i].isEnable == true)
			continue;

		//���˂���ʒu���Z�b�g
		BulletSight[i].pos.x = pos.x;
		BulletSight[i].pos.y = pos.y;

		//���ł����������Z�b�g
		BulletSight[i].dir = velovity;

		//�ړ������ɃX�s�[�h���|����
		BulletSight[i].dir *= 1;

		//�L���t���O��ON�ɂ���
		BulletSight[i].isEnable = true;

		//�e���P�Z�b�g������I������
		break;
	}
}
