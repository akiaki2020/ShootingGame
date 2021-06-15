//#include <math.h>
#include "Func_texture.h"
#define _USE_MATH_DEFINES 
#include "math.h"

float g_th=0.0f;

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertex(VERTEX_2D *g_vertexWk)
{
	// rhw�̐ݒ�
	g_vertexWk[0].rhw = 1.0f;
	g_vertexWk[1].rhw = 1.0f;
	g_vertexWk[2].rhw = 1.0f;
	g_vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	g_vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	return S_OK;
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertex(VERTEX_2D *g_vertexWk, D3DXVECTOR4 color)
{
	// rhw�̐ݒ�
	g_vertexWk[0].rhw = 1.0f;
	g_vertexWk[1].rhw = 1.0f;
	g_vertexWk[2].rhw = 1.0f;
	g_vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	g_vertexWk[0].diffuse = D3DCOLOR_RGBA((int)color.x, (int)color.y, (int)color.z, (int)color.w);
	g_vertexWk[1].diffuse = D3DCOLOR_RGBA((int)color.x, (int)color.y, (int)color.z, (int)color.w);
	g_vertexWk[2].diffuse = D3DCOLOR_RGBA((int)color.x, (int)color.y, (int)color.z, (int)color.w);
	g_vertexWk[3].diffuse = D3DCOLOR_RGBA((int)color.x, (int)color.y, (int)color.z, (int)color.w);

	return S_OK;
}




//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTexture(VERTEX_2D *g_vertexWk,
	int Texture_Divide_x,
	int Texture_Divide_y)
{
	int x = 0;
	int y = 0;
	// �e�N�X�`�����W�̐ݒ�
	float sizeX = 1.0f / Texture_Divide_x;
	float sizeY = 1.0f / Texture_Divide_y;

	g_vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	g_vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	g_vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	g_vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
}
//=============================================================================
// �e�N�X�`�����W�̐ݒ�PNG�̓���̃t�@�C�����g���ꍇ
//�����TEXTURE�FTexture_Number��0
//=============================================================================
void SetTexture(VERTEX_2D *g_vertexWk,
	int Texture_Divide_x,
	int Texture_Divide_y,
	int Texture_Number)
{
	int x = 0;
	int y = 0;
	// �e�N�X�`�����W�̐ݒ�
	float sizeX = 1.0f / Texture_Divide_x;
	float sizeY = 1.0f / Texture_Divide_y;
	x = Texture_Number % Texture_Divide_x;
	y = Texture_Number / Texture_Divide_x;
	g_vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	g_vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	g_vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	g_vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
}
//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertex(VERTEX_2D *g_vertexWk,
	D3DXVECTOR3 pos,
	float Texture_Size_x,
	float Texture_Size_y)
{
	// ���_���W�̐ݒ�
	g_vertexWk[0].vtx = D3DXVECTOR3(pos.x - Texture_Size_x/2, pos.y - Texture_Size_y/2, pos.z);
	g_vertexWk[1].vtx = D3DXVECTOR3(pos.x + Texture_Size_x / 2, pos.y - Texture_Size_y / 2, pos.z);
	g_vertexWk[2].vtx = D3DXVECTOR3(pos.x - Texture_Size_x / 2, pos.y + Texture_Size_y / 2, pos.z);
	g_vertexWk[3].vtx = D3DXVECTOR3(pos.x + Texture_Size_x / 2, pos.y + Texture_Size_y / 2, pos.z);
}
//=============================================================================
// ���_���W�̐ݒ� �Q�_�ŐL�яk����ꍇ�@//���������ꌻ���UI�̂ݎg��
										//�c�̂�
//=============================================================================

void SetVertexVeticalSpread(VERTEX_2D *g_vertexWk,
	D3DXVECTOR3 Spos,	//�X�^�[�g�|�W�V����
	D3DXVECTOR3 Epos,	//�L�у|�W�V����
	float Texture_Size_x)
{
	// ���_���W�̐ݒ�
	g_vertexWk[0].vtx = D3DXVECTOR3(Spos.x - Texture_Size_x / 2, Spos.y, Spos.z);
	g_vertexWk[1].vtx = D3DXVECTOR3(Spos.x + Texture_Size_x / 2, Spos.y, Spos.z);
	g_vertexWk[2].vtx = D3DXVECTOR3(Epos.x - Texture_Size_x / 2, Epos.y, Spos.z);
	g_vertexWk[3].vtx = D3DXVECTOR3(Epos.x + Texture_Size_x / 2, Epos.y, Spos.z);
}

//=============================================================================
// ���_���W�̐ݒ� �Q�_�ŐL�яk����ꍇ�@//���������ꌻ���UI�̂ݎg��
//�c�̂�
//=============================================================================

