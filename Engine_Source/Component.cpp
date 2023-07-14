#include "Component.h"

namespace roka
{
	
	Component::Component(EComponentType type):
		mType(type)
	{
	}

	Component::Component(const Component& ref)
	{
		mType = ref.mType;
	}

	Component::~Component()
	{
	}

	void Component::Initialize()
	{
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

	void Component::Copy(Component* src)
	{
		mType = src->type;
	}

}
