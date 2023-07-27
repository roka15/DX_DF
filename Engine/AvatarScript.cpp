#include "AvatarScript.h"
#include "Prefab.h"
#include "Image.h"
#include "SceneManager.h"
#include "Object.h"
#include "Transform.h"
#include "Animator.h"
#include "PlayerScript.h"


namespace roka
{
	AvatarScript::AvatarScript():Script(EScriptType::Avatar)
	{
	}
	AvatarScript::AvatarScript(const AvatarScript& ref):Script(ref)
	{
	}
	void AvatarScript::Copy(AvatarScript* src)
	{
		Script::Copy(src);
	}
	AvatarScript::~AvatarScript()
	{
	}
	void AvatarScript::Initialize()
	{
		auto itr = prefab::Prefabs.find(L"AniObject");
		std::shared_ptr<Image> CopyObj = std::dynamic_pointer_cast<Image>(itr->second);
		if (CopyObj == nullptr)
			return;

		std::shared_ptr<Image> base = object::Instantiate<Image>(CopyObj);
		std::shared_ptr<Image> face = object::Instantiate<Image>(CopyObj);
		std::shared_ptr<Image> hair = object::Instantiate<Image>(CopyObj);
		std::shared_ptr<Image> cap = object::Instantiate<Image>(CopyObj);
		std::shared_ptr<Image> coat = object::Instantiate<Image>(CopyObj);
		std::shared_ptr<Image> neck = object::Instantiate<Image>(CopyObj);
		std::shared_ptr<Image> pants = object::Instantiate<Image>(CopyObj);
		std::shared_ptr<Image> belt = object::Instantiate<Image>(CopyObj);
		std::shared_ptr<Image> shoes = object::Instantiate<Image>(CopyObj);
		std::shared_ptr<Image> weapon = object::Instantiate<Image>(CopyObj);

		mParts.insert(std::make_pair(EAvatarParts::Base, base));
		mParts.insert(std::make_pair(EAvatarParts::Face, face));
		mParts.insert(std::make_pair(EAvatarParts::Hair, hair));
		mParts.insert(std::make_pair(EAvatarParts::Cap, cap));
		mParts.insert(std::make_pair(EAvatarParts::Coat, coat));
		mParts.insert(std::make_pair(EAvatarParts::Neck, neck));
		mParts.insert(std::make_pair(EAvatarParts::Pants, pants));
		mParts.insert(std::make_pair(EAvatarParts::Belt, belt));
		mParts.insert(std::make_pair(EAvatarParts::Shoes, shoes));
		mParts.insert(std::make_pair(EAvatarParts::Weapon, weapon));

		std::wstring owner_name = owner->GetName();
		base->SetName(owner_name + L"base_avt");
		face->SetName(owner_name + L"face_avt");
		hair->SetName(owner_name + L"hair_avt");
		cap->SetName(owner_name + L"cap_avt");
		coat->SetName(owner_name + L"coat_avt");
		neck->SetName(owner_name + L"neck_avt");
		pants->SetName(owner_name + L"pants_avt");
		belt->SetName(owner_name + L"belt_avt");
		shoes->SetName(owner_name + L"shoes_avt");
		weapon->SetName(owner_name + L"weapon_avt");

		ELayerType layer_type = owner->layer_type;
		Scene* active_scene = SceneManager::GetActiveScene();
		active_scene->AddGameObject(layer_type, base);
		active_scene->AddGameObject(layer_type, face);
		active_scene->AddGameObject(layer_type, hair);
		active_scene->AddGameObject(layer_type, cap);
		active_scene->AddGameObject(layer_type, coat);
		active_scene->AddGameObject(layer_type, neck);
		active_scene->AddGameObject(layer_type, pants);
		active_scene->AddGameObject(layer_type, belt);
		active_scene->AddGameObject(layer_type, shoes);
		active_scene->AddGameObject(layer_type, weapon);

		std::shared_ptr<Transform> tf = owner->GetComponent<Transform>();
		tf->AddChild(base->GetComponent<Transform>());
		tf->AddChild(face->GetComponent<Transform>());
		tf->AddChild(hair->GetComponent<Transform>());
		tf->AddChild(cap->GetComponent<Transform>());
		tf->AddChild(coat->GetComponent<Transform>());
		tf->AddChild(neck->GetComponent<Transform>());
		tf->AddChild(pants->GetComponent<Transform>());
		tf->AddChild(belt->GetComponent<Transform>());
		tf->AddChild(shoes->GetComponent<Transform>());
		tf->AddChild(weapon->GetComponent<Transform>());
	}
	void AvatarScript::Update()
	{
		if (mUpdateFlag == true)
		{
			PlayPartsMotion();
			mUpdateFlag = false;
		}
	}
	void AvatarScript::LateUpdate()
	{
	}
	void AvatarScript::Render()
	{
	}
	void AvatarScript::CreatePartAni(EAvatarParts type, std::wstring npk_name, std::wstring pack_name, std::wstring set_name, UINT start, UINT end, float duration)
	{
		std::shared_ptr<Image> part = mParts[type].lock();
		std::shared_ptr<Animator> ani = part->GetComponent<Animator>();
		ani->Create(npk_name, pack_name, set_name, start, end, duration);
	}
	void AvatarScript::InsertStateAniInfo(EPlayerState state, EAvatarParts part, std::wstring ani_name)
	{
		mStateAnis[state] = {};
		mStateAnis[state].push_back(std::make_pair(part,ani_name));
	}
	void AvatarScript::PlayPartsMotion()
	{
		std::shared_ptr<PlayerScript> ps = owner->GetComponent<PlayerScript>();
		auto itr = mStateAnis.find(ps->player_state);
		if (itr == mStateAnis.end())
			return;
		for (auto& vec : itr->second)
		{
			EAvatarParts type = vec.first;
			std::wstring ani_name = vec.second;

			std::shared_ptr<Image> part = mParts[type].lock();
			std::shared_ptr<Animator> ani = part->GetComponent<Animator>();
			if (ps->player_state < EPlayerState::Skill)
				ani->PlayAnimation(ani_name, true);
			else
				ani->PlayAnimation(ani_name, false);
		}
	}
}