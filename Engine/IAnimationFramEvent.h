#pragma once
#include "RokaEngine.h"
namespace roka
{
	class GameObject;
	class IAnimationFramEvent
	{
	public:
		virtual void OnAnimationFramEvent(std::shared_ptr<GameObject> caster, std::wstring framEvent) = 0;
	};
}


