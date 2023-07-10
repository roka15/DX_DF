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
		std::shared_ptr<NPK> seria_npk = Resources::Find<NPK>(L"seria_npc");
		if (seria_npk == nullptr)
			seria_npk = Resources::Load<NPK>(L"seria_npc", L"..\\Resources\\npk\\npc_seria.npk");

		std::shared_ptr<NPK> hud_npk = Resources::Find<NPK>(L"hud_ui");
		if (hud_npk == nullptr)
			hud_npk = Resources::Load<NPK>(L"hud_ui", L"..\\Resources\\npk\\HudUI.npk");

		std::shared_ptr<NPK> mbskin_npk = Resources::Find<NPK>(L"mage_base_skin");
		if (mbskin_npk == nullptr)
			mbskin_npk = Resources::Load<NPK>(L"mage_base_skin", L"..\\Resources\\npk\\baseskin.npk");

#pragma region base bg
			GameObject* bg = object::Instantiate<GameObject>(
				Vector3(0.15f, 0.0f, 0.98f),
				Vector3::Zero,
				Vector3(8.5f, 4.4f, 1.0f),
				ELayerType::BackObject);
			{
				bg->SetName(L"BackGround");
				bg->ismove = false;
				MeshRenderer* mr = bg->AddComponent<MeshRenderer>();
				mr->mesh = Resources::Find<Mesh>(L"RectMesh");
				mr->material = Resources::Find<Material>(L"BGMaterial");

				{
					std::shared_ptr<Texture> texture = npk->GetTexture(L"bg", 0);
					mr->material->texture = texture;
				}
			}
#pragma endregion

#pragma region front tree
		GameObject* frontTree = object::Instantiate<GameObject>(
			Vector3(-2.6f, 0.0f, 0.1f),
			Vector3::Zero,
			Vector3(3.0f, 4.4f, 1.0f),
			ELayerType::FrontObject);
		{
			frontTree->SetName(L"FrontTree");
			frontTree->ismove = false;
			MeshRenderer* mr = frontTree->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"FrontObjMaterial01");
			{
				std::shared_ptr<Texture>texture = npk->GetTexture(L"border_tree", 0);
				mr->material->texture = texture;
			}
		}
		GameObject* frontTree2 = object::Instantiate<GameObject>(
			Vector3(3.4f, 0.0f, 0.1f),
			Vector3::Zero,
			Vector3(2.0f, 4.4f, 1.0f),
			ELayerType::FrontObject);
		{
			frontTree2->SetName(L"FrontTree2");
			frontTree2->ismove = false;
			MeshRenderer* mr = frontTree2->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"FrontObjMaterial02");
			{
				std::shared_ptr<Texture>texture = npk->GetTexture(L"border_tree", 1);
				mr->material->texture = texture;
			}
		}

#pragma endregion

#pragma region flower bg

		GameObject* Flower01 = object::Instantiate<GameObject>(
			Vector3(-2.0f, 1.8f, 0.98f),
			Vector3::Zero,
			Vector3(0.15f, 0.15f, 1.0f),
			ELayerType::BackObject
			);
		{
			Flower01->SetName(L"Flower01");
			Flower01->ismove = false;
			MeshRenderer* mr = Flower01->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"FlowerMaterial01");
			{
				std::shared_ptr<Texture>texture = npk->GetTexture(L"flower_1", 0);
				mr->material->texture = texture;
			}
		}

		GameObject* Flower02 = object::Instantiate<GameObject>(
			Vector3(-3.6f, 0.7f, 0.98f),
			Vector3::Zero,
			Vector3(0.15f, 0.15f, 1.0f),
			ELayerType::BackObject
			);
		{
			Flower02->SetName(L"Flower02");
			Flower02->ismove = false;
			MeshRenderer* mr = Flower02->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"FlowerMaterial01");
		}
		GameObject* Flower03 = object::Instantiate<GameObject>(
			Vector3(2.0f, 2.0f, 0.98f),
			Vector3(Vector3(0.0f, 0.0f, Deg2Rad(180))),
			Vector3(0.15f, 0.15f, 1.0f),
			ELayerType::BackObject
			);
		{
			Flower03->SetName(L"Flower03");
			Flower03->ismove = false;
			MeshRenderer* mr = Flower03->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"FlowerMaterial01");
		}

		GameObject* Flower04 = object::Instantiate<GameObject>(
			Vector3(1.5f, 2.0f, 0.98f),
			Vector3(Vector3(0.0f, 0.0f, Deg2Rad(180))),
			Vector3(0.15f, 0.15f, 1.0f),
			ELayerType::BackObject
			);
		{
			Flower04->SetName(L"Flower04");
			Flower04->ismove = false;
			MeshRenderer* mr = Flower04->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"FlowerMaterial02");
			{
				std::shared_ptr<Texture>texture = npk->GetTexture(L"flower_2", 0);
				mr->material->texture = texture;
			}
		}

		GameObject* Flower05 = object::Instantiate<GameObject>(
			Vector3(-3.3f, 2.0f, 0.98f),
			Vector3::Zero,
			Vector3(0.15f, 0.15f, 1.0f),
			ELayerType::BackObject
			);
		{
			Flower05->SetName(L"Flower05");
			Flower05->ismove = false;
			MeshRenderer* mr = Flower05->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"FlowerMaterial02");
		}
#pragma endregion	

#pragma region leaf bg
		GameObject* Leaf01 = object::Instantiate<GameObject>(
			Vector3(-2.2f, 1.8f, 0.98f),
			Vector3::Zero,
			Vector3(0.15f, 0.25f, 1.0f),
			ELayerType::BackObject
			);
		{
			Leaf01->SetName(L"Leaf01");
			Leaf01->ismove = false;
			MeshRenderer* mr = Leaf01->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"LeafMaterial01");
			{
				std::shared_ptr<Texture>texture = npk->GetTexture(L"leaf_1", 0);
				mr->material->texture = texture;
			}
		}
		GameObject* Leaf02 = object::Instantiate<GameObject>(
			Vector3(-2.6f, 2.0f, 0.98f),
			Vector3::Zero,
			Vector3(0.15f, 0.25f, 1.0f),
			ELayerType::BackObject
			);
		{
			Leaf02->SetName(L"Leaf02");
			Leaf02->ismove = false;
			MeshRenderer* mr = Leaf02->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"LeafMaterial03");
			{
				std::shared_ptr<Texture>texture = npk->GetTexture(L"leaf_3", 0);
				mr->material->texture = texture;
			}
		}
		GameObject* Leaf03 = object::Instantiate<GameObject>(
			Vector3(-3.5f, 1.9f, 0.98f),
			Vector3::Zero,
			Vector3(0.15f, 0.25f, 1.0f),
			ELayerType::BackObject
			);
		{
			Leaf03->SetName(L"Leaf03");
			Leaf03->ismove = false;
			MeshRenderer* mr = Leaf03->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"LeafMaterial03");
		}

		GameObject* Leaf04 = object::Instantiate<GameObject>(
			Vector3(2.5f, 1.8f, 0.98f),
			Vector3::Zero,
			Vector3(0.15f, 0.25f, 1.0f),
			ELayerType::BackObject
			);
		{
			Leaf04->SetName(L"Leaf04");
			Leaf04->ismove = false;
			MeshRenderer* mr = Leaf04->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"LeafMaterial02");
			{
				std::shared_ptr<Texture>texture = npk->GetTexture(L"leaf_2", 0);
				mr->material->texture = texture;
			}
		}

		GameObject* Leaf05 = object::Instantiate<GameObject>(
			Vector3(1.1f, 2.0f, 0.98f),
			Vector3::Zero,
			Vector3(0.15f, 0.25f, 1.0f),
			ELayerType::BackObject
			);
		{
			Leaf05->SetName(L"Leaf05");
			Leaf05->ismove = false;
			MeshRenderer* mr = Leaf05->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"LeafMaterial02");
		}

		GameObject* Leaf06 = object::Instantiate<GameObject>(
			Vector3(2.0f, 1.8f, 0.98f),
			Vector3::Zero,
			Vector3(0.15f, 0.25f, 1.0f),
			ELayerType::BackObject
			);
		{
			Leaf06->SetName(L"Leaf06");
			Leaf06->ismove = false;
			MeshRenderer* mr = Leaf06->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"LeafMaterial03");
		}

		GameObject* Leaf07 = object::Instantiate<GameObject>(
			Vector3(1.5f, 1.8f, 0.98f),
			Vector3::Zero,
			Vector3(0.15f, 0.25f, 1.0f),
			ELayerType::BackObject
			);
		{
			Leaf07->SetName(L"Leaf07");
			Leaf07->ismove = false;
			MeshRenderer* mr = Leaf07->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"LeafMaterial01");
		}
