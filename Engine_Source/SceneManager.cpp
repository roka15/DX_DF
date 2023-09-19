#include "SceneManager.h"
#include "..\\Engine\\Prefab.h"
#include "Application.h"
extern roka::Application application;
namespace roka
{
	Scene* SceneManager::mActiveScene = nullptr;
	std::map<std::wstring, Scene*> SceneManager::mScenes;
	void SceneManager::Initialize()
	{
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
		for (auto& itr : mScenes)
		{
			itr.second->Release();
			delete itr.second;
			itr.second = nullptr;
		}
	}
	void SceneManager::Destroy()
	{
		mActiveScene->Destroy();
	}
	Scene* SceneManager::LoadScene(std::wstring name)
	{
		std::map<std::wstring, Scene*>::iterator itr = mScenes.find(name);
		if (itr == mScenes.end())
			return nullptr;
		if (mActiveScene != nullptr)
			mActiveScene->OnExit();

		application.ClearTarget();

		mActiveScene = itr->second;
		mActiveScene->OnEnter();
		return itr->second;
	}
	Scene* SceneManager::LoadScene(ESceneType type)
	{
		std::wstring name = L"";
		switch (type)
		{
		case ESceneType::PlayTestScene:
			name = L"PlayScene";
			break;
		case ESceneType::SeriaRoom:
			name = L"SeriaGateScene";
			break;
		}
		return LoadScene(name);
	}
}