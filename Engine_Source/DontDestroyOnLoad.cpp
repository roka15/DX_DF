#include "DontDestroyOnLoad.h"
#include "GameObject.h"
namespace roka
{
	DontDestroyOnLoad::DontDestroyOnLoad()
	{
	}

	void DontDestroyOnLoad::Initialize()
	{
	}

	void DontDestroyOnLoad::Update()
	{
		for (auto& obj : mGameObjects)
		{
			obj->Update();
		}
	}

	void DontDestroyOnLoad::LateUpdate()
	{
		for (auto& obj : mGameObjects)
		{
			obj->LateUpdate();
		}
	}

	void DontDestroyOnLoad::Destroy()
	{
		for (std::vector<std::shared_ptr<GameObject>>::iterator itr = mGameObjects.begin();
			itr != mGameObjects.end();)
		{
			if ((*itr)->active == GameObject::EState::Dead)
			{
				itr = mGameObjects.erase(itr);
				continue;
			}
			else if ((*itr)->GetChildCont() != 0)
			{
				(*itr)->ChildDestroy();
			}
			itr++;
		}
	}

	void DontDestroyOnLoad::Release()
	{
		mGameObjects.clear();
	}

	std::shared_ptr<GameObject> DontDestroyOnLoad::FindGameObject(std::wstring name)
	{
		for (auto obj : mGameObjects)
		{
			if (obj->GetName().compare(name) == 0)
				return obj;
		}
		return nullptr;
	}

	std::vector<std::shared_ptr<GameObject>> DontDestroyOnLoad::GetGameObjects()
	{
		return mGameObjects;
	}

	std::vector<std::shared_ptr<GameObject>> DontDestroyOnLoad::FindGameObjects(enums::ELayerType type)
	{
		std::vector<std::shared_ptr<GameObject>> vec;
		for (auto& obj : mGameObjects)
		{
			if (obj->layer_type == type)
				vec.push_back(obj);
		}
		return vec;
	}

}
