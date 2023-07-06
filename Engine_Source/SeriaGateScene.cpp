#include "SeriaGateScene.h"
#include "Resources.h"
#include "MeshRenderer.h"
#include "Transform.h"
#include "Camera.h"
#include "CameraScript.h"

#include "Mesh.h"
#include "Material.h"

#include "NPK.h"
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
		GameObject* bg = new GameObject();
		{
			bg->SetName(L"BackGround");
			bg->ismove = false;
			AddGameObject(ELayerType::BackObject, bg);
			MeshRenderer* mr = bg->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"BGMaterial");

			Transform* tf = bg->GetComponent<Transform>();
			tf->position = Vector3(0.15f, 0.0f, 0.98f);
			tf->scale = Vector3(17.0f, 8.8f, 1.0f);
			{
				std::shared_ptr<Texture> texture = npk->GetTexture(L"bg", 0);
				mr->material->texture = texture;
			}
		}
#pragma endregion

#pragma region front tree
		GameObject* frontTree = new GameObject();
		{
			frontTree->SetName(L"FrontTree");
			frontTree->ismove = false;
			AddGameObject(ELayerType::FrontObject, frontTree);
			MeshRenderer* mr = frontTree->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"FrontObjMaterial01");
			

			Transform* tf = frontTree->GetComponent<Transform>();
			tf->position = Vector3(-2.6f, 0.0f, 0.1f);
			tf->scale = Vector3(6.0f, 8.8f, 1.0f);
			{
				std::shared_ptr<Texture>texture = npk->GetTexture(L"border_tree", 0);
				mr->material->texture = texture;
			}
		}
		GameObject* frontTree2 = new GameObject();
		{
			frontTree2->SetName(L"FrontTree2");
			frontTree2->ismove = false;
			AddGameObject(ELayerType::FrontObject, frontTree2);
			MeshRenderer* mr = frontTree2->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"FrontObjMaterial02");


			Transform* tf = frontTree2->GetComponent<Transform>();
			tf->position = Vector3(3.4f, 0.0f, 0.1f);
			tf->scale = Vector3(4.0f, 8.8f, 1.0f);
			{
				std::shared_ptr<Texture>texture = npk->GetTexture(L"border_tree", 1);
				mr->material->texture = texture;
			}
		}

#pragma endregion

#pragma region flower bg
		
		GameObject* Flower01 = new GameObject();
		{
			Flower01->SetName(L"Flower01");
			Flower01->ismove = false;
			AddGameObject(ELayerType::BackObject, Flower01);
			MeshRenderer* mr = Flower01->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"FlowerMaterial01");


			Transform* tf = Flower01->GetComponent<Transform>();
			tf->position = Vector3(-2.0f, 1.8f, 0.98f);
			tf->scale = Vector3(0.3f, 0.3f, 1.0f);
			{
				std::shared_ptr<Texture>texture = npk->GetTexture(L"flower_1", 0);
				mr->material->texture = texture;
			}
		}

		GameObject* Flower02 = new GameObject();
		{
			Flower02->SetName(L"Flower02");
			Flower02->ismove = false;
			AddGameObject(ELayerType::BackObject, Flower02);
			MeshRenderer* mr = Flower02->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"FlowerMaterial01");


			Transform* tf = Flower02->GetComponent<Transform>();
			tf->position = Vector3(-3.6f, 0.7f, 0.98f);
			tf->scale = Vector3(0.3f, 0.3f, 1.0f);
		}
		GameObject* Flower03 = new GameObject();
		{
			Flower03->SetName(L"Flower03");
			Flower03->ismove = false;
			AddGameObject(ELayerType::BackObject, Flower03);
			MeshRenderer* mr = Flower03->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"FlowerMaterial01");


			Transform* tf = Flower03->GetComponent<Transform>();
			tf->position = Vector3(2.0f, 2.0f, 0.98f);
			tf->scale = Vector3(0.3f, 0.3f, 1.0f);
			tf->rotation =Vector3(Vector3(0.0f, 0.0f, Deg2Rad(180)));
		}

		GameObject* Flower04 = new GameObject();
		{
			Flower04->SetName(L"Flower04");
			Flower04->ismove = false;
			AddGameObject(ELayerType::BackObject, Flower04);
			MeshRenderer* mr = Flower04->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"FlowerMaterial02");


			Transform* tf = Flower04->GetComponent<Transform>();
			tf->position = Vector3(1.5f, 2.0f, 0.98f);
			tf->scale = Vector3(0.3f, 0.3f, 1.0f);
			tf->rotation = Vector3(Vector3(0.0f, 0.0f, Deg2Rad(180)));
			{
				std::shared_ptr<Texture>texture = npk->GetTexture(L"flower_2", 0);
				mr->material->texture = texture;
			}
		}

		GameObject* Flower05 = new GameObject();
		{
			Flower05->SetName(L"Flower05");
			Flower05->ismove = false;
			AddGameObject(ELayerType::BackObject, Flower05);
			MeshRenderer* mr = Flower05->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"FlowerMaterial02");


			Transform* tf = Flower05->GetComponent<Transform>();
			tf->position = Vector3(-3.3f, 2.0f, 0.98f);
			tf->scale = Vector3(0.3f, 0.3f, 1.0f);
		}
