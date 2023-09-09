#include "AvatarScript.h"
#include "Resources.h"
#include "Texture.h"
#include "Prefab.h"
#include "Image.h"
#include "SceneManager.h"
#include "Object.h"
#include "Transform.h"
#include "Animator.h"
#include "MeshRenderer.h"
#include "PlayerScript.h"
#include "PartScript.h"
#include "WeaponScript.h"


namespace roka
{
	AvatarScript::AvatarScript() :Script(EScriptType::Avatar)
	{
	}
	AvatarScript::AvatarScript(const AvatarScript& ref) : Script(ref)
	{
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
		Script::Initialize();
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
		std::shared_ptr<PartScript> partScript = part->GetComponent<PartScript>();
		partScript->CreateAni(npk_name, pack_name, set_name, start, end, duration);
	}
	void AvatarScript::CreatePartAni(EAvatarParts type, std::shared_ptr<Texture> atlas, std::wstring set_name, UINT start, UINT end, float duration)
	{
		std::shared_ptr<GameObject> part = mParts[type].lock();
		std::shared_ptr<PartScript> partScript = part->GetComponent<PartScript>();
		partScript->CreateAni(atlas, set_name, start, end, duration);
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
			std::shared_ptr<PartScript> partScript = part->GetComponent<PartScript>();
			partScript->Right();
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
			std::shared_ptr<PartScript> partScript = part->GetComponent<PartScript>();
			partScript->Left();
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
			std::shared_ptr<PartScript> partScript = part->GetComponent<PartScript>();
			if (ps->player_state < EPlayerState::OnePlay)
				partScript->PlayPartMotion(ani_name, true);
			else
				partScript->PlayPartMotion(ani_name, false);
		}
	}

	void AvatarScript::PlayPartsMotion(EPlayerState state, int index, bool flag)
	{
		auto itr = mStateAnis.find(state);
		if (itr == mStateAnis.end())
			return;
		for (auto& map : itr->second)
		{
			if (map.second.size() <= index)
				continue;
			EAvatarParts type = map.first;
			std::wstring ani_name = map.second[index];

			std::shared_ptr<GameObject> part = mParts[type].lock();
			std::shared_ptr<PartScript> partScript = part->GetComponent<PartScript>();
			partScript->PlayPartMotion(ani_name, flag);
		}
	}

	void AvatarScript::PlayPartsSprite(EPlayerState state, int index)
	{
		auto itr = mStateAnis.find(state);
		if (itr == mStateAnis.end())
			return;
		for (auto& map : itr->second)
		{
			EAvatarParts type = map.first;
			std::wstring ani_name = map.second[index];

			std::shared_ptr<GameObject> part = mParts[type].lock();
			std::shared_ptr<PartScript> partScript = part->GetComponent<PartScript>();
			partScript->PlayPartSprite(ani_name, index);
		}
	}

	void AvatarScript::SetCompleteEventAnimation(EPlayerState state,int prev_index, int next_index)
	{
		auto itr = mStateAnis.find(state);
		if (itr == mStateAnis.end())
			return;
		for (auto& map : itr->second)
		{
			if (map.second.size() == 1)
				continue;
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
			if (type == EAvatarParts::Base)
			{
				size_t size = map.second.size();
				std::wstring name = map.second[prev_index];
				std::shared_ptr<PartScript> partScript = mParts[type].lock()->GetComponent<PartScript>();
				partScript->ConnectEvent((UINT)Animator::EAniEventType::StartEvent, name, func);
				return;
			}
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
			if (type == EAvatarParts::Base)
			{
				size_t size = map.second.size();
				std::wstring name = map.second[size - 1];
				std::shared_ptr<PartScript> partScript = mParts[type].lock()->GetComponent<PartScript>();
				partScript->ConnectEvent((UINT)Animator::EAniEventType::CompleteEvent, name, func);
				return;
			}
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
			if (type == EAvatarParts::Base)
			{
				std::wstring name = map.second[prev_index];
				std::shared_ptr<PartScript> partScript = mParts[type].lock()->GetComponent<PartScript>();
				partScript->ConnectEvent((UINT)Animator::EAniEventType::CompleteEvent, name, func);
				return;
			}
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
			if (type == EAvatarParts::Base)
			{
				size_t size = map.second.size();
				std::wstring name = map.second[index];
				std::shared_ptr<PartScript> partScript = mParts[type].lock()->GetComponent<PartScript>();
				partScript->ConnectEvent((UINT)Animator::EAniEventType::End, name, func);
				return;
			}
		}
	}


	void AvatarScript::ConnectNextAnimations(EAvatarParts part, std::wstring prev_ani, std::wstring next_ani)
	{
		std::shared_ptr<PartScript> partScript = mParts[part].lock()->GetComponent<PartScript>();
		partScript->ConnectAnimations(prev_ani, next_ani);
	}

	void AvatarScript::StopAni()
	{
		for (auto part : mParts)
		{
			std::shared_ptr<PartScript> partScript = part.second.lock()->GetComponent<PartScript>();
			partScript->Stop();
		}
	}

	void AvatarScript::StartAni()
	{
		for (auto part : mParts)
		{
			std::shared_ptr<PartScript> partScript = part.second.lock()->GetComponent<PartScript>();
			partScript->Start();
		}
	}

	void AvatarScript::AddSpriteIndex()
	{
		for (auto part : mParts)
		{
			std::shared_ptr<PartScript> partScript = part.second.lock()->GetComponent<PartScript>();
			partScript->NextSprite();
		}
	}

}