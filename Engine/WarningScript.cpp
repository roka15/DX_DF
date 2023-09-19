#include "WarningScript.h"

#include "RokaTime.h"
#include "Transform.h"
namespace roka
{
	WarningScript::WarningScript() :Script(EScriptType::Warning),
		mWarningCenter(Vector3::Zero),
		mPos(Vector3::Zero),
		mTime(0.0)
	{
	}
	WarningScript::WarningScript(const WarningScript& ref) :Script(ref)
	{
	}
	void WarningScript::Copy(Component* src)
	{
		WarningScript* source = dynamic_cast<WarningScript*>(src);
		if (source == nullptr)
			return;
		mTime = 0.0;
	}
	void WarningScript::Initialize()
	{
		std::shared_ptr<Transform> tf = owner->GetComponent<Transform>();
		tf->scale = Vector3::One;
		tf->position = Vector3::Zero;
		tf->rotation = Vector3::Zero;
		mWarningCenter = Vector3::Zero;
		mPos = Vector3::Zero;
		mTime = 0.0;
	}
	void WarningScript::Update()
	{
		mTime += Time::DeltaTime();
		if (mTarget.expired() == false)
		{
			if (mTime <= mActiveTime)
			{
				std::shared_ptr<Transform> tf = mTarget.lock()->GetComponent<Transform>();
				mPos = tf->position;

				std::shared_ptr<Transform> myTf = owner->GetComponent<Transform>();
				myTf->position = mPos + mWarningCenter;
			}
		}
	}
	void WarningScript::LateUpdate()
	{
	}
	void WarningScript::Render()
	{
	}
	void WarningScript::SetWarningSize(Vector3 size)
	{
		std::shared_ptr<Transform> tf = owner->GetComponent<Transform>();
		tf->scale = size;
	}
}