#pragma endregion

#pragma region gate
		GameObject* GateRight = object::Instantiate<GameObject>(
			Vector3(0.8f, -1.5f, 0.1f),
			Vector3::Zero,
			Vector3(1.0f, 1.25f, 1.0f),
			ELayerType::FrontObject);
		{
			GateRight->SetName(L"GateRight");
			GateRight->ismove = false;
			MeshRenderer* mr = GateRight->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"GateMaterial01");
			{
				std::shared_ptr<Texture>texture = npk->GetTexture(L"gate_new", 0);
				mr->material->texture = texture;
			}
		}
		GameObject* GateLeft = object::Instantiate<GameObject>(
			Vector3(-0.7f, -1.5f, 0.1f),
			Vector3::Zero,
			Vector3(1.0f, 1.25f, 1.0f),
			ELayerType::FrontObject);
		{
			GateLeft->SetName(L"GateLeft");
			GateLeft->ismove = false;
			MeshRenderer* mr = GateLeft->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"GateVInverseMaterial01");
			{
				std::shared_ptr<Texture>texture = npk->GetTexture(L"gate_new", 0);
				mr->material->texture = texture;
			}
		}
#pragma endregion

#pragma region hud
		GameObject* HudBase = object::Instantiate<GameObject>(
			Vector3(0.1f, -1.91f, 0.1f),
			Vector3::Zero,
			Vector3(2.85f, 0.5f, 1.0f),
			ELayerType::UI);
		{
			HudBase->SetName(L"HudBase");
			HudBase->ismove = false;
			MeshRenderer* mr = HudBase->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"HudBaseMaterial01");
			{
				std::shared_ptr<Texture> texture = hud_npk->GetTexture(L"hud.img", 0);
				mr->material->texture = texture;
			}
		}
		GameObject* HudBase2 = object::Instantiate<GameObject>(
			Vector3(-0.0f, -0.43f, -0.01f),
			Vector3::Zero,
			Vector3(1.1f, 0.25f, 1.0f),
			ELayerType::UI);
		{
			HudBase2->SetName(L"HudBase2");
			HudBase2->ismove = false;
			MeshRenderer* mr = HudBase2->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"HudBaseMaterial02");
			mr->material->render_mode = ERenderMode::Transparent;

			Transform* tf = HudBase2->GetComponent<Transform>();
			tf->parent = HudBase->GetComponent<Transform>();
			{
				std::shared_ptr<Texture> texture = hud_npk->GetTexture(L"hud.img", 201);
				mr->material->texture = texture;
			}
		}
		GameObject* ExpBar = object::Instantiate<GameObject>(
			Vector3(0.01f, -0.5f, -0.01f),
			Vector3::Zero,
			Vector3(0.8f, 0.07f, 1.0f),
			ELayerType::UI);
		{
			ExpBar->SetName(L"ExpBar");
			ExpBar->ismove = false;
			MeshRenderer* mr = ExpBar->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"ExpBarMaterial01");
			//mr->material->render_mode = ERenderMode::Transparent;

			Transform* tf = ExpBar->GetComponent<Transform>();
			tf->parent = HudBase->GetComponent<Transform>();
			{
				std::shared_ptr<Texture> texture = hud_npk->GetTexture(L"hud.img", 24);
				mr->material->texture = texture;
			}
		}

		GameObject* HPBase = object::Instantiate<GameObject>(
			Vector3(-0.4f, 0.0f, 0.0f),
			Vector3::Zero,
			Vector3(0.14f, 0.7f, 1.0f),
			ELayerType::UI);
		{
			HPBase->SetName(L"HPBase");
			HPBase->ismove = false;
			MeshRenderer* mr = HPBase->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"HPBaseMaterial01");

			Transform* tf = HPBase->GetComponent<Transform>();
			tf->parent = HudBase->GetComponent<Transform>();
			{
				std::shared_ptr<Texture> texture = hud_npk->GetTexture(L"hud.img", 1);
				mr->material->texture = texture;
			}
		}
		GameObject* MPBase = object::Instantiate<GameObject>(
			Vector3(0.39f, 0.0f, 0.0f),
			Vector3::Zero,
			Vector3(0.14f, 0.7f, 1.0f),
			ELayerType::UI);
		{
			MPBase->SetName(L"MPBase");
			MPBase->ismove = false;
			MeshRenderer* mr = MPBase->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"MPBaseMaterial01");

			Transform* tf = MPBase->GetComponent<Transform>();
			tf->parent = HudBase->GetComponent<Transform>();
			{
				std::shared_ptr<Texture> texture = hud_npk->GetTexture(L"hud.img", 2);
				mr->material->texture = texture;
			}
		}
		GameObject* HPFilter = object::Instantiate<GameObject>(
			Vector3(-0.395f, -0.01f, 0.0f),
			Vector3::Zero,
			Vector3(0.175f, 0.85f, 1.0f),
			ELayerType::UI);
		{
			HPFilter->SetName(L"HPFilter");
			HPFilter->ismove = false;
			MeshRenderer* mr = HPFilter->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"HPFilterMaterial01");
			mr->material->render_mode = ERenderMode::Transparent;
			Transform* tf = HPFilter->GetComponent<Transform>();
			tf->parent = HudBase->GetComponent<Transform>();
			{
				std::shared_ptr<Texture> texture = hud_npk->GetTexture(L"hud.img", 211);
				mr->material->texture = texture;
			}
		}
		GameObject* MPFilter = object::Instantiate<GameObject>(
			Vector3(0.385f, -0.01f, 0.0f),
			Vector3::Zero,
			Vector3(0.175f, 0.85f, 1.0f),
			ELayerType::UI);
		{
			MPFilter->SetName(L"MPFilter");
			MPFilter->ismove = false;
			MeshRenderer* mr = MPFilter->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"MPFilterMaterial01");
			mr->material->render_mode = ERenderMode::Transparent;
			Transform* tf = MPFilter->GetComponent<Transform>();
			tf->parent = HudBase->GetComponent<Transform>();
			{
				std::shared_ptr<Texture> texture = hud_npk->GetTexture(L"hud.img", 212);
				mr->material->texture = texture;
			}
		}
		GameObject* SkillQuickSlot01 = object::Instantiate<GameObject>(
			Vector3(-0.194f, 0.17f, 0.0f),
			Vector3::Zero,
			Vector3(0.08f, 0.45f, 1.0f),
			ELayerType::UI);
		{
			SkillQuickSlot01->SetName(L"SkillQuickSlot01");
			SkillQuickSlot01->ismove = false;
			MeshRenderer* mr = SkillQuickSlot01->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"SkillQuickSlotMaterial01");

			Transform* tf = SkillQuickSlot01->GetComponent<Transform>();
			tf->parent = HudBase->GetComponent<Transform>();
			{
				std::shared_ptr<Texture> texture = hud_npk->GetTexture(L"hud.img", 196);
				mr->material->texture = texture;
			}
		}
		GameObject* SkillQuickSlot02 = object::Instantiate<GameObject>(
			Vector3(-0.116f, 0.17f, 0.0f),
			Vector3::Zero,
			Vector3(0.08f, 0.45f, 1.0f),
			ELayerType::UI);
		{
			SkillQuickSlot02->SetName(L"SkillQuickSlot02");
			SkillQuickSlot02->ismove = false;
			MeshRenderer* mr = SkillQuickSlot02->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"SkillQuickSlotMaterial01");

			Transform* tf = SkillQuickSlot02->GetComponent<Transform>();
			tf->parent = HudBase->GetComponent<Transform>();
		}
		GameObject* SkillQuickSlot03 = object::Instantiate<GameObject>(
			Vector3(-0.038f, 0.17f, 0.0f),
			Vector3::Zero,
			Vector3(0.08f, 0.45f, 1.0f),
			ELayerType::UI);
		{
			SkillQuickSlot03->SetName(L"SkillQuickSlot03");
			SkillQuickSlot03->ismove = false;
			MeshRenderer* mr = SkillQuickSlot03->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"SkillQuickSlotMaterial01");

			Transform* tf = SkillQuickSlot03->GetComponent<Transform>();
			tf->parent = HudBase->GetComponent<Transform>();
		}
		GameObject* SkillQuickSlot04 = object::Instantiate<GameObject>(
			Vector3(0.04f, 0.17f, 0.0f),
			Vector3::Zero,
			Vector3(0.08f, 0.45f, 1.0f),
			ELayerType::UI);
		{
			SkillQuickSlot04->SetName(L"SkillQuickSlot04");
			SkillQuickSlot04->ismove = false;
			MeshRenderer* mr = SkillQuickSlot04->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"SkillQuickSlotMaterial01");

			Transform* tf = SkillQuickSlot04->GetComponent<Transform>();
			tf->parent = HudBase->GetComponent<Transform>();
		}
		GameObject* SkillQuickSlot05 = object::Instantiate<GameObject>(
			Vector3(0.118f, 0.17f, 0.0f),
			Vector3::Zero,
			Vector3(0.08f, 0.45f, 1.0f),
			ELayerType::UI);
		{
			SkillQuickSlot05->SetName(L"SkillQuickSlot05");
			SkillQuickSlot05->ismove = false;
			MeshRenderer* mr = SkillQuickSlot05->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"SkillQuickSlotMaterial01");

			Transform* tf = SkillQuickSlot05->GetComponent<Transform>();
			tf->parent = HudBase->GetComponent<Transform>();
		}
		GameObject* SkillQuickSlot06 = object::Instantiate<GameObject>(
			Vector3(0.196f, 0.17f, 0.0f),
			Vector3::Zero,
			Vector3(0.08f, 0.45f, 1.0f),
			ELayerType::UI);
		{
			SkillQuickSlot06->SetName(L"SkillQuickSlot06");
			SkillQuickSlot06->ismove = false;
			MeshRenderer* mr = SkillQuickSlot06->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"SkillQuickSlotMaterial01");

			Transform* tf = SkillQuickSlot06->GetComponent<Transform>();
			tf->parent = HudBase->GetComponent<Transform>();
		}
		GameObject* SkillQuickSlot07 = object::Instantiate<GameObject>(
			Vector3(0.274f, 0.17f, 0.0f),
			Vector3::Zero,
			Vector3(0.08f, 0.45f, 1.0f),
			ELayerType::UI);
		{
			SkillQuickSlot07->SetName(L"SkillQuickSlot07");
			SkillQuickSlot07->ismove = false;
			MeshRenderer* mr = SkillQuickSlot07->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"SkillQuickSlotMaterial01");

			Transform* tf = SkillQuickSlot07->GetComponent<Transform>();
			tf->parent = HudBase->GetComponent<Transform>();
		}
		GameObject* SkillQuickSlot08 = object::Instantiate<GameObject>(
			Vector3(-0.194f, -0.26f, 0.0f),
			Vector3::Zero,
			Vector3(0.08f, 0.45f, 1.0f),
			ELayerType::UI);
		{
			SkillQuickSlot08->SetName(L"SkillQuickSlot08");
			SkillQuickSlot08->ismove = false;
			MeshRenderer* mr = SkillQuickSlot08->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"SkillQuickSlotMaterial01");

			Transform* tf = SkillQuickSlot08->GetComponent<Transform>();
			tf->parent = HudBase->GetComponent<Transform>();
		}
		GameObject* SkillQuickSlot09 = object::Instantiate<GameObject>(
			Vector3(-0.116f, -0.26f, 0.0f),
			Vector3::Zero,
			Vector3(0.08f, 0.45f, 1.0f),
			ELayerType::UI);
		{
			SkillQuickSlot09->SetName(L"SkillQuickSlot09");
			SkillQuickSlot09->ismove = false;
			MeshRenderer* mr = SkillQuickSlot09->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"SkillQuickSlotMaterial01");

			Transform* tf = SkillQuickSlot09->GetComponent<Transform>();
			tf->parent = HudBase->GetComponent<Transform>();
		}
		GameObject* SkillQuickSlot10 = object::Instantiate<GameObject>(
			Vector3(-0.038f, -0.26f, 0.0f),
			Vector3::Zero,
			Vector3(0.08f, 0.45f, 1.0f),
			ELayerType::UI);
		{
			SkillQuickSlot10->SetName(L"SkillQuickSlot10");
			SkillQuickSlot10->ismove = false;
			MeshRenderer* mr = SkillQuickSlot10->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"SkillQuickSlotMaterial01");

			Transform* tf = SkillQuickSlot10->GetComponent<Transform>();
			tf->parent = HudBase->GetComponent<Transform>();
		}
		GameObject* SkillQuickSlot11 = object::Instantiate<GameObject>(
			Vector3(0.04f, -0.26f, 0.0f),
			Vector3::Zero,
			Vector3(0.08f, 0.45f, 1.0f),
			ELayerType::UI);
		{
			SkillQuickSlot11->SetName(L"SkillQuickSlot11");
			SkillQuickSlot11->ismove = false;
			MeshRenderer* mr = SkillQuickSlot11->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"SkillQuickSlotMaterial01");

			Transform* tf = SkillQuickSlot11->GetComponent<Transform>();
			tf->parent = HudBase->GetComponent<Transform>();
		}
		GameObject* SkillQuickSlot12 = object::Instantiate<GameObject>(
			Vector3(0.118f, -0.26f, 0.0f),
			Vector3::Zero,
			Vector3(0.08f, 0.45f, 1.0f),
			ELayerType::UI);
		{
			SkillQuickSlot12->SetName(L"SkillQuickSlot12");
			SkillQuickSlot12->ismove = false;
			MeshRenderer* mr = SkillQuickSlot12->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"SkillQuickSlotMaterial01");

			Transform* tf = SkillQuickSlot12->GetComponent<Transform>();
			tf->parent = HudBase->GetComponent<Transform>();
		}
		GameObject* SkillQuickSlot13 = object::Instantiate<GameObject>(
			Vector3(0.196f, -0.26f, 0.0f),
			Vector3::Zero,
			Vector3(0.08f, 0.45f, 1.0f),
			ELayerType::UI);
		{
			SkillQuickSlot13->SetName(L"SkillQuickSlot13");
			SkillQuickSlot13->ismove = false;
			MeshRenderer* mr = SkillQuickSlot13->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"SkillQuickSlotMaterial01");

			Transform* tf = SkillQuickSlot13->GetComponent<Transform>();
			tf->parent = HudBase->GetComponent<Transform>();
		}
		GameObject* SkillQuickSlot14 = object::Instantiate<GameObject>(
			Vector3(0.274f, -0.26f, 0.0f),
			Vector3::Zero,
			Vector3(0.08f, 0.45f, 1.0f),
			ELayerType::UI);
		{
			SkillQuickSlot14->SetName(L"SkillQuickSlot14");
			SkillQuickSlot14->ismove = false;
			MeshRenderer* mr = SkillQuickSlot14->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"SkillQuickSlotMaterial01");

			Transform* tf = SkillQuickSlot14->GetComponent<Transform>();
			tf->parent = HudBase->GetComponent<Transform>();
		}
		GameObject* MoreSkillBtn = object::Instantiate<GameObject>(
			Vector3(-0.26f, 0.16f, 0.0f),
			Vector3::Zero,
			Vector3(0.055f, 0.45f, 1.0f),
			ELayerType::UI);
		{
			MoreSkillBtn->SetName(L"MoreSkillBtn");
			MoreSkillBtn->ismove = false;
			MeshRenderer* mr = MoreSkillBtn->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"MoreSkillBtnMaterial01");

			Transform* tf = MoreSkillBtn->GetComponent<Transform>();;
			tf->parent = HudBase->GetComponent<Transform>();
			{
				std::shared_ptr<Texture> texture = hud_npk->GetTexture(L"hud.img", 192);
				mr->material->texture = texture;
			}
		}
		GameObject* SkillChangeBtn = object::Instantiate<GameObject>(
			Vector3(-0.26f, -0.25f, 0.0f),
			Vector3::Zero,
			Vector3(0.055f, 0.45f, 1.0f),
			ELayerType::UI);
		{
			SkillChangeBtn->SetName(L"SkillChangeBtn");
			SkillChangeBtn->ismove = false;
			MeshRenderer* mr = SkillChangeBtn->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"SkillChangeBtnMaterial01");

			Transform* tf = SkillChangeBtn->GetComponent<Transform>();
			tf->parent = HudBase->GetComponent<Transform>();
			{
				std::shared_ptr<Texture> texture = hud_npk->GetTexture(L"hud.img", 53);
				mr->material->texture = texture;
			}
		}

