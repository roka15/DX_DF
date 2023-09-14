#include "AvatarScript.h"
#include "Resources.h"
#include "Texture.h"
#include "Prefab.h"
#include "Image.h"
#include "SceneManager.h"
#include "Object.h"
#include "PartManager.h"

#include "Transform.h"
#include "Animator.h"
#include "MeshRenderer.h"
#include "PlayerScript.h"
#include "PartScript.h"



namespace roka
{
	AvatarScript::AvatarScript() :Script(EScriptType::Avatar),
		mbAniStop(false)
	{
	}
	AvatarScript::AvatarScript(const AvatarScript& ref) : Script(ref),
		mbAniStop(false)
	{
	}
	void AvatarScript::Copy(Component* src)
	{
		Script::Copy(src);
		mbAniStop = false;
	}
	AvatarScript::~AvatarScript()
	{
	}
	void AvatarScript::Initialize()
	{
		Script::Initialize();
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
	void AvatarScript::EquipPart(EAvatarParts type, std::wstring name)
	{
		std::shared_ptr<GameObject> part = manager::PartManager::GetInstance()->Find(type, name);
		if (part == nullptr)
			return;
		std::shared_ptr<PartScript>partScript = part->GetComponent<PartScript>();
		partScript->SetEvent();

		switch (partScript->part_type)
		{
		case EAvatarParts::Base:
			part->SetName(L"BasePart");
			break;
		case EAvatarParts::Weapon:
			part->SetName(L"WeaponPart");
			break;
		}
		
		std::shared_ptr<GameObject> obj = mParts[type].lock();
		if (obj != nullptr)
		{
			owner->SwapRemoveChild(obj, part);
		}
		else
		{
			owner->InsertChild(part,(UINT)type -1);
		}
		RegisterPart(type, part);
	}
	void AvatarScript::CreatePartAni(EAvatarParts type, std::wstring npk_name, std::wstring pack_name, std::wstring set_name, UINT start, UINT end, float duration)
	{
	}
	void AvatarScript::CreatePartAni(EAvatarParts type, std::shared_ptr<Texture> atlas, std::wstring set_name, UINT start, UINT end, float duration)
	{
	}
	void AvatarScript::InsertStateAniInfo(EPlayerState state, EAvatarParts part, std::wstring ani_name)
	{
	}

	void AvatarScript::SettingRightMaterial()
	{
		std::shared_ptr<PlayerScript> ps = owner->parent->GetComponent<PlayerScript>();
		for (auto part : mParts)
		{
			std::shared_ptr<PartScript> partScript = part.second.lock()->GetComponent<PartScript>();
			partScript->Right();
		}
	}

	void AvatarScript::SettingLeftMaterial()
	{
		std::shared_ptr<PlayerScript> ps = owner->parent->GetComponent<PlayerScript>();
		for (auto part : mParts)
		{
			std::shared_ptr<PartScript> partScript = part.second.lock()->GetComponent<PartScript>();
			partScript->Left();
		}
	}

	void AvatarScript::PlayPartsMotion()
	{
		std::shared_ptr<PlayerScript> ps = owner->parent->GetComponent<PlayerScript>();
		StartAni();
		for (auto part : mParts)
		{
			std::shared_ptr<PartScript> script = part.second.lock()->GetComponent<PartScript>();
			switch (ps->player_state)
			{
			case EPlayerState::Idle:
				script->Idle();
				break;
			case EPlayerState::Walk:
				script->Walk();
				break;
			case EPlayerState::Run:
				script->Run();
				break;
			case EPlayerState::Jump:
				script->Jump();
				break;
			case EPlayerState::JumpRun:
				script->JumpDash();
				break;
			case EPlayerState::FallDown:
				script->Fall();
				break;
			case EPlayerState::Landing:
				script->Landing();
				break;
			case EPlayerState::Standing:
				script->Standing();
				break;
			case EPlayerState::Stagger:
				script->Stagger();
				break;
			case EPlayerState::Down:
				script->Down();
				break;
			case EPlayerState::NomalAtk:
				script->NormalAtk();
				break;
			}
		}
	
	}

	void AvatarScript::PlayPartsMotion(EPlayerState state, int index, bool flag)
	{
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

	void AvatarScript::SetCompleteEventAnimation(EPlayerState state, int prev_index, int next_index)
	{
	}

	void AvatarScript::SetCompleteEventAnimations(EPlayerState state)
	{
	}

	void AvatarScript::SetStartEventAnimation(EPlayerState state, int prev_index, std::function<void()> func)
	{
	}

	void AvatarScript::CompleteEventAnimation(EPlayerState state, std::function<void()> func)
	{
	}

	void AvatarScript::CompleteEventAnimation(EPlayerState state, int prev_index, std::function<void()> func)
	{
	}

	void AvatarScript::EndEventAnimation(EPlayerState state, int index, std::function<void()> func)
	{
	}


	void AvatarScript::ConnectNextAnimations(EAvatarParts part, std::wstring prev_ani, std::wstring next_ani)
	{
	}

	void AvatarScript::StopAni()
	{
		for (auto part : mParts)
		{
			std::shared_ptr<PartScript> partScript = part.second.lock()->GetComponent<PartScript>();
			partScript->Stop();
		}
		mbAniStop = true;
	}

	void AvatarScript::StartAni()
	{
		for (auto part : mParts)
		{
			std::shared_ptr<PartScript> partScript = part.second.lock()->GetComponent<PartScript>();
			partScript->Start();
		}
		mbAniStop = false;
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