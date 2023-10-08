#pragma once
#include "..\Engine_Source\SceneManager.h"

#ifdef _DEBUG
#pragma comment(lib,"..\\Libraries\\Debug\\Engine.lib")
#else
#pragma comment(lib,"..\\Libraries\\Debug\\Engine.lib")
#endif

#include "StartLoadScene.h"
#include "PlayScene.h"
#include "SeriaGateScene.h"
#include "WestcoastScene.h"
#include "HendonmyreScene.h"
#include "SelectCharacterScene.h"
#include "TileMapToolScene.h"
#include "UITestScene.h"
namespace roka
{
	void InitializeScenes()
	{
		SceneManager::CreateScene<StartLoadScene>(L"StartLoadScene");
		SceneManager::CreateScene<PlayScene>(L"PlayScene");

		SceneManager::CreateScene<SelectCharacterScene>(L"SelectChScene");
		SceneManager::CreateScene<SeriaGateScene>(L"SeriaGateScene");
		SceneManager::CreateScene<WestcoastScene>(L"WestcoastScene");
		SceneManager::CreateScene<HendonmyreScene>(L"HendonmyreScene");
		SceneManager::CreateScene<TileMapToolScene>(L"TileMapToolScene");
		SceneManager::CreateScene<UITestScene>(L"UITestScene");

		//SceneManager::LoadScene(L"StartLoadScene");
		SceneManager::LoadScene(L"UITestScene");
	}
}