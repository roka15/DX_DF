#pragma once
#include "IAnimationFramEvent.h"

namespace roka
{
	using namespace math;
	class GameObject;
	class ISkill: public IAnimationFramEvent
	{
	public:
		virtual void Execute(std::shared_ptr<GameObject> caster) = 0;
		virtual void SpawnEffect(std::shared_ptr<GameObject> caster, std::wstring key)=0;
		virtual void SpawnCollider(std::shared_ptr<GameObject> caster)=0;
		virtual void SpawnCollider(Vector3 target) = 0;
		virtual void Sound(std::wstring key) = 0;
		virtual void OnAnimationFramEvent(std::shared_ptr<GameObject> caster, std::wstring frameEvent)=0;
	protected:
	};
	class Skill : public ISkill
	{
	public:
		Skill() { mbCallbackEvent = false; }
		virtual ~Skill() {}
		virtual void Execute(std::shared_ptr<GameObject> caster) = 0;
		virtual void SpawnEffect(std::shared_ptr<GameObject> caster, std::wstring key) = 0;
		virtual void SpawnCollider(std::shared_ptr<GameObject> caster) = 0;
		virtual void SpawnCollider(Vector3 target) = 0;
		virtual void Sound(std::wstring key) = 0;
		virtual void OnAnimationFramEvent(std::shared_ptr<GameObject> caster, std::wstring frameEvent) = 0;
	protected:
		bool mbCallbackEvent;
	};
}


