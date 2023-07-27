#include "WestcoastScene.h"
#include "Resources.h"
#include "MeshRenderer.h"
#include "Transform.h"
#include "Camera.h"
#include "CameraScript.h"

#include "Object.h"

#include "Mesh.h"
#include "Material.h"
#include "NPK.h"

#include "Input.h"
namespace roka
{
	WestcoastScene::WestcoastScene() :Scene(ESceneType::AnotherVillage)
	{
	}
	WestcoastScene::~WestcoastScene()
	{
	}
	void WestcoastScene::Initialize()
	{
		Scene::Initialize();
		/*SceneSector* sector1 = new SceneSector();
		sector1->texture_name = L"seriagateTexture";
		SceneSector* sector2 = new SceneSector();
		sector2->texture_name = L"hendonmyre2Texture";
		SceneSector* sector3 = new SceneSector();
		sector3->texture_name = L"hendonmyre3Texture";
		SceneSector* sector4 = new SceneSector();
		sector4->texture_name = L"blackmarketTexture";

		sector1->Register(L"WeastCoastMain", sector2);
		sector2->Register(L"SeriaRoom", sector1);
		sector2->Register(L"WeastCoastPort", sector3);
		sector3->Register(L"WeastCoastMain", sector2);
		sector3->Register(L"BlackMarket", sector4);

		sector = sector2;*/
	}
	void WestcoastScene::Update()
	{
		Scene::Update();
		//test
		/*if (Input::GetKeyDown(roka::EKeyCode::DOWN))
		{
			sector = sector->GetNextInfo(L"WeastCoastPort");
			GameObject* obj = FindGameObject(ELayerType::BackObject, L"BackGround");
			std::wstring key = sector->texture_name;
			obj->GetComponent<MeshRenderer>()->material->texture = Resources::Find<Texture>(key);
		}*/
	}
	void WestcoastScene::LateUpdate()
	{
		Scene::LateUpdate();
	}
	void WestcoastScene::Render()
	{
		Scene::Render();
	}
	void WestcoastScene::OnExit()
	{
		Scene::OnExit();
	}
	void WestcoastScene::OnEnter()
	{
		Scene::OnEnter();
		Loading();
	}
	void WestcoastScene::Loading()
	{
		std::shared_ptr<NPK> npk = Resources::Find<NPK>(L"mapnpk");
		if (npk == nullptr)
			npk = Resources::Load<NPK>(L"mapnpk", L"..\\Resources\\npk\\map.npk");

		{
			std::shared_ptr<GameObject> bg = object::Instantiate<GameObject>(
				Vector3(0.0f, 0.0f, 0.99f),
				Vector3::Zero,
				Vector3(14.0f, 5.5f, 1.0f),
				ELayerType::BackObject);
			bg->SetName(L"BackGround");
			std::shared_ptr<MeshRenderer> mr = bg->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"BGMaterial");

			std::shared_ptr<Texture> texture = npk->GetTexture(L"hendonmyre2", 0);
			npk->GetTexture(L"hendonmyre3", 0);
			mr->material->texture = texture;
		}

		{
			std::shared_ptr<GameObject> camera = object::Instantiate<GameObject>(
				Vector3(0.0f, 0.0f, -10.0f),
				ELayerType::Player);
			camera->AddScript<CameraScript>();
			std::shared_ptr<Camera> cameraComp = camera->AddComponent<Camera>();
		}
	}
}