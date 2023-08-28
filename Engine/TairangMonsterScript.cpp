#include "TairangMonsterScript.h"

#include "GameObject.h"
#include "RokaTime.h"

#include "Animator.h"
#include "Transform.h"
#include "MeshRenderer.h"

#include "SkillScript.h"
#include "TargetMoveScript.h"

namespace roka
{
	TairangMonsterScript::TairangMonsterScript() :NamedMonsterScript(EScriptType::TairangMonster)
	{
	}
	TairangMonsterScript::TairangMonsterScript(const TairangMonsterScript& ref)
	{
	}
	void TairangMonsterScript::Copy(Component* src)
	{
		NamedMonsterScript::Copy(src);
		TairangMonsterScript* source = dynamic_cast<TairangMonsterScript*>(src);
		if (source == nullptr)
			return;
	}
	void TairangMonsterScript::Initialize()
	{
		NamedMonsterScript::Initialize();
		std::shared_ptr<Animator> ani = owner->GetComponent<Animator>();
		ani->Create(L"tairang", L"tairang_of_speed.img", L"tairang_Idle", 0, 7, 0.2f);
		ani->Create(L"tairang", L"tairang_of_speed.img", L"tairang_Walk", 8, 13, 0.2f);
		ani->Create(L"tairang", L"tairang_of_speed.img", L"tairang_Skill01_start", 27, 37, 0.2f);
		ani->Create(L"tairang", L"tairang_of_speed.img", L"tairang_Skill01_middle", 43, 45, 3.0f);
		ani->Create(L"tairang", L"tairang_of_speed.img", L"tairang_Skill01_end", 25, 26, 0.2f);
		ani->Create(L"tairang", L"tairang_of_speed.img", L"tairang_NomalAttack1", 15, 19, 0.2f);
		ani->Create(L"tairang", L"tairang_of_speed.img", L"tairang_NomalAttack2", 20, 26, 0.2f);

		ani->CompleteEvent(L"tairang_Skill01_start") = std::bind([this]()->void
			{
				std::shared_ptr<Animator> ani = owner->GetComponent<Animator>();
				ani->PlayAnimation(L"tairang_Skill01_middle", false);
				Skill01SetPos();
			});
		ani->CompleteEvent(L"tairang_Skill01_middle") = std::bind([this]()->void
			{
				std::shared_ptr<TargetMoveScript> tm = owner->GetComponent<TargetMoveScript>();
				tm->ResetSpeed();
				std::shared_ptr<MeshRenderer> ms = owner->GetComponent<MeshRenderer>();
				ms->is_active = false;
				Time::CallBackTimerInfo info = {};
				info.endTime = 1.5f;
				Time::RequestEvent(info, std::bind([this]()->void {
					std::shared_ptr<Animator> ani = owner->GetComponent<Animator>();
					ani->PlayAnimation(L"tairang_Skill01_end"); })
				);

			});
		ani->StartEvent(L"tairang_Skill01_end") = std::bind([this]()->void
			{
				std::shared_ptr<MeshRenderer> ms = owner->GetComponent<MeshRenderer>();
				ms->is_active = true;
				std::shared_ptr<SkillScript> skill = owner->GetChild(L"skill01")->GetComponent<SkillScript>();
				Vector2 pos = skill->startPos;
				std::shared_ptr<Transform> tf = owner->GetComponent<Transform>();
				Vector3 myPos = tf->position;
				myPos.x = pos.x;
				myPos.y = pos.y;
				tf->position = myPos;
				EnableNextState();
				Idle();
			});
		RegisterSkillInfo(L"tairang_Skill01_start", L"tairang_Skill01_end");

		RegisterSkillFunc(std::bind([this]()->void {Skill01(); }));
	
		Time::RegisterEvent(L"Tairang_Skill01_middle_EndEvent", [](std::weak_ptr<void> ptr)->void {});
		Idle();
	}
	void TairangMonsterScript::Update()
	{
		NamedMonsterScript::Update();
	}
	void TairangMonsterScript::LateUpdate()
	{
		NamedMonsterScript::LateUpdate();
	}
	void TairangMonsterScript::Render()
	{
		NamedMonsterScript::Render();
	}
	void TairangMonsterScript::OnCollisionEnter(std::shared_ptr<Collider2D> other)
	{
		NamedMonsterScript::OnCollisionEnter(other);
	}
	void TairangMonsterScript::OnCollisionStay(std::shared_ptr<Collider2D> other)
	{
		NamedMonsterScript::OnCollisionStay(other);
	}
	void TairangMonsterScript::OnCollisionExit(std::shared_ptr<Collider2D> other)
	{
		NamedMonsterScript::OnCollisionExit(other);
	}
	void TairangMonsterScript::Ready()
	{
		NamedMonsterScript::Ready();
	}
	void TairangMonsterScript::Idle()
	{
		NamedMonsterScript::Idle();
		std::shared_ptr<Animator> ani = owner->GetComponent<Animator>();
		ani->PlayAnimation(L"tairang_Idle", true);
	}
	void TairangMonsterScript::Move()
	{
		std::shared_ptr<Animator> ani = owner->GetComponent<Animator>();
		ani->PlayAnimation(L"tairang_Walk", true);
		NamedMonsterScript::Move();
	}
	void TairangMonsterScript::Attack()
	{
		NamedMonsterScript::Attack();
	}
	void TairangMonsterScript::SetTargetPos(Vector2& outDir, Vector2& outTargetPos)
	{
		NamedMonsterScript::SetTargetPos(outDir, outTargetPos);
	}
	void TairangMonsterScript::Skill01()
	{
		
		std::shared_ptr<GameObject> skill = owner->GetChild(L"skill01");
		std::shared_ptr<SkillScript> skillScript = skill->GetComponent<SkillScript>();
		skillScript->Play(mCurDirType);
		
		std::shared_ptr<Animator> ani = owner->GetComponent<Animator>();
		mCurSkillKey = mSkillStartKey[0];
		ani->PlayAnimation(mSkillStartKey[0], false);
		DisableNextState();
	}
	void TairangMonsterScript::Skill02()
	{
	}
	void TairangMonsterScript::Skill03()
	{
	}
	void TairangMonsterScript::Skill04()
	{
	}
	void TairangMonsterScript::Skill01SetPos()
	{
		Vector2 targetPos = Vector2::Zero;
		Vector3 myPos = owner->GetComponent<Transform>()->position;

		Vector2 distance = Vector2(0.3f, 1.0f);

		float speed = 2.0f;

		if (mCurDirType == EDir4Type::LEFT)
		{
			targetPos = Vector2(myPos.x - distance.x, myPos.y + distance.y);
		}
		else if (mCurDirType == EDir4Type::RIGHT)
		{
			targetPos = Vector2(myPos.x + distance.x, myPos.y + distance.y);
		}
		std::shared_ptr<TargetMoveScript> tm = owner->GetComponent<TargetMoveScript>();
		tm->SetSpeed(speed);
		tm->SetDirX(distance.x);
		tm->SetDirY(distance.y);
		tm->SetTargetPos(targetPos);


		Vector3 PlayerPos = mTarget.lock()->GetComponent<Transform>()->position;
		
		std::shared_ptr<SkillScript> skill = owner->GetChild(L"skill01")->GetComponent<SkillScript>();
		skill->startPos = Vector2(PlayerPos.x, PlayerPos.y);
	}
}