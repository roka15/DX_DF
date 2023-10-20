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
#include "WeaponPartScript.h"
#include "SkinPartScript.h"
#include "Item.h"


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
	void AvatarScript::EquipPart(std::shared_ptr<GameObject> obj)
	{
	}
	void AvatarScript::EquipPart(EAvatarParts type, std::wstring name)
	{
		std::shared_ptr<GameObject> part = object::Instantiate<GameObject>(prefab::Prefabs[L"AniObject"]);//manager::PartManager::GetInstance()->Find(type, name);
		std::shared_ptr<Transform> tf = part->GetComponent<Transform>();
		std::shared_ptr<Transform> pTf = owner->parent->GetComponent<Transform>();
		tf->scale = pTf->scale;

		if (part == nullptr)
			return;

		std::shared_ptr<GameObject> obj = mParts[type].lock();
		if (obj != nullptr)
		{
			owner->SwapRemoveChild(obj, part);
		}
		else
		{
			owner->InsertChild(part, (UINT)type - 1);
		}
		RegisterPart(type, part);

	
		switch(type)
		{
		case EAvatarParts::Base:
		{
			std::shared_ptr<SkinPartScript> skin = part->AddScript<SkinPartScript>();
			skin->Create(L"baseskin", name);
			part->SetName(L"BasePart");
			break;
		}
		case EAvatarParts::Weapon:
			std::shared_ptr<WeaponPartScript> weapon = part->AddScript<WeaponPartScript>();
			weapon->Create(L"weapon", name);
			part->SetName(L"WeaponPart");
			part->GetComponent<WeaponPartScript>()->CreateSubObject();
			break;
		}
		std::shared_ptr<PartScript>partScript = part->GetComponent<PartScript>();
		partScript->SetEvent();

	}
    void AvatarScript::EquipPart(EAvatarParts type, std::vector<AvatarSubPartInfo> infos)
    {
		std::shared_ptr<GameObject> part = object::Instantiate<GameObject>(prefab::Prefabs[L"AniObject"]);//manager::PartManager::GetInstance()->Find(type, name);
		std::shared_ptr<Transform> tf = part->GetComponent<Transform>();
		std::shared_ptr<Transform> pTf = owner->parent->GetComponent<Transform>();
		tf->scale = pTf->scale;

		if (part == nullptr)
			return;

		std::shared_ptr<GameObject> obj = mParts[type].lock();
		if (obj != nullptr)
		{
			owner->SwapRemoveChild(obj, part);
		}
		else
		{
			owner->InsertChild(part, (UINT)type - 1);
		}
		RegisterPart(type, part);
		for (auto info : infos)
		{
			info.field
		}
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
			if (part.second.expired() == true)
				continue;
			std::shared_ptr<PartScript> partScript = part.second.lock()->GetComponent<PartScript>();
			if (partScript == nullptr)
			{
				SugPartFunc(part.second.lock(), std::bind(&AvatarScript::RightMaterial,this, std::placeholders::_1));
			}
			else
			partScript->Right();
		}
	}

	void AvatarScript::RightMaterial(std::shared_ptr<PartScript> script)
	{
		script->Right();
	}

	void AvatarScript::SettingLeftMaterial()
	{
		std::shared_ptr<PlayerScript> ps = owner->parent->GetComponent<PlayerScript>();
		for (auto part : mParts)
		{
			if (part.second.expired() == true)
				continue;
			std::shared_ptr<PartScript> partScript = part.second.lock()->GetComponent<PartScript>();
			if (partScript == nullptr)
			{
				SugPartFunc(part.second.lock(), std::bind(&AvatarScript::LeftMaterial, this, std::placeholders::_1));
			}
			else
			partScript->Left();
		}
	}

	void AvatarScript::LeftMaterial(std::shared_ptr<PartScript> script)
	{
		script->Left();
	}

	void AvatarScript::PlayPartsMotion()
	{
		std::shared_ptr<PlayerScript> ps = owner->parent->GetComponent<PlayerScript>();
		StartAni();
		for (auto part : mParts)
		{
			if (part.second.expired() == true)
				continue;
			std::shared_ptr<PartScript> script = part.second.lock()->GetComponent<PartScript>();
			if (script == nullptr)
			{
				if (part.second.lock()->GetChildCont() != 0)
				{
					std::vector<std::shared_ptr<PartScript>> scripts = part.second.lock()->GetChilds<PartScript>();
					for (auto sc : scripts)
					{
						StatePlay(sc, ps->player_state);
					}
				}
				else
					return;
			}
			else
			{
				StatePlay(script,ps->player_state);
			}
			
		}

	}
	void AvatarScript::SkillPartsMotion(std::wstring key)
	{
		std::shared_ptr<PlayerScript> ps = owner->parent->GetComponent<PlayerScript>();
		StartAni();
		for (auto part : mParts)
		{
			if (part.second.expired() == true)
				continue;
			std::shared_ptr<PartScript> script = part.second.lock()->GetComponent<PartScript>();
			if (ps->player_state == EPlayerState::Skill)
			{
				script->Skill(key);
			}
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
			if (part.second.expired() == true)
				continue;
			std::shared_ptr<PartScript> partScript = part.second.lock()->GetComponent<PartScript>();
			partScript->Stop();
		}
		mbAniStop = true;
	}

	void AvatarScript::StartAni()
	{
		for (auto part : mParts)
		{
			if (part.second.expired() == true)
				continue;
			std::shared_ptr<PartScript> partScript = part.second.lock()->GetComponent<PartScript>();
			if (partScript != nullptr)
			{
				partScript->Start();
			}
			else if (part.second.lock()->GetChildCont() != 0)
			{
				std::vector<std::shared_ptr<PartScript>> scripts = part.second.lock()->GetChilds<PartScript>();
				for (auto script : scripts)
				{
					script->Start();
				}
			}
		}
		mbAniStop = false;
	}

	void AvatarScript::AddSpriteIndex()
	{
		for (auto part : mParts)
		{
			if (part.second.expired() == true)
				continue;
			std::shared_ptr<PartScript> partScript = part.second.lock()->GetComponent<PartScript>();
			partScript->NextSprite();
		}
	}

	void AvatarScript::SugPartFunc(std::shared_ptr<GameObject> obj, std::function<void(std::shared_ptr<PartScript>)> func)
	{
		if (obj == nullptr)
			return;
		if (obj->GetChildCont() != 0)
		{
			std::vector<std::shared_ptr<PartScript>> scripts = obj->GetChilds<PartScript>();
			for (auto script : scripts)
			{
				func(script);
			}
		}
	}

	void AvatarScript::StatePlay(std::shared_ptr<PartScript> script, EPlayerState state)
	{
		switch (state)
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