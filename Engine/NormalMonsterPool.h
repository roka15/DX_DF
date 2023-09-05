#pragma once

#include "ObjectPoolManager.h"
#include "Prefab.h"
namespace roka::pool
{
	class NormalMonsterPool : public ObjectPoolManager<NormalMonsterPool, GameObject>
	{
	public:
		virtual ~NormalMonsterPool() { }
	public:
		virtual void Initialize()override
		{
			ObjectPoolManager<NormalMonsterPool, GameObject>::Initialize();
			bool is_create = AddPool(L"SpiderMonster", prefab::Prefabs[L"Spider_MonsterObject"]);
		}
		virtual void Release()override
		{
			ObjectPoolManager<NormalMonsterPool, GameObject>::Release();
		}
	private:
		friend class Singleton<NormalMonsterPool>;
		NormalMonsterPool() :ObjectPoolManager<NormalMonsterPool, GameObject>() { }

	};
}


