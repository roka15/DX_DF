#include "SeriaGateScene.h"
#include "Resources.h"
#include "MeshRenderer.h"
#include "Transform.h"
#include "Camera.h"
#include "CameraScript.h"
#include "GridScript.h"

#include "Mesh.h"
#include "Material.h"

#include "NPK.h"

#include "RokaTime.h"
#include "Object.h"
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
#pragma region base bg
		std::shared_ptr<GameObject> bg = object::Instantiate<GameObject>(
			Vector3(0.15f, 0.0f, 0.98f),
			Vector3::Zero,
			Vector3(8.5f, 4.4f, 1.0f),
			ELayerType::BackObject);
		{
			bg->SetName(L"BackGround");
			bg->ismove = false;
			std::shared_ptr<MeshRenderer> mr = bg->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"BGMaterial");

			{
				std::shared_ptr<Texture> texture = npk->GetTexture(L"bg", 0);
				mr->material->texture = texture;
			}
		}
#pragma endregion

#pragma region front tree
		std::shared_ptr<GameObject> frontTree = object::Instantiate<GameObject>(
			Vector3(-2.6f, 0.0f, 0.98f),
			Vector3::Zero,
			Vector3(3.0f, 4.4f, 1.0f),
			ELayerType::BackObject);
		{
			frontTree->SetName(L"FrontTree");
			frontTree->ismove = false;
			std::shared_ptr<MeshRenderer> mr = frontTree->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"FrontObjMaterial01");
			{
				std::shared_ptr<Texture>texture = npk->GetTexture(L"border_tree", 0);
				mr->material->texture = texture;
			}
		}
		std::shared_ptr<GameObject> frontTree2 = object::Instantiate<GameObject>(
			Vector3(3.4f, 0.0f, 0.98f),
			Vector3::Zero,
			Vector3(2.0f, 4.4f, 1.0f),
			ELayerType::BackObject);
		{
			frontTree2->SetName(L"FrontTree2");
			frontTree2->ismove = false;
			std::shared_ptr<MeshRenderer> mr = frontTree2->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"FrontObjMaterial02");
			{
				std::shared_ptr<Texture>texture = npk->GetTexture(L"border_tree", 1);
				mr->material->texture = texture;
			}
		}

#pragma endregion

#pragma region flower bg

		std::shared_ptr<GameObject> Flower01 = object::Instantiate<GameObject>(
			Vector3(-2.0f, 1.8f, 0.98f),
			Vector3::Zero,
			Vector3(0.15f, 0.15f, 1.0f),
			ELayerType::BackObject
			);
		{
			Flower01->SetName(L"Flower01");
			Flower01->ismove = false;
			std::shared_ptr<MeshRenderer> mr = Flower01->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"FlowerMaterial01");
			{
				std::shared_ptr<Texture>texture = npk->GetTexture(L"flower_1", 0);
				mr->material->texture = texture;
			}
		}

		std::shared_ptr<GameObject> Flower02 = object::Instantiate<GameObject>(
			Vector3(-3.6f, 0.7f, 0.98f),
			Vector3::Zero,
			Vector3(0.15f, 0.15f, 1.0f),
			ELayerType::BackObject
			);
		{
			Flower02->SetName(L"Flower02");
			Flower02->ismove = false;
			std::shared_ptr<MeshRenderer> mr = Flower02->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"FlowerMaterial01");
		}
		std::shared_ptr<GameObject> Flower03 = object::Instantiate<GameObject>(
			Vector3(2.0f, 2.0f, 0.98f),
			Vector3(Vector3(0.0f, 0.0f, Deg2Rad(180))),
			Vector3(0.15f, 0.15f, 1.0f),
			ELayerType::BackObject
			);
		{
			Flower03->SetName(L"Flower03");
			Flower03->ismove = false;
			std::shared_ptr<MeshRenderer> mr = Flower03->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"FlowerMaterial01");
		}

		std::shared_ptr<GameObject> Flower04 = object::Instantiate<GameObject>(
			Vector3(1.5f, 2.0f, 0.98f),
			Vector3(Vector3(0.0f, 0.0f, Deg2Rad(180))),
			Vector3(0.15f, 0.15f, 1.0f),
			ELayerType::BackObject
			);
		{
			Flower04->SetName(L"Flower04");
			Flower04->ismove = false;
			std::shared_ptr<MeshRenderer> mr = Flower04->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"FlowerMaterial02");
			{
				std::shared_ptr<Texture>texture = npk->GetTexture(L"flower_2", 0);
				mr->material->texture = texture;
			}
		}

		std::shared_ptr<GameObject> Flower05 = object::Instantiate<GameObject>(
			Vector3(-3.3f, 2.0f, 0.98f),
			Vector3::Zero,
			Vector3(0.15f, 0.15f, 1.0f),
			ELayerType::BackObject
			);
		{
			Flower05->SetName(L"Flower05");
			Flower05->ismove = false;
			std::shared_ptr<MeshRenderer> mr = Flower05->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"FlowerMaterial02");
		}
#pragma endregion	

#pragma region leaf bg
		std::shared_ptr<GameObject> Leaf01 = object::Instantiate<GameObject>(
			Vector3(-2.2f, 1.8f, 0.98f),
			Vector3::Zero,
			Vector3(0.15f, 0.25f, 1.0f),
			ELayerType::BackObject
			);
		{
			Leaf01->SetName(L"Leaf01");
			Leaf01->ismove = false;
			std::shared_ptr<MeshRenderer> mr = Leaf01->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"LeafMaterial01");
			{
				std::shared_ptr<Texture>texture = npk->GetTexture(L"leaf_1", 0);
				mr->material->texture = texture;
			}
		}
		std::shared_ptr<GameObject> Leaf02 = object::Instantiate<GameObject>(
			Vector3(-2.6f, 2.0f, 0.98f),
			Vector3::Zero,
			Vector3(0.15f, 0.25f, 1.0f),
			ELayerType::BackObject
			);
		{
			Leaf02->SetName(L"Leaf02");
			Leaf02->ismove = false;
			std::shared_ptr<MeshRenderer> mr = Leaf02->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"LeafMaterial03");
			{
				std::shared_ptr<Texture>texture = npk->GetTexture(L"leaf_3", 0);
				mr->material->texture = texture;
			}
		}
		std::shared_ptr<GameObject> Leaf03 = object::Instantiate<GameObject>(
			Vector3(-3.5f, 1.9f, 0.98f),
			Vector3::Zero,
			Vector3(0.15f, 0.25f, 1.0f),
			ELayerType::BackObject
			);
		{
			Leaf03->SetName(L"Leaf03");
			Leaf03->ismove = false;
			std::shared_ptr<MeshRenderer> mr = Leaf03->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"LeafMaterial03");
		}

		std::shared_ptr<GameObject> Leaf04 = object::Instantiate<GameObject>(
			Vector3(2.5f, 1.8f, 0.98f),
			Vector3::Zero,
			Vector3(0.15f, 0.25f, 1.0f),
			ELayerType::BackObject
			);
		{
			Leaf04->SetName(L"Leaf04");
			Leaf04->ismove = false;
			std::shared_ptr<MeshRenderer> mr = Leaf04->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"LeafMaterial02");
			{
				std::shared_ptr<Texture>texture = npk->GetTexture(L"leaf_2", 0);
				mr->material->texture = texture;
			}
		}

		std::shared_ptr<GameObject> Leaf05 = object::Instantiate<GameObject>(
			Vector3(1.1f, 2.0f, 0.98f),
			Vector3::Zero,
			Vector3(0.15f, 0.25f, 1.0f),
			ELayerType::BackObject
			);
		{
			Leaf05->SetName(L"Leaf05");
			Leaf05->ismove = false;
			std::shared_ptr<MeshRenderer> mr = Leaf05->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"LeafMaterial02");
		}

		std::shared_ptr<GameObject> Leaf06 = object::Instantiate<GameObject>(
			Vector3(2.0f, 1.8f, 0.98f),
			Vector3::Zero,
			Vector3(0.15f, 0.25f, 1.0f),
			ELayerType::BackObject
			);
		{
			Leaf06->SetName(L"Leaf06");
			Leaf06->ismove = false;
			std::shared_ptr<MeshRenderer> mr = Leaf06->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"LeafMaterial03");
		}

		std::shared_ptr<GameObject> Leaf07 = object::Instantiate<GameObject>(
			Vector3(1.5f, 1.8f, 0.98f),
			Vector3::Zero,
			Vector3(0.15f, 0.25f, 1.0f),
			ELayerType::BackObject
			);
		{
			Leaf07->SetName(L"Leaf07");
			Leaf07->ismove = false;
			std::shared_ptr<MeshRenderer> mr = Leaf07->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"LeafMaterial01");
		}
#pragma endregion

