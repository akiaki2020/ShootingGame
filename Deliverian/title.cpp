#include "main.h"
#include "input.h"
#include "scene.h"
#include "Func_texture.h"
#include "title.h"
#include "fade.h"
#include "sound.h"
#include <d3d9.h>



//*****************************************************************************
// CONST�ϐ�
//*****************************************************************************


// �}�N����`
#define WAIT_TIMELIMIT (0.5) //���V�[���̑҂�����

//�A�j���[�V����
#define TEXTURE_TITLE_DIVIDE_X	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_TITLE_DIVIDE_Y	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iY)

#define TEXTURE_TITLE_PUSH_DIVIDE_X	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_TITLE_PUSH_DIVIDE_Y	(12)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define TEXTURE_TITLE_PUSH_SIZE_X	(256)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_TITLE_PUSH_SIZE_Y	(22)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define TEXTURE_TITLE_PUSH_ANIME_TIME	(0.05)	// �A�j���p�^�[���̃e�N�X�`���̕ω�����
#define TEXTURE_TITLE_PUSH_ANIME_LIMIT	9	// �A�j���p�^�[���̃e�N�X�`���̕ω����

#define ANIM_TITLE_NUM			(3)	// �A�j���[�V�����p�^�[����
enum
{
	TEXTURE_TITLE_BG,
	TEXTURE_TITLE_PUSH,
	TEXTURE_MAX,
};

const static  Texture_DATA c_InitTexture[] =
{
	{
		(char *)"TEXTURE/Title/title.tga"
		,NULL
		,NULL
		,D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f)	
		,SCREEN_WIDTH
		,SCREEN_HEIGHT
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
		(char *)"TEXTURE/Title/Push_ENTER.tga"
		,NULL
		,NULL
		,D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4 * 3, 0.0f)
		,TEXTURE_TITLE_PUSH_SIZE_X
		,TEXTURE_TITLE_PUSH_SIZE_Y
		,true
		,0
		,0
		,false
		,TEXTURE_TITLE_PUSH_DIVIDE_X
		,TEXTURE_TITLE_PUSH_DIVIDE_Y
		,0
		,true
		,D3DXVECTOR4(255, 255, 255, 255)
	},

};


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
//���V�[���J�ڎ��̃X�C�b�`
static bool g_bEnd = false;
static VERTEX_2D g_PolygonVertex[TEXTURE_MAX][4];//���_�f�[�^
static Texture_DATA g_Texture[TEXTURE_MAX];
float g_Title_Push_Time;			//�\���e�N�X�`���[�v�Z�p
unsigned int g_Title_Push_Number;	//�\���e�N�X�`���[�ʒu
float g_Title_Wait_Time;			//���V�[���J�ڂ܂ł̑҂�����
static bool g_bWait_Time;	//�҂����ԃJ�E���g�t���O

void Title_Initialize(void)
{
	g_bEnd = false;
	g_bWait_Time = false;
	g_Title_Push_Time = 0.0F;
	g_Title_Push_Number = 0;


	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int i = 0; i < TEXTURE_MAX; i++)
	{

		SetTextureDATA
		(
			pDevice,
			g_PolygonVertex[i],
			&g_Texture[i],
			&c_InitTexture[i]
		);

	}

	//BGM�̐���
	PlaySound(SOUND_LABEL_BGM_title);
}

void Title_Finalize(void)
{
	//BGM�̐���
	StopSound(SOUND_LABEL_BGM_title);
	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		UnLoadTextureDATA(&g_Texture[i]);
	}
}

void Title_Update(void)
{
	//�^�C�g�����S�p
	g_Title_Push_Time += 1.0f / 120.0f;
	if (g_Title_Push_Time>TEXTURE_TITLE_PUSH_ANIME_TIME) 
	{
		g_Title_Push_Time = 0.0f;
		g_Texture[TEXTURE_TITLE_PUSH].TextureNumber += 1;
		if (g_Texture[TEXTURE_TITLE_PUSH].TextureNumber>TEXTURE_TITLE_PUSH_ANIME_LIMIT)
		{
			g_Texture[TEXTURE_TITLE_PUSH].TextureNumber = 0;
		}

		SetTexture(g_Texture[TEXTURE_TITLE_PUSH].Vertex,
			g_Texture[TEXTURE_TITLE_PUSH].Divide_x,
			g_Texture[TEXTURE_TITLE_PUSH].Divide_y
			, g_Texture[TEXTURE_TITLE_PUSH].TextureNumber);
	}

	//�G���^�[�L�[����������҂����Ԃ��������J��
	if( !g_bWait_Time) {
		if(GetKeyboardTrigger(DIK_RETURN) ) {
			PlaySound(SOUND_LABEL_SE_titlebutton);
			g_bWait_Time = true;
		}
	}
	else
	{
		if (!g_bEnd)
		{
			//�^�C�g�����S�p
			g_Title_Wait_Time += 1.0f / 120.0f;
			if (g_Title_Wait_Time>WAIT_TIMELIMIT) {
				Fade(SCENE_INDEX_GAME);
				g_bEnd = true;
			}			
		}
	}
}

void Title_Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		if (!g_Texture[i].IsEnable)
			continue;

		DrawTextureDATA(
			pDevice,
			&g_Texture[i]
		);
	}

}
