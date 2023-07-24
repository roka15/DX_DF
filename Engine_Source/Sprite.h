#pragma once
#include "RokaEngine.h"
namespace roka
{
    using namespace math;
    class Sprite 
    {
    public:
        Sprite();
        virtual ~Sprite();
    
        void Create(std::wstring npk_key,std::wstring imagepack_key,UINT index);
        
        void SetLeftTop(const Vector2& pos) { mLeftTop = pos; }
        Vector2 GetLeftTop() { return mLeftTop; }
        Vector2 GetCanvaseSize() { return mCanvasSize; }
        Vector2 GetImageSize() { return mImageSize; }
        Vector2 GetOffset() { return mOffset; }
        PROPERTY(GetLeftTop,SetLeftTop) Vector2 lefttop;
        GET_PROPERTY(GetCanvaseSize) Vector2 canvas_size;
        GET_PROPERTY(GetImageSize) Vector2 image_size;
        GET_PROPERTY(GetOffset) Vector2 offset;
        
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


