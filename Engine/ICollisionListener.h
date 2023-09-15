#pragma once
#include "RokaEngine.h"
namespace roka
{
	class GameObject;
	class Collider2D;
	class ICollisionListener
	{
	public:
		virtual void OnCollisionEnter(std::shared_ptr<GameObject> caster, std::shared_ptr<GameObject> target) = 0;
		virtual void OnCollisionStay(std::shared_ptr<GameObject> caster, std::shared_ptr<GameObject> target) = 0;
		virtual void OnCollisionExit(std::shared_ptr<GameObject> caster, std::shared_ptr<GameObject> target) = 0;
	};
}


