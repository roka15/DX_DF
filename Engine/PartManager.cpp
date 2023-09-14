#include "PartManager.h"

#include "GameObject.h"
#include "Prefab.h"
#include "Object.h"
#include "Image.h"

#include "Animator.h"

#include "PartScript.h"
#include "SkinPartScript.h"
#include "WeaponPartScript.h"
namespace roka::manager
{
	PartManager::PartManager()
	{
	}

	void PartManager::Initialize()
	{
		mPartInfos.insert(std::make_pair(EAvatarParts::Base, std::map<std::wstring, std::unique_ptr<GameObject>>()));
		mPartInfos.insert(std::make_pair(EAvatarParts::Weapon, std::map<std::wstring, std::unique_ptr<GameObject>>()));

		std::unique_ptr<GameObject> skin_80500 = std::make_unique<GameObject>(*(prefab::Prefabs[L"AniObject"].get()));
		{
			std::shared_ptr<SkinPartScript> script = skin_80500->AddScript<SkinPartScript>();
			script->Create(L"baseskin", L"mg_body80500.img");
		}
		std::unique_ptr<GameObject> mg_broom7200 = std::make_unique<GameObject>(*(prefab::Prefabs[L"AniObject"].get()));
		{
			std::shared_ptr<WeaponPartScript> script = mg_broom7200->AddScript<WeaponPartScript>();
			script->Create(L"weapon", L"mg_broom7200d.img");
		}

		mPartInfos[EAvatarParts::Base].insert(std::make_pair(L"mg_body80500.img", std::move(skin_80500)));
		mPartInfos[EAvatarParts::Weapon].insert(std::make_pair(L"mg_broom7200d.img", std::move(mg_broom7200)));

	}

	void PartManager::Release()
	{
	}

	std::shared_ptr<GameObject> PartManager::Find(EAvatarParts type, std::wstring name)
	{
		if (mPartInfos[type][name] == nullptr)
			return nullptr;

		std::shared_ptr<GameObject> copy = std::make_shared<GameObject>(*(mPartInfos[type][name].get()));
		std::shared_ptr<Animator> ani = copy->GetComponent<Animator>();
		ani->SetAnimationOwner();
		switch (type)
		{
		case EAvatarParts::Weapon:
			copy->GetComponent<WeaponPartScript>()->CreateSubObject();
			break;
		}
		return copy;
	}

}
