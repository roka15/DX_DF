#include "SceneManager.h"
#include "..\\Engine\\Prefab.h"
#include "Application.h"
#include "DontDestroyOnLoad.h"
#include "CollisionManager.h"
#include "Collider2D.h"
#include "GameObject.h"
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
		DontDestroyOnLoad::GetInstance()->Update();
	}
	void SceneManager::LateUpdate()
	{
		mActiveScene->LateUpdate();
		DontDestroyOnLoad::GetInstance()->LateUpdate();
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
		DontDestroyOnLoad::GetInstance()->Release();
	}
	void SceneManager::Destroy()
	{
		mActiveScene->Destroy();
		DontDestroyOnLoad::GetInstance()->Destroy();
	}
	Scene* SceneManager::LoadScene(std::wstring name)
	{
		std::map<std::wstring, Scene*>::iterator itr = mScenes.find(name);
		if (itr == mScenes.end())
			return nullptr;

		CollisionManager::DeleteID();

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
	void SceneManager::AddGameObject(enums::ELayerType type, std::shared_ptr<GameObject> obj)
	{
		mActiveScene->AddGameObject(type, obj);
	}
	void SceneManager::DontDestroy(std::shared_ptr<GameObject> obj)
	{
		DontDestroyOnLoad::GetInstance()->AddGameObject(obj);
	}
	std::shared_ptr<GameObject> SceneManager::FindGameObject(std::wstring key)
	{
		return DontDestroyOnLoad::GetInstance()->FindGameObject(key);
	}
	std::shared_ptr<GameObject> SceneManager::FindGameObject(enums::ELayerType type, std::wstring key)
	{
		return mActiveScene->FindGameObject(type, key);
	}
	std::vector<std::shared_ptr<GameObject>> SceneManager::GetGameObjects()
	{
		std::vector<std::shared_ptr<GameObject>> vec = {};
		std::vector<std::shared_ptr<GameObject>> tempVec = {};
		for (size_t i = 0; i < (UINT)ELayerType::End; i++)
		{
			tempVec = mActiveScene->GetGameObjects((ELayerType)i);
			for (auto& obj : tempVec)
			{
				vec.push_back(obj);
			}
		}
		tempVec = DontDestroyOnLoad::GetInstance()->GetGameObjects();
		for (auto& obj : tempVec)
		{
			vec.push_back(obj);
		}
		return vec;
	}
	std::vector<std::shared_ptr<GameObject>> SceneManager::GetGameObjects(const std::bitset<(UINT)ELayerType::End>& layerMask)
	{
		std::vector<std::shared_ptr<GameObject>> vec = {};
		std::vector<std::shared_ptr<GameObject>> tempVec = {};
		for (size_t i = 0; i < (UINT)ELayerType::End; i++)
		{
			if (layerMask[i] == false)
				continue;

			tempVec = mActiveScene->GetGameObjects((ELayerType)i);
			for (auto& obj : tempVec)
			{
				vec.push_back(obj);
			}
		}
		tempVec = DontDestroyOnLoad::GetInstance()->GetGameObjects();
		for (auto& obj : tempVec)
		{
			enums::ELayerType type = obj->layer_type;
			if (layerMask[(UINT)type] == false)
				continue;
			vec.push_back(obj);
		}
		return vec;
	}
	std::vector<std::shared_ptr<GameObject>> SceneManager::FindGameObjects(enums::ELayerType type)
	{
		std::vector<std::shared_ptr<GameObject>> vec = {};
		vec = mActiveScene->GetGameObjects(type);

		std::vector<std::shared_ptr<GameObject>> ddvec = {};
		ddvec = DontDestroyOnLoad::GetInstance()->FindGameObjects(type);

		for (auto& obj : ddvec)
		{
			vec.push_back(obj);
		}

		return vec;
	}
}