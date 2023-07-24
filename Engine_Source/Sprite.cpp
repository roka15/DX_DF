#include "Sprite.h"
#include "Resources.h"
#include "NPK.h"
namespace roka
{
	Sprite::Sprite() :
		mLeftTop(Vector2::Zero),
		mCanvasSize(Vector2::Zero),
		mImageSize(Vector2::Zero),
		mOffset(Vector2::Zero),
		mNPKKey(L""),
		mPackKey(L""),
		mIndex(0)
	{
	}
	Sprite::~Sprite()
	{
	}
	void Sprite::Create(std::wstring npk_key, std::wstring imagepack_key, UINT index)
	{
		using namespace roka::file;
		
		std::shared_ptr<NPK> npk = Resources::Find<NPK>(npk_key);
		if (npk == nullptr)
		{
			return;
		}

		mCanvasSize = npk->GetCanvasSize(imagepack_key, index);
		mImageSize = npk->GetSize(imagepack_key,index);
		mOffset = npk->GetPos(imagepack_key, index);

		mNPKKey = npk_key;
		mPackKey = imagepack_key;
		mIndex = index;
	}
	void Sprite::SetRatioValue(const Vector2& resolution)
	{
		mLeftTop.x /= resolution.x;
		mLeftTop.y /= resolution.y;
		mImageSize.x = mCanvasSize.x;
		mImageSize.y = mCanvasSize.y;
		mCanvasSize = Vector2((mImageSize.x)/ resolution.x, (mImageSize.y) / resolution.y);
		mImageSize.x /= resolution.x;
		mImageSize.y /= resolution.y;
	}
}