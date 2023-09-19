#include "TairangMonsterScript.h"

#include "GameObject.h"
#include "RokaTime.h"
#include "Prefab.h"
#include "Resources.h"
#include "NPK.h"

#include "Animator.h"
#include "Transform.h"
#include "MeshRenderer.h"
#include "Collider2D.h"
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
		mMonsterType = EMonsterType::Tairang;
		NamedMonsterScript::Initialize();

		std::shared_ptr<Animator> ani = owner->GetComponent<Animator>();
		std::shared_ptr<NPK> npk = Resources::Find<NPK>(L"tairang");
		std::shared_ptr<Texture> texture1 = npk->CreateAtlas(L"tairang_of_speed.img", 0, 14, L"NamedMonsterTairang01");
		ani->Create(texture1, L"Idle", 0, 7, 0.2f);
		ani->Create(texture1,L"Walk", 8, 13, 0.2f);
		std::shared_ptr<Texture> texture2 = npk->CreateAtlas(L"tairang_of_speed.img", 14, 27, L"NamedMonsterTairang02");
		ani->Create(texture2, L"NomalAttack1", 14, 19, 0.2f);
		ani->Create(texture2, L"NomalAttack2", 20, 26, 0.2f);
		std::shared_ptr<Texture> texture3 = npk->CreateAtlas(L"tairang_of_speed.img", 25, 38, L"NamedMonsterTairang03");
		ani->Create(texture3, L"Skill01_Start", 0, 13, 0.05f);
		ani->Create(texture3, L"Skill01_End", 0, 3, 0.05f);
		std::shared_ptr<Texture> texture4 = npk->CreateAtlas(L"tairang_of_speed.img", 37, 48, L"NamedMonsterTairang04");
		ani->Create(texture4, L"Skill01_Middle", 6, 8, 1.0f);

		std::shared_ptr<Animation> animation = ani->FindAnimation(L"Skill01_Start");
		animation->RegisterFrameEvent(L"Effect1", 6);
		animation->RegisterFrameEvent(L"NextMotion01",12);

		animation = ani->FindAnimation(L"Skill01_Middle");
		animation->RegisterFrameEvent(L"Effect2", 6);
		animation->RegisterFrameEvent(L"NextMotion02", 7);

		animation = ani->FindAnimation(L"Skill01_End");
		animation->RegisterFrameEvent(L"Effect3", 0);
		animation->RegisterFrameEvent(L"EndEvent", 2);

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
	}
}