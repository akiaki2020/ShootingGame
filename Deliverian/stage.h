//=============================================================================
//
// ���� [stage.h]
// Author : 
//
//=============================================================================
#pragma once

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define STAGE_NAME					32	//�X�e�[�W�̃}�b�N�X��
#define STAGE_MAX_ENEMYGROUP		999	//�X�e�[�W�̍ő�G�O���[�v�̏o����

enum STAGE_TYPE
{
	SKY,
	SPACE,
	ASTEROID,
	MAX_STAGE_TYPE
};

typedef struct
{
	enum STAGE_TYPE stage_type;		//�X�e�[�W�̃^�C�v
	float flame;				//�o�߃t���[��
	int	  EnemyPop;				//�G�̏o����
	float NormalEndflame;		//�I���t���[��
	enum BOSS_TYPE boss_type;
	char	StageName[STAGE_NAME];

	int	  int1;				//�n�C�X�R�A	
	int	  int2;
	int	  int3;
	int	  int4;

	float flt1;					//1�ϐ�
	float flt2;					//2�ϐ�
	float flt3;					//3�ϐ�
	float flt4;					//4�ϐ�
}STAGE;


//***************************BG**************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitStage();
void SetStage(STAGE_TYPE stagetype);

void UpdateStage();

void SetStageHighScore(int stage_type, int HighScore);

STAGE GetStageData(int stage_type);

//�ȉ���Ui.cpp�̂ݎg�p���邱��
float GetStagetime();
STAGE GetCurrentStageData();
