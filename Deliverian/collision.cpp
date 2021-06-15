//=============================================================================
//
// �����蔻�菈�� [collision.cpp]
// Author : �H�{
//�ڐG����ƁA�ڐG��ǂ̊֐����ĂԂ��L�q
//=============================================================================

#include "collision.h"
#include "player.h"
#include "enemy.h"
#include "bullet.h"
#include "Blade.h"
#include "boss.h"
#include "enemy_laser.h"
#include "Func_texture.h"
//#include "number.h"
//#include "explosion.h"




//�e�ƃv���C���[�E�G�̓����蔻��
void PlayerHitEnemyCheck(PLAYER_DATA *player, ENEMY* enemy);
void BulletHitEnemyCheck(PLAYER_DATA *player,ENEMY* enemy,BULLET* bullet);
void BulletHitPlayerCheck(PLAYER_DATA *player, BULLET* bullet);
void BladeHitEnemyCheck(PLAYER_DATA *player, ENEMY* enemy, BLADE* bullet);
void BladeHitPlayerCheck(PLAYER_DATA *player,BLADE* bullet);
void LaserHitEnemyCheck(PLAYER_DATA *player, ENEMY* enemy, LASER* laser);
void LaserHitPlayerCheck(PLAYER_DATA *player, LASER* laser);



//�~�̓����蔻��
bool HitCheckBC(D3DXVECTOR3 pos1, float size1,
	D3DXVECTOR3 pos2, float size2);

//�L���[�u�̓����蔻��
bool HitCheckBB(D3DXVECTOR3 pos1, D3DXVECTOR3 size1,
	 D3DXVECTOR3 pos2,  D3DXVECTOR3 size2);

bool HitCheckCupsule(const CIRCLE* p_circle, const CAPSULE* p_cupsule);

bool HitCheckTyouhoukei(const CIRCLE* p_circle, const CAPSULE* p_cupsule);


//game.cpp�݂̂ŌĂ�
void HitCheck() {
	//�v���C���[�ƃG�l�~�[�ƒe�̃|�C���^���Ƃ�
	PLAYER_DATA* pPlayer = GetPlayer();
	ENEMY* pEnemy = GetEnemy();
	BULLET* pBullet = GetBullet();
	BLADE* pBlade = GetBlade();
	ENEMY* pBoss= GetBoss();
	LASER* pLaser = GetEnemyLaser();


	//�����ƓG�Ƃ̓����蔻��
	PlayerHitEnemyCheck(pPlayer,pBoss);
	for (int i = 0; i < MAX_ENEMY; i++)
	{
		PlayerHitEnemyCheck(pPlayer, &pEnemy[i]);
	}

	//�e�ƓG�̓����蔻��
	for (int i_B = 0; i_B < MAX_BULLET; i_B++) {
		//�L�������Ă��Ȃ��e�̓X���[
		if (pBullet[i_B].isEnable == false)
			continue;
		BulletHitPlayerCheck(pPlayer, &pBullet[i_B]);
		BulletHitEnemyCheck(pPlayer, pBoss, &pBullet[i_B]);
		for (int i = 0; i < MAX_ENEMY; i++)
		{
			if (pEnemy[i].isEnable) 
			{
				BulletHitEnemyCheck(pPlayer, &pEnemy[i], &pBullet[i_B]);
			}
			
		}
	}

	//���ƓG�̓����蔻��
	for (int i_B = 0; i_B < MAX_BLADE; i_B++) {

		//�L�������Ă��Ȃ��e�̓X���[
		if (pBlade[i_B].isEnable == false)
			continue;
		BladeHitPlayerCheck(pPlayer, &pBlade[i_B]);
		BladeHitEnemyCheck(pPlayer, pBoss, &pBlade[i_B]);
		for (int i = 0; i < MAX_ENEMY; i++)
		{
			BladeHitEnemyCheck(pPlayer, &pEnemy[i], &pBlade[i_B]);
		}
	}

	//���[�U�[�Ƃ̓����蔻��
	for (int i_l = 0; i_l < MAX_LASER; i_l++) {

		//�L�������Ă��Ȃ��e�̓X���[
		if (pLaser[i_l].isEnable == false)
			continue;
		LaserHitPlayerCheck(pPlayer, &pLaser[i_l]);
		LaserHitEnemyCheck(pPlayer, pBoss, &pLaser[i_l]);
		for (int i = 0; i < MAX_ENEMY; i++)
		{
			LaserHitEnemyCheck(pPlayer, &pEnemy[i], &pLaser[i_l]);
		}
	}

	
}

