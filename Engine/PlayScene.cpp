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
#include "ObjectPoolManager.h"
#include "NormalMonsterPool.h"
#include "AnimationObjectPool.h"

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
#include "SkillScript.h"
#include "Collider2D.h"
#include "HitBoxScript.h"

#include "ComputeShader.h"
#include "PaintShader.h"

namespace roka
{
	static int test_num = 0;
	PlayScene::PlayScene() :Scene(ESceneType::End)
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
			= FindGameObject(ELayerType::Player, L"Player");
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


		std::shared_ptr<GameObject> player = object::Instantiate<GameObject>(origin);
		player->SetName(L"Player");
		playerScript = player->GetComponent<PlayerScript>();
		playerScript->LateInitialize();
	
		//player->AddComponent<Rigidbody>()->IsGravity(true);

		//cd->SetSize(Vector2(0.05f, 0.2f));
		AddGameObject(ELayerType::Player, player);

		//경직
		std::shared_ptr<GameObject> skill01 = object::Instantiate<GameObject>(
			Vector3(2.0f, 1.0f, 0.0f),
			Vector3::Zero,
			Vector3(1.0f, 1.0f, 1.0f),
			ELayerType::Monster);
		skill01->SetName(L"skill01");
		skill01->AddComponent<Collider2D>();
		std::shared_ptr<HitBoxScript> hitbox = skill01->AddScript<HitBoxScript>();
		hitbox->hitbox = HitBoxScript::EHitBoxType::Top;
		hitbox->hitbox_owner = skill01;
		skill01->AddComponent<SkillScript>()->stun_type = EStunState::Stagger;


		//다운
		std::shared_ptr<GameObject> skill02 = object::Instantiate<GameObject>(
			Vector3(2.0f, -1.0f, 0.0f),
			Vector3::Zero,
			Vector3(1.5f, 0.2f, 1.0f),
			ELayerType::Monster);
		skill02->SetName(L"skill02");
		skill02->AddComponent<Collider2D>();
		hitbox = skill02->AddScript<HitBoxScript>();
		hitbox->hitbox = HitBoxScript::EHitBoxType::Bottom;
		hitbox->hitbox_owner = skill02;
		std::shared_ptr<SkillScript>skillScript = skill02->AddComponent<SkillScript>();
		skillScript->stun_type = EStunState::Down;

		std::shared_ptr<GameObject> monsterOrigin = prefab::Prefabs[L"Spider_MonsterObject"];
		NormalMonsterPool* normalMonsterPool = ObjectPoolManager<NormalMonsterPool, GameObject>::GetInstance();
		for (int i = 0; i < 1; i++)
		{
			std::shared_ptr<GameObject> monster = normalMonsterPool->GetPool(L"SpiderMonster")->Spawn();

			monster->SetName(L"Monster" + std::to_wstring(i));
			monster->GetComponent<Transform>()->position = Vector3(0.5f * i, 0.0f, 0.0f);
			monster->GetComponent<MonsterScript>()->SetTarget(player);
			AddGameObject(ELayerType::Monster, monster);
		}

	

		/*std::shared_ptr<GameObject> TairangOrigin = prefab::Prefabs[L"Tairang_MonsterObject"];
		{
			std::shared_ptr<GameObject> monster = object::Instantiate<GameObject>(TairangOrigin);
			monster->SetName(L"Tiarang");
			monster->GetComponent<Transform>()->position = Vector3(-1.0f, 0.0f, 0.0f);
			monster->GetComponent<MonsterScript>()->SetTarget(player);
			AddGameObject(ELayerType::Monster, monster);
		}*/

