#include "StartLoadScene.h"
#include "Object.h"
#include "Prefab.h"
#include "InputManager.h"

#include "GameObject.h"
#include "Image.h"
#include "Texture.h"
#include "NPK.h"
#include "Resources.h"
#include "Transform.h"
#include "MeshRenderer.h"
#include "Collider2D.h"
#include "ImageComponent.h"
#include "PlayerScript.h"
#include "Cursor.h"
#include "Animator.h"
#include "AudioSource.h"
#include "ItemScript.h"
#include "ItemManager.h"
#include "GridGroupLayout.h"
#include "GaugeScript.h"
#include "GaugeManager.h"
#include "ScrollRect.h"
#include "ScrollView.h"

namespace roka
{
	manager::InputManager* MInput = manager::InputManager::GetInstance();
	void StartLoadScene::Initialize()
	{
		std::shared_ptr<NPK> hud_npk = Resources::Find<NPK>(L"ui_hud");
		std::shared_ptr<NPK> inven_npk = Resources::Find<NPK>(L"inventory");
		std::shared_ptr<NPK> tooltip_npk = Resources::Find<NPK>(L"tooltip");
		std::shared_ptr<NPK> baseskin_npk = Resources::Find<NPK>(L"baseskin");


		std::shared_ptr<GameObject> origin = prefab::Prefabs[L"PlayerObject"];
		std::shared_ptr<GameObject> player = object::Instantiate<GameObject>(origin);
		player->SetName(L"Player");
		player->layer_type = ELayerType::Player;
		std::shared_ptr<PlayerScript> playerScript = player->GetComponent<PlayerScript>();
		playerScript->LateInitialize();
		playerScript->RegisterKeyEvents();
		player->GetComponent<Transform>()->position = Vector3(0.0f, 0.0f, 0.3f);
		SceneManager::DontDestroy(player);



		std::shared_ptr<NPK> npk = Resources::Find<NPK>(L"infoBtn");
		std::shared_ptr<Texture> texture = npk->CreateAtlas(L"mouseIcon.img", 0, 3, L"MouseBtn");
		std::shared_ptr<roka::Image> cursor = object::Instantiate<roka::Image>(Vector3(0.0f, 0.0f, -9.0f), Vector3::Zero, Vector3(0.12f, 0.12f, 1.0f));
		cursor->SetName(L"Cursor");
		cursor->layer_type = ELayerType::Raycast;
		std::shared_ptr<MeshRenderer> mesh = cursor->AddComponent<MeshRenderer>();
		mesh->material->texture = texture;
		mesh->mesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<ImageComponent> image = cursor->GetComponent<ImageComponent>();
		image->SetSprite(1);
		std::shared_ptr<Collider2D> collider = cursor->AddComponent<Collider2D>();
		cursor->AddComponent<Cursor>();
		MInput->SetCursor(cursor);
		SceneManager::DontDestroy(cursor);

		/*	std::shared_ptr<AudioClip> clip = Resources::Load<AudioClip>(L"TestSound", L"..\\Resources\\Audio\\seria_gate.ogg");
			std::shared_ptr<AudioSource>as = cursor->AddComponent<AudioSource>();
			as->SetClip(clip);
			as->Play();*/




#pragma region hud/ui

		std::shared_ptr<Texture> hudTexture1 = hud_npk->CreateAtlas(L"hud.img", 0, 20, L"ui_hudAtlasTexture01");
		std::shared_ptr<Texture> hudTexture2 = hud_npk->CreateAtlas(L"hud.img", 20, 40, L"ui_hudAtlasTexture02");
		std::shared_ptr<Texture> hudTexture3 = hud_npk->CreateAtlas(L"hud.img", 40, 60, L"ui_hudAtlasTexture03");
		std::shared_ptr<Texture> hudTexture4 = hud_npk->CreateAtlas(L"hud.img", 60, 80, L"ui_hudAtlasTexture04");
		std::shared_ptr<Texture> hudTexture5 = hud_npk->CreateAtlas(L"hud.img", 80, 100, L"ui_hudAtlasTexture05");
		std::shared_ptr<Texture> hudTexture6 = hud_npk->CreateAtlas(L"hud.img", 100, 120, L"ui_hudAtlasTexture06");
		std::shared_ptr<Texture> hudTexture7 = hud_npk->CreateAtlas(L"hud.img", 120, 140, L"ui_hudAtlasTexture07");
		std::shared_ptr<Texture> hudTexture8 = hud_npk->CreateAtlas(L"hud.img", 140, 160, L"ui_hudAtlasTexture08");
		std::shared_ptr<Texture> hudTexture9 = hud_npk->CreateAtlas(L"hud.img", 160, 180, L"ui_hudAtlasTexture09");
		std::shared_ptr<Texture> hudTexture10 = hud_npk->CreateAtlas(L"hud.img", 180, 200, L"ui_hudAtlasTexture10");
		std::shared_ptr<Texture> hudTexture11 = hud_npk->CreateAtlas(L"hud.img", 200, 220, L"ui_hudAtlasTexture11");
		std::shared_ptr<Texture> hudTexture12 = hud_npk->CreateAtlas(L"hud.img", 220, 240, L"ui_hudAtlasTexture12");
		std::shared_ptr<Texture> hudTexture13 = hud_npk->CreateAtlas(L"hud.img", 240, 257, L"ui_hudAtlasTexture13");

		std::shared_ptr<GameObject> hudParent = object::Instantiate<GameObject>(Vector3(0.0f, 0.0f, 0.0f));
		hudParent->layer_type = ELayerType::UI;
		SceneManager::DontDestroy(hudParent);

		std::shared_ptr<Image> HudBase = object::Instantiate<Image>(
			Vector3(0.1f, -1.825f, 0.0f),
			Vector3::Zero,
			Vector3(3.7f, 0.75f, 1.0f));
		{
			HudBase->SetName(L"HudBase");
			HudBase->ismove = false;
			HudBase->layer_type = ELayerType::UI;
			std::shared_ptr<MeshRenderer> mr = HudBase->GetComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material->texture = hudTexture1;
			std::shared_ptr<ImageComponent> imageComp = HudBase->GetComponent<ImageComponent>();
			imageComp->SetSprite(0);
			hudParent->AddChild(HudBase);
		}


		std::shared_ptr<Image> HPBase = object::Instantiate<Image>(
			Vector3(-1.25f, -1.88f, -0.1f),
			Vector3::Zero,
			Vector3(0.5f, 0.5f, 1.0f));
		{
			HPBase->SetName(L"HPBase");
			HPBase->ismove = false;
			std::shared_ptr<MeshRenderer> mr = HPBase->GetComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material->shader = Resources::Find<Shader>(L"GaugeAtlasShader");
			mr->material->texture = hudTexture1;
			std::shared_ptr<ImageComponent> imageComp = HPBase->GetComponent<ImageComponent>();
			imageComp->SetSprite(1);

			hudParent->AddChild(HPBase);

			HPBase->AddScript<GaugeScript>();
			GaugeManager::GetInstance()->RegisterGaugeObject(EGaugeType::PlayerHP, HPBase);
		}

		std::shared_ptr<Image> MPBase = object::Instantiate<Image>(
			Vector3(1.45f, -1.88f, -0.1f),
			Vector3::Zero,
			Vector3(0.5f, 0.5f, 1.0f));
		{
			MPBase->SetName(L"MPBase");
			MPBase->ismove = false;
			std::shared_ptr<MeshRenderer> mr = MPBase->GetComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material->texture = hudTexture1;
			std::shared_ptr<ImageComponent> imageComp = MPBase->GetComponent<ImageComponent>();
			imageComp->SetSprite(2);

			hudParent->AddChild(MPBase);
		}


		std::shared_ptr<Image> HPFilter = object::Instantiate<Image>(
			Vector3(-1.25f, -1.85f, -0.11f),
			Vector3::Zero,
			Vector3(0.6f, 0.6f, 1.0f));
		{
			HPFilter->SetName(L"HPFilter");
			HPFilter->ismove = false;
			std::shared_ptr<MeshRenderer> mr = HPFilter->GetComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material->texture = hudTexture11;
			std::shared_ptr<ImageComponent> imageComp = HPFilter->GetComponent<ImageComponent>();
			imageComp->SetSprite(12);

			HPBase->AddChild(HPFilter);
		}
		std::shared_ptr<Image> MPFilter = object::Instantiate<Image>(
			Vector3(1.45f, -1.85f, -0.11f),
			Vector3::Zero,
			Vector3(0.6f, 0.6f, 1.0f));
		{
			MPFilter->SetName(L"MPFilter");
			MPFilter->ismove = false;
			std::shared_ptr<MeshRenderer> mr = MPFilter->GetComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material->texture = hudTexture11;
			std::shared_ptr<ImageComponent> imageComp = MPFilter->GetComponent<ImageComponent>();
			imageComp->SetSprite(13);

			MPBase->AddChild(MPFilter);
		}

		std::shared_ptr<UI> SkillQuickWindow = object::Instantiate<UI>(Vector3(-0.125f, -2.125f, -5.11f));
		SkillQuickWindow->SetName(L"SkillWindow");
		//SkillQuickWindow->AddComponent<Collider2D>();
		hudParent->AddChild(SkillQuickWindow);
		{
			std::shared_ptr<GridGroupLayout> grid = SkillQuickWindow->AddComponent<GridGroupLayout>();
			grid->SetInfo(Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), 2, 7);
			grid->SetCellSize(Vector2(0.25f, 0.25f));
		}
		for (int i = 0; i < 2 * 7; i++)
		{
			std::shared_ptr<Image> SkillQuickSlot = object::Instantiate<Image>(
				Vector3(0.0f, 0.0f, 0.0f),
				Vector3::Zero,
				Vector3(0.25f, 0.25f, 1.0f));
			{
				std::wstring name = L"SkillQuickSlot0" + i;
				SkillQuickSlot->SetName(name);
				SkillQuickSlot->ismove = false;
				SkillQuickSlot->AddComponent<Collider2D>();
				std::shared_ptr<MeshRenderer> mr = SkillQuickSlot->GetComponent<MeshRenderer>();
				mr->mesh = Resources::Find<Mesh>(L"RectMesh");
				mr->material->texture = hudTexture10;
				std::shared_ptr<ImageComponent> imageComp = SkillQuickSlot->GetComponent<ImageComponent>();
				imageComp->SetSprite(18);

				SkillQuickWindow->AddChild(SkillQuickSlot);
			}
		}


