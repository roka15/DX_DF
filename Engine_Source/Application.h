#pragma once
#include "RokaEngine.h"
#include "RokaGraphicDevice_Dx11.h"
#include "Scene.h"
namespace roka
{
	class Application
	{
	public:
		Application();
		virtual ~Application();

		virtual void Run();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();
		virtual void Release();
		virtual void Destroy(); 

		void Present();

		void ClearTarget();
		void SetWindow(HWND hwnd, UINT x, UINT y, UINT width, UINT height);

		UINT GetWidth() { return mWidth; }
		UINT GetHeight() { return mHeight; }
		HWND GetHwnd() { return mHwnd; }

		void SetWindowBGColor(float color[]);
		void SetActive(bool active) { mbActive = active; }
		bool GetActive() { return mbActive; }
	protected:
		bool mbInitialize = false;
		// 오로지 한개의 객체만 만들수 있는 스마트 포인터
		std::unique_ptr<roka::graphics::GraphicDevice_Dx11> mgraphicDevice;

		// HDC mHdc; -> GPU API
		HWND mHwnd;
		UINT mWidth;
		UINT mHeight;
		float mBgColor[4];

		EApplicationType mType;
		bool mbActive;
	};
}


