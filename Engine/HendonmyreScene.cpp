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
	HendonmyreScene::HendonmyreScene():Scene(ESceneType::End)
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
		std::shared_ptr<GameObject> bg = 
			object::Instantiate<GameObject>(
				Vector3(0.0f, 0.0f, 0.99f),
				Vector3::Zero,
				Vector3(20.0f, 5.0f, 1.0f),
				ELayerType::BackObject);
		std::shared_ptr<MeshRenderer> mr = bg->AddComponent<MeshRenderer>();
		mr->mesh = Resources::Find<Mesh>(L"RectMesh");
		mr->material = Resources::Find<Material>(L"BGMaterial");

		{
			std::shared_ptr<NPK> npk = Resources::Find<NPK>(L"mapnpk");
			if (npk == nullptr)
				npk = Resources::Load<NPK>(L"mapnpk", L"..\\Resources\\npk\\map.npk");

			std::shared_ptr<Texture> texture = npk->GetTexture(L"hendonmyre", 0);
			Resources::Insert(L"hendonmyreTexture", texture);
			mr->material->texture = texture;
		}

		{
			std::shared_ptr<GameObject>  camera = 
				object::Instantiate<GameObject>(
					Vector3(0.0f, 0.0f, -10.0f),
					ELayerType::Player);
			camera->AddScript<CameraScript>();
			std::shared_ptr<Camera> cameraComp = camera->AddComponent<Camera>();
		}
	}

	void HendonmyreScene::Loading()
	{
	}

}