#pragma region gate
		std::shared_ptr<GameObject> MGateRight = object::Instantiate<GameObject>(
			Vector3(0.8f, -1.5f, 0.1f),
			Vector3::Zero,
			Vector3(1.0f, 1.25f, 1.0f),
			ELayerType::FrontObject);
		{
			MGateRight->SetName(L"MGateRight");
			MGateRight->ismove = false;
			std::shared_ptr<MeshRenderer> mr = MGateRight->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"GateMaterial01");
			{
				std::shared_ptr<Texture>texture = npk->GetTexture(L"gate_new", 0);
				mr->material->texture = texture;
			}
		}
		std::shared_ptr<GameObject> MGateLeft = object::Instantiate<GameObject>(
			Vector3(-0.7f, -1.5f, 0.1f),
			Vector3::Zero,
			Vector3(1.0f, 1.25f, 1.0f),
			ELayerType::FrontObject);
		{
			MGateLeft->SetName(L"MGateLeft");
			MGateLeft->ismove = false;
			std::shared_ptr<MeshRenderer> mr = MGateLeft->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"GateVInverseMaterial01");
			{
				std::shared_ptr<Texture>texture = npk->GetTexture(L"gate_new", 0);
				mr->material->texture = texture;
			}
		}
		std::shared_ptr<GameObject> DoorEft = object::Instantiate<GameObject>(
			Vector3(3.4f, -0.3f, 0.98f),
			Vector3::Zero,
			Vector3(0.4f, 1.2f, 1.0f),
			ELayerType::BackObject);
		{
			DoorEft->SetName(L"DoorEft");
			DoorEft->ismove = false;
			std::shared_ptr<MeshRenderer> mr = DoorEft->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"SeriaGateDoorEftMaterial");
			mr->material->render_mode = ERenderMode::Transparent;
			mr->material->shader->bsstate = EBSType::OneOne;
			{
				std::shared_ptr<Texture>texture = gate_npk->GetTexture(L"seriagate_dooreffect.img", 3);
				mr->material->texture = texture;
			}
		}

		std::shared_ptr<GameObject> GateDown = object::Instantiate<GameObject>(
			Vector3(3.3f, -1.1f, 0.98f),
			Vector3::Zero,
			Vector3(0.6f, 0.25f, 1.0f),
			ELayerType::BackObject);
		{
			GateDown->SetName(L"GateDown");
			GateDown->ismove = false;
			std::shared_ptr<MeshRenderer> mr = GateDown->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"GateDownMaterial01");
			{
				std::shared_ptr<Texture>texture = gate_npk->GetTexture(L"gatedown.img", 0);
				mr->material->texture = texture;
			}
		}
		/*	GameObject* GateDownThin = object::Instantiate<GameObject>(
				Vector3(3.3f, -1.1f, 0.98f),
				Vector3::Zero,
				Vector3(0.6f, 0.25f, 1.0f),
				ELayerType::BackObject);
			{
				GateDownThin->SetName(L"GateDownThin");
				GateDownThin->ismove = false;
				MeshRenderer* mr = GateDownThin->AddComponent<MeshRenderer>();
				mr->mesh = Resources::Find<Mesh>(L"RectMesh");
				mr->material = Resources::Find<Material>(L"GateDownThinMaterial");
				mr->material->render_mode = ERenderMode::Transparent;
				{
					std::shared_ptr<Texture>texture = gate_npk->GetTexture(L"gatedownthin.img", 0);
					mr->material->texture = texture;
				}
			}*/

		std::shared_ptr<GameObject> GateUp = object::Instantiate<GameObject>(
			Vector3(-0.0f, 1.7f, 0.0f),
			Vector3::Zero,
			Vector3(1.0f, 4.0f, 1.0f),
			ELayerType::BackObject);
		{
			GateUp->SetName(L"GateUp");
			GateUp->ismove = false;
			std::shared_ptr<MeshRenderer> mr = GateUp->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"GateUpMaterial01");
			//mr->material->render_mode = ERenderMode::Transparent;
			{
				std::shared_ptr<Texture>texture = gate_npk->GetTexture(L"gateup.img", 0);
				mr->material->texture = texture;
			}
			std::shared_ptr<Transform> tf = GateUp->GetComponent<Transform>();
			tf->parent = GateDown->GetComponent<Transform>();
		}
#pragma endregion

