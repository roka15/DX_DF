#include "SeriaGateScene.h"
#include "Resources.h"
#include "MeshRenderer.h"
#include "Transform.h"
#include "Camera.h"
#include "CameraScript.h"
#include "GridScript.h"
#include "ImageComponent.h"
#include "Animator.h"
#include "PlayerScript.h"

#include "Mesh.h"
#include "Material.h"

#include "NPK.h"
#include "Prefab.h"
#include "Input.h"
#include "Renderer.h"

#include "Collider2D.h"
#include "HitBoxScript.h"
#include "PortalScript.h"


#include "RokaTime.h"
#include "Object.h"
#include "Image.h"
#include "Light.h"

#include "CollisionManager.h"
roka::SeriaGateScene::SeriaGateScene() :Scene(ESceneType::DefaultVillage)
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
	std::shared_ptr<GameObject> obj
		= FindGameObject(ELayerType::Player, L"Player");
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
	}
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
	lightComp->SetColor(Vector4(1.0f, 1.0f, 1.0f, 1.0f));

	{
		std::shared_ptr<NPK> npk = Resources::Find<NPK>(L"seria_room");
		if (npk == nullptr)
			npk = Resources::Load<NPK>(L"seria_room", L"..\\Resources\\npk\\seriaroom.npk");
		std::shared_ptr<NPK> npc_npk = Resources::Find<NPK>(L"npc");
		if (npc_npk == nullptr)
			npc_npk = Resources::Load<NPK>(L"npc", L"..\\Resources\\npk\\npc.npk");

		std::shared_ptr<NPK> hud_npk = Resources::Find<NPK>(L"hud_ui");
		if (hud_npk == nullptr)
			hud_npk = Resources::Load<NPK>(L"hud_ui", L"..\\Resources\\npk\\HudUI.npk");

		std::shared_ptr<NPK> mbskin_npk = Resources::Find<NPK>(L"mage_base_skin");
		if (mbskin_npk == nullptr)
			mbskin_npk = Resources::Load<NPK>(L"mage_base_skin", L"..\\Resources\\npk\\baseskin.npk");

		std::shared_ptr<NPK> gate_npk = Resources::Find<NPK>(L"gate");
		if (gate_npk == nullptr)
			gate_npk = Resources::Load<NPK>(L"gate", L"..\\Resources\\npk\\gate.npk");

		std::shared_ptr<NPK> inven_npk = Resources::Find<NPK>(L"inventory");
		if (inven_npk == nullptr)
			inven_npk = Resources::Load<NPK>(L"inventory", L"..\\Resources\\npk\\inventory.npk");

		std::shared_ptr<NPK> tooltip_npk = Resources::Find<NPK>(L"tooltip");
		if (tooltip_npk == nullptr)
			tooltip_npk = Resources::Load<NPK>(L"tooltip", L"..\\Resources\\npk\\tooltip.npk");

		std::shared_ptr<GameObject> origin = prefab::Prefabs[L"PlayerObject"];
		std::shared_ptr<GameObject> player = object::Instantiate<GameObject>(origin);
		player->SetName(L"Player");
		std::shared_ptr<PlayerScript> playerScript = player->GetComponent<PlayerScript>();
		playerScript->LateInitialize();
		player->GetComponent<Transform>()->position = Vector3(0.0f, 0.0f, 0.3f);
		AddGameObject(ELayerType::Player, player);

#pragma region base bg
		std::shared_ptr<Image> bg = object::Instantiate<Image>(
			Vector3(0.15f, 0.0f, 0.98f),
			Vector3::Zero,
			Vector3(8.5f, 4.4f, 1.0f),
			ELayerType::BackObject);
		{
			bg->SetName(L"BackGround");
			bg->ismove = false;
			std::shared_ptr<MeshRenderer> mr = bg->GetComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"DefaultMaterial");
			std::shared_ptr<ImageComponent> imageComp = bg->GetComponent<ImageComponent>();
			imageComp->SetSprite(L"seria_room", L"bg", 0);
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
			mr->material = Resources::Find<Material>(L"DefaultEffectMaterial");
			std::shared_ptr<ImageComponent> imageComp = bgeft->GetComponent<ImageComponent>();
			imageComp->SetSprite(L"seria_room", L"bgeff", 0);
		}
		std::shared_ptr<Image> bglight = object::Instantiate<Image>(
			Vector3(0.15f, 0.0f, 0.98f),
			Vector3::Zero,
			Vector3(8.5f, 4.4f, 1.0f),
			ELayerType::BackObject);
		{
			bglight->SetName(L"BackGroundLight");
			bglight->ismove = false;
			std::shared_ptr<MeshRenderer> mr = bglight->GetComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"DefaultEffectAniMaterial");
			std::shared_ptr<Animator> ani = bglight->AddComponent<Animator>();
			ani->Create(L"seria_room", L"bglight", L"SeriaRoom_Light", 0, 3, 1.0f);
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
			mr->material = Resources::Find<Material>(L"DefaultEffectMaterial");
			std::shared_ptr<ImageComponent> imageComp = bglight_reflect->GetComponent<ImageComponent>();
			imageComp->SetSprite(L"seria_room", L"bglightreflect", 0);
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
			mr->material = Resources::Find<Material>(L"DefaultMaterial");
			std::shared_ptr<ImageComponent> imageComp = frontTree->GetComponent<ImageComponent>();
			imageComp->SetSprite(L"seria_room", L"border_tree", 0);
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
			mr->material = Resources::Find<Material>(L"DefaultMaterial");
			std::shared_ptr<ImageComponent> imageComp = frontTree2->GetComponent<ImageComponent>();
			imageComp->SetSprite(L"seria_room", L"border_tree", 1);
		}

#pragma endregion

#pragma region flower bg

		std::shared_ptr<Image> Flower01 = object::Instantiate<Image>(
			Vector3(-2.0f, 1.8f, 0.98f),
			Vector3::Zero,
			Vector3(0.25f, 0.25f, 1.0f),
			ELayerType::BackObject
			);
		{
			Flower01->SetName(L"Flower01");
			Flower01->ismove = false;
			std::shared_ptr<MeshRenderer> mr = Flower01->GetComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"DefaultAniMaterial");
			std::shared_ptr<Animator> ani = Flower01->AddComponent<Animator>();
			ani->Create(L"seria_room", L"flower_1", L"SeriaFlower01", 0, 4, 0.3f);
			ani->PlayAnimation(L"SeriaFlower01", true);
		}

		std::shared_ptr<Image> Flower02 = object::Instantiate<Image>(
			Vector3(-3.6f, 0.7f, 0.98f),
			Vector3::Zero,
			Vector3(0.25f, 0.25f, 1.0f),
			ELayerType::BackObject
			);
		{
			Flower02->SetName(L"Flower02");
			Flower02->ismove = false;
			std::shared_ptr<MeshRenderer> mr = Flower02->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"DefaultAniMaterial");
			std::shared_ptr<Animator> ani = Flower02->AddComponent<Animator>();
			ani->Create(L"seria_room", L"flower_1", L"SeriaFlower01", 0, 4, 0.35f);
			ani->PlayAnimation(L"SeriaFlower01", true);
		}
		std::shared_ptr<Image> Flower03 = object::Instantiate<Image>(
			Vector3(2.0f, 2.0f, 0.98f),
			Vector3(Vector3(0.0f, 0.0f, Deg2Rad(180))),
			Vector3(0.25f, 0.25f, 1.0f),
			ELayerType::BackObject
			);
		{
			Flower03->SetName(L"Flower03");
			Flower03->ismove = false;
			std::shared_ptr<MeshRenderer> mr = Flower03->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"DefaultAniMaterial");
			std::shared_ptr<Animator> ani = Flower03->AddComponent<Animator>();
			ani->Create(L"seria_room", L"flower_1", L"SeriaFlower01", 0, 4, 0.25f);
			ani->PlayAnimation(L"SeriaFlower01", true);
		}

		std::shared_ptr<Image> Flower04 = object::Instantiate<Image>(
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
			mr->material = Resources::Find<Material>(L"DefaultAniMaterial");
			std::shared_ptr<Animator> ani = Flower04->AddComponent<Animator>();
			ani->Create(L"seria_room", L"flower_2", L"SeriaFlower02", 0, 4, 0.3f);
			ani->PlayAnimation(L"SeriaFlower02", true);
		}

		std::shared_ptr<Image> Flower05 = object::Instantiate<Image>(
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
			mr->material = Resources::Find<Material>(L"DefaultAniMaterial");
			std::shared_ptr<Animator> ani = Flower05->AddComponent<Animator>();
			ani->Create(L"seria_room", L"flower_2", L"SeriaFlower02", 0, 4, 0.4f);
			ani->PlayAnimation(L"SeriaFlower02", true);
		}
#pragma endregion	

