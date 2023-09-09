#include "TairangSkill01Script.h"

#include "RokaTime.h"
#include "AnimationObjectPool.h"
#include "GameObject.h"

#include "Animator.h"
#include "Transform.h"
#include "MeshRenderer.h"
#include "Collider2D.h"

#include "TairangMonsterScript.h"
#include "TargetMoveScript.h"
#include "HitBoxScript.h"
#include "PlayerScript.h"

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
		DelayedCollisionSkillScript::Initialize();
		mWarningFollowTime = 0.5;
		mWarningSize = Vector3(2.5f, 2.0f, 1.0f);
		mWarningCenter = Vector3(0.0f, -0.32f, 0.0f);

		std::shared_ptr<Animator> ani = owner->GetComponent<Animator>();
		ani->Create(L"tairang", L"tairang_of_speed.img", L"tairang_Skill01_start", 27, 38, 0.05f);
		ani->Create(L"tairang", L"tairang_of_speed.img", L"tairang_Skill01_middle", 43, 45, 0.4f);
		ani->Create(L"tairang", L"tairang_of_speed.img", L"tairang_Skill01_end", 25, 27, 0.2f);

		Animator* animator = ani.get();
		ani->StartEvent(L"tairang_Skill01_start") = std::bind(&TairangSkill01Script::StartStartEvent, this);
		ani->CompleteEvent(L"tairang_Skill01_start") = std::bind(&TairangSkill01Script::StartCompleteEvent,this);
		ani->CompleteEvent(L"tairang_Skill01_middle") = std::bind(&TairangSkill01Script::MiddleCompleteEvent,this);
		ani->CompleteEvent(L"tairang_Skill01_end") = std::bind(&TairangSkill01Script::EndCompleteEvent, this);

		/*std::shared_ptr<Animation> animation = ani->FindAnimation(L"ellipse_warning2");
		Animation::AnimationEvent TimeEvent = {};
		TimeEvent.*/

#pragma region start eft time event Init
		std::shared_ptr<Animation> animation = ani->FindAnimation(L"tairang_Skill01_start");
		{
			Animation::AnimationEvent TimeEvent = {};
			TimeEvent.mTime = 0.5f;
			TimeEvent.mNormalFunc = std::bind(&TairangSkill01Script::PlayStartEftObject,this,0, L"tairang_skill1glow");
			animation->AddTimeLineEvent(TimeEvent);
		}
		{
			Animation::AnimationEvent TimeEvent = {};
			TimeEvent.mTime = 0.5f;
			TimeEvent.mNormalFunc = std::bind(&TairangSkill01Script::PlayStartEftObject, this, 1, L"tairang_skill1trail");
			animation->AddTimeLineEvent(TimeEvent);
		}
		{
			Animation::AnimationEvent TimeEvent = {};
			TimeEvent.mTime = 0.5f;
			TimeEvent.mNormalFunc = std::bind(&TairangSkill01Script::PlayStartEftObject, this, 2, L"tairang_skill1purppleglow");
			animation->AddTimeLineEvent(TimeEvent);
		}
		{
			Animation::AnimationEvent TimeEvent = {};
			TimeEvent.mTime = 0.5f;
			TimeEvent.mNormalFunc = std::bind(&TairangSkill01Script::PlayStartEftObject, this, 3, L"tairang_skill1purppleglow");
			animation->AddTimeLineEvent(TimeEvent);
		}
		{
			Animation::AnimationEvent TimeEvent = {};
			TimeEvent.mTime = 0.5f;
			TimeEvent.mNormalFunc = std::bind(&TairangSkill01Script::PlayStartEftObject, this, 4, L"tairang_skill1purppleglow");
			animation->AddTimeLineEvent(TimeEvent);
		}
		{
			Animation::AnimationEvent TimeEvent = {};
			TimeEvent.mTime = 0.9f;
			TimeEvent.mNormalFunc = std::bind(&TairangSkill01Script::PlayStartEftObject, this, 5, L"tairang_skill1purppleglow");
			animation->AddTimeLineEvent(TimeEvent);
		}
		{
			Animation::AnimationEvent TimeEvent = {};
			TimeEvent.mTime = 0.9f;
			TimeEvent.mNormalFunc = std::bind(&TairangSkill01Script::PlayStartEftObject, this, 6, L"tairang_skill1purppleglow");
			animation->AddTimeLineEvent(TimeEvent);
		}
		{
			Animation::AnimationEvent TimeEvent = {};
			TimeEvent.mTime = 0.9f;
			TimeEvent.mNormalFunc = std::bind(&TairangSkill01Script::PlayStartEftObject, this, 7, L"tairang_skill1purppleglow");
			animation->AddTimeLineEvent(TimeEvent);
		}
