#include "Texture.h"
#include "RokaGraphicDevice_Dx11.h"
namespace roka::graphics
{
	Texture::Texture()
		:Resource(enums::EResourceType::Texture)
		,mImage{}
		,mTexture(nullptr)
		,mSRV(nullptr)
		, mDesc{}
	{
	}

	Texture::~Texture()
	{
	}

	HRESULT Texture::Load(const std::wstring& path)
	{
		wchar_t szExtension[50] = {};
		_wsplitpath_s(path.c_str(), nullptr, 0, nullptr, 0, nullptr, 0, szExtension, 50);

		std::wstring extension = szExtension;
		if (extension == L".dds" || extension == L".DDS")
		{
			if (FAILED(LoadFromDDSFile(path.c_str(), DDS_FLAGS::DDS_FLAGS_NONE, nullptr, mImage)))
				return S_FALSE;
		}
		else if (extension == L".tga" || extension == L".TGA")
		{
			if (FAILED(LoadFromTGAFile(path.c_str(), nullptr, mImage)))
				return S_FALSE;
		}
		else // WIC (png, jpg, jpeg, bmp )
		{
			if (FAILED(LoadFromWICFile(path.c_str(), WIC_FLAGS::WIC_FLAGS_NONE, nullptr, mImage)))
				return S_FALSE;
		}

		CreateShaderResourceView
		(
			GetDevice()->GetID3D11Device()
			, mImage.GetImages()
			, mImage.GetImageCount()
			, mImage.GetMetadata()
			, mSRV.GetAddressOf()
		);
		mSRV->GetResource((ID3D11Resource**)mTexture.GetAddressOf());

		return S_OK;
	}

	void Texture::BindShader(EShaderStage stage, UINT startSlot)
	{
		GetDevice()->BindShaderResource(stage, startSlot, mSRV.GetAddressOf());
	}
	void Texture::Clear()
	{
		ID3D11ShaderResourceView* rsv =nullptr;
		GetDevice()->BindShaderResource(EShaderStage::VS, 0, &rsv);
		GetDevice()->BindShaderResource(EShaderStage::DS, 0, &rsv);
		GetDevice()->BindShaderResource(EShaderStage::GS, 0, &rsv);
		GetDevice()->BindShaderResource(EShaderStage::HS, 0, &rsv);
		GetDevice()->BindShaderResource(EShaderStage::CS, 0, &rsv);
		GetDevice()->BindShaderResource(EShaderStage::PS, 0, &rsv);
	}
}


