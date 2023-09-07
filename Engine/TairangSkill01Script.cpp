#include "TairangSkill01Script.h"

#include "RokaTime.h"

#include "Animator.h"
#include "Transform.h"
#include "MeshRenderer.h"
#include "Collider2D.h"

#include "TairangMonsterScript.h"

namespace roka
{
	TairangSkill01Script::TairangSkill01Script():DelayedCollisionSkillScript(EScriptType::SkillTairangType01)
	{
	}
	TairangSkill01Script::TairangSkill01Script(const TairangSkill01Script& ref):DelayedCollisionSkillScript(ref)
	{
	}
	void TairangSkill01Script::Copy(Component* src)
	{
		DelayedCollisionSkillScript::Copy(src);
		TairangSkill01Script* source = dynamic_cast<TairangSkill01Script*>(src);
		if (source == nullptr)
			return;
	}
	void TairangSkill01Script::Initialize()
	{
		mWarningFollowTime = 0.5;

		std::shared_ptr<Animator> ani = owner->GetComponent<Animator>();
		ani->Create(L"tairang", L"tairang_of_speed.img", L"tairang_Skill01_start", 27, 37, 0.1f);
		ani->Create(L"tairang", L"tairang_of_speed.img", L"tairang_Skill01_middle", 43, 45, 0.1f);
		ani->Create(L"tairang", L"tairang_of_speed.img", L"tairang_Skill01_end", 25, 27, 0.2f);

		Animator* animator = ani.get();
		ani->CompleteEvent(L"tairang_Skill01_start") = std::bind([animator]()->void {animator->PlayAnimation(L"tairang_Skill01_middle", false); });
		ani->CompleteEvent(L"tairang_Skill01_middle") = std::bind([animator]()->void {animator->PlayAnimation(L"tairang_Skill01_end", false); });
		ani->CompleteEvent(L"tairang_Skill01_end") = std::bind(&TairangSkill01Script::Exit, this);

		/*std::shared_ptr<Animation> animation = ani->FindAnimation(L"ellipse_warning2");
		Animation::AnimationEvent TimeEvent = {};
		TimeEvent.*/

		mStartKey = L"tairang_Skill01_start";
	}
	void TairangSkill01Script::Update()
	{
		DelayedCollisionSkillScript::Update();
	}
	void TairangSkill01Script::LateUpdate()
	{
		DelayedCollisionSkillScript::LateUpdate();
	}
	void TairangSkill01Script::Render()
	{
		DelayedCollisionSkillScript::Render();
	}
	void TairangSkill01Script::Play()
	{
		if (mTarget.expired() == true)
		{
			mTarget = owner->GetComponent<TairangMonsterScript>()->GetTarget();
		}
		DelayedCollisionSkillScript::Play();
	}
	void TairangSkill01Script::Exit()
	{
		DelayedCollisionSkillScript::Exit();
	}
	void TairangSkill01Script::CreateColliderObject()
	{
	}
	void TairangSkill01Script::CreateWarningObject()
	{
		DelayedCollisionSkillScript::CreateWarningObject();
		std::shared_ptr<Animator> warning_ani = mWarningObj->GetComponent<Animator>();
		warning_ani->Create(L"warning", L"warningfloor_circle500.img", L"ellipse_warning1", 0, 11, 0.1f);
	
		std::shared_ptr<Animation> animation = warning_ani->FindAnimation(L"ellipse_warning1");

		Animation::AnimationEvent TimeEvent = {};
		TimeEvent.mTime = 0.5f;
		TimeEvent.mNormalFunc = std::bind(&TairangSkill01Script::StopWarningAniEvent, this);
		
		animation->AddTimeLineEvent(TimeEvent);

		warning_ani->CompleteEvent(L"ellipse_warning1") = std::bind(&TairangSkill01Script::DeleteWarningObject,this);
		warning_ani->PlayAnimation(L"ellipse_warning1", false);
	}
	void TairangSkill01Script::DeleteWarningObject()
	{
		DelayedCollisionSkillScript::DeleteWarningObject();
	}
	void TairangSkill01Script::StopWarningAniEvent()
	{
		DelayedCollisionSkillScript::StopWarningAniEvent();

		Time::CallBackTimerInfo callBack = {};
		callBack.endTime = 1.5f;
		Time::RequestEvent(callBack, std::bind(&TairangSkill01Script::ContinueWarningAniEvent, this));
	}
}