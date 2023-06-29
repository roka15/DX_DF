#pragma once
#include "RokaEngine.h"
namespace roka
{
	using namespace roka::math;
	class SceneSector
	{
	public:
		SceneSector(std::wstring name);
		~SceneSector();

		bool Register(std::wstring name,SceneSector* sector);
		SceneSector* GetNextInfo(std::wstring name);

		std::wstring GetTextureName() { return mTextureName; }
		void SetTextureName(std::wstring name) { mTextureName = name; }
		PROPERTY(GetTextureName, SetTextureName) std::wstring texture_name;

		std::wstring GetName() { return mName; }
		void SetName(std::wstring name) { mName = name; }
		PROPERTY(GetName, SetTextureName) std::wstring name;

	private:
		std::map<std::wstring, SceneSector*> mLinkSectorInfos;
		std::wstring mTextureName;
		std::wstring mName;
	};
}