#pragma region hud/ui
		std::shared_ptr<GameObject> HudBase = object::Instantiate<GameObject>(
			Vector3(0.1f, -1.92f, -10.0f),
			Vector3::Zero,
			Vector3(2.85f, 0.5f, 1.0f),
			ELayerType::UI);
		{
			HudBase->SetName(L"HudBase");
			HudBase->ismove = false;
			std::shared_ptr<MeshRenderer> mr = HudBase->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"HudBaseMaterial01");
			{
				std::shared_ptr<Texture> texture = hud_npk->GetTexture(L"hud.img", 0);
				mr->material->texture = texture;
			}
		}
		std::shared_ptr<Transform> HudBaseTF = HudBase->GetComponent<Transform>();

		std::shared_ptr<GameObject> HudBase2 = object::Instantiate<GameObject>(
			Vector3(-0.0f, -0.43f, -0.01f),
			Vector3::Zero,
			Vector3(1.1f, 0.25f, 1.0f),
			ELayerType::UI);
		{
			HudBase2->SetName(L"HudBase2");
			HudBase2->ismove = false;
			std::shared_ptr<MeshRenderer> mr = HudBase2->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"HudBaseMaterial02");
			mr->material->render_mode = ERenderMode::Transparent;

			std::shared_ptr<Transform> tf = HudBase2->GetComponent<Transform>();
			HudBaseTF->AddChild(tf);

			{
				std::shared_ptr<Texture> texture = hud_npk->GetTexture(L"hud.img", 201);
				mr->material->texture = texture;
			}
		}
		std::shared_ptr<GameObject> ExpBar = object::Instantiate<GameObject>(
			Vector3(0.01f, -0.5f, -0.01f),
			Vector3::Zero,
			Vector3(0.8f, 0.07f, 1.0f),
			ELayerType::UI);
		{
			ExpBar->SetName(L"ExpBar");
			ExpBar->ismove = false;
			std::shared_ptr<MeshRenderer> mr = ExpBar->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"ExpBarMaterial01");
			//mr->material->render_mode = ERenderMode::Transparent;

			std::shared_ptr<Transform> tf = ExpBar->GetComponent<Transform>();
			HudBaseTF->AddChild(tf);
			{
				std::shared_ptr<Texture> texture = hud_npk->GetTexture(L"hud.img", 24);
				mr->material->texture = texture;
			}
		}

		std::shared_ptr<GameObject> HPBase = object::Instantiate<GameObject>(
			Vector3(-0.4f, 0.0f, 0.0f),
			Vector3::Zero,
			Vector3(0.14f, 0.7f, 1.0f),
			ELayerType::UI);
		{
			HPBase->SetName(L"HPBase");
			HPBase->ismove = false;
			std::shared_ptr<MeshRenderer> mr = HPBase->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"HPBaseMaterial01");

			std::shared_ptr<Transform> tf = HPBase->GetComponent<Transform>();
			HudBaseTF->AddChild(tf);
			{
				std::shared_ptr<Texture> texture = hud_npk->GetTexture(L"hud.img", 1);
				mr->material->texture = texture;
			}
		}
		std::shared_ptr<GameObject> MPBase = object::Instantiate<GameObject>(
			Vector3(0.39f, 0.0f, 0.0f),
			Vector3::Zero,
			Vector3(0.14f, 0.7f, 1.0f),
			ELayerType::UI);
		{
			MPBase->SetName(L"MPBase");
			MPBase->ismove = false;
			std::shared_ptr<MeshRenderer> mr = MPBase->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"MPBaseMaterial01");

			std::shared_ptr<Transform> tf = MPBase->GetComponent<Transform>();
			HudBaseTF->AddChild(tf);
			{
				std::shared_ptr<Texture> texture = hud_npk->GetTexture(L"hud.img", 2);
				mr->material->texture = texture;
			}
		}
		std::shared_ptr<GameObject> HPFilter = object::Instantiate<GameObject>(
			Vector3(-0.395f, -0.01f, 0.0f),
			Vector3::Zero,
			Vector3(0.175f, 0.85f, 1.0f),
			ELayerType::UI);
		{
			HPFilter->SetName(L"HPFilter");
			HPFilter->ismove = false;
			std::shared_ptr<MeshRenderer> mr = HPFilter->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"HPFilterMaterial01");
			mr->material->render_mode = ERenderMode::Transparent;
			std::shared_ptr<Transform> tf = HPFilter->GetComponent<Transform>();
			HudBaseTF->AddChild(tf);
			{
				std::shared_ptr<Texture> texture = hud_npk->GetTexture(L"hud.img", 211);
				mr->material->texture = texture;
			}
		}
		std::shared_ptr<GameObject> MPFilter = object::Instantiate<GameObject>(
			Vector3(0.385f, -0.01f, 0.0f),
			Vector3::Zero,
			Vector3(0.175f, 0.85f, 1.0f),
			ELayerType::UI);
		{
			MPFilter->SetName(L"MPFilter");
			MPFilter->ismove = false;
			std::shared_ptr<MeshRenderer> mr = MPFilter->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"MPFilterMaterial01");
			mr->material->render_mode = ERenderMode::Transparent;
			std::shared_ptr<Transform> tf = MPFilter->GetComponent<Transform>();
			HudBaseTF->AddChild(tf);
			{
				std::shared_ptr<Texture> texture = hud_npk->GetTexture(L"hud.img", 212);
				mr->material->texture = texture;
			}
		}
		std::shared_ptr<GameObject> SkillQuickSlot01 = object::Instantiate<GameObject>(
			Vector3(-0.194f, 0.17f, 0.0f),
			Vector3::Zero,
			Vector3(0.08f, 0.45f, 1.0f),
			ELayerType::UI);
		{
			SkillQuickSlot01->SetName(L"SkillQuickSlot01");
			SkillQuickSlot01->ismove = false;
			std::shared_ptr<MeshRenderer> mr = SkillQuickSlot01->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"SkillQuickSlotMaterial01");

			std::shared_ptr<Transform> tf = SkillQuickSlot01->GetComponent<Transform>();
			HudBaseTF->AddChild(tf);
			{
				std::shared_ptr<Texture> texture = hud_npk->GetTexture(L"hud.img", 196);
				mr->material->texture = texture;
			}
		}
		std::shared_ptr<GameObject> SkillQuickSlot02 = object::Instantiate<GameObject>(
			Vector3(-0.116f, 0.17f, 0.0f),
			Vector3::Zero,
			Vector3(0.08f, 0.45f, 1.0f),
			ELayerType::UI);
		{
			SkillQuickSlot02->SetName(L"SkillQuickSlot02");
			SkillQuickSlot02->ismove = false;
			std::shared_ptr<MeshRenderer> mr = SkillQuickSlot02->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"SkillQuickSlotMaterial01");

			std::shared_ptr<Transform> tf = SkillQuickSlot02->GetComponent<Transform>();
			HudBaseTF->AddChild(tf);
		}
		std::shared_ptr<GameObject> SkillQuickSlot03 = object::Instantiate<GameObject>(
			Vector3(-0.038f, 0.17f, 0.0f),
			Vector3::Zero,
			Vector3(0.08f, 0.45f, 1.0f),
			ELayerType::UI);
		{
			SkillQuickSlot03->SetName(L"SkillQuickSlot03");
			SkillQuickSlot03->ismove = false;
			std::shared_ptr<MeshRenderer> mr = SkillQuickSlot03->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"SkillQuickSlotMaterial01");

			std::shared_ptr<Transform> tf = SkillQuickSlot03->GetComponent<Transform>();
			HudBaseTF->AddChild(tf);
		}
		std::shared_ptr<GameObject> SkillQuickSlot04 = object::Instantiate<GameObject>(
			Vector3(0.04f, 0.17f, 0.0f),
			Vector3::Zero,
			Vector3(0.08f, 0.45f, 1.0f),
			ELayerType::UI);
		{
			SkillQuickSlot04->SetName(L"SkillQuickSlot04");
			SkillQuickSlot04->ismove = false;
			std::shared_ptr<MeshRenderer> mr = SkillQuickSlot04->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"SkillQuickSlotMaterial01");

			std::shared_ptr<Transform> tf = SkillQuickSlot04->GetComponent<Transform>();
			HudBaseTF->AddChild(tf);
		}
		std::shared_ptr<GameObject> SkillQuickSlot05 = object::Instantiate<GameObject>(
			Vector3(0.118f, 0.17f, 0.0f),
			Vector3::Zero,
			Vector3(0.08f, 0.45f, 1.0f),
			ELayerType::UI);
		{
			SkillQuickSlot05->SetName(L"SkillQuickSlot05");
			SkillQuickSlot05->ismove = false;
			std::shared_ptr<MeshRenderer> mr = SkillQuickSlot05->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"SkillQuickSlotMaterial01");

			std::shared_ptr<Transform> tf = SkillQuickSlot05->GetComponent<Transform>();
			HudBaseTF->AddChild(tf);
		}
		std::shared_ptr<GameObject> SkillQuickSlot06 = object::Instantiate<GameObject>(
			Vector3(0.196f, 0.17f, 0.0f),
			Vector3::Zero,
			Vector3(0.08f, 0.45f, 1.0f),
			ELayerType::UI);
		{
			SkillQuickSlot06->SetName(L"SkillQuickSlot06");
			SkillQuickSlot06->ismove = false;
			std::shared_ptr<MeshRenderer> mr = SkillQuickSlot06->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"SkillQuickSlotMaterial01");

			std::shared_ptr<Transform> tf = SkillQuickSlot06->GetComponent<Transform>();
			HudBaseTF->AddChild(tf);
		}
		std::shared_ptr<GameObject> SkillQuickSlot07 = object::Instantiate<GameObject>(
			Vector3(0.274f, 0.17f, 0.0f),
			Vector3::Zero,
			Vector3(0.08f, 0.45f, 1.0f),
			ELayerType::UI);
		{
			SkillQuickSlot07->SetName(L"SkillQuickSlot07");
			SkillQuickSlot07->ismove = false;
			std::shared_ptr<MeshRenderer> mr = SkillQuickSlot07->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"SkillQuickSlotMaterial01");

			std::shared_ptr<Transform> tf = SkillQuickSlot07->GetComponent<Transform>();
			HudBaseTF->AddChild(tf);
		}
		std::shared_ptr<GameObject> SkillQuickSlot08 = object::Instantiate<GameObject>(
			Vector3(-0.194f, -0.26f, 0.0f),
			Vector3::Zero,
			Vector3(0.08f, 0.45f, 1.0f),
			ELayerType::UI);
		{
			SkillQuickSlot08->SetName(L"SkillQuickSlot08");
			SkillQuickSlot08->ismove = false;
			std::shared_ptr<MeshRenderer> mr = SkillQuickSlot08->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"SkillQuickSlotMaterial01");

			std::shared_ptr<Transform> tf = SkillQuickSlot08->GetComponent<Transform>();
			HudBaseTF->AddChild(tf);
		}
		std::shared_ptr<GameObject> SkillQuickSlot09 = object::Instantiate<GameObject>(
			Vector3(-0.116f, -0.26f, 0.0f),
			Vector3::Zero,
			Vector3(0.08f, 0.45f, 1.0f),
			ELayerType::UI);
		{
			SkillQuickSlot09->SetName(L"SkillQuickSlot09");
			SkillQuickSlot09->ismove = false;
			std::shared_ptr<MeshRenderer> mr = SkillQuickSlot09->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"SkillQuickSlotMaterial01");

			std::shared_ptr<Transform> tf = SkillQuickSlot09->GetComponent<Transform>();
			HudBaseTF->AddChild(tf);
		}
		std::shared_ptr<GameObject> SkillQuickSlot10 = object::Instantiate<GameObject>(
			Vector3(-0.038f, -0.26f, 0.0f),
			Vector3::Zero,
			Vector3(0.08f, 0.45f, 1.0f),
			ELayerType::UI);
		{
			SkillQuickSlot10->SetName(L"SkillQuickSlot10");
			SkillQuickSlot10->ismove = false;
			std::shared_ptr<MeshRenderer> mr = SkillQuickSlot10->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"SkillQuickSlotMaterial01");

			std::shared_ptr<Transform> tf = SkillQuickSlot10->GetComponent<Transform>();
			HudBaseTF->AddChild(tf);
		}
		std::shared_ptr<GameObject> SkillQuickSlot11 = object::Instantiate<GameObject>(
			Vector3(0.04f, -0.26f, 0.0f),
			Vector3::Zero,
			Vector3(0.08f, 0.45f, 1.0f),
			ELayerType::UI);
		{
			SkillQuickSlot11->SetName(L"SkillQuickSlot11");
			SkillQuickSlot11->ismove = false;
			std::shared_ptr<MeshRenderer> mr = SkillQuickSlot11->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"SkillQuickSlotMaterial01");

			std::shared_ptr<Transform> tf = SkillQuickSlot11->GetComponent<Transform>();
			HudBaseTF->AddChild(tf);
		}
		std::shared_ptr<GameObject> SkillQuickSlot12 = object::Instantiate<GameObject>(
			Vector3(0.118f, -0.26f, 0.0f),
			Vector3::Zero,
			Vector3(0.08f, 0.45f, 1.0f),
			ELayerType::UI);
		{
			SkillQuickSlot12->SetName(L"SkillQuickSlot12");
			SkillQuickSlot12->ismove = false;
			std::shared_ptr<MeshRenderer> mr = SkillQuickSlot12->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"SkillQuickSlotMaterial01");

			std::shared_ptr<Transform> tf = SkillQuickSlot12->GetComponent<Transform>();
			HudBaseTF->AddChild(tf);
		}
		std::shared_ptr<GameObject> SkillQuickSlot13 = object::Instantiate<GameObject>(
			Vector3(0.196f, -0.26f, 0.0f),
			Vector3::Zero,
			Vector3(0.08f, 0.45f, 1.0f),
			ELayerType::UI);
		{
			SkillQuickSlot13->SetName(L"SkillQuickSlot13");
			SkillQuickSlot13->ismove = false;
			std::shared_ptr<MeshRenderer> mr = SkillQuickSlot13->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"SkillQuickSlotMaterial01");

			std::shared_ptr<Transform> tf = SkillQuickSlot13->GetComponent<Transform>();
			HudBaseTF->AddChild(tf);
		}
		std::shared_ptr<GameObject> SkillQuickSlot14 = object::Instantiate<GameObject>(
			Vector3(0.274f, -0.26f, 0.0f),
			Vector3::Zero,
			Vector3(0.08f, 0.45f, 1.0f),
			ELayerType::UI);
		{
			SkillQuickSlot14->SetName(L"SkillQuickSlot14");
			SkillQuickSlot14->ismove = false;
			std::shared_ptr<MeshRenderer> mr = SkillQuickSlot14->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"SkillQuickSlotMaterial01");

			std::shared_ptr<Transform> tf = SkillQuickSlot14->GetComponent<Transform>();
			HudBaseTF->AddChild(tf);
		}
		std::shared_ptr<GameObject> MoreSkillBtn = object::Instantiate<GameObject>(
			Vector3(-0.26f, 0.16f, 0.0f),
			Vector3::Zero,
			Vector3(0.055f, 0.45f, 1.0f),
			ELayerType::UI);
		{
			MoreSkillBtn->SetName(L"MoreSkillBtn");
			MoreSkillBtn->ismove = false;
			std::shared_ptr<MeshRenderer> mr = MoreSkillBtn->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"MoreSkillBtnMaterial01");

			std::shared_ptr<Transform> tf = MoreSkillBtn->GetComponent<Transform>();
			HudBaseTF->AddChild(tf);
			{
				std::shared_ptr<Texture> texture = hud_npk->GetTexture(L"hud.img", 192);
				mr->material->texture = texture;
			}
		}
		std::shared_ptr<GameObject> SkillChangeBtn = object::Instantiate<GameObject>(
			Vector3(-0.26f, -0.25f, 0.0f),
			Vector3::Zero,
			Vector3(0.055f, 0.45f, 1.0f),
			ELayerType::UI);
		{
			SkillChangeBtn->SetName(L"SkillChangeBtn");
			SkillChangeBtn->ismove = false;
			std::shared_ptr<MeshRenderer> mr = SkillChangeBtn->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"SkillChangeBtnMaterial01");

			std::shared_ptr<Transform> tf = SkillChangeBtn->GetComponent<Transform>();
			HudBaseTF->AddChild(tf);
			{
				std::shared_ptr<Texture> texture = hud_npk->GetTexture(L"hud.img", 53);
				mr->material->texture = texture;
			}
		}

		std::shared_ptr<GameObject> ItemSlot1 = object::Instantiate<GameObject>(
			Vector3(-0.6f, -0.32f, 0.0f),
			Vector3::Zero,
			Vector3(0.08f, 0.45f, 1.0f),
			ELayerType::UI);
		{
			ItemSlot1->SetName(L"ItemSlot1");
			ItemSlot1->ismove = false;
			std::shared_ptr<MeshRenderer> mr = ItemSlot1->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"ItemSlotMaterial01");

			std::shared_ptr<Transform> tf = ItemSlot1->GetComponent<Transform>();
			HudBaseTF->AddChild(tf);
			{
				std::shared_ptr<Texture> texture = hud_npk->GetTexture(L"hud.img", 199);
				mr->material->texture = texture;
			}
		}
		std::shared_ptr<GameObject> ItemSlot2 = object::Instantiate<GameObject>(
			Vector3(-0.68f, -0.32f, 0.0f),
			Vector3::Zero,
			Vector3(0.08f, 0.45f, 1.0f),
			ELayerType::UI);
		{
			ItemSlot2->SetName(L"ItemSlot2");
			ItemSlot2->ismove = false;
			std::shared_ptr<MeshRenderer> mr = ItemSlot2->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"ItemSlotMaterial01");

			std::shared_ptr<Transform> tf = ItemSlot2->GetComponent<Transform>();
			HudBaseTF->AddChild(tf);
			{
				std::shared_ptr<Texture> texture = hud_npk->GetTexture(L"hud.img", 199);
				mr->material->texture = texture;
			}
		}
		std::shared_ptr<GameObject> ItemSlot3 = object::Instantiate<GameObject>(
			Vector3(-0.76f, -0.32f, 0.0f),
			Vector3::Zero,
			Vector3(0.08f, 0.45f, 1.0f),
			ELayerType::UI);
		{
			ItemSlot3->SetName(L"ItemSlot3");
			ItemSlot3->ismove = false;
			std::shared_ptr<MeshRenderer> mr = ItemSlot3->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"ItemSlotMaterial01");

			std::shared_ptr<Transform> tf = ItemSlot3->GetComponent<Transform>();
			HudBaseTF->AddChild(tf);
			{
				std::shared_ptr<Texture> texture = hud_npk->GetTexture(L"hud.img", 199);
				mr->material->texture = texture;
			}
		}
		std::shared_ptr<GameObject> ItemSlot4 = object::Instantiate<GameObject>(
			Vector3(-0.84f, -0.32f, 0.0f),
			Vector3::Zero,
			Vector3(0.08f, 0.45f, 1.0f),
			ELayerType::UI);
		{
			ItemSlot4->SetName(L"ItemSlot4");
			ItemSlot4->ismove = false;
			std::shared_ptr<MeshRenderer> mr = ItemSlot4->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"ItemSlotMaterial01");

			std::shared_ptr<Transform> tf = ItemSlot4->GetComponent<Transform>();
			HudBaseTF->AddChild(tf);
			{
				std::shared_ptr<Texture> texture = hud_npk->GetTexture(L"hud.img", 199);
				mr->material->texture = texture;
			}
		}
		std::shared_ptr<GameObject> ItemSlot5 = object::Instantiate<GameObject>(
			Vector3(-0.92f, -0.32f, 0.0f),
			Vector3::Zero,
			Vector3(0.08f, 0.45f, 1.0f),
			ELayerType::UI);
		{
			ItemSlot5->SetName(L"ItemSlot5");
			ItemSlot5->ismove = false;
			std::shared_ptr<MeshRenderer> mr = ItemSlot5->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"ItemSlotMaterial01");

			std::shared_ptr<Transform> tf = ItemSlot5->GetComponent<Transform>();
			HudBaseTF->AddChild(tf);
			{
				std::shared_ptr<Texture> texture = hud_npk->GetTexture(L"hud.img", 199);
				mr->material->texture = texture;
			}
		}
		std::shared_ptr<GameObject> ItemSlot6 = object::Instantiate<GameObject>(
			Vector3(-1.0f, -0.32f, 0.0f),
			Vector3::Zero,
			Vector3(0.08f, 0.45f, 1.0f),
			ELayerType::UI);
		{
			ItemSlot6->SetName(L"ItemSlot6");
			ItemSlot6->ismove = false;
			std::shared_ptr<MeshRenderer> mr = ItemSlot6->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"ItemSlotMaterial01");

			std::shared_ptr<Transform> tf = ItemSlot6->GetComponent<Transform>();
			HudBaseTF->AddChild(tf);
			{
				std::shared_ptr<Texture> texture = hud_npk->GetTexture(L"hud.img", 199);
				mr->material->texture = texture;
			}
		}

		std::shared_ptr<GameObject> Icon1 = object::Instantiate<GameObject>(
			Vector3(0.6f, -0.1f, 0.0f),
			Vector3::Zero,
			Vector3(0.13f, 0.31f, 1.0f),
			ELayerType::UI);
		{
			Icon1->SetName(L"Icon1");
			Icon1->ismove = false;
			std::shared_ptr<MeshRenderer> mr = Icon1->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"IconMaterial01");

			std::shared_ptr<Transform> tf = Icon1->GetComponent<Transform>();
			HudBaseTF->AddChild(tf);
			{
				std::shared_ptr<Texture> texture = hud_npk->GetTexture(L"hud.img", 72);
				mr->material->texture = texture;
			}
		}
		std::shared_ptr<GameObject> Icon2 = object::Instantiate<GameObject>(
			Vector3(0.69f, -0.1f, 0.0f),
			Vector3::Zero,
			Vector3(0.06f, 0.3f, 1.0f),
			ELayerType::UI);
		{
			Icon2->SetName(L"Icon2");
			Icon2->ismove = false;
			std::shared_ptr<MeshRenderer> mr = Icon2->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"IconMaterial02");

			std::shared_ptr<Transform> tf = Icon2->GetComponent<Transform>();
			HudBaseTF->AddChild(tf);
			{
				std::shared_ptr<Texture> texture = hud_npk->GetTexture(L"hud.img", 68);
				mr->material->texture = texture;
			}
		}
		std::shared_ptr<GameObject> Icon3 = object::Instantiate<GameObject>(
			Vector3(0.738f, -0.1f, 0.0f),
			Vector3::Zero,
			Vector3(0.04f, 0.3f, 1.0f),
			ELayerType::UI);
		{
			Icon3->SetName(L"Icon3");
			Icon3->ismove = false;
			std::shared_ptr<MeshRenderer> mr = Icon3->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"IconMaterial03");

			std::shared_ptr<Transform> tf = Icon3->GetComponent<Transform>();
			HudBaseTF->AddChild(tf);
			{
				std::shared_ptr<Texture> texture = hud_npk->GetTexture(L"hud.img", 93);
				mr->material->texture = texture;
			}
		}
		std::shared_ptr<GameObject> Icon4 = object::Instantiate<GameObject>(
			Vector3(0.772f, -0.1f, 0.0f),
			Vector3::Zero,
			Vector3(0.04f, 0.3f, 1.0f),
			ELayerType::UI);
		{
			Icon4->SetName(L"Icon4");
			Icon4->ismove = false;
			std::shared_ptr<MeshRenderer> mr = Icon4->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"IconMaterial04");

			std::shared_ptr<Transform> tf = Icon4->GetComponent<Transform>();
			HudBaseTF->AddChild(tf);
			{
				std::shared_ptr<Texture> texture = hud_npk->GetTexture(L"hud.img", 94);
				mr->material->texture = texture;
			}
		}
		std::shared_ptr<GameObject> Icon5 = object::Instantiate<GameObject>(
			Vector3(0.806f, -0.1f, 0.0f),
			Vector3::Zero,
			Vector3(0.04f, 0.3f, 1.0f),
			ELayerType::UI);
		{
			Icon5->SetName(L"Icon5");
			Icon5->ismove = false;
			std::shared_ptr<MeshRenderer> mr = Icon5->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"IconMaterial05");

			std::shared_ptr<Transform> tf = Icon5->GetComponent<Transform>();
			HudBaseTF->AddChild(tf);
			{
				std::shared_ptr<Texture> texture = hud_npk->GetTexture(L"hud.img", 95);
				mr->material->texture = texture;
			}
		}
		std::shared_ptr<GameObject> Icon6 = object::Instantiate<GameObject>(
			Vector3(0.84f, -0.1f, 0.0f),
			Vector3::Zero,
			Vector3(0.04f, 0.3f, 1.0f),
			ELayerType::UI);
		{
			Icon6->SetName(L"Icon6");
			Icon6->ismove = false;
			std::shared_ptr<MeshRenderer> mr = Icon6->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"IconMaterial06");

			std::shared_ptr<Transform> tf = Icon6->GetComponent<Transform>();
			HudBaseTF->AddChild(tf);
			{
				std::shared_ptr<Texture> texture = hud_npk->GetTexture(L"hud.img", 96);
				mr->material->texture = texture;
			}
		}
		std::shared_ptr<GameObject> Icon7 = object::Instantiate<GameObject>(
			Vector3(0.874f, -0.1f, 0.0f),
			Vector3::Zero,
			Vector3(0.04f, 0.3f, 1.0f),
			ELayerType::UI);
		{
			Icon7->SetName(L"Icon6");
			Icon7->ismove = false;
			std::shared_ptr<MeshRenderer> mr = Icon7->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"IconMaterial07");

			std::shared_ptr<Transform> tf = Icon7->GetComponent<Transform>();
			HudBaseTF->AddChild(tf);
			{
				std::shared_ptr<Texture> texture = hud_npk->GetTexture(L"hud.img", 97);
				mr->material->texture = texture;
			}
		}
		std::shared_ptr<GameObject> Icon8 = object::Instantiate<GameObject>(
			Vector3(0.57f, -0.29f, 0.0f),
			Vector3::Zero,
			Vector3(0.05f, 0.1f, 1.0f),
			ELayerType::UI);
		{
			Icon8->SetName(L"Icon8");
			Icon8->ismove = false;
			std::shared_ptr<MeshRenderer> mr = Icon8->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"IconMaterial08");

			std::shared_ptr<Transform> tf = Icon8->GetComponent<Transform>();
			HudBaseTF->AddChild(tf);
			{
				std::shared_ptr<Texture> texture = hud_npk->GetTexture(L"hud.img", 210);
				mr->material->texture = texture;
			}
		}
		std::shared_ptr<GameObject> Icon9 = object::Instantiate<GameObject>(
			Vector3(0.75f, -0.3f, 0.0f),
			Vector3::Zero,
			Vector3(0.28f, 0.1f, 1.0f),
			ELayerType::UI);
		{
			Icon9->SetName(L"Icon9");
			Icon9->ismove = false;
			std::shared_ptr<MeshRenderer> mr = Icon9->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"IconMaterial09");

			std::shared_ptr<Transform> tf = Icon9->GetComponent<Transform>();
			HudBaseTF->AddChild(tf);
			{
				std::shared_ptr<Texture> texture = hud_npk->GetTexture(L"hud.img", 202);
				mr->material->texture = texture;
			}
		}
		std::shared_ptr<GameObject> Icon10 = object::Instantiate<GameObject>(
			Vector3(0.725f, -0.425f, 0.0f),
			Vector3::Zero,
			Vector3(0.33f, 0.15f, 1.0f),
			ELayerType::UI);
		{
			Icon10->SetName(L"Icon10");
			Icon10->ismove = false;
			std::shared_ptr<MeshRenderer> mr = Icon10->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"IconMaterial10");

			std::shared_ptr<Transform> tf = Icon10->GetComponent<Transform>();
			HudBaseTF->AddChild(tf);
			{
				std::shared_ptr<Texture> texture = hud_npk->GetTexture(L"hud.img", 241);
				mr->material->texture = texture;
			}
		}

		std::shared_ptr<GameObject> Icon11 = object::Instantiate<GameObject>(
			Vector3(0.75f, -0.3f, 0.0f),
			Vector3::Zero,
			Vector3(0.27f, 0.05f, 1.0f),
			ELayerType::UI);
		{
			Icon11->SetName(L"Icon11");
			Icon11->ismove = false;
			std::shared_ptr<MeshRenderer> mr = Icon11->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"IconMaterial11");

			std::shared_ptr<Transform> tf = Icon11->GetComponent<Transform>();
			HudBaseTF->AddChild(tf);
			{
				std::shared_ptr<Texture> texture = hud_npk->GetTexture(L"hud.img", 3);
				mr->material->texture = texture;
			}
		}
		std::shared_ptr<GameObject> Icon12 = object::Instantiate<GameObject>(
			Vector3(0.76f, -0.425f, 0.0f),
			Vector3::Zero,
			Vector3(0.25f, 0.05f, 1.0f),
			ELayerType::UI);
		{
			Icon12->SetName(L"Icon12");
			Icon12->ismove = false;
			std::shared_ptr<MeshRenderer> mr = Icon12->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"IconMaterial12");

			std::shared_ptr<Transform> tf = Icon12->GetComponent<Transform>();
			HudBaseTF->AddChild(tf);
			{
				std::shared_ptr<Texture> texture = hud_npk->GetTexture(L"hud.img", 22);
				mr->material->texture = texture;
			}
		}
