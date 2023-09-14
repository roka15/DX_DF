#pragma once
#include "SingleTon.h"
#include "ContentEnums.h"

using namespace roka::enums;
namespace roka
{
	class GameObject;
}
namespace roka::manager
{
	class PartManager:public Singleton<PartManager>
	{
	private:
		PartManager();
	public:
		~PartManager() {}
		void Initialize();
		void Release();

		std::shared_ptr<GameObject> Find(EAvatarParts type, std::wstring name);
	private:
		friend class Singleton<PartManager>;

		std::map<EAvatarParts, std::map<std::wstring, std::unique_ptr<GameObject>>> mPartInfos;
	};
}


