#include "main.h"
#include "Func_texture.h"
#include "Blade.h"

//*****************************************************************************
// CONST�ϐ�
//*****************************************************************************

#define BLADE_APPEARTIME		(1.0)		//BLADE�̏o������

const static Texture_DATA c_InitTexture[] =
{
	{
		(char *)"TEXTURE/Stg_main/Shoot/10.png"
		,NULL
		,NULL
		,D3DXVECTOR3(SCREEN_GAME_WIDTH / 2, 
			SCREEN_GAME_HEIGHT / 4 * 3, 0.0f)	//�����ł͎g��Ȃ�
		,32
		,32
		,false
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

enum
{
	TEXTURE_BLADE,
	TEXTURE_BLADE_MAX,
};
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
//void MakeVertexBlade(int index,int affiliation);
//void SetTextureBlade(int index);	// 
//void SetVertexBlade(int index);					// ���_�̌v�Z����
//

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

BLADE Blade[MAX_BLADE];					//�e�̃f�[�^

static VERTEX_2D g_PolygonVertex[TEXTURE_BLADE_MAX][4];	//���_�f�[�^
static Texture_DATA g_Texture[TEXTURE_BLADE_MAX];			//�e�N�X�`���f�[�^


//����
static enum Affiliation {
	PLAYER,
	ENEMY,
	Affiliation_MAX
};

void InitBlade()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int i = 0; i < MAX_BLADE; i++)
	{
		Blade[i].pos.x = 0;
		Blade[i].pos.y = 0;

		//�L���t���O��OFF�ɂ���
		Blade[i].isEnable = false;
	}	


	//�e�N�X�`���f�[�^�̏�����
	for (int i = 0; i < TEXTURE_BLADE_MAX; i++)
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


void UninitBlade()
{
	for (int i = 0; i < TEXTURE_BLADE_MAX; i++)
	{
		UnLoadTextureDATA(&g_Texture[i]);
	}

}


void UpdateBlade()
{
	for (int i = 0; i < MAX_BLADE; i++)
	{
		//�L���t���O��ON����Ȃ���Ή������Ȃ�
		if (Blade[i].isEnable == false)
			continue;

		Blade[i].State_time += 1.0f/120.0f;
		if (Blade[i].State_time>BLADE_APPEARTIME) {
			Blade[i].isEnable = false;
		}

		//�e����ʂ���o�čs���Ă��܂�����
		//�L���t���O�𗎂Ƃ�
		if (Blade[i].pos.y < 0)
			Blade[i].isEnable = false;
		//�L���t���O�𗎂Ƃ�
		if (Blade[i].pos.y > SCREEN_GAME_HEIGHT - BLADE_HEIGHT)
			Blade[i].isEnable = false;
		//�L���t���O�𗎂Ƃ�
		if (Blade[i].pos.x < 0)
			Blade[i].isEnable = false;
		//�L���t���O�𗎂Ƃ�
		if (Blade[i].pos.x > SCREEN_GAME_WIDTH - BLADE_WIDTH)
			Blade[i].isEnable = false;
	}
}
void DrawBlade()
{

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	for (int i = 0; i < MAX_BLADE; i++)
	{
		//�L���t���O��ON����Ȃ���Ή������Ȃ�
		if (Blade[i].isEnable == false)
			continue;

		//���]����p�x�v�Z�͓��ς͌����Ȃ�
		//����b�p�x�i�Ɓj���v�Z����
		float baseAngle;	//��b�p�x
		baseAngle = atan2f(BLADE_HEIGHT, BLADE_WIDTH);

		//��莞�ԗ��Ə����鏈��
		switch (Blade[i].Affiliation)
		{
		case PLAYERS_BLADE:
			//���_���W�̐ݒ�
			//�ʏ�	
			MakeVertex(g_Texture[TEXTURE_BLADE].Vertex,
				D3DXVECTOR4(255, 255, 255, 255- Blade[i].State_time/BLADE_APPEARTIME*230));
			break;
		case ENEMYS_BLADE:
			//���_���W�̐ݒ�
			//�ԐF�E�E�f�L�i�C�J���Ƃ肠����������
			MakeVertex(g_Texture[TEXTURE_BLADE].Vertex, D3DXVECTOR4(255, 0, 0, 140));
			break;
		default:
			MakeVertex(g_Texture[TEXTURE_BLADE].Vertex, D3DXVECTOR4(255, 255, 255, 255));
			break;
		}

		//���_���W�Z�b�g
		SetVertex(g_Texture[TEXTURE_BLADE].Vertex
			, Blade[i].pos
			, BLADE_WIDTH
			, BLADE_HEIGHT
			, baseAngle
			,Blade[i].Rotation);

		//�e�N�X�`���[���W�̃Z�b�g
		SetTexture(g_Texture[TEXTURE_BLADE].Vertex,
			Blade[i].TextureDivide_x,
			Blade[i].TextureDivide_y,
			Blade[i].TextureType);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_Texture[TEXTURE_BLADE].pD3DTexture);
		// �|���S���̕`��
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_BLADE, g_Texture[TEXTURE_BLADE].Vertex, sizeof(VERTEX_2D));
		
	}
}

//�L���t���O��n��
bool GetIsEnableBlade(int index)
{
	return Blade[index].isEnable;
}


//ENEMY��Getter
BLADE* GetBlade() {
	return (&Blade[0]);
}

//�e�̎ˏo����
void SetBlade(
	D3DXVECTOR3 pos,
	D3DXVECTOR3 velovity,
	float Rotaion,
	float speed,
	int affiliation)	//�v���C���[���G��
{
	for (int i = 0; i < MAX_BLADE; i++) {
		//�e�̔z�񂩂�󂫂�T��
		//���ݎg���Ă���̈悾�����ꍇ��
		//�������Ȃ��ŃX���[����
		if (Blade[i].isEnable == true)
			continue;

		//�e�N�X�`���[���Z�b�g
		Blade[i].TextureDivide_x = 1;
		Blade[i].TextureDivide_y = 1;
		Blade[i].TextureType = 0;
		//���˂���ʒu���Z�b�g
		Blade[i].pos.x = pos.x;
		Blade[i].pos.y = pos.y;

		//���ł����������Z�b�g
		Blade[i].dir = velovity;
		//�ړ������ɃX�s�[�h���|����
		Blade[i].dir *= speed;

		//�v���C���[�̏ꏊ�Ɂ{�����𑫂�
		Blade[i].pos += Blade[i].dir;

		//�U�����������
		Blade[i].Rotation = Rotaion;

		//�G�������̒e�ǂ��炩���߂�
		Blade[i].Affiliation = affiliation;

		//�X�e�[�g�����߂�
		Blade[i].State = 0;
		Blade[i].State_time= 0.0f;

		//�L���t���O��ON�ɂ���
		Blade[i].isEnable = true;

		//�e���P�Z�b�g������I������
		break;
	}
}


//�ȉ��֐���Blade�̒��̂�

