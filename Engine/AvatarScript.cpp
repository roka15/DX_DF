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
	AvatarScript::AvatarScript() :Script(EScriptType::Avatar)
	{
	}
	AvatarScript::AvatarScript(const AvatarScript& ref) : Script(ref)
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
		auto itr1 = mStateAnis.find(state);
		if (itr1 == mStateAnis.end())
			mStateAnis.insert(std::make_pair(state, std::map<EAvatarParts, std::vector<std::wstring>>()));
		auto itr2 = mStateAnis[state].find(part);
		if (itr2 == mStateAnis[state].end())
			mStateAnis[state].insert(std::make_pair(part, std::vector<std::wstring>()));

		mStateAnis[state][part].push_back(ani_name);
	}

	void AvatarScript::SettingRightMaterial()
	{
		std::shared_ptr<PlayerScript> ps = owner->parent->GetComponent<PlayerScript>();
		auto itr = mStateAnis.find(ps->player_state);
		if (itr == mStateAnis.end())
			return;
		for (auto& map : itr->second)
		{
			EAvatarParts type = map.first;

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
		for (auto& map : itr->second)
		{
			EAvatarParts type = map.first;

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
		for (auto& map : itr->second)
		{
			EAvatarParts type = map.first;
			std::wstring ani_name = map.second[0];

			std::shared_ptr<GameObject> part = mParts[type].lock();
			std::shared_ptr<Animator> ani = part->GetComponent<Animator>();
			if (ps->player_state < EPlayerState::OnePlay)
				ani->PlayAnimation(ani_name, true);
			else
				ani->PlayAnimation(ani_name, false);
		}
	}

	void AvatarScript::PlayPartsMotion(EPlayerState state, int index, bool flag)
	{
		auto itr = mStateAnis.find(state);
		if (itr == mStateAnis.end())
			return;
		for (auto& map : itr->second)
		{
			EAvatarParts type = map.first;
			std::wstring ani_name = map.second[index];

			std::shared_ptr<GameObject> part = mParts[type].lock();
			std::shared_ptr<Animator> ani = part->GetComponent<Animator>();
			ani->PlayAnimation(ani_name, flag);
		}
	}

	void AvatarScript::SetCompleteEventAnimation(EPlayerState state,int prev_index, int next_index)
	{
		auto itr = mStateAnis.find(state);
		if (itr == mStateAnis.end())
			return;
		for (auto& map : itr->second)
		{
			EAvatarParts type = map.first;
			std::wstring prev_name = map.second[prev_index];
			std::wstring next_name = map.second[next_index];

			ConnectNextAnimations(type, prev_name, next_name);
		}
	}

	void AvatarScript::SetCompleteEventAnimations(EPlayerState state)
	{
		auto itr = mStateAnis.find(state);
		if (itr == mStateAnis.end())
			return;
		for (auto& map : itr->second)
		{
			EAvatarParts type = map.first;
			size_t size = map.second.size();
			for (size_t i = 0; i < size-1; i++)
			{
				std::wstring prev_name = map.second[i];
				std::wstring next_name = map.second[i+1];

				ConnectNextAnimations(type, prev_name, next_name);
			}
			
		}
	}
	
	void AvatarScript::SetStartEventAnimation(EPlayerState state, int prev_index, std::function<void()> func)
	{
		auto itr = mStateAnis.find(state);
		if (itr == mStateAnis.end())
			return;

		for (auto& map : itr->second)
		{
			EAvatarParts type = map.first;
			size_t size = map.second.size();
			std::wstring name = map.second[prev_index];
			std::shared_ptr<Animator> ani = mParts[type].lock()->GetComponent<Animator>();
			ani->StartEvent(name) = func;
		}
	}

	void AvatarScript::CompleteEventAnimation(EPlayerState state, std::function<void()> func)
	{
		auto itr = mStateAnis.find(state);
		if (itr == mStateAnis.end())
			return;
		for (auto& map : itr->second)
		{
			EAvatarParts type = map.first;
			size_t size = map.second.size();
			std::wstring name = map.second[size - 1];
			std::shared_ptr<Animator> ani = mParts[type].lock()->GetComponent<Animator>();
			ani->CompleteEvent(name) = func;
		}
	}

	void AvatarScript::CompleteEventAnimation(EPlayerState state, int prev_index, std::function<void()> func)
	{
		auto itr = mStateAnis.find(state);
		if (itr == mStateAnis.end())
			return;

		for (auto& map : itr->second)
		{
			EAvatarParts type = map.first;
			size_t size = map.second.size();
			std::wstring name = map.second[prev_index];
			std::shared_ptr<Animator> ani = mParts[type].lock()->GetComponent<Animator>();
			ani->CompleteEvent(name) = func;
		}
	}

	void AvatarScript::EndEventAnimation(EPlayerState state, int index, std::function<void()> func)
	{
		auto itr = mStateAnis.find(state);
		if (itr == mStateAnis.end())
			return;

		for (auto& map : itr->second)
		{
			EAvatarParts type = map.first;
			size_t size = map.second.size();
			std::wstring name = map.second[index];
			std::shared_ptr<Animator> ani = mParts[type].lock()->GetComponent<Animator>();
			ani->EndEvent(name) = func;
		}
	}


	void AvatarScript::ConnectNextAnimations(EAvatarParts part, std::wstring prev_ani, std::wstring next_ani)
	{
		std::shared_ptr<Animator> ani = mParts[part].lock()->GetComponent<Animator>();
		Animator* ani_ptr = ani.get();
		ani->CompleteEvent(prev_ani) = std::bind([ani_ptr,next_ani]()->void{
			if (ani_ptr == nullptr)
				return;
			ani_ptr->PlayAnimation(next_ani,false); 
		});
	}

	void AvatarScript::StopAni()
	{
		for (auto part : mParts)
		{
			std::shared_ptr<Animator> ani = part.second.lock()->GetComponent<Animator>();
			ani->is_active = false;
		}
	}

	void AvatarScript::StartAni()
	{
		for (auto part : mParts)
		{
			std::shared_ptr<Animator> ani = part.second.lock()->GetComponent<Animator>();
			ani->is_active = true;
		}
	}

}