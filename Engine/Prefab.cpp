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
#include "MonsterScript.h"
#include "PartScript.h"
#include "WeaponScript.h"
#include "HitBoxScript.h"
#include "TargetMoveScript.h"
#include "Rigidbody.h"
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
		std::shared_ptr<roka::Image> PartObject = object::Instantiate<roka::Image>(AniObject);
		{
			PartObject->SetName(L"PartObject");
			PartObject->AddScript<PartScript>();
		}
		std::shared_ptr<roka::GameObject> Spider_MonsterObject = object::Instantiate<roka::GameObject>(AniObject);
		{
			Spider_MonsterObject->SetName(L"Spider_MonsterObject");
			Spider_MonsterObject->GetComponent<Transform>()->scale = Vector3(2.0f, 2.0f, 1.0f);
			std::shared_ptr<MonsterScript> monster = Spider_MonsterObject->AddScript<MonsterScript>();
			std::shared_ptr<TargetMoveScript> ms = Spider_MonsterObject->AddScript<TargetMoveScript>();
			std::shared_ptr<Rigidbody> rigid = Spider_MonsterObject->AddComponent<Rigidbody>();

			std::shared_ptr<GameObject> TopColObject = object::Instantiate<GameObject>();
			Spider_MonsterObject->AddChild(TopColObject);
			std::shared_ptr<Collider2D> col = TopColObject->AddComponent<Collider2D>();
			col->SetSize(Vector2(0.13f, 0.08f));
			col->SetCenter(Vector2(-0.05f, 0.1f));
			
		
			std::shared_ptr<HitBoxScript> hitbox = TopColObject->AddScript<HitBoxScript>();
			hitbox->hitbox = HitBoxScript::EHitBoxType::Top;
			hitbox->hitbox_owner = Spider_MonsterObject;

			std::shared_ptr<GameObject> BottomColObject = object::Instantiate<GameObject>();
			Spider_MonsterObject->AddChild(BottomColObject);
			col = BottomColObject->AddComponent<Collider2D>();
			col->SetSize(Vector2(0.13f, 0.08f));
			col->SetCenter(Vector2(-0.05f, -0.1f));
			hitbox = BottomColObject->AddScript<HitBoxScript>();
			hitbox->hitbox = HitBoxScript::EHitBoxType::Bottom;
			hitbox->hitbox_owner = Spider_MonsterObject;

			std::shared_ptr<GameObject> skill = object::Instantiate<GameObject>(AniObject);
			Spider_MonsterObject->AddChild(skill);
			skill->SetName(L"skill01");
			skill->active = GameObject::EState::Paused;
			skill->GetComponent<MeshRenderer>()->material = Resources::Find<Material>(L"DefaultEffectAniMaterial");
			std::shared_ptr<Animator> ani = skill->GetComponent<Animator>();
			std::shared_ptr<NPK> npk = Resources::Find<NPK>(L"monster_eft");
			std::shared_ptr<Texture> texture = npk->CreateAtlas(L"laser009_eft.img", 0, 20, L"monster_skill");
			ani->Create(texture, L"monster_skill", 0, 20, 0.1f);
			ani->PlayAnimation(L"monster_skill", true);
			std::shared_ptr<Transform> tf = skill->GetComponent<Transform>();
			tf->position = Vector3(1.75f, 0.025f,0.0f);
			tf->scale = Vector3(4.0f, 1.0f, 1.0f);

			MonsterScript::SetColCenter(Vector2(0.085f, -0.1f), Vector2(-0.05f, -0.1f));
			MonsterScript::SetShooterPos(Vector2(-1.75f, 0.025f), Vector2(1.75f, 0.025f));
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

				std::shared_ptr<roka::Image> Base = object::Instantiate<roka::Image>(PartObject);
				std::shared_ptr<roka::Image> Face = object::Instantiate<roka::Image>(PartObject);
				std::shared_ptr<roka::Image> Hair = object::Instantiate<roka::Image>(PartObject);
				std::shared_ptr<roka::Image> Cap = object::Instantiate<roka::Image>(PartObject);
				std::shared_ptr<roka::Image> Coat = object::Instantiate<roka::Image>(PartObject);
				std::shared_ptr<roka::Image> Neck = object::Instantiate<roka::Image>(PartObject);
				std::shared_ptr<roka::Image> Pants = object::Instantiate<roka::Image>(PartObject);
				std::shared_ptr<roka::Image> Belt = object::Instantiate<roka::Image>(PartObject);
				std::shared_ptr<roka::Image> Shoes = object::Instantiate<roka::Image>(PartObject);
				std::shared_ptr<roka::Image> Weapon = object::Instantiate<roka::Image>(PartObject);
				

				Base->SetName(L"Base");
				Face->SetName(L"Face");
				Hair->SetName(L"Hair");
				Cap->SetName(L"Cap");
				Coat->SetName(L"Coat");
				Neck->SetName(L"Neck");
				Pants->SetName(L"Pants");
				Belt->SetName(L"Belt");
				Shoes->SetName(L"Shoes");
				Weapon->SetName(L"Weapon");
				
				AvatarParrent->AddChild(Weapon);
				AvatarParrent->AddChild(Base);
				AvatarParrent->AddChild(Face);
				AvatarParrent->AddChild(Hair);
				AvatarParrent->AddChild(Cap);
				AvatarParrent->AddChild(Coat);
				AvatarParrent->AddChild(Neck);
				AvatarParrent->AddChild(Pants);
				AvatarParrent->AddChild(Belt);
				AvatarParrent->AddChild(Shoes);
				
				Base->GetComponent<PartScript>()->part_type = EAvatarParts::Base;
				Face->GetComponent<PartScript>()->part_type = EAvatarParts::Face;
				Hair->GetComponent<PartScript>()->part_type = EAvatarParts::Hair;
				Cap->GetComponent<PartScript>()->part_type = EAvatarParts::Cap;
				Coat->GetComponent<PartScript>()->part_type = EAvatarParts::Coat;
				Neck->GetComponent<PartScript>()->part_type = EAvatarParts::Neck;
				Pants->GetComponent<PartScript>()->part_type = EAvatarParts::Pants;
				Belt->GetComponent<PartScript>()->part_type = EAvatarParts::Belt;
				Shoes->GetComponent<PartScript>()->part_type = EAvatarParts::Shoes;
				Weapon->GetComponent<PartScript>()->part_type = EAvatarParts::Weapon;
				
				{
					std::shared_ptr<WeaponScript> ws = Weapon->AddScript<WeaponScript>();
					ws->part_type = EAvatarParts::Weapon;

					std::shared_ptr<Collider2D> weapon_col = Weapon->AddComponent<Collider2D>();
					weapon_col->SetSize(Vector2(0.05f, 0.04f));
					weapon_col->SetCenter(Vector2(0.25f, -0.5f));
					std::shared_ptr<HitBoxScript> hitbox = Weapon->AddScript<HitBoxScript>();
					hitbox->hitbox = HitBoxScript::EHitBoxType::Top;
					hitbox->hitbox_owner = Weapon;

					//weapon_col->is_active = false;
					std::shared_ptr<roka::Image> Weapon2 = object::Instantiate<roka::Image>(AniObject);
					Weapon2->SetName(L"Weapon2");
					ws->RegisterSubPart(Weapon2);
					Weapon->AddChild(Weapon2);
					
				}

			
				AvatarParrent->AddScript<AvatarScript>();
			}
			std::shared_ptr<GameObject> TopColObject = object::Instantiate<GameObject>();
			PlayerObject->AddChild(TopColObject);
			std::shared_ptr<Collider2D> col = TopColObject->AddComponent<Collider2D>();
			std::shared_ptr<HitBoxScript> hitbox = TopColObject->AddScript<HitBoxScript>();
			col->SetSize(Vector2(0.05f, 0.045f));
			col->SetCenter(Vector2(-0.01f, -0.4f));
			hitbox->hitbox = HitBoxScript::EHitBoxType::Top;
			hitbox->hitbox_owner = PlayerObject;

			std::shared_ptr<GameObject> BottomColObject = object::Instantiate<GameObject>();
			PlayerObject->AddChild(BottomColObject);
			col = BottomColObject->AddComponent<Collider2D>();
			hitbox = BottomColObject->AddScript<HitBoxScript>();
			col->SetSize(Vector2(0.05f, 0.07f));
			col->SetCenter(Vector2(-0.01f, -0.65f));
			hitbox->hitbox = HitBoxScript::EHitBoxType::Bottom;
			hitbox->hitbox_owner = PlayerObject;

			PlayerObject->AddScript<MoveScript>();
			PlayerObject->AddComponent<Rigidbody>()->IsGravity(true);
			PlayerObject->AddScript<PlayerScript>();
		}

		Prefabs.insert(std::make_pair(TestObject->GetName(), TestObject));
		Prefabs.insert(std::make_pair(AniObject->GetName(), AniObject));
		Prefabs.insert(std::make_pair(Spider_MonsterObject->GetName(), Spider_MonsterObject));
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
		if (base_npk == nullptr)
			base_npk = Resources::Load<NPK>(L"baseskin", path + L"baseskin.npk");
		if (weapon_npk == nullptr)
			weapon_npk = Resources::Load<NPK>(L"weapon", path + L"weapon.npk");
		if (monster_npk == nullptr)
			monster_npk = Resources::Load<NPK>(L"monster", path + L"monster.npk");
		if (monsterEft_npk == nullptr)
			monsterEft_npk = Resources::Load<NPK>(L"monster_eft", path + L"monster_eft.npk");
	}
}