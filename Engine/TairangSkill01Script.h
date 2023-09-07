#pragma once
#include "DelayedCollisionSkillScript.h"

namespace roka
{
	class TairangSkill01Script:public DelayedCollisionSkillScript
	{
	protected:
		TairangSkill01Script();
		TairangSkill01Script(const TairangSkill01Script& ref);
		virtual void Copy(Component* src)override;
	public:
		virtual ~TairangSkill01Script() {}

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(std::shared_ptr<Collider2D> other) {}
		virtual void OnCollisionStay(std::shared_ptr<Collider2D> other) {}
		virtual void OnCollisionExit(std::shared_ptr<Collider2D> other) {}

		virtual void Play();
		virtual void Exit();

		virtual void StartStartEvent();
		virtual void MiddleStartEvent();
		virtual void EndStartEvent();
		virtual void StartCompleteEvent();
		virtual void MiddleCompleteEvent();
		virtual void EndCompleteEvent();

		virtual void CreateColliderObject()override;
		virtual void CreateWarningObject();
		void CreateStartEftObject();

		virtual void DeleteWarningObject();
		void DeleteStartEftObject();

		virtual void StopWarningAniEvent();

	private:
		friend class FactoryBase;
		friend class ScriptFactory;
	protected:
		std::vector<std::shared_ptr<GameObject>> mStartEftObject;
		
	};
}


