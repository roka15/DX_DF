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
		, mIndex(-1)
		, mTime(0.0f)
		, mIsComplete(false)
		, mDuration(0.0f)
		, mRange(std::make_pair(0, 0))
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

		if (mDuration <= mTime)
		{
			mIndex++;
			mTime = 0.0f;
			if (mRange.second <= mIndex)
			{
				mIndex = mRange.second-1;
				mIsComplete = true;
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
		mAtlas->BindShader(graphics::EShaderStage::PS, 12);
		renderer::AnimationCB data = {};
		Sprite sprite = mAtlas->GetSprite(mIndex);
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
		if (mIndex >= mRange.second)
			mIndex = mRange.first;
	}
}