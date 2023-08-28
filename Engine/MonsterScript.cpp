#include "MonsterScript.h"
#include "GameObject.h"
#include "RokaTime.h"
#include "Application.h"
#include "RokaMath.h"
#include "Camera.h"
#include "Resources.h"

#include "Animator.h"
#include "Transform.h"
#include "MeshRenderer.h"
#include "Collider2D.h"
#include "MoveScript.h"
#include "TargetMoveScript.h"


extern roka::Application application;
namespace roka
{
	using namespace math;

	MonsterScript::MonsterScript() :Script(EScriptType::Monster),
		mbNextState(true),
	    mLeftColCenter(Vector2::Zero),
		mRightColCenter(Vector2::Zero),
		mSkillStateCntMax(0),
		mSkillStateCnt(0)
	{
	}

	MonsterScript::MonsterScript(EScriptType type):Script(type),
		mbNextState(true),
		mLeftColCenter(Vector2::Zero),
		mRightColCenter(Vector2::Zero),
		mSkillStateCntMax(0),
		mSkillStateCnt(0)
	{
	}

	MonsterScript::MonsterScript(EScriptType type, const UINT ActiveSkillStateMaxCnt, const Vector2 leftColCenter, const Vector2 rightColCenter):Script(type),
		mbNextState(true),
		mLeftColCenter(leftColCenter),
		mRightColCenter(rightColCenter),
		mSkillStateCntMax(ActiveSkillStateMaxCnt),
		mSkillStateCnt(0)
	{
	}

	MonsterScript::MonsterScript(const MonsterScript& ref) : Script(ref),
		mbNextState(true),
		mLeftColCenter(ref.mLeftColCenter),
		mRightColCenter(ref.mRightColCenter),
		mSkillStateCntMax(ref.mSkillStateCntMax),
		mSkillStateCnt(0)
	{
		mbNextState = true;
	}

	void MonsterScript::Copy(Component* src)
	{
		MonsterScript* source = dynamic_cast<MonsterScript*>(src);
		if (source == nullptr)
			return;
		mbNextState = true;
		mSkillStateCnt = 0;
	}

	MonsterScript::~MonsterScript()
	{
	}

	void MonsterScript::Initialize()
	{
		mState = EMonsterState::Ready;
		mNextStateCoolTime = 5.0;
		mSpeed = 0.25f;
	
		Time::RegisterEvent(L"MonsterRandomStateEvent", MonsterScript::RandomState);
		mCurDirType = EDir4Type::RIGHT;
	}

	void MonsterScript::Update()
	{
		if (mState == EMonsterState::Ready)
		{
			Ready();
		}
		std::shared_ptr<TargetMoveScript> ts = owner->GetComponent<TargetMoveScript>();

		switch (mState)
		{
		case EMonsterState::Walk:
			if (ts->is_stop)
				Idle();
			break;
		case EMonsterState::Skill:
			if (mbNextState)
				Idle();
			break;
		}

	}

	void MonsterScript::LateUpdate()
	{
	}

	void MonsterScript::Render()
	{
	}

	void MonsterScript::OnCollisionEnter(std::shared_ptr<Collider2D> other)
	{
	}

	void MonsterScript::OnCollisionStay(std::shared_ptr<Collider2D> other)
	{
	}

	void MonsterScript::OnCollisionExit(std::shared_ptr<Collider2D> other)
	{
	}

