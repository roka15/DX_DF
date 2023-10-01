#include "Sprite.h"
#include "Resources.h"
#include "NPK.h"
#include "Texture.h"
#include <string.h>
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
	Sprite::Sprite(Vector2 canvasSize, Vector2 imageSize, Vector2 leftTop, Vector2 offset, UINT index)
	{
		mCanvasSize = canvasSize;
		mImageSize = imageSize;
		mLeftTop = leftTop;
		mOffset = offset;
		mIndex = index;
	}	
	Sprite::Sprite(const Sprite& ref)
	{
		mLeftTop = ref.mLeftTop;
		mCanvasSize = ref.mCanvasSize;
		mImageSize = ref.mImageSize;
		mOffset = ref.mOffset;
		size_t size = ref.mNPKKey.size();
		mNPKKey.resize(size);
		std::wcsncpy(mNPKKey.data(), ref.mNPKKey.c_str(),size);
		size = ref.mPackKey.size();
		mPackKey.resize(size);
		std::wcsncpy(mPackKey.data(), ref.mPackKey.c_str(),size);
	
		mIndex = ref.mIndex;
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
	void Sprite::Create(std::shared_ptr<Texture> texture, int index)
	{
		Sprite sprite = texture->GetSprite(index);
		mLeftTop = sprite.mLeftTop;
		mCanvasSize = sprite.mCanvasSize;
		mImageSize = sprite.mImageSize;
		mOffset = sprite.mOffset;
		size_t size = sprite.mNPKKey.size();
		mNPKKey.resize(size);
		std::wcsncpy(mNPKKey.data(), sprite.mNPKKey.c_str(), size);
		size = sprite.mPackKey.size();
		mPackKey.resize(size);
		std::wcsncpy(mPackKey.data(), sprite.mPackKey.c_str(), size);

		mIndex = sprite.mIndex;
	}
	void Sprite::SetRatioValue(const Vector2& resolution)
	{
		mLeftTop.x /= resolution.x;
		mLeftTop.y /= resolution.y;
		mOffset.x /= resolution.x;
		mOffset.y /= resolution.y;
		mImageSize.x /= resolution.x;
		mImageSize.y /= resolution.y;
		mCanvasSize = Vector2((mCanvasSize.x)/ resolution.x, (mCanvasSize.y) / resolution.y);
	}
}