void PlayerHitEnemyCheck(PLAYER_DATA *player, ENEMY* enemy)
{
	//�L�������Ă��Ȃ��G�̓X���[
	if (enemy->isEnable == false)
		return;

	//�v���C���[�����G�̂Ƃ��̓X���[
	if (player->State == PLAYER_STATE_MUTEKI)
		return;

	//�q�b�g���Ă��邩���`�F�b�N����
	D3DXVECTOR3 size1 = D3DXVECTOR3(player->size.x / 2, player->size.y / 2, 0);
	D3DXVECTOR3 size2 = D3DXVECTOR3(enemy->size.x / 2, enemy->size.y / 2, 0);
	float size1_len = D3DXVec3Length(&size1);
	float size2_len = D3DXVec3Length(&size1);

	//�v���C���[�̍��W�ƃT�C�Y�i���A�����j��
	//�G�l�~�[�̍��W�ƃT�C�Y�������œn��
	if (HitCheckBC(player->pos, size1_len,
		enemy->pos, size2_len))
	{
		//�v���C���[HP�����炷
		PlusPlayerHp(-enemy->Power);
		//���G��Ԃɂ���
		ChangePlayerState(PLAYER_STATE_MUTEKI);
	}
}

//�e�ƓG�̓����蔻��
void BulletHitEnemyCheck(PLAYER_DATA *player, ENEMY* enemy, BULLET* bullet) {

	//�L�������Ă��Ȃ��e�̓X���[
	if (bullet->isEnable == false)
		return;
	if (enemy->isEnable == false)
		return;

	D3DXVECTOR3 size1 = D3DXVECTOR3(0, 0, 0);
	D3DXVECTOR3 size2 = D3DXVECTOR3(0, 0, 0);
	float size1_len = 0.0f;
	float size2_len = 0.0f;
	switch (bullet->Affiliation)
	{
	case PLAYERS_BULLET:
			//�G�̗L���t���O���`�F�b�N
			//�L�������Ă��Ȃ��G�̓X���[
			//���G��ԂȂ画�肵�Ȃ�
			if (enemy->Enemy_Mutekiflg) {
				return;
			}
			//�q�b�g���Ă��邩���`�F�b�N����i�{�b�N�X�Łj
			 size1 = D3DXVECTOR3(bullet->size.x / 2, bullet->size.y /2, 0);
			 size2 = D3DXVECTOR3(enemy->size.x / 2, enemy->size.y / 2, 0);
			 size1_len = D3DXVec3Length(&size1);
			 size2_len = D3DXVec3Length(&size1);

			if (HitCheckBC(bullet->pos, size1_len,
				enemy->pos, size2_len))
			{
				//�L���t���O��OFF�ɂ��Ēe�������I
				bullet->isEnable = false;
				//�L���t���O��OFF�ɂ��ēG�������I
				//enemy->isEnable = false;
				PlusEnemyHp(enemy, -1*player->Power);
				ChangeEnemyState(enemy, ENEMY_STATE_DAMAGE);

				//�_����ǉ�
				//PlusPlayerScore(2);
				//�G�t�F�N�g�̒ǉ�
				//	SetExplosion(pEnemy->pos);
			}	
		break;
	case ENEMYS_BULLET:
		break;
	default:

		break;
	}
	return;
}

//�e�ƃv���C���[�̓����蔻��
void BulletHitPlayerCheck(PLAYER_DATA *player, BULLET* bullet) {

	//�L�������Ă��Ȃ��e�̓X���[
	if (bullet->isEnable == false)
		return;

	D3DXVECTOR3 size1 = D3DXVECTOR3(0, 0, 0);
	D3DXVECTOR3 size2 = D3DXVECTOR3(0, 0, 0);
	float size1_len = 0.0f;
	float size2_len = 0.0f;

	switch (bullet->Affiliation)
	{
	case PLAYERS_BULLET:
		break;
	case ENEMYS_BULLET:
		//�v���C���[�����G�̂Ƃ��̓X���[
		if (player->State == PLAYER_STATE_MUTEKI)
			return;

		//�q�b�g���Ă��邩���`�F�b�N����i�{�b�N�X�Łj
		size1 = D3DXVECTOR3(bullet->size.x / 2, bullet->size.y / 2, 0);
		size2 = D3DXVECTOR3(player->size.x / 2, player->size.y / 2, 0);
		size1_len = D3DXVec3Length(&size1);
		size2_len = D3DXVec3Length(&size1);

		if (HitCheckBC(bullet->pos, size1_len,
			player->pos, size2_len))
		{
			//�v���C���[HP�����炷
			PlusPlayerHp(-(bullet->power));
			//���G��Ԃɂ���
			ChangePlayerState(PLAYER_STATE_MUTEKI);
		}
		break;
	default:

		break;
	}
	return;
}