		//test
		AnimationObjectPool* aniPool = ObjectPoolManager<AnimationObjectPool, GameObject>::GetInstance();
		/*std::shared_ptr<GameObject> weapon_aniTest = aniPool->GetPool(L"AniObject")->Spawn();
		{
			std::shared_ptr<Transform> tf = weapon_aniTest->GetComponent<Transform>();
			tf->position = Vector3(1.0f, 1.0f, 0.0f);
			tf->scale = Vector3(2.0f, 2.0f, 1.0f);
			float speed = 0.1f;
			std::shared_ptr<Animator> ani1 = weapon_aniTest->GetComponent<Animator>();
			ani1->Create(L"weapon", L"mg_broom7200c.img", L"mg_broom7200c_01", 109, 127, speed);*/
		/*	ani1->Create(L"weapon", L"mg_broom7200c.img", L"mg_broom7200c_02",30, 60, speed);
			ani1->Create(L"weapon", L"mg_broom7200c.img", L"mg_broom7200c_03", 60, 90, speed);
			ani1->Create(L"weapon", L"mg_broom7200c.img", L"mg_broom7200c_04", 90, 120, speed);
			ani1->Create(L"weapon", L"mg_broom7200c.img", L"mg_broom7200c_05", 120, 150, speed);
			ani1->Create(L"weapon", L"mg_broom7200c.img", L"mg_broom7200c_06", 150, 182, speed);*/
			/*std::shared_ptr<GameObject> weapon_Test2 = aniPool->GetPool(L"AniObject")->Spawn();
			weapon_aniTest->AddChild(weapon_Test2);
			std::shared_ptr<Animator> ani2 = weapon_Test2->GetComponent<Animator>();
			ani2->Create(L"weapon", L"mg_broom7200d.img", L"mg_broom7200d_01", 109, 127, speed);*/
			/*ani2->Create(L"weapon", L"mg_broom7200d.img", L"mg_broom7200d_02", 30, 60, speed);
			ani2->Create(L"weapon", L"mg_broom7200d.img", L"mg_broom7200d_03", 60, 90, speed);
			ani2->Create(L"weapon", L"mg_broom7200d.img", L"mg_broom7200d_04", 90, 120, speed);
			ani2->Create(L"weapon", L"mg_broom7200d.img", L"mg_broom7200d_05", 120, 150, speed);
			ani2->Create(L"weapon", L"mg_broom7200d.img", L"mg_broom7200d_06", 150, 182, speed);*/

			/*Animator* ani1_ptr = ani1.get();
			ani1->CompleteEvent(L"mg_broom7200c_01") = std::bind([ani1_ptr]()->void {ani1_ptr->PlayAnimation(L"mg_broom7200c_02", false); });
			ani1->CompleteEvent(L"mg_broom7200c_02") = std::bind([ani1_ptr]()->void {ani1_ptr->PlayAnimation(L"mg_broom7200c_03", false); });
			ani1->CompleteEvent(L"mg_broom7200c_03") = std::bind([ani1_ptr]()->void {ani1_ptr->PlayAnimation(L"mg_broom7200c_04", false); });
			ani1->CompleteEvent(L"mg_broom7200c_04") = std::bind([ani1_ptr]()->void {ani1_ptr->PlayAnimation(L"mg_broom7200c_05", false); });
			ani1->CompleteEvent(L"mg_broom7200c_05") = std::bind([ani1_ptr]()->void {ani1_ptr->PlayAnimation(L"mg_broom7200c_06", false); });
			ani1->CompleteEvent(L"mg_broom7200c_06") = std::bind([ani1_ptr]()->void {ani1_ptr->PlayAnimation(L"mg_broom7200c_01", false); });

			Animator* ani2_ptr = ani2.get();
			ani2->CompleteEvent(L"mg_broom7200d_01") = std::bind([ani2_ptr]()->void {ani2_ptr->PlayAnimation(L"mg_broom7200d_02", false); });
			ani2->CompleteEvent(L"mg_broom7200d_02") = std::bind([ani2_ptr]()->void {ani2_ptr->PlayAnimation(L"mg_broom7200d_03", false); });
			ani2->CompleteEvent(L"mg_broom7200d_03") = std::bind([ani2_ptr]()->void {ani2_ptr->PlayAnimation(L"mg_broom7200d_04", false); });
			ani2->CompleteEvent(L"mg_broom7200d_04") = std::bind([ani2_ptr]()->void {ani2_ptr->PlayAnimation(L"mg_broom7200d_05", false); });
			ani2->CompleteEvent(L"mg_broom7200d_05") = std::bind([ani2_ptr]()->void {ani2_ptr->PlayAnimation(L"mg_broom7200d_06", false); });
			ani2->CompleteEvent(L"mg_broom7200d_06") = std::bind([ani2_ptr]()->void {ani2_ptr->PlayAnimation(L"mg_broom7200d_01", false); });*/

		/*	ani1->PlayAnimation(L"mg_broom7200c_01", true);
			ani2->PlayAnimation(L"mg_broom7200d_01", true);*/
		//}
		//AddGameObject(ELayerType::Player, weapon_aniTest);

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



		/*std::shared_ptr<GameObject> obj = object::Instantiate<GameObject>(Vector3(0.0f, 0.0f, 0.0f), ELayerType::Player);
		obj->SetName(L"player");
		obj->GetComponent<Transform>()->scale = Vector3(3.0f, 3.0f, 1.0f);
		std::shared_ptr<MeshRenderer> mr = obj->AddComponent<MeshRenderer>();
		mr->mesh = Resources::Find<Mesh>(L"RectMesh");
		mr->material = Resources::Find<Material>(L"DefaultAniMaterial");
		std::shared_ptr<Animator> ani = obj->AddComponent<Animator>();
		ani->Create(L"baseskin", L"mg_body80500.img", L"Idle", 10, 13,0.3f);
		ani->Create(L"baseskin", L"mg_body80500.img", L"Right", 0, 9,0.1f);
		ani->PlayAnimation(L"Idle", true);*/

