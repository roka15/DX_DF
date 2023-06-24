#include "Scene.h"

roka::Scene::Scene()
{
}

roka::Scene::~Scene()
{
}

void roka::Scene::Initialize()
{
	mLayers.resize((int)ELayerType::End);
}

void roka::Scene::Update()
{
	for (Layer& layer : mLayers)
	{
		layer.Update();
	}
}

void roka::Scene::LateUpdate()
{
	for (Layer& layer : mLayers)
	{
		layer.LateUpdate();
	}
}

void roka::Scene::Render()
{
	for (Layer& layer : mLayers)
	{
		layer.Render();
	}
}

void roka::Scene::OnExit()
{
}

void roka::Scene::OnEnter()
{
}

void roka::Scene::AddGameObject(ELayerType type, GameObject* gameObj)
{
	mLayers[(int)type].AddGameObject(gameObj);
}