#pragma endregion	

#pragma region leaf bg
		GameObject* Leaf01 = new GameObject();
		{
			Leaf01->SetName(L"Leaf01");
			Leaf01->ismove = false;
			AddGameObject(ELayerType::BackObject, Leaf01);
			MeshRenderer* mr = Leaf01->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"LeafMaterial01");


			Transform* tf = Leaf01->GetComponent<Transform>();
			tf->position = Vector3(-2.2f, 1.8f, 0.98f);
			tf->scale = Vector3(0.3f, 0.5f, 1.0f);
			{
				std::shared_ptr<Texture>texture = npk->GetTexture(L"leaf_1", 0);
				mr->material->texture = texture;
			}
		}
		GameObject* Leaf02 = new GameObject();
		{
			Leaf02->SetName(L"Leaf02");
			Leaf02->ismove = false;
			AddGameObject(ELayerType::BackObject, Leaf02);
			MeshRenderer* mr = Leaf02->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"LeafMaterial03");


			Transform* tf = Leaf02->GetComponent<Transform>();
			tf->position = Vector3(-2.6f, 2.0f, 0.98f);
			tf->scale = Vector3(0.3f, 0.5f, 1.0f);
			{
				std::shared_ptr<Texture>texture = npk->GetTexture(L"leaf_3", 0);
				mr->material->texture = texture;
			}
		}
		GameObject* Leaf03 = new GameObject();
		{
			Leaf03->SetName(L"Leaf03");
			Leaf03->ismove = false;
			AddGameObject(ELayerType::BackObject, Leaf03);
			MeshRenderer* mr = Leaf03->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"LeafMaterial03");


			Transform* tf = Leaf03->GetComponent<Transform>();
			tf->position = Vector3(-3.5f, 1.9f, 0.98f);
			tf->scale = Vector3(0.3f, 0.5f, 1.0f);
		}

		GameObject* Leaf04 = new GameObject();
		{
			Leaf04->SetName(L"Leaf04");
			Leaf04->ismove = false;
			AddGameObject(ELayerType::BackObject, Leaf04);
			MeshRenderer* mr = Leaf04->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"LeafMaterial02");
			{
				std::shared_ptr<Texture>texture = npk->GetTexture(L"leaf_2", 0);
				mr->material->texture = texture;
			}

			Transform* tf = Leaf04->GetComponent<Transform>();
			tf->position = Vector3(2.5f, 1.8f, 0.98f);
			tf->scale = Vector3(0.3f, 0.5f, 1.0f);
		}

		GameObject* Leaf05 = new GameObject();
		{
			Leaf05->SetName(L"Leaf05");
			Leaf05->ismove = false;
			AddGameObject(ELayerType::BackObject, Leaf05);
			MeshRenderer* mr = Leaf05->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"LeafMaterial02");
			

			Transform* tf = Leaf05->GetComponent<Transform>();
			tf->position = Vector3(1.1f, 2.0f, 0.98f);
			tf->scale = Vector3(0.3f, 0.5f, 1.0f);
		}

		GameObject* Leaf06 = new GameObject();
		{
			Leaf06->SetName(L"Leaf06");
			Leaf06->ismove = false;
			AddGameObject(ELayerType::BackObject, Leaf06);
			MeshRenderer* mr = Leaf06->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"LeafMaterial03");


			Transform* tf = Leaf06->GetComponent<Transform>();
			tf->position = Vector3(2.0f, 1.8f, 0.98f);
			tf->scale = Vector3(0.3f, 0.5f, 1.0f);
		}

		GameObject* Leaf07 = new GameObject();
		{
			Leaf07->SetName(L"Leaf07");
			Leaf07->ismove = false;
			AddGameObject(ELayerType::BackObject, Leaf07);
			MeshRenderer* mr = Leaf07->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"LeafMaterial01");


			Transform* tf = Leaf07->GetComponent<Transform>();
			tf->position = Vector3(1.5f, 1.8f, 0.98f);
			tf->scale = Vector3(0.3f, 0.5f, 1.0f);
		}
