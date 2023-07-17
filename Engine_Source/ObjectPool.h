#pragma once
#include "GameObject.h"
#include "Transform.h"
#include "Object.h"
namespace roka::object::pool
{
	template <typename T>
	class ObjectPool
	{
	public:
		static bool ActiveObjectPool();
		static void Initialize(size_t _capacity = 100, size_t _max_capacity = 500);
		static void Initialize(std::shared_ptr<GameObject> _origin, size_t _capacity = 100, size_t _max_capacity = 500);
		static void Release();
		static std::shared_ptr<T> Spawn();
		static void DeSpawn(T* _obj);
	private:
		static bool UpgradePoolSize();
		ObjectPool() = delete;
		~ObjectPool() = delete;
	private:
		static bool mbInit;
		static size_t mcapacity;
		static size_t mlimit_capacity;
		static std::queue<T*> mpools;
		static std::weak_ptr<T> mOrigin;
	};
	template<typename T>
	bool ObjectPool<T>::mbInit = false;
	template <typename T>
	size_t ObjectPool<T>::mcapacity = 0;
	template <typename T>
	std::queue<T*> ObjectPool<T>::mpools;
	template <typename T>
	size_t ObjectPool<T>::mlimit_capacity = 0;
	template <typename T>
	std::weak_ptr<T> ObjectPool<T>::mOrigin;


	template<typename T>
	inline bool ObjectPool<T>::ActiveObjectPool()
	{
		return mbInit == true;
	}

	template<typename T>
	inline void ObjectPool<T>::Initialize(size_t _capacity, size_t _max_capacity)
	{
		mbInit = true;
		mcapacity = _capacity;
		mlimit_capacity = _max_capacity;

		int temp_min = mcapacity < mlimit_capacity ? mcapacity : mlimit_capacity;

		for (int i = 0; i < temp_min; i++)
		{
			T* obj = new T();
			obj->Initialize();
			mpools.push(obj);
		}

		mOrigin = mpools.front();
	}
	template<typename T>
	inline void ObjectPool<T>::Initialize(std::shared_ptr<GameObject> _origin, size_t _capacity, size_t _max_capacity)
	{
		mbInit = true;
		mcapacity = _capacity;
		mlimit_capacity = _max_capacity;
		mOrigin = _origin;
		int temp_min = mcapacity < mlimit_capacity ? mcapacity : mlimit_capacity;

		for (int i = 0; i < temp_min; i++)
		{
			T* obj = new T(*(_origin.get()));
			obj->Initialize();
			mpools.push(obj);
		}
	}
	template<typename T>
	inline void ObjectPool<T>::Release()
	{
		while (mpools.empty() == false)
		{
			T* obj = mpools.front();
			mpools.pop();
			delete obj;
		}
		mpools.~queue();
		if (mOrigin.lock() != nullptr)
		{
			//해제는 origin 생성한 곳에서 하도록 하는게 좋을 듯.
			//prefab 인 경우 prefab 관리하는 곳에서 release 하도록 할려고 하는데
			//여기서 delete 해버리면 가독성이 떨어지는 것 같음.
			mOrigin.reset();
		}
		mbInit = false;
	}
	template<typename T>
	inline std::shared_ptr<T> ObjectPool<T>::Spawn()
	{
		if (mpools.size() <= 0)
		{
			if (UpgradePoolSize() == false)
				return nullptr;
		}

		T* data = mpools.front();
		std::shared_ptr<T> obj(data, [](T* obj)->void { DeSpawn(obj); });
		mpools.pop();
		obj->SetState(GameObject::EState::Active);
		return obj;
	}

	template<typename T>
	inline void ObjectPool<T>::DeSpawn(T* _obj)
	{
		if (_obj == nullptr)
			return;

		/*T* obj = dynamic_cast<T*>(_obj);
		if (obj == nullptr)
			return;*/
		std::shared_ptr<T> ptr = mOrigin.lock();
		_obj->Copy(ptr.get());
		_obj->SetState(GameObject::EState::Paused);
		mpools.push(_obj);
	}
	template<typename T>
	inline bool ObjectPool<T>::UpgradePoolSize()
	{
		if (mpools.size() == 0)
		{
			int add_cnt = mcapacity == 1 ? mcapacity + 1 : mcapacity + (mcapacity / 2);

			if (add_cnt > mlimit_capacity)
				return false;
			T* obj = nullptr;
			for (int i = mcapacity; i < add_cnt; i++)
			{
				std::shared_ptr<T> ptr = mOrigin.lock();
				obj = new T(*(ptr.get()));
				mpools.push(obj);
			}

			mcapacity = add_cnt;
			return true;
		}
	}
}


