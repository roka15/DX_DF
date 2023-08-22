#pragma once
#include "Entity.h"
#include "RokaGraphics.h"

namespace roka::graphics
{
    class StructBuffer :
        public GpuBuffer
    {
    public:
        StructBuffer();
        ~StructBuffer();

        bool Create(UINT size, UINT stride, ESRVType type);
        void SetData(void* data, UINT stride);
        void Bind(EShaderStage stage, UINT slot);

        UINT GetSize() { return mSize;}
        UINT GetStride() { return mStride; }
    private:
        Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mSRV;
        ESRVType mType;

        UINT mSize;
        UINT mStride;
    };

}