//���ƓG�̓����蔻��
void BladeHitEnemyCheck(PLAYER_DATA *player, ENEMY* enemy, BLADE* blade) {

	//�L�������Ă��Ȃ��e�̓X���[
	if (blade->isEnable == false)
		return;
	//�L�������Ă��Ȃ��G�̓X���[
	if (enemy->isEnable == false)
		return;
	//���G��ԂȂ画�肵�Ȃ�
	if (enemy->Enemy_Mutekiflg) {
		return;
	}

	D3DXVECTOR3 tempdir;
	//WAIT_ROTATION�Ŏg�p
	//�G�̒��S���W
	D3DXVECTOR3 center;
	//�v���C���[�̍��W���擾����
	D3DXVECTOR3 pl_pos;
	//�G�ƃv���C���[�̋������v�Z����
	D3DXVECTOR3 vLen;
	float length;
	switch (blade->Affiliation)
	{
	case PLAYERS_BLADE:
		//���̃x�N�g���擾
		tempdir = D3DXVECTOR3(sinf(blade->Rotation), -cosf(blade->Rotation), 0);
		D3DXVec3Normalize(&tempdir, &tempdir);

		//���̍��W���擾����
		pl_pos = D3DXVECTOR3(blade->pos.x, blade->pos.y, blade->pos.z);

		//�G�ƃv���C���[�̋������v�Z����
		vLen = enemy->pos - pl_pos;

		length = D3DXVec3Length(&vLen);

		//���肷�鋗���̒��ɓ����Ă��邩���`�F�b�N����
		if (length < BLADE_HEIGHT)
		{
			//�G���猩�ăv���C���[�̍��W�ւ̕����x�N�g�������
			D3DXVECTOR3 pl_dir = enemy->pos -pl_pos;
			D3DXVec3Normalize(&pl_dir, &pl_dir);

			//�G�̌����ƃv���C�����W�ւ̕����x�N�g���œ��ς����
			float dot = D3DXVec3Dot(&tempdir, &pl_dir);

			//���肷��p�x���ɓ����Ă��邩���`�F�b�N����
			if (dot > BLADE_ANGLE)
			{
				//enemy->isEnable = false;
				PlusEnemyHp(enemy, -1 * player->Power*PLAYER_BLADE_BAIRITU);
				ChangeEnemyState(enemy, ENEMY_STATE_DAMAGE);
			}
		}

		break;
	case ENEMYS_BLADE:
		break;
	default:

		break;
	}
	return;
}

//���ƃv���C���[�̓����蔻��
void BladeHitPlayerCheck(PLAYER_DATA *player, BLADE* blade) {

	D3DXVECTOR3 tempdir;

	//WAIT_ROTATION�Ŏg�p
	//�v���C���[�̍��W���擾����
	D3DXVECTOR3 pl_pos;

	//�G�̒��S���W
	D3DXVECTOR3 center;

	//�G�ƃv���C���[�̋������v�Z����
	D3DXVECTOR3 vLen;
	float length;

	//�L�������Ă��Ȃ��e�̓X���[
	if (blade->isEnable == false)
		return;

	switch (blade->Affiliation)
	{
	case PLAYERS_BLADE:
		break;
	case ENEMYS_BLADE:
		//�v���C���[�����G�̂Ƃ��̓X���[
		//if (player->State == PLAYER_STATE_MUTEKI)
		//	return;
		//tempdir = D3DXVECTOR3(sinf(blade->Rotation), -cosf(blade->Rotation), 0);
		////�v���C���[�̍��W���擾����
		//pl_pos = D3DXVECTOR3(blade->pos.x, blade->pos.y, blade->pos.z);

		////�G�ƃv���C���[�̋������v�Z����
		//vLen = enemy->pos - pl_pos;

		//length = D3DXVec3Length(&vLen);

		////���肷�鋗���̒��ɓ����Ă��邩���`�F�b�N����
		//if (length < BLADE_LENGTH)
		//{
		//	//�G���猩�ăv���C���[�̍��W�ւ̕����x�N�g�������
		//	D3DXVECTOR3 pl_dir = pl_pos - enemy->pos;
		//	D3DXVec3Normalize(&pl_dir, &pl_dir);

		//	//�G�̌����ƃv���C�����W�ւ̕����x�N�g���œ��ς����
		//	float dot = D3DXVec3Dot(&tempdir, &pl_dir);
		//	//���肷��p�x���ɓ����Ă��邩���`�F�b�N����
		//	if (dot > 0.85f)
		//	{
		//		//�v���C���[HP�����炷
		//		PlusPlayerHp(-1);
		//		//���G��Ԃɂ���
		//		ChangePlayerState(PLAYER_STATE_MUTEKI);
		//	}
		//}
		break;
	default:
		break;
	}
	return;
}

