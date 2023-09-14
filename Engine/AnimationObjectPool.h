#pragma once
#include "ObjectPoolManager.h"
#include "Prefab.h"

using namespace roka::manager;	
namespace roka::pool
{
	class AnimationObjectPool : public ObjectPoolManager<AnimationObjectPool, GameObject>
	{
	public:
		virtual ~AnimationObjectPool() {  }
	public:
		virtual void Initialize()override
		{
			ObjectPoolManager<AnimationObjectPool, GameObject>::Initialize();
			bool is_create = AddPool(L"AniObject", prefab::Prefabs[L"AniObject"]);
			is_create = AddPool(L"AniEftObject", prefab::Prefabs[L"AniEftObject"]);
			is_create = AddPool(L"ColAniObject", prefab::Prefabs[L"ColAniObject"]);
			is_create = AddPool(L"ColAniEftObject", prefab::Prefabs[L"ColAniEftObject"]);
		}
		virtual void Release()override
		{
			ObjectPoolManager<AnimationObjectPool, GameObject>::Release();
		}
	private:
		friend class Singleton<AnimationObjectPool>;
		AnimationObjectPool() :ObjectPoolManager<AnimationObjectPool, GameObject>() {  }
	};
}


