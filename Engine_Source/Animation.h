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
	class Animation :
		public Resource
	{
	public:
		Animation();
		virtual ~Animation();

		virtual HRESULT Load(const std::wstring& path) { return S_FALSE; };

		void Update();
		void LateUpdate();
		void Render();
		
		void Binds();
		void Reset();

		void Create(std::wstring npk_key, std::wstring pack_key,std::wstring set_name, UINT start_index,UINT end_index);

		void SetDuration(float duration) { mDuration = duration; }
		SET_PROPERTY(SetDuration) float duration;
		bool IsComplete() { return mIsComplete; }
		GET_PROPERTY(IsComplete) bool is_complete;

	private:
		std::shared_ptr<Texture> mAtlas;
		std::weak_ptr<Animator> mAnimator;
		std::vector<Sprite> mSprites;
		float mDuration;
		int mIndex;
		float mTime;
		bool mIsComplete;
	};
}


