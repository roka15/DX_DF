#include "AvatarScript.h"
#include "Resources.h"
#include "Prefab.h"
#include "Image.h"
#include "SceneManager.h"
#include "Object.h"
#include "Transform.h"
#include "Animator.h"
#include "MeshRenderer.h"
#include "PlayerScript.h"
#include "PartScript.h"


namespace roka
{
	AvatarScript::AvatarScript():Script(EScriptType::Avatar)
	{
	}
	AvatarScript::AvatarScript(const AvatarScript& ref):Script(ref)
	{
		int a = 0;
		mParts;
	}
	void AvatarScript::Copy(Component* src)
	{
		Script::Copy(src);
	}
	AvatarScript::~AvatarScript()
	{
	}
	void AvatarScript::Initialize()
	{
		std::vector<std::shared_ptr<GameObject>> childs = owner->GetChilds();

		for (auto child : childs)
		{
			std::shared_ptr<PartScript> part_script = child->GetComponent<PartScript>();
			if (part_script == nullptr)
				continue;

			mParts.insert(std::make_pair(part_script->part_type, child));
		}
	}
	void AvatarScript::Update()
	{
	}
	void AvatarScript::LateUpdate()
	{
	}
	void AvatarScript::Render()
	{
	}
	void AvatarScript::CreatePartAni(EAvatarParts type, std::wstring npk_name, std::wstring pack_name, std::wstring set_name, UINT start, UINT end, float duration)
	{
		std::shared_ptr<GameObject> part = mParts[type].lock();
		std::shared_ptr<Animator> ani = part->GetComponent<Animator>();
		ani->Create(npk_name, pack_name, set_name, start, end, duration);
	}
	void AvatarScript::InsertStateAniInfo(EPlayerState state, EAvatarParts part, std::wstring ani_name)
	{
		mStateAnis[state] = {};
		mStateAnis[state].push_back(std::make_pair(part,ani_name));
	}

	void AvatarScript::SettingRightMaterial()
	{
		std::shared_ptr<PlayerScript> ps = owner->parent->GetComponent<PlayerScript>();
		auto itr = mStateAnis.find(ps->player_state);
		if (itr == mStateAnis.end())
			return;
		for (auto& vec : itr->second)
		{
			EAvatarParts type = vec.first;
			std::wstring ani_name = vec.second;

			std::shared_ptr<GameObject> part = mParts[type].lock();
			std::shared_ptr<MeshRenderer> mr = part->GetComponent<MeshRenderer>();
			mr->material->shader = Resources::Find<Shader>(L"AnimationShader");
		}
	}

	void AvatarScript::SettingLeftMaterial()
	{
		std::shared_ptr<PlayerScript> ps = owner->parent->GetComponent<PlayerScript>();
		auto itr = mStateAnis.find(ps->player_state);
		if (itr == mStateAnis.end())
			return;
		for (auto& vec : itr->second)
		{
			EAvatarParts type = vec.first;
			std::wstring ani_name = vec.second;

			std::shared_ptr<GameObject> part = mParts[type].lock();
			std::shared_ptr<MeshRenderer> mr = part->GetComponent<MeshRenderer>();
			mr->material->shader = Resources::Find<Shader>(L"VerticalInverterAnimationShader");
		}
	}
	
	void AvatarScript::PlayPartsMotion()
	{
		//if(owner->parent->GetName().compare(L"Player")==)
		std::shared_ptr<PlayerScript> ps = owner->parent->GetComponent<PlayerScript>();
		auto itr = mStateAnis.find(ps->player_state);
		if (itr == mStateAnis.end())
			return;
		for (auto& vec : itr->second)
		{
			EAvatarParts type = vec.first;
			std::wstring ani_name = vec.second;

			std::shared_ptr<GameObject> part = mParts[type].lock();
			std::shared_ptr<Animator> ani = part->GetComponent<Animator>();
			if (ps->player_state < EPlayerState::Skill)
				ani->PlayAnimation(ani_name, true);
			else
				ani->PlayAnimation(ani_name, false);
		}
	}
}