#pragma endregion

#pragma region inventory ui
		std::shared_ptr<GameObject> inven_base = object::Instantiate<GameObject>(
			Vector3(3.0f, 0.0f, 0.0f),
			Vector3::Zero,
			Vector3(1.4f, 3.0f, 1.0f),
			ELayerType::UI
			);
		{
			inven_base->SetName(L"InvenBase");
			inven_base->ismove = false;
			std::shared_ptr<MeshRenderer> mr = inven_base->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"InvenBaseMaterial01");
			mr->material->texture = inven_npk->GetTexture(L"inventory.img", 175);
			mr->material->render_mode = graphics::ERenderMode::Transparent;
		}

		std::shared_ptr<Transform> inven_parrent = inven_base->GetComponent<Transform>();

		std::shared_ptr<GameObject> inven_base2 = object::Instantiate<GameObject>(
			Vector3(0.0f, 0.24f, -0.01f),
			Vector3::Zero,
			Vector3(0.95f, 0.35f, 1.0f),
			ELayerType::UI
			);
		{
			inven_base2->SetName(L"InvenBase2");
			inven_base2->ismove = false;
			std::shared_ptr<MeshRenderer> mr = inven_base2->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"InvenBaseMaterial02");
			mr->material->texture = inven_npk->GetTexture(L"inventory.img", 0);
			mr->material->render_mode = graphics::ERenderMode::Transparent;
			std::shared_ptr<Transform> tf = inven_base2->GetComponent<Transform>();
			tf->parent = inven_parrent;
		}

		std::shared_ptr<GameObject> inven_base3 = object::Instantiate<GameObject>(
			Vector3(0.0f, -0.19f, 0.1f),
			Vector3::Zero,
			Vector3(0.95f, 0.42f, 1.0f),
			ELayerType::UI
			);
		{
			inven_base3->SetName(L"InvenBase3");
			inven_base3->ismove = false;
			std::shared_ptr<MeshRenderer> mr = inven_base3->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"InvenBaseMaterial04");
			mr->material->texture = inven_npk->GetTexture(L"inventory.img", 39);
			mr->material->render_mode = graphics::ERenderMode::Transparent;
			std::shared_ptr<Transform> tf = inven_base3->GetComponent<Transform>();
			tf->parent = inven_parrent;
		}

		std::shared_ptr<GameObject> inven_base4 = object::Instantiate<GameObject>(
			Vector3(0.0f, -0.45f, 0.0f),
			Vector3::Zero,
			Vector3(0.95f, 0.09f, 1.0f),
			ELayerType::UI
			);
		{
			inven_base4->SetName(L"InvenBase4");
			inven_base4->ismove = false;
			std::shared_ptr<MeshRenderer> mr = inven_base4->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"InvenBaseMaterial03");
			mr->material->texture = inven_npk->GetTexture(L"inventory.img", 27);
			mr->material->render_mode = graphics::ERenderMode::Transparent;
			std::shared_ptr<Transform> tf = inven_base4->GetComponent<Transform>();
			tf->parent = inven_parrent;
		}

		std::shared_ptr<GameObject> inven_bar = object::Instantiate<GameObject>(
			Vector3(0.0f, 0.48f, 0.0f),
			Vector3::Zero,
			Vector3(1.0f, 0.05f, 1.0f),
			ELayerType::UI
			);
		{
			inven_bar->SetName(L"InvenBar");
			inven_bar->ismove = false;
			std::shared_ptr<MeshRenderer> mr = inven_bar->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"BarMaterial01");
			mr->material->texture = tooltip_npk->GetTexture(L"tooltip.img", 3);
			mr->material->render_mode = graphics::ERenderMode::Transparent;
			std::shared_ptr<Transform> tf = inven_bar->GetComponent<Transform>();
			tf->parent = inven_parrent;
		}
