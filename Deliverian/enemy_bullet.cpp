
#include "main.h"
#include "enemy_bullet.h"
#include "input.h"
#include "texture.h"
#include "table.h"


ENEMY_BULLET Enemy_bullet[ENEMY_MAX_BULLET];					//�G�l�~�[�f�[�^

static VERTEX_3D g_PolygonVertex[4];	//���_�f�[�^
static unsigned int g_Texture;			//�e�N�X�`���f�[�^
int ENEMYBULLET_absorb_check;					//�z�����ꂽ�G�̐�

void InitEnemy_Bullet()
{
	ENEMYBULLET_absorb_check = 0;
	for (int i = 0; i < ENEMY_MAX_BULLET; i++)
	{
		Enemy_bullet[i].pos.x = 0;
		Enemy_bullet[i].pos.y = 0;

		//�L���t���O��OFF�ɂ���
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
		//�L���t���O��ON����Ȃ���Ή������Ȃ�
		if (Enemy_bullet[i].isEnable == false)
			continue;

		//���W���X�V����
		Enemy_bullet[i].pos += Enemy_bullet[i].dir;

		//�e����ʂ���o�čs���Ă��܂�����
		//�L���t���O�𗎂Ƃ�
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
		//�L���t���O��ON����Ȃ���Ή������Ȃ�
		if (Enemy_bullet[i].isEnable == false)
			continue;

		//���_���W�Z�b�g
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


//�L���t���O��n��
bool GetIsEnableEnemy_Bullet(int index)
{
	return Enemy_bullet[index].isEnable;
}


//ENEMY��Getter
ENEMY_BULLET* GetEnemy_Bullet() {
	return (&Enemy_bullet[0]);
}

//ENEMYBULLET_absorb_check��Getter
int* GET_ENEMYBULLET_absorb_check() {
	return &ENEMYBULLET_absorb_check;
}

void DestroyEnemyBULLET(int index) {

	Enemy_bullet[index].isEnable = false;
	ENEMYBULLET_absorb_check+=1*3;
}

//�e�̎ˏo����
void SetEnemy_Bullet(nn::math::VEC2 player_pos, int muki,int color)
{
	for (int i = 0; i < ENEMY_MAX_BULLET; i++) {
		//�e�̔z�񂩂�󂫂�T��
		//���ݎg���Ă���̈悾�����ꍇ��
		//�������Ȃ��ŃX���[����
		if (Enemy_bullet[i].isEnable == true)
			continue;

		Enemy_bullet[i].pos.x = player_pos.x;
		Enemy_bullet[i].pos.y = player_pos.y;
		//muki�ɂ���Ĉړ�������ς���
		switch (muki) {
		case 0://������
			Enemy_bullet[i].dir.x = 0.0f;
			Enemy_bullet[i].dir.y = 1.0f;
			break;
		case 1://������
			Enemy_bullet[i].dir.x = -1.0f;
			Enemy_bullet[i].dir.y = 0.0f;
			break;
		case 2://�E����
			Enemy_bullet[i].dir.x = 1.0f;
			Enemy_bullet[i].dir.y = 0.0f;
			break;
		case 3://�����
			Enemy_bullet[i].dir.x = 0.0f;
			Enemy_bullet[i].dir.y = -1.0f;
			break;
		}
		//�ړ������ɃX�s�[�h���|����
		Enemy_bullet[i].dir *= ENEMY_BULLET_SPPED;

		//�F���i�[����
		Enemy_bullet[i].color = color;



		//�L���t���O��ON�ɂ���
		Enemy_bullet[i].isEnable = true;

		break;
	}
}
