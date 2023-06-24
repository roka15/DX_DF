#pragma once
#include "Entity.h"
namespace roka
{
	using namespace roka::enums;
	using namespace roka::math;

	class GameObject;
	class Component:public Entity
	{
	public:
		Component(EComponentType type);
		virtual ~Component();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		GameObject* GetOwner() {return mOwner;}
		void SetOwner(GameObject* owner) { mOwner = owner; }
		PROPERTY(GetOwner, SetOwner)GameObject* owner;
	private:
		const EComponentType mType;
		GameObject* mOwner;
	};
}


