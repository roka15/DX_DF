#include "Component.h"

namespace roka
{
	
	Component::Component(EComponentType type):
		mType(type),
		mbActive(true)
	{
	}

	Component::Component(const Component& ref)
	{
		mType = ref.mType;
		mbActive = ref.mbActive;
	}
	void Component::Copy(Component* src)
	{
		mType = src->type;
		mbActive = src->mbActive;
	}

	Component::~Component()
	{
	}

	void Component::Initialize()
	{
		is_active = true;
	}

	void Component::Update()
	{
	}

	void Component::LateUpdate()
	{
	}

	void Component::Render()
	{
	}
}
