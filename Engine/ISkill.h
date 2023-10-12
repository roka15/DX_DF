#pragma once
#include "IAnimationFramEvent.h"
#include "ICollisionListener.h"
namespace roka
{
	using namespace math;
	class GameObject;
	class ISkill: public IAnimationFramEvent, public ICollisionListener
	{
	public:
		virtual void Execute(std::shared_ptr<GameObject> caster) = 0;
		virtual void SpawnEffect(std::shared_ptr<GameObject> caster, std::wstring key)=0;
		virtual void DeSpawnEffect(std::shared_ptr<GameObject> caster, std::wstring key) = 0;
		virtual void SpawnCollider(std::shared_ptr<GameObject> caster)=0;
		virtual void DeSpawnCollider(std::shared_ptr<GameObject> caster) = 0;
		virtual void EnableCollision(std::shared_ptr<GameObject> caster) = 0;
		virtual void DisableCollision(std::shared_ptr<GameObject> caster) = 0;
		virtual void Left(std::shared_ptr<GameObject> caster) = 0;
		virtual void Right(std::shared_ptr<GameObject> caster) = 0;

		virtual void Sound(std::wstring key) = 0;
		virtual void End(std::shared_ptr<GameObject> caster) = 0;
		virtual void OnAnimationFramEvent(std::shared_ptr<GameObject> caster, std::wstring frameEvent)=0;
		
		virtual void OnCollisionEnter(std::shared_ptr<GameObject> caster, std::shared_ptr<GameObject> target) = 0;
		virtual void OnCollisionStay(std::shared_ptr<GameObject> caster, std::shared_ptr<GameObject> target) = 0;
		virtual void OnCollisionExit(std::shared_ptr<GameObject> caster, std::shared_ptr<GameObject> target) = 0;
		virtual void SetCollisionListener(std::shared_ptr<GameObject>& obj) = 0;

		virtual void Release()=0;
	protected:
	};
	class Skill : public ISkill
	{
	public:
		Skill(const UINT& damage):mDamage(damage) { mbCallbackEvent = false; }
		virtual ~Skill() {}
		virtual void Execute(std::shared_ptr<GameObject> caster)override;
		virtual void SpawnEffect(std::shared_ptr<GameObject> caster, std::wstring key) = 0;
		virtual void DeSpawnEffect(std::shared_ptr<GameObject> caster, std::wstring key) = 0;
		virtual void SpawnCollider(std::shared_ptr<GameObject> caster) = 0;
		virtual void DeSpawnCollider(std::shared_ptr<GameObject> caster) = 0;
		virtual void EnableCollision(std::shared_ptr<GameObject> caster) = 0;
		virtual void DisableCollision(std::shared_ptr<GameObject> caster) = 0;
		virtual void Left(std::shared_ptr<GameObject> caster) = 0;
		virtual void Right(std::shared_ptr<GameObject> caster) = 0;
		virtual void Sound(std::wstring key) = 0;
		virtual void End(std::shared_ptr<GameObject> caster) = 0;
		virtual void OnAnimationFramEvent(std::shared_ptr<GameObject> caster, std::wstring frameEvent) = 0;

		virtual void OnCollisionEnter(std::shared_ptr<GameObject> caster, std::shared_ptr<GameObject> target) = 0;
		virtual void OnCollisionStay(std::shared_ptr<GameObject> caster, std::shared_ptr<GameObject> target) = 0;
		virtual void OnCollisionExit(std::shared_ptr<GameObject> caster, std::shared_ptr<GameObject> target) = 0;
		virtual void SetCollisionListener(std::shared_ptr<GameObject>& obj)override;
		virtual void Release() = 0;
	protected:
		bool mbCallbackEvent;
		const UINT mDamage;
	};
}


