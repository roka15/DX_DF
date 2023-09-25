#pragma once
#include "ObjectPoolManager.h"
#include "Prefab.h"

using namespace roka::manager;
namespace roka::pool
{
	class WarningObjectPool:public ObjectPoolManager<WarningObjectPool,GameObject>
	{
	public:
		virtual ~WarningObjectPool() {  }
	public:
		virtual void Initialize()override
		{
			ObjectPoolManager<WarningObjectPool, GameObject>::Initialize();
			bool is_create = AddPool(L"WarningObject", prefab::Prefabs[L"WarningObject"]);
			is_create = AddPool(L"WarningEftObject", prefab::Prefabs[L"WarningEftObject"]);
			is_create = AddPool(L"ChangeSizeOverTimeObject", prefab::Prefabs[L"ChangeSizeOverTimeObject"],50);
			is_create = AddPool(L"ChangeSizeOverTimeEftObject", prefab::Prefabs[L"ChangeSizeOverTimeEftObject"],50);
		}
		virtual void Release()override
		{
			ObjectPoolManager<WarningObjectPool, GameObject>::Release();
		}
	private:
		friend class Singleton<WarningObjectPool>;
		WarningObjectPool() :ObjectPoolManager<WarningObjectPool, GameObject>() {  }
	};
}


