#pragma once
#include "MonsterScript.h"
namespace roka
{
	class NormalMonsterScript :
		public MonsterScript
	{
	protected:
		NormalMonsterScript();
		NormalMonsterScript(EScriptType type);
		NormalMonsterScript(EScriptType type, const UINT ActiveSkillStateMaxCnt,const Vector2 LeftColCenter,const Vector2 RightColCenter,const Vector2 LeftShooterPos,const Vector2 RightShooterPos,const Vector2 SkillSize,const Vector2 SkillColCenter);
		NormalMonsterScript(const NormalMonsterScript& ref);
		virtual void Copy(Component* src)override;

	public:
		virtual ~NormalMonsterScript()override {};

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(std::shared_ptr<Collider2D> other)override;
		virtual void OnCollisionStay(std::shared_ptr<Collider2D> other)override;
		virtual void OnCollisionExit(std::shared_ptr<Collider2D> other)override;

		virtual void Ready()override;
		virtual void Idle()override;
		virtual void Move()override;
		virtual void Attack()override;

		virtual void SetTargetPos(Vector2& outDir, Vector2& outTargetPos)override;


		virtual void LeftSetting()override;
		virtual void RightSetting()override;

		virtual void Skill01();

	private:
		friend class FactoryBase;
		friend class ScriptFactory;
	protected:
		const Vector2 mLeftShooterPos;
		const Vector2 mRightShooterPos;
		
		const Vector2 mSkillSize;
		const Vector2 mSkillColCenter;
	};
}


