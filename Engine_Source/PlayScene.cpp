#include "PlayScene.h"
#include "Resources.h"
#include "Renderer.h"

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

namespace roka
{
	PlayScene::PlayScene():Scene(ESceneType::End)
	{
	}
	PlayScene::~PlayScene()
	{
	}
	void PlayScene::Initialize()
	{
		Scene::Initialize();

	

		std::shared_ptr<GameObject> SeriaNPC =
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
			AddGameObject(ELayerType::BackObject,obj);
		}

		std::shared_ptr<GameObject> camera = object::Instantiate<GameObject>(
			Vector3(0.0f, 0.0f, -10.0f),
			ELayerType::Player);
		{
			camera->SetName(L"camera");
			camera->AddScript<CameraScript>();
			std::shared_ptr<Camera> cameraComp = camera->AddComponent<Camera>();
			cameraComp->TurnLayerMask(ELayerType::UI, false);
			AddGameObject(ELayerType::BackObject,camera);
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

