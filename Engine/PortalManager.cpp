#include "PortalManager.h"

namespace roka::manager
{
	PortalManager::PortalManager()
	{
	}
	void PortalManager::Initialize()
	{
		DirectPortal* portal = new DirectPortal(EPortalType::SeriaBottom,ESceneType::SeriaRoom, Vector2(-0.8f, 2.5f));
		portal->SetConnectScene(ESceneType::PlayTestScene);
		portal->SetConnectPortal(EPortalType::PlayTestUp);
		mPortalInfos.insert(std::make_pair(EPortalType::SeriaBottom, portal));

		portal = new DirectPortal(EPortalType::PlayTestUp,ESceneType::PlayTestScene,Vector2(-0.0f,-1.5f));
		portal->SetConnectScene(ESceneType::SeriaRoom);
		portal->SetConnectPortal(EPortalType::SeriaBottom);
		mPortalInfos.insert(std::make_pair(EPortalType::PlayTestUp, portal));
	}

	void PortalManager::Release()
	{
		for (auto& portal : mPortalInfos)
		{
			delete portal.second;
			portal.second = nullptr;
		}
		mPortalInfos.clear();
	}

	Portal* PortalManager::Find(EPortalType type)
	{
		auto itr = mPortalInfos.find(type);
		if (itr == mPortalInfos.end())
			return nullptr;
		else
			return itr->second;
	}
}

