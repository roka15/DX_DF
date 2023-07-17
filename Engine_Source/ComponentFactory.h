#pragma once
#include "FactoryBase.h"
namespace roka
{
	class Component;
	class Entity;
	class ComponentFactory : public ComponentFactoryBase
	{
	public:
		virtual void Initialize()override;
		virtual std::shared_ptr<Component> CreateNCopy(Component* comp)override;
	private:
		std::map<enums::EComponentType, std::function<std::shared_ptr<Component>(Component*)>> mFactories;
	};
}


