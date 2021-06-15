//=============================================================================
//
// �v���C���[���� [Player.cpp]
// Author : �H�{
//�X�R�A��HP�Ƃ������V�X�e����������Ɋi�[
//=============================================================================
#include "main.h"
#include "input.h"
#include "player.h"
#include "Sound.h"
#include "Func_texture.h"
#include "game.h"
#include "bullet.h"
#include "bulletsight.h"
#include "Blade.h"
#include "UI_Life.h"
#define _USE_MATH_DEFINES 
#include "math.h"
#ifdef _DEBUG
#include "scene.h"
#include "fade.h"
#endif


//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_PLAYER_SIZE_X	(40)	// �e�N�X�`���T�C�Y
#define TEXTURE_PLAYER_SIZE_Y	(40)	// 
#define PLAYER_SIZE_X	(24)	// �v���C���[�T�C�Y
#define PLAYER_SIZE_Y	(24)	// �v���C���[�T�C�Y
//�퓬�@�p
#define TEXTURE_PATTERN_DIVIDE_X	1	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y	1	// �A�j���p�^�[���̃e�N�X�`�����������iY)

#define ANIM_PATTERN_NUM			(3)	// �A�j���[�V�����p�^�[����

#define TIME_ANIMATION				(4)	// �A�j���[�V�����̐؂�ւ��J�E���g

#define PLAYER_FIRST_HP				3// �v���C���[�̍ŏ���HP
#define PLAYER_FIRST_SCORE			0// �v���C���[�̍ŏ���SCORE
#define PLAYER_FIRST_POWER			2// �v���C���[�̍ŏ���POWER
#define PLAYER_BLADE_RELOADTIME		(1)// �v���C���[�̌��̗͂̔{��

#define PLAYER_DMGHIT_MUTEKITIME	1// �v���C���[�̃_���[�W�q�b�g���̖��G����


#define	RADIUS_MIN				(50.0f)							// �|���S���̔��a�ŏ��l
#define	RADIUS_MAX				(300.0f)						// �|���S���̔��a�ő�l
#define	VALUE_ROTATION			(D3DX_PI * 0.01f)				// �|���S���̉�]��
#define	VALUE_SCALE				(2.0f)							// �|���S���̃X�P�[���ω���

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void DiePlayer(void);					//�v���C���[��HP���S���Ȃ�������
void PlayerMutekiState(void);			//�v���C���[�����G���̏���
void TenmetuPlayerTexture(int EffectOnOff);		//�v���C���[�̓_�ŏ���

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static LPDIRECT3DTEXTURE9		g_pD3DTexture = NULL;		// �e�N�X�`���ւ̃|�C���^

static VERTEX_2D				g_vertexWk[NUM_VERTEX];		// ���_���i�[���[�N

PLAYER_DATA player;							//�v���C���[�f�[�^

int						g_nCountAnim;						// �A�j���[�V�����J�E���g
int						g_nPatternAnim;						// �A�j���[�V�����p�^�[���i���o�[

enum
{
	TEXTURE_PLAYER,		// title
	TEXTURE_TURRET,		// result
	TEXTURE_MAX,
};

static VERTEX_2D g_ResultVertex[TEXTURE_MAX][4];

