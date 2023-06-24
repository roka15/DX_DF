#include "SceneManager.h"

#include "PlayScene.h"
namespace roka
{
	Scene* SceneManager::mActiveScene = nullptr;
	std::map<std::wstring, Scene*> SceneManager::mScenes;
	void SceneManager::Initialize()
	{
		mActiveScene = new PlayScene();
		mScenes.insert(std::make_pair(L"PlayScene",mActiveScene));
		mActiveScene->Initialize();
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
		mActiveScene->OnExit();
		mActiveScene = itr->second;
		mActiveScene->OnEnter();
		
		return itr->second;
	}
}