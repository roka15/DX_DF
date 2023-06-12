#include "Scene.h"

roka::Scene::Scene()
{
}

roka::Scene::~Scene()
{
}

void roka::Scene::Initialize()
{
}

void roka::Scene::Update()
{
	for (GameObject* gameObj : mGameObjects)
	{
		gameObj->Update();
	}
}

void roka::Scene::LateUpdate()
{
}

void roka::Scene::Render()
{
	for (GameObject* gameObj : mGameObjects)
	{
		gameObj->Render();
	}
}
