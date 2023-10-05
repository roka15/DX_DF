#include "Application.h"
#include "Input.h"
#include "RokaTime.h"
#include "Renderer.h"
#include "SceneManager.h"
#include "Resources.h"
#include "..\\Engine\\FactoryManager.h"
#include "..\\Engine\\Prefab.h"
#include "ObjectPoolManager.h"
#include "..\\Engine\\AnimationObjectPool.h"
#include "..\\Engine\\NormalMonsterPool.h"
#include "..\\Engine\\WarningObjectPool.h"
#include "TestPool.h"
#include "CollisionManager.h"
#include "..\\Engine\\PartManager.h"
#include "..\\Engine\\SkillManager.h"
#include "..\\Engine\\PortalManager.h"
#include "..\\Engine\\InputManager.h"

namespace roka
{

	Application::Application()
		:mgraphicDevice(nullptr),
		mHwnd(NULL),
		mWidth(-1),
		mHeight(-1),
		mType(EApplicationType::Main),
		mbEditObjectActive(false)
	{
		mbActive = false;
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
		manager::InputManager::GetInstance()->Initialize();
		
		FactoryManager::Initialize();

	
		roka::renderer::Initialize();
		roka::prefab::Initialize();
		manager::PartManager::GetInstance()->Initialize();
		roka::prefab::LateInitialize();
		SceneManager::Initialize();
		manager::SkillManager::GetInstance()->Initialize();
		manager::PortalManager::GetInstance()->Initialize();
		
		ObjectPoolManager<AnimationObjectPool, GameObject>::GetInstance()->Initialize();
		ObjectPoolManager<WarningObjectPool, GameObject>::GetInstance()->Initialize();
	}

	void Application::Update()
	{
		Time::Update();
		Input::Update();
		manager::InputManager::GetInstance()->Update();
		CollisionManager::Update();
		SceneManager::Update();
	}

	void Application::LateUpdate()
	{
		manager::InputManager::GetInstance()->LateUpdate();
		SceneManager::LateUpdate();
		CollisionManager::LateUpdate();
	}

	void Application::Render()
	{
		Time::Render();
	
		ClearTarget();
		roka::graphics::GetDevice()->UpdateViewPort(mType);
		renderer::Render();
	}

	void Application::Release()
	{
		Time::Release();
		manager::InputManager::GetInstance()->Release();
		SceneManager::Release();
		manager::PortalManager::GetInstance()->Release();
		renderer::Release();
		prefab::Release();
		manager::SkillManager::GetInstance()->Release();
		ObjectPoolManager<AnimationObjectPool, GameObject>::GetInstance()->Release();
		ObjectPoolManager<WarningObjectPool, GameObject>::GetInstance()->Release();
	}

	void Application::Destroy()
	{
		SceneManager::Destroy();
	}

	void Application::Present()
	{
		roka::graphics::GetDevice()->Present(mType);
	}

	void Application::ClearTarget()
	{
		roka::graphics::GetDevice()->ClearTarget(mType,mBgColor);
	}

	void Application::SetWindow(HWND hwnd,UINT x,UINT y, UINT width, UINT height)
	{
		mHwnd = hwnd;
		mWidth = width;
		mHeight = height;
		if (roka::graphics::GetDevice() == nullptr)
		{
			mgraphicDevice = std::make_unique<roka::graphics::GraphicDevice_Dx11>();
			roka::graphics::GetDevice() = mgraphicDevice.get();
		}
		
		roka::graphics::GetDevice()->CreateRenderSetting(mType);

		RECT rt = { 0, 0, (LONG)width , (LONG)height };
		AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);
	
		SetWindowPos(mHwnd, nullptr, x, y, rt.right - rt.left, rt.bottom - rt.top, 0);
	
		ShowWindow(mHwnd, true);
		UpdateWindow(mHwnd);
	}

	void Application::SetWindowBGColor(float color[])
	{
		for (int i = 0; i < 4; i++)
			mBgColor[i] = color[i];
	}

	void Application::BindViewPort()
	{
		RECT rect = {};
		GetClientRect(mHwnd, &rect);
		GetDevice()->SetViewPort(0.0f, rect.right - rect.left,0.0f,rect.bottom - rect.top+WindowBarHeight);
	}

	void Application::BindViewPort(RECT rect)
	{
		GetDevice()->SetViewPort(rect.left, rect.right - rect.left,rect.top, rect.bottom - rect.top);
	}

}