static Texture_DATA g_Result_InitTexture[] =
{
	{
	(char *)"TEXTURE/Stg_main/Player/tankbase_04.png"
	//(char *)"TEXTURE/Stg_main/Shoot/bullet2.tga"
	,NULL
	,NULL
	,D3DXVECTOR3(SCREEN_GAME_WIDTH / 2, SCREEN_GAME_HEIGHT / 4 * 3, 0.0f)
	,TEXTURE_PLAYER_SIZE_X
	,TEXTURE_PLAYER_SIZE_Y
	,true
	,0
	,0
	,false
	,NON_DIVIDE
	,NON_DIVIDE
	,NON_DIVIDE_TEXTURENUMBER
	,false
	,D3DXVECTOR4(255, 255, 255, 255)
	},

	{
	(char *)"TEXTURE/Stg_main/Player/tankcannon-01a.png"
	,NULL
	,NULL
	,D3DXVECTOR3(SCREEN_GAME_WIDTH / 2, SCREEN_GAME_HEIGHT / 4 * 3, 0.0f)
	,TEXTURE_PLAYER_SIZE_X
	,TEXTURE_PLAYER_SIZE_Y
	,true
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


static Texture_DATA g_Result_texture[TEXTURE_MAX];

//=============================================================================
// ����������
//=============================================================================
HRESULT InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		//������
		g_Result_texture[i] =
			g_Result_InitTexture[i];
		
		//�����p�x�̊i�[
		g_Result_texture[i].BaseAngle =
			atan2f(g_Result_texture[i].Size_y, g_Result_texture[i].Size_x);

		//���_���W�̐ݒ�
		MakeVertex(g_ResultVertex[i]);

		SetTexture(g_ResultVertex[i],
			TEXTURE_PATTERN_DIVIDE_X,
			TEXTURE_PATTERN_DIVIDE_Y);

		//�ꏊ����
		SetVertex(g_ResultVertex[i],
			g_Result_texture[i].Pos,
			g_Result_texture[i].Size_x,
			g_Result_texture[i].Size_y);

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
			g_Result_texture[i].Path,				// �t�@�C���̖��O
			&g_Result_texture[i].pD3DTexture);					// �ǂݍ��ރ������̃|�C���^
		//���_���W�����i�[
		g_Result_texture[i].Vertex = g_ResultVertex[i];

	}

	player.pos = D3DXVECTOR3(SCREEN_GAME_WIDTH / 2, 
		SCREEN_GAME_HEIGHT / 4 * 3, 0.0f);

	player.Rotation = 0;
	player.size = D3DXVECTOR3(PLAYER_SIZE_X,
		PLAYER_SIZE_Y, 0.0f);
	player.Score = PLAYER_FIRST_SCORE;
	player.Hp = PLAYER_FIRST_HP;
	player.Power = PLAYER_FIRST_POWER;
	player.State = PLAYER_STATE_NORMAL;
	player.State_time = 0;
	player.BulletReloadflg = false;
	player.BulletReload_time = 0;
	player.isEnable = true;

	g_nCountAnim = 0;
	g_nPatternAnim = 0;

	Ui_Life_Set(player.Hp);
	Ui_Score_Set(player.Score);
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitPlayer(void)
{
	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		if (g_Result_texture[i].pD3DTexture != NULL)
		{	// �e�N�X�`���̊J��
			g_Result_texture[i].pD3DTexture->Release();
			g_Result_texture[i].pD3DTexture = NULL;
		}
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePlayer(void)
{
	// �A�j���[�V����
	g_nCountAnim++;

	//�}�E�X�̓����l
	D3DXVECTOR3	Mouse_Move;
	Mouse_Move = D3DXVECTOR3(0,0,0);

	//�ꎞ�I�ȓ����l
	D3DXVECTOR3	Move_pos;
	Move_pos = D3DXVECTOR3(0, 0, 0);

	//�Ə�����������擾
	D3DXVECTOR3 dirBulletSightTemp;
	//float tempRotaion;
	BULLETSIGHT *BulletSightTemp;
	BulletSightTemp = GetBulletSight();
	dirBulletSightTemp = BulletSightTemp->pos - player.pos;
	dirBulletSightTemp = Vec3Normalize(&dirBulletSightTemp);
	player.Rotation = atan2f(dirBulletSightTemp.y, dirBulletSightTemp.x) + (M_PI / 2);


	// �A�j���[�V����Wait�`�F�b�N
	if( ( g_nCountAnim % TIME_ANIMATION ) == 0 )
	{
		// �p�^�[���̐؂�ւ�
		g_nPatternAnim = ( g_nPatternAnim + 1 ) % ANIM_PATTERN_NUM;

		// �e�N�X�`�����W��ݒ�
		//SetTexturePlayer(g_nPatternAnim, player.charaType, player.muki);
	}

	//�J�[�\���L�[�́������͂��ꂽ���̏���
	if (GetKeyboardPress(DIK_UP) || GetKeyboardPress(DIK_W))
	{
		Move_pos.y -= 1.0f;
		//player.muki = UP;

	}
	//�J�[�\���L�[�́������͂��ꂽ���̏���
	if (GetKeyboardPress(DIK_DOWN) || GetKeyboardPress(DIK_S))
	{
		Move_pos.y += 1.0f;
		//player.muki = DOWN;
	
	}
	//�J�[�\���L�[�́������͂��ꂽ���̏���
	if (GetKeyboardPress(DIK_RIGHT) || GetKeyboardPress(DIK_D))
	{
		Move_pos.x += 1.0f;
		//player.muki = RIGHT;

	}
	//�J�[�\���L�[�́������͂��ꂽ���̏���
	if (GetKeyboardPress(DIK_LEFT) || GetKeyboardPress(DIK_A))
	{
		Move_pos.x -= 1.0f;
		//player.muki = LEFT;

	}


	//��O����
	//�L���t���O�𗎂Ƃ�
	//������
	if (player.pos.y < 0+ TEXTURE_PLAYER_SIZE_Y / 2 && Move_pos.y < 0)
	{
		Move_pos.y = 0;
		player.pos.y = 0 + TEXTURE_PLAYER_SIZE_Y / 2;
	}
	//�L���t���O�𗎂Ƃ�
	if (player.pos.y > SCREEN_GAME_HEIGHT- TEXTURE_PLAYER_SIZE_Y / 2 && Move_pos.y>0)
	{
		Move_pos.y = 0;
		player.pos.y = SCREEN_GAME_HEIGHT - TEXTURE_PLAYER_SIZE_Y / 2;
	}
	//�L���t���O�𗎂Ƃ�
	if (player.pos.x < 0+ TEXTURE_PLAYER_SIZE_X / 2 && Move_pos.x < 0)
	{
		Move_pos.x = 0;
		player.pos.x = 0 + TEXTURE_PLAYER_SIZE_X / 2;
	}
	//�L���t���O�𗎂Ƃ�
	if (player.pos.x > SCREEN_GAME_WIDTH- TEXTURE_PLAYER_SIZE_X / 2 && Move_pos.x>0)
	{
		Move_pos.x = 0;
		player.pos.x = SCREEN_GAME_WIDTH - TEXTURE_PLAYER_SIZE_X / 2;
	}

	player.pos += Move_pos;




#ifdef _DEBUG
	//test�p
	if (GetKeyboardPress(DIK_Z))
	{
		Fade(SCENE_INDEX_RESULT);
	}
#endif


	//�W���̈ړ�
	if (GetMouseX !=0) {
		Mouse_Move.x = (float)GetMouseX();
	}

	if (GetMouseX != 0) {
		Mouse_Move.y = (float)GetMouseY();
	}
	BulletMove(Mouse_Move);
	   
	//�ʂ̎ˏo
	if (IsMouseLeftTriggered()) {
		PlaySound(SOUND_LABEL_SE_shot000);
		SetBullet(player.pos, dirBulletSightTemp,5.0f, PLAYERS_BULLET);
	}

	//�ߐ�
	if (player.BulletReloadflg)
	{
		player.BulletReload_time += 1.0f / 120.0f;
		if (player.BulletReload_time>= PLAYER_BLADE_RELOADTIME)
		{
			player.BulletReload_time = 0.0f;
			player.BulletReloadflg = false;
		}
	}

	if (IsMouseRightTriggered()&&!player.BulletReloadflg) {
		player.BulletReloadflg = true;
		D3DXVECTOR3 tempVec3 = 
			D3DXVECTOR3(g_Result_texture[TEXTURE_TURRET].Size_x / 2, g_Result_texture[TEXTURE_TURRET].Size_y / 2, 0);
		double TempLen = D3DXVec3Length(&tempVec3);

		PlaySound(SOUND_LABEL_SE_shot001);
		SetBlade(player.pos, dirBulletSightTemp, player.Rotation,
			TempLen, PLAYERS_BLADE);
	}

	//�ߐڏI���

	switch (player.State)
	{
	case PLAYER_STATE_NORMAL:
		break;
	case PLAYER_STATE_MUTEKI:
		PlayerMutekiState();
		break;

	default:
		break;
	}

		
	//SetVertexPlayer();	// ���_�̌v�Z����
	//�e�N�`���[�ɏꏊ������
	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		g_Result_texture[i].Pos = player.pos;
		g_Result_texture[i].Angle = player.Rotation;
	}

	UpdateBulletSight();//�Ə��̏���
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPlayer(void)
{
	if (!player.isEnable)
		return;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		if (!g_Result_texture[i].IsEnable)
			continue;
		//���_���W�Z�b�g
		if (g_Result_texture[i].IsEnableRotation) 
		{
			SetVertex(g_Result_texture[i].Vertex, g_Result_texture[i].Pos,
				g_Result_texture[i].Size_x, g_Result_texture[i].Size_y,
				g_Result_texture[i].BaseAngle, g_Result_texture[i].Angle);
		}
		else 
		{
			SetVertex(g_ResultVertex[i],
				g_Result_texture[i].Pos,
				g_Result_texture[i].Size_x,
				g_Result_texture[i].Size_y);
		
		}
		//�e�N�X�`���[���W�̃Z�b�g
		SetTexture(g_Result_texture[i].Vertex,
			g_Result_texture[i].Divide_x,
			g_Result_texture[i].Divide_y,
			g_Result_texture[i].TextureNumber);
		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);
		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_Result_texture[i].pD3DTexture);
		// �|���S���̕`��
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_PLAYER, g_Result_texture[i].Vertex, sizeof(VERTEX_2D));
	}

}

