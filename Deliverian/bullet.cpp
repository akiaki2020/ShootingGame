#include "main.h"
#define _USE_MATH_DEFINES 
#include "math.h"
#include "Func_texture.h"
#include "bullet.h"

//*****************************************************************************
// CONST�ϐ�
//*****************************************************************************

const static Texture_DATA c_InitTexture[] =
{
	{
	(char *)"TEXTURE/bullet.tga"
	,NULL
	,NULL
	,D3DXVECTOR3(SCREEN_GAME_WIDTH / 2, SCREEN_GAME_HEIGHT / 4 * 3, 0.0f)	//�����ł͎g��Ȃ�
	,BULLET_WIDTH
	,BULLET_HEIGHT
	,true
	,0
	,0
	,false
	,NON_DIVIDE
	,NON_DIVIDE
	,NON_DIVIDE_TEXTURENUMBER
	,false
	,D3DXVECTOR4(255, 255, 255, 255)
	},
};

enum TextureType {
	NORMAL,
	TYPE_MAX
};

//����
static enum Affiliation {
	PLAYER,
	ENEMY,
	Affiliation_MAX
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexBullet(BULLET* bullet);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

BULLET bullet[MAX_BULLET];					//�e�̃f�[�^

static LPDIRECT3DTEXTURE9		g_pD3DTexture = NULL;		// �e�N�X�`���ւ̃|�C���^
static VERTEX_2D g_PolygonVertex[TYPE_MAX][4];//���_�f�[�^
static Texture_DATA g_Texture[TYPE_MAX];

void InitBullet()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int i = 0; i < MAX_BULLET; i++)
	{
		bullet[i].pos.x = 0;
		bullet[i].pos.y = 0;
		bullet[i].size.x = BULLET_WIDTH;
		bullet[i].size.y = BULLET_HEIGHT;
		bullet[i].size.z = 0;
		bullet[i].type = NORMAL;

		bullet[i].power = 1;
		//�L���t���O��OFF�ɂ���
		bullet[i].isEnable = false;
	}

	//�e�N�X�`���f�[�^�̏�����
	for (int i = 0; i < TYPE_MAX; i++)
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


void UninitBullet()
{
	//UninitInput();
	for (int i = 0; i < TYPE_MAX; i++)
	{
		UnLoadTextureDATA(&g_Texture[i]);
	}
}


void UpdateBullet()
{
	for (int i = 0; i < MAX_BULLET; i++)
	{
		//�L���t���O��ON����Ȃ���Ή������Ȃ�
		if (bullet[i].isEnable == false)
			continue;

		//���W���X�V����
		bullet[i].pos += bullet[i].dir;
		//�������i�[����
		bullet[i].Rotation = atan2f(bullet[i].dir.y, bullet[i].dir.x) + (M_PI / 2);

		//�e����ʂ���o�čs���Ă��܂�����
		//�L���t���O�𗎂Ƃ�
		if (bullet[i].pos.y < 0- BULLET_HEIGHT/2)
			bullet[i].isEnable = false;
		//�L���t���O�𗎂Ƃ�
		if (bullet[i].pos.y > SCREEN_HEIGHT + BULLET_HEIGHT/2)
			bullet[i].isEnable = false;
		//�L���t���O�𗎂Ƃ�
		if (bullet[i].pos.x < 0 - BULLET_WIDTH / 2)
			bullet[i].isEnable = false;
		//�L���t���O�𗎂Ƃ�
		if (bullet[i].pos.x > SCREEN_WIDTH + BULLET_WIDTH/2)
			bullet[i].isEnable = false;
	}
}


void DrawBullet()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);


	for (int i = 0; i < MAX_BULLET; i++)
	{
		//�L���t���O��ON����Ȃ���Ή������Ȃ�
		if (bullet[i].isEnable == false)
			continue;

		int textureType = bullet[i].type;
		g_Texture[textureType].Pos = bullet[i].pos;
		g_Texture[textureType].Angle = bullet[i].Rotation;
		g_Texture[textureType].Size_x= bullet[i].size.x;
		g_Texture[textureType].Size_y = bullet[i].size.y;
		MakeVertexBullet(&bullet[i]);

		DrawTextureDATA(
			pDevice,
			&g_Texture[textureType]
		);
	}
}


//�L���t���O��n��
bool GetIsEnableBullet(int index)
{
	return bullet[index].isEnable;
}


//ENEMY��Getter
BULLET* GetBullet() {
	return (&bullet[0]);
}

//�e�̎ˏo����
void SetBullet(
	D3DXVECTOR3 pos,
	D3DXVECTOR3 velovity,
	float speed,
	int affiliation)	//�v���C���[���G��
{
	for (int i = 0; i < MAX_BULLET; i++) {
		//�e�̔z�񂩂�󂫂�T��
		//���ݎg���Ă���̈悾�����ꍇ��
		//�������Ȃ��ŃX���[����
		if (bullet[i].isEnable == true)
			continue;

		//���˂���ʒu���Z�b�g
		bullet[i].pos.x = pos.x;
		bullet[i].pos.y = pos.y;

		//���ł����������Z�b�g
		bullet[i].dir = velovity;
		//�ړ������ɃX�s�[�h���|����
		bullet[i].dir *= speed;

		//�G�������̒e�ǂ��炩���߂�
		bullet[i].Affiliation = affiliation;
		bullet[i].power = 1;

		//�L���t���O��ON�ɂ���
		bullet[i].isEnable = true;
		//�e���P�Z�b�g������I������
		break;
	}
}


//�e�̎ˏo����
void SetBullet(
	D3DXVECTOR3 pos,
	D3DXVECTOR3 velovity,
	float speed,
	int affiliation,
	int power)	//�v���C���[���G��
{
	for (int i = 0; i < MAX_BULLET; i++) {
		//�e�̔z�񂩂�󂫂�T��
		//���ݎg���Ă���̈悾�����ꍇ��
		//�������Ȃ��ŃX���[����
		if (bullet[i].isEnable == true)
			continue;

		//���˂���ʒu���Z�b�g
		bullet[i].pos.x = pos.x;
		bullet[i].pos.y = pos.y;

		//���ł����������Z�b�g
		bullet[i].dir = velovity;
		//�ړ������ɃX�s�[�h���|����
		bullet[i].dir *= speed;

		//�G�������̒e�ǂ��炩���߂�
		bullet[i].Affiliation = affiliation;
		bullet[i].power = power;

		//�L���t���O��ON�ɂ���
		bullet[i].isEnable = true;

		//�e���P�Z�b�g������I������
		break;
	}
}


//�ȉ��֐���BULLET�̒��̂�

//=============================================================================
// ���_�̍쐬
//=============================================================================
void MakeVertexBullet(BULLET* bullet)
{
	int textureType = bullet->type;
	// ���ˌ��̐ݒ�
	switch (bullet->Affiliation)
	{
	case PLAYERS_BULLET://	�f�t�H���g
		g_Texture[textureType].Color = D3DXVECTOR4(255, 255, 255, 255);
		break;
	case ENEMYS_BULLET://��
		g_Texture[textureType].Color = D3DXVECTOR4(255, 0, 0, 255);
		break;
	default:
		break;
	}
}