	void MonsterScript::RandomState(std::weak_ptr<void> ptr)
	{
		std::shared_ptr<GameObject> obj = std::reinterpret_pointer_cast<GameObject>(ptr.lock());

		if (obj->active == GameObject::EState::Dead)
			return;

		std::shared_ptr<MonsterScript> ms = obj->GetComponent<MonsterScript>();
		std::shared_ptr<TargetMoveScript> ts = obj->GetComponent<TargetMoveScript>();

		Time::CallBackTimerInfo info = {};
		info.endTime = ms->mNextStateCoolTime;
		std::wstring key = L"MonsterRandomStateEvent";
		std::wcsncpy(info.key, key.c_str(), key.size());

		if (obj->active == GameObject::EState::Active)
		{
			if (ts->is_stop == false || ms->mbNextState == false)
			{
				//�̵��� �ȳ����µ� ���� event �������̸� time event �ٽ� ��û�ϰ� ����.
				Time::RequestEvent(info, ptr);
				return;
			}
			
			while (1)
			{
				int range = (int)EMonsterState::Death - 1;
				EMonsterState state = (EMonsterState)(rand() % range + 1);

				if (ms->mState == state)
					continue;
				if (state == EMonsterState::Skill)
				{
					if (ms->mSkillStateCnt >= ms->mSkillStateCntMax)
					{
						ms->mState = state;
						ms->mSkillStateCnt = 0;
						break;
					}
					else continue;
				}
				ms->mState = state;
				break;
			}
		//	ms->mState = EMonsterState::Skill;
			ms->mSkillStateCnt++;
			switch (ms->mState)
			{
			case EMonsterState::Idle:
				ms->Idle();
				break;
			case EMonsterState::Walk:
				ms->Move();
				break;
			case EMonsterState::Skill:
			{
				ms->Attack();
			}
			break;
			}

		}

		Time::RequestEvent(info, ptr);
	}
	void MonsterScript::Ready()
	{
		Time::CallBackTimerInfo info = {};
		info.endTime = mNextStateCoolTime;
		std::wstring key = L"MonsterRandomStateEvent";
		std::wcsncpy(info.key, key.c_str(), key.size());
		Time::RequestEvent(info, owner->GetSharedPtr());
		mState = EMonsterState::Idle;
	}
	void MonsterScript::Idle()
	{
		
	}
	void MonsterScript::Move()
	{
		Vector2 Dir = Vector2::Zero;
		Vector2 TargetPos = Vector2::Zero;

		SetTargetPos(Dir, TargetPos);

		Vector3 PlayerPos =mTarget.lock()->GetComponent<Transform>()->position;
		Vector3 MyPos = owner->GetComponent<Transform>()->position;
		Vector3 lookat = PlayerPos - MyPos;

		if (fabs(TargetPos.x - MyPos.x) <= 0.05f)
		{
			if (fabs(TargetPos.y - MyPos.y) <= 0.05f);
			{
				mState = EMonsterState::Idle;
				Idle();
				return;
			}
		}

		if (lookat.x < 0.0f)
		{
			if (mCurDirType != EDir4Type::LEFT)
			{
				std::shared_ptr<MeshRenderer> mr = owner->GetComponent<MeshRenderer>();
				mCurDirType = EDir4Type::LEFT;
				mr->material = Resources::Find<Material>(L"DefaultVInverterAniMaterial");
				LeftSetting();
			}
		}
		else if (lookat.x > 0.0f)
		{
			if (mCurDirType != EDir4Type::RIGHT)
			{
				std::shared_ptr<MeshRenderer> mr = owner->GetComponent<MeshRenderer>();
				mCurDirType = EDir4Type::RIGHT;
				mr->material = Resources::Find<Material>(L"DefaultAniMaterial");
				RightSetting();
			}
		}
		
		std::shared_ptr<TargetMoveScript> ts = owner->GetComponent<TargetMoveScript>();
		ts->SetDirX(Dir.x);
		ts->SetDirY(Dir.y);
		ts->SetSpeed(mSpeed);
		ts->SetTargetPos(TargetPos);
	}
	void MonsterScript::Attack()
	{
	}
	void MonsterScript::AttackEnd()
	{
		SkillEnd();
	}
	void MonsterScript::SkillEnd()
	{
		std::shared_ptr<Animator> ani = owner->GetComponent<Animator>();
		std::wstring endkey = mSkillEndKey[mCurSkillKey];
		ani->PlayAnimation(endkey, false);
	}
	void MonsterScript::RegisterSkillInfo(std::wstring start, std::wstring end)
	{
		mSkillStartKey.push_back(start);
		mSkillEndKey.insert(std::make_pair(start, end));
	}
	void MonsterScript::LeftSetting()
	{
		std::vector<std::shared_ptr<Collider2D>> cols = owner->GetChilds<Collider2D>();

		for (auto col : cols)
		{
			Vector2 pos = col->GetCenter();
			pos.x = mLeftColCenter.x;
			col->SetCenter(pos);
		}
	}
	void MonsterScript::RightSetting()
	{
		std::vector<std::shared_ptr<Collider2D>> cols = owner->GetChilds<Collider2D>();

		for (auto col : cols)
		{
			Vector2 pos = col->GetCenter();
			pos.x = mRightColCenter.x;
			col->SetCenter(pos);
		}

	}
	void MonsterScript::SetTargetPos(Vector2& outDir, Vector2& outTargetPos)
	{
	}
	
}
