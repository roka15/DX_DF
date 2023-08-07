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
		Component() = delete;
		Component(EComponentType type);
		Component(const Component& ref);
		virtual ~Component();
		virtual void Copy(Component* src);

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		

		GameObject* GetOwner() {return mOwner;}
		void SetOwner(GameObject* owner) { mOwner = owner; }
		PROPERTY(GetOwner, SetOwner)GameObject* owner;

		EComponentType GetType() { return mType; }
		GET_PROPERTY(GetType) EComponentType type;

		void SetActive(bool flag) { mbActive = flag; }
		bool GetActive() { return mbActive; }

		PROPERTY(GetActive, SetActive) bool is_active;
	protected:
		EComponentType mType;
		GameObject* mOwner;
		bool mbActive;
	};
}


