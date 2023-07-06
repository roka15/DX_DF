#include "Texture.h"
#include "RokaGraphicDevice_Dx11.h"



namespace roka::graphics
{
	Texture::Texture()
		:Resource(enums::EResourceType::Texture)
		, mImage{}
		, mTexture(nullptr)
		, mSRV(nullptr)
		, mDesc{}
		, mSRVDesc{}
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
			if (FAILED(LoadFromWICFile(path.c_str(), WIC_FLAGS::WIC_FLAGS_IGNORE_SRGB, nullptr, mImage)))
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
	void Texture::Create(void* data,size_t size)
	{
		IWICImagingFactory* imagingFactory = nullptr;
		IWICBitmapDecoder* bitmapDecoder = nullptr;
		IWICBitmapFrameDecode* frameDecode = nullptr;
		IWICFormatConverter* formatConverter = nullptr;
		
		UINT channel_count = 0;
		
		//read color type
		char* read_point = (char*)data +25;
		memcpy(&channel_count, read_point, 1);

		GUID pfguid= GUID_WICPixelFormat32bppRGBA;
		EChannelType type = EChannelType::C32;
		mDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		switch (channel_count)
		{
		case 2:
			type = EChannelType::C24;
			break;
		case 6:
			type = EChannelType::C32;
			break;
		}

		int channel = 4;
		
		// Initialize Windows Imaging Component (WIC)
		HRESULT hr = CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&imagingFactory));
		if (FAILED(hr)) {
			//"Error initializing Windows Imaging Component" 
			return;
		}
		
		unsigned char* buf = static_cast<unsigned char*>(data);
		// Create the PNG decoder
		hr = imagingFactory->CreateDecoderFromStream(reinterpret_cast<IStream*>(SHCreateMemStream(buf, size)), nullptr, WICDecodeMetadataCacheOnDemand, &bitmapDecoder);
		if (FAILED(hr)) {
			//"Error creating PNG decoder"
			imagingFactory->Release();
			return;
		}

		// Get the first frame of the PNG image
		hr = bitmapDecoder->GetFrame(0, &frameDecode);
		if (FAILED(hr)) {
			//"Error getting frame from PNG decoder"
			bitmapDecoder->Release();
			imagingFactory->Release();
			return;
		}
		// Convert the image format to 32-bit RGBA
		hr = imagingFactory->CreateFormatConverter(&formatConverter);
		if (FAILED(hr)) {
			//"Error creating format converter"
			frameDecode->Release();
			bitmapDecoder->Release();
			imagingFactory->Release();
			return;
		}
		
		hr = formatConverter->Initialize(frameDecode, pfguid, WICBitmapDitherTypeNone, nullptr, 0.0, WICBitmapPaletteTypeCustom);
		if (FAILED(hr)) {
			//"Error initializing format converter"
			formatConverter->Release();
			frameDecode->Release();
			bitmapDecoder->Release();
			imagingFactory->Release();
			return ;
		}
		// Retrieve image dimensions
		UINT width, height;
		hr = formatConverter->GetSize(&width, &height);
		if (FAILED(hr)) {
			//"Error getting image size"
			formatConverter->Release();
			frameDecode->Release();
			bitmapDecoder->Release();
			imagingFactory->Release();
			return;
		}
		mDesc.Width = width;
		mDesc.Height = height;
		mDesc.MipLevels = 1;
		mDesc.ArraySize = 1;
		mDesc.SampleDesc.Count = 1;
		mDesc.SampleDesc.Quality = 0;
		mDesc.Usage = D3D11_USAGE_DEFAULT;
		mDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		mDesc.CPUAccessFlags = 0;
		mDesc.MiscFlags = 0;

		hr = roka::graphics::GetDevice()->CreateTexture(&mDesc, nullptr, mTexture.GetAddressOf(), channel);
		if (FAILED(hr)) {
			//"Error creating texture resource"
			formatConverter->Release();
			frameDecode->Release();
			bitmapDecoder->Release();
			imagingFactory->Release();
			return;
		}

		// Retrieve the pixel data from the format converter
		UINT bufferSize = width * height * channel; // 4 bytes per pixel (RGBA)
		std::vector<BYTE> pixelData(bufferSize);
		hr = formatConverter->CopyPixels(nullptr, width * channel, bufferSize, pixelData.data());
		if (FAILED(hr)) {
			//"Error copying pixel data"
			formatConverter->Release();
			frameDecode->Release();
			bitmapDecoder->Release();
			imagingFactory->Release();
			return;
		}

		if (type == EChannelType::C24)
		{
			for (UINT i = 0; i < width * height; ++i)
			{
				pixelData[i * 4 + 3] = 255; // Alpha
			}
		}
		
		// Update the texture with the pixel data
		roka::graphics::GetDevice()->UpdateSubResource(mTexture.Get(), 0,nullptr, pixelData.data(), width* channel, 0);
		
		formatConverter->Release();
		frameDecode->Release();
		bitmapDecoder->Release();
		imagingFactory->Release();

		ID3D11ShaderResourceView* pSRV = nullptr;

		mSRVDesc.Format = mDesc.Format;
		mSRVDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		mSRVDesc.Texture2D.MostDetailedMip = 0;
		mSRVDesc.Texture2D.MipLevels = 1;

		roka::graphics::GetDevice()->GetID3D11Device()->CreateShaderResourceView(mTexture.Get(), &mSRVDesc, mSRV.GetAddressOf());
	}
	void Texture::Clear()
	{
		ID3D11ShaderResourceView* rsv = nullptr;
		GetDevice()->BindShaderResource(EShaderStage::VS, 0, &rsv);
		GetDevice()->BindShaderResource(EShaderStage::DS, 0, &rsv);
		GetDevice()->BindShaderResource(EShaderStage::GS, 0, &rsv);
		GetDevice()->BindShaderResource(EShaderStage::HS, 0, &rsv);
		GetDevice()->BindShaderResource(EShaderStage::CS, 0, &rsv);
		GetDevice()->BindShaderResource(EShaderStage::PS, 0, &rsv);
	}
}