#pragma endregion

#pragma region gate
		GameObject* GateRight = new GameObject();
		{
			GateRight->SetName(L"GateRight");
			GateRight->ismove = false;
			AddGameObject(ELayerType::FrontObject, GateRight);
			MeshRenderer* mr = GateRight->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"GateMaterial01");

			Transform* tf = GateRight->GetComponent<Transform>();
			tf->position = Vector3(0.8f, -1.5f, 0.1f);
			tf->scale = Vector3(2.0f, 2.5f, 1.0f);
			{
				std::shared_ptr<Texture>texture = npk->GetTexture(L"gate_new", 0);
				mr->material->texture = texture;
			}
		}
		GameObject* GateLeft = new GameObject();
		{
			GateLeft->SetName(L"GateLeft");
			GateLeft->ismove = false;
			AddGameObject(ELayerType::FrontObject, GateLeft);
			MeshRenderer* mr = GateLeft->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"GateVInverseMaterial01");
			
			Transform* tf = GateLeft->GetComponent<Transform>();
			tf->position = Vector3(-0.7f, -1.5f, 0.1f);
			tf->scale = Vector3(2.0f, 2.5f, 1.0f);
			{
				std::shared_ptr<Texture>texture = npk->GetTexture(L"gate_new", 0);
				mr->material->texture = texture;
			}
		}
#pragma endregion