#pragma region base2 ui 
		std::shared_ptr<GameObject> inven_base2_tab = object::Instantiate<GameObject>(
			Vector3(-0.05f, 0.43f, 0.0f),
			Vector3::Zero,
			Vector3(0.9f, 0.045f, 1.0f),
			ELayerType::UI
			);
		{
			inven_base2_tab->SetName(L"inven_base2_tab");
			inven_base2_tab->ismove = false;
			std::shared_ptr<MeshRenderer> mr = inven_base2_tab->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"InvenBasetab01");
			mr->material->texture = inven_npk->GetTexture(L"inventory.img", 203);
			mr->material->render_mode = graphics::ERenderMode::Transparent;
			std::shared_ptr<Transform> tf = inven_base2_tab->GetComponent<Transform>();
			tf->parent = inven_parrent;
		}
		std::shared_ptr<GameObject> inven_base2_eft = object::Instantiate<GameObject>(
			Vector3(0.0f, 0.21f, -0.01f),
			Vector3::Zero,
			Vector3(0.4f, 0.4f, 1.0f),
			ELayerType::UI
			);
		{
			inven_base2_eft->SetName(L"inven_base2_eft");
			inven_base2_eft->ismove = false;
			std::shared_ptr<MeshRenderer> mr = inven_base2_eft->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"InvenBaseEftMaterial");
			mr->material->texture = inven_npk->GetTexture(L"inventory.img", 178);
			mr->material->render_mode = graphics::ERenderMode::Transparent;
			std::shared_ptr<Transform> tf = inven_base2_eft->GetComponent<Transform>();
			tf->parent = inven_parrent;
		}
		std::shared_ptr<GameObject> inven_player = object::Instantiate<GameObject>(
			Vector3(0.0f, 0.18f, -0.01f),
			Vector3::Zero,
			Vector3(0.23f, 0.19f, 1.0f),
			ELayerType::UI
			);
		{
			inven_player->SetName(L"inven_player");
			inven_player->ismove = false;
			std::shared_ptr<MeshRenderer> mr = inven_player->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"InvenPlayerMaterial");
			mr->material->texture = mbskin_npk->GetTexture(L"mg_body80500.img", 10);
			mr->material->render_mode = graphics::ERenderMode::Transparent;
			std::shared_ptr<Transform> tf = inven_player->GetComponent<Transform>();
			tf->parent = inven_parrent;
		}
		std::shared_ptr<GameObject> inven_useitem_slot = object::Instantiate<GameObject>(
			Vector3(0.0f, 0.32f, -0.01f),
			Vector3::Zero,
			Vector3(0.9f, 0.172f, 1.0f),
			ELayerType::UI
			);
		{
			inven_useitem_slot->SetName(L"InvenUseItemSlot01");
			inven_useitem_slot->ismove = false;
			std::shared_ptr<MeshRenderer> mr = inven_useitem_slot->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"InvenUseItemSlot01");
			mr->material->texture = inven_npk->GetTexture(L"inventory.img", 21);
			mr->material->render_mode = graphics::ERenderMode::Transparent;
			std::shared_ptr<Transform> tf = inven_useitem_slot->GetComponent<Transform>();
			tf->parent = inven_parrent;
		}
		std::shared_ptr<GameObject> inven_useitem_slot2 = object::Instantiate<GameObject>(
			Vector3(0.27f, 0.263f, -0.01f),
			Vector3::Zero,
			Vector3(0.125f, 0.057f, 1.0f),
			ELayerType::UI
			);
		{
			inven_useitem_slot2->SetName(L"InvenUseItemSlot02");
			inven_useitem_slot2->ismove = false;
			std::shared_ptr<MeshRenderer> mr = inven_useitem_slot2->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"InvenUseItemSlot02");
			mr->material->texture = inven_npk->GetTexture(L"inventory.img", 19);
			mr->material->render_mode = graphics::ERenderMode::Transparent;
			std::shared_ptr<Transform> tf = inven_useitem_slot2->GetComponent<Transform>();
			tf->parent = inven_parrent;
		}
		std::shared_ptr<GameObject> inven_useitem_slot3 = object::Instantiate<GameObject>(
			Vector3(0.39f, 0.205f, -0.01f),
			Vector3::Zero,
			Vector3(0.125f, 0.057f, 1.0f),
			ELayerType::UI
			);
		{
			inven_useitem_slot3->SetName(L"InvenUseItemSlot03");
			inven_useitem_slot3->ismove = false;
			std::shared_ptr<MeshRenderer> mr = inven_useitem_slot3->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"InvenUseItemSlot03");
			mr->material->texture = inven_npk->GetTexture(L"inventory.img", 20);
			mr->material->render_mode = graphics::ERenderMode::Transparent;
			std::shared_ptr<Transform> tf = inven_useitem_slot3->GetComponent<Transform>();
			tf->parent = inven_parrent;
		}
		std::shared_ptr<GameObject> inven_useitem_slot4 = object::Instantiate<GameObject>(
			Vector3(0.27f, 0.205f, -0.01f),
			Vector3::Zero,
			Vector3(0.125f, 0.057f, 1.0f),
			ELayerType::UI
			);
		{
			inven_useitem_slot4->SetName(L"InvenUseItemSlot04");
			inven_useitem_slot4->ismove = false;
			std::shared_ptr<MeshRenderer> mr = inven_useitem_slot4->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"InvenUseItemSlot04");
			mr->material->texture = inven_npk->GetTexture(L"inventory.img", 122);
			mr->material->render_mode = graphics::ERenderMode::Transparent;
			std::shared_ptr<Transform> tf = inven_useitem_slot4->GetComponent<Transform>();
			tf->parent = inven_parrent;
		}

		std::shared_ptr<GameObject> inven_book1 = object::Instantiate<GameObject>(
			Vector3(-0.42f, 0.095f, -0.01f),
			Vector3::Zero,
			Vector3(0.065f, 0.038f, 1.0f),
			ELayerType::UI
			);
		{
			inven_book1->SetName(L"inven_book1");
			inven_book1->ismove = false;
			std::shared_ptr<MeshRenderer> mr = inven_book1->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"InvenBook01");
			mr->material->texture = inven_npk->GetTexture(L"inventory.img", 50);
			mr->material->render_mode = graphics::ERenderMode::Transparent;
			std::shared_ptr<Transform> tf = inven_book1->GetComponent<Transform>();
			tf->parent = inven_parrent;
		}
		std::shared_ptr<GameObject> inven_book2 = object::Instantiate<GameObject>(
			Vector3(-0.35f, 0.095f, -0.01f),
			Vector3::Zero,
			Vector3(0.065f, 0.038f, 1.0f),
			ELayerType::UI
			);
		{
			inven_book2->SetName(L"inven_book2");
			inven_book2->ismove = false;
			std::shared_ptr<MeshRenderer> mr = inven_book2->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"InvenBook02");
			mr->material->texture = inven_npk->GetTexture(L"inventory.img", 128);
			mr->material->render_mode = graphics::ERenderMode::Transparent;
			std::shared_ptr<Transform> tf = inven_book2->GetComponent<Transform>();
			tf->parent = inven_parrent;
		}
		std::shared_ptr<GameObject> inven_book3 = object::Instantiate<GameObject>(
			Vector3(-0.28f, 0.095f, -0.01f),
			Vector3::Zero,
			Vector3(0.065f, 0.038f, 1.0f),
			ELayerType::UI
			);
		{
			inven_book3->SetName(L"inven_book3");
			inven_book3->ismove = false;
			std::shared_ptr<MeshRenderer> mr = inven_book3->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"InvenBook03");
			mr->material->texture = inven_npk->GetTexture(L"inventory.img", 134);
			mr->material->render_mode = graphics::ERenderMode::Transparent;
			std::shared_ptr<Transform> tf = inven_book3->GetComponent<Transform>();
			tf->parent = inven_parrent;
		}
		std::shared_ptr<GameObject> inven_book4 = object::Instantiate<GameObject>(
			Vector3(0.42f, 0.095f, -0.01f),
			Vector3::Zero,
			Vector3(0.065f, 0.038f, 1.0f),
			ELayerType::UI
			);
		{
			inven_book4->SetName(L"inven_book4");
			inven_book4->ismove = false;
			std::shared_ptr<MeshRenderer> mr = inven_book4->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"InvenBook04");
			mr->material->texture = inven_npk->GetTexture(L"inventory.img", 172);
			mr->material->render_mode = graphics::ERenderMode::Transparent;
			std::shared_ptr<Transform> tf = inven_book4->GetComponent<Transform>();
			tf->parent = inven_parrent;
		}
		
