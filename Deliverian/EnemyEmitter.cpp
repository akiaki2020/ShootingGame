//�C���N���[�h����ۂ�MAIN.h����ԏ�ɂ��邱��
#include "Main.h"
#include "Enemy.h"
#include "EnemyEmitter.h"
static float g_Size;//�~�`��s�p�̊p�x�@�����搶�͂���ĂȂ���

void EnemyEmitter(D3DXVECTOR3 pos, D3DXVECTOR3 dir, int EnemyType, D3DXVECTOR3 size,int Emitt_type) {
	//�G�̍s�Ԃ͋@�̖{�ԋ󂯂�
	//�����̏ꍇ�͋󂫃X�y�[�X��^�񒆂�
	//��̏ꍇ�͋@�̂�^�񒆂ɂ���
	D3DXVECTOR3 Space = size / 2;
	D3DXVECTOR3 Space_2 = size / 4;
	D3DXVECTOR3 TempPos= D3DXVECTOR3(0,0,0);
	switch (Emitt_type)
	{
	ONE:
		SetEnemy(pos, dir, EnemyType);
		break;
	DOUBLE_HOLIZNE:
		TempPos.x = pos.x - size.x- Space_2.x;
		SetEnemy(TempPos, dir, EnemyType);
		TempPos.x = pos.x + size.x + Space_2.x;
		SetEnemy(TempPos, dir, EnemyType);
		break;
	DOUBLE_VERTICAL:
		TempPos.y = pos.y - size.y - Space_2.y;
		SetEnemy(TempPos, dir, EnemyType);
		TempPos.y = pos.y + size.y + Space_2.y;
		SetEnemy(TempPos, dir, EnemyType);
		break;
	THREE_HOLZNE:
		break;
	THREE_VERTICAL:
		break;
	THREE_TRIANGLE:
		break;
	THREE_TRIANGLE_R:
		break;
	FOUR_HOLIZNE:
		break;
	FOUR_VERTICAL:
		break;
	PENTA:
		break;
	CIRCLE:
		break;
	default:
		break;
	}
//	SetEnemy(tblEnemy[g_EmitCount].pos, tblEnemy[g_EmitCount].dir);
}

void EnemyEmitter(D3DXVECTOR3 pos, D3DXVECTOR3 dir, int EnemyType, int Emitt_type) {
	//�G�̃^�C�v����X�e�[�^�X���擾
	ENEMY ENEMY = GetEnemyTbl(EnemyType);
	D3DXVECTOR3 size = ENEMY.size;
	//�G�̍s�Ԃ͋@�̖{�ԋ󂯂�
	//�����̏ꍇ�͋󂫃X�y�[�X��^�񒆂�
	//��̏ꍇ�͋@�̂�^�񒆂ɂ���
	D3DXVECTOR3 Space = size / 2;
	D3DXVECTOR3 Space_2 = size / 4;
	D3DXVECTOR3 TempPos = D3DXVECTOR3(0, 0, 0);
	switch (Emitt_type)
	{
	case ONE:
		SetEnemy(pos, dir, EnemyType);
		break;
	case DOUBLE_HOLIZNE:
		TempPos.x = pos.x - size.x - Space_2.x;
		TempPos.y = pos.y;
		SetEnemy(TempPos, dir, EnemyType);
		TempPos.x = pos.x + size.x + Space_2.x;
		SetEnemy(TempPos, dir, EnemyType);
		break;
	case DOUBLE_VERTICAL:
		TempPos.x = pos.x;
		TempPos.y = pos.y - size.y - Space_2.y;
		SetEnemy(TempPos, dir, EnemyType);
		TempPos.y = pos.y + size.y + Space_2.y;
		SetEnemy(TempPos, dir, EnemyType);
		break;
	case THREE_HOLIZNE:
		TempPos.x = pos.x - size.x*2;
		TempPos.y = pos.y;
		SetEnemy(TempPos, dir, EnemyType);
		TempPos.x = pos.x;
		SetEnemy(TempPos, dir, EnemyType);
		TempPos.x = pos.x + size.x * 2;
		SetEnemy(TempPos, dir, EnemyType);
		break;
	case THREE_VERTICAL:
		break;
	case THREE_TRIANGLE:
		break;
	case THREE_TRIANGLE_R:
		break;
	case FOUR_HOLIZNE:
		break;
	case FOUR_VERTICAL:
		break;
	case PENTA:
		break;
	case CIRCLE:
		break;
	default:
		break;
	}
	
}


