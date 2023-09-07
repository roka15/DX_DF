#pragma once
#include "Script.h"
#include "RokaMath.h"
namespace roka
{
	using namespace math;

	class SkillScript;

	class MonsterScript :
		public Script
	{
	protected:
		MonsterScript();
		MonsterScript(EScriptType type);
		MonsterScript(EScriptType type,const UINT ActiveSkillStateMaxCnt,const Vector2 leftColCenter,const Vector2 rightColCenter);
		MonsterScript(const MonsterScript& ref);
		virtual void Copy(Component* src)override;
	public:
		virtual ~MonsterScript();

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
	
		virtual void Skill();
		
		void SetTarget(std::shared_ptr<GameObject> target) { mTarget = target; }
		std::shared_ptr<GameObject> GetTarget() { return mTarget.lock(); }
		void EnableNextState() { mbNextState = true; }
		void DisableNextState() { mbNextState = false; }

		virtual void LeftSetting();
		virtual void RightSetting();

		virtual void SetTargetPos(Vector2& outDir,Vector2& outTargetPos);

		EDir4Type GetDir() { return mCurDirType; }
		EMonsterState GetState() { return mState; }
		GET_PROPERTY(GetState) EMonsterState state;
	private:
		friend class FactoryBase;
		friend class ScriptFactory;
	protected:
		std::weak_ptr<GameObject> mTarget;
		EMonsterState mState;

		const Vector2 mLeftColCenter;
		const Vector2 mRightColCenter;

		

		double mNextStateCoolTime;
		float mSpeed;
		bool mbNextState;
		EDir4Type mCurDirType;

		const UINT mSkillStateCntMax;
		UINT mSkillStateCnt;
		UINT mExcuteSkillIndex;

		std::vector<std::shared_ptr<SkillScript>> mSkillList;
	};
}


