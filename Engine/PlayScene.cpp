#include "PlayScene.h"
#include "Resources.h"
#include "Renderer.h"
#include "Input.h"

#include "MeshRenderer.h"
#include "CameraScript.h"
#include "Transform.h"
#include "Camera.h"
#include "Mesh.h"
#include "NPK.h"
#include "Object.h"
#include "CollisionManager.h"
#include "PartManager.h"
#include "PortalManager.h"
#include "ObjectPoolManager.h"
#include "NormalMonsterPool.h"
#include "AnimationObjectPool.h"
#include "RokaTime.h"



#include "MoveScript.h"
#include "ObjectPool.h"
#include "Prefab.h"
#include "TestPool.h"
#include "Image.h"
#include "ImageComponent.h"
#include "Light.h"
#include "Animator.h"
#include "Rigidbody.h"
#include "PlayerScript.h"
#include "MonsterScript.h"
#include "AvatarScript.h"
#include "PartScript.h"
#include "Collider2D.h"

#include "ComputeShader.h"
#include "PaintShader.h"

namespace roka
{
	static int test_num = 0;
	PlayScene::PlayScene() :Scene(ESceneType::PlayTestScene)
	{
	}
	PlayScene::~PlayScene()
	{
		OnExit();
	}
	void PlayScene::Initialize()
	{
		Scene::Initialize();


		
	}

	void PlayScene::Update()
	{
		Scene::Update();

		std::shared_ptr<GameObject> obj
			= SceneManager::FindGameObject(L"Player");
	
		std::shared_ptr<GameObject> obj2
			= FindGameObject(ELayerType::Player, L"AnotherPlayer");

		std::shared_ptr<PlayerScript> ps
			= obj->GetComponent<PlayerScript>();

		if (Input::GetKeyDown(EKeyCode::LEFT))
			ps->LeftBtnDown();
		if (Input::GetKeyUp(EKeyCode::LEFT))
			ps->LeftBtnUp();
		if (Input::GetKeyDown(EKeyCode::RIGHT))
			ps->RightBtnDown();
		if (Input::GetKeyUp(EKeyCode::RIGHT))
			ps->RightBtnUp();
		if (Input::GetKeyDown(EKeyCode::UP))
			ps->UpBtnDown();
		if (Input::GetKeyUp(EKeyCode::UP))
			ps->UpBtnUp();
		if (Input::GetKeyDown(EKeyCode::DOWN))
			ps->DownBtnDown();
		if (Input::GetKeyUp(EKeyCode::DOWN))
			ps->DownBtnUp();
		if (Input::GetKeyDown(EKeyCode::X))
			ps->NomalAtkBtnDown();
		if (Input::GetKeyDown(EKeyCode::F))
			ps->Skill((UINT)EKeyCode::F);

		//if (Input::GetKeyDown(EKeyCode::F))
		//{
		//	obj->GetComponent<Rigidbody>()->AddForce(Vector2(30.0f, 60*980.0f));
		//	obj->GetComponent<Rigidbody>()->disableGround();
		//}
		//
		if (Input::GetKeyDown(EKeyCode::G))
		{
			test_num += 90;
			if (test_num > 360)
				test_num = 0;
			if (obj2 != nullptr)
				obj2->GetComponent<Transform>()->rotation = Vector3(0.0, 0.0, Deg2Rad(test_num));
		}
		if (Input::GetKeyDown(EKeyCode::SPACE))
			ps->JumpBtnDown();
	}

	void PlayScene::LateUpdate()
	{
		Scene::LateUpdate();
	}

