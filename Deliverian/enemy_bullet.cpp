
#include "main.h"
#include "enemy_bullet.h"
#include "input.h"
#include "texture.h"
#include "table.h"


ENEMY_BULLET Enemy_bullet[ENEMY_MAX_BULLET];					//エネミーデータ

static VERTEX_3D g_PolygonVertex[4];	//頂点データ
static unsigned int g_Texture;			//テクスチャデータ
int ENEMYBULLET_absorb_check;					//吸収された敵の数

void InitEnemy_Bullet()
{
	ENEMYBULLET_absorb_check = 0;
	for (int i = 0; i < ENEMY_MAX_BULLET; i++)
	{
		Enemy_bullet[i].pos.x = 0;
		Enemy_bullet[i].pos.y = 0;

		//有効フラグをOFFにする
		Enemy_bullet[i].isEnable = false;
	}

	g_PolygonVertex[0].Position = nn::math::VEC3( 10.0f, 10.0f, 0.0f);
	g_PolygonVertex[1].Position = nn::math::VEC3( 42.0f, 10.0f, 0.0f);
	g_PolygonVertex[2].Position = nn::math::VEC3( 10.0f, 42.0f, 0.0f);
	g_PolygonVertex[3].Position = nn::math::VEC3( 42.0f, 42.0f, 0.0f);

	g_PolygonVertex[0].Color = nn::math::VEC4(0.25f, 1.0f, 1.0f, 0.1f);
	g_PolygonVertex[1].Color = nn::math::VEC4(0.25f, 1.0f, 1.0f, 0.1f);
	g_PolygonVertex[2].Color = nn::math::VEC4(0.25f, 1.0f, 1.0f, 0.1f);
	g_PolygonVertex[3].Color = nn::math::VEC4(0.25f, 1.0f, 1.0f, 0.1f);

	g_PolygonVertex[0].TexCoord = nn::math::VEC2( 0.0f, 0.0f);
	g_PolygonVertex[1].TexCoord = nn::math::VEC2( 1.0f, 0.0f);
	g_PolygonVertex[2].TexCoord = nn::math::VEC2( 0.0f, 1.0f);
	g_PolygonVertex[3].TexCoord = nn::math::VEC2( 1.0f, 1.0f);

	g_Texture = LoadTexture("rom:/data/enbullet.tga");
}


void UninitEnemy_Bullet()
{
	UnloadTexture(g_Texture);
}


void UpdateEnemy_Bullet()
{
	for (int i = 0; i < ENEMY_MAX_BULLET; i++)
	{
		//有効フラグがONじゃなければ何もしない
		if (Enemy_bullet[i].isEnable == false)
			continue;

		//座標を更新する
		Enemy_bullet[i].pos += Enemy_bullet[i].dir;

		//弾が画面から出て行ってしまったら
		//有効フラグを落とす
		if (Enemy_bullet[i].pos.x > 400)
			Enemy_bullet[i].isEnable = false;
		if (Enemy_bullet[i].pos.x < 0)
			Enemy_bullet[i].isEnable = false;
		if (Enemy_bullet[i].pos.y > 240)
			Enemy_bullet[i].isEnable = false;
		if (Enemy_bullet[i].pos.y < 0)
			Enemy_bullet[i].isEnable = false;
	}
}


void DrawEnemy_Bullet()
{
	for (int i = 0; i < ENEMY_MAX_BULLET; i++)
	{
		//有効フラグがONじゃなければ何もしない
		if (Enemy_bullet[i].isEnable == false)
			continue;

		//頂点座標セット
		g_PolygonVertex[0].Position = nn::math::VEC3(Enemy_bullet[i].pos.x - (ENEMY_BULLET_WIDTH / 2), Enemy_bullet[i].pos.y - (ENEMY_BULLET_HEIGHT / 2), 0.0f);
		g_PolygonVertex[1].Position = nn::math::VEC3(Enemy_bullet[i].pos.x + (ENEMY_BULLET_WIDTH / 2), Enemy_bullet[i].pos.y - (ENEMY_BULLET_HEIGHT / 2), 0.0f);
		g_PolygonVertex[2].Position = nn::math::VEC3(Enemy_bullet[i].pos.x - (ENEMY_BULLET_WIDTH / 2), Enemy_bullet[i].pos.y + (ENEMY_BULLET_HEIGHT / 2), 0.0f);
		g_PolygonVertex[3].Position = nn::math::VEC3(Enemy_bullet[i].pos.x + (ENEMY_BULLET_WIDTH / 2), Enemy_bullet[i].pos.y + (ENEMY_BULLET_HEIGHT / 2), 0.0f);


		g_PolygonVertex[0].Color = GetENEMYBULLETTable(Enemy_bullet[i].color);
		g_PolygonVertex[1].Color = GetENEMYBULLETTable(Enemy_bullet[i].color);
		g_PolygonVertex[2].Color = GetENEMYBULLETTable(Enemy_bullet[i].color);
		g_PolygonVertex[3].Color = GetENEMYBULLETTable(Enemy_bullet[i].color);


		glBindTexture(GL_TEXTURE_2D, g_Texture);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VERTEX_3D), (GLvoid*)&g_PolygonVertex[0].Position);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VERTEX_3D), (GLvoid*)&g_PolygonVertex[0].Color);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VERTEX_3D), (GLvoid*)&g_PolygonVertex[0].TexCoord);

		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	}
}


//有効フラグを渡す
bool GetIsEnableEnemy_Bullet(int index)
{
	return Enemy_bullet[index].isEnable;
}


//ENEMYのGetter
ENEMY_BULLET* GetEnemy_Bullet() {
	return (&Enemy_bullet[0]);
}

//ENEMYBULLET_absorb_checkのGetter
int* GET_ENEMYBULLET_absorb_check() {
	return &ENEMYBULLET_absorb_check;
}

void DestroyEnemyBULLET(int index) {

	Enemy_bullet[index].isEnable = false;
	ENEMYBULLET_absorb_check+=1*3;
}

//弾の射出処理
void SetEnemy_Bullet(nn::math::VEC2 player_pos, int muki,int color)
{
	for (int i = 0; i < ENEMY_MAX_BULLET; i++) {
		//弾の配列から空きを探す
		//現在使っている領域だった場合は
		//何もしないでスルーする
		if (Enemy_bullet[i].isEnable == true)
			continue;

		Enemy_bullet[i].pos.x = player_pos.x;
		Enemy_bullet[i].pos.y = player_pos.y;
		//mukiによって移動方向を変える
		switch (muki) {
		case 0://下向き
			Enemy_bullet[i].dir.x = 0.0f;
			Enemy_bullet[i].dir.y = 1.0f;
			break;
		case 1://左向き
			Enemy_bullet[i].dir.x = -1.0f;
			Enemy_bullet[i].dir.y = 0.0f;
			break;
		case 2://右向き
			Enemy_bullet[i].dir.x = 1.0f;
			Enemy_bullet[i].dir.y = 0.0f;
			break;
		case 3://上向き
			Enemy_bullet[i].dir.x = 0.0f;
			Enemy_bullet[i].dir.y = -1.0f;
			break;
		}
		//移動方向にスピードを掛ける
		Enemy_bullet[i].dir *= ENEMY_BULLET_SPPED;

		//色を格納する
		Enemy_bullet[i].color = color;



		//有効フラグをONにする
		Enemy_bullet[i].isEnable = true;

		break;
	}
}
