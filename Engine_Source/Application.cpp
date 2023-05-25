#include "Application.h"
#include "Input.h"
#include "RokaTime.h"
#include "Renderer.h"

namespace roka
{

	Application::Application()
		:graphicDevice(nullptr),
		mHwnd(NULL),
		mWidth(-1),
		mHeight(-1)
	{
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		Update();
		LateUpdate();
		Render();
	}

	void Application::Initialize()
	{
		Time::Initiailize();
		Input::Initialize();

		roka::renderer::Initialize();
	}

	void Application::Update()
	{
	}

	void Application::LateUpdate()
	{
	}

	void Application::Render()
	{
		Time::Render();

		graphicDevice->Draw();
	}

	void Application::SetWindow(HWND hwnd, UINT width, UINT height)
	{
		if (graphicDevice == nullptr)
		{
			mHwnd = hwnd;
			mWidth = width;
			mHeight = height;

			graphicDevice = std::make_unique<roka::graphics::GraphicDevice_Dx11>();
			roka::graphics::GetDevice() = graphicDevice.get();
		}

		RECT rt = { 0, 0, (LONG)width , (LONG)height };
		AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);
		SetWindowPos(mHwnd, nullptr, 0, 0, rt.right - rt.left, rt.bottom - rt.top, 0);
		ShowWindow(mHwnd, true);
		UpdateWindow(mHwnd);
	}

}