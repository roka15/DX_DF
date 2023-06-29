#include "SceneSector.h"

namespace roka
{
	SceneSector::SceneSector(std::wstring name):mName(name)
	{
	}
	SceneSector::~SceneSector()
	{
	}
	bool SceneSector::Register(std::wstring name, SceneSector* sector)
	{
		std::map<std::wstring, SceneSector*>::iterator itr = mLinkSectorInfos.find(name);
		if (itr != mLinkSectorInfos.end())
			return false;

		mLinkSectorInfos.insert(std::make_pair(name, sector));
		return true;
	}
	SceneSector* SceneSector::GetNextInfo(std::wstring name)
	{
		auto itr = mLinkSectorInfos.find(name);
		if (itr == mLinkSectorInfos.end())
			return nullptr;

		return itr->second;
	}
}