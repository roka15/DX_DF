#pragma once
#include "SingleTon.h"
#include "Portal.h"
namespace roka::manager
{
	class PortalManager : public Singleton<PortalManager>
	{
	private:
		PortalManager();
	public:
		~PortalManager() {}
		void Initialize();
		void Release();

		Portal* Find(EPortalType type);
	private:
		friend class Singleton<PortalManager>;

		std::map<EPortalType, Portal*> mPortalInfos;
	};
}


