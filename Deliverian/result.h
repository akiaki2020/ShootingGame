#pragma once
// �}�N����`

#define TEXTURE_RESULT_MAX	(5)	// �e�N�X�`���[�̐�


//�A�j���[�V����
#define TEXTURE_RESULT_DIVIDE_X	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_RESULT_DIVIDE_Y	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_RESULT_NUM			(3)	// �A�j���[�V�����p�^�[����

#define TEXTURE_RESULT_PAPER_SIZE_X	(600)	// 
#define TEXTURE_RESULT_PAPER_SIZE_Y	(400)	// 

#define TEXTURE_RESULT_PUSH_SIZE_X	(200)// 
#define TEXTURE_RESULT_PUSH_SIZE_Y	(50)	// 
#define TEXTURE_RESULT_NEXT_SIZE_X	(400)// 
#define TEXTURE_RESULT_NEXT_SIZE_Y	(50)	// 
#define TEXTURE_RESULT_POS_Y	(30)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define TEXTURE_RESULT_POS_X	(50)	// �A�j���p�^�[���̃e�N�X�`�����������iY)


#define TEXTURE_RESULT_PUSH_ANIME_TIME	(0.05)	// �A�j���p�^�[���̃e�N�X�`���̕ω�����
#define TEXTURE_RESULT_PUSH_ANIME_LIMIT	9	// �A�j���p�^�[���̃e�N�X�`���̕ω����


void Result_Initialize(void);
void Result_Finalize(void);
void Result_Update(void);
void Result_Draw(void);