#pragma region leaf bg
		std::shared_ptr<Image> Leaf01 = object::Instantiate<Image>(
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

			mr->material = Resources::Find<Material>(L"DefaultAniMaterial");
			std::shared_ptr<Animator> ani = Leaf01->AddComponent<Animator>();
			ani->Create(L"seria_room", L"leaf_1", L"SeriaLeaf01", 0, 4, 0.3f);
			ani->PlayAnimation(L"SeriaLeaf01", true);
		}
		std::shared_ptr<Image> Leaf02 = object::Instantiate<Image>(
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
			mr->material = Resources::Find<Material>(L"DefaultAniMaterial");
			std::shared_ptr<Animator> ani = Leaf02->AddComponent<Animator>();
			ani->Create(L"seria_room", L"leaf_3", L"SeriaLeaf03", 0, 4, 0.3f);
			ani->PlayAnimation(L"SeriaLeaf03", true);
		}
		std::shared_ptr<Image> Leaf03 = object::Instantiate<Image>(
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
			mr->material = Resources::Find<Material>(L"DefaultAniMaterial");
			std::shared_ptr<Animator> ani = Leaf03->AddComponent<Animator>();
			ani->Create(L"seria_room", L"leaf_3", L"SeriaLeaf03", 0, 4, 0.3f);
			ani->PlayAnimation(L"SeriaLeaf03", true);
		}

		std::shared_ptr<Image> Leaf04 = object::Instantiate<Image>(
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
			mr->material = Resources::Find<Material>(L"DefaultAniMaterial");
			std::shared_ptr<Animator> ani = Leaf04->AddComponent<Animator>();
			ani->Create(L"seria_room", L"leaf_2", L"SeriaLeaf02", 0, 4, 0.3f);
			ani->PlayAnimation(L"SeriaLeaf02", true);
		}

		std::shared_ptr<Image> Leaf05 = object::Instantiate<Image>(
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
			mr->material = Resources::Find<Material>(L"DefaultAniMaterial");
			std::shared_ptr<Animator> ani = Leaf05->AddComponent<Animator>();
			ani->Create(L"seria_room", L"leaf_2", L"SeriaLeaf02", 0, 4, 0.3f);
			ani->PlayAnimation(L"SeriaLeaf02", true);
		}

		std::shared_ptr<Image> Leaf06 = object::Instantiate<Image>(
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
			mr->material = Resources::Find<Material>(L"DefaultAniMaterial");
			std::shared_ptr<Animator> ani = Leaf06->AddComponent<Animator>();
			ani->Create(L"seria_room", L"leaf_3", L"SeriaLeaf03", 0, 4, 0.3f);
			ani->PlayAnimation(L"SeriaLeaf03", true);
		}

		std::shared_ptr<Image> Leaf07 = object::Instantiate<Image>(
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
			ani->Create(L"seria_room", L"leaf_1", L"SeriaLeaf01", 0, 4, 0.3f);
			ani->PlayAnimation(L"SeriaLeaf01", true);
		}
#pragma endregion
	
#pragma region gate
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
			mr->material = Resources::Find<Material>(L"TransparentMaterial");
			std::shared_ptr<ImageComponent> imageComp = MGateRight->GetComponent<ImageComponent>();
			imageComp->SetSprite(L"seria_room", L"gate_new", 0);
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
			mr->material = Resources::Find<Material>(L"TransparentVInverterMaterial");
			std::shared_ptr<ImageComponent> imageComp = MGateLeft->GetComponent<ImageComponent>();
			imageComp->SetSprite(L"seria_room", L"gate_new", 0);
		}
		std::shared_ptr<Image> DoorEft = object::Instantiate<Image>(
			Vector3(3.4f, -0.3f, 0.98f),
			Vector3::Zero,
			Vector3(0.4f, 1.2f, 1.0f),
			ELayerType::BackObject);
		{
			DoorEft->SetName(L"DoorEft");
			DoorEft->ismove = false;
			std::shared_ptr<MeshRenderer> mr = DoorEft->GetComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"DefaultEffectAniMaterial");
			std::shared_ptr<Animator> ani = DoorEft->AddComponent<Animator>();
			ani->Create(L"gate", L"seriagate_dooreffect.img", L"DoorEft01", 0, 9, 0.1f);
			ani->PlayAnimation(L"DoorEft01", true);
		}

		std::shared_ptr<Image> GateDown = object::Instantiate<Image>(
			Vector3(3.2f, -0.75f, 0.98f),
			Vector3::Zero,
			Vector3(2.5f, 2.0f, 1.0f),
			ELayerType::BackObject);
		{
			GateDown->SetName(L"GateDown");
			GateDown->ismove = false;
			std::shared_ptr<MeshRenderer> mr = GateDown->GetComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"DefaultAniMaterial");
			std::shared_ptr<Animator> ani = GateDown->AddComponent<Animator>();
			ani->Create(L"gate", L"gatedown.img", L"DoorEft02", 0, 29, 0.08f);
			ani->PlayAnimation(L"DoorEft02", true);
		}
		std::shared_ptr<Image> GateDownThin = object::Instantiate<Image>(
			Vector3(0.0f, 0.0f, 0.0f),
			Vector3::Zero,
			Vector3(1.0f, 1.0f, 1.0f));
		{
			GateDownThin->SetName(L"GateDownThin");
			GateDownThin->ismove = false;
			std::shared_ptr<MeshRenderer> mr = GateDownThin->GetComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"DefaultEffectAniMaterial");
			std::shared_ptr<Animator> ani = GateDownThin->AddComponent<Animator>();
			ani->Create(L"gate", L"gatedownthin.img", L"DoorEft03", 0, 29, 0.08f);
			ani->PlayAnimation(L"DoorEft03", true);
			std::shared_ptr<Transform> tf = GateDownThin->GetComponent<Transform>();
			GateDown->AddChild(GateDownThin);
		}

		std::shared_ptr<Image> GateUp = object::Instantiate<Image>(
			Vector3(0.0f, 0.105f, 0.0f),
			Vector3::Zero,
			Vector3(1.0f, 1.5f, 1.0f));
		{
			GateUp->SetName(L"GateUp");
			GateUp->ismove = false;
			std::shared_ptr<MeshRenderer> mr = GateUp->GetComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"DefaultAniMaterial");
			std::shared_ptr<Animator> ani = GateUp->AddComponent<Animator>();
			ani->Create(L"gate", L"gateup.img", L"DoorEft04", 0, 29, 0.08f);
			ani->PlayAnimation(L"DoorEft04", true);
			std::shared_ptr<Transform> tf = GateUp->GetComponent<Transform>();
			GateDown->AddChild(GateUp);
		}

		std::shared_ptr<Image> GateUpThin = object::Instantiate<Image>(
			Vector3(0.0f, 0.0f, 0.0f),
			Vector3::Zero,
			Vector3(1.0f, 1.0f, 1.0f));
		{
			GateUpThin->SetName(L"GateUpThin");
			GateUpThin->ismove = false;
			std::shared_ptr<MeshRenderer> mr = GateUpThin->GetComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"DefaultEffectAniMaterial");
			std::shared_ptr<Animator> ani = GateUpThin->AddComponent<Animator>();
			ani->Create(L"gate", L"getupthin.img", L"DoorEft05", 0, 29, 0.08f);
			ani->PlayAnimation(L"DoorEft05", true);
			std::shared_ptr<Transform> tf = GateUpThin->GetComponent<Transform>();
			GateUp->AddChild(GateUpThin);
		}

		std::shared_ptr<Image> GateMidRightEft = object::Instantiate<Image>(
			Vector3(0.0f, 0.0f, 0.0f),
			Vector3::Zero,
			Vector3(1.0f, 1.0f, 1.0f));
		{
			GateMidRightEft->SetName(L"GateMidRightEft");
			GateMidRightEft->ismove = false;
			std::shared_ptr<MeshRenderer> mr = GateMidRightEft->GetComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"DefaultEffectAniMaterial");
			std::shared_ptr<Animator> ani = GateMidRightEft->AddComponent<Animator>();
			ani->Create(L"seria_room", L"gate_new_eff", L"DoorEft06", 0, 5, 0.08f);
			ani->PlayAnimation(L"DoorEft06", true);
			std::shared_ptr<Transform> tf = GateMidRightEft->GetComponent<Transform>();
			MGateRight->AddChild(GateMidRightEft);
		}

		std::shared_ptr<Image> GateMidLeftEft = object::Instantiate<Image>(
			Vector3(0.0f, 0.0f, 0.0f),
			Vector3::Zero,
			Vector3(1.0f, 1.0f, 1.0f));
		{
			GateMidLeftEft->SetName(L"GateMidLeftEft");
			GateMidLeftEft->ismove = false;
			std::shared_ptr<MeshRenderer> mr = GateMidLeftEft->GetComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"DefaultVInverterEftAniMaterial");
			std::shared_ptr<Animator> ani = GateMidLeftEft->AddComponent<Animator>();
			ani->Create(L"seria_room", L"gate_new_eff", L"DoorEft06", 0, 5, 0.08f);
			ani->PlayAnimation(L"DoorEft06", true);
			std::shared_ptr<Transform> tf = GateMidLeftEft->GetComponent<Transform>();
			MGateLeft->AddChild(GateMidLeftEft);
		}

		std::shared_ptr<Image> GateMidRightGlowEft = object::Instantiate<Image>(
			Vector3(0.0f, 0.0f, 0.0f),
			Vector3::Zero,
			Vector3(1.0f, 1.0f, 1.0f));
		{
			GateMidRightGlowEft->SetName(L"GateMidRightGlowEft");
			GateMidRightGlowEft->ismove = false;
			std::shared_ptr<MeshRenderer> mr = GateMidRightGlowEft->GetComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"DefaultEffectAniMaterial");
			std::shared_ptr<Animator> ani = GateMidRightGlowEft->AddComponent<Animator>();
			ani->Create(L"seria_room", L"gate_new_glow_eff", L"DoorEft07", 0, 24, 0.08f);
			ani->PlayAnimation(L"DoorEft07", true);
			std::shared_ptr<Transform> tf = GateMidRightGlowEft->GetComponent<Transform>();
			MGateRight->AddChild(GateMidRightGlowEft);
		}

		std::shared_ptr<Image> GateMidLeftGlowEft = object::Instantiate<Image>(
			Vector3(0.0f, 0.0f, 0.0f),
			Vector3::Zero,
			Vector3(1.0f, 1.0f, 1.0f));
		{
			GateMidLeftGlowEft->SetName(L"GateMidLeftGlowEft");
			GateMidLeftGlowEft->ismove = false;
			std::shared_ptr<MeshRenderer> mr = GateMidLeftGlowEft->GetComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"DefaultVInverterEftAniMaterial");
			std::shared_ptr<Animator> ani = GateMidLeftGlowEft->AddComponent<Animator>();
			ani->Create(L"seria_room", L"gate_new_glow_eff", L"DoorEft07", 0, 24, 0.08f);
			ani->PlayAnimation(L"DoorEft07", true);
			std::shared_ptr<Transform> tf = GateMidLeftGlowEft->GetComponent<Transform>();
			MGateLeft->AddChild(GateMidLeftGlowEft);
		}
