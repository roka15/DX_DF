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
	Vector2 MonsterScript::mLeftColCenter = Vector2::Zero;
	Vector2 MonsterScript::mRightColCenter = Vector2::Zero;

	Vector2 MonsterScript::mLeftShooterPos = Vector2::Zero;
	Vector2 MonsterScript::mRightShooterPos = Vector2::Zero;

	MonsterScript::MonsterScript() :Script(EScriptType::Monster),
		mbNextState(true)
	{
	}

	MonsterScript::MonsterScript(const MonsterScript& ref) : Script(ref)
	{
		mbNextState = true;
	}

	void MonsterScript::Copy(Component* src)
	{
		MonsterScript* source = dynamic_cast<MonsterScript*>(src);
		if (source == nullptr)
			return;
		mbNextState = true;
	}

	MonsterScript::~MonsterScript()
	{
	}

	void MonsterScript::Initialize()
	{
		mState = EMonsterState::Ready;
		mNextStateCoolTime = 5.0;
		mSpeed = 0.25f;
		std::shared_ptr<Animator> ani = owner->GetComponent<Animator>();

		ani->Create(L"monster", L"web_spider_z.img", L"web_spider_Idle", 0, 5, 0.2f);
		ani->Create(L"monster", L"web_spider_z.img", L"web_spider_Walk", 5, 13, 0.2f);
		ani->Create(L"monster", L"web_spider_z.img", L"web_spider_Skill1_start", 28, 38, 0.1f);
		ani->Create(L"monster", L"web_spider_z.img", L"web_spider_Skill1_middle", 39, 44, 0.1f);
		ani->Create(L"monster", L"web_spider_z.img", L"web_spider_Skill1_end", 45, 46, 0.1f);
		
		ani->CompleteEvent(L"web_spider_Skill1_start") = std::bind([this]()->void {
			std::shared_ptr<GameObject> skill = owner->GetChild(L"skill01");
			skill->active = GameObject::EState::Active;
			std::shared_ptr<Animator> ani = owner->GetComponent<Animator>();
			ani->PlayAnimation(L"web_spider_Skill1_middle", false);
			});
		ani->CompleteEvent(L"web_spider_Skill1_middle") = std::bind([this]()->void {
			std::shared_ptr<Animator> ani = owner->GetComponent<Animator>();
			ani->PlayAnimation(L"web_spider_Skill1_end", false);
			});
		ani->CompleteEvent(L"web_spider_Skill1_end") = std::bind([this]()->void {
			EnableNextState();
			std::shared_ptr<GameObject> skill = owner->GetChild(L"skill01");
			skill->active = GameObject::EState::Paused;
			});
		ani->PlayAnimation(L"web_spider_Idle", true);

		Time::RegisterEvent(L"MonsterRandomStateEvent", MonsterScript::RandomState);
	}

	void MonsterScript::Update()
	{
		if (mState == EMonsterState::Ready)
		{
			Ready();
		}
		std::shared_ptr<TargetMoveScript> ts = owner->GetComponent<TargetMoveScript>();
		if (ts->is_stop && mbNextState)
		{
			mState = EMonsterState::Idle;
			Idle();
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
			if (ts->is_stop == false|| ms->mbNextState == false)
			{
				//이동이 안끝났는데 다음 event 물색중이면 time event 다시 요청하고 종료.
				Time::RequestEvent(info, ptr);
				return;
			}
				
			while (1)
			{
				int range = (int)EMonsterState::Death - 1;
				EMonsterState state = (EMonsterState)(rand() % range + 1);
	
				//if (state == EMonsterState::Walk || state == EMonsterState::Skill)
				//{
				//	//이전 state가 walk 인데 지금도 walk가 된 경우.
				//	if (ms->mState == state)
				//		continue;
				//	//이미 움직이는 중.
				//	if (state == EMonsterState::Walk)
				//	{
				//		if(ts->is_stop == false)
				//		continue;
				//	}
				//}
				ms->mState = state;
				break;
			}

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
		std::shared_ptr<Animator> ani = owner->GetComponent<Animator>();
		ani->PlayAnimation(L"web_spider_Idle", true);
	}
	void MonsterScript::Move()
	{
		std::shared_ptr<Animator> ani = owner->GetComponent<Animator>();
		ani->PlayAnimation(L"web_spider_Walk", true);

		Vector3 targetPos = mTarget.lock()->GetComponent<Transform>()->position;
		Vector3 myPos = owner->GetComponent<Transform>()->position;
		Vector3 FinalTargetPos = {};

		UINT AspectRatioX = application.GetWidth();
		UINT AspectRatioY = application.GetHeight();
		float DirX = 0.0f;
		float DirY = 0.0f;
		while (1)
		{
			Vector2 Distance = { (float)(rand() % AspectRatioX),(float)(rand() % AspectRatioY) };
			if (Distance.x < AspectRatioX / 2.0f)
				Distance.x *= -1;
			if (Distance.y < AspectRatioY / 2.0f)
				Distance.y *= -1;

			Distance.x /= AspectRatioX / 2.0f;
			Distance.y /= AspectRatioY / 2.0f;

			FinalTargetPos.x = myPos.x + Distance.x;
			FinalTargetPos.y = myPos.y + Distance.y;
			
		
			Distance.Normalize();
			DirX = Distance.x;
			DirY = Distance.y;

			if (Distance.x == 0.0f)
			{
				DirX = 0.0f;
			}
			if (Distance.y == 0.0f)
			{
				DirY = 0.0f;
			}

			std::shared_ptr<MeshRenderer> mr = owner->GetComponent<MeshRenderer>();
			if (DirX < 0.0f)
			{
				if (mCurDirType == EDir4Type::LEFT)
					return;
				mCurDirType = EDir4Type::LEFT;
				mr->material = Resources::Find<Material>(L"DefaultVInverterAniMaterial");
				std::vector<std::shared_ptr<Collider2D>> cols = owner->GetChilds<Collider2D>();
				
				for (auto col : cols)
				{
					Vector2 pos = col->GetCenter();
					pos.x = mLeftColCenter.x;
					col->SetCenter(pos);
				}
				std::shared_ptr<GameObject> skill = owner->GetChild(L"skill01");
				std::shared_ptr<Transform> tf = skill->GetComponent<Transform>();
				Vector3 pos = tf->position;
				float z = tf->position.z;
				tf->position = Vector3(mLeftShooterPos.x, mLeftShooterPos.y, z);
			}
			else if (DirX > 0.0f)
			{
				if (mCurDirType == EDir4Type::RIGHT)
					return;
				mCurDirType == EDir4Type::RIGHT;
				mr->material = Resources::Find<Material>(L"DefaultAniMaterial");
				std::vector<std::shared_ptr<Collider2D>> cols = owner->GetChilds<Collider2D>();
				for (auto col : cols)
				{
					Vector2 pos = col->GetCenter();
					pos.x = mRightColCenter.x;
					col->SetCenter(pos);
				}
				std::shared_ptr<GameObject> skill = owner->GetChild(L"skill01");
				std::shared_ptr<Transform> tf = skill->GetComponent<Transform>();
				float z = tf->position.z;
				tf->position = Vector3(mRightShooterPos.x,mRightShooterPos.y,z);
			}

			Viewport view;
			view.width = AspectRatioX;
			view.height = AspectRatioY;
			view.x = 0;
			view.y = 0;
			view.minDepth = 0.0f;
			view.maxDepth = 1.0f;

			Vector3 projectPos = view.Project(FinalTargetPos, Camera::GetGpuProjectionMatrix(), Camera::GetGpuViewMatrix(), Matrix::Identity);

			if (projectPos.x > AspectRatioX ||
				projectPos.x < 0.0f ||
				projectPos.y >AspectRatioY ||
				projectPos.y < 0.0f)
			{
				continue;
			}
			else
				break;
		}
	
		std::shared_ptr<TargetMoveScript> ts = owner->GetComponent<TargetMoveScript>();
		ts->SetDirX(DirX);
		ts->SetDirY(DirY);
		ts->SetSpeed(mSpeed);
		ts->SetTargetPos(Vector2(FinalTargetPos.x, FinalTargetPos.y));
	}
	void MonsterScript::Attack()
	{
		Skill01();
	}
	void MonsterScript::Skill01()
	{
		std::shared_ptr<Animator> ani = owner->GetComponent<Animator>();
		ani->PlayAnimation(L"web_spider_Skill1_start", false);
		DisableNextState();
	}
	
}

