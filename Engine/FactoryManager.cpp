#include "FactoryManager.h"
#include "ComponentFactory.h"
#include "ScriptFactory.h"

namespace roka
{
	using namespace roka::enums;
	std::map<enums::EFactoryType, std::unique_ptr<FactoryBase>> FactoryManager::mFactorys = {};
	void FactoryManager::Initialize()
	{
		mFactorys.insert(std::make_pair(EFactoryType::Component, std::make_unique<ComponentFactory>()));
		mFactorys.insert(std::make_pair(EFactoryType::Script, std::make_unique<ScriptFactory>()));
		
		for (auto& factory : mFactorys)
		{
			factory.second->Initialize();
		}
	}
}

