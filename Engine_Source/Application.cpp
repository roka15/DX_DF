#include "Application.h"
#include "Input.h"
#include "RokaTime.h"
#include "Renderer.h"
#include "SceneManager.h"
#include "Resources.h"
#include "..\\Engine\\FactoryManager.h"
#include "..\\Engine\\Prefab.h"
#include "TestPool.h"
#include "CollisionManager.h"
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
		srand(time(NULL));

		Time::Initiailize();
		Input::Initialize();
		
		FactoryManager::Initialize();

		roka::renderer::Initialize();
		roka::prefab::Initialize();
		//test 나중에 object pool manager 만들면 변경
		//object::pool::ObjectPool<GameObject>::Initialize(prefab::Prefabs[L"TestObject"], 10);
		SceneManager::Initialize();

		
	}

	void Application::Update()
	{
		Time::Update();
		Input::Update();
		CollisionManager::Update();
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
	}

	void Application::Release()
	{
		SceneManager::Release();
		renderer::Release();
		//object::pool::ObjectPool<GameObject>::Release();
		prefab::Release();
	}

	void Application::Destroy()
	{
		SceneManager::Destroy();
	}

	void Application::Present()
	{
		graphicDevice->Present();
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