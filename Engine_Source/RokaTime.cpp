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
	std::map<std::wstring, Time::CallBackEvent> Time::mEvents = {};
	std::queue<std::pair<Time::CallBackTimerInfo, std::weak_ptr<void>>> Time::mRequestRegisterEvent;
	std::queue<std::pair<Time::CallBackTimerInfo, std::function<void()>>> Time::mRequestEvent;
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
		size_t start_size = mRequestRegisterEvent.size();
		size_t cur_size = 0;
		while (mRequestRegisterEvent.empty() == false)
		{
			if (start_size == cur_size)
				break;
			std::pair<CallBackTimerInfo, std::weak_ptr<void>> value = mRequestRegisterEvent.front();
			mRequestRegisterEvent.pop();

			CallBackTimerInfo& info = value.first;
			std::weak_ptr<void> ptr = value.second;
			if (ptr.expired() == true)
				continue;
			std::wstring key = info.key;
			double endTime = info.endTime;
			double curTime = info.curTime;

			if (endTime <= curTime)
			{
				mEvents[key](ptr);
				continue;
			}

			info.curTime += DeltaTime();
			mRequestRegisterEvent.push(value);
			cur_size++;
		}
		start_size = mRequestEvent.size();
		if (start_size != 0)
			int a = 0;
		cur_size = 0;
		while (mRequestEvent.empty() == false)
		{
			if (start_size == cur_size)
				break;
			std::pair<CallBackTimerInfo,std::function<void()>> value = mRequestEvent.front();
			mRequestEvent.pop();
			CallBackTimerInfo& info = value.first;
			std::function<void()> func = value.second;
			double endTime = info.endTime;
			double curTime = info.curTime;
			if (endTime <= curTime)
			{
				func();
				continue;
			}
			info.curTime += DeltaTime();
			mRequestEvent.push(value);
			cur_size++;
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

	void Time::Release()
	{
		Clear();
	}

	void Time::Clear()
	{
		while (mRequestRegisterEvent.empty() == false)
		{
			mRequestRegisterEvent.pop();
		}
		while (mRequestEvent.empty() == false)
		{
			mRequestEvent.pop();
		}
	}

	void Time::RegisterEvent(std::wstring key,std::function<void(std::weak_ptr<void>)> func)
	{
		CallBackEvent callback = func;
		auto itr = mEvents.find(key);
		if (itr != mEvents.end())
			return;
		mEvents.insert(std::make_pair(key, callback));
	}

	void Time::RequestEvent(CallBackTimerInfo info, std::weak_ptr<void> ptr)
	{
		mRequestRegisterEvent.push(std::make_pair(info, ptr));
	}

	void Time::RequestEvent(CallBackTimerInfo info, std::function<void()> func)
	{
		mRequestEvent.push(std::make_pair(info, func));
	}

}
