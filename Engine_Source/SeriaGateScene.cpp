#include "SeriaGateScene.h"
#include "Resources.h"
#include "MeshRenderer.h"
#include "Transform.h"
#include "Camera.h"
#include "CameraScript.h"

#include "Mesh.h"
#include "Material.h"
#include "NPK.h"
roka::SeriaGateScene::SeriaGateScene():Scene(ESceneType::DefaultVillage)
{
}

roka::SeriaGateScene::~SeriaGateScene()
{
}

void roka::SeriaGateScene::Initialize()
{
	Scene::Initialize();
}

void roka::SeriaGateScene::Update()
{
	Scene::Update();
}

void roka::SeriaGateScene::LateUpdate()
{
	Scene::LateUpdate();
}

void roka::SeriaGateScene::Render()
{
	Scene::Render();
}

void roka::SeriaGateScene::OnExit()
{
	Scene::OnExit();
}

void roka::SeriaGateScene::OnEnter()
{
	Scene::OnEnter();

	
	{
	GameObject* bg = new GameObject();
	bg->SetName(L"BackGround");
	bg->ismove = false;
	AddGameObject(ELayerType::BackObject, bg);
	MeshRenderer* mr = bg->AddComponent<MeshRenderer>();
	mr->mesh = Resources::Find<Mesh>(L"RectMesh");
	mr->material = Resources::Find<Material>(L"BGMaterial");

	Transform* tf = bg->GetComponent<Transform>();
	tf->position = Vector3(0.0f, 0.0f, 0.9f);
	tf->scale = Vector3(16.0f, 8.8f, 1.0f);
	{
		std::shared_ptr<NPK> npk = Resources::Find<NPK>(L"mapnpk");
			if(npk==nullptr)
				npk = Resources::Load<NPK>(L"mapnpk", L"..\\Resources\\npk\\map.npk");

		std::shared_ptr<Texture> texture = npk->GetTexture(L"seriagate", 0);
		Resources::Insert(L"seriagateTexture", texture);
		mr->material->texture = texture;
	}
	}

	//test
	GameObject* bg = new GameObject();
	bg->SetName(L"Smile");
	AddGameObject(ELayerType::Player, bg);
	MeshRenderer* mr = bg->AddComponent<MeshRenderer>();
	mr->mesh = Resources::Find<Mesh>(L"RectMesh");
	mr->material = Resources::Find<Material>(L"SpriteMaterial");

	Transform* tf = bg->GetComponent<Transform>();
	tf->position = Vector3(0.0f, 0.0f, 0.0f);
	mr->material->texture = Resources::Find<Texture>(L"Smile");

	{
		GameObject* camera = new GameObject();
		AddGameObject(ELayerType::Player, camera);
		camera->AddComponent<CameraScript>();
		Camera* cameraComp = camera->AddComponent<Camera>();
		cameraComp->TurnLayerMask(ELayerType::UI, false);
		camera->GetComponent<Transform>()->position = Vector3(0.0f, 0.0f, -10.0f);
	}

	{
		GameObject* camera = new GameObject();
		AddGameObject(ELayerType::UI, camera);
		Camera* cameraComp = camera->AddComponent<Camera>();
		cameraComp->DisableLayerMasks();
		cameraComp->TurnLayerMask(ELayerType::UI,true);
		camera->GetComponent<Transform>()->position = Vector3(0.0f, 0.0f, -10.0f);
	}
}

void roka::SeriaGateScene::Loading()
{
}
