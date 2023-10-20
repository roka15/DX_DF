#include "SeriaGateScene.h"
#include "Resources.h"

#include "RokaTime.h"
#include "Object.h"
#include "Image.h"
#include "Light.h"
#include "CollisionManager.h"
#include "PortalManager.h"

#include "Mesh.h"
#include "Material.h"

#include "NPK.h"
#include "Prefab.h"
#include "Input.h"
#include "Renderer.h"

#include "Collider2D.h"
#include "MeshRenderer.h"
#include "Transform.h"
#include "Camera.h"
#include "CameraScript.h"
#include "GridScript.h"
#include "ImageComponent.h"
#include "Animator.h"
#include "PlayerScript.h"
#include "ChangeSizeOverTime.h"
#include "ScrollView.h"
#include "ScrollRect.h"
#include "GridGroupLayout.h"

#include "GaugeManager.h"
#include "GaugeScript.h"
#include "ItemManager.h"
#include "ItemScript.h"
#include "InputManager.h"
#include "AudioClip.h"
#include "AudioSource.h"
#include "Text.h"

roka::SeriaGateScene::SeriaGateScene() :Scene(ESceneType::SeriaRoom)
{
}

roka::SeriaGateScene::~SeriaGateScene()
{
}

void roka::SeriaGateScene::Initialize()
{
	Scene::Initialize();
	std::shared_ptr<NPK> hud_npk = Resources::Find<NPK>(L"ui_hud");

	std::shared_ptr<NPK> inven_npk = Resources::Find<NPK>(L"inventory");
	std::shared_ptr<NPK> tooltip_npk = Resources::Find<NPK>(L"tooltip");
	std::shared_ptr<NPK> baseskin_npk = Resources::Find<NPK>(L"baseskin");


	/*{
		std::shared_ptr<roka::Image> testimg = object::Instantiate<roka::Image>();
		testimg->SetName(L"TestImage");
		testimg->AddComponent <Collider2D>();
		std::shared_ptr<Transform> tf = testimg->GetComponent<Transform>();
		tf->scale = Vector3(1.0f, 1.0f, 1.0f);
		std::shared_ptr<MeshRenderer> mesh = testimg->GetComponent<MeshRenderer>();
		mesh->mesh = Resources::Find<Mesh>(L"RectMesh");
		mesh->material->shader = Resources::Find<Shader>(L"AtlasShader");
		mesh->material->texture = baseskin_npk->CreateAtlas(L"mg_body80500.img", 0, 1, L"TestTexture");
		std::shared_ptr<ImageComponent> imageComp = testimg->GetComponent<ImageComponent>();
		imageComp->SetSprite(0);
		AddGameObject(ELayerType::BackObject, testimg);
	}*/




	
}

