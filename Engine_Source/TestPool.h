#pragma once
#include "ObjectPoolManager.h"
#include "Prefab.h"
namespace roka::pool
{
	class TestPool : public ObjectPoolManager<TestPool,GameObject>
	{
	public:
		virtual ~TestPool() {}
	private:
		virtual void Initialize()override
		{
			ObjectPoolManager<TestPool, GameObject>::Initialize();
			bool is_create = AddPool(L"TestObject", prefab::Prefabs[L"TestObject"]);
		}
		virtual void Release()override
		{
			ObjectPoolManager<TestPool, GameObject>::Release();
		}	
	private:
		friend class Singleton<TestPool>;
		TestPool() :ObjectPoolManager<TestPool, GameObject>() { Initialize(); }
		
	};
}