#pragma endregion

#pragma region hud/ui
		std::shared_ptr<Image> HudBase = object::Instantiate<Image>(
			Vector3(0.1f, -1.89f, -20.0f),
			Vector3::Zero,
			Vector3(3.5f, 0.6f, 1.0f),
			ELayerType::UI);
		{
			HudBase->SetName(L"HudBase");
			HudBase->ismove = false;
			std::shared_ptr<MeshRenderer> mr = HudBase->GetComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"DefaultMaterial");
			std::shared_ptr<ImageComponent> imageComp = HudBase->GetComponent<ImageComponent>();
			imageComp->SetSprite(L"hud_ui", L"hud.img", 0);
		}

		std::shared_ptr<Image> HPBase = object::Instantiate<Image>(
			Vector3(-0.365f, -0.05f, 0.0f),
			Vector3::Zero,
			Vector3(0.14f, 0.7f, 1.0f),
			ELayerType::UI);
		{
			HPBase->SetName(L"HPBase");
			HPBase->ismove = false;
			std::shared_ptr<MeshRenderer> mr = HPBase->GetComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"HPBaseMaterial01");

			mr->material = Resources::Find<Material>(L"DefaultMaterial");
			std::shared_ptr<ImageComponent> imageComp = HPBase->GetComponent<ImageComponent>();
			imageComp->SetSprite(L"hud_ui", L"hud.img", 1);

			HudBase->AddChild(HPBase);
		}
		std::shared_ptr<Image> MPBase = object::Instantiate<Image>(
			Vector3(0.365f, -0.05f, 0.0f),
			Vector3::Zero,
			Vector3(0.14f, 0.7f, 1.0f),
			ELayerType::UI);
		{
			MPBase->SetName(L"MPBase");
			MPBase->ismove = false;
			std::shared_ptr<MeshRenderer> mr = MPBase->GetComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"DefaultMaterial");
			std::shared_ptr<ImageComponent> imageComp = MPBase->GetComponent<ImageComponent>();
			imageComp->SetSprite(L"hud_ui", L"hud.img", 2);

			HudBase->AddChild(MPBase);
		}
		std::shared_ptr<Image> HPFilter = object::Instantiate<Image>(
			Vector3(0.0f, -0.05f, 0.0f),
			Vector3::Zero,
			Vector3(1.1f, 1.1f, 1.0f),
			ELayerType::UI);
		{
			HPFilter->SetName(L"HPFilter");
			HPFilter->ismove = false;
			std::shared_ptr<MeshRenderer> mr = HPFilter->GetComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"TransparentMaterial");
			std::shared_ptr<ImageComponent> imageComp = HPFilter->GetComponent<ImageComponent>();
			imageComp->SetSprite(L"hud_ui", L"hud.img", 212);

			HPBase->AddChild(HPFilter);
		}
		std::shared_ptr<Image> MPFilter = object::Instantiate<Image>(
			Vector3(0.0f, -0.05f, 0.0f),
			Vector3::Zero,
			Vector3(1.1f, 1.1f, 1.0f),
			ELayerType::UI);
		{
			MPFilter->SetName(L"MPFilter");
			MPFilter->ismove = false;
			std::shared_ptr<MeshRenderer> mr = MPFilter->GetComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"TransparentMaterial");
			std::shared_ptr<ImageComponent> imageComp = MPFilter->GetComponent<ImageComponent>();
			imageComp->SetSprite(L"hud_ui", L"hud.img", 213);

			MPBase->AddChild(MPFilter);
		}
		float startx = -0.18f;
		float starty = -0.26f;
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 7; j++)
			{
				int index = i * 8 + j;
				float x = startx + 0.071 * j;
				float y = starty + 0.37 * i;
				std::shared_ptr<Image> SkillQuickSlot = object::Instantiate<Image>(
					Vector3(x, y, 0.0f),
					Vector3::Zero,
					Vector3(0.075f, 0.4f, 1.0f),
					ELayerType::UI);
				{
					std::wstring name = L"SkillQuickSlot01" + index;
					SkillQuickSlot->SetName(name);
					SkillQuickSlot->ismove = false;

					std::shared_ptr<MeshRenderer> mr = SkillQuickSlot->GetComponent<MeshRenderer>();
					mr->mesh = Resources::Find<Mesh>(L"RectMesh");
					mr->material = Resources::Find<Material>(L"TransparentMaterial");

					std::shared_ptr<ImageComponent> imageComp = SkillQuickSlot->GetComponent<ImageComponent>();
					imageComp->SetSprite(L"hud_ui", L"hud.img", 198);

					HudBase->AddChild(SkillQuickSlot);
				}
			}
		}
		
		std::shared_ptr<Image> MoreSkillBtn = object::Instantiate<Image>(
			Vector3(-0.238f, 0.11f, 0.0f),
			Vector3::Zero,
			Vector3(0.055f, 0.42f, 1.0f),
			ELayerType::UI);
		{
			MoreSkillBtn->SetName(L"MoreSkillBtn");
			MoreSkillBtn->ismove = false;
			std::shared_ptr<MeshRenderer> mr = MoreSkillBtn->GetComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"DefaultMaterial");

			std::shared_ptr<ImageComponent> imageComp = MoreSkillBtn->GetComponent<ImageComponent>();
			imageComp->SetSprite(L"hud_ui", L"hud.img", 193);

			HudBase->AddChild(MoreSkillBtn);
		}
		std::shared_ptr<Image> SkillChangeBtn = object::Instantiate<Image>(
			Vector3(-0.238f, -0.265f, 0.0f),
			Vector3::Zero,
			Vector3(0.055f, 0.41f, 1.0f),
			ELayerType::UI);
		{
			SkillChangeBtn->SetName(L"SkillChangeBtn");
			SkillChangeBtn->ismove = false;
			std::shared_ptr<MeshRenderer> mr = SkillChangeBtn->GetComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"DefaultMaterial");

			std::shared_ptr<ImageComponent> imageComp = SkillChangeBtn->GetComponent<ImageComponent>();
			imageComp->SetSprite(L"hud_ui", L"hud.img", 53);

			HudBase->AddChild(SkillChangeBtn);
		}

		startx = -0.88f;
		starty = -0.32f;
		for (int i = 0; i < 1; i++)
		{
			for (int j = 0; j < 6; j++)
			{
				int index = i * 8 + j;
				float x = startx + 0.065 * j;
				float y = starty + 0.37 * i;
				std::shared_ptr<Image> ItemSlot = object::Instantiate<Image>(
					Vector3(x, y, 0.0f),
					Vector3::Zero,
					Vector3(0.07f, 0.4f, 1.0f),
					ELayerType::UI);
				{
					std::wstring name = L"SkillQuickSlot" + index;
					ItemSlot->SetName(name);
					ItemSlot->ismove = false;

					std::shared_ptr<MeshRenderer> mr = ItemSlot->GetComponent<MeshRenderer>();
					mr->mesh = Resources::Find<Mesh>(L"RectMesh");
					mr->material = Resources::Find<Material>(L"DefaultMaterial");

					std::shared_ptr<ImageComponent> imageComp = ItemSlot->GetComponent<ImageComponent>();
					imageComp->SetSprite(L"hud_ui", L"hud.img", 200);

					HudBase->AddChild(ItemSlot);
				}
			}
		}
		std::shared_ptr<Image> Icon1 = object::Instantiate<Image>(
			Vector3(0.55f, -0.19f, 0.0f),
			Vector3::Zero,
			Vector3(0.11f, 0.25f, 1.0f),
			ELayerType::UI);
		{
			Icon1->SetName(L"Icon1");
			Icon1->ismove = false;
			std::shared_ptr<MeshRenderer> mr = Icon1->GetComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"DefaultMaterial");

			std::shared_ptr<ImageComponent> imageComp = Icon1->GetComponent<ImageComponent>();
			imageComp->SetSprite(L"hud_ui", L"hud.img", 72);

			HudBase->AddChild(Icon1);
		}
		std::shared_ptr<Image> Icon2 = object::Instantiate<Image>(
			Vector3(0.71f, -0.05f, 0.0f),
			Vector3::Zero,
			Vector3(0.5f, 0.9f, 1.0f),
			ELayerType::UI);
		{
			Icon2->SetName(L"Icon2");
			Icon2->ismove = false;
			std::shared_ptr<MeshRenderer> mr = Icon2->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"DefaultMaterial");

			std::shared_ptr<ImageComponent> imageComp = Icon2->GetComponent<ImageComponent>();
			imageComp->SetSprite(L"hud_ui", L"hud.img", 68);
			
			Icon1->AddChild(Icon2);
		}
		std::shared_ptr<Image> Icon3 = object::Instantiate<Image>(
			Vector3(1.05f, -0.05f, 0.0f),
			Vector3::Zero,
			Vector3(0.25f, 0.9f, 1.0f),
			ELayerType::UI);
		{
			Icon3->SetName(L"Icon3");
			Icon3->ismove = false;
			std::shared_ptr<MeshRenderer> mr = Icon3->GetComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"DefaultMaterial");

			std::shared_ptr<ImageComponent> imageComp = Icon3->GetComponent<ImageComponent>();
			imageComp->SetSprite(L"hud_ui", L"hud.img", 93);

			Icon1->AddChild(Icon3);
		}
		std::shared_ptr<Image> Icon4 = object::Instantiate<Image>(
			Vector3(1.27f, -0.05f, 0.0f),
			Vector3::Zero,
			Vector3(0.25f, 0.9f, 1.0f),
			ELayerType::UI);
		{
			Icon4->SetName(L"Icon4");
			Icon4->ismove = false;
			std::shared_ptr<MeshRenderer> mr = Icon4->GetComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"IconMaterial04");
			mr->material = Resources::Find<Material>(L"DefaultMaterial");

			std::shared_ptr<ImageComponent> imageComp = Icon4->GetComponent<ImageComponent>();
			imageComp->SetSprite(L"hud_ui", L"hud.img", 94);

			Icon1->AddChild(Icon4);
		}
		std::shared_ptr<Image> Icon5 = object::Instantiate<Image>(
			Vector3(1.49f, -0.05f, 0.0f),
			Vector3::Zero,
			Vector3(0.25f, 0.9f, 1.0f),
			ELayerType::UI);
		{
			Icon5->SetName(L"Icon5");
			Icon5->ismove = false;
			std::shared_ptr<MeshRenderer> mr = Icon5->GetComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"DefaultMaterial");

			std::shared_ptr<ImageComponent> imageComp = Icon5->GetComponent<ImageComponent>();
			imageComp->SetSprite(L"hud_ui", L"hud.img", 95);

			Icon1->AddChild(Icon5);
		}
		std::shared_ptr<Image> Icon6 = object::Instantiate<Image>(
			Vector3(1.7f, -0.05f, 0.0f),
			Vector3::Zero,
			Vector3(0.25f, 0.9f, 1.0f),
			ELayerType::UI);
		{
			Icon6->SetName(L"Icon6");
			Icon6->ismove = false;
			std::shared_ptr<MeshRenderer> mr = Icon6->GetComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"DefaultMaterial");

			std::shared_ptr<ImageComponent> imageComp = Icon6->GetComponent<ImageComponent>();
			imageComp->SetSprite(L"hud_ui", L"hud.img", 96);

			Icon1->AddChild(Icon6);
		}
		std::shared_ptr<Image> Icon7 = object::Instantiate<Image>(
			Vector3(1.92f, -0.05f, 0.0f),
			Vector3::Zero,
			Vector3(0.25f, 0.9f, 1.0f),
			ELayerType::UI);
		{
			Icon7->SetName(L"Icon7");
			Icon7->ismove = false;
			std::shared_ptr<MeshRenderer> mr = Icon7->GetComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"DefaultMaterial");

			std::shared_ptr<ImageComponent> imageComp = Icon7->GetComponent<ImageComponent>();
			imageComp->SetSprite(L"hud_ui", L"hud.img", 97);

			Icon1->AddChild(Icon7);
		}
		std::shared_ptr<Image> Icon8 = object::Instantiate<Image>(
			Vector3(-0.5f, -0.57, 0.0f),
			Vector3::Zero,
			Vector3(0.9f, 0.4f, 1.0f),
			ELayerType::UI);
		{
			Icon8->SetName(L"Icon8");
			Icon8->ismove = false;
			std::shared_ptr<MeshRenderer> mr = Icon8->GetComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"DefaultMaterial");

			std::shared_ptr<ImageComponent> imageComp = Icon8->GetComponent<ImageComponent>();
			imageComp->SetSprite(L"hud_ui", L"hud.img", 211);

			Icon1->AddChild(Icon8);
		}
		std::shared_ptr<Image> Icon9 = object::Instantiate<Image>(
			Vector3(1.05f, -0.57f, 0.0f),
			Vector3::Zero,
			Vector3(2.0f, 0.3f, 1.0f),
			ELayerType::UI);
		{
			Icon9->SetName(L"Icon9");
			Icon9->ismove = false;
			std::shared_ptr<MeshRenderer> mr = Icon9->GetComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"DefaultMaterial");

			std::shared_ptr<ImageComponent> imageComp = Icon9->GetComponent<ImageComponent>();
			imageComp->SetSprite(L"hud_ui", L"hud.img", 203);

			Icon1->AddChild(Icon9);
		}
		std::shared_ptr<Image> Icon10 = object::Instantiate<Image>(
			Vector3(0.9f, -1.0f, 0.0f),
			Vector3::Zero,
			Vector3(2.3f, 0.6f, 1.0f),
			ELayerType::UI);
		{
			Icon10->SetName(L"Icon10");
			Icon10->ismove = false;
			std::shared_ptr<MeshRenderer> mr = Icon10->GetComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"DefaultMaterial");

			std::shared_ptr<ImageComponent> imageComp = Icon10->GetComponent<ImageComponent>();
			imageComp->SetSprite(L"hud_ui", L"hud.img", 242);

			Icon1->AddChild(Icon10);
		}

		std::shared_ptr<Image> Icon11 = object::Instantiate<Image>(
			Vector3(1.035f, -0.57f, 0.0f),
			Vector3::Zero,
			Vector3(1.9f, 0.15f, 1.0f),
			ELayerType::UI);
		{
			Icon11->SetName(L"Icon11");
			Icon11->ismove = false;
			std::shared_ptr<MeshRenderer> mr = Icon11->GetComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"DefaultMaterial");

			std::shared_ptr<ImageComponent> imageComp = Icon11->GetComponent<ImageComponent>();
			imageComp->SetSprite(L"hud_ui", L"hud.img", 3);

			Icon1->AddChild(Icon11);
		}
		std::shared_ptr<Image> Icon12 = object::Instantiate<Image>(
			Vector3(1.0f, -1.0f, 0.0f),
			Vector3::Zero,
			Vector3(1.5f, 0.2f, 1.0f),
			ELayerType::UI);
		{
			Icon12->SetName(L"Icon12");
			Icon12->ismove = false;
			std::shared_ptr<MeshRenderer> mr = Icon12->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"DefaultMaterial");

			std::shared_ptr<ImageComponent> imageComp = Icon12->GetComponent<ImageComponent>();
			imageComp->SetSprite(L"hud_ui", L"hud.img", 22);

			Icon1->AddChild(Icon12);
		}

		std::shared_ptr<Image> HudBase2 = object::Instantiate<Image>(
			Vector3(-0.0f, -0.43f, -0.01f),
			Vector3::Zero,
			Vector3(1.1f, 0.17f, 1.0f),
			ELayerType::UI);
		{
			HudBase2->SetName(L"HudBase2");
			HudBase2->ismove = false;
			std::shared_ptr<MeshRenderer> mr = HudBase2->GetComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"TransparentMaterial");
			
			std::shared_ptr<ImageComponent> imageComp = HudBase2->GetComponent<ImageComponent>();
			imageComp->SetSprite(L"hud_ui", L"hud.img", 202);

			HudBase->AddChild(HudBase2);
		}
		std::shared_ptr<Image> ExpBar = object::Instantiate<Image>(
			Vector3(0.01f, -0.5f, -0.01f),
			Vector3::Zero,
			Vector3(0.7f, 0.05f, 1.0f),
			ELayerType::UI);
		{
			ExpBar->SetName(L"ExpBar");
			ExpBar->ismove = false;
			std::shared_ptr<MeshRenderer> mr = ExpBar->GetComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"TransparentMaterial");
			//mr->material->render_mode = ERenderMode::Transparent;

			std::shared_ptr<ImageComponent> imageComp = ExpBar->GetComponent<ImageComponent>();
			imageComp->SetSprite(L"hud_ui", L"hud.img", 24);

			std::shared_ptr<Transform> tf = ExpBar->GetComponent<Transform>();
			HudBase->AddChild(ExpBar);
		}
