#pragma once
#include "ISkill.h"
namespace roka
{
    class SpiderNormalAtk :
        public Skill
    {
    public:
        SpiderNormalAtk(const UINT& damage);
        virtual ~SpiderNormalAtk();
		virtual void Execute(std::shared_ptr<GameObject> caster) override;
		virtual void SpawnEffect(std::shared_ptr<GameObject> caster, std::wstring key)override;
		virtual void DeSpawnEffect(std::shared_ptr<GameObject> caster, std::wstring key)override;
		virtual void SpawnCollider(std::shared_ptr<GameObject> caster) override;
		virtual void DeSpawnCollider(std::shared_ptr<GameObject> caster) override;
		virtual void EnableCollision(std::shared_ptr<GameObject> caster) override;
		virtual void DisableCollision(std::shared_ptr<GameObject> caster) override;
		virtual void Left(std::shared_ptr<GameObject> caster) override;
		virtual void Right(std::shared_ptr<GameObject> caster) override;
		virtual void Sound(std::wstring key) override;
		virtual void End(std::shared_ptr<GameObject> caster) override;
		virtual void OnAnimationFramEvent(std::shared_ptr<GameObject> caster, std::wstring frameEvent) override;

		virtual void OnCollisionEnter(std::shared_ptr<GameObject> caster, std::shared_ptr<GameObject> target) override;
		virtual void OnCollisionStay(std::shared_ptr<GameObject> caster, std::shared_ptr<GameObject> target) override;
		virtual void OnCollisionExit(std::shared_ptr<GameObject> caster, std::shared_ptr<GameObject> target) override;
		virtual void Release()override;
    protected:
    };
}


