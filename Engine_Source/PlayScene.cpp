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

#include "MoveScript.h"
#include "ObjectPool.h"
#include "Prefab.h"
#include "TestPool.h"
#include "Image.h"
#include "ImageComponent.h"
#include "Animator.h"

namespace roka
{
	PlayScene::PlayScene() :Scene(ESceneType::End)
	{
	}
	PlayScene::~PlayScene()
	{
	}
	void PlayScene::Initialize()
	{
		Scene::Initialize();


		/*std::shared_ptr<NPK> npc_npk = Resources::Find<NPK>(L"baseskin");
		if (npc_npk == nullptr)
			npc_npk = Resources::Load<NPK>(L"baseskin", L"..\\Resources\\npk\\baseskin.npk");*/

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

		std::shared_ptr<NPK> gate_npk = Resources::Find<NPK>(L"gate");
		if (gate_npk == nullptr)
			gate_npk = Resources::Load<NPK>(L"gate", L"..\\Resources\\npk\\gate.npk");
		std::shared_ptr<Image> img1 = object::Instantiate<Image>(Vector3(0.0f, 0.0f, 0.0f),Vector3::Zero,Vector3(2.0f,2.0f,1.0f), ELayerType::Player);
		img1->SetName(L"image1");
		img1->GetComponent<ImageComponent>()->SetSprite(L"gate", L"gatedown.img", 0);
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

	void PlayScene::Update()
	{
		Scene::Update();
		static int num = 0;
		static EKeyCode code;
		/*std::shared_ptr<GameObject> obj = SceneManager::GetActiveScene()->FindGameObject(ELayerType::Player, L"player");
		if (Input::GetKeyUp(EKeyCode::RIGHT))
		{
			code = EKeyCode::S;
			obj->GetComponent<Animator>()->PlayAnimation(L"Idle", true);
		}
		if (Input::GetKeyUp(EKeyCode::LEFT))
		{
			code = EKeyCode::S;
			obj->GetComponent<MeshRenderer>()->material->shader = Resources::Find<Shader>(L"AnimationShader");
			obj->GetComponent<Animator>()->PlayAnimation(L"Idle", true);
		}
		
		if (Input::GetKey(EKeyCode::RIGHT)&& code !=EKeyCode::RIGHT)
		{
			code = EKeyCode::RIGHT;
			obj->GetComponent<Animator>()->PlayAnimation(L"Right", true);
		}
		if (Input::GetKey(EKeyCode::LEFT) && code != EKeyCode::LEFT)
		{
			code = EKeyCode::LEFT;
			obj->GetComponent<MeshRenderer>()->material->shader = Resources::Find<Shader>(L"VerticalInverterAnimationShader");
			obj->GetComponent<Animator>()->PlayAnimation(L"Right", true);
		}*/
		if (Input::GetKeyDown(EKeyCode::SPACE))
		{
			std::shared_ptr<GameObject> obj = SceneManager::GetActiveScene()->FindGameObject(ELayerType::Player, L"image1");
			obj->GetComponent<ImageComponent>()->SetSprite(L"gate", L"gatedown.img", num++);
			if (num == 29)
				num = 0;
		}
	}

	void PlayScene::LateUpdate()
	{
		Scene::LateUpdate();
	}

	void PlayScene::Render()
	{
		Scene::Render();
	}
	void PlayScene::Loading()
	{
	}
}

