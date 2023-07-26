#include "Prefab.h"
#include "NPK.h"
#include "Resources.h"
#include "Object.h"
#include "MeshRenderer.h"
#include "Transform.h"
#include "MoveScript.h"
#include "Collider2D.h"

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
		{
			std::shared_ptr<Material> material = std::make_shared<Material>();
			material->shader = Resources::Find<Shader>(L"SpriteShader");
			Resources.insert(std::make_pair(L"DefaultMaterial", material));
			Resources::Insert(L"DefaultMaterial", material);
		}
		{
			std::shared_ptr<Material> material = std::make_shared<Material>();
			material->shader = Resources::Find<Shader>(L"SpriteShader");
			material->render_mode = ERenderMode::Transparent;
			Resources.insert(std::make_pair(L"DefaultMaterial", material));
			Resources::Insert(L"TransparentMaterial", material);
		}
		{
			std::shared_ptr<Material> material = std::make_shared<Material>();
			material->shader = Resources::Find<Shader>(L"VerticalInverterShader");
			Resources.insert(std::make_pair(L"DefaultVInverterMaterial", material));
			Resources::Insert(L"DefaultVInverterMaterial", material);
		}
		{
			std::shared_ptr<Material> material = std::make_shared<Material>();
			material->shader = Resources::Find<Shader>(L"AnimationShader");
			Resources.insert(std::make_pair(L"DefaultAniMaterial", material));
			Resources::Insert(L"DefaultAniMaterial", material);
		}
		{
			std::shared_ptr<Material> material = std::make_shared<Material>();
			material->shader = Resources::Find<Shader>(L"EffectShader");
			Resources.insert(std::make_pair(L"DefaultEffectMaterial", material));
			Resources::Insert(L"DefaultEffectMaterial", material);
		}
		{
			std::shared_ptr<Material> material = std::make_shared<Material>();
			material->shader = Resources::Find<Shader>(L"EffectAniShader");
			material->render_mode = ERenderMode::Transparent;
			Resources.insert(std::make_pair(L"DefaultEffectAniMaterial", material));
			Resources::Insert(L"DefaultEffectAniMaterial", material);
		}
		{
			std::shared_ptr<Material> material = std::make_shared<Material>();
			material->shader = Resources::Find<Shader>(L"VerticalInverterAnimationShader");
			material->render_mode = ERenderMode::Transparent;
			Resources.insert(std::make_pair(L"DefaultVInverterAniMaterial", material));
			Resources::Insert(L"DefaultVInverterAniMaterial", material);
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
			TestObject->AddScript<MoveScript>();
			TestObject->AddComponent<Collider2D>();
			mr->mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->material = Resources::Find<Material>(L"SeriaTextureMaterial01");
			{
				std::shared_ptr<Texture> texture = npc_npk->GetTexture(L"seria_event_2012summer.img", 0);
				mr->material->texture = texture;
			}
		}

		Prefabs.insert(std::make_pair(TestObject->GetName(), TestObject));
	}
	void Release()
	{
		Prefabs.clear();
	}
}