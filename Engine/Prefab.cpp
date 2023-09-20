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
			key = L"DefaultAniMaterial";
			std::shared_ptr<Material> material = std::make_shared<Material>();
			material->SetKey(key);
			material->shader = Resources::Find<Shader>(L"AnimationShader");
			material->render_mode = ERenderMode::Transparent;
			Resources.insert(std::make_pair(key, material));
			Resources::Insert(key, material);
		}
		{
			key = L"DefaultEffectAniMaterial";
			std::shared_ptr<Material> material = std::make_shared<Material>();
			material->SetKey(key);
			material->shader = Resources::Find<Shader>(L"EffectAniShader");
			material->render_mode = ERenderMode::Transparent;
			Resources.insert(std::make_pair(key, material));
			Resources::Insert(key, material);
		}
		{
			key = L"DefaultVInverterAniMaterial";
			std::shared_ptr<Material> material = std::make_shared<Material>();
			material->SetKey(key);
			material->shader = Resources::Find<Shader>(L"VerticalInverterAnimationShader");
			material->render_mode = ERenderMode::Transparent;
			Resources.insert(std::make_pair(key, material));
			Resources::Insert(key, material);
		}
		{
			key = L"DefaultVInverterEftAniMaterial";
			std::shared_ptr<Material> material = std::make_shared<Material>();
			material->SetKey(key);
			material->shader = Resources::Find<Shader>(L"VerticalInverterEftAnimationShader");
			material->render_mode = ERenderMode::Transparent;
			Resources.insert(std::make_pair(key, material));
			Resources::Insert(key, material);
		}

		std::shared_ptr<NPK> npc_npk = Resources::Find<NPK>(L"npc");
		if (npc_npk == nullptr)
			npc_npk = Resources::Load<NPK>(L"npc", L"..\\Resources\\npk\\npc.npk");

		std::shared_ptr<roka::GameObject> TestObject = object::Instantiate<roka::GameObject>(
			Vector3(0.0f, 0.0f, 1.0001f),
			Vector3::Zero,
			Vector3(0.4f, 0.875f, 1.0f));
		{
			TestObject->SetName(L"TestObject");
			std::shared_ptr<MeshRenderer> mr = TestObject->AddComponent<MeshRenderer>();
			TestObject->AddComponent<Collider2D>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"SeriaTextureMaterial01");
			{
				std::shared_ptr<Texture> texture = npc_npk->GetTexture(L"seria_event_2012summer.img", 0);
				mr->material->texture = texture;
			}
		}

		std::shared_ptr<roka::Image> AniObject = object::Instantiate<roka::Image>(
			Vector3::Zero,
			Vector3::Zero,
			Vector3::One);
		{
			AniObject->SetName(L"AniObject");
			AniObject->AddComponent<Animator>();

			std::shared_ptr<MeshRenderer>mr = AniObject->GetComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"DefaultAniMaterial");
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

			std::shared_ptr<MeshRenderer>mr = AniEftObject->GetComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"DefaultEffectAniMaterial");
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

			std::shared_ptr<MeshRenderer>mr = ColAniObject->GetComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"DefaultAniMaterial");
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

			std::shared_ptr<MeshRenderer>mr = ColAniEftObject->GetComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"DefaultEffectAniMaterial");
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
			mr->material = Resources::Find<Material>(L"DefaultAniMaterial");
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
			mr->material = Resources::Find<Material>(L"DefaultEffectAniMaterial");
		}

		Prefabs.insert(std::make_pair(TestObject->GetName(), TestObject));
		Prefabs.insert(std::make_pair(AniObject->GetName(), AniObject));
		Prefabs.insert(std::make_pair(AniEftObject->GetName(), AniEftObject));
		Prefabs.insert(std::make_pair(ColAniObject->GetName(), ColAniObject));
		Prefabs.insert(std::make_pair(ColAniEftObject->GetName(), ColAniEftObject));
		Prefabs.insert(std::make_pair(WarningObject->GetName(), WarningObject));
		Prefabs.insert(std::make_pair(WarningEftObject->GetName(), WarningEftObject));
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
			Spider_MonsterObject->AddChild(TopColObject);
			std::shared_ptr<Collider2D> col = TopColObject->AddComponent<Collider2D>();
			col->SetSize(Vector2(0.13f, 0.08f));
			col->SetCenter(Vector2(-0.05f, 0.1f));
			col->SetHitType(EHitBoxType::Top);
			


			/*std::shared_ptr<HitBoxScript> hitbox = TopColObject->AddScript<HitBoxScript>();
			hitbox->hitbox = HitBoxScript::EHitBoxType::Top;
			hitbox->hitbox_owner = Spider_MonsterObject;*/

			std::shared_ptr<GameObject> BottomColObject = object::Instantiate<GameObject>();
			Spider_MonsterObject->AddChild(BottomColObject);
			col = BottomColObject->AddComponent<Collider2D>();
			col->SetSize(Vector2(0.13f, 0.08f));
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

			std::shared_ptr<roka::GameObject> AvatarParrent = object::Instantiate<roka::GameObject>(
				Vector3::Zero,
				Vector3::Zero,
				Vector3::One);
			{
				AvatarParrent->SetName(L"AvatarParrentObj");
				PlayerObject->AddChild(AvatarParrent);
				AvatarParrent->AddScript<AvatarScript>();
			}
			std::shared_ptr<GameObject> TopColObject = object::Instantiate<GameObject>();
			PlayerObject->AddChild(TopColObject);
			std::shared_ptr<Collider2D> col = TopColObject->AddComponent<Collider2D>();
			col->SetSize(Vector2(0.05f, 0.045f));
			col->SetCenter(Vector2(-0.01f, -0.4f));
			col->SetHitType(EHitBoxType::Top);
			TopColObject->layer_type = ELayerType::Player;

			std::shared_ptr<GameObject> BottomColObject = object::Instantiate<GameObject>();
			PlayerObject->AddChild(BottomColObject);
			col = BottomColObject->AddComponent<Collider2D>();
			col->SetSize(Vector2(0.05f, 0.07f));
			col->SetCenter(Vector2(-0.01f, -0.65f));
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
	}
}