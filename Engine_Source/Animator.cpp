#include "Animator.h"
#include "Sprite.h"
namespace roka
{
	Animator::Animator() :Component(EComponentType::Animator)
		, mAnimations{}
		, mEvents{}
		, mActiveAnimation()
		, mFirstUpdateAnimation()
		, mIsLoop(false)
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
			mEvents.insert(std::make_pair(map.first, map.second));
		}
		mActiveAnimation = ref.mActiveAnimation.lock();
		mFirstUpdateAnimation = ref.mFirstUpdateAnimation.lock();
		mIsLoop = ref.mIsLoop;
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
			mEvents.insert(std::make_pair(map.first, map.second));
		}
		mActiveAnimation = source->mActiveAnimation.lock();
		mFirstUpdateAnimation = source->mFirstUpdateAnimation.lock();
		mIsLoop = source->mIsLoop;
	}
	Animator::~Animator()
	{
	}
	void Animator::Initialize()
	{
	}
	void Animator::Update()
	{
		GameObject* Owner = owner;
		if (mActiveAnimation.expired() == true)
			return;
		mFirstUpdateAnimation = mActiveAnimation.lock();
		if (mActiveAnimation.lock()->IsComplete() && mIsLoop)
		{
			std::shared_ptr<Events> events
				= FindEvents(mActiveAnimation.lock()->GetKey());
			if (events != nullptr)
				events->completeEvent();

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
			if (prevAnimation == animation && mIsLoop == true)
			{
				return;
			}
			events = FindEvents(prevAnimation->GetKey());
			if (events != nullptr)
				events->endEvent();
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
			events->startEvent();

		mIsLoop = loop;
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

		return events->startEvent.mEvent;
	}
	std::function<void()>& Animator::CompleteEvent(const std::wstring key)
	{
		std::shared_ptr<Events> events = FindEvents(key);
		return events->completeEvent.mEvent;
	}
	std::function<void()>& Animator::EndEvent(const std::wstring key)
	{
		std::shared_ptr<Events> events = FindEvents(key);
		return events->endEvent.mEvent;
	}
	const Sprite& Animator::GetSprite()
	{
		return mActiveAnimation.lock()->GetSprite();
	}
}