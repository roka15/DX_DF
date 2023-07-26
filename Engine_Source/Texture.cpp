#include "Texture.h"
#include "RokaGraphicDevice_Dx11.h"



namespace roka::graphics
{
	using namespace math;
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
	void Texture::Create(const file::CSVInfo* csvs, const file::PackInfo* packs)
	{
		std::vector<Microsoft::WRL::ComPtr<ID3D11Texture2D>> textures;
		int count = packs->binbuf.size();
		for (int i = 0; i < count; i++)
		{
			textures.push_back(CreateTexture(packs->binbuf[i]->buffer, packs->binbuf[i]->length));
		}


		Vector2 canvas = Vector2(csvs->canvas[0].first, csvs->canvas[0].second);
		Vector2 imagesize = Vector2(csvs->size[0].first, csvs->size[0].second);
		Vector2 offset = Vector2(csvs->pos[0].first, csvs->pos[0].second);

		if (canvas.x * count == imagesize.x && canvas.y == imagesize.y)
		{
			mTexture = textures[0];
			return;
		}

		Microsoft::WRL::ComPtr<ID3D11Texture2D> dest = CreateCanvasBaseTexture(csvs->canvas, count);

		CombineTextures(textures, dest, count, csvs, packs);
	}
	void Texture::Create(void* data, size_t size)
	{
		IWICImagingFactory* imagingFactory = nullptr;
		IWICBitmapDecoder* bitmapDecoder = nullptr;
		IWICBitmapFrameDecode* frameDecode = nullptr;
		IWICFormatConverter* formatConverter = nullptr;

		UINT channel_count = 0;

		//read color type
		char* read_point = (char*)data + 25;
		memcpy(&channel_count, read_point, 1);

		GUID pfguid = GUID_WICPixelFormat32bppRGBA;
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
			return;
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
		roka::graphics::GetDevice()->UpdateSubResource(mTexture.Get(), 0, nullptr, pixelData.data(), width * channel, 0);

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
	Microsoft::WRL::ComPtr<ID3D11Texture2D> Texture::CreateCanvasBaseTexture(std::vector<std::pair<int,int>> canvas_sizes, int count)
	{
		Vector2 length = { };
		int height = 0;
		for (int i = 0; i < count; i++)
		{
			length.x += canvas_sizes[i].first;
			if (canvas_sizes[i].second > height)
				height = canvas_sizes[i].second;
		}
		length.y = height;
		Microsoft::WRL::ComPtr<ID3D11Texture2D> texture;
		D3D11_TEXTURE2D_DESC desc = {};
		desc.Format = DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM;
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.Width = length.x;
		desc.Height = length.y;
		desc.MipLevels = 1;
		desc.ArraySize = 1;
		desc.SampleDesc.Count = 1;
		desc.SampleDesc.Quality = 0;
		desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		desc.CPUAccessFlags = 0;
		desc.MiscFlags = 0;

		roka::graphics::GetDevice()->CreateTexture(&desc, nullptr, texture.GetAddressOf(), 32);
		return texture;
	}
	Microsoft::WRL::ComPtr<ID3D11Texture2D> Texture::CreateTexture(void* data, size_t size)
	{
		Microsoft::WRL::ComPtr<ID3D11Texture2D> texture = nullptr;
		IWICImagingFactory* imagingFactory = nullptr;
		IWICBitmapDecoder* bitmapDecoder = nullptr;
		IWICBitmapFrameDecode* frameDecode = nullptr;
		IWICFormatConverter* formatConverter = nullptr;

		UINT channel_count = 0;

		//read color type
		char* read_point = (char*)data + 25;
		memcpy(&channel_count, read_point, 1);

		GUID pfguid = GUID_WICPixelFormat32bppRGBA;
		EChannelType type = EChannelType::C32;
		
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
			return texture;
		}

		unsigned char* buf = static_cast<unsigned char*>(data);
		// Create the PNG decoder
		hr = imagingFactory->CreateDecoderFromStream(reinterpret_cast<IStream*>(SHCreateMemStream(buf, size)), nullptr, WICDecodeMetadataCacheOnDemand, &bitmapDecoder);
		if (FAILED(hr)) {
			//"Error creating PNG decoder"
			imagingFactory->Release();
			return texture;
		}

		// Get the first frame of the PNG image
		hr = bitmapDecoder->GetFrame(0, &frameDecode);
		if (FAILED(hr)) {
			//"Error getting frame from PNG decoder"
			bitmapDecoder->Release();
			imagingFactory->Release();
			return texture;
		}
		// Convert the image format to 32-bit RGBA
		hr = imagingFactory->CreateFormatConverter(&formatConverter);
		if (FAILED(hr)) {
			//"Error creating format converter"
			frameDecode->Release();
			bitmapDecoder->Release();
			imagingFactory->Release();
			return texture;
		}

		hr = formatConverter->Initialize(frameDecode, pfguid, WICBitmapDitherTypeNone, nullptr, 0.0, WICBitmapPaletteTypeCustom);
		if (FAILED(hr)) {
			//"Error initializing format converter"
			formatConverter->Release();
			frameDecode->Release();
			bitmapDecoder->Release();
			imagingFactory->Release();
			return texture;
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
			return texture;
		}

		D3D11_TEXTURE2D_DESC desc = {};
		desc.Width = width;
		desc.Height = height;
		desc.MipLevels = 1;
		desc.ArraySize = 1;
		desc.SampleDesc.Count = 1;
		desc.SampleDesc.Quality = 0;
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		desc.CPUAccessFlags = 0;
		desc.MiscFlags = 0;
		desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

		hr = roka::graphics::GetDevice()->CreateTexture(&desc, nullptr, texture.GetAddressOf(), channel);
		if (FAILED(hr)) {
			//"Error creating texture resource"
			formatConverter->Release();
			frameDecode->Release();
			bitmapDecoder->Release();
			imagingFactory->Release();
			return texture;
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
			return texture;
		}

		if (type == EChannelType::C24)
		{
			for (UINT i = 0; i < width * height; ++i)
			{
				pixelData[i * 4 + 3] = 255; // Alpha
			}
		}

		// Update the texture with the pixel data
		roka::graphics::GetDevice()->UpdateSubResource(texture.Get(), 0, nullptr, pixelData.data(), width * channel, 0);

		formatConverter->Release();
		frameDecode->Release();
		bitmapDecoder->Release();
		imagingFactory->Release();

		
		mSRVDesc.Format = desc.Format;
		mSRVDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		mSRVDesc.Texture2D.MostDetailedMip = 0;
		mSRVDesc.Texture2D.MipLevels = 1;

		mSRV.Reset();
		roka::graphics::GetDevice()->GetID3D11Device()->CreateShaderResourceView(texture.Get(), &mSRVDesc, mSRV.GetAddressOf());

		return texture;
	}
	void Texture::CombineTextures(std::vector<Microsoft::WRL::ComPtr<ID3D11Texture2D>> textures, Microsoft::WRL::ComPtr<ID3D11Texture2D> base, int count, const file::CSVInfo* csv, const file::PackInfo* pack)
	{
		Vector2 LeftTop = { 0,0 };
		for (int i = 0; i < count; i++)
		{
			Vector2 canvas = Vector2(csv->canvas[i].first, csv->canvas[i].second);
			Vector2 imagesize = Vector2(csv->size[i].first, csv->size[i].second);
			Vector2 offset = Vector2(csv->pos[i].first, csv->pos[i].second);
			Microsoft::WRL::ComPtr<ID3D11Texture2D> src = textures[i];

			D3D11_BOX box;
			box.front = 0;
			box.back = 1;
			box.left = 0;
			box.right = imagesize.x;
			box.top = 0;
			box.bottom = imagesize.y;


			graphics::GetDevice()->CopySubResourceRegion(base.Get(), 0,
				LeftTop.x + offset.x, LeftTop.y + offset.y, 0,
				src.Get(), 0, &box);
			LeftTop.x += canvas.x;
		}

		mSRV.Reset();

		mSRVDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		mSRVDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		mSRVDesc.Texture2D.MostDetailedMip = 0;
		mSRVDesc.Texture2D.MipLevels = 1;
		roka::graphics::GetDevice()->GetID3D11Device()->CreateShaderResourceView(base.Get(), &mSRVDesc, mSRV.GetAddressOf());
		mTexture = base;
	}
}


