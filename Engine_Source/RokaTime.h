#pragma once
#include "RokaEngine.h"

#define WChar_t_MAX 256
namespace roka
{
	class Time
	{
	public:
		struct CallBackTimerInfo
		{
			double startTime;
			double endTime;
			double curTime;
			wchar_t key[WChar_t_MAX];
		};
		
		typedef std::function<void(std::weak_ptr<void>)> CallBackEvent;
		static void Initiailize();
		static void Update();
		static void Render();

		__forceinline static double DeltaTime() { return mDeltaTime; }

		static void RegisterEvent(std::wstring key, std::function<void(std::weak_ptr<void>)> func);
		static void RequestEvent(CallBackTimerInfo info, std::weak_ptr<void> ptr);
		static void RequestEvent(CallBackTimerInfo info, std::function<void()> func);
	private:
		static double mDeltaTime;
		static double mSecond;
		static LARGE_INTEGER mCpuFrequency;
		static LARGE_INTEGER mPrevFrequency;
		static LARGE_INTEGER mCurFrequency;
		static std::map<std::wstring, CallBackEvent> mEvents;
		static std::queue<std::pair<CallBackTimerInfo, std::weak_ptr<void>>> mRequestRegisterEvent;
		static std::queue<std::pair<CallBackTimerInfo, std::function<void()>>> mRequestEvent;
	};
}
