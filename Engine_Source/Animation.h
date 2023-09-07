#pragma once
#include "MyResource.h"

namespace roka
{
	namespace graphics
	{
		class Texture;
	}

	using namespace graphics;

	class Sprite;
	class Animator;
	class GameObject;
	class Animation :
		public Resource
	{
	public:
		class AnimationEvent
		{
		public:
			double mTime;
			std::function<void()> mNormalFunc;
			std::function<void(float)> mFloatFunc;
			std::function<void(int)> mIntFunc;
			std::function<void(std::wstring)> mWstringFunc;
			std::function<void(std::shared_ptr<GameObject>)>mObjFunc;

			float mFloat;
			int mInt;
			std::wstring mWstring;
			std::shared_ptr<GameObject> mObject;
		};
		struct AnimationEventOperator
		{
			bool operator()(AnimationEvent src1, AnimationEvent src2)
			{
				return src1.mTime > src2.mTime;
			}
		};
	public:
		Animation();
		Animation(const Animation& ref);
		virtual ~Animation();

		virtual HRESULT Load(const std::wstring& path) { return S_FALSE; };

		void Update();
		void LateUpdate();
		void Render();

		void Binds();
		void Reset();

		void Create(std::wstring npk_key, std::wstring pack_key, std::wstring set_name, UINT start_index, UINT end_index);
		void SetAnimator(std::shared_ptr<Animator> ani) { mAnimator = ani; }
		void SetDuration(float duration) { mDuration = duration; }
		float GetDuration() { return mDuration; }
		bool IsComplete() { return mIsComplete; }
		void SetAtlas(std::shared_ptr<Texture> atlas) { mAtlas = atlas; }
		const Sprite& GetSprite();
		void SetPlayRange(std::pair<UINT, UINT> range) { mRange = range; }
		void AddIndex();
		PROPERTY(GetDuration, SetDuration) float duration;
		GET_PROPERTY(IsComplete) bool is_complete;
		SET_PROPERTY(SetPlayRange) std::pair<UINT, UINT> play_range;

		void AddTimeLineEvent(AnimationEvent aniEvent);
	private:
		void EventFunc();
	private:
		std::shared_ptr<Texture> mAtlas;
		std::weak_ptr<Animator> mAnimator;
		float mDuration;
		std::pair<UINT, UINT> mRange;
		int mIndex;
		float mTime;
		bool mIsComplete;

		std::vector<AnimationEvent> mEvents;
		std::vector<bool> mEventFlag;
		float mEventTime;
	};
}


