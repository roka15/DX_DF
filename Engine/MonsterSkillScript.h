#pragma once
#include "SkillScript.h"
namespace roka
{
	class MonsterSkillScript :
		public SkillScript
	{
	protected:
		MonsterSkillScript();
		MonsterSkillScript(MonsterSkillScript& ref);
		void Copy(Component* src);
	public:
		virtual ~MonsterSkillScript() {}
		virtual void Update()override;
		virtual void OnCollisionExit(std::shared_ptr<Collider2D> other)override;
		virtual void Play(EDir4Type dir)override;
		virtual void End()override;
	private:
		friend class FactoryBase;
		friend class ScriptFactory;
	};
}