	void PlayScene::Render()
	{
		Scene::Render();
	}
	void PlayScene::OnEnter()
	{
		ObjectPoolManager<NormalMonsterPool, GameObject>::GetInstance()->Initialize();
		//std::shared_ptr<PaintShader> paintShader = Resources::Find<PaintShader>(L"PaintShader");
		//std::shared_ptr<Texture> paintTexture = Resources::Find<Texture>(L"PaintTexture");
		//paintShader->SetTarget(paintTexture);
		//paintShader->OnExcute();

		//std::shared_ptr<Image> smile = object::Instantiate<Image>();
		//smile->SetName(L"Smile");
		//AddGameObject(ELayerType::BackObject, smile);
		//std::shared_ptr<MeshRenderer> mr = smile->AddComponent<MeshRenderer>();
		//mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		//mr->SetMaterial(Resources::Find<Material>(L"PaintMaterial"));
		//smile->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
		//std::shared_ptr<Collider2D> cd = smile->AddComponent<Collider2D>();

		std::shared_ptr<GameObject> light = object::Instantiate<GameObject>();
		light->SetName(L"main_light");
		AddGameObject(ELayerType::Light, light);
		std::shared_ptr<Light> lightComp = light->AddComponent<Light>();
		lightComp->SetType(ELightType::Directional);
		lightComp->SetColor(Vector4(1.0f, 1.0f, 1.0f, 1.0f));


		//point light
		/*std::shared_ptr<GameObject> light = object::Instantiate<GameObject>();
		light->SetName(L"light");
		AddGameObject(ELayerType::Light, light);
		std::shared_ptr<Light> lightComp = light->AddComponent<Light>();
		lightComp->SetType(ELightType::Directional);
		lightComp->SetColor(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
		lightComp->SetType(ELightType::Point);
		lightComp->SetRadius(3.0f);*/


		/* player script text*/
		std::shared_ptr<GameObject> origin = prefab::Prefabs[L"PlayerObject"];

		std::shared_ptr<GameObject> another_player = object::Instantiate<GameObject>(origin);
		another_player->SetName(L"AnotherPlayer");
		another_player->GetComponent<Transform>()->position = Vector3(-2.0f, 0.0f, 0.0f);
		std::shared_ptr<PlayerScript> playerScript = another_player->GetComponent<PlayerScript>();
		playerScript->LateInitialize();
	
		//another_player->GetComponent<Transform>()->rotation = Vector3(0.0f, 0.0f, Deg2Rad(90.0f));
		AddGameObject(ELayerType::Player, another_player);

		std::shared_ptr<GameObject> player
			=SceneManager::FindGameObject(L"Player");
		std::vector<std::shared_ptr<Collider2D>> playercols = player->GetChilds<Collider2D>();
		

		//경직
		std::shared_ptr<GameObject> skill01 = object::Instantiate<GameObject>(
			Vector3(2.0f, 1.0f, 0.0f),
			Vector3::Zero,
			Vector3(1.0f, 1.0f, 1.0f),
			ELayerType::Monster);
		skill01->SetName(L"skill01");
		skill01->AddComponent<Collider2D>();
		


		//다운
		std::shared_ptr<GameObject> skill02 = object::Instantiate<GameObject>(
			Vector3(2.0f, -1.0f, 0.0f),
			Vector3::Zero,
			Vector3(1.5f, 0.2f, 1.0f),
			ELayerType::Monster);
		skill02->SetName(L"skill02");
		skill02->AddComponent<Collider2D>();
		
		std::shared_ptr<GameObject> monsterOrigin = prefab::Prefabs[L"Spider_MonsterObject"];
		NormalMonsterPool* normalMonsterPool = ObjectPoolManager<NormalMonsterPool, GameObject>::GetInstance();
		for (int i = 0; i < 1; i++)
		{
			std::shared_ptr<GameObject> monster = normalMonsterPool->Spawn(L"SpiderMonster");

			monster->SetName(L"Monster" + std::to_wstring(i));
			monster->GetComponent<Transform>()->position = Vector3(0.5f * i, 0.0f, 0.0f);
			monster->GetComponent<MonsterScript>()->SetTarget(player);
			AddGameObject(ELayerType::Monster, monster);
		}

	

		std::shared_ptr<GameObject> TairangOrigin = prefab::Prefabs[L"Tairang_MonsterObject"];
		{
			std::shared_ptr<GameObject> monster = object::Instantiate<GameObject>(TairangOrigin);
			monster->SetName(L"Tiarang");
			monster->GetComponent<Transform>()->position = Vector3(-1.0f, 0.0f, 0.0f);
			monster->GetComponent<MonsterScript>()->SetTarget(player);
			AddGameObject(ELayerType::Monster, monster);
		}


		CollisionManager::SetLayer(ELayerType::Player, ELayerType::Player, true);
		CollisionManager::SetLayer(ELayerType::Monster, ELayerType::Player, true);
		CollisionManager::SetLayer(ELayerType::Skill, ELayerType::Player, true);

		std::shared_ptr<GameObject> camera = object::Instantiate<GameObject>(
			Vector3(0.0f, 0.0f, -10.0f),
			ELayerType::Player);
		{
			camera->SetName(L"camera");
			camera->AddScript<CameraScript>();
			std::shared_ptr<Camera> cameraComp = camera->AddComponent<Camera>();
			cameraComp->TurnLayerMask(ELayerType::UI, false);
			renderer::MainCamera = cameraComp;
		}
		std::shared_ptr<GameObject> portal01 = object::Instantiate<GameObject>(
			Vector3(-1.0f, 2.0f, 0.0f),
			Vector3::Zero,
			Vector3(1.0f, 1.0f, 1.0f),
			ELayerType::Portal
			);
		std::shared_ptr<Collider2D> portalCol = portal01->AddComponent<Collider2D>();
		Portal* portal = manager::PortalManager::GetInstance()->Find(EPortalType::PlayTestUp);
		portal->SetCollisionListener(portal01);
		
		CollisionManager::RegisterID(portalCol, playercols[0]);
		CollisionManager::RegisterID(portalCol, playercols[1]);

		CollisionManager::SetLayer(ELayerType::Player, ELayerType::Portal, true);
	}
	void PlayScene::OnExit()
	{
		Time::Clear();
		Scene::OnExit();
		renderer::MainCamera->Release();
		renderer::cameras.clear();
		renderer::MainCamera.reset();
		ObjectPoolManager<NormalMonsterPool, GameObject>::GetInstance()->Release();
	}
	
	void PlayScene::Loading()
	{
	}
}

