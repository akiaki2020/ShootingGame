//=============================================================================
//
// シーン遷移処理 [scene.h]
// Author : 秋本
// 更新処理はMAIN.cppのみ呼ばれる
//=============================================================================
#pragma once

typedef enum SCENE_INDEX
{
	//STG用
	SCENE_INDEX_TITLE,
	SCENE_INDEX_GAME,
	SCENE_INDEX_RESULT,

	SCENE_INDEX_MAX
};

void Scene_Initialize(SCENE_INDEX index);
void Scene_Finalize(void);
void Scene_Update(void);
void Scene_Draw(void);
void Scene_Check(void);
void Scene_Change(SCENE_INDEX index);