#pragma endregion

//#pragma region inventory ui
//		std::shared_ptr<GameObject> inven_base = object::Instantiate<GameObject>(
//			Vector3(3.0f, 0.0f, 0.0f),
//			Vector3::Zero,
//			Vector3(1.4f, 3.0f, 1.0f),
//			ELayerType::UI
//			);
//		{
//			inven_base->SetName(L"InvenBase");
//			inven_base->ismove = false;
//			std::shared_ptr<MeshRenderer> mr = inven_base->AddComponent<MeshRenderer>();
//			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
//			mr->material = Resources::Find<Material>(L"InvenBaseMaterial01");
//			mr->material->texture = inven_npk->GetTexture(L"inventory.img", 175);
//			mr->material->render_mode = graphics::ERenderMode::Transparent;
//		}
//
//		std::shared_ptr<Transform> inven_parrent = inven_base->GetComponent<Transform>();
//
//		std::shared_ptr<GameObject> inven_base2 = object::Instantiate<GameObject>(
//			Vector3(0.0f, 0.24f, -0.01f),
//			Vector3::Zero,
//			Vector3(0.95f, 0.35f, 1.0f),
//			ELayerType::UI
//			);
//		{
//			inven_base2->SetName(L"InvenBase2");
//			inven_base2->ismove = false;
//			std::shared_ptr<MeshRenderer> mr = inven_base2->AddComponent<MeshRenderer>();
//			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
//			mr->material = Resources::Find<Material>(L"InvenBaseMaterial02");
//			mr->material->texture = inven_npk->GetTexture(L"inventory.img", 0);
//			mr->material->render_mode = graphics::ERenderMode::Transparent;
//		
//			inven_base->AddChild(inven_base2);
//		}
//
//		std::shared_ptr<GameObject> inven_base3 = object::Instantiate<GameObject>(
//			Vector3(0.0f, -0.19f, 0.1f),
//			Vector3::Zero,
//			Vector3(0.95f, 0.42f, 1.0f),
//			ELayerType::UI
//			);
//		{
//			inven_base3->SetName(L"InvenBase3");
//			inven_base3->ismove = false;
//			std::shared_ptr<MeshRenderer> mr = inven_base3->AddComponent<MeshRenderer>();
//			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
//			mr->material = Resources::Find<Material>(L"InvenBaseMaterial04");
//			mr->material->texture = inven_npk->GetTexture(L"inventory.img", 39);
//			mr->material->render_mode = graphics::ERenderMode::Transparent;
//			inven_base->AddChild(inven_base3);
//		}
//
//		std::shared_ptr<GameObject> inven_base4 = object::Instantiate<GameObject>(
//			Vector3(0.0f, -0.45f, 0.0f),
//			Vector3::Zero,
//			Vector3(0.95f, 0.09f, 1.0f),
//			ELayerType::UI
//			);
//		{
//			inven_base4->SetName(L"InvenBase4");
//			inven_base4->ismove = false;
//			std::shared_ptr<MeshRenderer> mr = inven_base4->AddComponent<MeshRenderer>();
//			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
//			mr->material = Resources::Find<Material>(L"InvenBaseMaterial03");
//			mr->material->texture = inven_npk->GetTexture(L"inventory.img", 27);
//			mr->material->render_mode = graphics::ERenderMode::Transparent;
//			inven_base->AddChild(inven_base4);
//		}
//
//		std::shared_ptr<GameObject> inven_bar = object::Instantiate<GameObject>(
//			Vector3(0.0f, 0.48f, 0.0f),
//			Vector3::Zero,
//			Vector3(1.0f, 0.05f, 1.0f),
//			ELayerType::UI
//			);
//		{
//			inven_bar->SetName(L"InvenBar");
//			inven_bar->ismove = false;
//			std::shared_ptr<MeshRenderer> mr = inven_bar->AddComponent<MeshRenderer>();
//			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
//			mr->material = Resources::Find<Material>(L"BarMaterial01");
//			mr->material->texture = tooltip_npk->GetTexture(L"tooltip.img", 3);
//			mr->material->render_mode = graphics::ERenderMode::Transparent;
//			inven_base->AddChild(inven_bar);
//		}
//#pragma region base2 ui 
//		std::shared_ptr<GameObject> inven_base2_tab = object::Instantiate<GameObject>(
//			Vector3(-0.05f, 0.43f, 0.0f),
//			Vector3::Zero,
//			Vector3(0.9f, 0.045f, 1.0f),
//			ELayerType::UI
//			);
//		{
//			inven_base2_tab->SetName(L"inven_base2_tab");
//			inven_base2_tab->ismove = false;
//			std::shared_ptr<MeshRenderer> mr = inven_base2_tab->AddComponent<MeshRenderer>();
//			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
//			mr->material = Resources::Find<Material>(L"InvenBasetab01");
//			mr->material->texture = inven_npk->GetTexture(L"inventory.img", 203);
//			mr->material->render_mode = graphics::ERenderMode::Transparent;
//			inven_base->AddChild(inven_base2_tab);
//		}
//		std::shared_ptr<GameObject> inven_base2_eft = object::Instantiate<GameObject>(
//			Vector3(0.0f, 0.21f, -0.01f),
//			Vector3::Zero,
//			Vector3(0.4f, 0.4f, 1.0f),
//			ELayerType::UI
//			);
//		{
//			inven_base2_eft->SetName(L"inven_base2_eft");
//			inven_base2_eft->ismove = false;
//			std::shared_ptr<MeshRenderer> mr = inven_base2_eft->AddComponent<MeshRenderer>();
//			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
//			mr->material = Resources::Find<Material>(L"InvenBaseEftMaterial");
//			mr->material->texture = inven_npk->GetTexture(L"inventory.img", 178);
//			mr->material->render_mode = graphics::ERenderMode::Transparent;
//			inven_base->AddChild(inven_base2_eft);
//		}
//		std::shared_ptr<GameObject> inven_player = object::Instantiate<GameObject>(
//			Vector3(0.0f, 0.18f, -0.01f),
//			Vector3::Zero,
//			Vector3(0.23f, 0.19f, 1.0f),
//			ELayerType::UI
//			);
//		{
//			inven_player->SetName(L"inven_player");
//			inven_player->ismove = false;
//			std::shared_ptr<MeshRenderer> mr = inven_player->AddComponent<MeshRenderer>();
//			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
//			mr->material = Resources::Find<Material>(L"InvenPlayerMaterial");
//			mr->material->texture = mbskin_npk->GetTexture(L"mg_body80500.img", 10);
//			mr->material->render_mode = graphics::ERenderMode::Transparent;
//			inven_base->AddChild(inven_player);
//		}
//		std::shared_ptr<GameObject> inven_useitem_slot = object::Instantiate<GameObject>(
//			Vector3(0.0f, 0.32f, -0.01f),
//			Vector3::Zero,
//			Vector3(0.9f, 0.172f, 1.0f),
//			ELayerType::UI
//			);
//		{
//			inven_useitem_slot->SetName(L"InvenUseItemSlot01");
//			inven_useitem_slot->ismove = false;
//			std::shared_ptr<MeshRenderer> mr = inven_useitem_slot->AddComponent<MeshRenderer>();
//			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
//			mr->material = Resources::Find<Material>(L"InvenUseItemSlot01");
//			mr->material->texture = inven_npk->GetTexture(L"inventory.img", 21);
//			mr->material->render_mode = graphics::ERenderMode::Transparent;
//			inven_base->AddChild(inven_useitem_slot);
//		}
//		std::shared_ptr<GameObject> inven_useitem_slot2 = object::Instantiate<GameObject>(
//			Vector3(0.27f, 0.263f, -0.01f),
//			Vector3::Zero,
//			Vector3(0.125f, 0.057f, 1.0f),
//			ELayerType::UI
//			);
//		{
//			inven_useitem_slot2->SetName(L"InvenUseItemSlot02");
//			inven_useitem_slot2->ismove = false;
//			std::shared_ptr<MeshRenderer> mr = inven_useitem_slot2->AddComponent<MeshRenderer>();
//			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
//			mr->material = Resources::Find<Material>(L"InvenUseItemSlot02");
//			mr->material->texture = inven_npk->GetTexture(L"inventory.img", 19);
//			mr->material->render_mode = graphics::ERenderMode::Transparent;
//			inven_base->AddChild(inven_useitem_slot2);
//		}
//		std::shared_ptr<GameObject> inven_useitem_slot3 = object::Instantiate<GameObject>(
//			Vector3(0.39f, 0.205f, -0.01f),
//			Vector3::Zero,
//			Vector3(0.125f, 0.057f, 1.0f),
//			ELayerType::UI
//			);
//		{
//			inven_useitem_slot3->SetName(L"InvenUseItemSlot03");
//			inven_useitem_slot3->ismove = false;
//			std::shared_ptr<MeshRenderer> mr = inven_useitem_slot3->AddComponent<MeshRenderer>();
//			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
//			mr->material = Resources::Find<Material>(L"InvenUseItemSlot03");
//			mr->material->texture = inven_npk->GetTexture(L"inventory.img", 20);
//			mr->material->render_mode = graphics::ERenderMode::Transparent;
//			inven_base->AddChild(inven_useitem_slot3);
//		}
//		std::shared_ptr<GameObject> inven_useitem_slot4 = object::Instantiate<GameObject>(
//			Vector3(0.27f, 0.205f, -0.01f),
//			Vector3::Zero,
//			Vector3(0.125f, 0.057f, 1.0f),
//			ELayerType::UI
//			);
//		{
//			inven_useitem_slot4->SetName(L"InvenUseItemSlot04");
//			inven_useitem_slot4->ismove = false;
//			std::shared_ptr<MeshRenderer> mr = inven_useitem_slot4->AddComponent<MeshRenderer>();
//			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
//			mr->material = Resources::Find<Material>(L"InvenUseItemSlot04");
//			mr->material->texture = inven_npk->GetTexture(L"inventory.img", 122);
//			mr->material->render_mode = graphics::ERenderMode::Transparent;
//			inven_base->AddChild(inven_useitem_slot4);
//		}
//
//		std::shared_ptr<GameObject> inven_book1 = object::Instantiate<GameObject>(
//			Vector3(-0.42f, 0.095f, -0.01f),
//			Vector3::Zero,
//			Vector3(0.065f, 0.038f, 1.0f),
//			ELayerType::UI
//			);
//		{
//			inven_book1->SetName(L"inven_book1");
//			inven_book1->ismove = false;
//			std::shared_ptr<MeshRenderer> mr = inven_book1->AddComponent<MeshRenderer>();
//			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
//			mr->material = Resources::Find<Material>(L"InvenBook01");
//			mr->material->texture = inven_npk->GetTexture(L"inventory.img", 50);
//			mr->material->render_mode = graphics::ERenderMode::Transparent;
//			inven_base->AddChild(inven_book1);
//		}
//		std::shared_ptr<GameObject> inven_book2 = object::Instantiate<GameObject>(
//			Vector3(-0.35f, 0.095f, -0.01f),
//			Vector3::Zero,
//			Vector3(0.065f, 0.038f, 1.0f),
//			ELayerType::UI
//			);
//		{
//			inven_book2->SetName(L"inven_book2");
//			inven_book2->ismove = false;
//			std::shared_ptr<MeshRenderer> mr = inven_book2->AddComponent<MeshRenderer>();
//			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
//			mr->material = Resources::Find<Material>(L"InvenBook02");
//			mr->material->texture = inven_npk->GetTexture(L"inventory.img", 128);
//			mr->material->render_mode = graphics::ERenderMode::Transparent;
//			inven_base->AddChild(inven_book2);
//		}
//		std::shared_ptr<GameObject> inven_book3 = object::Instantiate<GameObject>(
//			Vector3(-0.28f, 0.095f, -0.01f),
//			Vector3::Zero,
//			Vector3(0.065f, 0.038f, 1.0f),
//			ELayerType::UI
//			);
//		{
//			inven_book3->SetName(L"inven_book3");
//			inven_book3->ismove = false;
//			std::shared_ptr<MeshRenderer> mr = inven_book3->AddComponent<MeshRenderer>();
//			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
//			mr->material = Resources::Find<Material>(L"InvenBook03");
//			mr->material->texture = inven_npk->GetTexture(L"inventory.img", 134);
//			mr->material->render_mode = graphics::ERenderMode::Transparent;
//			inven_base->AddChild(inven_book3);
//		}
//		std::shared_ptr<GameObject> inven_book4 = object::Instantiate<GameObject>(
//			Vector3(0.42f, 0.095f, -0.01f),
//			Vector3::Zero,
//			Vector3(0.065f, 0.038f, 1.0f),
//			ELayerType::UI
//			);
//		{
//			inven_book4->SetName(L"inven_book4");
//			inven_book4->ismove = false;
//			std::shared_ptr<MeshRenderer> mr = inven_book4->AddComponent<MeshRenderer>();
//			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
//			mr->material = Resources::Find<Material>(L"InvenBook04");
//			mr->material->texture = inven_npk->GetTexture(L"inventory.img", 172);
//			mr->material->render_mode = graphics::ERenderMode::Transparent;
//			inven_base->AddChild(inven_book4);
//		}
//
//#pragma endregion
//
//#pragma region base3 ui
//		std::shared_ptr<GameObject> inven_base3_tab = object::Instantiate<GameObject>(
//			Vector3(-0.045f, 0.035f, 0.0f),
//			Vector3::Zero,
//			Vector3(0.9f, 0.045f, 1.0f),
//			ELayerType::UI
//			);
//		{
//			inven_base3_tab->SetName(L"inven_base3_tab");
//			inven_base3_tab->ismove = false;
//			std::shared_ptr<MeshRenderer> mr = inven_base3_tab->AddComponent<MeshRenderer>();
//			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
//			mr->material = Resources::Find<Material>(L"InvenBasetab02");
//			mr->material->texture = inven_npk->GetTexture(L"inventory.img", 202);
//			mr->material->render_mode = graphics::ERenderMode::Transparent;
//			inven_base->AddChild(inven_base3_tab);
//		}
//		std::shared_ptr<GameObject> inven_icon1 = object::Instantiate<GameObject>(
//			Vector3(-0.42f, -0.473f, -0.0001f),
//			Vector3::Zero,
//			Vector3(0.08f, 0.04f, 1.0f),
//			ELayerType::UI
//			);
//		{
//			inven_icon1->SetName(L"inven_icon1");
//			inven_icon1->ismove = false;
//			std::shared_ptr<MeshRenderer> mr = inven_icon1->AddComponent<MeshRenderer>();
//			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
//			mr->material = Resources::Find<Material>(L"InvenIcon01");
//			mr->material->texture = inven_npk->GetTexture(L"inventory.img", 4);
//			mr->material->render_mode = graphics::ERenderMode::Transparent;
//			inven_base->AddChild(inven_icon1);
//		}
//		std::shared_ptr<GameObject> inven_icon2 = object::Instantiate<GameObject>(
//			Vector3(0.06f, -0.473f, 0.0f),
//			Vector3::Zero,
//			Vector3(0.08f, 0.04f, 1.0f),
//			ELayerType::UI
//			);
//		{
//			inven_icon2->SetName(L"inven_icon2");
//			inven_icon2->ismove = false;
//			std::shared_ptr<MeshRenderer> mr = inven_icon2->AddComponent<MeshRenderer>();
//			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
//			mr->material = Resources::Find<Material>(L"InvenIcon02");
//			mr->material->texture = inven_npk->GetTexture(L"inventory.img", 8);
//			mr->material->render_mode = graphics::ERenderMode::Transparent;
//			inven_base->AddChild(inven_icon2);
//		}
//	    startx = -0.4f;
//		starty = -0.32f;
//		for (int i = 0; i < 7; i++)
//		{
//			for (int j = 0; j < 8; j++)
//			{
//				int index = i * 8 + j;
//				float x = startx + 0.115 * j;
//				float y = starty + 0.051 * i;
//				std::shared_ptr<GameObject> inven_slot = object::Instantiate<GameObject>(
//					Vector3(x, y, -0.001f),
//					Vector3::Zero,
//					Vector3(0.12f, 0.0525f, 1.0f),
//					ELayerType::UI
//					);
//				{
//					std::wstring name = L"inven_slot" + index;
//					inven_slot->SetName(name);
//					inven_slot->ismove = false;
//					std::shared_ptr<MeshRenderer> mr = inven_slot->AddComponent<MeshRenderer>();
//					mr->mesh = Resources::Find<Mesh>(L"RectMesh");
//					mr->material = Resources::Find<Material>(L"InvenSlotMaterial01");
//					mr->material->texture = inven_npk->GetTexture(L"inventory.img", 49);
//					mr->material->render_mode = graphics::ERenderMode::Transparent;
//					inven_base->AddChild(inven_slot);
//				}
//			}
//		}
//		std::shared_ptr<GameObject> inven_base3_icon1 = object::Instantiate<GameObject>(
//			Vector3(-0.06f, -0.37f, -0.0f),
//			Vector3::Zero,
//			Vector3(0.5f, 0.0125f, 1.0f),
//			ELayerType::UI
//			);
//		{
//			inven_base3_icon1->SetName(L"inven_base3_icon1");
//			inven_base3_icon1->ismove = false;
//			std::shared_ptr<MeshRenderer> mr = inven_base3_icon1->AddComponent<MeshRenderer>();
//			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
//			mr->material = Resources::Find<Material>(L"InvenBase3Icon01");
//			mr->material->texture = inven_npk->GetTexture(L"inventory.img", 2);
//			mr->material->render_mode = graphics::ERenderMode::Transparent;
//			inven_base->AddChild(inven_base3_icon1);
//		}
//		std::shared_ptr<GameObject> inven_base3_icon2 = object::Instantiate<GameObject>(
//			Vector3(-0.075f, -0.37f, -0.001f),
//			Vector3::Zero,
//			Vector3(0.45f, 0.005f, 1.0f),
//			ELayerType::UI
//			);
//		{
//			inven_base3_icon2->SetName(L"inven_base3_icon2");
//			inven_base3_icon2->ismove = false;
//			std::shared_ptr<MeshRenderer> mr = inven_base3_icon2->AddComponent<MeshRenderer>();
//			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
//			mr->material = Resources::Find<Material>(L"InvenBase3Icon02");
//			mr->material->texture = inven_npk->GetTexture(L"inventory.img", 1);
//			mr->material->render_mode = graphics::ERenderMode::Transparent;
//			inven_base->AddChild(inven_base3_icon2);
//		}
//		std::shared_ptr<GameObject> inven_base3_icon3 = object::Instantiate<GameObject>(
//			Vector3(0.23f, -0.368f, -0.0f),
//			Vector3::Zero,
//			Vector3(0.07f, 0.04f, 1.0f),
//			ELayerType::UI
//			);
//		{
//			inven_base3_icon3->SetName(L"inven_base3_icon3");
//			inven_base3_icon3->ismove = false;
//			std::shared_ptr<MeshRenderer> mr = inven_base3_icon3->AddComponent<MeshRenderer>();
//			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
//			mr->material = Resources::Find<Material>(L"InvenBase3Icon03");
//			mr->material->texture = inven_npk->GetTexture(L"inventory.img", 95);
//			mr->material->render_mode = graphics::ERenderMode::Transparent;
//			inven_base->AddChild(inven_base3_icon3);
//		}
//		std::shared_ptr<GameObject> inven_base3_icon4 = object::Instantiate<GameObject>(
//			Vector3(0.31f, -0.368f, -0.0f),
//			Vector3::Zero,
//			Vector3(0.07f, 0.041f, 1.0f),
//			ELayerType::UI
//			);
//		{
//			inven_base3_icon4->SetName(L"inven_base3_icon4");
//			inven_base3_icon4->ismove = false;
//			std::shared_ptr<MeshRenderer> mr = inven_base3_icon4->AddComponent<MeshRenderer>();
//			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
//			mr->material = Resources::Find<Material>(L"InvenBase3Icon04");
//			mr->material->texture = inven_npk->GetTexture(L"inventory.img", 79);
//			mr->material->render_mode = graphics::ERenderMode::Transparent;
//			inven_base->AddChild(inven_base3_icon4);
//		}
//		std::shared_ptr<GameObject> inven_base3_icon5 = object::Instantiate<GameObject>(
//			Vector3(0.4f, -0.368f, -0.0f),
//			Vector3::Zero,
//			Vector3(0.07f, 0.04f, 1.0f),
//			ELayerType::UI
//			);
//		{
//			inven_base3_icon5->SetName(L"inven_base3_icon5");
//			inven_base3_icon5->ismove = false;
//			std::shared_ptr<MeshRenderer> mr = inven_base3_icon5->AddComponent<MeshRenderer>();
//			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
//			mr->material = Resources::Find<Material>(L"InvenBase3Icon05");
//			mr->material->texture = inven_npk->GetTexture(L"inventory.img", 74);
//			mr->material->render_mode = graphics::ERenderMode::Transparent;
//			inven_base->AddChild(inven_base3_icon5);
//		}
//#pragma endregion
//
//#pragma endregion
//
//#pragma region skill tool tip
//		std::shared_ptr<GameObject> skill_tooltip_base = object::Instantiate<GameObject>(
//			Vector3(-1.0f, 0.0f, -0.01f),
//			Vector3::Zero,
//			Vector3(4.7f, 3.5f, 1.0f),
//			ELayerType::UI
//			);
//		{
//			skill_tooltip_base->SetName(L"SkillTooltipBase");
//			skill_tooltip_base->ismove = false;
//			std::shared_ptr<MeshRenderer> mr = skill_tooltip_base->AddComponent<MeshRenderer>();
//			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
//			mr->material = Resources::Find<Material>(L"SkillTooltipBaseMaterial01");
//			mr->material->texture = tooltip_npk->GetTexture(L"newskillshop.img", 0);
//			//mr->material->render_mode = graphics::ERenderMode::Transparent;
//		}
//
//		std::shared_ptr<Transform> skill_tooltip_parrent = skill_tooltip_base->GetComponent<Transform>();
//		std::shared_ptr<GameObject> skill_tooltip_bar = object::Instantiate<GameObject>(
//			Vector3(0.0f, 0.5f, -0.01f),
//			Vector3::Zero,
//			Vector3(1.00f, 0.04f, 1.0f),
//			ELayerType::UI
//			);
//		{
//			skill_tooltip_bar->SetName(L"SkillTooltipBar");
//			skill_tooltip_bar->ismove = false;
//			std::shared_ptr<MeshRenderer> mr = skill_tooltip_bar->AddComponent<MeshRenderer>();
//			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
//			mr->material = Resources::Find<Material>(L"BarMaterial01");
//			mr->material->texture = tooltip_npk->GetTexture(L"tooltip.img", 3);
//			//mr->material->render_mode = graphics::ERenderMode::Transparent;
//			skill_tooltip_base->AddChild(skill_tooltip_bar);
//		}
//
//		std::shared_ptr<GameObject> skill_tooltip_base2 = object::Instantiate<GameObject>(
//			Vector3(0.3465f, 0.3f, -0.01f),
//			Vector3::Zero,
//			Vector3(0.295f, 0.32f, 1.0f),
//			ELayerType::UI
//			);
//		{
//			skill_tooltip_base2->SetName(L"SkillTooltipBase2");
//			skill_tooltip_base2->ismove = false;
//			std::shared_ptr<MeshRenderer> mr = skill_tooltip_base2->AddComponent<MeshRenderer>();
//			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
//			mr->material = Resources::Find<Material>(L"SkillTooltipBaseMaterial02");
//			mr->material->texture = tooltip_npk->GetTexture(L"newskillshop.img", 71);
//			//mr->material->render_mode = graphics::ERenderMode::Transparent;
//			skill_tooltip_base->AddChild(skill_tooltip_base2);
//		}
//
//		std::shared_ptr<GameObject> skill_tooltip_icon1 = object::Instantiate<GameObject>(
//			Vector3(-0.43f, 0.45f, -0.01f),
//			Vector3::Zero,
//			Vector3(0.12f, 0.045f, 1.0f),
//			ELayerType::UI
//			);
//		{
//			skill_tooltip_icon1->SetName(L"SkillTooltipIcon1");
//			skill_tooltip_icon1->ismove = false;
//			std::shared_ptr<MeshRenderer> mr = skill_tooltip_icon1->AddComponent<MeshRenderer>();
//			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
//			mr->material = Resources::Find<Material>(L"SkillTooltipIconMaterial01");
//			mr->material->texture = tooltip_npk->GetTexture(L"newskillshop.img", 1);
//			mr->material->render_mode = graphics::ERenderMode::Transparent;
//			skill_tooltip_base->AddChild(skill_tooltip_icon1);
//		}
//		std::shared_ptr<GameObject> skill_tooltip_icon2 = object::Instantiate<GameObject>(
//			Vector3(-0.31f, 0.45f, -0.01f),
//			Vector3::Zero,
//			Vector3(0.12f, 0.045f, 1.0f),
//			ELayerType::UI
//			);
//		{
//			skill_tooltip_icon2->SetName(L"SkillTooltipIcon2");
//			skill_tooltip_icon2->ismove = false;
//			std::shared_ptr<MeshRenderer> mr = skill_tooltip_icon2->AddComponent<MeshRenderer>();
//			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
//			mr->material = Resources::Find<Material>(L"SkillTooltipIconMaterial02");
//			mr->material->texture = tooltip_npk->GetTexture(L"newskillshop.img", 5);
//			mr->material->render_mode = graphics::ERenderMode::Transparent;
//			skill_tooltip_base->AddChild(skill_tooltip_icon2);
//		}
//		std::shared_ptr<GameObject> skill_tooltip_icon3 = object::Instantiate<GameObject>(
//			Vector3(-0.365f, 0.39f, -0.01f),
//			Vector3::Zero,
//			Vector3(0.23f, 0.04f, 1.0f),
//			ELayerType::UI
//			);
//		{
//			skill_tooltip_icon3->SetName(L"SkillTooltipIcon3");
//			skill_tooltip_icon3->ismove = false;
//			std::shared_ptr<MeshRenderer> mr = skill_tooltip_icon3->AddComponent<MeshRenderer>();
//			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
//			mr->material = Resources::Find<Material>(L"SkillTooltipIconMaterial03");
//			mr->material->texture = tooltip_npk->GetTexture(L"newskillshop.img", 9);
//			mr->material->render_mode = graphics::ERenderMode::Transparent;
//			skill_tooltip_base->AddChild(skill_tooltip_icon3);
//		}
//		std::shared_ptr<GameObject> skill_tooltip_icon4 = object::Instantiate<GameObject>(
//			Vector3(-0.13f, 0.39f, -0.01f),
//			Vector3::Zero,
//			Vector3(0.23f, 0.04f, 1.0f),
//			ELayerType::UI
//			);
//		{
//			skill_tooltip_icon4->SetName(L"SkillTooltipIcon4");
//			skill_tooltip_icon4->ismove = false;
//			std::shared_ptr<MeshRenderer> mr = skill_tooltip_icon4->AddComponent<MeshRenderer>();
//			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
//			mr->material = Resources::Find<Material>(L"SkillTooltipIconMaterial04");
//			mr->material->texture = tooltip_npk->GetTexture(L"newskillshop.img", 13);
//			mr->material->render_mode = graphics::ERenderMode::Transparent;
//			skill_tooltip_base->AddChild(skill_tooltip_icon4);
//		}
//
//		//초기화 버튼 캡처 편집 npk 만들기
//		/*std::shared_ptr<GameObject> skill_tooltip_icon5 = object::Instantiate<GameObject>(
//			Vector3(-0.13f, 0.39f, -0.01f),
//			Vector3::Zero,
//			Vector3(0.23f, 0.04f, 1.0f),
//			ELayerType::UI
//			);
//		{
//			skill_tooltip_icon5->SetName(L"SkillTooltipIcon5");
//			skill_tooltip_icon5->ismove = false;
//			std::shared_ptr<MeshRenderer> mr = skill_tooltip_icon5->AddComponent<MeshRenderer>();
//			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
//			mr->material = Resources::Find<Material>(L"SkillTooltipIconMaterial04");
//			mr->material->texture = tooltip_npk->GetTexture(L"newskillshop.img", 13);
//			mr->material->render_mode = graphics::ERenderMode::Transparent;
//			std::shared_ptr<Transform> tf = skill_tooltip_icon5->GetComponent<Transform>();
//			tf->parent = skill_tooltip_parrent;
//		}*/
//		//자동찍기 버튼 캡처 편집 npk
//	/*	std::shared_ptr<GameObject> skill_tooltip_icon5 = object::Instantiate<GameObject>(
//			Vector3(-0.13f, 0.39f, -0.01f),
//			Vector3::Zero,
//			Vector3(0.23f, 0.04f, 1.0f),
//			ELayerType::UI
//			);
//		{
//			skill_tooltip_icon5->SetName(L"SkillTooltipIcon5");
//			skill_tooltip_icon5->ismove = false;
//			std::shared_ptr<MeshRenderer> mr = skill_tooltip_icon5->AddComponent<MeshRenderer>();
//			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
//			mr->material = Resources::Find<Material>(L"SkillTooltipIconMaterial04");
//			mr->material->texture = tooltip_npk->GetTexture(L"newskillshop.img", 13);
//			mr->material->render_mode = graphics::ERenderMode::Transparent;
//			std::shared_ptr<Transform> tf = skill_tooltip_icon5->GetComponent<Transform>();
//			tf->parent = skill_tooltip_parrent;
//		}*/
//
//		std::shared_ptr<GameObject> skill_tooltip_skill1 = object::Instantiate<GameObject>(
//			Vector3(-0.13f, 0.2f, -0.01f),
//			Vector3::Zero,
//			Vector3(0.05f, 0.08f, 1.0f),
//			ELayerType::UI
//			);
//		{
//			skill_tooltip_skill1->SetName(L"SkillTooltipSkill1");
//			skill_tooltip_skill1->ismove = false;
//			std::shared_ptr<MeshRenderer> mr = skill_tooltip_skill1->AddComponent<MeshRenderer>();
//			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
//			mr->material = Resources::Find<Material>(L"SkillTooltipSkillMaterial01");
//			mr->material->texture = tooltip_npk->GetTexture(L"newskillshop.img", 34);
//			mr->material->render_mode = graphics::ERenderMode::Transparent;
//			std::shared_ptr<Transform> tf = skill_tooltip_skill1->GetComponent<Transform>();
//			skill_tooltip_base->AddChild(skill_tooltip_skill1);
//		}
//
//		std::shared_ptr<GameObject> skill_tooltip_skill2 = object::Instantiate<GameObject>(
//			Vector3(-0.13f, 0.05f, -0.01f),
//			Vector3::Zero,
//			Vector3(0.05f, 0.08f, 1.0f),
//			ELayerType::UI
//			);
//		{
//			skill_tooltip_skill2->SetName(L"SkillTooltipSkill2");
//			skill_tooltip_skill2->ismove = false;
//			std::shared_ptr<MeshRenderer> mr = skill_tooltip_skill2->AddComponent<MeshRenderer>();
//			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
//			mr->material = Resources::Find<Material>(L"SkillTooltipSkillMaterial01");
//			mr->material->texture = tooltip_npk->GetTexture(L"newskillshop.img", 34);
//			mr->material->render_mode = graphics::ERenderMode::Transparent;
//			skill_tooltip_base->AddChild(skill_tooltip_skill2);
//		}
//
//
//#pragma endregion

