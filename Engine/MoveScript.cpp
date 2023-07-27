#include "MoveScript.h"
#include "GameObject.h"
#include "Transform.h"
#include "Input.h"
#include "RokaTime.h"
namespace roka
{
	MoveScript::MoveScript():Script(EScriptType::Move)
		,mSpeed(0.0f)
	{
	}

	MoveScript::MoveScript(const MoveScript& ref):Script(ref)
	{
		mSpeed = ref.mSpeed;
	}

	void MoveScript::Copy(Component* src)
	{
		Script::Copy(src);
		MoveScript* source = dynamic_cast<MoveScript*>(src);
		mSpeed = source->mSpeed;
	}

	MoveScript::~MoveScript()
	{
	}

	void MoveScript::Initialize()
	{
		
	}

	void MoveScript::Update()
	{
		if (owner == nullptr)
			return;

		std::shared_ptr<Transform> tf = owner->GetComponent<Transform>();
		Vector3 pos = tf->position;

		if (mIsVertical == true)
		{
			if (mRightKey == mVerticalActiveKey)
			{
				pos.x += mSpeed * Time::DeltaTime();
				tf->position = pos;
			}
			else if (mLeftKey == mVerticalActiveKey)
			{
				pos.x -= mSpeed * Time::DeltaTime();
				tf->position = pos;
			}

		}

		if (mIsHorizontal == true)
		{
			if (mUpKey == mHorizontalActiveKey)
			{
				pos.y += mSpeed * Time::DeltaTime();
				tf->position = pos;
			}
			else if (mDownKey == mHorizontalActiveKey)
			{
				pos.y -= mSpeed * Time::DeltaTime();
				tf->position = pos;
			}
		}
	

	}

	void MoveScript::LateUpdate()
	{
	}

	void MoveScript::Render()
	{
	}

	void MoveScript::SetKeys(UINT right, UINT left, UINT up, UINT down)
	{
		mRightKey = right;
		mLeftKey = left;
		mUpKey = up;
		mDownKey = down;
	}

	void MoveScript::VerticalMove(UINT vertical)
	{
		mVerticalActiveKey = vertical;
		mIsVertical = true;
	}

	void MoveScript::HorizontalMove(UINT horizontal)
	{
		mHorizontalActiveKey = horizontal;
		mIsHorizontal = true;
	}

	void MoveScript::VerticalStop(UINT vertical)
	{
		if (mVerticalActiveKey == vertical)
			mIsVertical = false;
	}

	void MoveScript::HorizontalStop(UINT horizontal)
	{
		if (mHorizontalActiveKey == horizontal)
			mIsHorizontal = false;
	}
	
}

