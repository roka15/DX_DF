#include "Layer.h"
#include "Transform.h"
namespace roka
{
	Layer::Layer()
	{
	}
	Layer::~Layer()
	{
		if (mGameObjects.size() == 0)
			return;
		std::shared_ptr<GameObject>& ptr = *(mGameObjects.begin());
		mGameObjects.clear();
	}
	void Layer::Initialize()
	{
	}
	void Layer::Update()
	{
		for (std::shared_ptr<GameObject> gameObj : mGameObjects)
		{
			if (gameObj->active != GameObject::EState::Active)
				continue;

			gameObj->Update();
		}
	}
	void Layer::LateUpdate()
	{
		for (std::shared_ptr<GameObject> gameObj : mGameObjects)
		{
			if (gameObj->active != GameObject::EState::Active)
				continue;
			gameObj->LateUpdate();
		}
	}
	void Layer::Render()
	{
		for (std::shared_ptr<GameObject> gameObj : mGameObjects)
		{
			if (gameObj->active != GameObject::EState::Active)
				continue;
			gameObj->Render();
		}
	}
	void Layer::Destroy()
	{
		for (std::vector<std::shared_ptr<GameObject>>::iterator itr = mGameObjects.begin();
			itr != mGameObjects.end();)
		{
			if ((*itr)->active == GameObject::EState::Dead)
			{
				itr = mGameObjects.erase(itr);
				continue;
			}
			itr++;
		}
	}
	void Layer::AddGameObject(std::shared_ptr<GameObject> gameObj)
	{
		mGameObjects.push_back(gameObj);
	}
    void Layer::Clear()
    {
		mGameObjects.clear();
    }
    std::shared_ptr<GameObject> Layer::FindGameObject(std::wstring name)
	{
		for (auto obj : mGameObjects)
		{
			if (obj->GetName().compare(name) == 0)
				return obj;
		}
		return nullptr;
	}
	void Layer::RemoveGameObject(std::wstring name)
	{
		for (int i=0;i<mGameObjects.size();i++)
		{
			if (mGameObjects[i]->GetName().compare(name) == 0)
			{
				mGameObjects.erase(mGameObjects.begin() + i);
				return;
			}
		}
	}
	void Layer::RemoveGameObject(std::shared_ptr<GameObject> gameObj)
	{
		for (int i = 0; i < mGameObjects.size(); i++)
		{
			if (mGameObjects[i] == gameObj)
			{
				mGameObjects.erase(mGameObjects.begin() + i);
				return;
			}
		}
	}
}