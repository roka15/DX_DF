#include "RokaTime.h"
#include "Application.h"

extern roka::Application application;
namespace roka
{
	double Time::mDeltaTime = 0.0l;
	double Time::mSecond = 0.0f;
	LARGE_INTEGER Time::mCpuFrequency = {};
	LARGE_INTEGER Time::mPrevFrequency = {};
	LARGE_INTEGER Time::mCurFrequency = {};
	std::map<std::wstring, std::shared_ptr<Time::CallBackEvent>> Time::mEvents = {};
	std::map<std::wstring, std::map<void*, bool>> Time::mEventActives = {};
	void Time::Initiailize()
	{	 
		// CPU 고유 진동수 가져오기
		QueryPerformanceFrequency(&mCpuFrequency);

		// 프로그램이 처음 시작할때 진동수
		QueryPerformanceCounter(&mPrevFrequency);
	}	 
		 
	void Time::Update()
	{
		QueryPerformanceCounter(&mCurFrequency);

		double differnceFrequency = mCurFrequency.QuadPart - mPrevFrequency.QuadPart;

		mDeltaTime = differnceFrequency / mCpuFrequency.QuadPart;

		mPrevFrequency.QuadPart = mCurFrequency.QuadPart;

		for (auto map1 : mEventActives)
		{
			for (auto& map2 : map1.second)
			{
				if (map2.second == true)
				{
					std::wstring key = map1.first;
					CallBackTimerInfo& info = mEvents[key]->info;
					if (info.curTime >= info.endTime)
					{
						void* ptr = map2.first;
						mEvents[key]->func(ptr);

						info.curTime = 0.0f;
						info.endTime = 0.0f;
						map2.second = false;
						continue;
					}
					info.curTime += DeltaTime();
				}
			}
		}
	}	 
		 
	void Time::Render()
	{
		mSecond += mDeltaTime;

		if (mSecond > 1.0f)
		{
			HWND hWnd = application.GetHwnd();

			wchar_t szFloat[50] = {};
			float FPS = 1.0f / (float)mDeltaTime;
			swprintf_s(szFloat, 50, L"FPS : %d", (UINT)FPS);
			//int iLen = wcsnlen_s(szFloat, 50);
			SetWindowText(hWnd, szFloat);

			//TextOut(hdc, 0, 0, szFloat, 20);
			mSecond = 0.0f;
		}
	}

	void Time::RegisterEvent(std::wstring key,double end,std::function<void(void*)> func, void* this_ptr)
	{
		CallBackTimerInfo info = {};
		info.endTime = end;
		std::shared_ptr<CallBackEvent> callback = std::make_shared<CallBackEvent>();
		callback->info = info;
		callback->func = func;
		mEvents.insert(std::make_pair(key, callback));
		mEventActives.insert(std::make_pair(key, std::map<void*,bool>()));
		mEventActives[key].insert(std::make_pair(this_ptr, false));
	}

	void Time::ActiveEvent(std::wstring key, void* ptr)
	{
		mEventActives[key][ptr] = true; 
	}

}
