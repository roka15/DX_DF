#include "Application.h"
#include "Input.h"
#include "RokaTime.h"
#include "Renderer.h"
#include "SceneManager.h"
#include "Resources.h"
#include "ComponentFactory.h"
#include "ScriptFactory.h"
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
		Destroy();
	}

	void Application::Initialize()
	{
		Time::Initiailize();
		Input::Initialize();

		roka::renderer::Initialize();
		SceneManager::Initialize();

		ComponentFactory::Initialize();
		ScriptFactory::Initialize();
	}

	void Application::Update()
	{
		Input::Update();
		Time::Update();
		
		SceneManager::Update();
	}

	void Application::LateUpdate()
	{
		SceneManager::LateUpdate();
	}

	void Application::Render()
	{
		Time::Render();

		graphicDevice->ClearTarget();
		graphicDevice->UpdateViewPort();
		renderer::Render();
		graphicDevice->Present();
	}

	void Application::Release()
	{
		renderer::Release();
		SceneManager::Release();
	}

	void Application::Destroy()
	{
		SceneManager::Destroy();
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