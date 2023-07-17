#pragma once
#include "FactoryBase.h"

namespace roka
{
	class FactoryManager
	{
	public:
		static void Initialize();
	
		static FactoryBase* GetFactory(enums::EFactoryType type)
		{
			return mFactorys[type].get();
		}
	
	private:
		static std::map<enums::EFactoryType, std::unique_ptr<FactoryBase>> mFactorys;
	};
}


