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

		virtual void Start()override {}
		virtual void Middle()override {}
		virtual void End()override {}

		virtual void CreateColliderObject()override;
		virtual void CreateWarningObject();

		virtual void DeleteWarningObject();

		virtual void StopWarningAniEvent();

	private:
		friend class FactoryBase;
		friend class ScriptFactory;
	protected:
	};
}