		std::shared_ptr<Image> MoreSkillBtn = object::Instantiate<Image>(
			Vector3(-0.75f, -1.75f, -0.01f),
			Vector3::Zero,
			Vector3(0.25f, 0.25f, 1.0f));
		{
			MoreSkillBtn->SetName(L"MoreSkillBtn");
			MoreSkillBtn->ismove = false;
			std::shared_ptr<MeshRenderer> mr = MoreSkillBtn->GetComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material->texture = hudTexture10;
			std::shared_ptr<ImageComponent> imageComp = MoreSkillBtn->GetComponent<ImageComponent>();
			imageComp->SetSprite(13);

			hudParent->AddChild(MoreSkillBtn);
		}
		std::shared_ptr<Image> SkillChangeBtn = object::Instantiate<Image>(
			Vector3(-0.75f, -2.0f, -0.01f),
			Vector3::Zero,
			Vector3(0.25f, 0.25f, 1.0f));
		{
			SkillChangeBtn->SetName(L"SkillChangeBtn");
			SkillChangeBtn->ismove = false;
			std::shared_ptr<MeshRenderer> mr = SkillChangeBtn->GetComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material->texture = hudTexture3;
			std::shared_ptr<ImageComponent> imageComp = SkillChangeBtn->GetComponent<ImageComponent>();
			imageComp->SetSprite(13);

			hudParent->AddChild(SkillChangeBtn);
		}

