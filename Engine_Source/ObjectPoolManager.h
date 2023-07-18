#pragma once
#include "RokaEngine.h"
#include "ObjectPool.h"
#include "SingleTon.h"
namespace roka::pool
{
	template <typename Pool,typename Origin>
	class ObjectPoolManager : public Singleton<Pool>
	{
	public:
		ObjectPool<Origin>* GetPool(std::wstring key)
		{
			if (key.size() == 0)
				return nullptr;


			typename std::map<std::wstring, std::unique_ptr<ObjectPool<Origin>>>::iterator itr;
			itr = mPools.find(key);
			if (itr == mPools.end())
				return nullptr;
            
			return itr->second.get();
		}
	protected:
		ObjectPoolManager() {}
		virtual ~ObjectPoolManager() 
		{
			mPools.clear();
		}
		virtual void Initialize()
		{
			mPoolSize = 100;
		}
		virtual void Release()
		{
			mPools.clear();
		}

		bool AddPool(std::wstring key, std::shared_ptr<Origin> origin)
		{
			if (mPools.find(key) != mPools.end())
				return false;
			mPools.insert(std::make_pair(key,std::unique_ptr<ObjectPool<Origin>>(new ObjectPool<Origin>())));
			mPools[key]->Initialize(origin,mPoolSize);
		
			return true;
		}
	private:
		size_t mPoolSize;
		std::map<std::wstring, std::unique_ptr<ObjectPool<Origin>>> mPools;
	};

}

