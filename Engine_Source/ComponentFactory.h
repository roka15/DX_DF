#pragma once
#include "Component.h"
namespace roka
{
	class ComponentFactory
	{
	public:
		static void Initialize();
		static std::shared_ptr<Component> CreateNCopyComponent(Component* comp);
		template <typename T>
		static std::shared_ptr<T> GetComponent()
		{
			return std::shared_ptr<T>(new T());
		}
	
	private:
		static std::map<EComponentType, std::function<std::shared_ptr<Component>(Component*)>> mFactories;
	};
}


