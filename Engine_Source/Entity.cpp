#include "Entity.h"

namespace roka
{
	Entity::Entity()
		:mName(L""),
		mID((UINT64)this)
	{
	}

	Entity::Entity(const Entity& ref)
		:mName(ref.mName)
	{
	}

	Entity::~Entity()
	{
	}

}