void roka::SeriaGateScene::Update()
{
	Scene::Update();
	/*std::shared_ptr<GameObject> obj
		= SceneManager::FindGameObject(L"Player");
	if (obj != nullptr)
	{
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
		if (Input::GetKeyDown(EKeyCode::SPACE))
			ps->JumpBtnDown();
		if (Input::GetKeyDown(EKeyCode::F))
			ps->Skill((UINT)EKeyCode::F);
	}*/
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

	std::shared_ptr<GameObject> light = object::Instantiate<GameObject>();
	light->SetName(L"main_light");
	AddGameObject(ELayerType::Light, light);
	std::shared_ptr<Light> lightComp = light->AddComponent<Light>();
	lightComp->SetType(ELightType::Directional);
	lightComp->SetColor(Vector4(0.5f, 0.5f, 0.5f, 1.0f));


	std::shared_ptr<GameObject> cursor = manager::InputManager::GetInstance()->GetCursor();
	std::shared_ptr<AudioClip> clip = Resources::Load<AudioClip>(L"SeriaRoomBGM", L"..\\Resources\\Audio\\seria_gate.ogg");
	std::shared_ptr<AudioSource>as = cursor->AddComponent<AudioSource>();
	as->Stop();
	as->SetClip(clip);
	as->SetLoop(true);
	as->Play();

	{
		std::shared_ptr<NPK> npk = Resources::Find<NPK>(L"seria_room");
		std::shared_ptr<NPK> npc_npk = Resources::Find<NPK>(L"npc");
		std::shared_ptr<NPK> gate_npk = Resources::Find<NPK>(L"gate");

#pragma region test를 위해 잠시 주석

#pragma region base bg
		std::shared_ptr<Image> bg = object::Instantiate<Image>(
			Vector3(0.15f, 0.0f, 0.99f),
			Vector3::Zero,
			Vector3(8.5f, 4.4f, 1.0f),
			ELayerType::BackObject);
		{
			bg->SetName(L"BackGround");
			bg->ismove = false;
			std::shared_ptr<MeshRenderer> mr = bg->GetComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			std::shared_ptr<NPK> npk = Resources::Find<NPK>(L"seria_room");
			std::shared_ptr<Texture> texture = npk->CreateAtlas(L"bg", 0, 1, L"SeriamRoomBG");
			mr->material->texture = texture;
			std::shared_ptr<ImageComponent> imageComp = bg->GetComponent<ImageComponent>();
			imageComp->SetSprite(0);
		}
		std::shared_ptr<Image> bgeft = object::Instantiate<Image>(
			Vector3(0.15f, 0.0f, 0.98f),
			Vector3::Zero,
			Vector3(8.5f, 4.4f, 1.0f),
			ELayerType::BackObject);
		{
			bgeft->SetName(L"BackGroundEft");
			bgeft->ismove = false;
			std::shared_ptr<MeshRenderer> mr = bgeft->GetComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material->shader = Resources::Find<Shader>(L"EffectAtlasShader");
			std::shared_ptr<NPK> npk = Resources::Find<NPK>(L"seria_room");
			std::shared_ptr<Texture> texture = npk->CreateAtlas(L"bgeff", 0, 1, L"SeriamRoomEft");
			mr->material->texture = texture;
			std::shared_ptr<ImageComponent> imageComp = bgeft->GetComponent<ImageComponent>();
			imageComp->SetSprite(0);
		}
		std::shared_ptr<Image> bglight = object::Instantiate<Image>(
			Vector3(0.15f, 0.0f, 0.98f),
			Vector3::Zero,
			Vector3(8.5f, 4.4f, 1.0f),
			ELayerType::BackObject);
		{
			bglight->SetName(L"BackGroundLight");
			bglight->ismove = false;
			std::shared_ptr<Animator> ani = bglight->AddComponent<Animator>();

			std::shared_ptr<MeshRenderer> mr = bglight->GetComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material->shader = Resources::Find<Shader>(L"EffectAtlasShader");
			std::shared_ptr<NPK> npk = Resources::Find<NPK>(L"seria_room");
			std::shared_ptr<Texture> texture = npk->CreateAtlas(L"bglight", 0, 3, L"SeriaRoom_Light");

			ani->Create(texture, L"SeriaRoom_Light", 0, 3, 1.0f);
			ani->PlayAnimation(L"SeriaRoom_Light", true);
		}
		std::shared_ptr<Image> bglight_reflect = object::Instantiate<Image>(
			Vector3(0.15f, 0.0f, 0.98f),
			Vector3::Zero,
			Vector3(8.5f, 4.4f, 1.0f),
			ELayerType::BackObject);
		{
			bglight_reflect->SetName(L"BackGroundLight_Reflect");
			bglight_reflect->ismove = false;
			std::shared_ptr<MeshRenderer> mr = bglight_reflect->GetComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material->shader = Resources::Find<Shader>(L"EffectAtlasShader");
			std::shared_ptr<NPK> npk = Resources::Find<NPK>(L"seria_room");
			std::shared_ptr<Texture> texture = npk->CreateAtlas(L"bglightreflect", 0, 1, L"SeriamRoomReflect");
			mr->material->texture = texture;
			std::shared_ptr<ImageComponent> imageComp = bglight_reflect->GetComponent<ImageComponent>();
			imageComp->SetSprite(0);
		}

#pragma endregion


#pragma region front tree
		std::shared_ptr<Image> frontTree = object::Instantiate<Image>(
			Vector3(-2.6f, 0.0f, 0.98f),
			Vector3::Zero,
			Vector3(3.0f, 4.4f, 1.0f),
			ELayerType::BackObject);
		{
			frontTree->SetName(L"FrontTree");
			frontTree->ismove = false;
			std::shared_ptr<MeshRenderer> mr = frontTree->GetComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			std::shared_ptr<NPK> npk = Resources::Find<NPK>(L"seria_room");
			std::shared_ptr<Texture> texture = npk->CreateAtlas(L"border_tree", 0, 2, L"SeriamRoomBorder_tree");
			mr->material->texture = texture;
			std::shared_ptr<ImageComponent> imageComp = frontTree->GetComponent<ImageComponent>();
			imageComp->SetSprite(0);
		}
		std::shared_ptr<Image> frontTree2 = object::Instantiate<Image>(
			Vector3(3.4f, 0.0f, 0.98f),
			Vector3::Zero,
			Vector3(2.0f, 4.4f, 1.0f),
			ELayerType::BackObject);
		{
			frontTree2->SetName(L"FrontTree2");
			frontTree2->ismove = false;
			std::shared_ptr<MeshRenderer> mr = frontTree2->GetComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			std::shared_ptr<NPK> npk = Resources::Find<NPK>(L"seria_room");
			std::shared_ptr<Texture> texture = npk->CreateAtlas(L"border_tree", 0, 2, L"SeriamRoomBorder_tree");
			mr->material->texture = texture;
			std::shared_ptr<ImageComponent> imageComp = frontTree2->GetComponent<ImageComponent>();
			imageComp->SetSprite(1);
		}

#pragma endregion

#pragma region flower bg
		std::shared_ptr<NPK> seriaRoom_npk = Resources::Find<NPK>(L"seria_room");
		std::shared_ptr<Texture> flower_texture01 = seriaRoom_npk->CreateAtlas(L"flower_1", 0, 4, L"SeriamRoomFlower1");
		std::shared_ptr<Texture> flower_texture02 = seriaRoom_npk->CreateAtlas(L"flower_2", 0, 4, L"SeriamRoomFlower2");
		std::shared_ptr<Image> Flower01 = object::Instantiate<Image>(
			prefab::Prefabs[L"AniObject"],
			Vector3(-2.0f, 1.8f, 0.985f),
			Vector3::Zero,
			Vector3(0.25f, 0.25f, 1.0f),
			ELayerType::BackObject
			);
		{
			Flower01->SetName(L"Flower01");
			Flower01->ismove = false;
			std::shared_ptr<MeshRenderer> mr = Flower01->GetComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");

			std::shared_ptr<Animator> ani = Flower01->AddComponent<Animator>();
			ani->Create(flower_texture01, L"SeriaFlower01", 0, 4, 0.3f);
			ani->PlayAnimation(L"SeriaFlower01", true);
		}

		std::shared_ptr<Image> Flower02 = object::Instantiate<Image>(
			prefab::Prefabs[L"AniObject"],
			Vector3(-3.6f, 0.7f, 0.985f),
			Vector3::Zero,
			Vector3(0.25f, 0.25f, 1.0f),
			ELayerType::BackObject
			);
		{
			Flower02->SetName(L"Flower02");
			Flower02->ismove = false;
			std::shared_ptr<MeshRenderer> mr = Flower02->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			std::shared_ptr<Animator> ani = Flower02->AddComponent<Animator>();
			ani->Create(flower_texture01, L"SeriaFlower01", 0, 4, 0.35f);
			ani->PlayAnimation(L"SeriaFlower01", true);
		}
		std::shared_ptr<Image> Flower03 = object::Instantiate<Image>(
			prefab::Prefabs[L"AniObject"],
			Vector3(2.0f, 2.0f, 0.985f),
			Vector3(Vector3(0.0f, 0.0f, Deg2Rad(180))),
			Vector3(0.25f, 0.25f, 1.0f),
			ELayerType::BackObject
			);
		{
			Flower03->SetName(L"Flower03");
			Flower03->ismove = false;
			std::shared_ptr<MeshRenderer> mr = Flower03->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			std::shared_ptr<Animator> ani = Flower03->AddComponent<Animator>();
			ani->Create(flower_texture01, L"SeriaFlower01", 0, 4, 0.25f);
			ani->PlayAnimation(L"SeriaFlower01", true);
		}

		std::shared_ptr<Image> Flower04 = object::Instantiate<Image>(
			prefab::Prefabs[L"AniObject"],
			Vector3(1.5f, 2.0f, 0.98f),
			Vector3(Vector3(0.0f, 0.0f, Deg2Rad(180))),
			Vector3(0.25f, 0.25f, 1.0f),
			ELayerType::BackObject
			);
		{
			Flower04->SetName(L"Flower04");
			Flower04->ismove = false;
			std::shared_ptr<MeshRenderer> mr = Flower04->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			std::shared_ptr<Animator> ani = Flower04->AddComponent<Animator>();
			ani->Create(flower_texture02, L"SeriaFlower02", 0, 4, 0.3f);
			ani->PlayAnimation(L"SeriaFlower02", true);
		}

		std::shared_ptr<Image> Flower05 = object::Instantiate<Image>(
			prefab::Prefabs[L"AniObject"],
			Vector3(-3.3f, 2.0f, 0.98f),
			Vector3::Zero,
			Vector3(0.25f, 0.25f, 1.0f),
			ELayerType::BackObject
			);
		{
			Flower05->SetName(L"Flower05");
			Flower05->ismove = false;
			std::shared_ptr<MeshRenderer> mr = Flower05->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			std::shared_ptr<Animator> ani = Flower05->AddComponent<Animator>();
			ani->Create(flower_texture02, L"SeriaFlower02", 0, 4, 0.4f);
			ani->PlayAnimation(L"SeriaFlower02", true);
		}

#pragma endregion	

#pragma region leaf bg
		std::shared_ptr<Texture> left_texture01 = seriaRoom_npk->CreateAtlas(L"leaf_1", 0, 4, L"SeriamRoomLeaf1");
		std::shared_ptr<Texture> left_texture02 = seriaRoom_npk->CreateAtlas(L"leaf_2", 0, 4, L"SeriamRoomLeaf2");
		std::shared_ptr<Texture> left_texture03 = seriaRoom_npk->CreateAtlas(L"leaf_3", 0, 4, L"SeriamRoomLeaf3");
		std::shared_ptr<Image> Leaf01 = object::Instantiate<Image>(
			prefab::Prefabs[L"AniObject"],
			Vector3(-2.2f, 1.8f, 0.98f),
			Vector3::Zero,
			Vector3(0.2f, 0.25f, 1.0f),
			ELayerType::BackObject
			);
		{
			Leaf01->SetName(L"Leaf01");
			Leaf01->ismove = false;
			std::shared_ptr<MeshRenderer> mr = Leaf01->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			std::shared_ptr<Animator> ani = Leaf01->AddComponent<Animator>();
			ani->Create(left_texture01, L"SeriaLeaf01", 0, 4, 0.3f);
			ani->PlayAnimation(L"SeriaLeaf01", true);
		}
		std::shared_ptr<Image> Leaf02 = object::Instantiate<Image>(
			prefab::Prefabs[L"AniObject"],
			Vector3(-2.6f, 2.0f, 0.98f),
			Vector3::Zero,
			Vector3(0.2f, 0.25f, 1.0f),
			ELayerType::BackObject
			);
		{
			Leaf02->SetName(L"Leaf02");
			Leaf02->ismove = false;
			std::shared_ptr<MeshRenderer> mr = Leaf02->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			std::shared_ptr<Animator> ani = Leaf02->AddComponent<Animator>();
			ani->Create(left_texture03, L"SeriaLeaf03", 0, 4, 0.3f);
			ani->PlayAnimation(L"SeriaLeaf03", true);
		}
		std::shared_ptr<Image> Leaf03 = object::Instantiate<Image>(
			prefab::Prefabs[L"AniObject"],
			Vector3(-3.5f, 1.9f, 0.98f),
			Vector3::Zero,
			Vector3(0.2f, 0.25f, 1.0f),
			ELayerType::BackObject
			);
		{
			Leaf03->SetName(L"Leaf03");
			Leaf03->ismove = false;
			std::shared_ptr<MeshRenderer> mr = Leaf03->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			std::shared_ptr<Animator> ani = Leaf03->AddComponent<Animator>();
			ani->Create(left_texture03, L"SeriaLeaf03", 0, 4, 0.3f);
			ani->PlayAnimation(L"SeriaLeaf03", true);
		}

		std::shared_ptr<Image> Leaf04 = object::Instantiate<Image>(
			prefab::Prefabs[L"AniObject"],
			Vector3(2.5f, 1.8f, 0.98f),
			Vector3::Zero,
			Vector3(0.2f, 0.25f, 1.0f),
			ELayerType::BackObject
			);
		{
			Leaf04->SetName(L"Leaf04");
			Leaf04->ismove = false;
			std::shared_ptr<MeshRenderer> mr = Leaf04->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			std::shared_ptr<Animator> ani = Leaf04->AddComponent<Animator>();
			ani->Create(left_texture02, L"SeriaLeaf02", 0, 4, 0.3f);
			ani->PlayAnimation(L"SeriaLeaf02", true);
		}

		std::shared_ptr<Image> Leaf05 = object::Instantiate<Image>(
			prefab::Prefabs[L"AniObject"],
			Vector3(1.1f, 2.0f, 0.98f),
			Vector3::Zero,
			Vector3(0.2f, 0.25f, 1.0f),
			ELayerType::BackObject
			);
		{
			Leaf05->SetName(L"Leaf05");
			Leaf05->ismove = false;
			std::shared_ptr<MeshRenderer> mr = Leaf05->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			std::shared_ptr<Animator> ani = Leaf05->AddComponent<Animator>();
			ani->Create(left_texture02, L"SeriaLeaf02", 0, 4, 0.3f);
			ani->PlayAnimation(L"SeriaLeaf02", true);
		}

		std::shared_ptr<Image> Leaf06 = object::Instantiate<Image>(
			prefab::Prefabs[L"AniObject"],
			Vector3(2.0f, 1.8f, 0.98f),
			Vector3::Zero,
			Vector3(0.2f, 0.25f, 1.0f),
			ELayerType::BackObject
			);
		{
			Leaf06->SetName(L"Leaf06");
			Leaf06->ismove = false;
			std::shared_ptr<MeshRenderer> mr = Leaf06->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			std::shared_ptr<Animator> ani = Leaf06->AddComponent<Animator>();
			ani->Create(left_texture03, L"SeriaLeaf03", 0, 4, 0.3f);
			ani->PlayAnimation(L"SeriaLeaf03", true);
		}

		std::shared_ptr<Image> Leaf07 = object::Instantiate<Image>(
			prefab::Prefabs[L"AniObject"],
			Vector3(1.5f, 1.8f, 0.98f),
			Vector3::Zero,
			Vector3(0.2f, 0.25f, 1.0f),
			ELayerType::BackObject
			);
		{
			Leaf07->SetName(L"Leaf07");
			Leaf07->ismove = false;
			std::shared_ptr<MeshRenderer> mr = Leaf07->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			std::shared_ptr<Animator> ani = Leaf07->AddComponent<Animator>();
			ani->Create(left_texture01, L"SeriaLeaf01", 0, 4, 0.3f);
			ani->PlayAnimation(L"SeriaLeaf01", true);
		}
#pragma endregion

#pragma region gate
		std::shared_ptr<Texture> MiddleDoortexture = seriaRoom_npk->CreateAtlas(L"gate_new", 0, 1, L"SeriamRoomGate_New");
		std::shared_ptr<NPK> gateNpk = Resources::Find<NPK>(L"gate");
		std::shared_ptr<Texture> LeftPortalEfttexture = gateNpk->CreateAtlas(L"seriagate_dooreffect.img", 0, 9, L"SeriamRoomGate_PortalEft");
		std::shared_ptr<Texture> LeftGateDownTexture = gateNpk->CreateAtlas(L"gatedown.img", 0, 29, L"SeriamRoomGate_DownEft");
		std::shared_ptr<Texture> LeftGateDownThinTexture = gateNpk->CreateAtlas(L"gatedownthin.img", 0, 29, L"SeriamRoomGate_DownThinEft");
		std::shared_ptr<Texture> LeftGateUpTexture = gateNpk->CreateAtlas(L"gateup.img", 0, 29, L"SeriamRoomGate_UpEft");
		std::shared_ptr<Texture> LeftGateUpThinTexture = gateNpk->CreateAtlas(L"getupthin.img", 0, 29, L"SeriamRoomGate_UpThinEft");
		std::shared_ptr<Texture> MiddleGateEftTexture = seriaRoom_npk->CreateAtlas(L"gate_new_eff", 0, 5, L"SeriamRoomGate_Gate_NewEft");
		std::shared_ptr<Texture> MiddleGateGlowEftTexture = seriaRoom_npk->CreateAtlas(L"gate_new_glow_eff", 0, 24, L"SeriamRoomGate_Gate_NewGlowEft");
		std::shared_ptr<Image> MGateRight = object::Instantiate<Image>(
			Vector3(0.8f, -1.3f, 0.1f),
			Vector3::Zero,
			Vector3(2.0f, 2.0f, 1.0f),
			ELayerType::FrontObject);
		{
			MGateRight->SetName(L"MGateRight");
			MGateRight->ismove = false;
			std::shared_ptr<MeshRenderer> mr = MGateRight->GetComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");

			mr->material->texture = MiddleDoortexture;
			std::shared_ptr<ImageComponent> imageComp = MGateRight->GetComponent<ImageComponent>();
			imageComp->SetSprite(0);
		}
		std::shared_ptr<Image> MGateLeft = object::Instantiate<Image>(
			Vector3(-0.7f, -1.3f, 0.1f),
			Vector3::Zero,
			Vector3(2.0f, 2.0f, 1.0f),
			ELayerType::FrontObject);
		{
			MGateLeft->SetName(L"MGateLeft");
			MGateLeft->ismove = false;
			std::shared_ptr<MeshRenderer> mr = MGateLeft->GetComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material->shader = Resources::Find<Shader>(L"VerticalInverterAtlasShader");
			mr->material->texture = MiddleDoortexture;
			std::shared_ptr<ImageComponent> imageComp = MGateLeft->GetComponent<ImageComponent>();
			imageComp->SetSprite(0);
		}
		std::shared_ptr<Image> DoorEft = object::Instantiate<Image>(
			prefab::Prefabs[L"AniEftObject"],
			Vector3(3.4f, -0.3f, 0.98f),
			Vector3::Zero,
			Vector3(0.4f, 1.2f, 1.0f),
			ELayerType::BackObject);
		{
			DoorEft->SetName(L"DoorEft");
			DoorEft->ismove = false;

			std::shared_ptr<Animator> ani = DoorEft->AddComponent<Animator>();

			std::shared_ptr<MeshRenderer> mr = DoorEft->GetComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material->shader = Resources::Find<Shader>(L"EffectAtlasShader");

			ani->Create(LeftPortalEfttexture, L"DoorEft01", 0, 9, 0.1f);
			ani->PlayAnimation(L"DoorEft01", true);
		}

		std::shared_ptr<Image> GateDown = object::Instantiate<Image>(
			prefab::Prefabs[L"AniObject"],
			Vector3(3.0f, -0.75f, 0.98f),
			Vector3::Zero,
			Vector3(2.5f, 2.0f, 1.0f),
			ELayerType::BackObject);
		{
			GateDown->SetName(L"GateDown");
			GateDown->ismove = false;
			std::shared_ptr<MeshRenderer> mr = GateDown->GetComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->alpha = 0.6f;
			std::shared_ptr<Animator> ani = GateDown->AddComponent<Animator>();
			ani->Create(LeftGateDownTexture, L"DoorEft02", 0, 29, 0.08f);
			ani->PlayAnimation(L"DoorEft02", true);
		}
		std::shared_ptr<Image> GateDownThin = object::Instantiate<Image>(
			prefab::Prefabs[L"AniEftObject"],
			Vector3(-5.2f, 2.0f, 0.0f),
			Vector3::Zero,
			Vector3(1.0f, 1.0f, 1.0f));
		{
			GateDownThin->SetName(L"GateDownThin");
			GateDownThin->ismove = false;
			std::shared_ptr<Animator> ani = GateDownThin->AddComponent<Animator>();

			std::shared_ptr<MeshRenderer> mr = GateDownThin->GetComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material->shader = Resources::Find<Shader>(L"EffectAtlasShader");
			mr->alpha = 0.6f;

			ani->Create(LeftGateDownThinTexture, L"DoorEft03", 0, 29, 0.08f);
			ani->PlayAnimation(L"DoorEft03", true);
			std::shared_ptr<Transform> tf = GateDownThin->GetComponent<Transform>();
			GateDown->AddChild(GateDownThin);
		}

		std::shared_ptr<Image> GateUp = object::Instantiate<Image>(
			prefab::Prefabs[L"AniObject"],
			Vector3(3.0f, -0.65f, -0.01f),
			Vector3::Zero,
			Vector3(2.5f, 2.5f, 1.0f),
			ELayerType::FrontObject);
		{
			GateUp->SetName(L"GateUp");
			GateUp->ismove = false;
			std::shared_ptr<MeshRenderer> mr = GateUp->GetComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			//mr->alpha = 0.6f;
			std::shared_ptr<Animator> ani = GateUp->AddComponent<Animator>();
			ani->Create(LeftGateUpTexture, L"DoorEft04", 0, 29, 0.08f);
			ani->PlayAnimation(L"DoorEft04", true);
			std::shared_ptr<Transform> tf = GateUp->GetComponent<Transform>();
		}

		std::shared_ptr<Image> GateUpThin = object::Instantiate<Image>(
			prefab::Prefabs[L"AniEftObject"],
			Vector3(0.0f, 0.1f, 0.0f),
			Vector3::Zero,
			Vector3(1.0f, 1.0f, 1.0f));
		{
			GateUpThin->SetName(L"GateUpThin");
			GateUpThin->ismove = false;
			std::shared_ptr<Animator> ani = GateUpThin->AddComponent<Animator>();
			std::shared_ptr<MeshRenderer> mr = GateUpThin->GetComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material->shader = Resources::Find<Shader>(L"EffectAtlasShader");
			//mr->alpha = 0.6f;

			ani->Create(LeftGateUpThinTexture, L"DoorEft05", 0, 29, 0.08f);
			ani->PlayAnimation(L"DoorEft05", true);
			std::shared_ptr<Transform> tf = GateUpThin->GetComponent<Transform>();
			GateUp->AddChild(GateUpThin);
		}

		std::shared_ptr<Image> GateMidRightEft = object::Instantiate<Image>(
			prefab::Prefabs[L"AniEftObject"],
			Vector3(0.75f, -1.28f, 0.01f),
			Vector3::Zero,
			Vector3(1.5f, 2.0f, 1.0f),
			ELayerType::FrontObject);
		{
			GateMidRightEft->SetName(L"GateMidRightEft");
			GateMidRightEft->ismove = false;
			std::shared_ptr<Animator> ani = GateMidRightEft->AddComponent<Animator>();
			std::shared_ptr<MeshRenderer> mr = GateMidRightEft->GetComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material->shader = Resources::Find<Shader>(L"EffectAtlasShader");

			ani->Create(MiddleGateEftTexture, L"DoorEft06", 0, 5, 0.08f);
			ani->PlayAnimation(L"DoorEft06", true);
			std::shared_ptr<Transform> tf = GateMidRightEft->GetComponent<Transform>();
		}

		std::shared_ptr<Image> GateMidLeftEft = object::Instantiate<Image>(
			prefab::Prefabs[L"AniEftObject"],
			Vector3(-0.68f, -1.28f, 0.01f),
			Vector3::Zero,
			Vector3(1.5f, 2.0f, 1.0f),
			ELayerType::FrontObject);
		{
			GateMidLeftEft->SetName(L"GateMidLeftEft");
			GateMidLeftEft->ismove = false;
			std::shared_ptr<Animator> ani = GateMidLeftEft->AddComponent<Animator>();
			std::shared_ptr<MeshRenderer> mr = GateMidLeftEft->GetComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material->shader = Resources::Find<Shader>(L"VerticalInverterEftAtlasShader");
			ani->Create(MiddleGateEftTexture, L"DoorEft06", 0, 5, 0.08f);
			ani->PlayAnimation(L"DoorEft06", true);
			std::shared_ptr<Transform> tf = GateMidLeftEft->GetComponent<Transform>();
		}

		std::shared_ptr<Image> GateMidRightGlowEft = object::Instantiate<Image>(
			prefab::Prefabs[L"AniEftObject"],
			Vector3(0.75f, -1.28f, 0.01f),
			Vector3::Zero,
			Vector3(1.5f, 2.0f, 1.0f),
			ELayerType::FrontObject);
		{
			GateMidRightGlowEft->SetName(L"GateMidRightGlowEft");
			GateMidRightGlowEft->ismove = false;
			std::shared_ptr<Animator> ani = GateMidRightGlowEft->AddComponent<Animator>();
			std::shared_ptr<MeshRenderer> mr = GateMidRightGlowEft->GetComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material->shader = Resources::Find<Shader>(L"EffectAtlasShader");

			ani->Create(MiddleGateGlowEftTexture, L"DoorEft07", 0, 24, 0.08f);
			ani->PlayAnimation(L"DoorEft07", true);
			std::shared_ptr<Transform> tf = GateMidRightGlowEft->GetComponent<Transform>();
		}

		std::shared_ptr<Image> GateMidLeftGlowEft = object::Instantiate<Image>(
			prefab::Prefabs[L"AniEftObject"],
			Vector3(-0.68f, -1.28f, 0.01f),
			Vector3::Zero,
			Vector3(1.5f, 2.0f, 1.0f),
			ELayerType::FrontObject);
		{
			GateMidLeftGlowEft->SetName(L"GateMidLeftGlowEft");
			GateMidLeftGlowEft->ismove = false;
			std::shared_ptr<Animator> ani = GateMidLeftGlowEft->AddComponent<Animator>();
			std::shared_ptr<MeshRenderer> mr = GateMidLeftGlowEft->GetComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material->shader = Resources::Find<Shader>(L"VerticalInverterEftAtlasShader");

			ani->Create(MiddleGateGlowEftTexture, L"DoorEft07", 0, 24, 0.08f);
			ani->PlayAnimation(L"DoorEft07", true);
			std::shared_ptr<Transform> tf = GateMidLeftGlowEft->GetComponent<Transform>();
		}
#pragma endregion

#pragma endregion

#pragma region obj
		std::shared_ptr<Image> SeriaNPC = object::Instantiate<Image>(
			prefab::Prefabs[L"AniObject"],
			Vector3(0.2f, 0.15f, 0.98f),
			Vector3::Zero,
			Vector3(1.0f, 1.25f, 1.0f),
			ELayerType::BackObject);
		{
			SeriaNPC->SetName(L"SeriaNPC");
			SeriaNPC->ismove = false;
			std::shared_ptr<MeshRenderer> mr = SeriaNPC->GetComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			std::shared_ptr<Animator> ani = SeriaNPC->AddComponent<Animator>();
			ani->Create(L"npc", L"seria_event_2012summer.img", L"SeriaNPC_Room", 0, 33, 0.1f);
			ani->PlayAnimation(L"SeriaNPC_Room", true);
		}
		std::shared_ptr<Image> GoldBox = object::Instantiate<Image>(
			prefab::Prefabs[L"AniObject"],
			Vector3(-1.3f, -0.45f, 0.98f),
			Vector3::Zero,
			Vector3(0.75f, 0.75f, 1.0f),
			ELayerType::BackObject);
		{
			GoldBox->SetName(L"GoldBox");
			GoldBox->ismove = false;
			std::shared_ptr<MeshRenderer> mr = GoldBox->GetComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			std::shared_ptr<Animator> ani = GoldBox->AddComponent<Animator>();
			ani->Create(L"npc", L"storagebrilliantdiamond.img", L"GoldBoxNPC_Room", 0, 18, 0.1f);
			ani->PlayAnimation(L"GoldBoxNPC_Room", true);
		}


		std::shared_ptr<Image> PremiumCoinShop = object::Instantiate<Image>(
			prefab::Prefabs[L"AniObject"],
			Vector3(1.5f, 0.0f, 0.98f),
			Vector3::Zero,
			Vector3(3.0f, 3.0f, 1.0f),
			ELayerType::BackObject);
		{
			PremiumCoinShop->SetName(L"PremiumCoinShop");
			PremiumCoinShop->ismove = false;
			std::shared_ptr<MeshRenderer> mr = PremiumCoinShop->GetComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			std::shared_ptr<Animator> ani = PremiumCoinShop->AddComponent<Animator>();
			ani->Create(L"npc", L"npc_coin.img", L"CoinNPC_Room", 0, 28, 0.1f);
			ani->PlayAnimation(L"CoinNPC_Room", true);
		}
		std::shared_ptr<Image> EnchantBook = object::Instantiate<Image>(
			prefab::Prefabs[L"AniObject"],
			Vector3(0.9f, 0.6f, 0.98f),
			Vector3::Zero,
			Vector3(2.5f, 2.5f, 1.0f),
			ELayerType::BackObject);
		{
			EnchantBook->SetName(L"EnchantBook");
			EnchantBook->ismove = false;
			std::shared_ptr<MeshRenderer> mr = EnchantBook->GetComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			std::shared_ptr<Animator> ani = EnchantBook->AddComponent<Animator>();
			ani->Create(L"npc", L"enchant_book_normal.img", L"EnchantBookNPC_Room", 0, 8, 0.12f);
			ani->PlayAnimation(L"EnchantBookNPC_Room", true);
		}
		std::shared_ptr<Image> EnchantBookEft = object::Instantiate<Image>(
			prefab::Prefabs[L"AniEftObject"],
			Vector3(-0.9f, -0.6f, -0.98f),
			Vector3::Zero,
			Vector3(2.5f, 2.5f, 1.0f));
		{
			EnchantBookEft->SetName(L"EnchantBookEft");
			EnchantBookEft->ismove = false;
			std::shared_ptr<Animator> ani = EnchantBookEft->AddComponent<Animator>();
			ani->Create(L"npc", L"enchant_book_front_dodge.img", L"EnchantBookNPCEft_Room", 0, 8, 0.12f);
			ani->PlayAnimation(L"EnchantBookNPCEft_Room", true);
			std::shared_ptr<MeshRenderer> mr = EnchantBookEft->GetComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material->shader = Resources::Find<Shader>(L"EffectAtlasShader");

			std::shared_ptr<Transform> tf = EnchantBookEft->GetComponent<Transform>();
			EnchantBook->AddChild(EnchantBookEft);
		}
		std::shared_ptr<Image> PostBox = object::Instantiate<Image>(
			Vector3(2.45f, -0.40f, 0.98f),
			Vector3::Zero,
			Vector3(0.7f, 0.85f, 1.0f),
			ELayerType::BackObject);
		{
			PostBox->SetName(L"PostBox");
			PostBox->ismove = false;
			std::shared_ptr<NPK> npk = Resources::Find<NPK>(L"npc");
			std::shared_ptr<Texture> texture = npk->CreateAtlas(L"postbox.img", 0, 1, L"SeriaRoomPostBox");

			std::shared_ptr<ImageComponent> imageComp = PostBox->GetComponent<ImageComponent>();

			std::shared_ptr<MeshRenderer> mr = PostBox->GetComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material->texture = texture;
			imageComp->SetSprite(0);
		}
#pragma endregion
	}

	//test

	/*GameObject* player1 = new GameObject();
	player1->SetName(L"Smile");
	AddGameObject(ELayerType::Player, player1);
	{
		MeshRenderer* mr = player1->AddComponent<MeshRenderer>();
		mr->mesh = Resources::Find<Mesh>(L"RectMesh");
		mr->material = Resources::Find<Material>(L"SpriteMaterial");


		Transform* tf = player1->GetComponent<Transform>();
		tf->position = Vector3(0.0f, 0.0f, 0.5f);
		mr->material->texture = Resources::Find<Texture>(L"Smile");
	}



	GameObject* player2 = new GameObject();
	player2->SetName(L"Smile2");
	AddGameObject(ELayerType::Player, player2);
	{
		MeshRenderer* mr = player2->AddComponent<MeshRenderer>();
		mr->mesh = Resources::Find<Mesh>(L"RectMesh");
		mr->material = Resources::Find<Material>(L"SpriteMaterial");

		Transform* tf = player2->GetComponent<Transform>();
		tf->position = Vector3(1.0f, 0.0f, 0.1f);
		mr->material->texture = Resources::Find<Texture>(L"Smile");

		tf->parent = player1->GetComponent<Transform>();
	}


	player1->GetComponent<Transform>()->SetPosition(Vector3(-3.0f, 0.0f, 0.5f));
	player1->GetComponent<Transform>()->SetRotation(Vector3(0.0f, 0.0f, Deg2Rad(90)));*/
	std::shared_ptr<GameObject> camera = object::Instantiate<GameObject>(
		Vector3(0.0f, 0.0f, -10.0f),
		ELayerType::FrontObject);
	{
		camera->SetName(L"camera");
		//camera->AddScript<CameraScript>();
		std::shared_ptr<Camera> cameraComp = camera->AddComponent<Camera>();
		cameraComp->TurnLayerMask(ELayerType::UI, false);
		cameraComp->TurnLayerMask(ELayerType::Raycast, false);
		renderer::MainCamera = cameraComp;
	}

	std::shared_ptr<GameObject> UIcamera = object::Instantiate<GameObject>(
		Vector3(0.0f, 0.0f, -10.0f),
		ELayerType::UI);
	{
		UIcamera->SetName(L"UICamera");
		std::shared_ptr<Camera> cameraComp = UIcamera->AddComponent<Camera>();
		cameraComp->DisableLayerMasks();
		cameraComp->TurnLayerMask(ELayerType::UI, true);
		cameraComp->TurnLayerMask(ELayerType::Raycast, true);
	}

	/*{
		std::shared_ptr<GameObject> grid = object::Instantiate<GameObject>(ELayerType::Grid);
		grid->SetName(L"Grid");
		std::shared_ptr<MeshRenderer> mr = grid->AddComponent<MeshRenderer>();
		mr->mesh = Resources::Find<Mesh>(L"RectMesh");
		mr->material = Resources::Find<Material>(L"GridMaterial");
		std::shared_ptr<GridScript> script = grid->AddScript<GridScript>();
		script->camera = UIcamera->GetComponent<Camera>();
	}*/
	std::shared_ptr<GameObject> player
		= SceneManager::FindGameObject(L"Player");
	std::vector<std::shared_ptr<Collider2D>> playercols = player->GetChilds<Collider2D>();

	std::shared_ptr<GameObject> portal01 = object::Instantiate<GameObject>(
		Vector3(-0.0f, -1.8f, 0.0f),
		Vector3::Zero,
		Vector3(0.5f, 0.7f, 1.0f),
		ELayerType::Portal
		);
	std::shared_ptr<Collider2D> portalCol = portal01->AddComponent<Collider2D>();
	Portal* portal = manager::PortalManager::GetInstance()->Find(EPortalType::SeriaBottom);
	portal->SetCollisionListener(portal01);

	CollisionManager::RegisterID(portalCol, playercols[0]);
	CollisionManager::RegisterID(portalCol, playercols[1]);

	CollisionManager::SetLayer(ELayerType::Player, ELayerType::Portal, true);
	CollisionManager::SetLayer(ELayerType::Player, ELayerType::Item, true);
	CollisionManager::SetLayer(ELayerType::Raycast, ELayerType::Player, true);
	CollisionManager::SetLayer(ELayerType::Raycast, ELayerType::UI, true);
	//CollisionManager::SetLayer(ELayerType::Raycast,E)
}

void roka::SeriaGateScene::Loading()
{
}