		std::shared_ptr<UI> QuickItemWindow = object::Instantiate<UI>(Vector3(-2.8f, -2.45f, -5.11f));
		QuickItemWindow->SetName(L"QuickItemWindow");
		hudParent->AddChild(QuickItemWindow);
		{
			std::shared_ptr<GridGroupLayout> grid = QuickItemWindow->AddComponent<GridGroupLayout>();
			grid->SetInfo(Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), 1, 6);
			grid->SetCellSize(Vector2(0.225f, 0.225f));
		}
		for (int i = 0; i < 1 * 6; i++)
		{
			std::shared_ptr<Image> ItemQuickSlot = object::Instantiate<Image>(
				Vector3(0.0f, 0.0f, -0.01f),
				Vector3::Zero,
				Vector3(0.25f, 0.25f, 1.0f));
			{
				std::wstring name = L"ItemQuickSlot01" + i;
				ItemQuickSlot->SetName(name);
				ItemQuickSlot->ismove = false;

				std::shared_ptr<MeshRenderer> mr = ItemQuickSlot->GetComponent<MeshRenderer>();
				mr->mesh = Resources::Find<Mesh>(L"RectMesh");
				mr->material->texture = hudTexture11;
				std::shared_ptr<ImageComponent> imageComp = ItemQuickSlot->GetComponent<ImageComponent>();
				imageComp->SetSprite(0);

				QuickItemWindow->AddChild(ItemQuickSlot);
			}
		}


		std::shared_ptr<GameObject> hudIconParent = object::Instantiate<GameObject>(Vector3(0.1f, -0.15f, -5.11f));
		hudParent->AddChild(hudIconParent);
		hudIconParent->layer_type = ELayerType::UI;
		SceneManager::DontDestroy(hudIconParent);

		std::shared_ptr<Image> Icon1 = object::Instantiate<Image>(
			Vector3(2.0f, -1.5f, -0.01f),
			Vector3::Zero,
			Vector3(0.28f, 0.25f, 1.0f));
		{
			Icon1->SetName(L"Icon1");
			Icon1->ismove = false;
			std::shared_ptr<MeshRenderer> mr = Icon1->GetComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material->texture = hudTexture4;
			std::shared_ptr<ImageComponent> imageComp = Icon1->GetComponent<ImageComponent>();
			imageComp->SetSprite(12);

			hudIconParent->AddChild(Icon1);
		}

		std::shared_ptr<Image> Icon2 = object::Instantiate<Image>(
			Vector3(2.25f, -1.5f, -0.01f),
			Vector3::Zero,
			Vector3(0.25f, 0.25f, 1.0f));
		{
			Icon2->SetName(L"Icon2");
			Icon2->ismove = false;
			std::shared_ptr<MeshRenderer> mr = Icon2->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material->texture = hudTexture4;
			std::shared_ptr<ImageComponent> imageComp = Icon2->GetComponent<ImageComponent>();
			imageComp->SetSprite(8);

			hudIconParent->AddChild(Icon2);
		}
		std::shared_ptr<Image> Icon3 = object::Instantiate<Image>(
			Vector3(2.45f, -1.5f, -0.01f),
			Vector3::Zero,
			Vector3(0.15f, 0.25f, 1.0f));
		{
			Icon3->SetName(L"Icon3");
			Icon3->ismove = false;
			std::shared_ptr<MeshRenderer> mr = Icon3->GetComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material->texture = hudTexture5;
			std::shared_ptr<ImageComponent> imageComp = Icon3->GetComponent<ImageComponent>();
			imageComp->SetSprite(13);

			hudIconParent->AddChild(Icon3);
		}

		std::shared_ptr<Image> Icon4 = object::Instantiate<Image>(
			Vector3(2.575f, -1.5f, -0.01f),
			Vector3::Zero,
			Vector3(0.15f, 0.25f, 1.0f));
		{
			Icon4->SetName(L"Icon4");
			Icon4->ismove = false;
			std::shared_ptr<MeshRenderer> mr = Icon4->GetComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material->texture = hudTexture5;
			std::shared_ptr<ImageComponent> imageComp = Icon4->GetComponent<ImageComponent>();
			imageComp->SetSprite(14);

			hudIconParent->AddChild(Icon4);
		}
		std::shared_ptr<Image> Icon5 = object::Instantiate<Image>(
			Vector3(2.7f, -1.5f, -0.01f),
			Vector3::Zero,
			Vector3(0.15f, 0.25f, 1.0f));
		{
			Icon5->SetName(L"Icon5");
			Icon5->ismove = false;
			std::shared_ptr<MeshRenderer> mr = Icon5->GetComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material->texture = hudTexture5;
			std::shared_ptr<ImageComponent> imageComp = Icon5->GetComponent<ImageComponent>();
			imageComp->SetSprite(15);

			hudIconParent->AddChild(Icon5);
		}
		std::shared_ptr<Image> Icon6 = object::Instantiate<Image>(
			Vector3(2.825f, -1.5f, -0.01f),
			Vector3::Zero,
			Vector3(0.15f, 0.25f, 1.0f));
		{
			Icon6->SetName(L"Icon6");
			Icon6->ismove = false;
			std::shared_ptr<MeshRenderer> mr = Icon6->GetComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material->texture = hudTexture5;
			std::shared_ptr<ImageComponent> imageComp = Icon6->GetComponent<ImageComponent>();
			imageComp->SetSprite(16);

			hudIconParent->AddChild(Icon6);
		}
		std::shared_ptr<Image> Icon7 = object::Instantiate<Image>(
			Vector3(2.95f, -1.5f, -0.01f),
			Vector3::Zero,
			Vector3(0.15f, 0.25f, 1.0f));
		{
			Icon7->SetName(L"Icon7");
			Icon7->ismove = false;
			std::shared_ptr<MeshRenderer> mr = Icon7->GetComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material->texture = hudTexture5;
			std::shared_ptr<ImageComponent> imageComp = Icon7->GetComponent<ImageComponent>();
			imageComp->SetSprite(17);

			hudIconParent->AddChild(Icon7);
		}
		std::shared_ptr<Image> Icon8 = object::Instantiate<Image>(
			Vector3(1.95f, -1.67f, -0.01f),
			Vector3::Zero,
			Vector3(0.25f, 0.15f, 1.0f));
		{
			Icon8->SetName(L"Icon8");
			Icon8->ismove = false;
			std::shared_ptr<MeshRenderer> mr = Icon8->GetComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material->texture = hudTexture11;
			std::shared_ptr<ImageComponent> imageComp = Icon8->GetComponent<ImageComponent>();
			imageComp->SetSprite(11);

			hudIconParent->AddChild(Icon8);
		}
		std::shared_ptr<Image> Icon9 = object::Instantiate<Image>(
			Vector3(2.6f, -1.67f, -0.01f),
			Vector3::Zero,
			Vector3(0.9f, 0.05f, 1.0f));
		{
			Icon9->SetName(L"Icon9");
			Icon9->ismove = false;
			std::shared_ptr<MeshRenderer> mr = Icon9->GetComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material->texture = hudTexture11;
			std::shared_ptr<ImageComponent> imageComp = Icon9->GetComponent<ImageComponent>();
			imageComp->SetSprite(3);

			hudIconParent->AddChild(Icon9);
		}
		std::shared_ptr<Image> Icon10 = object::Instantiate<Image>(
			Vector3(2.5f, -1.77f, -0.01f),
			Vector3::Zero,
			Vector3(1.1f, 0.1f, 1.0f));
		{
			Icon10->SetName(L"Icon10");
			Icon10->ismove = false;
			std::shared_ptr<MeshRenderer> mr = Icon10->GetComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material->texture = hudTexture13;
			std::shared_ptr<ImageComponent> imageComp = Icon10->GetComponent<ImageComponent>();
			imageComp->SetSprite(2);

			hudIconParent->AddChild(Icon10);
		}

		std::shared_ptr<Image> Icon11 = object::Instantiate<Image>(
			Vector3(2.6f, -1.67f, -0.02f),
			Vector3::Zero,
			Vector3(0.8f, 0.048f, 1.0f));
		{
			Icon11->SetName(L"Icon11");
			Icon11->ismove = false;
			std::shared_ptr<MeshRenderer> mr = Icon11->GetComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material->texture = hudTexture1;
			std::shared_ptr<ImageComponent> imageComp = Icon11->GetComponent<ImageComponent>();
			imageComp->SetSprite(3);

			hudIconParent->AddChild(Icon11);
		}
		std::shared_ptr<Image> Icon12 = object::Instantiate<Image>(
			Vector3(2.6f, -1.77f, -0.01f),
			Vector3::Zero,
			Vector3(0.8f, 0.048f, 1.0f));
		{
			Icon12->SetName(L"Icon12");
			Icon12->ismove = false;
			std::shared_ptr<MeshRenderer> mr = Icon12->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material->texture = hudTexture2;
			std::shared_ptr<ImageComponent> imageComp = Icon12->GetComponent<ImageComponent>();
			imageComp->SetSprite(2);

			hudIconParent->AddChild(Icon12);
		}




		std::shared_ptr<Image> HudBase2 = object::Instantiate<Image>(
			Vector3(0.1f, -2.1f, -0.2f),
			Vector3::Zero,
			Vector3(4.0f, 0.225f, 1.0f));
		{
			HudBase2->SetName(L"HudBase2");
			HudBase2->ismove = false;
			std::shared_ptr<MeshRenderer> mr = HudBase2->GetComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material->texture = hudTexture11;
			std::shared_ptr<ImageComponent> imageComp = HudBase2->GetComponent<ImageComponent>();
			imageComp->SetSprite(2);

			hudParent->AddChild(HudBase2);
		}
		std::shared_ptr<Image> ExpBar = object::Instantiate<Image>(
			Vector3(0.1f, -2.18f, -0.2f),
			Vector3::Zero,
			Vector3(2.0f, 0.08f, 1.0f));
		{
			ExpBar->SetName(L"ExpBar");
			ExpBar->ismove = false;
			std::shared_ptr<MeshRenderer> mr = ExpBar->GetComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material->texture = hudTexture2;
			std::shared_ptr<ImageComponent> imageComp = ExpBar->GetComponent<ImageComponent>();
			imageComp->SetSprite(4);

			std::shared_ptr<Transform> tf = ExpBar->GetComponent<Transform>();
			hudParent->AddChild(ExpBar);
		}
