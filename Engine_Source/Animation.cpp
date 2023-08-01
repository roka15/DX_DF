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
		, mSprites{}
		, mIndex(-1)
		, mTime(0.0f)
		, mIsComplete(false)
		, mDuration(0.0f)
	{
	}
	Animation::Animation(const Animation& ref):Resource(ref)
	{
		mAtlas = ref.mAtlas;
		for (const auto& copy_sprite : ref.mSprites)
		{
			Sprite sprite = copy_sprite;
			mSprites.push_back(sprite);
		}
		mDuration = ref.mDuration;
		mIndex = 0;
		mTime = 0;
		mIsComplete = false;
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
			if (mSprites.size() <= mIndex)
			{
				mIndex = mSprites.size() - 1;
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
		data.SpriteLeftTop = mSprites[mIndex].lefttop;
		data.SpriteOffset = mSprites[mIndex].offset;
		data.SpriteSize = mSprites[mIndex].image_size;
		data.CanvasSize = mSprites[mIndex].canvas_size;

		ConstantBuffer* cb = renderer::constantBuffer[(UINT)ECBType::Animation];
		cb->SetData(&data);

		cb->Bind(EShaderStage::VS);
		cb->Bind(EShaderStage::PS);
	}
	void Animation::Reset()
	{
		mTime = 0.0f;
		mIsComplete = false;
		mIndex = 0;
	}
	void Animation::Create(std::wstring npk_key, std::wstring pack_key, std::wstring set_name, UINT start_index, UINT end_index)
	{
		Vector2 LeftTop = {};
		float width = 0;
		float height = 0;
		
		for (int i = start_index; i < end_index; i++)
		{
			Sprite sprite;
			sprite.lefttop = LeftTop;
			sprite.Create(npk_key, pack_key, i);

			LeftTop.x += sprite.canvas_size.x;
			if (height < sprite.canvas_size.y)
				height = sprite.canvas_size.y;
			mSprites.push_back(sprite);
		}
		width = LeftTop.x;

		for (auto& sprite : mSprites)
		{
			sprite.SetRatioValue(Vector2(width, height));
		}

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
		return mSprites[mIndex];
	}
}