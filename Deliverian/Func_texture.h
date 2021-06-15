//=============================================================================
//
// ���ʏ��� [Func_texture.h]
// Author : 
//
//=============================================================================

#pragma once
#include"main.h"
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertex(VERTEX_2D*);

HRESULT MakeVertex(VERTEX_2D*, D3DXVECTOR4 color);

void SetTexture(VERTEX_2D*,
				int Texture_Divide_x,
				int Texture_Divide_y);

//�I�[�o�[���[�h�A�e�N�`���[���������Ă���ꍇ
void SetTexture(VERTEX_2D*,
	int Texture_Divide_x,
	int Texture_Divide_y,
	int Texture_Number);	//�������ڂ��g����

void SetVertex(VERTEX_2D*,
					D3DXVECTOR3 pos,
					float Texture_Size_x,
					float Texture_Size_y);

//�I�[�o�[���[�h�A������t��������ꍇ
void SetVertex(VERTEX_2D*,
	D3DXVECTOR3 pos,
	float Texture_Size_x,
	float Texture_Size_y,
	float baseAngle,
	float rotation
	);

//�c�ɐL�яk����
void SetVertexVeticalSpread(VERTEX_2D *g_vertexWk,
	D3DXVECTOR3 Spos,	//�X�^�[�g�|�W�V����
	D3DXVECTOR3 Epos,	//�L�у|�W�V����
	float Texture_Size_x);

//�c�ɐL�яk����
void SetHorizoneVeticalSpread(VERTEX_2D *g_vertexWk,
	D3DXVECTOR3 Spos,	//�X�^�[�g�|�W�V����
	D3DXVECTOR3 Epos,	//�L�т�T�C�Y
	float Texture_Size_y);

//�����t��
void SetVertexVeticalSpread(VERTEX_2D *g_vertexWk,
	D3DXVECTOR3 Spos,	//�X�^�[�g�|�W�V����
	D3DXVECTOR3 Epos,	//�L�у|�W�V����
	float Texture_Size_x, //����
	float Texture_Size_y,
	float baseAngle,
	float rotation);


//�x�N�g���̐��K��
D3DXVECTOR3 Vec3Normalize(D3DXVECTOR3 *pV);

//2�̃x�N�g������p�x�����߂�
double AngleOf2Vector(D3DXVECTOR3 A, D3DXVECTOR3 B);

//�e�N�X�`���[�f�[�^�̃Z�b�g
void SetTextureDATA(
	LPDIRECT3DDEVICE9 pDevice,
	VERTEX_2D *g_vertexWk,
	Texture_DATA *texture,		//�Z�b�g����e�N�X�`���[�f�[�^
	const Texture_DATA *InitTexture	//�Z�b�g����l
	);

//�e�N�X�`���[�f�[�^�̃A�����[�h
void UnLoadTextureDATA(
	Texture_DATA *texture		//�A�����[�h����e�N�X�`���[�f�[�^
);


//�e�N�X�`���[�f�[�^�̕`��
void DrawTextureDATA(
	LPDIRECT3DDEVICE9 pDevice,
	Texture_DATA *texture		//Draw����e�N�X�`���[�f�[�^
);