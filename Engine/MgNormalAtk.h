#pragma once
#include "ISkill.h"
namespace roka
{
	class MgNormalAtk :
		public Skill
	{
	public:
		MgNormalAtk();
		virtual ~MgNormalAtk() {};

		virtual void Execute(std::shared_ptr<GameObject> caster)override;
		virtual void SpawnEffect(std::shared_ptr<GameObject> caster, std::wstring key)override;
		virtual void SpawnCollider(std::shared_ptr<GameObject> caster)override;
		virtual void SpawnCollider(Vector3 target)override;
		virtual void Sound(std::wstring key)override;
		virtual void OnAnimationFramEvent(std::shared_ptr<GameObject> caster, std::wstring frameEvent)override;
	};
}

