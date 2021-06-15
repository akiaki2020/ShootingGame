//=============================================================================
//
// 当たり判定処理 [collision.cpp]
// Author : 秋本
//接触判定と、接触後どの関数を呼ぶか記述
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




//弾とプレイヤー・敵の当たり判定
void PlayerHitEnemyCheck(PLAYER_DATA *player, ENEMY* enemy);
void BulletHitEnemyCheck(PLAYER_DATA *player,ENEMY* enemy,BULLET* bullet);
void BulletHitPlayerCheck(PLAYER_DATA *player, BULLET* bullet);
void BladeHitEnemyCheck(PLAYER_DATA *player, ENEMY* enemy, BLADE* bullet);
void BladeHitPlayerCheck(PLAYER_DATA *player,BLADE* bullet);
void LaserHitEnemyCheck(PLAYER_DATA *player, ENEMY* enemy, LASER* laser);
void LaserHitPlayerCheck(PLAYER_DATA *player, LASER* laser);



//円の当たり判定
bool HitCheckBC(D3DXVECTOR3 pos1, float size1,
	D3DXVECTOR3 pos2, float size2);

//キューブの当たり判定
bool HitCheckBB(D3DXVECTOR3 pos1, D3DXVECTOR3 size1,
	 D3DXVECTOR3 pos2,  D3DXVECTOR3 size2);

bool HitCheckCupsule(const CIRCLE* p_circle, const CAPSULE* p_cupsule);

bool HitCheckTyouhoukei(const CIRCLE* p_circle, const CAPSULE* p_cupsule);


