#pragma once
#include "Script.h"

namespace roka
{
	class ScriptFactory
	{
	public:
		static void Initialize();
		static std::shared_ptr<Script> CreateNCopyComponent(Script* script);
		/*template <typename T>
		static EScriptType GetType()
		{
			for (auto& ptr : mOrigins)
			{
				T* script = dynamic_cast<T*>(ptr.get());
				if (script == nullptr)
					return EScriptType::None;
				return ptr->script_type;
			}
		}*/
		template<typename T>
		static std::shared_ptr<T> GetComponent()
		{
			return std::shared_ptr<T>(new T());
		}
	private:
		static std::map<EScriptType, std::function<std::shared_ptr<Script>(Script*)>> mFactories;
		//static std::vector<std::unique_ptr<Script>> mOrigins;
	};
}


