#include "Animation.h"
#include "Renderer.h"
#include "Sprite.h"
#include "Animation.h"
#include "Texture.h"
#include "NPK.h"
#include "Resources.h"
#include "RokaTime.h"
namespace roka
{
	Animation::Animation() :Resource(enums::EResourceType::Animation)
		, mAtlas(nullptr)
		, mAnimator()
		, mIndex(0)
		, mTime(0.0f)
		, mIsComplete(false)
		, mDuration(0.0f)
		, mRange(std::make_pair(0, 0))
		,mEventTime(0.0f)
	{
	}
	Animation::Animation(const Animation& ref) :Resource(ref)
	{
		mAtlas = ref.mAtlas;
		mDuration = ref.mDuration;
		mIndex = 0;
		mTime = 0;
		mIsComplete = false;
		mRange.first = ref.mRange.first;
		mRange.second = ref.mRange.second;
		mEventTime = 0.0f;
	}
	Animation::~Animation()
	{
	}
	void Animation::Update()
	{
	}
	void Animation::LateUpdate()
	{
		if (mIsComplete)
			return;

		mTime += Time::DeltaTime();
		mEventTime += Time::DeltaTime();
		
		EventFunc();
		if (mDuration <= mTime)
		{
			mIndex++;
			mTime = 0.0f;
			if (mRange.second <= mIndex)
			{
				if (mRange.first == mRange.second)
					mIndex = mRange.second;
				else
					mIndex = mRange.second - 1;
				mIsComplete = true;
				std::replace(mEventFlag.begin(), mEventFlag.end(), true, false);
			}
		}
	}
	void Animation::Render()
	{
	}
	void Animation::Binds()
	{
		if (mAtlas == nullptr)
			return;
		mAtlas->BindShaderResource(graphics::EShaderStage::PS, 12);
		renderer::AnimationCB data = {};
		Sprite sprite = mAtlas->GetSprite(mIndex);
		mAtlas->SetCurSpriteIndex(mIndex);
		data.SpriteLeftTop = sprite.lefttop;
		data.SpriteOffset = sprite.offset;
		data.SpriteSize = sprite.image_size;
		data.CanvasSize = sprite.canvas_size;

		ConstantBuffer* cb = renderer::constantBuffer[(UINT)ECBType::Animation];
		cb->SetData(&data);

		cb->Bind(EShaderStage::VS);
		cb->Bind(EShaderStage::PS);
	}
	void Animation::Reset()
	{
		mTime = 0.0f;
		mEventTime = 0.0f;
		mIsComplete = false;
		mIndex = mRange.first;
	}
	void Animation::Create(std::wstring npk_key, std::wstring pack_key, std::wstring set_name, UINT start_index, UINT end_index)
	{
		std::shared_ptr<NPK> npk = Resources::Find<NPK>(npk_key);
		if (npk == nullptr)
			return;
		mAtlas = Resources::Find<Texture>(set_name + L"AtlasTexture");
		if (mAtlas != nullptr)
			return;
		mAtlas = npk->CreateAtlas(pack_key, start_index, end_index, set_name);
	}
	const Sprite& Animation::GetSprite()
	{
		return  mAtlas->GetSprite(mIndex);
	}
	void Animation::AddIndex()
	{
		mIndex++;
		if (mIndex == 3)
			int a = 0;
		if (mIndex >= mRange.second)
			mIndex = mRange.first;
	}
	void Animation::AddTimeLineEvent(AnimationEvent aniEvent)
	{
		mEvents.push_back(aniEvent);
		mEventFlag.push_back(false);
	}
	void Animation::EventFunc()
	{
		int index = 0;
		for (auto aniEvent : mEvents)
		{
			if (mEventFlag[index] == true)
				continue;
			if (aniEvent.mTime <= mEventTime)
			{
				if (aniEvent.mNormalFunc != nullptr)
				{
					aniEvent.mNormalFunc();
				}
				else if (aniEvent.mObjFunc != nullptr)
				{
					aniEvent.mObjFunc(aniEvent.mObject);
				}
				
				mEventFlag[index] = true;
				if (GetKey().compare(L"tairang_Skill01_start") == 0)
				{
					if (mEventFlag[2] == true)
					{
						int a = 0;
					}
				}
			}
			index++;
		}
	}
}