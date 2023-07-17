#include "MyResource.h"


namespace roka
{
	Resource::Resource(roka::enums::EResourceType type)
		:mType(type)
	{

	}

	Resource::Resource(const Resource& ref)
		:mType(ref.mType),
		mKey(ref.mKey),
		mPath(ref.mPath)
	{

	}

	Resource::~Resource()
	{

	}
}
