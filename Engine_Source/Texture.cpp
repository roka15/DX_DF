#include "Texture.h"
#include "RokaGraphicDevice_Dx11.h"



namespace roka::graphics
{
	using namespace math;
	Texture::Texture()
		:Resource(enums::EResourceType::Texture)
		, mImage{}
		, mTexture(nullptr)
		, mRTV(nullptr)
		, mSRV(nullptr)
		, mDSV(nullptr)
		, mUAV(nullptr)
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
	bool Texture::Create(UINT width, UINT height, DXGI_FORMAT format, UINT bindFlags)
	{
		if (mTexture == nullptr)
		{
			mDesc.BindFlags = bindFlags;
			mDesc.Usage = D3D11_USAGE_DEFAULT;
			mDesc.CPUAccessFlags = 0;
			mDesc.Width = width;
			mDesc.Height = height;
			mDesc.ArraySize = 1;
			mDesc.SampleDesc.Count = 1;
			mDesc.SampleDesc.Quality = 0;
			mDesc.MipLevels = 0;
			mDesc.MiscFlags = 0;

			if (!GetDevice()->CreateTexture2D(&mDesc, nullptr, mTexture.GetAddressOf()))
				return false;
		}

		if (bindFlags & (UINT)D3D11_BIND_FLAG::D3D11_BIND_DEPTH_STENCIL)
		{
			if (!GetDevice()->CreateDepthStencilView(mTexture.Get(), nullptr, mDSV.GetAddressOf()))
				return false;
		}
		if (bindFlags & (UINT)D3D11_BIND_FLAG::D3D11_BIND_SHADER_RESOURCE)
		{
			D3D11_SHADER_RESOURCE_VIEW_DESC tSRVDesc = {};
			tSRVDesc.Format = mDesc.Format;
			tSRVDesc.Texture2D.MipLevels = 1;
			tSRVDesc.Texture2D.MostDetailedMip = 0;
			tSRVDesc.ViewDimension = D3D11_SRV_DIMENSION::D3D11_SRV_DIMENSION_TEXTURE2D;

			if (!GetDevice()->CreateShaderResourceView(mTexture.Get(), &tSRVDesc, mSRV.GetAddressOf()))
				return false;
		}
		if (bindFlags & (UINT)D3D11_BIND_FLAG::D3D11_BIND_RENDER_TARGET)
		{
			D3D11_RENDER_TARGET_VIEW_DESC tRTVDesc = {};
			tRTVDesc.Format = mDesc.Format;
			tRTVDesc.Texture2D.MipSlice = 0;
			tRTVDesc.ViewDimension = D3D11_RTV_DIMENSION::D3D11_RTV_DIMENSION_TEXTURE2D;

			if (!GetDevice()->CreateRenderTargetView(mTexture.Get(), &tRTVDesc, mRTV.GetAddressOf()))
				return false;
		}
		if (bindFlags & (UINT)D3D11_BIND_FLAG::D3D11_BIND_UNORDERED_ACCESS)
		{
			D3D11_UNORDERED_ACCESS_VIEW_DESC tUAVDesc = {};
			tUAVDesc.Format = mDesc.Format;
			tUAVDesc.Texture1D.MipSlice = 0;
			tUAVDesc.ViewDimension = D3D11_UAV_DIMENSION::D3D11_UAV_DIMENSION_TEXTURE2D;

			if (!GetDevice()->CreateUnordedAccessView(mTexture.Get(), &tUAVDesc, mUAV.GetAddressOf()))
				return false;
		}
		return true;
	}
	void Texture::Create(const file::CSVInfo* csvs, const file::PackInfo* packs)
	{
		std::vector<std::shared_ptr<Texture>> textures;
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
			mDesc = textures[0]->mDesc;
			mTexture = textures[0]->GetTexture();
			Create(0, 0, mDesc.Format, D3D11_BIND_FLAG::D3D11_BIND_SHADER_RESOURCE);
			return;
		}

		CreateCanvasBaseTexture(csvs->canvas, count);
		CombineTextures(textures, count, csvs, packs);
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
	void  Texture::CreateCanvasBaseTexture(std::vector<std::pair<int, int>> canvas_sizes, int count)
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

