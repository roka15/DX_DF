#pragma once
#include "SkillScript.h"
namespace roka
{
	class DelayedCollisionSkillScript :
		public SkillScript
	{
	protected:
		DelayedCollisionSkillScript();
		DelayedCollisionSkillScript(EScriptType type);
		DelayedCollisionSkillScript(const DelayedCollisionSkillScript& ref);
		virtual void Copy(Component* src)override;
	public:
		virtual~ DelayedCollisionSkillScript() {}

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(std::shared_ptr<Collider2D> other) {}
		virtual void OnCollisionStay(std::shared_ptr<Collider2D> other) {}
		virtual void OnCollisionExit(std::shared_ptr<Collider2D> other) {}

		virtual void Play();
		virtual void Exit();

		virtual void Start()override {}
		virtual void Middle()override {}
		virtual void End()override {}

		virtual void CreateColliderObject()override;
		virtual void CreateWarningObject();

		virtual void DeleteColliderObject()override;
		virtual void DeleteWarningObject();

		virtual void StopWarningAniEvent();
		virtual void ContinueWarningAniEvent();

		void MoveWarningObject();
	private:
		friend class FactoryBase;
		friend class ScriptFactory;
	protected:
		std::weak_ptr<GameObject> mTarget;
		std::shared_ptr<GameObject> mWarningObj;
		double mWarningFollowTime;
		double mWarningEnableTime;

		Vector3 mWarningSize;
		Vector3 mWarningCenter;

		Vector3 mPos;
	};
}