#pragma endregion

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
	void TairangSkill01Script::OnCollisionEnter(std::shared_ptr<Collider2D> other)
	{
		std::shared_ptr<HitBoxScript> hitbox = other->owner->GetComponent<HitBoxScript>();
		std::shared_ptr<GameObject> hitboxOwner = hitbox->hitbox_owner;
		if (hitboxOwner == nullptr)
			return;
		std::shared_ptr<PlayerScript> player = hitboxOwner->GetComponent<PlayerScript>();
		if (player == nullptr)
			return;

		float damage = 1;
		player->BeAttacked(mDamage, mStunType);
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
		CreateMiddleEftObject();
		Jump();
	}
	void TairangSkill01Script::EndStartEvent()
	{
		std::shared_ptr<MeshRenderer> mr = owner->GetComponent<MeshRenderer>();
		mr->is_active = true;
		std::shared_ptr<Animator> ani = owner->GetComponent<Animator>();
		ani->PlayAnimation(L"tairang_Skill01_end", false);
		DeleteMiddleEftObject();
		DeleteWarningObject();
		Landing();
		CreateColliderObject();
		CreateEndEftObject();
	}
	void TairangSkill01Script::StartCompleteEvent()
	{
		Time::CallBackTimerInfo callBack = {};
		callBack.endTime = 0.8f;
		Time::RequestEvent(callBack, std::bind(&TairangSkill01Script::MiddleStartEvent, this));
	}
	void TairangSkill01Script::MiddleCompleteEvent()
	{
		Hide();
		Explosion();
		Time::CallBackTimerInfo callBack = {};
		callBack.endTime = 2.5f;
		Time::RequestEvent(callBack, std::bind(&TairangSkill01Script::EndStartEvent, this));
	}
	void TairangSkill01Script::EndCompleteEvent()
	{
		Exit();
	}
	void TairangSkill01Script::CreateColliderObject()
	{
		DelayedCollisionSkillScript::CreateColliderObject();
		std::shared_ptr<Animator> ani = mColObj->GetComponent<Animator>();
		ani->Create(L"tairnag_eft", L"bearas1crackn.img", L"tairang_skill1groundcrack", 0, 3, 0.08);
		ani->PlayAnimation(L"tairang_skill1groundcrack", false);
		std::shared_ptr<Transform> tf =mColObj->GetComponent<Transform>();
		tf->scale = Vector3(1.5f,0.5f,1.0f);
		Vector3 pos = tf->position;
		tf->position = pos + Vector3(0.0f, -0.75f, 0.0f);

		mStunType = EStunState::Down;

		std::shared_ptr<HitBoxScript> hitBox = mColObj->GetComponent<HitBoxScript>();
		mColObj->layer_type = ELayerType::Skill;
		hitBox->hitbox = HitBoxScript::EHitBoxType::Bottom;
		hitBox->hitbox_owner = owner->GetSharedPtr();
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
		MeshRenderer* meshRenderer = mWarningObj->GetComponent<MeshRenderer>().get();
		warning_ani->CompleteEvent(L"ellipse_warning1") = std::bind([meshRenderer]()->void {meshRenderer->is_active = false; });
		warning_ani->PlayAnimation(L"ellipse_warning1", false);
	}
	void TairangSkill01Script::CreateStartEftObject()
	{
		std::shared_ptr<Animator> owner_ani = owner->GetComponent<Animator>();
		

		pool::AnimationObjectPool* pool = pool::AnimationObjectPool::GetInstance();
		std::shared_ptr<GameObject> Eft01 = pool->GetPool(L"AniEftObject")->Spawn();
		{
			std::shared_ptr<Animator> ani = Eft01->GetComponent<Animator>();
			ani->Create(L"tairnag_eft", L"attack3slashglow.img", L"tairang_skill1glow", 0, 12, 0.05f);
			MeshRenderer* meshRenderer = Eft01->GetComponent<MeshRenderer>().get();
			ani->CompleteEvent(L"tairang_skill1glow") = std::bind([meshRenderer]()->void {meshRenderer->is_active = false; });
		}
		std::shared_ptr<GameObject> Eft02 = pool->GetPool(L"AniEftObject")->Spawn();
		{
			std::shared_ptr<Animator> ani = Eft02->GetComponent<Animator>();
			ani->Create(L"tairnag_eft", L"attack3trail.img", L"tairang_skill1trail", 0, 12, 0.05f);
			MeshRenderer* meshRenderer = Eft02->GetComponent<MeshRenderer>().get();
			ani->CompleteEvent(L"tairang_skill1trail") = std::bind([meshRenderer]()->void {meshRenderer->is_active = false; });
		}
		std::shared_ptr<GameObject> Eft03 = pool->GetPool(L"AniEftObject")->Spawn();
		{
			std::shared_ptr<Animator> ani = Eft03->GetComponent<Animator>();
			std::shared_ptr<Transform> tf = Eft03->GetComponent<Transform>();
			tf->position = Vector3(-0.03f, -0.1f, 0.0f);
			tf->scale = Vector3(0.25f, 0.25f, 1.0f);
			
			ani->Create(L"tairnag_eft", L"attack3purppleglow.img", L"tairang_skill1purppleglow", 0, 6, 0.05f);
			MeshRenderer* meshRenderer = Eft03->GetComponent<MeshRenderer>().get();
			ani->CompleteEvent(L"tairang_skill1purppleglow") = std::bind([meshRenderer]()->void {meshRenderer->is_active = false; });
		}
		std::shared_ptr<GameObject> Eft04 = pool->GetPool(L"AniEftObject")->Spawn();
		{
			std::shared_ptr<Animator> ani = Eft04->GetComponent<Animator>();
			std::shared_ptr<Transform> tf = Eft04->GetComponent<Transform>();
			tf->position = Vector3(-0.1f, -0.11f, 0.0f);
			tf->scale = Vector3(0.25f, 0.25f, 1.0f);
			ani->Create(L"tairnag_eft", L"attack3purppleglow.img", L"tairang_skill1purppleglow", 0, 6, 0.05f);
			MeshRenderer* meshRenderer = Eft04->GetComponent<MeshRenderer>().get();
			ani->CompleteEvent(L"tairang_skill1purppleglow") = std::bind([meshRenderer]()->void {meshRenderer->is_active = false; });
		}
		std::shared_ptr<GameObject> Eft05 = pool->GetPool(L"AniEftObject")->Spawn();
		{
			std::shared_ptr<Animator> ani = Eft05->GetComponent<Animator>();
			std::shared_ptr<Transform> tf = Eft05->GetComponent<Transform>();
			tf->position = Vector3(-0.19f, -0.13f, 0.0f);
			tf->scale = Vector3(0.28f, 0.3f, 1.0f);
			ani->Create(L"tairnag_eft", L"attack3purppleglow.img", L"tairang_skill1purppleglow", 0, 6, 0.05f);
			MeshRenderer* meshRenderer = Eft05->GetComponent<MeshRenderer>().get();
			ani->CompleteEvent(L"tairang_skill1purppleglow") = std::bind([meshRenderer]()->void {meshRenderer->is_active = false; });
		}
		std::shared_ptr<GameObject> Eft06 = pool->GetPool(L"AniEftObject")->Spawn();
		{
			std::shared_ptr<Animator> ani = Eft06->GetComponent<Animator>();
			std::shared_ptr<Transform> tf = Eft06->GetComponent<Transform>();
			tf->position = Vector3(-0.05f, -0.1f, 0.0f);
			tf->scale = Vector3(0.3f, 0.3f, 1.0f);
			ani->Create(L"tairnag_eft", L"attack3purppleglow.img", L"tairang_skill1purppleglow", 0, 6, 0.05f);
			MeshRenderer* meshRenderer = Eft06->GetComponent<MeshRenderer>().get();
			ani->CompleteEvent(L"tairang_skill1purppleglow") = std::bind([meshRenderer]()->void {meshRenderer->is_active = false; });
		}
		std::shared_ptr<GameObject> Eft07 = pool->GetPool(L"AniEftObject")->Spawn();
		{
			std::shared_ptr<Animator> ani = Eft07->GetComponent<Animator>();
			std::shared_ptr<Transform> tf = Eft07->GetComponent<Transform>();
			tf->position = Vector3(-0.1f, -0.11f, 0.01f);
			tf->scale = Vector3(0.3f, 0.3f, 1.0f);
			ani->Create(L"tairnag_eft", L"attack3purppleglow.img", L"tairang_skill1purppleglow", 0, 6, 0.05f);
			MeshRenderer* meshRenderer = Eft07->GetComponent<MeshRenderer>().get();
			ani->CompleteEvent(L"tairang_skill1purppleglow") = std::bind([meshRenderer]()->void {meshRenderer->is_active = false; });
		}
		std::shared_ptr<GameObject> Eft08 = pool->GetPool(L"AniEftObject")->Spawn();
		{
			std::shared_ptr<Animator> ani = Eft08->GetComponent<Animator>();
			std::shared_ptr<Transform> tf = Eft08->GetComponent<Transform>();
			tf->position = Vector3(-0.2f, -0.13f, 0.0f);
			tf->scale = Vector3(0.3f, 0.3f, 1.0f);
			ani->Create(L"tairnag_eft", L"attack3purppleglow.img", L"tairang_skill1purppleglow", 0, 6, 0.05f);
			MeshRenderer* meshRenderer = Eft08->GetComponent<MeshRenderer>().get();
			ani->CompleteEvent(L"tairang_skill1purppleglow") = std::bind([meshRenderer]()->void {meshRenderer->is_active = false; });
		}
		owner->AddChild(Eft01);
		owner->AddChild(Eft02);
		owner->AddChild(Eft03);
		owner->AddChild(Eft04);
		owner->AddChild(Eft05);
		owner->AddChild(Eft06);
		owner->AddChild(Eft07);
		owner->AddChild(Eft08);
		mStartEftObject.push_back(Eft01);
		mStartEftObject.push_back(Eft02);
		mStartEftObject.push_back(Eft03);
		mStartEftObject.push_back(Eft04);
		mStartEftObject.push_back(Eft05);
		mStartEftObject.push_back(Eft06);
		mStartEftObject.push_back(Eft07);
		mStartEftObject.push_back(Eft08);
	}
	void TairangSkill01Script::CreateMiddleEftObject()
	{
		pool::AnimationObjectPool* pool = pool::AnimationObjectPool::GetInstance();
		std::shared_ptr<GameObject> Eft01 = pool->GetPool(L"AniEftObject")->Spawn();
		{
			std::shared_ptr<Animator> ani = Eft01->GetComponent<Animator>();
			ani->Create(L"tairnag_eft",L"attack3line.img", L"tairang_skill1line", 0, 3,0.08);
			ani->PlayAnimation(L"tairang_skill1line", false);

			std::shared_ptr<Transform> tf = Eft01->GetComponent<Transform>();
			tf->scale = Vector3(1.5f, 1.5f, 1.0f);
			tf->rotation = Vector3(0.0f, 0.0f, Deg2Rad(90));
			tf->position = Vector3(-0.225f, 0.5f, 0.01f);

			MeshRenderer* meshRenderer = Eft01->GetComponent<MeshRenderer>().get();
			ani->CompleteEvent(L"tairang_skill1line") = std::bind([meshRenderer]()->void {meshRenderer->is_active = false; });
		}
		std::shared_ptr<GameObject> Eft02 = pool->GetPool(L"AniEftObject")->Spawn();
		{
			std::shared_ptr<Animator> ani = Eft02->GetComponent<Animator>();
			ani->Create(L"tairnag_eft", L"attack3booster.img", L"tairang_skill1booster", 0, 12, 0.08);
			ani->PlayAnimation(L"tairang_skill1booster", false);

			std::shared_ptr<Transform> tf = Eft02->GetComponent<Transform>();
			tf->position = Vector3(0.05f, 0.2f, 0.01f);
		}
		std::shared_ptr<GameObject> Eft03 = pool->GetPool(L"AniEftObject")->Spawn();
		{
			std::shared_ptr<Animator> ani = Eft03->GetComponent<Animator>();
			ani->Create(L"tairnag_eft", L"abyssbombsmall.img", L"tairang_skill1abyss_explosion", 0, 12, 0.08);

			std::shared_ptr<Transform> tf = Eft03->GetComponent<Transform>();
			tf->scale = Vector3(0.25f, 0.25f, 1.0f);
			tf->position = Vector3(0.0f, 0.08f, 0.01f);
		}

		owner->AddChild(Eft01);
		owner->AddChild(Eft02);
		owner->AddChild(Eft03);

		mMiddleEftObject.push_back(Eft01);
		mMiddleEftObject.push_back(Eft02);
		mMiddleEftObject.push_back(Eft03);
	}
	void TairangSkill01Script::CreateEndEftObject()
	{
		pool::AnimationObjectPool* pool = pool::AnimationObjectPool::GetInstance();
		std::shared_ptr<GameObject> Eft01 = pool->GetPool(L"AniObject")->Spawn();
		{
			std::shared_ptr<Animator> ani = Eft01->GetComponent<Animator>();
			ani->Create(L"tairnag_eft", L"lightning01a.img", L"tairang_skill1lightning", 0, 9, 0.08);
			ani->PlayAnimation(L"tairang_skill1lightning", false);
			MeshRenderer* meshRenderer = Eft01->GetComponent<MeshRenderer>().get();
			ani->CompleteEvent(L"tairang_skill1lightning") = std::bind([meshRenderer]()->void {meshRenderer->is_active = false; });

			std::shared_ptr<Transform> tf = Eft01->GetComponent<Transform>();
			tf->scale = Vector3(0.1f, 4.0f, 1.0f);
			tf->position = Vector3(0.0f, 1.7f, 0.0f);
		}
		std::shared_ptr<GameObject> Eft02 = pool->GetPool(L"AniObject")->Spawn();
		{
			std::shared_ptr<Animator> ani = Eft02->GetComponent<Animator>();
			ani->Create(L"tairnag_eft", L"abyssbombmiddlen.img", L"tairang_skill1abyssBomb", 0, 20, 0.01);
			ani->PlayAnimation(L"tairang_skill1abyssBomb", false);
			MeshRenderer* meshRenderer = Eft02->GetComponent<MeshRenderer>().get();
			ani->CompleteEvent(L"tairang_skill1abyssBomb") = std::bind([meshRenderer]()->void {meshRenderer->is_active = false; });
			
			std::shared_ptr<Transform> tf = Eft02->GetComponent<Transform>();
			tf->scale = Vector3(0.8f, 0.25f, 1.0f);
			tf->position = Vector3(0.0f, -0.2f, 0.0f);
		}
		std::shared_ptr<GameObject> Eft03 = pool->GetPool(L"AniObject")->Spawn();
		{
			std::shared_ptr<Animator> ani = Eft03->GetComponent<Animator>();
			ani->Create(L"tairnag_eft", L"jump_dust04.img", L"tairang_skill1dust", 0, 8, 0.01);
			ani->PlayAnimation(L"tairang_skill1dust", false);
			MeshRenderer* meshRenderer = Eft03->GetComponent<MeshRenderer>().get();
			ani->CompleteEvent(L"tairang_skill1dust") = std::bind([meshRenderer]()->void {meshRenderer->is_active = false; });

			std::shared_ptr<Transform> tf = Eft03->GetComponent<Transform>();
			tf->scale = Vector3(0.8f, 1.0f, 1.0f);
		}
		std::shared_ptr<GameObject> Eft04 = pool->GetPool(L"AniObject")->Spawn();
		{
			std::shared_ptr<Animator> ani = Eft04->GetComponent<Animator>();
			ani->Create(L"tairnag_eft", L"bolt01.img", L"tairang_skill1bolt", 0, 13, 0.05);
			ani->PlayAnimation(L"tairang_skill1bolt", false);
			MeshRenderer* meshRenderer = Eft04->GetComponent<MeshRenderer>().get();
			ani->CompleteEvent(L"tairang_skill1bolt") = std::bind([meshRenderer]()->void {meshRenderer->is_active = false; });

			std::shared_ptr<Transform> tf = Eft04->GetComponent<Transform>();
			tf->position = Vector3(-0.05f, -0.05f, 0.0f);
		}
		owner->AddChild(Eft01);
		owner->AddChild(Eft02);
		owner->AddChild(Eft03);
		owner->AddChild(Eft04);

		mEndEftObject.push_back(Eft01);
		mEndEftObject.push_back(Eft02);
		mEndEftObject.push_back(Eft03);
		mEndEftObject.push_back(Eft04);
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
	void TairangSkill01Script::DeleteMiddleEftObject()
	{
		for (auto eft : mMiddleEftObject)
		{
			owner->RemoveChild(eft);
		}
		mMiddleEftObject.clear();
	}
	void TairangSkill01Script::DeleteEndEftObject()
	{
		for (auto eft : mEndEftObject)
		{
			owner->RemoveChild(eft);
		}
		mEndEftObject.clear();
	}
	void TairangSkill01Script::StopWarningAniEvent()
	{
		DelayedCollisionSkillScript::StopWarningAniEvent();

		Time::CallBackTimerInfo callBack = {};
		callBack.endTime = 3.5f;
		Time::RequestEvent(callBack, std::bind(&TairangSkill01Script::ContinueWarningAniEvent, this));
	}
	void TairangSkill01Script::PlayStartEftObject(int index,std::wstring key)
	{
		mStartEftObject[index]->GetComponent<Animator>()->PlayAnimation(key, false);
	}
	void TairangSkill01Script::Jump()
	{
		std::shared_ptr<TairangMonsterScript> monster = owner->GetComponent<TairangMonsterScript>();
		EDir4Type dir = monster->GetDir();
		Vector3 diff = Vector3(0.0f, -0.5f, 0.0f);
		Vector3 distance = Vector3(0.3f, 0.5f, 0.0f);
		float speed = 1.5f;
		std::shared_ptr<Transform> tf = owner->GetComponent<Transform>();
		Vector3 CurPos = tf->position+diff;
		tf->position = CurPos;
		Vector3 TargetPos = {};
		switch (dir)
		{
		case EDir4Type::LEFT:
			TargetPos.x = CurPos.x - distance.x;
			TargetPos.y = CurPos.y + distance.y;
			break;
		case EDir4Type::RIGHT:
			TargetPos.x = CurPos.x + distance.x;
			TargetPos.y = CurPos.y + distance.y;
			break;
		}

		std::shared_ptr<TargetMoveScript> targetMove = owner->GetComponent<TargetMoveScript>();
		targetMove->SetSpeed(speed);
		targetMove->SetDirX(distance.x);
		targetMove->SetDirY(distance.y);
		targetMove->SetTargetPos(Vector2(TargetPos.x,TargetPos.y));
	}
	void TairangSkill01Script::Hide()
	{
		std::shared_ptr<MeshRenderer> mr = owner->GetComponent<MeshRenderer>();
		mr->is_active = false;

		mMiddleEftObject[1]->GetComponent<MeshRenderer>()->is_active = false;
	}
	void TairangSkill01Script::Explosion()
	{
		std::shared_ptr<Animator> ani = mMiddleEftObject[2]->GetComponent<Animator>();
		ani->PlayAnimation(L"tairang_skill1abyss_explosion",false);
	}
	void TairangSkill01Script::Landing()
	{
		std::shared_ptr<Transform> tf = owner->GetComponent<Transform>();
		tf->position = mPos;
	}
}