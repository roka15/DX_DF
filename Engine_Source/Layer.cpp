#include "Layer.h"
namespace roka
{
	Layer::Layer()
	{
	}
	Layer::~Layer()
	{
		for (GameObject* gameObj : mGameObjects)
		{
			if (gameObj == nullptr)
				continue;
			delete gameObj;
			gameObj = nullptr;
		}
	}
	void Layer::Initialize()
	{
	}
	void Layer::Update()
	{
		for (GameObject* gameObj : mGameObjects)
		{
			if (gameObj->active != GameObject::EState::Active)
				continue;

			gameObj->Update();
		}
	}
	void Layer::LateUpdate()
	{
		for (GameObject* gameObj : mGameObjects)
		{
			if (gameObj->active != GameObject::EState::Active)
				continue;
			gameObj->LateUpdate();
		}
	}
	void Layer::Render()
	{
		for (GameObject* gameObj : mGameObjects)
		{
			if (gameObj->active != GameObject::EState::Active)
				continue;
			gameObj->Render();
		}
	}
	void Layer::Destroy()
	{
		for (std::vector<GameObject*>::iterator itr = mGameObjects.begin();
			itr != mGameObjects.end();)
		{
			if ((*itr)->active == GameObject::EState::Dead)
			{
				GameObject* deleteObj = (*itr);
				itr = mGameObjects.erase(itr);
				delete deleteObj;
				deleteObj = nullptr;
				continue;
			}

			itr++;
		}
	}
	void Layer::AddGameObject(GameObject* gameObj)
	{
		mGameObjects.push_back(gameObj);
	}
	GameObject* Layer::FindGameObject(std::wstring name)
	{
		for (auto& obj : mGameObjects)
		{
			if (obj->GetName().compare(name) == 0)
				return obj;
		}
		return nullptr;
	}
}