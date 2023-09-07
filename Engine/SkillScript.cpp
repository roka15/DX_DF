#include "SkillScript.h"
#include "RokaTime.h"
#include "GameObject.h"

#include "Animator.h"
#include "MeshRenderer.h"
#include "Collider2D.h"
#include "Transform.h"

#include "MonsterScript.h"

namespace roka
{
	SkillScript::SkillScript() :Script(EScriptType::SkillBase),
		mStunType(EStunState::None),
		mStartKey(L"")
	{
	}
	SkillScript::SkillScript(EScriptType type) : Script(type),
		mStunType(EStunState::None),
		mStartKey(L"")
	{
	}
	SkillScript::SkillScript(const SkillScript& ref) : Script(ref)
	{
		mStunType = ref.mStunType;
	}
	void SkillScript::Copy(Component* src)
	{
		SkillScript* source = dynamic_cast<SkillScript*>(src);
		mStunType = source->mStunType;
		mStartKey = source->mStartKey;
	}
	SkillScript::~SkillScript()
	{
	}
	void SkillScript::Initialize()
	{
	}
	void SkillScript::Update()
	{
	}
	void SkillScript::LateUpdate()
	{
	}
	void SkillScript::Render()
	{
	}
	void SkillScript::Play()
	{
		std::shared_ptr<Animator> ani = owner->GetComponent<Animator>();
		//test
		if (ani != nullptr)
			if(mStartKey.size()!=0)
			ani->PlayAnimation(mStartKey, false);

		std::shared_ptr<MonsterScript> monsterScript = owner->GetComponent<MonsterScript>();
		monsterScript->DisableNextState();
	}
	void SkillScript::Exit()
	{
		std::shared_ptr<MonsterScript> monsterScript = owner->GetComponent<MonsterScript>();
		monsterScript->EnableNextState();
	}
}