#pragma once
#include "RokaEngine.h"
namespace roka
{
	template <typename T>
	class Singleton
	{
	public:
		static T* GetInstance()
		{
			if (instance == nullptr)
				instance = std::unique_ptr<T>(new T());

			return instance.get();
		}
	private:
		static std::unique_ptr<T> instance;
	};

	template<typename T>
	std::unique_ptr<T> Singleton<T>::instance = nullptr;
}


