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

		virtual void OnCollisionEnter(std::shared_ptr<Collider2D> other);
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
		void CreateMiddleEftObject();
		void CreateEndEftObject();

		virtual void DeleteWarningObject();
		void DeleteStartEftObject();
		void DeleteMiddleEftObject();
		void DeleteEndEftObject();

		virtual void StopWarningAniEvent();

		void PlayStartEftObject(int index,std::wstring key);
		void Jump();
		void Hide();
		void Explosion();
		void Landing();
	private:
		friend class FactoryBase;
		friend class ScriptFactory;
	protected:
		std::vector<std::shared_ptr<GameObject>> mStartEftObject;
		std::vector<std::shared_ptr<GameObject>> mMiddleEftObject;
		std::vector<std::shared_ptr<GameObject>> mEndEftObject;
	};
}


