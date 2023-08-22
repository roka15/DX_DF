#include "StructBuffer.h"
#include "RokaGraphicDevice_Dx11.h"
namespace roka::graphics
{
	StructBuffer::StructBuffer()
		:mSRV(nullptr)
		,mType(ESRVType::None)
		,mSize(0)
		,mStride(0)
	{
	}
	StructBuffer::~StructBuffer()
	{
	}
	bool StructBuffer::Create(UINT size, UINT stride, ESRVType type)
	{
		mSize = size;
		mStride = stride;
		mType = type;

		desc.ByteWidth = mSize * mStride;
		desc.StructureByteStride = mSize;

		desc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;
		desc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_SHADER_RESOURCE;
		desc.MiscFlags = D3D11_RESOURCE_MISC_FLAG::D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;

		if (!(GetDevice()->CreateBuffer(buffer.GetAddressOf(), &desc, nullptr)))
			return false;
		D3D11_SHADER_RESOURCE_VIEW_DESC  srvDesc = {};
		srvDesc.BufferEx.NumElements = mStride;
		srvDesc.ViewDimension = D3D_SRV_DIMENSION::D3D_SRV_DIMENSION_BUFFEREX;

		if (!(GetDevice()->CreateShaderResourceView(buffer.Get(), &srvDesc, mSRV.GetAddressOf())))
			return false;
		return true;
	}
	void StructBuffer::SetData(void* data, UINT stride)
	{
		if (mStride < stride)
			Create(mSize, stride, ESRVType::None);
		else
		{
			mStride = stride;
			GetDevice()->BindBuffer(buffer.Get(), data, mSize * mStride);
		}
	}
	void StructBuffer::Bind(EShaderStage stage, UINT slot)
	{
		GetDevice()->BindShaderResource(stage, slot, mSRV.GetAddressOf());
	}
}