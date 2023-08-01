#include "Prefab.h"
#include "NPK.h"
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
		}
		std::shared_ptr<roka::Image> PartObject = object::Instantiate<roka::Image>(AniObject);
		{
			PartObject->SetName(L"PartObject");
			PartObject->AddScript<PartScript>();

			
			std::shared_ptr<MeshRenderer>mr = PartObject->GetComponent<MeshRenderer>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"DefaultAniMaterial");
			mr->material->shader->bsstate = EBSType::AlphaBlend;
			mr->material->render_mode = ERenderMode::Transparent;
		}

		std::shared_ptr<roka::GameObject> PlayerObject = object::Instantiate<roka::GameObject>(
			Vector3::Zero,
			Vector3::Zero,
			Vector3::One);
		{
			PlayerObject->SetName(L"PlayerObject");
			PlayerObject->GetComponent<Transform>()->scale = Vector3(3.0f, 3.0f, 1.0f);
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

				AvatarParrent->AddChild(Base);
				AvatarParrent->AddChild(Face);
				AvatarParrent->AddChild(Hair);
				AvatarParrent->AddChild(Cap);
				AvatarParrent->AddChild(Coat);
				AvatarParrent->AddChild(Neck);
				AvatarParrent->AddChild(Pants);
				AvatarParrent->AddChild(Belt);
				AvatarParrent->AddChild(Shoes);
				AvatarParrent->AddChild(Weapon);

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

				AvatarParrent->AddScript<AvatarScript>();
			}
			std::shared_ptr<Collider2D> cd = PlayerObject->AddComponent<Collider2D>();
			cd->SetSize(Vector2(0.1f, 0.2f));
			cd->SetCenter(Vector2(-0.01f, -0.525f));
			PlayerObject->AddScript<MoveScript>();
			PlayerObject->AddScript<PlayerScript>();
		}

		Prefabs.insert(std::make_pair(TestObject->GetName(), TestObject));
		Prefabs.insert(std::make_pair(AniObject->GetName(), AniObject));
		Prefabs.insert(std::make_pair(PlayerObject->GetName(), PlayerObject));
	}
	void Release()
	{
		Prefabs.clear();
	}
	void NPKLoad()
	{
		std::shared_ptr<NPK> npc_npk = Resources::Find<NPK>(L"baseskin");
		if (npc_npk == nullptr)
			npc_npk = Resources::Load<NPK>(L"baseskin", L"..\\Resources\\npk\\baseskin.npk");
	}
}