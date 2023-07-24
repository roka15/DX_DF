#pragma once
#include "Component.h"
#include "Animation.h"
namespace roka
{
	class Animator :
		public Component
	{
	public:
		struct Event
		{
			void operator=(std::function<void()> func)
			{
				mEvent = std::move(func);
			}
			void operator()()
			{
				if (mEvent)
					mEvent();
			}

			std::function<void()> mEvent;
		};
		struct Events
		{
			Event startEvent;
			Event completeEvent;
			Event endEvent;
		};

		Animator();
		~Animator();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		void Create(std::wstring npk_name,std::wstring pack_name,std::wstring set_name,int start_index,int end_index,float duration);
		std::shared_ptr<Animation> FindAnimation(const std::wstring& name);
		std::shared_ptr<Animator::Events> FindEvents(const std::wstring& name);
		void PlayAnimation(const std::wstring& name, bool loop, float duration=0.0f);
		void Binds();

		std::function<void()>& StartEvent(const std::wstring key);
		std::function<void()>& CompleteEvent(const std::wstring key);
		std::function<void()>& EndEvent(const std::wstring key);

	private:
		std::map<std::wstring, std::shared_ptr<Animation>> mAnimations;
		std::map<std::wstring, std::shared_ptr<Events>> mEvents;
		std::weak_ptr<Animation> mActiveAnimation;
		bool mIsLoop;
	};
}


