#pragma once
#include "RokaEngine.h"

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
		};
		class CallBackEvent
		{
		public:
			CallBackTimerInfo info;
			std::function<void(void*)> func;
		};
		static void Initiailize();
		static void Update();
		static void Render();

		__forceinline static double DeltaTime() { return mDeltaTime; }

		static void RegisterEvent(std::wstring key, double end, std::function<void(void*)> func,void* this_ptr);
		static void ActiveEvent(std::wstring key, void* ptr);
	private:
		static double mDeltaTime;
		static double mSecond;
		static LARGE_INTEGER mCpuFrequency;
		static LARGE_INTEGER mPrevFrequency;
		static LARGE_INTEGER mCurFrequency;
		static std::map<std::wstring, std::shared_ptr<CallBackEvent>> mEvents;
		static std::map<std::wstring,std::map<void*, bool>> mEventActives;
	};
}
