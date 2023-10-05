#include "TileMapToolScene.h"
#include "DontDestroyOnLoad.h"
#include "GameObject.h"
#include "Object.h"
#include "Renderer.h"
#include "Camera.h"
#include "Application.h"

extern roka::DontDestroyOnLoad* M_DotDestroyObj;
extern roka::Application* applications[2];
namespace roka
{
	TileMapToolScene::TileMapToolScene() :Scene(ESceneType::TileMapTool)
	{
	}
	TileMapToolScene::~TileMapToolScene()
	{
	}
	void TileMapToolScene::Initialize()
	{
		Scene::Initialize();
	}
	void TileMapToolScene::Update()
	{
		Scene::Update();
	}
	void TileMapToolScene::LateUpdate()
	{
		Scene::LateUpdate();
	}
	void TileMapToolScene::Render()
	{
		Scene::Render();
	}
	void TileMapToolScene::Release()
	{
		Scene::Release();
	}
	void TileMapToolScene::Destroy()
	{
		Scene::Destroy();
	}
	void TileMapToolScene::OnExit()
	{
		Scene::OnExit();
		applications[(UINT)EApplicationType::Main]->SetEditObjRender(false);
		std::vector<std::shared_ptr<GameObject>> objs = M_DotDestroyObj->GetGameObjects();
		for (auto& obj : objs)
		{
			obj->active = GameObject::EState::Active;
		}
	}
	void TileMapToolScene::OnEnter()
	{
		Scene::OnEnter();
		applications[(UINT)EApplicationType::Main]->SetEditObjRender(true);
		std::shared_ptr<GameObject> camera = object::Instantiate<GameObject>(
			Vector3(0.0f, 0.0f, -10.0f),
			ELayerType::Player);
		{
			camera->SetName(L"camera");
		
			std::shared_ptr<Camera> cameraComp = camera->AddComponent<Camera>();
			cameraComp->TurnLayerMask(ELayerType::UI, false);
			cameraComp->TurnLayerMask(ELayerType::Raycast, false);
			renderer::MainCamera = cameraComp;
		}

		std::vector<std::shared_ptr<GameObject>> objs =  M_DotDestroyObj->GetGameObjects();
		for (auto& obj : objs)
		{
			obj->active = GameObject::EState::Paused;
		}
	}
	void TileMapToolScene::Loading()
	{
		Scene::Loading();
	}
}