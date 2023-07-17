#include "HendonmyreScene.h"
#include "Resources.h"
#include "MeshRenderer.h"
#include "Transform.h"
#include "Camera.h"
#include "CameraScript.h"

#include "Object.h"

#include "Mesh.h"
#include "Material.h"
#include "NPK.h"
namespace roka
{
	HendonmyreScene::HendonmyreScene():Scene(ESceneType::AnotherVillage)
	{
	}

	HendonmyreScene::~HendonmyreScene()
	{
	}

	void HendonmyreScene::Initialize()
	{
		Scene::Initialize();
	}

	void HendonmyreScene::Update()
	{
		Scene::Update();
	}

	void HendonmyreScene::LateUpdate()
	{
		Scene::LateUpdate();
	}

	void HendonmyreScene::Render()
	{
		Scene::Render();
	}

	void HendonmyreScene::OnExit()
	{
		Scene::OnExit();
	}

	void HendonmyreScene::OnEnter()
	{
		Scene::OnEnter();
		std::shared_ptr<GameObject> bg = object::Instantiate<GameObject>();
		AddGameObject(ELayerType::BackObject, bg);
		std::shared_ptr<MeshRenderer> mr = bg->AddComponent<MeshRenderer>();
		mr->mesh = Resources::Find<Mesh>(L"RectMesh");
		mr->material = Resources::Find<Material>(L"BGMaterial");

		std::shared_ptr<Transform> tf = bg->GetComponent<Transform>();
		tf->position = Vector3(0.0f, 0.0f, 0.0f);
		tf->scale = Vector3(40.0f, 9.0f, 1.0f);
		{
			std::shared_ptr<NPK> npk = Resources::Find<NPK>(L"mapnpk");
			if (npk == nullptr)
				npk = Resources::Load<NPK>(L"mapnpk", L"..\\Resources\\npk\\map.npk");

			std::shared_ptr<Texture> texture = npk->GetTexture(L"hendonmyre", 0);
			Resources::Insert(L"hendonmyreTexture", texture);
			mr->material->texture = texture;
		}

		{
			std::shared_ptr<GameObject>  camera = object::Instantiate<GameObject>();
			AddGameObject(ELayerType::Player, camera);
			camera->AddScript<CameraScript>();
			std::shared_ptr<Camera> cameraComp = camera->AddComponent<Camera>();
			camera->GetComponent<Transform>()->position = Vector3(0.0f, 0.0f, -10.0f);
		}
	}

	void HendonmyreScene::Loading()
	{
	}

}
