#include "SelectCharacterScene.h"
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
namespace roka
{
	SelectCharacterScene::SelectCharacterScene():Scene(ESceneType::End)
	{
	}
	SelectCharacterScene::~SelectCharacterScene()
	{
	}
	void SelectCharacterScene::Initialize()
	{
		Scene::Initialize();
	}
	void SelectCharacterScene::Update()
	{
		Scene::Update();
	}
	void SelectCharacterScene::LateUpdate()
	{
		Scene::LateUpdate();
	}
	void SelectCharacterScene::Render()
	{
		Scene::Render();
	}
	
	void SelectCharacterScene::OnExit()
	{
		Scene::OnExit();
	}
//	void SelectCharacterScene::OnEnter()
//	{
//		Scene::OnEnter();
//		std::shared_ptr<NPK> npk = Resources::Find<NPK>(L"selectch");
//		if (npk == nullptr)
//		{
//			npk = Resources::Load<NPK>(L"selectch", L"..\\Resources\\npk\\selectch.npk");
//		}
//
//		std::shared_ptr<GameObject> bg = object::Instantiate<GameObject>(
//			Vector3(0.0f, 0.0f, 0.98f),
//			Vector3::Zero,
//			Vector3(8.5f, 4.4f, 1.0f),
//			ELayerType::BackObject);
//		{
//			bg->SetName(L"SelectChBG");
//			bg->ismove = false;
//			std::shared_ptr<MeshRenderer> mr = bg->AddComponent<MeshRenderer>();
//			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
//			mr->material = Resources::Find<Material>(L"BGMaterial");
//			{
//				std::shared_ptr<Texture> texture = npk->GetTexture(L"bg.img", 0);
//				mr->material->texture = texture;
//			}
//		}
//		std::shared_ptr<GameObject> bg2 = object::Instantiate<GameObject>(
//			Vector3(0.0f, -1.0f, 0.98f),
//			Vector3::Zero,
//			Vector3(8.5f, 2.2f, 1.0f),
//			ELayerType::BackObject);
//		{
//			bg2->SetName(L"SelectChBG2");
//			bg2->ismove = false;
//			std::shared_ptr<MeshRenderer> mr = bg2->AddComponent<MeshRenderer>();
//			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
//			mr->material = Resources::Find<Material>(L"BGMaterial02");
//			{
//				std::shared_ptr<Texture> texture = npk->GetTexture(L"ui.img", 0);
//				mr->material->texture = texture;
//			}
//		}
//#pragma region select ground
//		
//		std::shared_ptr<GameObject> Selectch_ground = object::Instantiate<GameObject>(
//			Vector3(-2.4f, 0.5f, 0.98f),
//			Vector3::Zero,
//			Vector3(0.8f, 0.3f, 1.0f),
//			ELayerType::BackObject);
//		{
//			Selectch_ground->SetName(L"Selectch_ground");
//			Selectch_ground->ismove = false;
//			std::shared_ptr<MeshRenderer> mr = Selectch_ground->AddComponent<MeshRenderer>();
//			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
//			mr->material = Resources::Find<Material>(L"SelectChGround");
//			{
//				std::shared_ptr<Texture> texture = npk->GetTexture(L"ui.img", 10);
//				mr->material->texture = texture;
//			}
//		}
//
//		std::shared_ptr<Transform> groundup_parent = Selectch_ground->GetComponent<Transform>();
//
//		std::shared_ptr<GameObject> Selectch_ground2 = object::Instantiate<GameObject>(
//			Vector3(1.5f, 0.0f, 0.0f),
//			Vector3::Zero,
//			Vector3(1.0f, 1.0f, 1.0f),
//			ELayerType::BackObject);
//		{
//			Selectch_ground2->SetName(L"Selectch_ground2");
//			Selectch_ground2->ismove = false;
//			std::shared_ptr<MeshRenderer> mr = Selectch_ground2->AddComponent<MeshRenderer>();
//			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
//			mr->material = Resources::Find<Material>(L"SelectChGround");
//			std::shared_ptr<Transform> tf = Selectch_ground2->GetComponent<Transform>();
//			groundup_parent->AddChild(tf);
//		}
//
//		std::shared_ptr<GameObject> Selectch_ground3 = object::Instantiate<GameObject>(
//			Vector3(3.0f, 0.0f, 0.0f),
//			Vector3::Zero,
//			Vector3(1.0f, 1.0f, 1.0f),
//			ELayerType::BackObject);
//		{
//			Selectch_ground3->SetName(L"Selectch_ground3");
//			Selectch_ground3->ismove = false;
//			std::shared_ptr<MeshRenderer> mr = Selectch_ground3->AddComponent<MeshRenderer>();
//			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
//			mr->material = Resources::Find<Material>(L"SelectChGround");
//			std::shared_ptr<Transform> tf = Selectch_ground3->GetComponent<Transform>();
//			groundup_parent->AddChild(tf);
//		}
//		std::shared_ptr<GameObject> Icon3 = object::Instantiate<GameObject>(
//			Vector3(-0.3f, -0.75f, 0.0f),
//			Vector3::Zero,
//			Vector3(0.1f, 0.3f, 1.0f),
//			ELayerType::BackObject);
//		{
//			Icon3->SetName(L"Icon3");
//			Icon3->ismove = false;
//			std::shared_ptr<MeshRenderer> mr = Icon3->AddComponent<MeshRenderer>();
//			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
//			mr->material = Resources::Find<Material>(L"IconMaterial03");
//			{
//				std::shared_ptr<Texture> texture = npk->GetTexture(L"ui.img", 21);
//				mr->material->texture = texture;
//			}
//			std::shared_ptr<Transform> tf = Icon3->GetComponent<Transform>();
//		    Selectch_ground3->GetComponent<Transform>()->AddChild(tf);
//		}
//		std::shared_ptr<GameObject> Selectch_ground4 = object::Instantiate<GameObject>(
//			Vector3(4.5f, 0.0f, 0.0f),
//			Vector3::Zero,
//			Vector3(1.0f, 1.0f, 1.0f),
//			ELayerType::BackObject);
//		{
//			Selectch_ground4->SetName(L"Selectch_ground4");
//			Selectch_ground4->ismove = false;
//			std::shared_ptr<MeshRenderer> mr = Selectch_ground4->AddComponent<MeshRenderer>();
//			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
//			mr->material = Resources::Find<Material>(L"SelectChGround");
//			std::shared_ptr<Transform> tf = Selectch_ground4->GetComponent<Transform>();
//			groundup_parent->AddChild(tf);
//		}
//
//
//		std::shared_ptr<GameObject> Selectch_ground5 = object::Instantiate<GameObject>(
//			Vector3(6.0f, 0.0f, 0.0f),
//			Vector3::Zero,
//			Vector3(1.0f, 1.0f, 1.0f),
//			ELayerType::BackObject);
//		{
//			Selectch_ground5->SetName(L"Selectch_ground5");
//			Selectch_ground5->ismove = false;
//			std::shared_ptr<MeshRenderer> mr = Selectch_ground5->AddComponent<MeshRenderer>();
//			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
//			mr->material = Resources::Find<Material>(L"SelectChGround");
//			std::shared_ptr<Transform> tf = Selectch_ground5->GetComponent<Transform>();
//			groundup_parent->AddChild(tf);
//		}
//
//		//down
//		
//		std::shared_ptr<GameObject> Selectch_ground6 = object::Instantiate<GameObject>(
//			Vector3(-3.35f, -1.4f, 0.98f),
//			Vector3::Zero,
//			Vector3(0.8f, 0.3f, 1.0f),
//			ELayerType::BackObject);
//		{
//			Selectch_ground6->SetName(L"Selectch_ground6");
//			Selectch_ground6->ismove = false;
//			std::shared_ptr<MeshRenderer> mr = Selectch_ground6->AddComponent<MeshRenderer>();
//			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
//			mr->material = Resources::Find<Material>(L"SelectChGround");
//		}
//
//		std::shared_ptr<Transform> grounddown_parent = Selectch_ground6->GetComponent<Transform>();
//
//		std::shared_ptr<GameObject> Selectch_ground7 = object::Instantiate<GameObject>(
//			Vector3(1.4f, 0.0f, 0.0f),
//			Vector3::Zero,
//			Vector3(1.0f, 1.0f, 1.0f),
//			ELayerType::BackObject);
//		{
//			Selectch_ground7->SetName(L"Selectch_ground7");
//			Selectch_ground7->ismove = false;
//			std::shared_ptr<MeshRenderer> mr = Selectch_ground7->AddComponent<MeshRenderer>();
//			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
//			mr->material = Resources::Find<Material>(L"SelectChGround");
//			std::shared_ptr<Transform> tf = Selectch_ground7->GetComponent<Transform>();
//			grounddown_parent->AddChild(tf);
//		}
//		std::shared_ptr<GameObject> Selectch_ground8 = object::Instantiate<GameObject>(
//			Vector3(2.8f, 0.0f, 0.0f),
//			Vector3::Zero,
//			Vector3(1.0f, 1.0f, 1.0f),
//			ELayerType::BackObject);
//		{
//			Selectch_ground8->SetName(L"Selectch_ground8");
//			Selectch_ground8->ismove = false;
//			std::shared_ptr<MeshRenderer> mr = Selectch_ground8->AddComponent<MeshRenderer>();
//			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
//			mr->material = Resources::Find<Material>(L"SelectChGround");
//			std::shared_ptr<Transform> tf = Selectch_ground8->GetComponent<Transform>();
//			grounddown_parent->AddChild(tf);
//		}
//		
//		std::shared_ptr<GameObject> Selectch_ground9 = object::Instantiate<GameObject>(
//			Vector3(4.2f, 0.0f, 0.0f),
//			Vector3::Zero,
//			Vector3(1.0f, 1.0f, 1.0f),
//			ELayerType::BackObject);
//		{
//			Selectch_ground9->SetName(L"Selectch_ground9");
//			Selectch_ground9->ismove = false;
//			std::shared_ptr<MeshRenderer> mr = Selectch_ground9->AddComponent<MeshRenderer>();
//			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
//			mr->material = Resources::Find<Material>(L"SelectChGround");
//			std::shared_ptr<Transform> tf = Selectch_ground9->GetComponent<Transform>();
//			grounddown_parent->AddChild(tf);
//		}
//
//		std::shared_ptr<GameObject> Selectch_ground10 = object::Instantiate<GameObject>(
//			Vector3(5.6f, 0.0f, 0.0f),
//			Vector3::Zero,
//			Vector3(1.0f, 1.0f, 1.0f),
//			ELayerType::BackObject);
//		{
//			Selectch_ground10->SetName(L"Selectch_ground10");
//			Selectch_ground10->ismove = false;
//			std::shared_ptr<MeshRenderer> mr = Selectch_ground10->AddComponent<MeshRenderer>();
//			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
//			mr->material = Resources::Find<Material>(L"SelectChGround");
//			std::shared_ptr<Transform> tf = Selectch_ground10->GetComponent<Transform>();
//			grounddown_parent->AddChild(tf);
//		}
//
//		std::shared_ptr<GameObject> Selectch_ground11 = object::Instantiate<GameObject>(
//			Vector3(7.0f, 0.0f, 0.0f),
//			Vector3::Zero,
//			Vector3(1.0f, 1.0f, 1.0f),
//			ELayerType::BackObject);
//		{
//			Selectch_ground11->SetName(L"Selectch_ground11");
//			Selectch_ground11->ismove = false;
//			std::shared_ptr<MeshRenderer> mr = Selectch_ground11->AddComponent<MeshRenderer>();
//			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
//			mr->material = Resources::Find<Material>(L"SelectChGround");
//			std::shared_ptr<Transform> tf = Selectch_ground11->GetComponent<Transform>();
//			grounddown_parent->AddChild(tf);
//		}
//
//		std::shared_ptr<GameObject> Selectch_ground12 = object::Instantiate<GameObject>(
//			Vector3(8.4f, 0.0f, 0.0f),
//			Vector3::Zero,
//			Vector3(1.0f, 1.0f, 1.0f),
//			ELayerType::BackObject);
//		{
//			Selectch_ground12->SetName(L"Selectch_ground11");
//			Selectch_ground12->ismove = false;
//			std::shared_ptr<MeshRenderer> mr = Selectch_ground12->AddComponent<MeshRenderer>();
//			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
//			mr->material = Resources::Find<Material>(L"SelectChGround");
//			std::shared_ptr<Transform> tf = Selectch_ground12->GetComponent<Transform>();
//			grounddown_parent->AddChild(tf);
//		}
//#pragma endregion
//
//#pragma region ui 
//		std::shared_ptr<GameObject> Icon1 = object::Instantiate<GameObject>(
//			Vector3(-3.7f, 2.0f, 0.98f),
//			Vector3::Zero,
//			Vector3(0.15f, 0.16f, 1.0f),
//			ELayerType::BackObject);
//		{
//			Icon1->SetName(L"Icon1");
//			Icon1->ismove = false;
//			std::shared_ptr<MeshRenderer> mr = Icon1->AddComponent<MeshRenderer>();
//			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
//			mr->material = Resources::Find<Material>(L"IconMaterial01");
//			{
//				std::shared_ptr<Texture> texture = npk->GetTexture(L"ui.img", 8);
//				mr->material->texture = texture;
//			}
//		}
//		std::shared_ptr<GameObject> Icon2 = object::Instantiate<GameObject>(
//			Vector3(-3.7f, 1.8f, 0.98f),
//			Vector3::Zero,
//			Vector3(0.15f, 0.15f, 1.0f),
//			ELayerType::BackObject);
//		{
//			Icon2->SetName(L"Icon2");
//			Icon2->ismove = false;
//			std::shared_ptr<MeshRenderer> mr = Icon2->AddComponent<MeshRenderer>();
//			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
//			mr->material = Resources::Find<Material>(L"IconMaterial02");
//			{
//				std::shared_ptr<Texture> texture = npk->GetTexture(L"ui.img", 9);
//				mr->material->texture = texture;
//			}
//		}
//		std::shared_ptr<GameObject> StartBtn = object::Instantiate<GameObject>(
//			Vector3(0.0f, -2.0f, 0.98f),
//			Vector3::Zero,
//			Vector3(1.3f, 0.35f, 1.0f),
//			ELayerType::BackObject);
//		{
//			StartBtn->SetName(L"StartBtn");
//			StartBtn->ismove = false;
//			std::shared_ptr<MeshRenderer> mr = StartBtn->AddComponent<MeshRenderer>();
//			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
//			mr->material = Resources::Find<Material>(L"BtnMaterial01");
//			{
//				std::shared_ptr<Texture> texture = npk->GetTexture(L"ui.img", 22);
//				mr->material->texture = texture;
//			}
//		}
//		std::shared_ptr<GameObject> FocusEft = object::Instantiate<GameObject>(
//			Vector3(0.0f, 0.9f, 0.98f),
//			Vector3::Zero,
//			Vector3(1.0f, 1.5f, 1.0f),
//			ELayerType::BackObject);
//		{
//			FocusEft->SetName(L"FocusEft");
//			FocusEft->ismove = false;
//			std::shared_ptr<MeshRenderer> mr = FocusEft->AddComponent<MeshRenderer>();
//			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
//			mr->material = Resources::Find<Material>(L"FocusEftMaterial01");
//			{
//				std::shared_ptr<Texture> texture = npk->GetTexture(L"ui.img", 1);
//				mr->material->texture = texture;
//			}
//		}
//
//		std::shared_ptr<GameObject> FocusEft2 = object::Instantiate<GameObject>(
//			Vector3(0.0f, -1.0f, 0.98f),
//			Vector3::Zero,
//			Vector3(1.0f, 1.5f, 1.0f),
//			ELayerType::BackObject);
//		{
//			FocusEft2->SetName(L"FocusEft");
//			FocusEft2->ismove = false;
//			std::shared_ptr<MeshRenderer> mr = FocusEft2->AddComponent<MeshRenderer>();
//			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
//			mr->material = Resources::Find<Material>(L"FocusEftMaterial01");
//			{
//				std::shared_ptr<Texture> texture = npk->GetTexture(L"ui.img", 1);
//				mr->material->texture = texture;
//			}
//		}
//
//		std::shared_ptr<GameObject> ChangeSlotTxt = object::Instantiate<GameObject>(
//			Vector3(0.0f, 0.9f, 0.98f),
//			Vector3::Zero,
//			Vector3(0.4f, 0.4f, 1.0f),
//			ELayerType::BackObject);
//		{
//			ChangeSlotTxt->SetName(L"ChangeSlotTxt");
//			ChangeSlotTxt->ismove = false;
//			std::shared_ptr<MeshRenderer> mr = ChangeSlotTxt->AddComponent<MeshRenderer>();
//			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
//			mr->material = Resources::Find<Material>(L"SelectChMoveMaterial01");
//			{
//				std::shared_ptr<Texture> texture = npk->GetTexture(L"ui.img", 5);
//				mr->material->texture = texture;
//			}
//		}
//
//		std::shared_ptr<Transform> subFocusParrent = FocusEft2->GetComponent<Transform>();
//		std::shared_ptr<GameObject> MoveSlot = object::Instantiate<GameObject>(
//			Vector3(0.0f, 0.9f, 0.98f),
//			Vector3::Zero,
//			Vector3(0.4f, 0.4f, 1.0f),
//			ELayerType::BackObject);
//		{
//			MoveSlot->SetName(L"MoveSlot");
//			MoveSlot->ismove = false;
//			std::shared_ptr<MeshRenderer> mr = MoveSlot->AddComponent<MeshRenderer>();
//			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
//			mr->material = Resources::Find<Material>(L"SelectChMoveMaterial02");
//			{
//				std::shared_ptr<Texture> texture = npk->GetTexture(L"ui.img", 13);
//				mr->material->texture = texture;
//			}
//		}
//
//		std::shared_ptr<GameObject> MoveSlotLeft = object::Instantiate<GameObject>(
//			Vector3(-0.25f, 0.0f, 0.0f),
//			Vector3::Zero,
//			Vector3(0.5f, 1.0f, 1.0f),
//			ELayerType::BackObject);
//		{
//			MoveSlotLeft->SetName(L"MoveSlotLeft");
//			MoveSlotLeft->ismove = false;
//			std::shared_ptr<MeshRenderer> mr = MoveSlotLeft->AddComponent<MeshRenderer>();
//			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
//			mr->material = Resources::Find<Material>(L"SelectChMoveMaterial03");
//			{
//				std::shared_ptr<Texture> texture = npk->GetTexture(L"ui.img", 14);
//				mr->material->texture = texture;
//			}
//			std::shared_ptr<Transform> tf = MoveSlotLeft->GetComponent<Transform>();
//			subFocusParrent->AddChild(tf);
//		}
//		std::shared_ptr<GameObject> MoveSlotRight = object::Instantiate<GameObject>(
//			Vector3(0.25f, 0.0f, 0.0f),
//			Vector3::Zero,
//			Vector3(0.5f, 1.0f, 1.0f),
//			ELayerType::BackObject);
//		{
//			MoveSlotRight->SetName(L"MoveSlotRight");
//			MoveSlotRight->ismove = false;
//			std::shared_ptr<MeshRenderer> mr = MoveSlotRight->AddComponent<MeshRenderer>();
//			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
//			mr->material = Resources::Find<Material>(L"SelectChMoveMaterial04");
//			{
//				std::shared_ptr<Texture> texture = npk->GetTexture(L"ui.img", 15);
//				mr->material->texture = texture;
//			}
//			std::shared_ptr<Transform> tf = MoveSlotRight->GetComponent<Transform>();
//			subFocusParrent->AddChild(tf);
//		}
//	
//#pragma endregion
//
//		std::shared_ptr<GameObject> camera = object::Instantiate<GameObject>(
//			Vector3(0.0f, 0.0f, -10.0f),
//			ELayerType::Player);
//		{
//			camera->SetName(L"camera");
//			camera->AddScript<CameraScript>();
//			std::shared_ptr<Camera> cameraComp = camera->AddComponent<Camera>();
//			cameraComp->TurnLayerMask(ELayerType::UI, false);
//		}
//
//		std::shared_ptr<GameObject> UIcamera = object::Instantiate<GameObject>(
//			Vector3(0.0f, 0.0f, -10.0f),
//			ELayerType::UI);
//		{
//			UIcamera->SetName(L"UICamera");
//			std::shared_ptr<Camera> cameraComp = UIcamera->AddComponent<Camera>();
//			cameraComp->DisableLayerMasks();
//			cameraComp->TurnLayerMask(ELayerType::UI, true);
//		}
//	}
	void SelectCharacterScene::Loading()
	{
	}
}