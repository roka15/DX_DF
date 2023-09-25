#pragma once
#include "RokaEngine.h"
namespace roka::graphics
{
    class Texture;
}
using namespace roka::graphics;
namespace roka
{
    using namespace math;
    class Sprite 
    {
    public:
        Sprite();
        Sprite(Vector2 canvasSize, Vector2 imageSize,Vector2 leftTop=Vector2::Zero,Vector2 offset=Vector2::Zero,UINT index=0);
        Sprite(const Sprite& ref);
        virtual ~Sprite();
    
        void Create(std::wstring npk_key,std::wstring imagepack_key,UINT index);
        void Create(std::shared_ptr<Texture> texture, int index);
        
        void SetLeftTop(const Vector2& pos) { mLeftTop = pos; }
        Vector2 GetLeftTop()const  { return mLeftTop; }
        Vector2 GetCanvaseSize()const { return mCanvasSize; }
        Vector2 GetImageSize()const { return mImageSize; }
        Vector2 GetOffset()const { return mOffset; }
        PROPERTY(GetLeftTop,SetLeftTop) Vector2 lefttop;
        GET_PROPERTY(GetCanvaseSize) const Vector2 canvas_size;
        GET_PROPERTY(GetImageSize) const Vector2 image_size;
        GET_PROPERTY(GetOffset) const Vector2 offset;
        
        std::wstring GetNpkKey() { return mNPKKey;}
        std::wstring GetPackKey() { return mPackKey;}
        UINT GetIndex() { return mIndex; }
        GET_PROPERTY(GetNpkKey) std::wstring npk_key;
        GET_PROPERTY(GetPackKey) std::wstring pack_key;
        GET_PROPERTY(GetIndex) UINT index;

        void SetRatioValue(const Vector2& resolution);
    private:
        Vector2 mLeftTop;
        Vector2 mCanvasSize;
        Vector2 mImageSize;
        Vector2 mOffset; // ÁÂÇ¥

        std::wstring mNPKKey;
        std::wstring mPackKey;
        UINT mIndex;
    };
}