//game.cppのみで呼ぶ
void HitCheck() {
	//プレイヤーとエネミーと弾のポインタをとる
	PLAYER_DATA* pPlayer = GetPlayer();
	ENEMY* pEnemy = GetEnemy();
	BULLET* pBullet = GetBullet();
	BLADE* pBlade = GetBlade();
	ENEMY* pBoss= GetBoss();
	LASER* pLaser = GetEnemyLaser();


	//自分と敵との当たり判定
	PlayerHitEnemyCheck(pPlayer,pBoss);
	for (int i = 0; i < MAX_ENEMY; i++)
	{
		PlayerHitEnemyCheck(pPlayer, &pEnemy[i]);
	}

	//弾と敵の当たり判定
	for (int i_B = 0; i_B < MAX_BULLET; i_B++) {
		//有効化していない弾はスルー
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

	//剣と敵の当たり判定
	for (int i_B = 0; i_B < MAX_BLADE; i_B++) {

		//有効化していない弾はスルー
		if (pBlade[i_B].isEnable == false)
			continue;
		BladeHitPlayerCheck(pPlayer, &pBlade[i_B]);
		BladeHitEnemyCheck(pPlayer, pBoss, &pBlade[i_B]);
		for (int i = 0; i < MAX_ENEMY; i++)
		{
			BladeHitEnemyCheck(pPlayer, &pEnemy[i], &pBlade[i_B]);
		}
	}

	//レーザーとの当たり判定
	for (int i_l = 0; i_l < MAX_LASER; i_l++) {

		//有効化していない弾はスルー
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
	//有効化していない敵はスルー
	if (enemy->isEnable == false)
		return;

	//プレイヤーが無敵のときはスルー
	if (player->State == PLAYER_STATE_MUTEKI)
		return;

	//ヒットしているかをチェックする
	D3DXVECTOR3 size1 = D3DXVECTOR3(player->size.x / 2, player->size.y / 2, 0);
	D3DXVECTOR3 size2 = D3DXVECTOR3(enemy->size.x / 2, enemy->size.y / 2, 0);
	float size1_len = D3DXVec3Length(&size1);
	float size2_len = D3DXVec3Length(&size1);

	//プレイヤーの座標とサイズ（幅、高さ）と
	//エネミーの座標とサイズを引数で渡す
	if (HitCheckBC(player->pos, size1_len,
		enemy->pos, size2_len))
	{
		//プレイヤーHPを減らす
		PlusPlayerHp(-enemy->Power);
		//無敵状態にする
		ChangePlayerState(PLAYER_STATE_MUTEKI);
	}
}

//弾と敵の当たり判定
void BulletHitEnemyCheck(PLAYER_DATA *player, ENEMY* enemy, BULLET* bullet) {

	//有効化していない弾はスルー
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
			//敵の有効フラグをチェック
			//有効化していない敵はスルー
			//無敵状態なら判定しない
			if (enemy->Enemy_Mutekiflg) {
				return;
			}
			//ヒットしているかをチェックする（ボックス版）
			 size1 = D3DXVECTOR3(bullet->size.x / 2, bullet->size.y /2, 0);
			 size2 = D3DXVECTOR3(enemy->size.x / 2, enemy->size.y / 2, 0);
			 size1_len = D3DXVec3Length(&size1);
			 size2_len = D3DXVec3Length(&size1);

			if (HitCheckBC(bullet->pos, size1_len,
				enemy->pos, size2_len))
			{
				//有効フラグをOFFにして弾を消す！
				bullet->isEnable = false;
				//有効フラグをOFFにして敵を消す！
				//enemy->isEnable = false;
				PlusEnemyHp(enemy, -1*player->Power);
				ChangeEnemyState(enemy, ENEMY_STATE_DAMAGE);

				//点数を追加
				//PlusPlayerScore(2);
				//エフェクトの追加
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

//弾とプレイヤーの当たり判定
void BulletHitPlayerCheck(PLAYER_DATA *player, BULLET* bullet) {

	//有効化していない弾はスルー
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
		//プレイヤーが無敵のときはスルー
		if (player->State == PLAYER_STATE_MUTEKI)
			return;

		//ヒットしているかをチェックする（ボックス版）
		size1 = D3DXVECTOR3(bullet->size.x / 2, bullet->size.y / 2, 0);
		size2 = D3DXVECTOR3(player->size.x / 2, player->size.y / 2, 0);
		size1_len = D3DXVec3Length(&size1);
		size2_len = D3DXVec3Length(&size1);

		if (HitCheckBC(bullet->pos, size1_len,
			player->pos, size2_len))
		{
			//プレイヤーHPを減らす
			PlusPlayerHp(-(bullet->power));
			//無敵状態にする
			ChangePlayerState(PLAYER_STATE_MUTEKI);
		}
		break;
	default:

		break;
	}
	return;
}

//剣と敵の当たり判定
void BladeHitEnemyCheck(PLAYER_DATA *player, ENEMY* enemy, BLADE* blade) {

	//有効化していない弾はスルー
	if (blade->isEnable == false)
		return;
	//有効化していない敵はスルー
	if (enemy->isEnable == false)
		return;
	//無敵状態なら判定しない
	if (enemy->Enemy_Mutekiflg) {
		return;
	}

	D3DXVECTOR3 tempdir;
	//WAIT_ROTATIONで使用
	//敵の中心座標
	D3DXVECTOR3 center;
	//プレイヤーの座標を取得する
	D3DXVECTOR3 pl_pos;
	//敵とプレイヤーの距離を計算する
	D3DXVECTOR3 vLen;
	float length;
	switch (blade->Affiliation)
	{
	case PLAYERS_BLADE:
		//剣のベクトル取得
		tempdir = D3DXVECTOR3(sinf(blade->Rotation), -cosf(blade->Rotation), 0);
		D3DXVec3Normalize(&tempdir, &tempdir);

		//剣の座標を取得する
		pl_pos = D3DXVECTOR3(blade->pos.x, blade->pos.y, blade->pos.z);

		//敵とプレイヤーの距離を計算する
		vLen = enemy->pos - pl_pos;

		length = D3DXVec3Length(&vLen);

		//判定する距離の中に入っているかをチェックする
		if (length < BLADE_HEIGHT)
		{
			//敵から見てプレイヤーの座標への方向ベクトルを作る
			D3DXVECTOR3 pl_dir = enemy->pos -pl_pos;
			D3DXVec3Normalize(&pl_dir, &pl_dir);

			//敵の向きとプレイヤ座標への方向ベクトルで内積を取る
			float dot = D3DXVec3Dot(&tempdir, &pl_dir);

			//判定する角度内に入っているかをチェックする
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

//剣とプレイヤーの当たり判定
void BladeHitPlayerCheck(PLAYER_DATA *player, BLADE* blade) {

	D3DXVECTOR3 tempdir;

	//WAIT_ROTATIONで使用
	//プレイヤーの座標を取得する
	D3DXVECTOR3 pl_pos;

	//敵の中心座標
	D3DXVECTOR3 center;

	//敵とプレイヤーの距離を計算する
	D3DXVECTOR3 vLen;
	float length;

	//有効化していない弾はスルー
	if (blade->isEnable == false)
		return;

	switch (blade->Affiliation)
	{
	case PLAYERS_BLADE:
		break;
	case ENEMYS_BLADE:
		//プレイヤーが無敵のときはスルー
		//if (player->State == PLAYER_STATE_MUTEKI)
		//	return;
		//tempdir = D3DXVECTOR3(sinf(blade->Rotation), -cosf(blade->Rotation), 0);
		////プレイヤーの座標を取得する
		//pl_pos = D3DXVECTOR3(blade->pos.x, blade->pos.y, blade->pos.z);

		////敵とプレイヤーの距離を計算する
		//vLen = enemy->pos - pl_pos;

		//length = D3DXVec3Length(&vLen);

		////判定する距離の中に入っているかをチェックする
		//if (length < BLADE_LENGTH)
		//{
		//	//敵から見てプレイヤーの座標への方向ベクトルを作る
		//	D3DXVECTOR3 pl_dir = pl_pos - enemy->pos;
		//	D3DXVec3Normalize(&pl_dir, &pl_dir);

		//	//敵の向きとプレイヤ座標への方向ベクトルで内積を取る
		//	float dot = D3DXVec3Dot(&tempdir, &pl_dir);
		//	//判定する角度内に入っているかをチェックする
		//	if (dot > 0.85f)
		//	{
		//		//プレイヤーHPを減らす
		//		PlusPlayerHp(-1);
		//		//無敵状態にする
		//		ChangePlayerState(PLAYER_STATE_MUTEKI);
		//	}
		//}
		break;
	default:
		break;
	}
	return;
}

//レーザーと敵の当たり判定
void LaserHitEnemyCheck(PLAYER_DATA *player, ENEMY* enemy, LASER* laser) {

	//有効化していない弾はスルー
	if (laser->isEnable == false)
		return;
	//有効化していない敵はスルー
	if (enemy->isEnable == false)
		return;
	//無敵状態なら判定しない
	if (enemy->Enemy_Mutekiflg) {
		return;
	}

	D3DXVECTOR3 tempdir;
	CAPSULE CAPSULE;
	CIRCLE CIRCLE;

	switch (laser->Affiliation)
	{
	case PLAYERS_BLADE:
		//サークルに格納
		CIRCLE.cx = enemy->pos.x;
		CIRCLE.cy = enemy->pos.y;
		tempdir = D3DXVECTOR3(enemy->size.x / 2, enemy->size.y / 2, 0);
		CIRCLE.r = D3DXVec3Length(&tempdir);;

		//カプセルにレーザーを格納
		CAPSULE.x = laser->s_pos.x;
		CAPSULE.y = laser->s_pos.y;
		CAPSULE.ex = laser->pos.x;
		CAPSULE.ey = laser->pos.y;
		CAPSULE.r = laser->Futosa/2;

		//プレイヤーの座標とサイズ（幅、高さ）と
		//エネミーの座標とサイズを引数で渡す
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

//レーザーとプレイヤーの当たり判定
void LaserHitPlayerCheck(PLAYER_DATA *player, LASER* laser)
{
	//有効化していない弾はスルー
	if (laser->isEnable == false)
		return;
	//プレイヤーが無敵のときはスルー
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

		//サークルに格納
		CIRCLE.cx = player->pos.x;
		CIRCLE.cy = player->pos.y;
		tempdir = D3DXVECTOR3(player->size.x / 2, player->size.y / 2, 0);
		CIRCLE.r = D3DXVec3Length(&tempdir);;

		//カプセルにレーザーを格納
		CAPSULE.x = laser->s_pos.x;
		CAPSULE.y = laser->s_pos.y;
		CAPSULE.ex = laser->pos.x;
		CAPSULE.ey = laser->pos.y;
		CAPSULE.r = laser->Futosa/2;

		//プレイヤーの座標とサイズ（幅、高さ）と
		//エネミーの座標とサイズを引数で渡す
		if (HitCheckCupsule(&CIRCLE, &CAPSULE))
		{
			//プレイヤーHPを減らす
			PlusPlayerHp(-laser->power);
			//無敵状態にする
			ChangePlayerState(PLAYER_STATE_MUTEKI);
		}

		break;
	default:
		break;
	}
	return;
}


//円型の当たり判定
bool HitCheckBC( D3DXVECTOR3 pos1, float size1,
	 D3DXVECTOR3 pos2, float size2)
{
	//pos1とpos2の距離のベクトル
	 D3DXVECTOR3 distance;
	distance = pos1 - pos2;

	//distanceのベクトル長を計算する
	float length = 0.0f;
	length = D3DXVec3Length(&distance);
	//当たり判定をとる物体2つの半径を足す
	float w = size1 + size2;

	//距離のほうが短ければヒットしている
	if (length < w)
		return true;
	else
		return false;
}

//BOXの当たり判定
//POSの点はテクスチャーの左上
bool HitCheckBB( 
	D3DXVECTOR3 pos1,  
	D3DXVECTOR3 size1,
	D3DXVECTOR3 pos2,  
	D3DXVECTOR3 size2)
{
	//左辺のチェックをする
	//自分の左より相手の右のほうが大きい
	if (pos1.x - size1.x< pos2.x + size2.x)
	{
		//右辺のチェックをする
		//自分の右より相手の左のほうが小さい
		if (pos1.x + size1.x > pos2.x- size2.x)
		{
			//上辺のチェックをする
			//自分の上より相手の下のほうが大きい
			if (pos1.y - size1.y< pos2.y + size2.y) {
				//下辺のチェックをする
				//自分の下より相手の上のほうが小さい
				if (pos1.y + size1.y > pos2.y - size2.y) {
					return true;
				}
			}
		}
	}
	return false;
}

//カプセルと円のの当たり判定
bool HitCheckCupsule(const CIRCLE* p_circle, const CAPSULE* p_cupsule)
{
	//円とカプセルの位置
	 D3DXVECTOR3 cir_pos =  D3DXVECTOR3(p_circle->cx, p_circle->cy,0);
	 D3DXVECTOR3 cup_pos =  D3DXVECTOR3(p_cupsule->x, p_cupsule->y, 0);
	 D3DXVECTOR3 cup_end = D3DXVECTOR3(p_cupsule->x, p_cupsule->y, 0)
							-D3DXVECTOR3(p_cupsule->ex, p_cupsule->ey, 0);

	 D3DXVECTOR3 distance = cir_pos - cup_pos;

	//媒介変数(0.0~1.0まで動く)
	float t = 0.0f;

	//交点を求める
	//以下計算を内包している
	//内積を求める（分母）、２、求めた体積を斜辺の長さで割る＝底の長さとなる
	//底をもともとのcup_endのが長さで割り比率を出す
	t = (cup_end.x * distance.x + cup_end.y * distance.y) /
		(cup_end.x * cup_end.x + cup_end.y * cup_end.y);
		
	
	if (t < 0.0f)
		t = 0.0f;
	if (t > 1.0f)
		t = 1.0f;
		D3DXVECTOR3 pos_cross;
		//交点pos_cross
		//始点を足すことで平行移動している
		pos_cross.x = (cup_end.x * t) + cup_pos.x;
		pos_cross.y = (cup_end.y * t) + cup_pos.y;
	


	//交点までの長さとお互いの半径を足したものの大きさを比べる
	float cross_len = (pos_cross.x - cir_pos.x) * (pos_cross.x - cir_pos.x) +
		(pos_cross.y - cir_pos.y) * (pos_cross.y - cir_pos.y);

	float size = (p_circle->r + p_cupsule->r);

	//→ベクトルの長さの方が小さければヒットしている！
	if (cross_len < size * size)
	{
		return true;
	}

	//ヒットしていなかった
	return false;
}

