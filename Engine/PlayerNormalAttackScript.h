#pragma once
#include "SkillScript.h"
namespace roka
{
	class PlayerNormalAttackScript :
		public SkillScript
	{
	protected:
		PlayerNormalAttackScript();
		PlayerNormalAttackScript(EScriptType type);
		PlayerNormalAttackScript(const PlayerNormalAttackScript& ref);
		virtual void Copy(Component* src);
	public:
		virtual ~PlayerNormalAttackScript() {};

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(std::shared_ptr<Collider2D> other) {}
		virtual void OnCollisionStay(std::shared_ptr<Collider2D> other) {}
		virtual void OnCollisionExit(std::shared_ptr<Collider2D> other) {}

		virtual void Play();
		virtual void Exit();

		virtual void Start() {}
		virtual void Middle() {}
		virtual void End() {}

		virtual void CreateColliderObject() {}
		virtual void DeleteColliderObject() {}
	private:
		friend class FactoryBase;
		friend class ScriptFactory;
	protected:
		std::vector<std::function<void()>> mAtkFunc;
		int mAtkIndex;
		double mCurTime;
		double mKeyDownTime;
		const double mConditionSec;
	};
}


