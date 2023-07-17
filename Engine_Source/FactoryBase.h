#pragma once
#include "RokaEngine.h"
namespace roka
{
	class FactoryBase
	{
	public:
		virtual ~FactoryBase() {};
		virtual void Initialize() = 0;
	
		template <typename T>
		std::shared_ptr<T> Create()
		{
			return std::shared_ptr<T>(new T());
		}
	};
	class Component;
	class ComponentFactoryBase :public FactoryBase
	{
	public:
		virtual ~ComponentFactoryBase() {};
		virtual void Initialize() = 0;
		virtual std::shared_ptr<Component> CreateNCopy(Component* comp)=0;
	};
}