		/*std::shared_ptr<NPK> gate_npk = Resources::Find<NPK>(L"gate");
		if (gate_npk == nullptr)
			gate_npk = Resources::Load<NPK>(L"gate", L"..\\Resources\\npk\\gate.npk");
		std::shared_ptr<Image> img1 = object::Instantiate<Image>(Vector3(0.0f, 0.0f, 0.0f),Vector3::Zero,Vector3(2.0f,2.0f,1.0f), ELayerType::Player);
		img1->SetName(L"image1");
		img1->GetComponent<ImageComponent>()->SetSprite(L"gate", L"gatedown.img", 0);*/
		/*std::shared_ptr<Animator> ani = img1->AddComponent<Animator>();
		ani->Create(L"gate", L"gatedown.img", L"gate", 0, 29, 0.3f);
		ani->PlayAnimation(L"gate", true);
		std::shared_ptr<MeshRenderer> mr = img1->AddComponent<MeshRenderer>();
		mr->material = Resources::Find<Material>(L"DefaultAniMaterial");*/
		/*std::shared_ptr<GameObject> obj = object::Instantiate<GameObject>(Vector3(0.0f, 0.0f, 0.0f), ELayerType::Player);
		obj->SetName(L"obj");
		std::shared_ptr<MeshRenderer> mr = obj->AddComponent<MeshRenderer>();
		mr->mesh = Resources::Find<Mesh>(L"RectMesh");
		mr->material = Resources::Find<Material>(L"DefaultAniMaterial");
		mr->material->shader->bsstate = EBSType::OneOne;
		std::shared_ptr<Animator> ani = obj->AddComponent<Animator>();
		ani->Create(L"gate", L"seriagate_dooreffect.img", L"SeriaDoorEffect", 0, 8);
		ani->PlayAnimation(L"SeriaDoorEffect", true, 0.5f);*/




		//ani->Create();

			/*std::shared_ptr<Image> img2 = object::Instantiate<Image>(Vector3(2.0f, 0.0f, 0.0f), ELayerType::Player);
			img2->GetComponent<ImageComponent>()->SetSprite(L"gate", L"summer_2018_seria.img", 0);*/

			/*std::shared_ptr<GameObject> SeriaNPC =
				object::Instantiate<GameObject>(prefab::Prefabs[L"TestObject"],ELayerType::Player);


			for (int i = 0; i < 2; i++)
			{
				pool::TestPool* pool = pool::TestPool::GetInstance();
				std::shared_ptr<GameObject> obj = pool->GetPool(L"TestObject")->Spawn();
				Vector3 pos = obj->GetComponent<Transform>()->position;
				pos.x += 1.5 * i;
				obj->GetComponent<Transform>()->position = pos;
				const float pi = 3.141592f;
				float degree = pi / 8.0f;
				obj->GetComponent<Transform>()->SetRotation(Vector3(0.0f, 0.0f, degree));
			}
			*/

			/*{
				GameObject* player = new GameObject();
				AddGameObject(ELayerType::Player, player);
				MeshRenderer* mr = player->AddComponent<MeshRenderer>();
				mr->mesh = Resources::Find<Mesh>(L"RectMesh");
				mr->material=Resources::Find<Material>(L"SpriteMaterial");

				Transform* tf = player->GetComponent<Transform>();
				tf->position = Vector3(2.0f, 0.0f, 0.0f);
				tf->scale = Vector3(2.0f, 2.0f, 1.0f);
				{
					std::shared_ptr<NPK> npk = Resources::Load<NPK>(L"mapnpk", L"..\\Resources\\npk\\map.npk");
					std::shared_ptr<Texture> texture = npk->GetTexture(L"seriagate", 0);
					Resources::Insert(L"seriagateTexture", texture);
					mr->material->texture = texture;
				}

			}*/
			/*	{
					GameObject* player = new GameObject();
					AddGameObject(ELayerType::Player, player);
					MeshRenderer* mr = player->AddComponent<MeshRenderer>();
					mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
					mr->SetMaterial(Resources::Find<Material>(L"SpriteMaterial02"));
					player->GetComponent<Transform>()->position = Vector3(0.0f, 0.0f, 0.0f);
				}*/

	}
	void PlayScene::OnExit()
	{
		Scene::OnExit();
		renderer::cameras.clear();
		renderer::MainCamera.reset();
		ObjectPoolManager<NormalMonsterPool, GameObject>::GetInstance()->Release();
	}
	
	void PlayScene::Loading()
	{
	}
}

