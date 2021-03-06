//=============================================================================
//
// CSV読み込み処理処理 [ReadCsv.cpp]
//
//=============================================================================
#include "ReadCsv.h"
#include <Vector>
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define FILEEXTENSION_CSV ".csv"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************

// 各音素材のパラメータ


//=============================================================================
// 初期化処理
//=============================================================================
bool InitReadCsv()
{
	HRESULT hr;



	return true;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitReadCsv(void)
{
}

//対象パスのファイルを読み込む
FILE *ReadCsv(const char *file_name) {
	FILE *fp = NULL;
	//ファイル読み込み
	char fileNameandExtension[1000];
	fileNameandExtension[0] = '\0';
	char fileExtension[] = FILEEXTENSION_CSV;

	strcpy(fileNameandExtension, file_name);
	strcat(fileNameandExtension, FILEEXTENSION_CSV);

	fp = fopen(fileNameandExtension, "r");
	if (fp == NULL)return NULL;

	return fp;
}







