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
#include "WeaponScript.h"
#include "HitBoxScript.h"
#include "SkillScript.h"
#include "MonsterSkillScript.h"
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

			std::shared_ptr<MeshRenderer>mr = ColAniEftObject->GetComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"DefaultEffectAniMaterial");
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
			std::shared_ptr<SpiderMonsterScript> monster = Spider_MonsterObject->AddScript<SpiderMonsterScript>();
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
		std::shared_ptr<GameObject> SpiderSkillObject01 = object::Instantiate<GameObject>(AniObject);
		{
			SpiderSkillObject01->SetName(L"skill01");
			
			Spider_MonsterObject->AddChild(SpiderSkillObject01);
			std::shared_ptr<Collider2D> col = SpiderSkillObject01->AddComponent<Collider2D>();
			std::shared_ptr<MonsterSkillScript> skill = SpiderSkillObject01->AddScript<MonsterSkillScript>();
			std::shared_ptr<HitBoxScript> hitbox = SpiderSkillObject01->AddScript<HitBoxScript>();
			std::shared_ptr<MeshRenderer> mr = SpiderSkillObject01->GetComponent<MeshRenderer>();
			std::shared_ptr<Transform> tf = SpiderSkillObject01->GetComponent<Transform>();
			std::shared_ptr<Animator> ani = SpiderSkillObject01->GetComponent<Animator>();

			std::shared_ptr<NPK> npk = Resources::Find<NPK>(L"monster_eft");
			std::shared_ptr<Texture> texture = npk->CreateAtlas(L"laser009_eft.img", 0, 20, L"monster_skill01");
			ani->Create(texture, L"monster_skill01", 0, 20, 0.1f);

			tf->scale = Vector3(5.0f, 1.0f, 1.0f);
			tf->position = Vector3(0.0f, 0.0f, 0.1f);

			col->is_active = false;
			col->DisableRender();

			mr->is_active = false;
			mr->material = Resources::Find<Material>(L"DefaultEffectAniMaterial");

			hitbox->hitbox = HitBoxScript::EHitBoxType::Top;
			hitbox->hitbox_owner = SpiderSkillObject01;

			skill->stun_type = EStunState::HardStagger;
			skill->distance = Vector2(8.5f, 0.025f);
			skill->range = Vector2(3.0f, 0.05f);
			skill->startPos = Vector2(2.15f, 0.025f);
			skill->deleteTime = 1.5f;
			skill->startKey = L"monster_skill01";
		}
		std::shared_ptr<GameObject> TairangSkillEft01 = object::Instantiate<GameObject>();
		{
			TairangSkillEft01->SetName(L"TairangSkillEft01");
			std::shared_ptr<Transform> tf = TairangSkillEft01->GetComponent<Transform>();
			tf->scale = Vector3(1.0f, 1.0f, 1.0f);

			std::shared_ptr<GameObject> TairangSkillEft01_1 = object::Instantiate<GameObject>(AniEftObject);
			std::shared_ptr<GameObject> TairangSkillEft01_2 = object::Instantiate<GameObject>(AniEftObject);
			std::shared_ptr<GameObject> TairangSkillEft01_3 = object::Instantiate<GameObject>(AniEftObject);
			TairangSkillEft01->AddChild(TairangSkillEft01_1);
			TairangSkillEft01->AddChild(TairangSkillEft01_2);
			TairangSkillEft01->AddChild(TairangSkillEft01_3);

			tf = TairangSkillEft01_1->GetComponent<Transform>();
			Vector3 pos = tf->position;
			pos.z -= 0.1f;
			tf->position = pos;

			std::shared_ptr<Animator> ani1 = TairangSkillEft01_1->GetComponent<Animator>();
			std::shared_ptr<Animator> ani2 = TairangSkillEft01_2->GetComponent<Animator>();
			std::shared_ptr<Animator> ani3 = TairangSkillEft01_3->GetComponent<Animator>();

			std::shared_ptr<NPK> npk = Resources::Find<NPK>(L"tairnag_eft");
			std::shared_ptr<Texture> texture = npk->CreateAtlas(L"attack3slashglow.img", 0, 12, L"tairang_attack3slagshglow");
			ani1->Create(texture, L"tairang_attack3slagshglow", 0, 12, 0.08f);
			ani1->PlayAnimation(L"tairang_attack3slagshglow", true);
			ani1->Stop();
			Animator* ani_ptr = ani1.get();
			ani1->CompleteEvent(L"tairang_attack3slagshglow") = std::bind([ani_ptr]()->void {
				std::shared_ptr<MeshRenderer> ms = ani_ptr->owner->GetComponent<MeshRenderer>();
				ms->is_active = false;
				ani_ptr->Stop();
				});
		

			texture = npk->CreateAtlas(L"attack3trail.img", 0, 12, L"tairang_attack3trail");
			ani2->Create(texture, L"tairang_attack3trail", 0, 12, 0.08f);
			ani2->PlayAnimation(L"tairang_attack3trail", true);
			ani2->Stop();
			ani_ptr = ani2.get();
			ani2->CompleteEvent(L"tairang_attack3trail") = std::bind([ani_ptr]()->void {
				std::shared_ptr<MeshRenderer> ms = ani_ptr->owner->GetComponent<MeshRenderer>();
				ms->is_active = false;
				ani_ptr->Stop();
				});
		}
		std::shared_ptr<GameObject> TairangSkillEft02 = object::Instantiate<GameObject>();
		{
			TairangSkillEft02->SetName(L"TairangSkillEft02");
			std::shared_ptr<Transform> tf = TairangSkillEft02->GetComponent<Transform>();
			tf->scale = Vector3(1.0f, 1.0f, 1.0f);
		
			std::shared_ptr<GameObject> TairangSkillEft01_1 = object::Instantiate<GameObject>(AniEftObject);
			std::shared_ptr<GameObject> TairangSkillEft01_2 = object::Instantiate<GameObject>(AniEftObject);

			TairangSkillEft01_1->SetName(L"Eft01_1");
			TairangSkillEft01_2->SetName(L"Eft01_2");
			TairangSkillEft02->AddChild(TairangSkillEft01_1);
			TairangSkillEft02->AddChild(TairangSkillEft01_2);
	
			tf = TairangSkillEft01_1->GetComponent<Transform>();
			tf->position = Vector3(-0.15f, 0.15f, 0.0f);
			tf->rotation = Vector3(0.0f, 0.0f, Deg2Rad(90.0f));

			tf = TairangSkillEft01_2->GetComponent<Transform>();
			tf->position = Vector3(0.05f, 0.2f, 0.0f);
			
			std::shared_ptr<Animator> ani1 = TairangSkillEft01_1->GetComponent<Animator>();
			std::shared_ptr<Animator> ani2 = TairangSkillEft01_2->GetComponent<Animator>();

			std::shared_ptr<NPK> npk = Resources::Find<NPK>(L"tairnag_eft");
			std::shared_ptr<Texture> texture = npk->CreateAtlas(L"attack3line.img", 0, 3, L"tairang_attack3line");
			ani1->Create(texture, L"tairang_attack3line", 0, 3, 0.1f);
			ani1->PlayAnimation(L"tairang_attack3line", true);
			ani1->Stop();
			Animator* ani_ptr = ani1.get();
			ani1->CompleteEvent(L"tairang_attack3line") = std::bind([ani_ptr]()->void {
				std::shared_ptr<MeshRenderer> ms = ani_ptr->owner->GetComponent<MeshRenderer>();
				ms->is_active = false;
				ani_ptr->Stop();
				});

			texture = npk->CreateAtlas(L"attack3booster.img", 0, 12, L"tairang_attack3booster");
			ani2->Create(texture, L"tairang_attack3booster", 0, 12, 0.2f);
			texture = npk->CreateAtlas(L"abyssbombsmall.img", 0, 12, L"tairang_abyssbombsmall");
			ani2->Create(texture, L"tairang_abyssbombsmall", 0, 12, 0.13f);
			ani2->PlayAnimation(L"tairang_attack3booster", true);
			ani2->Stop();
			ani_ptr = ani2.get();

			ani2->StartEvent(L"tairang_abyssbombsmall")= std::bind([ani_ptr]()->void {
				std::shared_ptr<Transform> tf = ani_ptr->owner->GetComponent<Transform>();
				tf->scale = Vector3(0.25f, 0.25f, 1.0f);
				Vector3 pos = Vector3(-0.03f, 0.1f, 0.0f);
				tf->position = pos;
				});

			ani2->CompleteEvent(L"tairang_abyssbombsmall") = std::bind([ani_ptr]()->void {
				std::shared_ptr<MeshRenderer> ms = ani_ptr->owner->GetComponent<MeshRenderer>();
				ms->is_active = false;
				ani_ptr->Stop();
				std::shared_ptr<Transform> tf = ani_ptr->owner->GetComponent<Transform>();
				tf->scale = Vector3(1.0f, 1.0f, 1.0f);
				tf->position = Vector3(0.05f, 0.2f, 0.0f);
				ani_ptr->PlayAnimation(L"tairang_attack3booster", true);
				ani_ptr->Stop();
				});

		
		}

		std::shared_ptr<GameObject> TairangSkillEft03 = object::Instantiate<GameObject>();
		{
			TairangSkillEft03->SetName(L"TairangSkillEft03");
			std::shared_ptr<Transform> tf = TairangSkillEft03->GetComponent<Transform>();
			tf->scale = Vector3(1.0f, 1.0f, 1.0f);

			std::shared_ptr<GameObject> TairangSkillEft01_1 = object::Instantiate<GameObject>(AniEftObject);
			std::shared_ptr<GameObject> TairangSkillEft01_2 = object::Instantiate<GameObject>(AniEftObject);

			TairangSkillEft03->AddChild(TairangSkillEft01_1);
			TairangSkillEft03->AddChild(TairangSkillEft01_2);

			tf = TairangSkillEft01_1->GetComponent<Transform>();
			tf->position = Vector3(-0.0f, -0.25f, 2.0f);
			tf->scale = Vector3(0.5f, 0.1f, 1.0f);
			tf = TairangSkillEft01_2->GetComponent<Transform>();
			tf->position = Vector3(0.0f, 0.0f, 0.0f);

			std::shared_ptr<Animator> ani1 = TairangSkillEft01_1->GetComponent<Animator>();

			std::shared_ptr<NPK> npk = Resources::Find<NPK>(L"tairnag_eft");
			std::shared_ptr<Texture> texture = npk->CreateAtlas(L"bearas1crackn.img", 0, 16, L"tairang_bearas1crackn");
			ani1->Create(texture, L"tairang_bearas1crackn", 0, 16, 0.01f);
			ani1->PlayAnimation(L"tairang_bearas1crackn", true);
			ani1->Stop();
			Animator* ani_ptr = ani1.get();
			ani1->CompleteEvent(L"tairang_bearas1crackn") = std::bind([ani_ptr]()->void {
				std::shared_ptr<MeshRenderer> ms = ani_ptr->owner->GetComponent<MeshRenderer>();
				ms->is_active = false;
				ani_ptr->Stop();
				});

		}


		std::shared_ptr<GameObject> TairangeSkillObject01 = object::Instantiate<GameObject>(AniObject);
		{
			TairangeSkillObject01->SetName(L"skill01");
			Tairang_MonsterObject->AddChild(TairangeSkillObject01);
			//std::shared_ptr<Collider2D> col = TairangeSkillObject01->AddComponent<Collider2D>();
			std::shared_ptr<MonsterSkillScript> skill = TairangeSkillObject01->AddScript<MonsterSkillScript>();
			std::shared_ptr<HitBoxScript> hitbox = TairangeSkillObject01->AddScript<HitBoxScript>();
			std::shared_ptr<MeshRenderer> mr = TairangeSkillObject01->GetComponent<MeshRenderer>();
			std::shared_ptr<Transform> tf = TairangeSkillObject01->GetComponent<Transform>();
			std::shared_ptr<Animator> ani = TairangeSkillObject01->GetComponent<Animator>();


			//col->is_active = false;
			//col->DisableRender();

			mr->is_active = false;
			mr->material = Resources::Find<Material>(L"DefaultEffectAniMaterial");

			hitbox->hitbox = HitBoxScript::EHitBoxType::Bottom;
			hitbox->hitbox_owner = SpiderSkillObject01;

			skill->stun_type = EStunState::HardStagger;
			skill->distance = Vector2(0.0f,-0.0f);
			skill->range = Vector2(0.5f, 0.05f);
			skill->startPos = Vector2(0.0f, 0.0f);
			
			skill->startKey =L"";
			skill->deleteTime = 0.0f;
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
		Prefabs.insert(std::make_pair(AniEftObject->GetName(), AniEftObject));
		Prefabs.insert(std::make_pair(ColAniObject->GetName(), ColAniObject));
		Prefabs.insert(std::make_pair(ColAniEftObject->GetName(), ColAniEftObject));
		Prefabs.insert(std::make_pair(Spider_MonsterObject->GetName(), Spider_MonsterObject));
		Prefabs.insert(std::make_pair(Tairang_MonsterObject->GetName(), Tairang_MonsterObject));
		Prefabs.insert(std::make_pair(PlayerObject->GetName(), PlayerObject));
		Prefabs.insert(std::make_pair(TairangSkillEft01->GetName(), TairangSkillEft01)); 
		Prefabs.insert(std::make_pair(TairangSkillEft02->GetName(), TairangSkillEft02));
		Prefabs.insert(std::make_pair(TairangSkillEft03->GetName(), TairangSkillEft03));
		
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
	}
}