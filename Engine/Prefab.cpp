#include "Prefab.h"
#include "NPK.h"
#include "RokaMath.h"
#include "Resources.h"
#include "Object.h"
#include "Image.h"
#include "MeshRenderer.h"
#include "Transform.h"
#include "Collider2D.h"
#include "Animator.h"
#include "AvatarScript.h"
#include "MoveScript.h"
#include "PlayerScript.h"
#include "PartScript.h"

#include "WarningScript.h"
#include "TargetMoveScript.h"
#include "Rigidbody.h"
#include "MonsterScript.h"
#include "SpiderMonsterScript.h"
#include "TairangMonsterScript.h"
#include "ChangeSizeOverTime.h"
#include "AudioSource.h"
#include "Text.h"
namespace roka::prefab
{
	std::map<std::wstring, std::shared_ptr<roka::GameObject>> Prefabs = {};
	std::map<std::wstring, std::shared_ptr<roka::Resource>> Resources = {};


	void RegisterPrefab(std::wstring key, roka::GameObject* obj)
	{
		std::map<std::wstring, std::shared_ptr<roka::GameObject>>::iterator itr
			= Prefabs.find(key);
		if (itr != Prefabs.end())
			return;

		Prefabs.insert(std::make_pair(key, obj));
	}

	void Initialize()
	{
		NPKLoad();

		std::wstring key;
		{
			key = L"DefaultMaterial";
			std::shared_ptr<Material> material = std::make_shared<Material>();
			material->SetKey(key);
			material->shader = Resources::Find<Shader>(L"SpriteShader");
			material->render_mode = ERenderMode::Transparent;
			Resources.insert(std::make_pair(key, material));
			Resources::Insert(key, material);
		}
		{
			key = L"TransparentMaterial";
			std::shared_ptr<Material> material = std::make_shared<Material>();
			material->SetKey(key);
			material->shader = Resources::Find<Shader>(L"SpriteShader");
			material->render_mode = ERenderMode::Transparent;
			Resources.insert(std::make_pair(key, material));
			Resources::Insert(key, material);
		}
		{
			key = L"TransparentVInverterMaterial";
			std::shared_ptr<Material> material = std::make_shared<Material>();
			material->SetKey(key);
			material->shader = Resources::Find<Shader>(L"VerticalInverterShader");
			material->render_mode = ERenderMode::Transparent;
			Resources.insert(std::make_pair(key, material));
			Resources::Insert(key, material);
		}
		{
			key = L"DefaultVInverterMaterial";
			std::shared_ptr<Material> material = std::make_shared<Material>();
			material->SetKey(key);
			material->shader = Resources::Find<Shader>(L"VerticalInverterShader");
			Resources.insert(std::make_pair(key, material));
			Resources::Insert(key, material);
		}
		{
			key = L"DefaultEffectMaterial";
			std::shared_ptr<Material> material = std::make_shared<Material>();
			material->SetKey(key);
			material->shader = Resources::Find<Shader>(L"EffectShader");
			material->render_mode = ERenderMode::Transparent;
			Resources.insert(std::make_pair(key, material));
			Resources::Insert(key, material);
		}
		{
			key = L"DefaultAtlasMaterial";
			std::shared_ptr<Material> material = std::make_shared<Material>();
			material->SetKey(key);
			material->shader = Resources::Find<Shader>(L"AtlasShader");
			material->render_mode = ERenderMode::Transparent;
			Resources.insert(std::make_pair(key, material));
			Resources::Insert(key, material);
		}
		{
			key = L"DefaultEffectAtlasMaterial";
			std::shared_ptr<Material> material = std::make_shared<Material>();
			material->SetKey(key);
			material->shader = Resources::Find<Shader>(L"EffectAtlasShader");
			material->render_mode = ERenderMode::Transparent;
			Resources.insert(std::make_pair(key, material));
			Resources::Insert(key, material);
		}
		{
			key = L"DefaultVInverterAtlasMaterial";
			std::shared_ptr<Material> material = std::make_shared<Material>();
			material->SetKey(key);
			material->shader = Resources::Find<Shader>(L"VerticalInverterAtlasShader");
			material->render_mode = ERenderMode::Transparent;
			Resources.insert(std::make_pair(key, material));
			Resources::Insert(key, material);
		}
		{
			key = L"DefaultVInverterEftAtlasMaterial";
			std::shared_ptr<Material> material = std::make_shared<Material>();
			material->SetKey(key);
			material->shader = Resources::Find<Shader>(L"VerticalInverterEftAtlasShader");
			material->render_mode = ERenderMode::Transparent;
			Resources.insert(std::make_pair(key, material));
			Resources::Insert(key, material);
		}

		std::shared_ptr<NPK> npc_npk = Resources::Find<NPK>(L"npc");
		if (npc_npk == nullptr)
			npc_npk = Resources::Load<NPK>(L"npc", L"..\\Resources\\npk\\npc.npk");


		std::shared_ptr<roka::Image> AniObject = object::Instantiate<roka::Image>(
			Vector3::Zero,
			Vector3::Zero,
			Vector3::One);
		{
			AniObject->SetName(L"AniObject");
			AniObject->AddComponent<Animator>();
			AniObject->AddComponent<AudioSource>();

			std::shared_ptr<MeshRenderer>mr = AniObject->GetComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"DefaultAtlasMaterial");
			mr->material->shader->bsstate = EBSType::AlphaBlend;
			mr->material->render_mode = ERenderMode::Transparent;
		}
		std::shared_ptr<roka::Image> AniEftObject = object::Instantiate<roka::Image>(
			Vector3::Zero,
			Vector3::Zero,
			Vector3::One);
		{
			AniEftObject->SetName(L"AniEftObject");
			AniEftObject->AddComponent<Animator>();
			AniEftObject->AddComponent<AudioSource>();

			std::shared_ptr<MeshRenderer>mr = AniEftObject->GetComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"DefaultEffectAtlasMaterial");
			mr->material->render_mode = ERenderMode::Transparent;
		}
		std::shared_ptr<roka::Image> ColAniObject = object::Instantiate<roka::Image>(
			Vector3::Zero,
			Vector3::Zero,
			Vector3::One);
		{
			ColAniObject->SetName(L"ColAniObject");
			ColAniObject->AddComponent<Animator>();
			ColAniObject->AddComponent<Collider2D>();
			ColAniObject->AddComponent<AudioSource>();

			std::shared_ptr<MeshRenderer>mr = ColAniObject->GetComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"DefaultAtlasMaterial");
			mr->material->shader->bsstate = EBSType::AlphaBlend;
			mr->material->render_mode = ERenderMode::Transparent;
		}
		std::shared_ptr<roka::Image> ColAniEftObject = object::Instantiate<roka::Image>(
			Vector3::Zero,
			Vector3::Zero,
			Vector3::One);
		{
			ColAniEftObject->SetName(L"ColAniEftObject");
			ColAniEftObject->AddComponent<Animator>();
			ColAniEftObject->AddComponent<Collider2D>();
			ColAniEftObject->AddComponent<AudioSource>();

			std::shared_ptr<MeshRenderer>mr = ColAniEftObject->GetComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"DefaultEffectAtlasMaterial");
		}
		std::shared_ptr<roka::Image> ChangeSizeOverTimeObject = object::Instantiate<roka::Image>(
			Vector3::Zero,
			Vector3::Zero,
			Vector3::One);
		{
			ChangeSizeOverTimeObject->SetName(L"ChangeSizeOverTimeObject");
			ChangeSizeOverTimeObject->AddComponent<Animator>();
			ChangeSizeOverTimeObject->AddScript<ChangeSizeOverTime>();
			std::shared_ptr<MeshRenderer>mr = ChangeSizeOverTimeObject->GetComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"DefaultAtlasMaterial");
			mr->material->shader->bsstate = EBSType::AlphaBlend;
			mr->material->render_mode = ERenderMode::Transparent;
		}
		std::shared_ptr<roka::Image> ChangeSizeOverTimeEftObject = object::Instantiate<roka::Image>(
			Vector3::Zero,
			Vector3::Zero,
			Vector3::One);
		{
			ChangeSizeOverTimeEftObject->SetName(L"ChangeSizeOverTimeEftObject");
			ChangeSizeOverTimeEftObject->AddComponent<Animator>();
			ChangeSizeOverTimeEftObject->AddScript<ChangeSizeOverTime>();
			std::shared_ptr<MeshRenderer>mr = ChangeSizeOverTimeEftObject->GetComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"DefaultEffectAtlasMaterial");
			mr->material->render_mode = ERenderMode::Transparent;
		}

		std::shared_ptr<roka::Image> WarningObject = object::Instantiate<roka::Image>(
			Vector3::Zero,
			Vector3::Zero,
			Vector3::One);
		{
			WarningObject->SetName(L"WarningObject");
			WarningObject->AddComponent<Animator>();
			WarningObject->AddScript<WarningScript>();

			std::shared_ptr<MeshRenderer>mr = WarningObject->GetComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"DefaultAtlasMaterial");
		}
		std::shared_ptr<roka::Image> WarningEftObject = object::Instantiate<roka::Image>(
			Vector3::Zero,
			Vector3::Zero,
			Vector3::One);
		{
			WarningEftObject->SetName(L"WarningEftObject");
			WarningEftObject->AddComponent<Animator>();
			WarningEftObject->AddScript<WarningScript>();

			std::shared_ptr<MeshRenderer>mr = WarningEftObject->GetComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"DefaultEffectAtlasMaterial");
		}

		Prefabs.insert(std::make_pair(AniObject->GetName(), AniObject));
		Prefabs.insert(std::make_pair(AniEftObject->GetName(), AniEftObject));
		Prefabs.insert(std::make_pair(ColAniObject->GetName(), ColAniObject));
		Prefabs.insert(std::make_pair(ColAniEftObject->GetName(), ColAniEftObject));
		Prefabs.insert(std::make_pair(WarningObject->GetName(), WarningObject));
		Prefabs.insert(std::make_pair(WarningEftObject->GetName(), WarningEftObject));
		Prefabs.insert(std::make_pair(ChangeSizeOverTimeObject->GetName(), ChangeSizeOverTimeObject));
		Prefabs.insert(std::make_pair(ChangeSizeOverTimeEftObject->GetName(), ChangeSizeOverTimeEftObject));
		/*Prefabs.insert(std::make_pair(TairangSkillEft01->GetName(), TairangSkillEft01));
		Prefabs.insert(std::make_pair(TairangSkillEft02->GetName(), TairangSkillEft02));
		Prefabs.insert(std::make_pair(TairangSkillEft03->GetName(), TairangSkillEft03));*/

	}
	void LateInitialize()
	{
		std::shared_ptr<GameObject> AniObject = Prefabs[L"AniObject"];
		std::shared_ptr<roka::GameObject> Spider_MonsterObject = object::Instantiate<roka::GameObject>(AniObject);
		{
			Spider_MonsterObject->SetName(L"Spider_MonsterObject");
			Spider_MonsterObject->GetComponent<Transform>()->scale = Vector3(2.0f, 2.0f, 1.0f);
			std::shared_ptr<SpiderMonsterScript> monster = Spider_MonsterObject->AddScript<SpiderMonsterScript>();
			std::shared_ptr<TargetMoveScript> ms = Spider_MonsterObject->AddScript<TargetMoveScript>();
			std::shared_ptr<Rigidbody> rigid = Spider_MonsterObject->AddComponent<Rigidbody>();


			std::shared_ptr<GameObject> TopColObject = object::Instantiate<GameObject>();
			TopColObject->GetComponent<Transform>()->scale = Vector3(2.0f, 2.0f, 1.0f);
			Spider_MonsterObject->AddChild(TopColObject);
			std::shared_ptr<Collider2D> col = TopColObject->AddComponent<Collider2D>();
			col->SetSize(Vector2(0.25f, 0.25f));
			//col->SetCenter(Vector2(-0.0f, -0.1f));
			//col->SetSize(Vector2(0.13f, 0.08f));
			col->SetCenter(Vector2(-0.05f, 0.1f));
			col->SetHitType(EHitBoxType::Top);



			/*std::shared_ptr<HitBoxScript> hitbox = TopColObject->AddScript<HitBoxScript>();
			hitbox->hitbox = HitBoxScript::EHitBoxType::Top;
			hitbox->hitbox_owner = Spider_MonsterObject;*/

			std::shared_ptr<GameObject> BottomColObject = object::Instantiate<GameObject>();
			BottomColObject->GetComponent<Transform>()->scale = Vector3(2.0f, 2.0f, 1.0f);
			Spider_MonsterObject->AddChild(BottomColObject);
			col = BottomColObject->AddComponent<Collider2D>();
			col->SetSize(Vector2(0.25f, 0.25f));
			col->SetCenter(Vector2(-0.05f, -0.1f));
			col->SetHitType(EHitBoxType::Bottom);
			/*hitbox = BottomColObject->AddScript<HitBoxScript>();
			hitbox->hitbox = HitBoxScript::EHitBoxType::Bottom;
			hitbox->hitbox_owner = Spider_MonsterObject;*/
		}

		std::shared_ptr<GameObject> Tairang_MonsterObject = object::Instantiate<GameObject>(AniObject);
		{
			Tairang_MonsterObject->SetName(L"Tairang_MonsterObject");
			Tairang_MonsterObject->GetComponent<Transform>()->scale = Vector3(3.0f, 3.0f, 1.0f);
			std::shared_ptr<TairangMonsterScript> monster = Tairang_MonsterObject->AddScript<TairangMonsterScript>();
			std::shared_ptr<TargetMoveScript> ms = Tairang_MonsterObject->AddScript<TargetMoveScript>();
			std::shared_ptr<Rigidbody> rigid = Tairang_MonsterObject->AddComponent<Rigidbody>();
			std::shared_ptr<Transform> tf = Tairang_MonsterObject->GetComponent<Transform>();
			tf->position = Vector3(0.0f, 0.0f, 0.1f);
		}

		std::shared_ptr<roka::GameObject> PlayerObject = object::Instantiate<roka::GameObject>(
			Vector3::Zero,
			Vector3::Zero,
			Vector3::One);
		{
			PlayerObject->SetName(L"PlayerObject");
			PlayerObject->GetComponent<Transform>()->scale = Vector3(3.0f, 3.0f, 1.0f);
			PlayerObject->layer_type = ELayerType::Player;

			PlayerObject->AddComponent<AudioSource>();

			std::shared_ptr<UI> text = object::Instantiate<UI>();
			text->SetName(L"MyText");
			std::shared_ptr<Text> tc = text->AddComponent<Text>();
			PlayerObject->AddChild(text);

			std::shared_ptr<roka::GameObject> AvatarParrent = object::Instantiate<roka::GameObject>(
				Vector3::Zero,
				Vector3::Zero,
				Vector3::One);
			{
				AvatarParrent->SetName(L"AvatarParrentObj");
				AvatarParrent->GetComponent<Transform>()->scale = Vector3(3.0f, 3.0f, 1.0f);
				PlayerObject->AddChild(AvatarParrent);
				AvatarParrent->AddScript<AvatarScript>();
			}
			std::shared_ptr<GameObject> TopColObject = object::Instantiate<GameObject>();
			TopColObject->SetName(L"PlayerTopCol");
			TopColObject->GetComponent<Transform>()->scale = Vector3(3.0f, 3.0f, 1.0f);
			PlayerObject->AddChild(TopColObject);
			std::shared_ptr<Collider2D> col = TopColObject->AddComponent<Collider2D>();
			col->SetSize(Vector2(0.05f, 0.05f));
			col->SetCenter(Vector2(-0.0f, -0.1f));
			col->SetHitType(EHitBoxType::Top);
			TopColObject->layer_type = ELayerType::Player;

			std::shared_ptr<GameObject> BottomColObject = object::Instantiate<GameObject>();
			BottomColObject->GetComponent<Transform>()->scale = Vector3(3.0f, 3.0f, 1.0f);
			PlayerObject->AddChild(BottomColObject);

			col = BottomColObject->AddComponent<Collider2D>();
			BottomColObject->SetName(L"PlayerBottomCol");
			col->SetSize(Vector2(0.05f, 0.05f));
			col->SetCenter(Vector2(-0.0f, -0.2f));
			col->SetHitType(EHitBoxType::Bottom);
			BottomColObject->layer_type = ELayerType::Player;

			PlayerObject->AddScript<MoveScript>();
			PlayerObject->AddComponent<Rigidbody>()->IsGravity(true);
			PlayerObject->AddScript<PlayerScript>();
		}
		Prefabs.insert(std::make_pair(Spider_MonsterObject->GetName(), Spider_MonsterObject));
		Prefabs.insert(std::make_pair(Tairang_MonsterObject->GetName(), Tairang_MonsterObject));
		Prefabs.insert(std::make_pair(PlayerObject->GetName(), PlayerObject));

	}
	void Release()
	{
		Prefabs.clear();
	}
	void NPKLoad()
	{
		const std::wstring path = L"..\\Resources\\npk\\";
		std::shared_ptr<NPK> base_npk = Resources::Find<NPK>(L"baseskin");
		std::shared_ptr<NPK> weapon_npk = Resources::Find<NPK>(L"weapon");
		std::shared_ptr<NPK> monster_npk = Resources::Find<NPK>(L"monster");
		std::shared_ptr<NPK> monsterEft_npk = Resources::Find<NPK>(L"monster_eft");
		std::shared_ptr<NPK> tairang_npk = Resources::Find<NPK>(L"tairnag");
		std::shared_ptr<NPK> tairangEft_npk = Resources::Find<NPK>(L"tairnag_eft");
		std::shared_ptr<NPK> warning_npk = Resources::Find<NPK>(L"warning");
		std::shared_ptr<NPK> hudUI_npk = Resources::Find<NPK>(L"ui_hud");
		std::shared_ptr<NPK> mage_AntiGravity = Resources::Find<NPK>(L"mageAntiGravity");
		std::shared_ptr<NPK> mage_homonculouse = Resources::Find<NPK>(L"homonculouse");
		std::shared_ptr<NPK> mage_familiar = Resources::Find<NPK>(L"familiar");
		std::shared_ptr<NPK> seria_room = Resources::Find<NPK>(L"seria_room");
		std::shared_ptr<NPK> npc = Resources::Find<NPK>(L"npc");
		std::shared_ptr<NPK> gate = Resources::Find<NPK>(L"gate");
		std::shared_ptr<NPK> inven_npk = Resources::Find<NPK>(L"inventory");
		std::shared_ptr<NPK> tooltip_npk = Resources::Find<NPK>(L"tooltip");
		std::shared_ptr<NPK> infomationButton = Resources::Find<NPK>(L"infoBtn");
		std::shared_ptr<NPK> item = Resources::Find<NPK>(L"item");
		std::shared_ptr<NPK> mgAvatarUI = Resources::Find<NPK>(L"mgAvatarUI");
		std::shared_ptr<NPK> mgHair = Resources::Find<NPK>(L"mgHair");
		std::shared_ptr<NPK> mgCap = Resources::Find<NPK>(L"mgCap");
		std::shared_ptr<NPK> mgNeck = Resources::Find<NPK>(L"mgNeck");
		std::shared_ptr<NPK> mgCoat = Resources::Find<NPK>(L"mgCoat");
		std::shared_ptr<NPK> mgPants = Resources::Find<NPK>(L"mgPants");
		std::shared_ptr<NPK> dgbg1 = Resources::Find<NPK>(L"dgbg1");
		if (base_npk == nullptr)
			base_npk = Resources::Load<NPK>(L"baseskin", path + L"baseskin.npk");
		if (weapon_npk == nullptr)
			weapon_npk = Resources::Load<NPK>(L"weapon", path + L"weapon.npk");
		if (monster_npk == nullptr)
			monster_npk = Resources::Load<NPK>(L"monster", path + L"monster.npk");
		if (monsterEft_npk == nullptr)
			monsterEft_npk = Resources::Load<NPK>(L"monster_eft", path + L"monster_eft.npk");
		if (tairang_npk == nullptr)
			tairang_npk = Resources::Load<NPK>(L"tairang", path + L"tairang.npk");
		if (tairangEft_npk == nullptr)
			tairangEft_npk = Resources::Load<NPK>(L"tairnag_eft", path + L"tairang_eft.npk");
		if (warning_npk == nullptr)
			warning_npk = Resources::Load<NPK>(L"warning", path + L"warning.npk");
		if (hudUI_npk == nullptr)
			hudUI_npk = Resources::Load<NPK>(L"ui_hud", path + L"HudUI.npk");
		if (mage_AntiGravity == nullptr)
			mage_AntiGravity = Resources::Load<NPK>(L"mageAntiGravity", path + L"mageAntiGravity.npk");
		if (mage_homonculouse == nullptr)
			mage_homonculouse = Resources::Load<NPK>(L"homonculouse", path + L"homonculouse.npk");
		if (mage_familiar == nullptr)
			mage_familiar = Resources::Load<NPK>(L"mage_familiar", path + L"mage_familiar.npk");

		if (seria_room == nullptr)
			seria_room = Resources::Load<NPK>(L"seria_room", L"..\\Resources\\npk\\seriaroom.npk");
		if (npc == nullptr)
			npc = Resources::Load<NPK>(L"npc", L"..\\Resources\\npk\\npc.npk");
		if (gate == nullptr)
			gate = Resources::Load<NPK>(L"gate", L"..\\Resources\\npk\\gate.npk");
		if (inven_npk == nullptr)
			inven_npk = Resources::Load<NPK>(L"inventory", L"..\\Resources\\npk\\inventory.npk");
		if (tooltip_npk == nullptr)
			tooltip_npk = Resources::Load<NPK>(L"tooltip", L"..\\Resources\\npk\\tooltip.npk");
		if (infomationButton == nullptr)
			infomationButton = Resources::Load<NPK>(L"infoBtn", L"..\\Resources\\npk\\InformationButton.npk");
		if (item == nullptr)
			item = Resources::Load<NPK>(L"item", L"..\\Resources\\npk\\Item.npk");
		if (mgAvatarUI == nullptr)
			mgAvatarUI = Resources::Load<NPK>(L"mgAvatarUI", L"..\\Resources\\npk\\mgAvatarUI.npk");
		if (mgHair == nullptr)
			mgHair = Resources::Load<NPK>(L"mgHair", L"..\\Resources\\npk\\mg_hair.npk");
		if (mgCap == nullptr)
			mgCap = Resources::Load<NPK>(L"mgCap", L"..\\Resources\\npk\\mg_cap.npk");
		if (mgNeck == nullptr)
			mgNeck = Resources::Load<NPK>(L"mgNeck", L"..\\Resources\\npk\\mg_neck.npk");
		if (mgCoat == nullptr)
			mgCoat = Resources::Load<NPK>(L"mgCoat", L"..\\Resources\\npk\\mg_coat.npk");
		if (mgPants == nullptr)
			mgPants = Resources::Load<NPK>(L"mgPants", L"..\\Resources\\npk\\mg_pants.npk");
		
		if (dgbg1 == nullptr)
			dgbg1 = Resources::Load<NPK>(L"dgbg1", L"..\\Resources\\npk\\dgbg1.npk");
	}
}