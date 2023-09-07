#include "TairangSkill01Script.h"

#include "RokaTime.h"
#include "AnimationObjectPool.h"
#include "GameObject.h"

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
		mWarningSize = Vector3(2.5f, 2.0f, 1.0f);
		mWarningCenter = Vector3(0.0f, -0.32f, 0.0f);

		std::shared_ptr<Animator> ani = owner->GetComponent<Animator>();
		ani->Create(L"tairang", L"tairang_of_speed.img", L"tairang_Skill01_start", 27, 37, 0.1f);
		ani->Create(L"tairang", L"tairang_of_speed.img", L"tairang_Skill01_middle", 43, 45, 1.5f);
		ani->Create(L"tairang", L"tairang_of_speed.img", L"tairang_Skill01_end", 25, 27, 0.2f);

		Animator* animator = ani.get();
		ani->StartEvent(L"tairang_Skill01_start") = std::bind(&TairangSkill01Script::StartStartEvent, this);
		ani->CompleteEvent(L"tairang_Skill01_start") = std::bind(&TairangSkill01Script::StartCompleteEvent,this);
		ani->CompleteEvent(L"tairang_Skill01_middle") = std::bind(&TairangSkill01Script::MiddleCompleteEvent,this);
		ani->CompleteEvent(L"tairang_Skill01_end") = std::bind(&TairangSkill01Script::EndCompleteEvent, this);

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
	void TairangSkill01Script::StartStartEvent()
	{
		CreateStartEftObject();
	}
	void TairangSkill01Script::MiddleStartEvent()
	{
		/*std::shared_ptr<TairangMonsterScript> monster = owner->GetComponent<TairangMonsterScript>();
		monster->Skill01SetPos();*/
		
		std::shared_ptr<Animator> ani = owner->GetComponent<Animator>();
		ani->PlayAnimation(L"tairang_Skill01_middle", false);
		DeleteStartEftObject();
	}
	void TairangSkill01Script::EndStartEvent()
	{
	}
	void TairangSkill01Script::StartCompleteEvent()
	{
		Time::CallBackTimerInfo callBack = {};
		callBack.endTime = 2.0f;
		Time::RequestEvent(callBack, std::bind(&TairangSkill01Script::MiddleStartEvent, this));
	}
	void TairangSkill01Script::MiddleCompleteEvent()
	{
		std::shared_ptr<Animator> ani = owner->GetComponent<Animator>();
		ani->PlayAnimation(L"tairang_Skill01_end", false);
	}
	void TairangSkill01Script::EndCompleteEvent()
	{
		Exit();
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
	void TairangSkill01Script::CreateStartEftObject()
	{
		std::shared_ptr<Animator> owner_ani = owner->GetComponent<Animator>();
		std::shared_ptr<Animation> animation = owner_ani->FindAnimation(L"tairang_Skill01_start");

		pool::AnimationObjectPool* pool = pool::AnimationObjectPool::GetInstance();
		std::shared_ptr<GameObject> Eft01 = pool->GetPool(L"AniEftObject")->Spawn();
		{
			std::shared_ptr<Animator> ani = Eft01->GetComponent<Animator>();
			ani->Create(L"tairnag_eft", L"attack3slashglow.img", L"tairang_skill1glow", 0, 12, 0.08f);
			Animator* animator = ani.get();
			Animation::AnimationEvent TimeEvent = {};
			TimeEvent.mTime = 0.5f;
			TimeEvent.mNormalFunc = std::bind([animator]()->void {animator->PlayAnimation(L"tairang_skill1glow", false); });
			animation->AddTimeLineEvent(TimeEvent);
		}
		std::shared_ptr<GameObject> Eft02 = pool->GetPool(L"AniEftObject")->Spawn();
		{
			std::shared_ptr<Animator> ani = Eft02->GetComponent<Animator>();
			ani->Create(L"tairnag_eft", L"attack3trail.img", L"tairang_skill1trail", 0, 12, 0.08f);
			Animator* animator = ani.get();
			Animation::AnimationEvent TimeEvent = {};
			TimeEvent.mTime = 0.5f;
			TimeEvent.mNormalFunc = std::bind([animator]()->void {animator->PlayAnimation(L"tairang_skill1trail", false); });
			animation->AddTimeLineEvent(TimeEvent);
		}
		std::shared_ptr<GameObject> Eft03 = pool->GetPool(L"AniEftObject")->Spawn();
		{
			std::shared_ptr<Animator> ani = Eft03->GetComponent<Animator>();
			std::shared_ptr<Transform> tf = Eft03->GetComponent<Transform>();
			tf->position = Vector3(-0.05f, -0.1f, 0.0f);
			tf->scale = Vector3(0.25f, 0.25f, 1.0f);
			ani->Create(L"tairnag_eft", L"attack3purppleglow.img", L"tairang_skill1purppleglow", 0, 6, 0.1f);
			Animator* animator = ani.get();
			Animation::AnimationEvent TimeEvent = {};
			TimeEvent.mTime = 0.7f;
			TimeEvent.mNormalFunc = std::bind([animator]()->void {animator->PlayAnimation(L"tairang_skill1purppleglow", false); });
			animation->AddTimeLineEvent(TimeEvent);
		}
		owner->AddChild(Eft01);
		owner->AddChild(Eft02);
		owner->AddChild(Eft03);
		mStartEftObject.push_back(Eft01);
		mStartEftObject.push_back(Eft02);
		mStartEftObject.push_back(Eft03);
	}
	void TairangSkill01Script::DeleteWarningObject()
	{
		DelayedCollisionSkillScript::DeleteWarningObject();
	}
	void TairangSkill01Script::DeleteStartEftObject()
	{
		for (auto eft : mStartEftObject)
		{
			owner->RemoveChild(eft);
		}
		mStartEftObject.clear();
	}
	void TairangSkill01Script::StopWarningAniEvent()
	{
		DelayedCollisionSkillScript::StopWarningAniEvent();

		Time::CallBackTimerInfo callBack = {};
		callBack.endTime = 1.5f;
		Time::RequestEvent(callBack, std::bind(&TairangSkill01Script::ContinueWarningAniEvent, this));
	}
}