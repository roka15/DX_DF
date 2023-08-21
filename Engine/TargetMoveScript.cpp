#include "TargetMoveScript.h"
#include "GameObject.h"
#include "RokaTime.h"

#include "Transform.h"

namespace roka
{
	TargetMoveScript::TargetMoveScript() :MoveScript(EScriptType::TargetMove)
		, mTargetPos(Vector2::Zero)
	{
	}
	TargetMoveScript::TargetMoveScript(const TargetMoveScript& ref) : MoveScript(ref)
	{
		mTargetPos = Vector2::Zero;
	}
	void TargetMoveScript::Copy(Component* src)
	{
		TargetMoveScript* source = dynamic_cast<TargetMoveScript*>(src);
		if (source == nullptr)
			return;
		mTargetPos = Vector2::Zero;
	}
	void TargetMoveScript::Initialize()
	{
	}
	void TargetMoveScript::Update()
	{
		if (owner == nullptr)
			return;
		if (mbActive == false)
			return;
		std::shared_ptr<Transform> tf = owner->GetComponent<Transform>();
		Vector3 pos = tf->position;

		pos.x += mDir.x * mSpeed * Time::DeltaTime();
		pos.y += mDir.y * mSpeed * Time::DeltaTime();

		int true_cnt = 0;
		if (mDir.x > 0.0f)
		{
			if (mTargetPos.x <= pos.x)
				true_cnt++;
		}
		else if (mDir.x < 0.0f)
		{
			if (mTargetPos.x >= pos.x)
				true_cnt++;
		}
		else if (mDir.y != 0.0f && mDir.x == 0.0f)
			true_cnt++;

		if (mDir.y > 0.0f)
		{
			if (mTargetPos.y <= pos.y)
				true_cnt++;
		}
		else if (mDir.y < 0.0f)
		{
			if (mTargetPos.y >= pos.y)
				true_cnt++;
		}
		else if (mDir.x != 0.0f && mDir.y == 0.0f)
			true_cnt++;


		if (true_cnt == 2)
		{
			mDir.x = 0.0f;
			mDir.y = 0.0f;
			mTargetPos = Vector2::Zero;
		}

		tf->position = pos;

	}
	void TargetMoveScript::LateUpdate()
	{
	}
	void TargetMoveScript::Render()
	{
	}
	void TargetMoveScript::OnCollisionEnter(std::shared_ptr<Collider2D> other)
	{
	}
	void TargetMoveScript::OnCollisionStay(std::shared_ptr<Collider2D> other)
	{
	}
	void TargetMoveScript::OnCollisionExit(std::shared_ptr<Collider2D> other)
	{
	}
}