#include "PlayScene.h"
#include "Resources.h"
#include "MeshRenderer.h"
#include "CameraScript.h"
#include "Transform.h"
#include "Camera.h"
#include "Mesh.h"
#include "NPK.h"
#include "Object.h"

#include "MoveScript.h"
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

		std::shared_ptr<NPK> npc_npk = Resources::Find<NPK>(L"npc");
		if (npc_npk == nullptr)
			npc_npk = Resources::Load<NPK>(L"npc", L"..\\Resources\\npk\\npc.npk");

		GameObject* SeriaNPC = object::Instantiate<GameObject>(
			Vector3(0.0f, 0.0f, 0.98f),
			Vector3::Zero,
			Vector3(0.4f, 0.875f, 1.0f),
			ELayerType::BackObject);
		{
			SeriaNPC->SetName(L"SeriaNPC");
			//SeriaNPC->ismove = false;
			std::shared_ptr<MeshRenderer> mr = SeriaNPC->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"SeriaTextureMaterial01");
			{
				std::shared_ptr<Texture> texture = npc_npk->GetTexture(L"seria_event_2012summer.img", 0);
				mr->material->texture = texture;
			}
		}

		GameObject* dst = object::Instantiate<GameObject>(SeriaNPC,ELayerType::BackObject);
		dst->SetName(L"dst");
		dst->ismove = true;
		dst->AddScript<MoveScript>();
		

		dst->GetComponent<Transform>()->position = Vector3(0.5f, 0.0f, 0.9f);
		int a = 0;

		GameObject* camera = object::Instantiate<GameObject>(
			Vector3(0.0f, 0.0f, -10.0f),
			ELayerType::Player);
		{
			camera->SetName(L"camera");
			camera->AddScript<CameraScript>();
			std::shared_ptr<Camera> cameraComp = camera->AddComponent<Camera>();
			cameraComp->TurnLayerMask(ELayerType::UI, false);
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

