#include "PlayScene.h"
#include "Resources.h"
#include "MeshRenderer.h"
#include "CameraScript.h"
#include "Transform.h"
#include "Camera.h"
#include "Mesh.h"
namespace roka
{
	PlayScene::PlayScene()
	{
	}
	PlayScene::~PlayScene()
	{
	}
	void PlayScene::Initialize()
	{
		Scene::Initialize();
		{
			GameObject* player = new GameObject();
			AddGameObject(ELayerType::Player, player);
			MeshRenderer* mr = player->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SpriteMaterial"));
			player->GetComponent<Transform>()->position = Vector3(2.0f, 0.0f, 0.0f);
		}
		{
			GameObject* player = new GameObject();
			AddGameObject(ELayerType::Player, player);
			MeshRenderer* mr = player->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SpriteMaterial02"));
			player->GetComponent<Transform>()->position = Vector3(0.0f, 0.0f, 0.0f);
		}
		{
			GameObject* camera = new GameObject();
			AddGameObject(ELayerType::Player, camera);
			camera->AddComponent<CameraScript>();
			Camera* cameraComp = camera->AddComponent<Camera>();
			camera->GetComponent<Transform>()->position = Vector3(0.0f, 0.0f, -10.0f);
		}
	}

	void PlayScene::Update()
	{
		Scene::Update();                                         
	}

	void PlayScene::LateUpdate()
	{
		Scene::LateUpdate();
	}

	void PlayScene::Render()
	{
		Scene::Render();
	}
}

