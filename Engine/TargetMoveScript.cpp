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
		if (IsStop() == true)
		{
			if (mTargetPos != Vector2::Zero)
				mTargetPos = Vector2::Zero;
			return;
		}

		
		std::shared_ptr<Transform> tf = owner->GetComponent<Transform>();
		Vector3 pos = tf->position;

		if (fabs(mTargetPos.x - pos.x) <= 0.05f)
		{
			if (fabs(mTargetPos.y - pos.y) <= 0.05f)
			{
				mDir = Vector2::Zero;
				mTargetPos = Vector2::Zero;
				return;
			}
		}
		pos.x += mDir.x * mSpeed * Time::DeltaTime();
		pos.y += mDir.y * mSpeed* Time::DeltaTime();

		if (mDir.x > 0.0f)
		{
			if (mTargetPos.x <= pos.x)
				mDir.x = 0.0f;
		}
		else if (mDir.x < 0.0f)
		{
			if (mTargetPos.x >= pos.x)
			{
				mDir.x = 0.0f;
			}
		}

		if (mDir.y > 0.0f)
		{
			if (pos.y >= mTargetPos.y)
				mDir.y = 0.0f;
		}
		else if (mDir.y < 0.0f)
		{
			if (pos.y <= mTargetPos.y)
				mDir.y = 0.0f;
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