//PLAYER��Getter
PLAYER_DATA* GetPlayer() {
	return (&player);
}

// PLAYER��Score��ς��鏈��
void PlusPlayerScore(int PlusScore) {

	//�v���C���[��Score��0�ȉ��ɂ͂Ȃ�Ȃ�
	if (PlusScore < 0 && player.Score == 0)
		return;
	player.Score += PlusScore;
	Ui_Score_Set(player.Score);
}

// PLAYER��Hp��ς��鏈��
void PlusPlayerHp(int PlusHp) {
	
	player.Hp += PlusHp;
	//UI�Ƀ��C�t�𔽉f������
	Ui_Life_Set(player.Hp);
	//�_���[�W�Ȃ�
	if (PlusHp<0)PlaySound(SOUND_LABEL_SE_DAMAGE000);
	//�v���C���[��Hp��0�ɂȂ����Ƃ�
	if (player.Hp<=0) {
		DiePlayer();
	}
}

// PLAYER�̏�Ԃ�ς��鏈��
void ChangePlayerState(PLAYER_STATE targetstate) {
	player.State = targetstate;
}

void DiePlayer() {
	player.isEnable = false;
	PlaySound(SOUND_LABEL_SE_PLAYERDIE);
	SetGamePhase(PHASE_GAME_END);
}

