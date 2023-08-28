#include "MonsterSkillScript.h"

#include "GameObject.h"

#include "Collider2D.h"

#include "MonsterScript.h"
#include "SpiderMonsterScript.h"

namespace roka
{
	MonsterSkillScript::MonsterSkillScript() :SkillScript(EScriptType::SkillMonster)
	{
	}
	MonsterSkillScript::MonsterSkillScript(MonsterSkillScript& ref) : SkillScript(ref)
	{
	}
	void MonsterSkillScript::Copy(Component* src)
	{
		SkillScript::Copy(src);
		MonsterSkillScript* source = dynamic_cast<MonsterSkillScript*>(src);
		if (source == nullptr)
			return;
	}
	void MonsterSkillScript::Update()
	{
		std::shared_ptr<GameObject> parrent = owner->GetParent();
		if (parrent == nullptr)return;
		std::shared_ptr<MonsterScript> monster = parrent->GetComponent<MonsterScript>();
		if (monster->state != MonsterScript::EMonsterState::Skill)
		{
			std::shared_ptr<Collider2D> col = owner->GetComponent<Collider2D>();
			//test
			if (col != nullptr)
				col->is_active = false;
		}
	}
	void MonsterSkillScript::OnCollisionExit(std::shared_ptr<Collider2D> other)
	{
	}
	void MonsterSkillScript::Play(EDir4Type dir)
	{
		SkillScript::Play(dir);
		std::shared_ptr<GameObject> parrent = owner->GetParent();
		if (parrent == nullptr)return;
		std::shared_ptr<MonsterScript> monster = parrent->GetComponent<MonsterScript>();
		monster->DisableNextState();
	}
	void MonsterSkillScript::End()
	{
		SkillScript::End();
		std::shared_ptr<GameObject> parrent = owner->GetParent();
		if (parrent == nullptr)return;
		std::shared_ptr<MonsterScript> monster = parrent->GetComponent<MonsterScript>();
			monster->SkillEnd();
	}
}