//���[�U�[�ƓG�̓����蔻��
void LaserHitEnemyCheck(PLAYER_DATA *player, ENEMY* enemy, LASER* laser) {

	//�L�������Ă��Ȃ��e�̓X���[
	if (laser->isEnable == false)
		return;
	//�L�������Ă��Ȃ��G�̓X���[
	if (enemy->isEnable == false)
		return;
	//���G��ԂȂ画�肵�Ȃ�
	if (enemy->Enemy_Mutekiflg) {
		return;
	}

	D3DXVECTOR3 tempdir;
	CAPSULE CAPSULE;
	CIRCLE CIRCLE;

	switch (laser->Affiliation)
	{
	case PLAYERS_BLADE:
		//�T�[�N���Ɋi�[
		CIRCLE.cx = enemy->pos.x;
		CIRCLE.cy = enemy->pos.y;
		tempdir = D3DXVECTOR3(enemy->size.x / 2, enemy->size.y / 2, 0);
		CIRCLE.r = D3DXVec3Length(&tempdir);;

		//�J�v�Z���Ƀ��[�U�[���i�[
		CAPSULE.x = laser->s_pos.x;
		CAPSULE.y = laser->s_pos.y;
		CAPSULE.ex = laser->pos.x;
		CAPSULE.ey = laser->pos.y;
		CAPSULE.r = laser->Futosa/2;

		//�v���C���[�̍��W�ƃT�C�Y�i���A�����j��
		//�G�l�~�[�̍��W�ƃT�C�Y�������œn��
		if (HitCheckCupsule(&CIRCLE, &CAPSULE))
		{
			PlusEnemyHp(enemy, -1 * player->Power);
			ChangeEnemyState(enemy, ENEMY_STATE_DAMAGE);
		}

		break;
	case ENEMYS_BLADE:
		break;
	default:

		break;
	}
	return;
}

//���[�U�[�ƃv���C���[�̓����蔻��
void LaserHitPlayerCheck(PLAYER_DATA *player, LASER* laser)
{
	//�L�������Ă��Ȃ��e�̓X���[
	if (laser->isEnable == false)
		return;
	//�v���C���[�����G�̂Ƃ��̓X���[
	if (player->State == PLAYER_STATE_MUTEKI)
		return;

	D3DXVECTOR3 tempdir;
	CAPSULE CAPSULE;
	CIRCLE CIRCLE;

	switch (laser->Affiliation)
	{
	case PLAYERS_BLADE:
		break;
	case ENEMYS_BLADE:

		//�T�[�N���Ɋi�[
		CIRCLE.cx = player->pos.x;
		CIRCLE.cy = player->pos.y;
		tempdir = D3DXVECTOR3(player->size.x / 2, player->size.y / 2, 0);
		CIRCLE.r = D3DXVec3Length(&tempdir);;

		//�J�v�Z���Ƀ��[�U�[���i�[
		CAPSULE.x = laser->s_pos.x;
		CAPSULE.y = laser->s_pos.y;
		CAPSULE.ex = laser->pos.x;
		CAPSULE.ey = laser->pos.y;
		CAPSULE.r = laser->Futosa/2;

		//�v���C���[�̍��W�ƃT�C�Y�i���A�����j��
		//�G�l�~�[�̍��W�ƃT�C�Y�������œn��
		if (HitCheckCupsule(&CIRCLE, &CAPSULE))
		{
			//�v���C���[HP�����炷
			PlusPlayerHp(-laser->power);
			//���G��Ԃɂ���
			ChangePlayerState(PLAYER_STATE_MUTEKI);
		}

		break;
	default:
		break;
	}
	return;
}