void SetHorizoneVeticalSpread(VERTEX_2D *g_vertexWk,
	D3DXVECTOR3 Spos,	//�X�^�[�g�|�W�V����
	D3DXVECTOR3 Epos,	
	float Texture_Size_y)
{
	// ���_���W�̐ݒ�
	g_vertexWk[0].vtx = D3DXVECTOR3(Spos.x, Spos.y - Texture_Size_y / 2, Spos.z);
	g_vertexWk[1].vtx = D3DXVECTOR3(Epos.x, Spos.y - Texture_Size_y / 2, Spos.z);
	g_vertexWk[2].vtx = D3DXVECTOR3(Spos.x, Epos.y + Texture_Size_y / 2, Spos.z);
	g_vertexWk[3].vtx = D3DXVECTOR3(Epos.x, Epos.y + Texture_Size_y / 2, Spos.z);
}

//=============================================================================
// ���_���W�̐ݒ�	������t��������ꍇ
//=============================================================================
void SetVertex(VERTEX_2D *g_vertexWk,
	D3DXVECTOR3 pos,
	float Texture_Size_x,
	float Texture_Size_y,
	float baseAngle,
	float rotation)
{
	D3DXVECTOR3 tempVec3= D3DXVECTOR3(Texture_Size_x / 2, Texture_Size_y / 2, 0);

	double TempLen= D3DXVec3Length(&tempVec3);

	D3DXVECTOR3 TempD3 = D3DXVECTOR3(0, 0, 0);
	D3DXVECTOR3 MoveD3 = D3DXVECTOR3(0, 0, 0);

	//////�O�p�֐��̉��@�藝
	TempD3.x = pos.x - cosf(baseAngle+ rotation) *TempLen;
	TempD3.y = pos.y - sinf(baseAngle + rotation) * TempLen;
	g_vertexWk[0].vtx = D3DXVECTOR3(TempD3.x, TempD3.y, pos.z);

	TempD3.x = pos.x + cosf(baseAngle - rotation) * TempLen;
	TempD3.y = pos.y - sinf(baseAngle - rotation) * TempLen;
	g_vertexWk[1].vtx = D3DXVECTOR3(TempD3.x, TempD3.y, pos.z) ;
	
	TempD3.x = pos.x - cosf(baseAngle - rotation) * TempLen;
	TempD3.y = pos.y + sinf(baseAngle - rotation) * TempLen;
	g_vertexWk[2].vtx = D3DXVECTOR3(TempD3.x, TempD3.y, pos.z) ;

	TempD3.x = pos.x + cosf(baseAngle + rotation) * TempLen;
	TempD3.y = pos.y + sinf(baseAngle + rotation) * TempLen;
	g_vertexWk[3].vtx = D3DXVECTOR3(TempD3.x, TempD3.y, pos.z) ;

	}


//=============================================================================
// ���_���W�̐ݒ�	������t��������ꍇ �Q�_�ŐL�яk����ꍇ
//=============================================================================
void SetVertexVeticalSpread(VERTEX_2D *g_vertexWk,
	D3DXVECTOR3 Spos,	//�X�^�[�g�|�W�V����
	D3DXVECTOR3 Epos,	//�L�у|�W�V����
	float Texture_Size_x, //����
	float Texture_Size_y,
	float baseAngle,
	float rotation)
{



	D3DXVECTOR3 tempVec3 = D3DXVECTOR3(Texture_Size_x / 2, Texture_Size_y / 2, 0);

	double TempLen = D3DXVec3Length(&tempVec3);

	D3DXVECTOR3 TempD3 = D3DXVECTOR3(0, 0, 0);
	D3DXVECTOR3 MoveD3 = D3DXVECTOR3(0, 0, 0);

	//////�O�p�֐��̉��@�藝
	
	TempD3.x = Epos.x - cosf(baseAngle + rotation) * TempLen;
	TempD3.y = Epos.y - sinf(baseAngle + rotation) * TempLen;
	g_vertexWk[0].vtx = D3DXVECTOR3(TempD3.x, TempD3.y, Spos.z);

	TempD3.x = Epos.x + cosf(baseAngle - rotation) * TempLen;
	TempD3.y = Epos.y - sinf(baseAngle - rotation) * TempLen;
	g_vertexWk[1].vtx = D3DXVECTOR3(TempD3.x, TempD3.y, Spos.z);

	TempD3.x = Spos.x - cosf(baseAngle - rotation) * TempLen;
	TempD3.y = Spos.y + sinf(baseAngle - rotation) * TempLen;
	g_vertexWk[2].vtx = D3DXVECTOR3(TempD3.x, TempD3.y, Epos.z);

	TempD3.x = Spos.x + cosf(baseAngle + rotation) * TempLen;
	TempD3.y = Spos.y + sinf(baseAngle + rotation) * TempLen;
	g_vertexWk[3].vtx = D3DXVECTOR3(TempD3.x, TempD3.y, Epos.z);

}




