#include "RokaGraphicDevice_Dx11.h"
#include "Application.h"
#include "Renderer.h"
extern roka::Application application;
namespace roka::graphics
{
	GraphicDevice_Dx11::GraphicDevice_Dx11()
	{
		HWND hWnd = application.GetHwnd();
		UINT deviceFlag = D3D11_CREATE_DEVICE_DEBUG;
		D3D_FEATURE_LEVEL featurelevel = (D3D_FEATURE_LEVEL)0;

		D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr,
			deviceFlag, nullptr, 0,
			D3D11_SDK_VERSION, mDevice.GetAddressOf(), &featurelevel,
			mContext.GetAddressOf());

#pragma region Swap Chain
		DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
		swapChainDesc.BufferCount = 2;
		swapChainDesc.BufferDesc.Width = application.GetWidth();
		swapChainDesc.BufferDesc.Height = application.GetHeight();

		if (!CreateSwapChain(&swapChainDesc, hWnd))
			return;
#pragma endregion

		if (FAILED(mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)mRenderTarget.GetAddressOf())))
			return;

		mDevice->CreateRenderTargetView((ID3D11Resource*)mRenderTarget.Get(), nullptr,
			mRenderTargetView.GetAddressOf());

		D3D11_TEXTURE2D_DESC depthStencilDesc = {};
		depthStencilDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_DEPTH_STENCIL;
		//깊이정보만 저장할거라 4byte
		depthStencilDesc.Format = DXGI_FORMAT::DXGI_FORMAT_D24_UNORM_S8_UINT;
		depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
		depthStencilDesc.Width = application.GetWidth();
		depthStencilDesc.Height = application.GetHeight();
		//배열의 텍스쳐 수. 여러장 쓰는 경우 ex ) 그림자 표현할 때.
		//방법에 따라 다름 이 방법을 쓰면 연산량 증가하고, 그냥 그림자 이미지 넣으면 메모리 손해보지만 연산량은 비교적 손해 안봄.
		depthStencilDesc.ArraySize = 1;
		//다중 표본화를 위한 구조체 SampleDesc
		//픽셀 당 추출할 표본의 개수 지정.
		depthStencilDesc.SampleDesc.Count = 1;
		//퀄리티
		depthStencilDesc.MiscFlags = 0;
		
		D3D11_SUBRESOURCE_DATA data;
		if (!CreateTexture(&depthStencilDesc, &data))
			return;

		mContext->OMSetRenderTargets(1, mRenderTargetView.GetAddressOf(), mDepthStencilView.Get());

	}

	GraphicDevice_Dx11::~GraphicDevice_Dx11()
	{
	}
	bool GraphicDevice_Dx11::CreateSwapChain(const DXGI_SWAP_CHAIN_DESC* desc, HWND hwnd)
	{
		DXGI_SWAP_CHAIN_DESC dxgiDesc = {};
		dxgiDesc.OutputWindow = hwnd;
		//창모드인지
		dxgiDesc.Windowed = true;
		dxgiDesc.BufferCount = desc->BufferCount;
		//swap시 지워지도록 설정
		dxgiDesc.SwapEffect = DXGI_SWAP_EFFECT::DXGI_SWAP_EFFECT_DISCARD;

		//출력용
		dxgiDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		//크기
		dxgiDesc.BufferDesc.Width = desc->BufferDesc.Width;
		dxgiDesc.BufferDesc.Height = desc->BufferDesc.Height;
		//buffer 색상 설정
		dxgiDesc.BufferDesc.Format = DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM;
		//fps max / min
		dxgiDesc.BufferDesc.RefreshRate.Numerator = 240;
		dxgiDesc.BufferDesc.RefreshRate.Denominator = 1;

		//해상도에 맞게 이미지가 늘어날지 아닌지 현재 설정은 안늘어남.
		dxgiDesc.BufferDesc.Scaling = DXGI_MODE_SCALING::DXGI_MODE_SCALING_UNSPECIFIED;
		//이미지 그리는 순서 - 순서지정 안함.
		dxgiDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER::DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;

		//https://codingfarm.tistory.com/420
		dxgiDesc.SampleDesc.Count = 1;
		dxgiDesc.SampleDesc.Quality = 0;

		Microsoft::WRL::ComPtr<IDXGIDevice> pDXGIDevice = nullptr;
		Microsoft::WRL::ComPtr<IDXGIAdapter> pAdapter = nullptr;
		Microsoft::WRL::ComPtr<IDXGIFactory> pFactory = nullptr;

		if (FAILED(mDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)pDXGIDevice.GetAddressOf())))
			return false;
		if (FAILED(pDXGIDevice->GetParent(__uuidof(IDXGIAdapter), (void**)pAdapter.GetAddressOf())))
			return false;
		if (FAILED(pAdapter->GetParent(__uuidof(IDXGIFactory), (void**)pFactory.GetAddressOf())))
			return false;
		if (FAILED(pFactory->CreateSwapChain(mDevice.Get(), &dxgiDesc, mSwapChain.GetAddressOf())))
			return false;

		return true;
	}
	bool GraphicDevice_Dx11::CreateBuffer(ID3D11Buffer** buffer, D3D11_BUFFER_DESC* desc, D3D11_SUBRESOURCE_DATA* data)
	{
		if (FAILED(mDevice->CreateBuffer(desc, data, buffer)))
			return false;
		return true;
	}
	bool GraphicDevice_Dx11::CreateShader()
	{
		std::filesystem::path shaderPath = std::filesystem::current_path().parent_path();
		shaderPath += L"\\ShaderSource\\";
		std::filesystem::path vsPath(shaderPath.c_str());
		vsPath += L"TriangleVS.hlsl";

		D3DCompileFromFile(vsPath.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, 
			"main","vs_5_0", 0, 0, &roka::renderer::triangleVSBlob, &roka::renderer::errorBlob);

		if (roka::renderer::errorBlob)
		{
			OutputDebugStringA((char*)roka::renderer::errorBlob->GetBufferPointer());
			roka::renderer::errorBlob->Release();
		}

		mDevice->CreateVertexShader(roka::renderer::triangleVSBlob->GetBufferPointer(), roka::renderer::triangleVSBlob->GetBufferSize(),
			nullptr, &roka::renderer::triangleVSShader);

		return true;
	}
	bool GraphicDevice_Dx11::CreateTexture(const D3D11_TEXTURE2D_DESC* desc, void* data)
	{
		D3D11_TEXTURE2D_DESC dxgiDesc = {};
		dxgiDesc.BindFlags = desc->BindFlags;
		dxgiDesc.Usage = desc->Usage;
		//CPU access 설정 -0 은 access x
		dxgiDesc.CPUAccessFlags = 0;

		dxgiDesc.Format = desc->Format;
		dxgiDesc.Width = desc->Width;
		dxgiDesc.Height = desc->Height;
		dxgiDesc.ArraySize = desc->ArraySize;
		dxgiDesc.SampleDesc.Count = desc->SampleDesc.Count;
		dxgiDesc.SampleDesc.Quality = 0;

		//연산량을 줄이기 위해 크기별로 텍스쳐를 찍어두는것을 설정 할 수 있다.
		dxgiDesc.MipLevels = desc->MipLevels;
		dxgiDesc.MiscFlags = desc->MiscFlags;

		if (FAILED(mDevice->CreateTexture2D(&dxgiDesc, nullptr, mDepthStencilBuffer.ReleaseAndGetAddressOf())))
			return false;
		if (FAILED(mDevice->CreateDepthStencilView(mDepthStencilBuffer.Get(), nullptr, mDepthStencilView.GetAddressOf())))
			return false;
		
		return true;
	}
	void GraphicDevice_Dx11::Draw()
	{
		FLOAT bgColor[4] = { 0.3f,0.74f,0.88f,1.0f };
		mContext->ClearRenderTargetView(mRenderTargetView.Get(), bgColor);

		mSwapChain->Present(0, 0); 
	}
}