#pragma endregion


#pragma region inventory ui

		std::shared_ptr<Texture> invenTexture1 = inven_npk->CreateAtlas(L"inventory.img", 0, 30, L"ui_Inven01");
		std::shared_ptr<Texture> invenTexture2 = inven_npk->CreateAtlas(L"inventory.img", 30, 60, L"ui_Inven02");
		std::shared_ptr<Texture> invenTexture3 = inven_npk->CreateAtlas(L"inventory.img", 60, 90, L"ui_Inven03");
		std::shared_ptr<Texture> invenTexture4 = inven_npk->CreateAtlas(L"inventory.img", 90, 120, L"ui_Inven04");
		std::shared_ptr<Texture> invenTexture5 = inven_npk->CreateAtlas(L"inventory.img", 120, 150, L"ui_Inven05");
		std::shared_ptr<Texture> invenTexture6 = inven_npk->CreateAtlas(L"inventory.img", 150, 180, L"ui_Inven06");
		std::shared_ptr<Texture> invenTexture7 = inven_npk->CreateAtlas(L"inventory.img", 180, 204, L"ui_Inven07");

		std::shared_ptr<Texture> tooltipTexture = tooltip_npk->CreateAtlas(L"tooltip.img", 0, 8, L"ui_ToolTip");

		std::shared_ptr<GameObject> InvenParent = object::Instantiate<GameObject>(Vector3(3.0f, 0.0f, -0.6f));
		InvenParent->layer_type = ELayerType::UI;
		SceneManager::DontDestroy(InvenParent);
		playerScript->SetInven(InvenParent);

		std::shared_ptr<roka::Image> inven_base = object::Instantiate<roka::Image>(
			Vector3(-3.0f, 0.0f, 0.0),
			Vector3::Zero,
			Vector3(1.6f, 3.0f, 1.0f));
		{
			inven_base->SetName(L"InvenBase");
			inven_base->ismove = false;
			std::shared_ptr<MeshRenderer> mr = inven_base->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material->texture = invenTexture6;
			mr->material->render_mode = graphics::ERenderMode::Transparent;
			mr->alpha = 0.5f;
			mr->EnableChangeAlpha();
			std::shared_ptr<ImageComponent> image = inven_base->GetComponent<ImageComponent>();
			image->SetSprite(25);
			InvenParent->AddChild(inven_base);
		}

		std::shared_ptr<Transform> inven_parrent = inven_base->GetComponent<Transform>();

		std::shared_ptr<roka::Image> inven_base2 = object::Instantiate<roka::Image>(
			Vector3(-3.0f, 0.725f, 0.01f),
			Vector3::Zero,
			Vector3(1.4f, 1.0f, 1.0f));
		{
			inven_base2->SetName(L"InvenBase2");
			inven_base2->ismove = false;
			std::shared_ptr<MeshRenderer> mr = inven_base2->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material->texture = invenTexture1;
			mr->material->render_mode = graphics::ERenderMode::Transparent;
			std::shared_ptr<ImageComponent> image = inven_base2->GetComponent<ImageComponent>();
			image->SetSprite(0);

			InvenParent->AddChild(inven_base2);
		}

		std::shared_ptr<roka::Image> inven_base3 = object::Instantiate<roka::Image>(
			Vector3(-3.0f, -0.55f, 0.01f),
			Vector3::Zero,
			Vector3(1.4f, 1.35f, 1.0f));
		{
			inven_base3->SetName(L"InvenBase3");
			inven_base3->ismove = false;
			std::shared_ptr<MeshRenderer> mr = inven_base3->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material->texture = invenTexture2;
			mr->material->render_mode = graphics::ERenderMode::Transparent;
			mr->alpha = 0.5f;
			mr->EnableChangeAlpha();
			std::shared_ptr<ImageComponent> image = inven_base3->GetComponent<ImageComponent>();
			image->SetSprite(9);
			InvenParent->AddChild(inven_base3);
		}

		std::shared_ptr<roka::Image> inven_base4 = object::Instantiate<roka::Image>(
			Vector3(-3.0f, -1.35f, 0.0f),
			Vector3::Zero,
			Vector3(1.4f, 0.26f, 1.0f));
		{
			inven_base4->SetName(L"InvenBase4");
			inven_base4->ismove = false;
			std::shared_ptr<MeshRenderer> mr = inven_base4->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material->texture = invenTexture1;
			mr->material->render_mode = graphics::ERenderMode::Transparent;
			mr->alpha = 0.75f;
			mr->EnableChangeAlpha();
			std::shared_ptr<ImageComponent> image = inven_base4->GetComponent<ImageComponent>();
			image->SetSprite(27);
			InvenParent->AddChild(inven_base4);
		}

		std::shared_ptr<roka::Image> inven_bar = object::Instantiate<roka::Image>(
			Vector3(-3.0f, 1.5f, 0.0f),
			Vector3::Zero,
			Vector3(1.6f, 0.1f, 1.0f));
		{
			inven_bar->SetName(L"InvenBar");
			inven_bar->ismove = false;
			std::shared_ptr<MeshRenderer> mr = inven_bar->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material->texture = tooltipTexture;
			mr->material->render_mode = graphics::ERenderMode::Transparent;
			std::shared_ptr<ImageComponent> image = inven_bar->GetComponent<ImageComponent>();
			image->SetSprite(3);
			InvenParent->AddChild(inven_bar);
		}