		mDesc = desc;
		roka::graphics::GetDevice()->CreateTexture2D(&mDesc, nullptr, mTexture.GetAddressOf());
		Create(0, 0, mDesc.Format, D3D11_BIND_FLAG::D3D11_BIND_SHADER_RESOURCE);
		return;
	}
	std::shared_ptr<Texture>  Texture::CreateTexture(void* data, size_t size)
	{
		std::shared_ptr<Texture> texture = std::make_shared<Texture>();
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
			return nullptr;
		}

		unsigned char* buf = static_cast<unsigned char*>(data);
		// Create the PNG decoder
		hr = imagingFactory->CreateDecoderFromStream(reinterpret_cast<IStream*>(SHCreateMemStream(buf, size)), nullptr, WICDecodeMetadataCacheOnDemand, &bitmapDecoder);
		if (FAILED(hr)) {
			//"Error creating PNG decoder"
			imagingFactory->Release();
			return nullptr;
		}

		// Get the first frame of the PNG image
		hr = bitmapDecoder->GetFrame(0, &frameDecode);
		if (FAILED(hr)) {
			//"Error getting frame from PNG decoder"
			bitmapDecoder->Release();
			imagingFactory->Release();
			return nullptr;
		}
		// Convert the image format to 32-bit RGBA
		hr = imagingFactory->CreateFormatConverter(&formatConverter);
		if (FAILED(hr)) {
			//"Error creating format converter"
			frameDecode->Release();
			bitmapDecoder->Release();
			imagingFactory->Release();
			return nullptr;
		}

		hr = formatConverter->Initialize(frameDecode, pfguid, WICBitmapDitherTypeNone, nullptr, 0.0, WICBitmapPaletteTypeCustom);
		if (FAILED(hr)) {
			//"Error initializing format converter"
			formatConverter->Release();
			frameDecode->Release();
			bitmapDecoder->Release();
			imagingFactory->Release();
			return nullptr;
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
			return nullptr;
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

		texture->mDesc = desc;
		hr = roka::graphics::GetDevice()->CreateTexture2D(&desc, nullptr, texture->GetTexture().GetAddressOf());
		if (FAILED(hr)) {
			//"Error creating texture resource"
			formatConverter->Release();
			frameDecode->Release();
			bitmapDecoder->Release();
			imagingFactory->Release();
			return nullptr;
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
			return nullptr;
		}

		if (type == EChannelType::C24)
		{
			for (UINT i = 0; i < width * height; ++i)
			{
				pixelData[i * 4 + 3] = 255; // Alpha
			}
		}

		// Update the texture with the pixel data
		roka::graphics::GetDevice()->UpdateSubResource(texture->GetTexture().Get(), 0, nullptr, pixelData.data(), width * channel, 0);

		formatConverter->Release();
		frameDecode->Release();
		bitmapDecoder->Release();
		imagingFactory->Release();

		return texture;
	}
	void Texture::CombineTextures(std::vector<std::shared_ptr<Texture>> textures, int count, const file::CSVInfo* csv, const file::PackInfo* pack)
	{
		Vector2 LeftTop = { 0,0 };
		for (int i = 0; i < count; i++)
		{
			Vector2 canvas = Vector2(csv->canvas[i].first, csv->canvas[i].second);
			Vector2 imagesize = Vector2(csv->size[i].first, csv->size[i].second);
			Vector2 offset = Vector2(csv->pos[i].first, csv->pos[i].second);
			Microsoft::WRL::ComPtr<ID3D11Texture2D> src = textures[i]->GetTexture();

			D3D11_BOX box;
			box.front = 0;
			box.back = 1;
			box.left = 0;
			box.right = imagesize.x;
			box.top = 0;
			box.bottom = imagesize.y;


			graphics::GetDevice()->CopySubResourceRegion(mTexture.Get(), 0,
				LeftTop.x + offset.x, LeftTop.y + offset.y, 0,
				src.Get(), 0, &box);
			LeftTop.x += canvas.x;
		}

	}
}