#pragma endregion

#pragma region obj
		GameObject* SeriaNPC = object::Instantiate<GameObject>(
			Vector3(0.2f, 0.07f, 0.1f),
			Vector3::Zero,
			Vector3(0.4f, 0.875f, 1.0f),
			ELayerType::BackObject);
		{
			SeriaNPC->SetName(L"SeriaNPC");
			SeriaNPC->ismove = false;
			MeshRenderer* mr = SeriaNPC->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"SeriaTextureMaterial01");
			{
				std::shared_ptr<Texture> texture = seria_npk->GetTexture(L"seria_event_2012summer.img", 0);
				mr->material->texture = texture;
			}
		}
		GameObject* Player = object::Instantiate<GameObject>(
			Vector3(0.0f, -1.0f, 0.1f),
			Vector3::Zero,
			Vector3(0.4f, 0.75f, 1.0f),
			ELayerType::Player);
		{
			Player->SetName(L"Player");
			MeshRenderer* mr = Player->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"PlayerTextureMaterial01");
			{
				std::shared_ptr<Texture> texture = mbskin_npk->GetTexture(L"mg_body80500.img", 10);
				mr->material->texture = texture;
			}
		}
		GameObject* GoldBox = object::Instantiate<GameObject>(
			Vector3(-1.3f, -0.45f, 0.1f),
			Vector3::Zero,
			Vector3(0.75f, 0.75f, 1.0f),
			ELayerType::BackObject);
		{
			GoldBox->SetName(L"GoldBox");
			GoldBox->ismove = false;
			MeshRenderer* mr = GoldBox->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"GoldBoxMaterial01");
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
	GameObject* camera = object::Instantiate<GameObject>(
		Vector3(0.0f, 0.0f, -10.0f),
		ELayerType::Player);
	{
		camera->AddComponent<CameraScript>();
		Camera* cameraComp = camera->AddComponent<Camera>();
		cameraComp->TurnLayerMask(ELayerType::UI, false);
	}

	GameObject* UIcamera = object::Instantiate<GameObject>(
		Vector3(0.0f, 0.0f, -10.0f),
		ELayerType::UI);
	{
		Camera* cameraComp = UIcamera->AddComponent<Camera>();
		cameraComp->DisableLayerMasks();
		cameraComp->TurnLayerMask(ELayerType::UI, true);
	}

	{
		GameObject* grid = object::Instantiate<GameObject>(ELayerType::Grid);
		grid->SetName(L"Grid");
		MeshRenderer* mr = grid->AddComponent<MeshRenderer>();
		mr->mesh = Resources::Find<Mesh>(L"RectMesh");
		mr->material = Resources::Find<Material>(L"GridMaterial");
		GridScript* script = grid->AddComponent<GridScript>();
		script->camera = UIcamera->GetComponent<Camera>();
	}
}

void roka::SeriaGateScene::Loading()
{
}
