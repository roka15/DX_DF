#pragma once
#include "Script.h"
namespace roka
{
	class MonsterScript :
		public Script
	{
	protected:
		MonsterScript();
		MonsterScript(const MonsterScript& ref);
		void Copy(Component* src);
	public:
		~MonsterScript();

		enum class EMonsterState
		{
			Ready,
			Idle,
			Walk,
			Skill,
			Death,
			End,
		};
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(std::shared_ptr<Collider2D> other)override;
		virtual void OnCollisionStay(std::shared_ptr<Collider2D> other)override;
		virtual void OnCollisionExit(std::shared_ptr<Collider2D> other)override;
        
		static void RandomState(std::weak_ptr<void> ptr);

		virtual void Ready();
		virtual void Idle();
		virtual void Move();

		void SetTarget(std::shared_ptr<GameObject> target) { mTarget = target; }

	private:
		friend class FactoryBase;
		friend class ScriptFactory;
	protected:
		std::weak_ptr<GameObject> mTarget;
		EMonsterState mState;

		double mNextStateCoolTime;
		float mSpeed;
	};
}