#pragma region hud
		GameObject* HudBase = new GameObject();
		{
			HudBase->SetName(L"HudBase");
			HudBase->ismove = false;
			AddGameObject(ELayerType::UI, HudBase);
			MeshRenderer* mr = HudBase->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"HudBaseMaterial01");
			
			Transform* tf = HudBase->GetComponent<Transform>();
			tf->position = Vector3(0.1f, -1.91f, 0.1f);
			tf->scale = Vector3(5.7f, 1.0f, 1.0f);
			{
				std::shared_ptr<Texture> texture = hud_npk->GetTexture(L"hud.img", 0);
				mr->material->texture = texture;
			}
		}
		GameObject* HudBase2 = new GameObject();
		{
			HudBase2->SetName(L"HudBase2");
			HudBase2->ismove = false;
			AddGameObject(ELayerType::UI, HudBase2);
			MeshRenderer* mr = HudBase2->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"HudBaseMaterial02");
			mr->material->render_mode = ERenderMode::Transparent;

			Transform* tf = HudBase2->GetComponent<Transform>();
			tf->position = Vector3(-0.0f, -0.23f, -0.01f);
			tf->scale = Vector3(1.1f, 0.25f, 1.0f);
			tf->parent = HudBase->GetComponent<Transform>();
			{
				std::shared_ptr<Texture> texture = hud_npk->GetTexture(L"hud.img", 201);
				mr->material->texture = texture;
			}
		}
		GameObject* ExpBar = new GameObject();
		{
			ExpBar->SetName(L"ExpBar");
			ExpBar->ismove = false;
			AddGameObject(ELayerType::UI, ExpBar);
			MeshRenderer* mr = ExpBar->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"ExpBarMaterial01");
			//mr->material->render_mode = ERenderMode::Transparent;
			
			Transform* tf = ExpBar->GetComponent<Transform>();
			tf->position = Vector3(0.01f, -0.26f, -0.01f);
			tf->scale = Vector3(0.8f, 0.07f, 1.0f);
			tf->parent = HudBase->GetComponent<Transform>();
			{
				std::shared_ptr<Texture> texture = hud_npk->GetTexture(L"hud.img", 24);
				mr->material->texture = texture;
			}
		}
		
		GameObject* HPBase = new GameObject();
		{
			HPBase->SetName(L"HPBase");
			HPBase->ismove = false;
			AddGameObject(ELayerType::UI, HPBase);
			MeshRenderer* mr = HPBase->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"HPBaseMaterial01");
			
			Transform* tf = HPBase->GetComponent<Transform>();
			tf->position = Vector3(-0.2f, 0.0f, 0.0f);
			tf->scale = Vector3(0.14f, 0.7f, 1.0f);
			tf->parent = HudBase->GetComponent<Transform>();
			{
				std::shared_ptr<Texture> texture = hud_npk->GetTexture(L"hud.img", 1);
				mr->material->texture = texture;
			}
		}
		GameObject* MPBase = new GameObject();
		{
			MPBase->SetName(L"MPBase");
			MPBase->ismove = false;
			AddGameObject(ELayerType::UI, MPBase);
			MeshRenderer* mr = MPBase->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"MPBaseMaterial01");
			
			Transform* tf = MPBase->GetComponent<Transform>();
			tf->position = Vector3(0.19f, 0.0f, 0.0f);
			tf->scale = Vector3(0.14f, 0.7f, 1.0f);
			tf->parent = HudBase->GetComponent<Transform>();

			{
				std::shared_ptr<Texture> texture = hud_npk->GetTexture(L"hud.img", 2);
				mr->material->texture = texture;
			}
		}
		GameObject* HPFilter = new GameObject();
		{
			HPFilter->SetName(L"HPFilter");
			HPFilter->ismove = false;
			AddGameObject(ELayerType::UI, HPFilter);
			MeshRenderer* mr = HPFilter->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"HPFilterMaterial01");
			mr->material->render_mode = ERenderMode::Transparent;
			Transform* tf = HPFilter->GetComponent<Transform>();
			tf->position = Vector3(-0.195f, -0.01f, 0.0f);
			tf->scale = Vector3(0.175f, 0.85f, 1.0f);
			tf->parent = HudBase->GetComponent<Transform>();
			{
				std::shared_ptr<Texture> texture = hud_npk->GetTexture(L"hud.img", 211);
				mr->material->texture = texture;
			}
		}
		GameObject* MPFilter = new GameObject();
		{
			MPFilter->SetName(L"MPFilter");
			MPFilter->ismove = false;
			AddGameObject(ELayerType::UI, MPFilter);
			MeshRenderer* mr = MPFilter->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"MPFilterMaterial01");
			mr->material->render_mode = ERenderMode::Transparent;
			Transform* tf = MPFilter->GetComponent<Transform>();
			tf->position = Vector3(0.195f, -0.01f, 0.0f);
			tf->scale = Vector3(0.175f, 0.85f, 1.0f);
			tf->parent = HudBase->GetComponent<Transform>();
			{
				std::shared_ptr<Texture> texture = hud_npk->GetTexture(L"hud.img", 212);
				mr->material->texture = texture;
			}
		}
		GameObject* SkillQuickSlot01 = new GameObject();
		{
			SkillQuickSlot01->SetName(L"SkillQuickSlot01");
			SkillQuickSlot01->ismove = false;
			AddGameObject(ELayerType::UI, SkillQuickSlot01);
			MeshRenderer* mr = SkillQuickSlot01->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"SkillQuickSlotMaterial01");

			Transform* tf = SkillQuickSlot01->GetComponent<Transform>();
			tf->position = Vector3(-0.097f, 0.085f, 0.0f);
			tf->scale = Vector3(0.08f, 0.45f, 1.0f);
			tf->parent = HudBase->GetComponent<Transform>();
			{
				std::shared_ptr<Texture> texture = hud_npk->GetTexture(L"hud.img", 196);
				mr->material->texture = texture;
			}
		}
		GameObject* SkillQuickSlot02 = new GameObject();
		{
			SkillQuickSlot02->SetName(L"SkillQuickSlot02");
			SkillQuickSlot02->ismove = false;
			AddGameObject(ELayerType::UI, SkillQuickSlot02);
			MeshRenderer* mr = SkillQuickSlot02->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"SkillQuickSlotMaterial01");

			Transform* tf = SkillQuickSlot02->GetComponent<Transform>();
			tf->position = Vector3(-0.058f, 0.085f, 0.0f);
			tf->scale = Vector3(0.08f, 0.45f, 1.0f);
			tf->parent = HudBase->GetComponent<Transform>();
		}
		GameObject* SkillQuickSlot03 = new GameObject();
		{
			SkillQuickSlot03->SetName(L"SkillQuickSlot03");
			SkillQuickSlot03->ismove = false;
			AddGameObject(ELayerType::UI, SkillQuickSlot03);
			MeshRenderer* mr = SkillQuickSlot03->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"SkillQuickSlotMaterial01");

			Transform* tf = SkillQuickSlot03->GetComponent<Transform>();
			tf->position = Vector3(-0.019f, 0.085f, 0.0f);
			tf->scale = Vector3(0.08f, 0.45f, 1.0f);
			tf->parent = HudBase->GetComponent<Transform>();
		}
		GameObject* SkillQuickSlot04 = new GameObject();
		{
			SkillQuickSlot04->SetName(L"SkillQuickSlot04");
			SkillQuickSlot04->ismove = false;
			AddGameObject(ELayerType::UI, SkillQuickSlot04);
			MeshRenderer* mr = SkillQuickSlot04->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"SkillQuickSlotMaterial01");

			Transform* tf = SkillQuickSlot04->GetComponent<Transform>();
			tf->position = Vector3(0.02f, 0.085f, 0.0f);
			tf->scale = Vector3(0.08f, 0.45f, 1.0f);
			tf->parent = HudBase->GetComponent<Transform>();
		}
		GameObject* SkillQuickSlot05 = new GameObject();
		{
			SkillQuickSlot05->SetName(L"SkillQuickSlot05");
			SkillQuickSlot05->ismove = false;
			AddGameObject(ELayerType::UI, SkillQuickSlot05);
			MeshRenderer* mr = SkillQuickSlot05->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"SkillQuickSlotMaterial01");

			Transform* tf = SkillQuickSlot05->GetComponent<Transform>();
			tf->position = Vector3(0.059f, 0.085f, 0.0f);
			tf->scale = Vector3(0.08f, 0.45f, 1.0f);
			tf->parent = HudBase->GetComponent<Transform>();
		}
		GameObject* SkillQuickSlot06 = new GameObject();
		{
			SkillQuickSlot06->SetName(L"SkillQuickSlot06");
			SkillQuickSlot06->ismove = false;
			AddGameObject(ELayerType::UI, SkillQuickSlot06);
			MeshRenderer* mr = SkillQuickSlot06->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"SkillQuickSlotMaterial01");

			Transform* tf = SkillQuickSlot06->GetComponent<Transform>();
			tf->position = Vector3(0.098f, 0.085f, 0.0f);
			tf->scale = Vector3(0.08f, 0.45f, 1.0f);
			tf->parent = HudBase->GetComponent<Transform>();
		}
		GameObject* SkillQuickSlot07 = new GameObject();
		{
			SkillQuickSlot07->SetName(L"SkillQuickSlot07");
			SkillQuickSlot07->ismove = false;
			AddGameObject(ELayerType::UI, SkillQuickSlot07);
			MeshRenderer* mr = SkillQuickSlot07->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"SkillQuickSlotMaterial01");

			Transform* tf = SkillQuickSlot07->GetComponent<Transform>();
			tf->position = Vector3(0.137f, 0.085f, 0.0f);
			tf->scale = Vector3(0.08f, 0.45f, 1.0f);
			tf->parent = HudBase->GetComponent<Transform>();
		}
		GameObject* SkillQuickSlot08 = new GameObject();
		{
			SkillQuickSlot08->SetName(L"SkillQuickSlot08");
			SkillQuickSlot08->ismove = false;
			AddGameObject(ELayerType::UI, SkillQuickSlot08);
			MeshRenderer* mr = SkillQuickSlot08->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"SkillQuickSlotMaterial01");

			Transform* tf = SkillQuickSlot08->GetComponent<Transform>();
			tf->position = Vector3(-0.097f, -0.13f, 0.0f);
			tf->scale = Vector3(0.08f, 0.45f, 1.0f);
			tf->parent = HudBase->GetComponent<Transform>();
		}
		GameObject* SkillQuickSlot09 = new GameObject();
		{
			SkillQuickSlot09->SetName(L"SkillQuickSlot09");
			SkillQuickSlot09->ismove = false;
			AddGameObject(ELayerType::UI, SkillQuickSlot09);
			MeshRenderer* mr = SkillQuickSlot09->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"SkillQuickSlotMaterial01");

			Transform* tf = SkillQuickSlot09->GetComponent<Transform>();
			tf->position = Vector3(-0.058f, -0.13f, 0.0f);
			tf->scale = Vector3(0.08f, 0.45f, 1.0f);
			tf->parent = HudBase->GetComponent<Transform>();
		}
		GameObject* SkillQuickSlot10 = new GameObject();
		{
			SkillQuickSlot10->SetName(L"SkillQuickSlot10");
			SkillQuickSlot10->ismove = false;
			AddGameObject(ELayerType::UI, SkillQuickSlot10);
			MeshRenderer* mr = SkillQuickSlot10->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"SkillQuickSlotMaterial01");

			Transform* tf = SkillQuickSlot10->GetComponent<Transform>();
			tf->position = Vector3(-0.019f, -0.13f, 0.0f);
			tf->scale = Vector3(0.08f, 0.45f, 1.0f);
			tf->parent = HudBase->GetComponent<Transform>();
		}
		GameObject* SkillQuickSlot11 = new GameObject();
		{
			SkillQuickSlot11->SetName(L"SkillQuickSlot11");
			SkillQuickSlot11->ismove = false;
			AddGameObject(ELayerType::UI, SkillQuickSlot11);
			MeshRenderer* mr = SkillQuickSlot11->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"SkillQuickSlotMaterial01");

			Transform* tf = SkillQuickSlot11->GetComponent<Transform>();
			tf->position = Vector3(0.02f, -0.13f, 0.0f);
			tf->scale = Vector3(0.08f, 0.45f, 1.0f);
			tf->parent = HudBase->GetComponent<Transform>();
		}
		GameObject* SkillQuickSlot12 = new GameObject();
		{
			SkillQuickSlot12->SetName(L"SkillQuickSlot12");
			SkillQuickSlot12->ismove = false;
			AddGameObject(ELayerType::UI, SkillQuickSlot12);
			MeshRenderer* mr = SkillQuickSlot12->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"SkillQuickSlotMaterial01");

			Transform* tf = SkillQuickSlot12->GetComponent<Transform>();
			tf->position = Vector3(0.059f, -0.13f, 0.0f);
			tf->scale = Vector3(0.08f, 0.45f, 1.0f);
			tf->parent = HudBase->GetComponent<Transform>();
		}
		GameObject* SkillQuickSlot13 = new GameObject();
		{
			SkillQuickSlot13->SetName(L"SkillQuickSlot13");
			SkillQuickSlot13->ismove = false;
			AddGameObject(ELayerType::UI, SkillQuickSlot13);
			MeshRenderer* mr = SkillQuickSlot13->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"SkillQuickSlotMaterial01");

			Transform* tf = SkillQuickSlot13->GetComponent<Transform>();
			tf->position = Vector3(0.098f, -0.13f, 0.0f);
			tf->scale = Vector3(0.08f, 0.45f, 1.0f);
			tf->parent = HudBase->GetComponent<Transform>();
		}
		GameObject* SkillQuickSlot14 = new GameObject();
		{
			SkillQuickSlot14->SetName(L"SkillQuickSlot14");
			SkillQuickSlot14->ismove = false;
			AddGameObject(ELayerType::UI, SkillQuickSlot14);
			MeshRenderer* mr = SkillQuickSlot14->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"SkillQuickSlotMaterial01");

			Transform* tf = SkillQuickSlot14->GetComponent<Transform>();
			tf->position = Vector3(0.137f, -0.13f, 0.0f);
			tf->scale = Vector3(0.08f, 0.45f, 1.0f);
			tf->parent = HudBase->GetComponent<Transform>();
		}
		GameObject* MoreSkillBtn = new GameObject();
		{
			MoreSkillBtn->SetName(L"MoreSkillBtn");
			MoreSkillBtn->ismove = false;
			AddGameObject(ELayerType::UI, MoreSkillBtn);
			MeshRenderer* mr = MoreSkillBtn->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"MoreSkillBtnMaterial01");

			Transform* tf = MoreSkillBtn->GetComponent<Transform>();
			tf->position = Vector3(-0.132f, 0.085f, 0.0f);
			tf->scale = Vector3(0.055f, 0.45f, 1.0f);
			tf->parent = HudBase->GetComponent<Transform>();
			{
				std::shared_ptr<Texture> texture = hud_npk->GetTexture(L"hud.img", 192);
				mr->material->texture = texture;
			}
		}
		GameObject* SkillChangeBtn = new GameObject();
		{
			SkillChangeBtn->SetName(L"SkillChangeBtn");
			SkillChangeBtn->ismove = false;
			AddGameObject(ELayerType::UI, SkillChangeBtn);
			MeshRenderer* mr = SkillChangeBtn->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"SkillChangeBtnMaterial01");

			Transform* tf = SkillChangeBtn->GetComponent<Transform>();
			tf->position = Vector3(-0.132f, -0.13f, 0.0f);
			tf->scale = Vector3(0.055f, 0.45f, 1.0f);
			tf->parent = HudBase->GetComponent<Transform>();
			{
				std::shared_ptr<Texture> texture = hud_npk->GetTexture(L"hud.img", 53);
				mr->material->texture = texture;
			}
		}
		
