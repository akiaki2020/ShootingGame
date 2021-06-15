
#include "main.h"
#include "Func_texture.h"
#define _USE_MATH_DEFINES 
#include "math.h"
#include "enemy_laser.h"
#include "input.h"
#include "texture.h"
#include "table.h"


//*****************************************************************************
// CONST�ϐ�
//*****************************************************************************



const Texture_DATA c_InitTexture[MAX_LASER_TYPE] =
{
	{
		(char *)"TEXTURE/Stg_main/Shoot/bullet2.tga"
		,NULL
		,NULL
		,D3DXVECTOR3(
			SCREEN_GAME_WIDTH / 2,
			SCREEN_GAME_HEIGHT / 4 * 3,
			0.0f)	//�����ł͎g��Ȃ�
		,LASER_WIDTH
		,LASER_WIDTH
		,true
		,0
		,0
		,true
		,NON_DIVIDE
		,NON_DIVIDE
		,NON_DIVIDE_TEXTURENUMBER
		,false
		,D3DXVECTOR4(255, 255, 255, 255)
	},
};

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

LASER Laser[MAX_LASER];

static VERTEX_2D g_PolygonVertex[MAX_LASER_TYPE][4];	//���_�f�[�^
static unsigned int g_Texture;			//�e�N�X�`���f�[�^
static Texture_DATA g_texture[MAX_LASER_TYPE];

void InitEnemyLaser()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (int i = 0; i < MAX_LASER_TYPE; i++)
	{
		SetTextureDATA(
			pDevice,
			g_PolygonVertex[i]
			, &g_texture[i]
			, &c_InitTexture[i]);
	}
	for (int i = 0; i < MAX_LASER; i++)
	{
		Laser[i].isEnable = false;
	}
}


void UninitEnemyLaser()
{
	for (int i = 0; i < MAX_LASER_TYPE; i++)
	{
		UnLoadTextureDATA(&g_texture[i]);
	}
	
}


void UpdateEnemyLaser()
{
	for (int i = 0; i < MAX_LASER; i++)
	{
		//�L���t���O��ON����Ȃ���Ή������Ȃ�
		if (Laser[i].isEnable == false)
			continue;

		//���W���X�V����
		Laser[i].pos += Laser[i].dir;
		
		//���[�U�[���ˏI���t���O���L����������
		//�X�^�[�g�n�_�𓮂���
		if (Laser[i].isEnd ==true)
			Laser[i].s_pos += Laser[i].dir;

		//����̒����܂ōs������L�т鏈���͏I���ƂȂ�
		D3DXVECTOR3 tempVec3 = Laser[i].pos - Laser[i].s_pos;
		float tempflt = D3DXVec3Length(&tempVec3);

		if (tempflt > Laser[i].Nagasa)
		{
			Laser[i].isEnd = true;
		}


		//�e����ʂ���o�čs���Ă��܂�����
		//�L���t���O�𗎂Ƃ�
		if (Laser[i].s_pos.x > SCREEN_GAME_WIDTH)
			Laser[i].isEnable = false;
		if (Laser[i].s_pos.x < 0)
			Laser[i].isEnable = false;
		if (Laser[i].s_pos.y > SCREEN_GAME_HEIGHT)
			Laser[i].isEnable = false;
		if (Laser[i].s_pos.y < 0)
			Laser[i].isEnable = false;


	}
}


void DrawEnemyLaser()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int i = 0; i < MAX_LASER; i++)
	{
		//�L���t���O��ON����Ȃ���Ή������Ȃ�
		if (Laser[i].isEnable == false)
			continue;

		//���[�U�[�^�C�v���i�[����
		int textureType = Laser[i].texType;

		//�L�т̏���
		g_texture[textureType].Pos = Laser[i].pos;
		g_texture[textureType].Size_x = Laser[i].Futosa;
		g_texture[textureType].BaseAngle = 
			atan2f(g_texture[textureType].Size_y, g_texture[textureType].Size_x);
		g_texture[textureType].Angle = Laser[i].Rotation;

		SetVertexVeticalSpread(g_texture[textureType].Vertex,
			Laser[i].s_pos,	//�X�^�[�g�|�W�V����
			g_texture[textureType].Pos,//�L�у|�W�V����
			g_texture[textureType].Size_x,
			g_texture[textureType].Size_y,
			g_texture[textureType].BaseAngle,
			g_texture[textureType].Angle);
			
		//�e�N�X�`���[���W�̃Z�b�g
		SetTexture(g_texture[textureType].Vertex,
			g_texture[textureType].Divide_x,
			g_texture[textureType].Divide_y);

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);
		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_texture[textureType].pD3DTexture);
		// �|���S���̕`��
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_PLAYER, g_texture[textureType].Vertex, sizeof(VERTEX_2D));
		
	}
}


//�L���t���O��n��
bool GetIsEnableEnemyLaser(int index)
{
	return Laser[index].isEnable;
}


//ENEMY��Getter
LASER* GetEnemyLaser() {
	return (Laser);
}



void DestroyEnemyLaser(int index) {

	Laser[index].isEnable = false;
}

void EndEnemyLaser(int index) {

	Laser[index].isEnd = true;
}

//�e�̎ˏo����
LASER* SetEnemyLaser(D3DXVECTOR3 pos, int affiliation, int color
					, float Futosa, float nagasa, int power, D3DXVECTOR3 dir)
{
	for (int i = 0; i < MAX_LASER; i++)
	{
		//�e�̔z�񂩂�󂫂�T��
		//���ݎg���Ă���̈悾�����ꍇ��
		//�������Ȃ��ŃX���[����
		if (Laser[i].isEnable == true)
			continue;

		
		Laser[i].texType = LASER1;
		Laser[i].Affiliation = affiliation;
		Laser[i].power = power;

		Laser[i].s_pos = pos;
		//���@�O���ɏo��
		Laser[i].s_pos.x += dir.x*50.0f;
		Laser[i].s_pos.y += dir.y*50.0f;


		Laser[i].pos = Laser[i].s_pos;
		Laser[i].Futosa = Futosa;
		Laser[i].Nagasa = nagasa;
		Laser[i].isEnd = false;

		Laser[i].dir = dir;
		Laser[i].Rotation =	atan2f(dir.y, dir.x) + (M_PI / 2);
		//�ړ������ɃX�s�[�h���|����
		Laser[i].dir *= LASER_SPPED;

		//�L���t���O��ON�ɂ���
		Laser[i].isEnable = true;
		return &Laser[i];
		break;
	}
}