void PlayerMutekiState() {
	player.State_time += 1 / 60.0f;

	if (int(player.State_time*1000) % 4 == 0) {
		TenmetuPlayerTexture(0);
	}
	
	if (player.State_time > PLAYER_DMGHIT_MUTEKITIME)
	{
		TenmetuPlayerTexture(1);
		player.State_time = 0;
		player.State = PLAYER_STATE_NORMAL;
	}
}

//*****************************************************************************
// �������牺��player.cpp�݂̂Ŏg����֐�
//*****************************************************************************

//=============================================================================
//�v���C���[�̓_�ŏ���

//ON=0 OFF=1
//=============================================================================
void TenmetuPlayerTexture(int EffectOnOff) {

	switch (EffectOnOff)
	{
	case 0:
		for (int i = 0; i < TEXTURE_MAX; i++)
		{
			//�v���C���[���\������Ă��鎞
			if (g_Result_texture[i].Vertex->diffuse == D3DCOLOR_RGBA(255, 255, 255, 255))
			{
				g_Result_texture[i].Vertex->diffuse = D3DCOLOR_RGBA(255, 255, 255, 0);
				(g_Result_texture[i].Vertex+1)->diffuse = D3DCOLOR_RGBA(255, 255, 255, 0);
				(g_Result_texture[i].Vertex+2)->diffuse = D3DCOLOR_RGBA(255, 255, 255, 0);
				(g_Result_texture[i].Vertex+3)->diffuse = D3DCOLOR_RGBA(255, 255, 255, 0);
				continue;
			}
			else
			//�v���C���[���\������ĂȂ��Ƃ�
			//if ((g_Result_texture[i].Vertex)->diffuse == D3DCOLOR_RGBA(255, 255, 255, 0))
			{
				(g_Result_texture[i].Vertex)->diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
				(g_Result_texture[i].Vertex+1)->diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
				(g_Result_texture[i].Vertex+2)->diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
				(g_Result_texture[i].Vertex+3)->diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
				continue;
			}

		}

		break;
	case 1:
		for (int i = 0; i < TEXTURE_MAX; i++)
		{
			//�v���C���[��\�����鎞
			(g_Result_texture[i].Vertex)->diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
			(g_Result_texture[i].Vertex+1)->diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
			(g_Result_texture[i].Vertex+2)->diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
			(g_Result_texture[i].Vertex+3)->diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		}
		break;
	default:
		break;

	}
}
