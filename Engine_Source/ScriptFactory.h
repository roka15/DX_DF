#pragma once
#include "FactoryBase.h"
namespace roka
{
	class Script;
	class ScriptFactory :public ComponentFactoryBase
	{
	public:
		virtual void Initialize()override;
		virtual std::shared_ptr<Component> CreateNCopy(Component* comp)override;
	private:
		std::map<enums::EScriptType, std::function<std::shared_ptr<Script>(Script*)>> mFactories;
	};
}


