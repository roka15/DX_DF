#include "TileMapToolScene.h"
#include "DontDestroyOnLoad.h"
#include "GameObject.h"
#include "Object.h"
#include "Renderer.h"
#include "Camera.h"
namespace roka
{
	DontDestroyOnLoad* M_DotDestroyObj = DontDestroyOnLoad::GetInstance();
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
		std::vector<std::shared_ptr<GameObject>> objs = M_DotDestroyObj->GetGameObjects();
		for (auto& obj : objs)
		{
			obj->active = GameObject::EState::Active;
		}
	}
	void TileMapToolScene::OnEnter()
	{
		Scene::OnEnter();

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