#pragma once
#include "..\Engine_Source\SceneManager.h"

#include "PlayScene.h"
#include "SeriaGateScene.h"
#include "WestcoastScene.h"
#include "HendonmyreScene.h"

#ifdef _DEBUG
#pragma comment(lib,"..\\Libraries\\Debug\\Engine.lib")
#else
#pragma comment(lib,"..\\Libraries\\Release\\Engine.lib")
#endif

namespace roka
{
	void InitializeScenes()
	{
		SceneManager::CreateScene<PlayScene>(L"PlayScene");
		SceneManager::CreateScene<SeriaGateScene>(L"SeriaGateScene");
		SceneManager::CreateScene<WestcoastScene>(L"WestcoastScene");
		SceneManager::CreateScene<HendonmyreScene>(L"HendonmyreScene");

		SceneManager::LoadScene(L"SeriaGateScene");
	}
}