//�Q�̃x�N�g��AB�̂Ȃ��p�x�Ƃ����߂�
double AngleOf2Vector(D3DXVECTOR3 A, D3DXVECTOR3 B)
{
	//�@���x�N�g���̒�����0���Ɠ������o�܂���̂Œ��ӂ��Ă��������B

	//�x�N�g��A��B�̒������v�Z����
	double length_A = D3DXVec3Length(&A);
	double length_B = D3DXVec3Length(&B);

	//���ςƃx�N�g���������g����cos�Ƃ����߂�
	double cos_sita = D3DXVec3Dot(&A, &B) / (length_A * length_B);

	//cos�Ƃ���Ƃ����߂�
	double sita = acos(cos_sita);

	//���W�A���łȂ�0�`180�̊p�x�łق����ꍇ�̓R�����g�O��
	//sita = sita * 180.0 / PI;

	return sita;
}
D3DXVECTOR3 Vec3Normalize(D3DXVECTOR3 *pV)
{
	double len;
	double x, y, z;

	x = (double)(pV->x);
	y = (double)(pV->y);
	z = (double)(pV->z);
	len = sqrt(x * x + y * y + z * z);

	if (len < (1e-6)) return D3DXVECTOR3(0, 0, 0);

	len = 1.0 / len;
	x *= len;
	y *= len;
	z *= len;
	return D3DXVECTOR3((float)x, (float)y, (float)z);
}


//�e�֐�Init���Ɏg�p
void SetTextureDATA(
	LPDIRECT3DDEVICE9 pDevice,
	VERTEX_2D *g_vertexWk,
	Texture_DATA *texture,		//�Z�b�g����e�N�X�`���[�f�[�^
	const Texture_DATA *InitTexture	//�Z�b�g����l
	)
{
	//������
	*texture =
		*InitTexture;

	//�����p�x�̊i�[
	texture->BaseAngle =
		atan2f(texture->Size_y, texture->Size_x);

	//���_���W�̐ݒ�
	MakeVertex(g_vertexWk);

	if (texture->IsEnableDivide)
	{
		SetTexture(g_vertexWk,
			texture->Divide_x,
			texture->Divide_y,
			texture->TextureNumber);
	}
	else
	{
		SetTexture(g_vertexWk,
			texture->Divide_x,
			texture->Divide_y);
	}


	//�ꏊ����
	SetVertex(g_vertexWk,
		texture->Pos,
		texture->Size_x,
		texture->Size_y);

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
		texture->Path,				// �t�@�C���̖��O
		&texture->pD3DTexture);					// �ǂݍ��ރ������̃|�C���^
															//���_���W�����i�[
	texture->Vertex = g_vertexWk;
}

//�e�֐�UnInit���Ɏg�p
void UnLoadTextureDATA(
	Texture_DATA *texture		//�A�����[�h����e�N�X�`���[�f�[�^
	)
{
	if (texture->pD3DTexture != NULL)
	{	// �e�N�X�`���̊J��
		texture->pD3DTexture->Release();
		texture->pD3DTexture = NULL;
	}
}


//�e�֐�Draw���Ɏg�p
void DrawTextureDATA(
	LPDIRECT3DDEVICE9 pDevice,
	Texture_DATA *texture		//Draw����e�N�X�`���[�f�[�^
	)
{
	//�L���t���O��ON����Ȃ���Ή������Ȃ�
	if (texture->IsEnable == false)
		return;

	//�����p�x�̊i�[
	texture->BaseAngle =atan2f(texture->Size_y, texture->Size_x);
	//�F�ݒ�
	MakeVertex(texture->Vertex, texture->Color);

	//���_���W�Z�b�g
	if (texture->IsEnableRotation)
	{
		SetVertex(texture->Vertex,
			texture->Pos,
			texture->Size_x,
			texture->Size_y,
			texture->BaseAngle,
			texture->Angle);

	}
	else
	{
		SetVertex(texture->Vertex,
			texture->Pos,
			texture->Size_x,
			texture->Size_y);
	}

	if (texture->IsEnableDivide)
	{
		SetTexture(texture->Vertex,
			texture->Divide_x,
			texture->Divide_y,
			texture->TextureNumber);
	}
	else
	{
		SetTexture(texture->Vertex,
			texture->Divide_x,
			texture->Divide_y);
	}

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, texture->pD3DTexture);
	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_PLAYER, texture->Vertex, sizeof(VERTEX_2D));

}