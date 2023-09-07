#include "Scene.h"
namespace roka
{
	Scene::Scene(ESceneType type) :mType(type)
	{
	}

	Scene::~Scene()
	{
	}

	void Scene::Initialize()
	{
		mLayers.resize((int)ELayerType::End);
	}

	void Scene::Update()
	{
		for (Layer& layer : mLayers)
		{
			layer.Update();
		}
	}

	void Scene::LateUpdate()
	{
		for (Layer& layer : mLayers)
		{
			layer.LateUpdate();
		}
	}

	void Scene::Render()
	{
		for (Layer& layer : mLayers)
		{
			layer.Render();
		}
	}

	void Scene::Destroy()
	{
		for (Layer& layer : mLayers)
		{
			layer.Destroy();
		}
	}

	void Scene::OnExit()
	{
		for (Layer& layer : mLayers)
		{
			layer.Clear();
		}
	}

	void Scene::OnEnter()
	{
	}

	void Scene::Loading()
	{
	}

	void Scene::AddGameObject(ELayerType type, std::shared_ptr<GameObject> gameObj)
	{
		mLayers[(int)type].AddGameObject(gameObj);
	}

	std::shared_ptr<GameObject> Scene::FindGameObject(ELayerType type, std::wstring name)
	{
		return mLayers[(int)type].FindGameObject(name);
	}
	void Scene::RemoveGameObject(ELayerType type, std::wstring name)
	{
		mLayers[(int)type].RemoveGameObject(name);
	}
	void Scene::RemoveGameObject(ELayerType type, std::shared_ptr<GameObject> gameObj)
	{
		mLayers[(int)type].RemoveGameObject(gameObj);
	}
	const std::vector<std::shared_ptr<GameObject>>& Scene::GetGameObjects(ELayerType type)
	{
		return mLayers[(int)type].GetGameObjects();
	}
}

