#include "SceneManager.h"

#include "PlayScene.h"
#include "SeriaGateScene.h"
#include "HendonmyreScene.h"
#include "WestcoastScene.h"
namespace roka
{
	Scene* SceneManager::mActiveScene = nullptr;
	std::map<std::wstring, Scene*> SceneManager::mScenes;
	void SceneManager::Initialize()
	{

		mScenes.insert(std::make_pair(L"PlayScene", new PlayScene()));
		mScenes.insert(std::make_pair(L"SeriaGateScene", new SeriaGateScene()));
		mScenes.insert(std::make_pair(L"HendonmyreScene", new HendonmyreScene()));
		mScenes.insert(std::make_pair(L"WestCoastScene", new WestcoastScene()));
		for (auto scene : mScenes)
		{
			scene.second->Initialize();
		}

		LoadScene(L"SeriaGateScene");
	}
	void SceneManager::Update()
	{
		mActiveScene->Update();
	}
	void SceneManager::LateUpdate()
	{
		mActiveScene->LateUpdate();
	}
	void SceneManager::Render()
	{
		mActiveScene->Render();
	}
	void SceneManager::Release()
	{
		for (auto itr : mScenes)
		{
			delete itr.second;
			itr.second = nullptr;
		}
	}
	Scene* SceneManager::LoadScene(std::wstring name)
	{
		std::map<std::wstring, Scene*>::iterator itr = mScenes.find(name);
		if (itr == mScenes.end())
			return nullptr;
		if (mActiveScene != nullptr)
			mActiveScene->OnExit();
		mActiveScene = itr->second;
		mActiveScene->OnEnter();

		return itr->second;
	}
}