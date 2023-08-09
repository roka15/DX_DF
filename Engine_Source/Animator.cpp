#include "Animator.h"
#include "Sprite.h"
#include "GameObject.h"
namespace roka
{
	Animator::Animator() :Component(EComponentType::Animator)
		, mAnimations{}
		, mEvents{}
		, mActiveAnimation()
		, mFirstUpdateAnimation()
		, mbLoop(false)
	{
	}
	Animator::Animator(const Animator& ref) :Component(ref)
	{
		for (auto map : ref.mAnimations)
		{
			std::shared_ptr<Animation> animation = std::make_shared<Animation>(*(map.second));
			mAnimations.insert(std::make_pair(map.first, animation));
		}
		for (auto map : ref.mEvents)
		{
			mEvents.insert(std::make_pair(map.first, std::make_shared<Events>()));
			mEvents[map.first]->completeEvent = map.second->completeEvent;
			mEvents[map.first]->endEvent = map.second->endEvent;
			mEvents[map.first]->startEvent = map.second->startEvent;
		}
		mActiveAnimation = ref.mActiveAnimation.lock();
		mFirstUpdateAnimation = ref.mFirstUpdateAnimation.lock();
		mbLoop = ref.mbLoop;
	}
	void Animator::Copy(Component* src)
	{
		Component::Copy(src);
		Animator* source = dynamic_cast<Animator*>(src);
		for (auto map : source->mAnimations)
		{
			std::shared_ptr<Animation> animation = std::make_shared<Animation>(*(map.second));
			mAnimations.insert(std::make_pair(map.first, animation));
		}
		for (auto map : source->mEvents)
		{
			mEvents.insert(std::make_pair(map.first, std::make_shared<Events>()));
			mEvents[map.first]->completeEvent = map.second->completeEvent;
			mEvents[map.first]->endEvent = map.second->endEvent;
			mEvents[map.first]->startEvent = map.second->startEvent;
		}
		mActiveAnimation = source->mActiveAnimation.lock();
		mFirstUpdateAnimation = source->mFirstUpdateAnimation.lock();
		mbLoop = source->mbLoop;
	}
	Animator::~Animator()
	{
	}
	void Animator::Initialize()
	{
		for (auto map : mAnimations)
		{
			map.second->SetAnimator(GetSharedPtr());
		}
	}
	void Animator::Update()
	{
		if (mbActive==false)
			return;
		
		if (mActiveAnimation.expired() == true)
			return;
		mFirstUpdateAnimation = mActiveAnimation.lock();

		std::shared_ptr<Events> events
			= FindEvents(mActiveAnimation.lock()->GetKey());
		if (mActiveAnimation.lock()->IsComplete())
		{
			if (events != nullptr)
			{
				for (auto comp_event : events->completeEvent)
				{
					comp_event();
				}
			}
			mActiveAnimation.lock()->Reset();
		}
		mActiveAnimation.lock()->LateUpdate();
	}
	void Animator::LateUpdate()
	{
		if (mFirstUpdateAnimation.lock().get() != mActiveAnimation.lock().get())
		{
			mActiveAnimation.lock()->LateUpdate();
		}
		else
		{
			mFirstUpdateAnimation.reset();
		}
	}
	void Animator::Render()
	{
	}
	void Animator::Create(std::wstring npk_name, std::wstring pack_name, std::wstring set_name, int start_index, int end_index, float duration)
	{
		std::shared_ptr<Animation> animation = FindAnimation(set_name);
		if (animation != nullptr)
			return;

		animation = std::make_shared<Animation>();
		animation->SetKey(set_name);
		animation->duration = duration;
		animation->Create(npk_name, pack_name, set_name, start_index, end_index);
		animation->play_range = std::make_pair(0,end_index-start_index);
		mAnimations.insert(std::make_pair(set_name, animation));

		std::shared_ptr<Events> events = FindEvents(set_name);
		if (events != nullptr)
			return;
		events = std::make_shared<Events>();
		mEvents.insert(std::make_pair(set_name, events));
	}
	void Animator::Create(std::shared_ptr<Texture> atlas, std::wstring set_name, int start_index, int end_index, float duration)
	{
		std::shared_ptr<Animation> animation = FindAnimation(set_name);
		if (animation != nullptr)
			return;

		animation = std::make_shared<Animation>();
		animation->SetKey(set_name);
		animation->duration = duration;
		animation->SetAtlas(atlas);
		animation->play_range = std::make_pair(start_index, end_index);
		mAnimations.insert(std::make_pair(set_name, animation));

		std::shared_ptr<Events> events = FindEvents(set_name);
		if (events != nullptr)
			return;
		events = std::make_shared<Events>();
		mEvents.insert(std::make_pair(set_name, events));
	}
	std::shared_ptr<Animation> Animator::FindAnimation(const std::wstring& name)
	{
		std::map<std::wstring, std::shared_ptr<Animation>>::iterator iter
			= mAnimations.find(name);

		if (iter == mAnimations.end())
			return nullptr;

		return iter->second;
	}
	std::shared_ptr<Animator::Events> Animator::FindEvents(const std::wstring& name)
	{
		std::map<std::wstring, std::shared_ptr<Events>>::iterator iter
			= mEvents.find(name);

		if (iter == mEvents.end())
			return nullptr;

		return iter->second;
	}
	void Animator::PlayAnimation(const std::wstring& name, bool loop, float duration)
	{
		std::shared_ptr<Animation> prevAnimation = mActiveAnimation.lock();
		std::shared_ptr<Animation> animation = FindAnimation(name);
		std::shared_ptr<Events> events;
		if (prevAnimation != nullptr)
		{
			if (prevAnimation == animation && mbLoop == true)
			{
				return;
			}
			events = FindEvents(prevAnimation->GetKey());
			if (events != nullptr)
			{
				for (auto end_event : events->endEvent)
				{
					end_event();
				}
			}
		}

		if (animation != nullptr)
		{
			mActiveAnimation = animation;
			if (duration != 0.0f)
				mActiveAnimation.lock()->duration = duration;
		}

		std::shared_ptr<Animation> ActiveAni = mActiveAnimation.lock();
		events = FindEvents(ActiveAni->GetKey());
		if (events)
		{
			for (auto start_event : events->startEvent)
			{
				start_event();
			}
		}
		mbLoop = loop;
		ActiveAni->Reset();
	}
	bool Animator::Binds()
	{
		std::shared_ptr<Animation> ani = mActiveAnimation.lock();
		if (ani == nullptr)
			return false;
		ani->Binds();
		return true;
	}
	std::function<void()>& Animator::StartEvent(const std::wstring key)
	{
		std::shared_ptr<Events> events = FindEvents(key);
		events->startEvent.push_back(Event());
		size_t size = events->startEvent.size() - 1;
		return events->startEvent[size].mEvent;
	}
	std::function<void()>& Animator::CompleteEvent(const std::wstring key)
	{
		std::shared_ptr<Events> events = FindEvents(key);
		events->completeEvent.push_back(Event());
		size_t size = events->completeEvent.size() - 1;
		return events->completeEvent[size].mEvent;
	}
	std::function<void()>& Animator::EndEvent(const std::wstring key)
	{
		std::shared_ptr<Events> events = FindEvents(key);
		events->endEvent.push_back(Event());
		size_t size = events->endEvent.size() - 1;
		return events->endEvent[size].mEvent;
	}
	const Sprite& Animator::GetSprite()
	{
		return mActiveAnimation.lock()->GetSprite();
	}
}