#pragma endregion

#pragma region base3 ui
		std::shared_ptr<GameObject> inven_base3_tab = object::Instantiate<GameObject>(
			Vector3(-0.045f, 0.035f, 0.0f),
			Vector3::Zero,
			Vector3(0.9f, 0.045f, 1.0f),
			ELayerType::UI
			);
		{
			inven_base3_tab->SetName(L"inven_base3_tab");
			inven_base3_tab->ismove = false;
			std::shared_ptr<MeshRenderer> mr = inven_base3_tab->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"InvenBasetab02");
			mr->material->texture = inven_npk->GetTexture(L"inventory.img", 202);
			mr->material->render_mode = graphics::ERenderMode::Transparent;
			std::shared_ptr<Transform> tf = inven_base3_tab->GetComponent<Transform>();
			tf->parent = inven_parrent;
		}
		std::shared_ptr<GameObject> inven_icon1 = object::Instantiate<GameObject>(
			Vector3(-0.42f, -0.473f, -0.0001f),
			Vector3::Zero,
			Vector3(0.08f, 0.04f, 1.0f),
			ELayerType::UI
			);
		{
			inven_icon1->SetName(L"inven_icon1");
			inven_icon1->ismove = false;
			std::shared_ptr<MeshRenderer> mr = inven_icon1->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"InvenIcon01");
			mr->material->texture = inven_npk->GetTexture(L"inventory.img",4);
			mr->material->render_mode = graphics::ERenderMode::Transparent;
			std::shared_ptr<Transform> tf = inven_icon1->GetComponent<Transform>();
			tf->parent = inven_parrent;
		}
		std::shared_ptr<GameObject> inven_icon2 = object::Instantiate<GameObject>(
			Vector3(0.06f, -0.473f, 0.0f),
			Vector3::Zero,
			Vector3(0.08f, 0.04f, 1.0f),
			ELayerType::UI
			);
		{
			inven_icon2->SetName(L"inven_icon2");
			inven_icon2->ismove = false;
			std::shared_ptr<MeshRenderer> mr = inven_icon2->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"InvenIcon02");
			mr->material->texture = inven_npk->GetTexture(L"inventory.img", 8);
			mr->material->render_mode = graphics::ERenderMode::Transparent;
			std::shared_ptr<Transform> tf = inven_icon2->GetComponent<Transform>();
			tf->parent = inven_parrent;
		}
		float startx = -0.4f;
		float starty = -0.32f;
		for (int i = 0; i < 7; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				int index = i * 8 + j;
				float x = startx + 0.115 * j;
				float y = starty + 0.051 * i;
				std::shared_ptr<GameObject> inven_slot = object::Instantiate<GameObject>(
					Vector3(x, y, -0.001f),
					Vector3::Zero,
					Vector3(0.12f, 0.0525f, 1.0f),
					ELayerType::UI
					);
				{
					std::wstring name = L"inven_slot" + index;
					inven_slot->SetName(name);
					inven_slot->ismove = false;
					std::shared_ptr<MeshRenderer> mr = inven_slot->AddComponent<MeshRenderer>();
					mr->mesh = Resources::Find<Mesh>(L"RectMesh");
					mr->material = Resources::Find<Material>(L"InvenSlotMaterial01");
					mr->material->texture = inven_npk->GetTexture(L"inventory.img", 49);
					mr->material->render_mode = graphics::ERenderMode::Transparent;
					std::shared_ptr<Transform> tf = inven_slot->GetComponent<Transform>();
					tf->parent = inven_parrent;
				}
			}
		}
		std::shared_ptr<GameObject> inven_base3_icon1 = object::Instantiate<GameObject>(
			Vector3(-0.06f, -0.37f, -0.0f),
			Vector3::Zero,
			Vector3(0.5f, 0.0125f, 1.0f),
			ELayerType::UI
			);
		{
			inven_base3_icon1->SetName(L"inven_base3_icon1");
			inven_base3_icon1->ismove = false;
			std::shared_ptr<MeshRenderer> mr = inven_base3_icon1->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"InvenBase3Icon01");
			mr->material->texture = inven_npk->GetTexture(L"inventory.img", 2);
			mr->material->render_mode = graphics::ERenderMode::Transparent;
			std::shared_ptr<Transform> tf = inven_base3_icon1->GetComponent<Transform>();
			tf->parent = inven_parrent;
		}
		std::shared_ptr<GameObject> inven_base3_icon2 = object::Instantiate<GameObject>(
			Vector3(-0.075f, -0.37f, -0.001f),
			Vector3::Zero,
			Vector3(0.45f, 0.005f, 1.0f),
			ELayerType::UI
			);
		{
			inven_base3_icon2->SetName(L"inven_base3_icon2");
			inven_base3_icon2->ismove = false;
			std::shared_ptr<MeshRenderer> mr = inven_base3_icon2->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"InvenBase3Icon02");
			mr->material->texture = inven_npk->GetTexture(L"inventory.img", 1);
			mr->material->render_mode = graphics::ERenderMode::Transparent;
			std::shared_ptr<Transform> tf = inven_base3_icon2->GetComponent<Transform>();
			tf->parent = inven_parrent;
		}
		std::shared_ptr<GameObject> inven_base3_icon3 = object::Instantiate<GameObject>(
			Vector3(0.23f, -0.368f, -0.0f),
			Vector3::Zero,
			Vector3(0.07f, 0.04f, 1.0f),
			ELayerType::UI
			);
		{
			inven_base3_icon3->SetName(L"inven_base3_icon3");
			inven_base3_icon3->ismove = false;
			std::shared_ptr<MeshRenderer> mr = inven_base3_icon3->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"InvenBase3Icon03");
			mr->material->texture = inven_npk->GetTexture(L"inventory.img", 95);
			mr->material->render_mode = graphics::ERenderMode::Transparent;
			std::shared_ptr<Transform> tf = inven_base3_icon3->GetComponent<Transform>();
			tf->parent = inven_parrent;
		}
		std::shared_ptr<GameObject> inven_base3_icon4 = object::Instantiate<GameObject>(
			Vector3(0.31f, -0.368f, -0.0f),
			Vector3::Zero,
			Vector3(0.07f, 0.041f, 1.0f),
			ELayerType::UI
			);
		{
			inven_base3_icon4->SetName(L"inven_base3_icon4");
			inven_base3_icon4->ismove = false;
			std::shared_ptr<MeshRenderer> mr = inven_base3_icon4->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"InvenBase3Icon04");
			mr->material->texture = inven_npk->GetTexture(L"inventory.img", 79);
			mr->material->render_mode = graphics::ERenderMode::Transparent;
			std::shared_ptr<Transform> tf = inven_base3_icon4->GetComponent<Transform>();
			tf->parent = inven_parrent;
		}
		std::shared_ptr<GameObject> inven_base3_icon5 = object::Instantiate<GameObject>(
			Vector3(0.4f, -0.368f, -0.0f),
			Vector3::Zero,
			Vector3(0.07f, 0.04f, 1.0f),
			ELayerType::UI
			);
		{
			inven_base3_icon5->SetName(L"inven_base3_icon5");
			inven_base3_icon5->ismove = false;
			std::shared_ptr<MeshRenderer> mr = inven_base3_icon5->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"InvenBase3Icon05");
			mr->material->texture = inven_npk->GetTexture(L"inventory.img", 74);
			mr->material->render_mode = graphics::ERenderMode::Transparent;
			std::shared_ptr<Transform> tf = inven_base3_icon5->GetComponent<Transform>();
			tf->parent = inven_parrent;
		}