#pragma endregion

#pragma region obj
		GameObject* SeriaNPC = new GameObject();
		{
			SeriaNPC->SetName(L"SeriaNPC");
			SeriaNPC->ismove = false;
			AddGameObject(ELayerType::BackObject, SeriaNPC);
			MeshRenderer* mr = SeriaNPC->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"SeriaTextureMaterial01");

			Transform* tf = SeriaNPC->GetComponent<Transform>();
			tf->position = Vector3(0.2f, 0.07f, 0.1f);
			tf->scale = Vector3(0.8f, 1.75f, 1.0f);
			{
				std::shared_ptr<Texture> texture = seria_npk->GetTexture(L"seria_event_2012summer.img", 0);
				mr->material->texture = texture;
			}
		}
		GameObject* Player = new GameObject();
		{
			Player->SetName(L"Player");
		
			AddGameObject(ELayerType::Player, Player);
			MeshRenderer* mr = Player->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"PlayerTextureMaterial01");
			
			Transform* tf = Player->GetComponent<Transform>();
			tf->position = Vector3(0.0f, -1.0f, 0.1f);
			tf->scale = Vector3(0.8f, 1.5f, 1.0f);
			{
				std::shared_ptr<Texture> texture = mbskin_npk->GetTexture(L"mg_body80500.img", 10);
				mr->material->texture = texture;
			}
		}
		GameObject* GoldBox = new GameObject();
		{
			GoldBox->SetName(L"GoldBox");
			GoldBox->ismove = false;
			AddGameObject(ELayerType::BackObject, GoldBox);
			MeshRenderer* mr = GoldBox->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"GoldBoxMaterial01");

			Transform* tf = GoldBox->GetComponent<Transform>();
			tf->position = Vector3(-1.3f, -0.45f, 0.1f);
			tf->scale = Vector3(1.5f, 1.5f, 1.0f);
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
		cameraComp->TurnLayerMask(ELayerType::UI, true);
		camera->GetComponent<Transform>()->position = Vector3(0.0f, 0.0f, -10.0f);
	}
}

void roka::SeriaGateScene::Loading()
{
}