#pragma region base2 ui 
		std::shared_ptr<roka::Image> inven_base2_tab = object::Instantiate<roka::Image>(
			Vector3(-3.0f, 1.3f, -0.2f),
			Vector3::Zero,
			Vector3(1.5f, 0.15f, 1.0f));
		{
			inven_base2_tab->SetName(L"inven_base2_tab");
			inven_base2_tab->ismove = false;
			std::shared_ptr<MeshRenderer> mr = inven_base2_tab->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material->texture = invenTexture7;
			mr->material->render_mode = graphics::ERenderMode::Transparent;
			std::shared_ptr<ImageComponent> image = inven_base2_tab->GetComponent<ImageComponent>();
			image->SetSprite(23);
			InvenParent->AddChild(inven_base2_tab);
		}
		std::shared_ptr<roka::Image> inven_base2_eft = object::Instantiate<roka::Image>(
			Vector3(-3.0f, 0.72f, -0.00f),
			Vector3::Zero,
			Vector3(1.4f, 1.0f, 1.0f));
		{
			inven_base2_eft->SetName(L"inven_base2_eft");
			inven_base2_eft->ismove = false;
			std::shared_ptr<MeshRenderer> mr = inven_base2_eft->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material->texture = invenTexture6;


			std::shared_ptr<ImageComponent> image = inven_base2_eft->GetComponent<ImageComponent>();
			image->SetSprite(28);
			InvenParent->AddChild(inven_base2_eft);
		}

		std::shared_ptr<Texture> baseTexture = Resources::Find<Texture>(L"MgBaseIdleWalkAtlasTexture");
		std::shared_ptr<roka::Image> inven_player = object::Instantiate<roka::Image>(
			Vector3(-3.0f, 1.0f, -0.01f),
			Vector3::Zero,
			Vector3(2.5f, 2.5f, 1.0f));
		{
			inven_player->SetName(L"inven_player");
			inven_player->ismove = false;
			std::shared_ptr<MeshRenderer> mr = inven_player->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material->texture = baseTexture;

			std::shared_ptr<ImageComponent> image = inven_player->GetComponent<ImageComponent>();
			image->SetSprite(10);
			InvenParent->AddChild(inven_player);
		}
		std::shared_ptr<roka::Image> inven_useitem_slot = object::Instantiate<roka::Image>(
			Vector3(-3.0f, 0.95f, -0.01f),
			Vector3::Zero,
			Vector3(1.4f, 0.5f, 1.0f));
		{
			inven_useitem_slot->SetName(L"InvenUseItemSlot01");
			inven_useitem_slot->ismove = false;
			std::shared_ptr<MeshRenderer> mr = inven_useitem_slot->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material->texture = invenTexture1;
			std::shared_ptr<ImageComponent> image = inven_useitem_slot->GetComponent<ImageComponent>();
			image->SetSprite(21);
			InvenParent->AddChild(inven_useitem_slot);
		}
		std::shared_ptr<roka::Image> inven_useitem_slot2 = object::Instantiate<roka::Image>(
			Vector3(-2.59f, 0.787f, -0.01f),
			Vector3::Zero,
			Vector3(0.2f, 0.18f, 1.0f));
		{
			inven_useitem_slot2->SetName(L"InvenUseItemSlot02");
			inven_useitem_slot2->ismove = false;
			std::shared_ptr<MeshRenderer> mr = inven_useitem_slot2->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material->texture = invenTexture1;
			std::shared_ptr<ImageComponent> image = inven_useitem_slot2->GetComponent<ImageComponent>();
			image->SetSprite(19);
			InvenParent->AddChild(inven_useitem_slot2);
		}
		std::shared_ptr<roka::Image> inven_useitem_slot3 = object::Instantiate<roka::Image>(
			Vector3(-2.59f, 0.635f, -0.01f),
			Vector3::Zero,
			Vector3(0.2f, 0.18f, 1.0f));
		{
			inven_useitem_slot3->SetName(L"InvenUseItemSlot03");
			inven_useitem_slot3->ismove = false;
			std::shared_ptr<MeshRenderer> mr = inven_useitem_slot3->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material->texture = invenTexture1;
			std::shared_ptr<ImageComponent> image = inven_useitem_slot3->GetComponent<ImageComponent>();
			image->SetSprite(20);
			InvenParent->AddChild(inven_useitem_slot3);
		}
		std::shared_ptr<roka::Image> inven_useitem_slot4 = object::Instantiate<roka::Image>(
			Vector3(-2.41f, 0.635f, -0.01f),
			Vector3::Zero,
			Vector3(0.2f, 0.18f, 1.0f));
		{
			inven_useitem_slot4->SetName(L"InvenUseItemSlot04");
			inven_useitem_slot4->ismove = false;
			std::shared_ptr<MeshRenderer> mr = inven_useitem_slot4->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material->texture = invenTexture5;
			std::shared_ptr<ImageComponent> image = inven_useitem_slot4->GetComponent<ImageComponent>();
			image->SetSprite(2);
			InvenParent->AddChild(inven_useitem_slot4);
		}

		std::shared_ptr<roka::Image> inven_book1 = object::Instantiate<roka::Image>(
			Vector3(-3.6f, 0.3f, -0.01f),
			Vector3::Zero,
			Vector3(0.15f, 0.15f, 1.0f));
		{
			inven_book1->SetName(L"inven_book1");
			inven_book1->ismove = false;
			std::shared_ptr<MeshRenderer> mr = inven_book1->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material->texture = invenTexture2;
			std::shared_ptr<ImageComponent> image = inven_book1->GetComponent<ImageComponent>();
			image->SetSprite(20);
			InvenParent->AddChild(inven_book1);
		}
		std::shared_ptr<roka::Image> inven_book2 = object::Instantiate<roka::Image>(
			Vector3(-3.5f, 0.3f, -0.01f),
			Vector3::Zero,
			Vector3(0.15f, 0.15f, 1.0f));
		{
			inven_book2->SetName(L"inven_book2");
			inven_book2->ismove = false;
			std::shared_ptr<MeshRenderer> mr = inven_book2->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material->texture = invenTexture5;
			std::shared_ptr<ImageComponent> image = inven_book2->GetComponent<ImageComponent>();
			image->SetSprite(8);
			InvenParent->AddChild(inven_book2);
		}
		std::shared_ptr<roka::Image> inven_book3 = object::Instantiate<roka::Image>(
			Vector3(-3.4f, 0.3f, -0.01f),
			Vector3::Zero,
			Vector3(0.15f, 0.15f, 1.0f));
		{
			inven_book3->SetName(L"inven_book3");
			inven_book3->ismove = false;
			std::shared_ptr<MeshRenderer> mr = inven_book3->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material->texture = invenTexture5;
			std::shared_ptr<ImageComponent> image = inven_book3->GetComponent<ImageComponent>();
			image->SetSprite(14);
			InvenParent->AddChild(inven_book3);
		}
		std::shared_ptr<roka::Image> inven_book4 = object::Instantiate<roka::Image>(
			Vector3(-2.4f, 0.3f, -0.01f),
			Vector3::Zero,
			Vector3(0.15f, 0.15f, 1.0f));
		{
			inven_book4->SetName(L"inven_book4");
			inven_book4->ismove = false;
			std::shared_ptr<MeshRenderer> mr = inven_book4->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material->texture = invenTexture6;
			std::shared_ptr<ImageComponent> image = inven_book4->GetComponent<ImageComponent>();
			image->SetSprite(22);
			InvenParent->AddChild(inven_book4);
		}