#pragma endregion

#pragma endregion

#pragma region skill tool tip
		std::shared_ptr<GameObject> skill_tooltip_base = object::Instantiate<GameObject>(
			Vector3(-1.0f, 0.0f, -0.01f),
			Vector3::Zero,
			Vector3(4.7f, 3.5f, 1.0f),
			ELayerType::UI
			);
		{
			skill_tooltip_base->SetName(L"SkillTooltipBase");
			skill_tooltip_base->ismove = false;
			std::shared_ptr<MeshRenderer> mr = skill_tooltip_base->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"SkillTooltipBaseMaterial01");
			mr->material->texture = tooltip_npk->GetTexture(L"newskillshop.img", 0);
			//mr->material->render_mode = graphics::ERenderMode::Transparent;
		}

		std::shared_ptr<Transform> skill_tooltip_parrent = skill_tooltip_base->GetComponent<Transform>();
		std::shared_ptr<GameObject> skill_tooltip_bar = object::Instantiate<GameObject>(
			Vector3(0.0f, 0.5f, -0.01f),
			Vector3::Zero,
			Vector3(1.00f, 0.04f, 1.0f),
			ELayerType::UI
			);
		{
			skill_tooltip_bar->SetName(L"SkillTooltipBar");
			skill_tooltip_bar->ismove = false;
			std::shared_ptr<MeshRenderer> mr = skill_tooltip_bar->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"BarMaterial01");
			mr->material->texture = tooltip_npk->GetTexture(L"tooltip.img", 3);
			//mr->material->render_mode = graphics::ERenderMode::Transparent;
			std::shared_ptr<Transform> tf = skill_tooltip_bar->GetComponent<Transform>();
			tf->parent = skill_tooltip_parrent;
		}

		std::shared_ptr<GameObject> skill_tooltip_base2 = object::Instantiate<GameObject>(
			Vector3(0.3465f, 0.3f, -0.01f),
			Vector3::Zero,
			Vector3(0.295f, 0.32f, 1.0f),
			ELayerType::UI
			);
		{
			skill_tooltip_base2->SetName(L"SkillTooltipBase2");
			skill_tooltip_base2->ismove = false;
			std::shared_ptr<MeshRenderer> mr = skill_tooltip_base2->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"SkillTooltipBaseMaterial02");
			mr->material->texture = tooltip_npk->GetTexture(L"newskillshop.img", 71);
			//mr->material->render_mode = graphics::ERenderMode::Transparent;
			std::shared_ptr<Transform> tf = skill_tooltip_base2->GetComponent<Transform>();
			tf->parent = skill_tooltip_parrent;
		}

		std::shared_ptr<GameObject> skill_tooltip_icon1 = object::Instantiate<GameObject>(
			Vector3(-0.43f, 0.45f, -0.01f),
			Vector3::Zero,
			Vector3(0.12f, 0.045f, 1.0f),
			ELayerType::UI
			);
		{
			skill_tooltip_icon1->SetName(L"SkillTooltipIcon1");
			skill_tooltip_icon1->ismove = false;
			std::shared_ptr<MeshRenderer> mr = skill_tooltip_icon1->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"SkillTooltipIconMaterial01");
			mr->material->texture = tooltip_npk->GetTexture(L"newskillshop.img", 1);
			mr->material->render_mode = graphics::ERenderMode::Transparent;
			std::shared_ptr<Transform> tf = skill_tooltip_icon1->GetComponent<Transform>();
			tf->parent = skill_tooltip_parrent;
		}
		std::shared_ptr<GameObject> skill_tooltip_icon2 = object::Instantiate<GameObject>(
			Vector3(-0.31f, 0.45f, -0.01f),
			Vector3::Zero,
			Vector3(0.12f, 0.045f, 1.0f),
			ELayerType::UI
			);
		{
			skill_tooltip_icon2->SetName(L"SkillTooltipIcon2");
			skill_tooltip_icon2->ismove = false;
			std::shared_ptr<MeshRenderer> mr = skill_tooltip_icon2->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"SkillTooltipIconMaterial02");
			mr->material->texture = tooltip_npk->GetTexture(L"newskillshop.img", 5);
			mr->material->render_mode = graphics::ERenderMode::Transparent;
			std::shared_ptr<Transform> tf = skill_tooltip_icon2->GetComponent<Transform>();
			tf->parent = skill_tooltip_parrent;
		}
		std::shared_ptr<GameObject> skill_tooltip_icon3 = object::Instantiate<GameObject>(
			Vector3(-0.365f, 0.39f, -0.01f),
			Vector3::Zero,
			Vector3(0.23f, 0.04f, 1.0f),
			ELayerType::UI
			);
		{
			skill_tooltip_icon3->SetName(L"SkillTooltipIcon3");
			skill_tooltip_icon3->ismove = false;
			std::shared_ptr<MeshRenderer> mr = skill_tooltip_icon3->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"SkillTooltipIconMaterial03");
			mr->material->texture = tooltip_npk->GetTexture(L"newskillshop.img", 9);
			mr->material->render_mode = graphics::ERenderMode::Transparent;
			std::shared_ptr<Transform> tf = skill_tooltip_icon3->GetComponent<Transform>();
			tf->parent = skill_tooltip_parrent;
		}
		std::shared_ptr<GameObject> skill_tooltip_icon4 = object::Instantiate<GameObject>(
			Vector3(-0.13f, 0.39f, -0.01f),
			Vector3::Zero,
			Vector3(0.23f, 0.04f, 1.0f),
			ELayerType::UI
			);
		{
			skill_tooltip_icon4->SetName(L"SkillTooltipIcon4");
			skill_tooltip_icon4->ismove = false;
			std::shared_ptr<MeshRenderer> mr = skill_tooltip_icon4->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"SkillTooltipIconMaterial04");
			mr->material->texture = tooltip_npk->GetTexture(L"newskillshop.img",13);
			mr->material->render_mode = graphics::ERenderMode::Transparent;
			std::shared_ptr<Transform> tf = skill_tooltip_icon4->GetComponent<Transform>();
			tf->parent = skill_tooltip_parrent;
		}

		//초기화 버튼 캡처 편집 npk 만들기
		/*std::shared_ptr<GameObject> skill_tooltip_icon5 = object::Instantiate<GameObject>(
			Vector3(-0.13f, 0.39f, -0.01f),
			Vector3::Zero,
			Vector3(0.23f, 0.04f, 1.0f),
			ELayerType::UI
			);
		{
			skill_tooltip_icon5->SetName(L"SkillTooltipIcon5");
			skill_tooltip_icon5->ismove = false;
			std::shared_ptr<MeshRenderer> mr = skill_tooltip_icon5->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"SkillTooltipIconMaterial04");
			mr->material->texture = tooltip_npk->GetTexture(L"newskillshop.img", 13);
			mr->material->render_mode = graphics::ERenderMode::Transparent;
			std::shared_ptr<Transform> tf = skill_tooltip_icon5->GetComponent<Transform>();
			tf->parent = skill_tooltip_parrent;
		}*/
		//자동찍기 버튼 캡처 편집 npk
	/*	std::shared_ptr<GameObject> skill_tooltip_icon5 = object::Instantiate<GameObject>(
			Vector3(-0.13f, 0.39f, -0.01f),
			Vector3::Zero,
			Vector3(0.23f, 0.04f, 1.0f),
			ELayerType::UI
			);
		{
			skill_tooltip_icon5->SetName(L"SkillTooltipIcon5");
			skill_tooltip_icon5->ismove = false;
			std::shared_ptr<MeshRenderer> mr = skill_tooltip_icon5->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"SkillTooltipIconMaterial04");
			mr->material->texture = tooltip_npk->GetTexture(L"newskillshop.img", 13);
			mr->material->render_mode = graphics::ERenderMode::Transparent;
			std::shared_ptr<Transform> tf = skill_tooltip_icon5->GetComponent<Transform>();
			tf->parent = skill_tooltip_parrent;
		}*/

		std::shared_ptr<GameObject> skill_tooltip_skill1 = object::Instantiate<GameObject>(
			Vector3(-0.13f, 0.2f, -0.01f),
			Vector3::Zero,
			Vector3(0.05f, 0.08f, 1.0f),
			ELayerType::UI
			);
		{
			skill_tooltip_skill1->SetName(L"SkillTooltipSkill1");
			skill_tooltip_skill1->ismove = false;
			std::shared_ptr<MeshRenderer> mr = skill_tooltip_skill1->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"SkillTooltipSkillMaterial01");
			mr->material->texture = tooltip_npk->GetTexture(L"newskillshop.img", 34);
			mr->material->render_mode = graphics::ERenderMode::Transparent;
			std::shared_ptr<Transform> tf = skill_tooltip_skill1->GetComponent<Transform>();
			tf->parent = skill_tooltip_parrent;
		}

		std::shared_ptr<GameObject> skill_tooltip_skill2 = object::Instantiate<GameObject>(
			Vector3(-0.13f, 0.05f, -0.01f),
			Vector3::Zero,
			Vector3(0.05f, 0.08f, 1.0f),
			ELayerType::UI
			);
		{
			skill_tooltip_skill2->SetName(L"SkillTooltipSkill2");
			skill_tooltip_skill2->ismove = false;
			std::shared_ptr<MeshRenderer> mr = skill_tooltip_skill2->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"SkillTooltipSkillMaterial01");
			mr->material->texture = tooltip_npk->GetTexture(L"newskillshop.img", 34);
			mr->material->render_mode = graphics::ERenderMode::Transparent;
			std::shared_ptr<Transform> tf = skill_tooltip_skill2->GetComponent<Transform>();
			tf->parent = skill_tooltip_parrent;
		}
	
		
