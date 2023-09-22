#include "ChangeSizeOverTime.h"

#include "RokaTime.h"
#include "Transform.h"
#include "MeshRenderer.h"

namespace roka
{
	ChangeSizeOverTime::ChangeSizeOverTime() :Script(EScriptType::ChangeSizeOverTime),
		mOffset(Vector3::Zero),
		mCurTime(0.0),
		mEndTime(0.0),
		mAlpha(0.0f),
		mAlphaType(EAlphaType::None)
	{
		mbActive = false;
	}

	ChangeSizeOverTime::ChangeSizeOverTime(const ChangeSizeOverTime& ref) :Script(ref),
		mOffset(Vector3::Zero),
		mCurTime(0.0),
		mEndTime(0.0),
		mAlpha(0.0f),
		mAlphaType(EAlphaType::None)
	{
		mbActive = false;
	}

	void ChangeSizeOverTime::Copy(Component* src)
	{
		ChangeSizeOverTime* source = dynamic_cast<ChangeSizeOverTime*>(src);
		if (source == nullptr)
			return;
		mOffset = source->mOffset;
		mCurTime = 0.0;
		mEndTime = source->mEndTime;
		mAlpha = source->mAlpha;
		mAlphaType = source->mAlphaType;
		mbActive = false;
	}

	void ChangeSizeOverTime::Initialize()
	{
		mOffset = Vector3::Zero;
		mbActive = false;
	}

	void ChangeSizeOverTime::Update()
	{
		if (mbActive == false)
			return;
		std::shared_ptr<Transform> tf = owner->GetComponent<Transform>();
		std::shared_ptr<MeshRenderer> mesh = owner->GetComponent<MeshRenderer>();
		mCurTime += Time::DeltaTime();

		Vector3 scale = tf->GetLocalScale();
		float alpha = 0.0f;
		if (mCurTime <= mEndTime)
		{
			scale = scale + mOffset;
			if (mAlphaType == EAlphaType::FadeIn)
			{
				alpha += mAlpha;
			}
			else if (mAlphaType == EAlphaType::FadeOut)
			{
				alpha -= mAlpha;
			}
		}
		else
		{
			if (mEndEvent != nullptr)
			{
				mEndEvent();
				mEndEvent = nullptr;
			}
			mbActive = false;
			mAlpha = 0.0f;
			mOffset = Vector3::Zero;
			mCurTime = 0.0f;
		}
		float resultAlpha = mesh->alpha + alpha;
		if (resultAlpha <= 0.0)
			mesh->alpha = 0.0f;
		else
			mesh->alpha = resultAlpha;

		tf->scale = scale;
	}

}