#pragma endregion

#pragma region base3 ui
		std::shared_ptr<roka::Image> inven_base3_tab = object::Instantiate<roka::Image>(
			Vector3(-3.0f, 0.16f, -0.2f),
			Vector3::Zero,
			Vector3(1.5f, 0.15f, 1.0f));
		{
			inven_base3_tab->SetName(L"inven_base3_tab");
			inven_base3_tab->ismove = false;
			std::shared_ptr<MeshRenderer> mr = inven_base3_tab->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material->texture = invenTexture7;
			std::shared_ptr<ImageComponent> image = inven_base3_tab->GetComponent<ImageComponent>();
			image->SetSprite(22);
			InvenParent->AddChild(inven_base3_tab);
		}
		std::shared_ptr<roka::Image> inven_icon1 = object::Instantiate<roka::Image>(
			Vector3(-3.625f, -1.425f, -0.0001f),
			Vector3::Zero,
			Vector3(0.1f, 0.1f, 1.0f));
		{
			inven_icon1->SetName(L"inven_icon1");
			inven_icon1->ismove = false;
			std::shared_ptr<MeshRenderer> mr = inven_icon1->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material->texture = invenTexture1;
			std::shared_ptr<ImageComponent> image = inven_icon1->GetComponent<ImageComponent>();
			image->SetSprite(4);
			InvenParent->AddChild(inven_icon1);
		}
		std::shared_ptr<roka::Image> inven_icon2 = object::Instantiate<roka::Image>(
			Vector3(-2.925f, -1.425f, -0.0001f),
			Vector3::Zero,
			Vector3(0.1f, 0.1f, 1.0f));
		{
			inven_icon2->SetName(L"inven_icon2");
			inven_icon2->ismove = false;
			std::shared_ptr<MeshRenderer> mr = inven_icon2->AddComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material->texture = invenTexture1;
			std::shared_ptr<ImageComponent> image = inven_icon2->GetComponent<ImageComponent>();
			image->SetSprite(8);
			InvenParent->AddChild(inven_icon2);
		}
		{

			std::shared_ptr<ScrollView> scrollTest = object::Instantiate<ScrollView>();
			scrollTest->GetComponent<Transform>()->position = Vector3(-3.0f, -0.56f, -0.9f);
			scrollTest->GetComponent<Transform>()->scale = Vector3(0.65f, 0.45f, 1.0f);
		
			std::shared_ptr<Texture> texture = invenTexture2;
			std::shared_ptr<ScrollRect> rect = scrollTest->GetComponent<ScrollRect>();
			std::shared_ptr<GameObject> ViewPort = rect->GetViewPort();
		
			std::shared_ptr<GameObject> Content = rect->GetContent();
		
			InvenParent->AddChild(scrollTest);
			//SceneManager::DontDestroy(scrollTest);
			{
				std::shared_ptr<GridGroupLayout>grid = Content->AddComponent<GridGroupLayout>();
				grid->SetInfo(Vector2(0.0f, -0.1f), Vector2(0.0f, 0.2f), 14,8);
				grid->SetCellSize(Vector2(0.5f, 0.5f));

				for (int i = 0; i < 14 * 8; i++)
				{
					std::shared_ptr<Image> ItemSlot = object::Instantiate<Image>(
						Vector3(0.0f, 0.0f, 0.0f),
						Vector3::Zero,
						Vector3(0.25f, 0.35f, 1.0f));
					{
						std::wstring name = L"InvenSlot" + std::to_wstring(i);
						ItemSlot->SetName(name);
						ItemSlot->ismove = false;
						ItemSlot->AddComponent<Collider2D>();
						std::shared_ptr<MeshRenderer> mr = ItemSlot->GetComponent<MeshRenderer>();
						mr->mesh = Resources::Find<Mesh>(L"RectMesh");
						mr->material->texture = texture;
						std::shared_ptr<ImageComponent> imageComp = ItemSlot->GetComponent<ImageComponent>();
						imageComp->SetSprite(19);

						rect->AddContent(ItemSlot);
					}
				}
			}
		}
		//test item
		std::shared_ptr<roka::Image> item = object::Instantiate<roka::Image>();
		{
			std::shared_ptr<ItemScript> script = item->AddScript<ItemScript>();
			script->SetUseOwner(player);
			script->SetItem(1000);
			script->SetMode(cursor, EItemModeType::Icon);
			std::shared_ptr<Transform> tf = item->GetComponent<Transform>();
			tf->scale = Vector3(0.25f, 0.25f, 1.0f);
			tf->position = Vector3(-3.75f, 1.325f, 0.0f);
		}
		SceneManager::DontDestroy(item);
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
#pragma endregion

#pragma endregion
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
#pragma endregion


	}
	void StartLoadScene::Update()
	{
	}
	void StartLoadScene::LateUpdate()
	{
	}
	void StartLoadScene::Render()
	{
	}
	void StartLoadScene::OnExit()
	{
	}
	void StartLoadScene::OnEnter()
	{
		SceneManager::LoadScene(ESceneType::SeriaRoom);
	}
	void StartLoadScene::Loading()
	{
	}
}