#pragma region obj
		std::shared_ptr<Image> SeriaNPC = object::Instantiate<Image>(
			Vector3(0.2f, 0.15f, 0.98f),
			Vector3::Zero,
			Vector3(1.0f, 1.25f, 1.0f),
			ELayerType::BackObject);
		{
			SeriaNPC->SetName(L"SeriaNPC");
			SeriaNPC->ismove = false;
			std::shared_ptr<MeshRenderer> mr = SeriaNPC->GetComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"DefaultAniMaterial");
			std::shared_ptr<Animator> ani = SeriaNPC->AddComponent<Animator>();
			ani->Create(L"npc", L"seria_event_2012summer.img",L"SeriaNPC_Room", 0, 33, 0.1f);
			ani->PlayAnimation(L"SeriaNPC_Room", true);
		}
		std::shared_ptr<Image> GoldBox = object::Instantiate<Image>(
			Vector3(-1.3f, -0.45f, 0.98f),
			Vector3::Zero,
			Vector3(0.75f, 0.75f, 1.0f),
			ELayerType::BackObject);
		{
			GoldBox->SetName(L"GoldBox");
			GoldBox->ismove = false;
			std::shared_ptr<MeshRenderer> mr = GoldBox->GetComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"DefaultAniMaterial");
			std::shared_ptr<Animator> ani = GoldBox->AddComponent<Animator>();
			ani->Create(L"npc", L"storagebrilliantdiamond.img", L"GoldBoxNPC_Room", 0, 18, 0.1f);
			ani->PlayAnimation(L"GoldBoxNPC_Room", true);
		}
	

		std::shared_ptr<Image> PremiumCoinShop = object::Instantiate<Image>(
			Vector3(1.5f, 0.0f, 0.98f),
			Vector3::Zero,
			Vector3(3.0f, 3.0f, 1.0f),
			ELayerType::BackObject);
		{
			PremiumCoinShop->SetName(L"PremiumCoinShop");
			PremiumCoinShop->ismove = false;
			std::shared_ptr<MeshRenderer> mr = PremiumCoinShop->GetComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"DefaultAniMaterial");
			std::shared_ptr<Animator> ani = PremiumCoinShop->AddComponent<Animator>();
			ani->Create(L"npc", L"npc_coin.img", L"CoinNPC_Room", 0, 28, 0.1f);
			ani->PlayAnimation(L"CoinNPC_Room", true);
		}
		std::shared_ptr<Image> EnchantBook = object::Instantiate<Image>(
			Vector3(0.9f, 0.6f, 0.98f),
			Vector3::Zero,
			Vector3(2.5f, 2.5f, 1.0f),
			ELayerType::BackObject);
		{
			EnchantBook->SetName(L"EnchantBook");
			EnchantBook->ismove = false;
			std::shared_ptr<MeshRenderer> mr = EnchantBook->GetComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"DefaultAniMaterial");
			std::shared_ptr<Animator> ani = EnchantBook->AddComponent<Animator>();
			ani->Create(L"npc", L"enchant_book_normal.img", L"EnchantBookNPC_Room", 0, 8, 0.12f);
			ani->PlayAnimation(L"EnchantBookNPC_Room", true);
		}
		std::shared_ptr<Image> EnchantBookEft = object::Instantiate<Image>(
			Vector3(-0.001f, 0.0f, 0.0f),
			Vector3::Zero,
			Vector3(1.0f, 1.0f, 1.0f));
		{
			EnchantBookEft->SetName(L"EnchantBookEft");
			EnchantBookEft->ismove = false;
			std::shared_ptr<MeshRenderer> mr = EnchantBookEft->GetComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"DefaultEffectAniMaterial");
			std::shared_ptr<Animator> ani = EnchantBookEft->AddComponent<Animator>();
			ani->Create(L"npc", L"enchant_book_front_dodge.img", L"EnchantBookNPCEft_Room", 0, 8, 0.18f);
			ani->PlayAnimation(L"EnchantBookNPCEft_Room", true);
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
			std::shared_ptr<MeshRenderer> mr = PostBox->GetComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"DefaultMaterial");
			std::shared_ptr<ImageComponent> imageComp = PostBox->GetComponent<ImageComponent>();
			imageComp->SetSprite(L"npc", L"postbox.img", 0);
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
		ELayerType::Player);
	{
		camera->SetName(L"camera");
		camera->AddScript<CameraScript>();
		std::shared_ptr<Camera> cameraComp = camera->AddComponent<Camera>();
		cameraComp->TurnLayerMask(ELayerType::UI, false);
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

	std::shared_ptr<GameObject> portal01 = object::Instantiate<GameObject>(
		Vector3(-0.0f, -1.8f, 0.0f),
		Vector3::Zero,
		Vector3(0.5f, 0.7f, 1.0f),
		ELayerType::Portal
		);
	portal01->AddComponent<Collider2D>();
	std::shared_ptr<PortalScript> portalscript = portal01->AddScript<PortalScript>();
	portalscript->SetType(EMapType::PlayTestScene);


	CollisionManager::SetLayer(ELayerType::Player, ELayerType::Portal,true);
}

void roka::SeriaGateScene::Loading()
{
}
