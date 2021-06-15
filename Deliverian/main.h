//=============================================================================
//
// Main�w�b�_�[ [main.h]
// Author : 
//
//=============================================================================
#ifndef _MAIN_H_
#define _MAIN_H_

#define _CRT_SECURE_NO_WARNINGS			// scanf ��warning�h�~

#include "windows.h"
#include "d3dx9.h"
#include <tchar.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DIRECTINPUT_VERSION 0x0800		// �x���Ώ�
#include "dinput.h"
#include "mmsystem.h"

#if 1	// [������"0"�ɂ����ꍇ�A"�\���v���p�e�B" -> "�����J" -> "����" -> "�ǉ��̈ˑ��t�@�C��"�ɑΏۃ��C�u������ݒ肷��]
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "winmm.lib")
#endif

#define SCREEN_GAME_WIDTH	(500)			// UI���k�߂��E�C���h�E�̕�
#define SCREEN_GAME_HEIGHT	(480)			// UI���k�߂��E�C���h�E�̍���
#define SCREEN_WIDTH	(640)				// �E�C���h�E�̕�
#define SCREEN_HEIGHT	(480)				// �E�C���h�E�̍���
#define SCREEN_CENTER_X	(SCREEN_WIDTH / 2)	// �E�C���h�E�̒��S�w���W
#define SCREEN_CENTER_Y	(SCREEN_HEIGHT / 2)	// �E�C���h�E�̒��S�x���W

#define NON_DIVIDE 1//�e�N�X�`���[�������Ȃ��Ƃ�
#define NON_DIVIDE_TEXTURENUMBER 0//�����g�p�����ۂ̃e�N�X�`���[�ԍ�



#define	NUM_VERTEX		(4)					// ���_��
#define	NUM_PLAYER		(2)					// �|���S����

// ���_�t�H�[�}�b�g( ���_���W[2D] / ���ˌ� / �e�N�X�`�����W )
#define	FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)

// ��L���_�t�H�[�}�b�g�ɍ��킹���\���̂��`
typedef struct
{
	D3DXVECTOR3 vtx;		// ���_���W
	float rhw;				// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	D3DCOLOR diffuse;		// ���ˌ�
	D3DXVECTOR2 tex;		// �e�N�X�`�����W
} VERTEX_2D;

//�e�N�X�`���p�̍\����
typedef struct
{
	char * Path;		// �i�[�ꏊ
	LPDIRECT3DTEXTURE9 pD3DTexture;//�e�N�X�`���i�[�ꏊ
	VERTEX_2D* Vertex;//���_���W
	D3DXVECTOR3 Pos;	//�ꏊ
	float Size_x;				// �T�C�YX
	float Size_y;			// �T�C�YY
	bool IsEnable;			//�\��
	float Angle;			//�p�x
	float BaseAngle;	//�����p�x
	bool IsEnableRotation; //��]���ďo����
	int Divide_x;			//������_x
	int Divide_y;			//������_y
	int TextureNumber;		//�e�N�X�`���[�ԍ�	
	bool IsEnableDivide;	//�e�N�X�`������������Ă��邩�H
	D3DXVECTOR4 Color;//�e�N�X�`���[�J���[

} Texture_DATA;




LPDIRECT3DDEVICE9 GetDevice(void);		// �f�o�C�X�擾�֐�


#endif