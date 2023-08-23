#pragma once
#include "Script.h"
#include "RokaMath.h"
namespace roka
{
	using namespace math;
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
		virtual void Attack();

		void Skill01();
		
		void SetTarget(std::shared_ptr<GameObject> target) { mTarget = target; }

		void EnableNextState() { mbNextState = true; }
		void DisableNextState() { mbNextState = false; }
	public:
		static void SetColCenter(Vector2 left, Vector2 right) { mLeftColCenter = left; mRightColCenter = right; }
		static void SetShooterPos(Vector2 left, Vector2 right) { mLeftShooterPos = left; mRightShooterPos = right; }
	private:
		friend class FactoryBase;
		friend class ScriptFactory;
	protected:
		std::weak_ptr<GameObject> mTarget;
		EMonsterState mState;

		static Vector2 mLeftColCenter;
		static Vector2 mRightColCenter;

		static Vector2 mLeftShooterPos;
		static Vector2 mRightShooterPos;

		double mNextStateCoolTime;
		float mSpeed;
		bool mbNextState;
		EDir4Type mCurDirType;
	};
}