//�~�^�̓����蔻��
bool HitCheckBC( D3DXVECTOR3 pos1, float size1,
	 D3DXVECTOR3 pos2, float size2)
{
	//pos1��pos2�̋����̃x�N�g��
	 D3DXVECTOR3 distance;
	distance = pos1 - pos2;

	//distance�̃x�N�g�������v�Z����
	float length = 0.0f;
	length = D3DXVec3Length(&distance);
	//�����蔻����Ƃ镨��2�̔��a�𑫂�
	float w = size1 + size2;

	//�����̂ق����Z����΃q�b�g���Ă���
	if (length < w)
		return true;
	else
		return false;
}

//BOX�̓����蔻��
//POS�̓_�̓e�N�X�`���[�̍���
bool HitCheckBB( 
	D3DXVECTOR3 pos1,  
	D3DXVECTOR3 size1,
	D3DXVECTOR3 pos2,  
	D3DXVECTOR3 size2)
{
	//���ӂ̃`�F�b�N������
	//�����̍���葊��̉E�̂ق����傫��
	if (pos1.x - size1.x< pos2.x + size2.x)
	{
		//�E�ӂ̃`�F�b�N������
		//�����̉E��葊��̍��̂ق���������
		if (pos1.x + size1.x > pos2.x- size2.x)
		{
			//��ӂ̃`�F�b�N������
			//�����̏��葊��̉��̂ق����傫��
			if (pos1.y - size1.y< pos2.y + size2.y) {
				//���ӂ̃`�F�b�N������
				//�����̉���葊��̏�̂ق���������
				if (pos1.y + size1.y > pos2.y - size2.y) {
					return true;
				}
			}
		}
	}
	return false;
}

//�J�v�Z���Ɖ~�̂̓����蔻��
bool HitCheckCupsule(const CIRCLE* p_circle, const CAPSULE* p_cupsule)
{
	//�~�ƃJ�v�Z���̈ʒu
	 D3DXVECTOR3 cir_pos =  D3DXVECTOR3(p_circle->cx, p_circle->cy,0);
	 D3DXVECTOR3 cup_pos =  D3DXVECTOR3(p_cupsule->x, p_cupsule->y, 0);
	 D3DXVECTOR3 cup_end = D3DXVECTOR3(p_cupsule->x, p_cupsule->y, 0)
							-D3DXVECTOR3(p_cupsule->ex, p_cupsule->ey, 0);

	 D3DXVECTOR3 distance = cir_pos - cup_pos;

	//�}��ϐ�(0.0~1.0�܂œ���)
	float t = 0.0f;

	//��_�����߂�
	//�ȉ��v�Z�����Ă���
	//���ς����߂�i����j�A�Q�A���߂��̐ς��Εӂ̒����Ŋ��遁��̒����ƂȂ�
	//������Ƃ��Ƃ�cup_end�̂������Ŋ���䗦���o��
	t = (cup_end.x * distance.x + cup_end.y * distance.y) /
		(cup_end.x * cup_end.x + cup_end.y * cup_end.y);
		
	
	if (t < 0.0f)
		t = 0.0f;
	if (t > 1.0f)
		t = 1.0f;
		D3DXVECTOR3 pos_cross;
		//��_pos_cross
		//�n�_�𑫂����Ƃŕ��s�ړ����Ă���
		pos_cross.x = (cup_end.x * t) + cup_pos.x;
		pos_cross.y = (cup_end.y * t) + cup_pos.y;
	


	//��_�܂ł̒����Ƃ��݂��̔��a�𑫂������̂̑傫�����ׂ�
	float cross_len = (pos_cross.x - cir_pos.x) * (pos_cross.x - cir_pos.x) +
		(pos_cross.y - cir_pos.y) * (pos_cross.y - cir_pos.y);

	float size = (p_circle->r + p_cupsule->r);

	//���x�N�g���̒����̕�����������΃q�b�g���Ă���I
	if (cross_len < size * size)
	{
		return true;
	}

	//�q�b�g���Ă��Ȃ�����
	return false;
}

