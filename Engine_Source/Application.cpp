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
#include "DontDestroyOnLoad.h"
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
		manager::PartManager::GetInstance()->Initialize();
		roka::prefab::LateInitialize();
		SceneManager::Initialize();
		DontDestroyOnLoad::GetInstance()->Initialize();
		manager::SkillManager::GetInstance()->Initialize();
		manager::PortalManager::GetInstance()->Initialize();
		
		ObjectPoolManager<AnimationObjectPool, GameObject>::GetInstance()->Initialize();
		ObjectPoolManager<WarningObjectPool, GameObject>::GetInstance()->Initialize();
	}

	void Application::Update()
	{
		Time::Update();
		Input::Update();
		CollisionManager::Update();
		SceneManager::Update();
		DontDestroyOnLoad::GetInstance()->Update();
	}

	void Application::LateUpdate()
	{
		SceneManager::LateUpdate();
		DontDestroyOnLoad::GetInstance()->LateUpdate();
		CollisionManager::LateUpdate();
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
		Time::Release();
		SceneManager::Release();
		DontDestroyOnLoad::GetInstance()->Release();
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
		DontDestroyOnLoad::GetInstance()->Destroy();
	}

	void Application::Present()
	{
		graphicDevice->Present();
	}

	void Application::ClearTarget()
	{
		graphicDevice->ClearTarget();
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