#pragma endregion

#pragma region obj
		std::shared_ptr<GameObject> SeriaNPC = object::Instantiate<GameObject>(
			Vector3(0.2f, 0.07f, 0.98f),
			Vector3::Zero,
			Vector3(0.4f, 0.875f, 1.0f),
			ELayerType::BackObject);
		{
			SeriaNPC->SetName(L"SeriaNPC");
			SeriaNPC->ismove = false;
			std::shared_ptr<MeshRenderer> mr = SeriaNPC->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"SeriaTextureMaterial01");
			{
				std::shared_ptr<Texture> texture = npc_npk->GetTexture(L"seria_event_2012summer.img", 0);
				mr->material->texture = texture;
			}
		}
		std::shared_ptr<GameObject> Player = object::Instantiate<GameObject>(
			Vector3(0.0f, -1.0f, 0.1f),
			Vector3::Zero,
			Vector3(0.4f, 0.75f, 1.0f),
			ELayerType::Player);
		{
			Player->SetName(L"Player");
			std::shared_ptr<MeshRenderer> mr = Player->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"PlayerTextureMaterial01");
			{
				std::shared_ptr<Texture> texture = mbskin_npk->GetTexture(L"mg_body80500.img", 10);
				mr->material->texture = texture;
			}
		}
		std::shared_ptr<GameObject> GoldBox = object::Instantiate<GameObject>(
			Vector3(-1.3f, -0.45f, 0.98f),
			Vector3::Zero,
			Vector3(0.75f, 0.75f, 1.0f),
			ELayerType::BackObject);
		{
			GoldBox->SetName(L"GoldBox");
			GoldBox->ismove = false;
			std::shared_ptr<MeshRenderer> mr = GoldBox->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"GoldBoxMaterial01");
			{
				std::shared_ptr<Texture> texture = npc_npk->GetTexture(L"storagebrilliantdiamond.img", 0);
				mr->material->texture = texture;
			}
		}
		std::shared_ptr<GameObject> PremiumCoinShop = object::Instantiate<GameObject>(
			Vector3(1.2f, 0.0f, 0.98f),
			Vector3::Zero,
			Vector3(0.4f, 0.2f, 1.0f),
			ELayerType::BackObject);
		{
			PremiumCoinShop->SetName(L"PremiumCoinShop");
			PremiumCoinShop->ismove = false;
			std::shared_ptr<MeshRenderer> mr = PremiumCoinShop->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"PremiumCoinMaterial");
			{
				std::shared_ptr<Texture> texture = npc_npk->GetTexture(L"npc_coin.img", 0);
				mr->material->texture = texture;
			}
		}
		std::shared_ptr<GameObject> EnchantBook = object::Instantiate<GameObject>(
			Vector3(0.7f, 0.6f, 0.98f),
			Vector3::Zero,
			Vector3(0.35f, 0.45f, 1.0f),
			ELayerType::BackObject);
		{
			EnchantBook->SetName(L"EnchantBook");
			EnchantBook->ismove = false;
			std::shared_ptr<MeshRenderer> mr = EnchantBook->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"EnchantBookMaterial");
			{
				std::shared_ptr<Texture> texture = npc_npk->GetTexture(L"enchant_book_normal.img", 0);
				mr->material->texture = texture;
			}
		}
		std::shared_ptr<GameObject> EnchantBookEft = object::Instantiate<GameObject>(
			Vector3(0.73f, 0.66f, 0.98f),
			Vector3::Zero,
			Vector3(0.65f, 0.7f, 1.0f),
			ELayerType::BackObject);
		{
			EnchantBookEft->SetName(L"EnchantBookEft");
			EnchantBookEft->ismove = false;
			std::shared_ptr<MeshRenderer> mr = EnchantBookEft->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"EnchantBookEftMaterial");
			{
				std::shared_ptr<Texture> texture = npc_npk->GetTexture(L"enchant_book_front_dodge.img", 0);
				mr->material->texture = texture;
			}
		}

		std::shared_ptr<GameObject> PostBox = object::Instantiate<GameObject>(
			Vector3(2.45f, -0.40f, 0.98f),
			Vector3::Zero,
			Vector3(0.7f, 0.85f, 1.0f),
			ELayerType::BackObject);
		{
			PostBox->SetName(L"PostBox");
			PostBox->ismove = false;
			std::shared_ptr<MeshRenderer> mr = PostBox->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"PostBoxMaterial");
			{
				std::shared_ptr<Texture> texture = npc_npk->GetTexture(L"postbox.img", 0);
				mr->material->texture = texture;
			}
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
}

void roka::SeriaGateScene::Loading()
{
}
