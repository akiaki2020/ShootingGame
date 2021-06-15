
#include "main.h"
#include "Func_texture.h"
#include "fade.h"
#include "scene.h"
#include "sound.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define FVF_FADE_VERTEX (D3DFVF_XYZRHW|D3DFVF_DIFFUSE)
#define FADE_SPEED (120) //�傫���Ȃ�قǃt�F�[�h���Ԃ������Ȃ�
#define TEXTURE_FADE_SAMPLE00	_T("TEXTURE/white.tga")	// �T���v���p�摜

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

static LPDIRECT3DTEXTURE9		g_pD3DTexture = NULL;		// �e�N�X�`���ւ̃|�C���^

static VERTEX_2D g_FadeTopVertex[4];//��ʃt�F�[�h�p���_
static D3DXVECTOR3 g_FadePosition;//�|�W�V����

//�t�F�[�h���
enum FADE_STATE
{
	FADE_STATE_NONE,
	FADE_STATE_IN,
	FADE_STATE_OUT
};

FADE_STATE	g_FadeState;		//�t�F�[�h�̏��
SCENE_INDEX	g_FadeNextState;	//�t�F�[�h�A�E�g��Ɉڍs����V�[��
float		g_FadeAlpha;		//���݂̃A���t�@�l


unsigned int g_FadeTexture;		//�t�F�[�h�p�e�N�X�`��

typedef struct FadeVertex_tag
{
	D3DXVECTOR4 position;
	D3DCOLOR color;
} FadeVertex;


static D3DXCOLOR g_FadeColor(0.0f, 0.0f, 0.0f, 1.0f);
static float g_Alpha = 0.0f;
static float g_AddAlpha = 0.0f;


void InitFade()
{

	g_FadeState = FADE_STATE_NONE;
	g_FadeNextState = SCENE_INDEX_MAX;
	g_FadeAlpha = 0.0f;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	g_FadePosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//���_���W�̐ݒ�
	MakeVertex(g_FadeTopVertex);
	SetTexture(g_FadeTopVertex,
		TEXTURE_FADE_DIVIDE_X,
		TEXTURE_FADE_DIVIDE_Y);

	SetVertex(g_FadeTopVertex,
		g_FadePosition,
		SCREEN_WIDTH,
		SCREEN_HEIGHT );
	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
		TEXTURE_FADE_SAMPLE00,				// �t�@�C���̖��O
		&g_pD3DTexture);					// �ǂݍ��ރ������̃|�C���^


}



void UninitFade()
{
	if (g_pD3DTexture != NULL)
	{	// �e�N�X�`���̊J��
		g_pD3DTexture->Release();
		g_pD3DTexture = NULL;
	}
}


void UpdateFade()
{
	//�t�F�[�h�A�E�g��
	if (g_FadeState == FADE_STATE_OUT)
	{

		//�A���t�@�l��1.0�𒴂�����
		if (g_FadeAlpha >= 1.0f)
		{
			//�V�[����؂�ւ��ăt�F�[�h�C���Ɉڍs����
			g_FadeAlpha = 1.0f;
			g_FadeState = FADE_STATE_IN;
			GetMasteringVoice()->SetVolume(1.0 - g_FadeAlpha);
			Scene_Change(g_FadeNextState);

		}
		GetMasteringVoice()->SetVolume(1.0 - g_FadeAlpha);
		//�A���t�@�l�𑝉�������
		g_FadeAlpha += 1.0f / FADE_SPEED;

	}//�t�F�[�h�C����
	else if (g_FadeState == FADE_STATE_IN)
	{
		//�A���t�@�l���[����菬�����Ȃ�����
		if (g_FadeAlpha <= 0.0f)
		{
			//�t�F�[�h���I��������
			g_FadeAlpha = 0.0f;
			GetMasteringVoice()->SetVolume(1.0 - g_FadeAlpha);
			g_FadeState = FADE_STATE_NONE;
		}
		GetMasteringVoice()->SetVolume(1.0 - g_FadeAlpha);
		//�A���t�@�l������������
		g_FadeAlpha -= 1.0f / FADE_SPEED;
	}
}



void DrawFade()
{
	//�t�F�[�h���I�����Ă���Ȃ牽�����Ȃ�
	if (g_FadeState == FADE_STATE_NONE)
		return;

	g_FadeColor.a = g_FadeAlpha;
	D3DCOLOR c = g_FadeColor;

	FadeVertex v[] = {
	{ D3DXVECTOR4(0.0f,          0.0f, 0.0f, 1.0f), c },
	{ D3DXVECTOR4(SCREEN_WIDTH,          0.0f, 0.0f, 1.0f), c },
	{ D3DXVECTOR4(0.0f, SCREEN_HEIGHT, 0.0f, 1.0f), c },
	{ D3DXVECTOR4(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 1.0f), c },
	};

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetFVF(FVF_FADE_VERTEX);
	pDevice->SetTexture(0, NULL);
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(FadeVertex));
}




//�t�F�[�h����
void Fade(SCENE_INDEX nextScene)
{
	//�t�F�[�h�A�E�g��Ɉڍs����V�[��
	g_FadeNextState = nextScene;
	//�t�F�[�h�A�E�g�X�^�[�g
	g_FadeState = FADE_STATE_OUT;
}