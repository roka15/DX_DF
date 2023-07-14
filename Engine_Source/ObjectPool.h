#pragma once
#include "GameObject.h"
#include "Transform.h"
namespace roka::object::pool
{
	template <typename T>
	class ObjectPool
	{
	public:
		static bool ActiveObjectPool();
		static void Initialize(size_t _capacity = 100, size_t _max_capacity = 500);
		static void Initialize(T* _origin, size_t _capacity = 100, size_t _max_capacity = 500);
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
		static T* mOrigin;
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
	T* ObjectPool<T>::mOrigin = nullptr;
	

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
			GameObject* obj = GameObject::Instantiate<T>();
			obj->Initialize();
			mpools.push(obj);
		}
	}
	template<typename T>
	inline void ObjectPool<T>::Initialize(T* _origin, size_t _capacity, size_t _max_capacity)
	{
		mbInit = true;
		mcapacity = _capacity;
		mlimit_capacity = _max_capacity;
		int temp_min = mcapacity < mlimit_capacity ? mcapacity : mlimit_capacity;
		for (int i = 0; i < temp_min; i++)
		{
			GameObject* obj = nullptr;
			if (dynamic_cast<Rectangle*>(_origin) != nullptr)
			{
				obj = GameObject::Instantiate<Rectangle>();
			}
			else
			{
				obj = GameObject::Instantiate<GameObject>();
			}
			mOrigin = _origin;
			obj->AddComponent<T>();
			obj->Initialize();
			mpools.push(obj);
		}
	}
	template<typename T>
	inline void ObjectPool<T>::Release()
	{
		while (mpools.empty() == false)
		{
			GameObject* obj = mpools.front();
			mpools.pop();
			obj->Release();
			delete obj;
		}
		mpools.~queue();
		if (mOrigin != nullptr)
		{
			mOrigin->Release();
			delete mOrigin;
			mOrigin = nullptr;
		}
		mbInit = false;
	}
	template<typename T>
	inline std::shared_ptr<GameObject> ObjectPool<T>::Spawn()
	{
		if (mpools.size() <= 0)
		{
			if (UpgradePoolSize() == false)
				return nullptr;
		}
		

		std::shared_ptr<GameObject> obj(mpools.front(), DeSpawn);
		mpools.pop();
		obj->SetActive(true);
		return obj;
	}

	template<typename T>
	inline void ObjectPool<T>::DeSpawn(GameObject* _obj)
	{
		if (_obj == nullptr)
			return;

		/*T* obj = dynamic_cast<T*>(_obj);
		if (obj == nullptr)
			return;*/
		_obj->Release();
		_obj->Initialize();
		_obj->SetActive(false);
		_obj->RemoveChilds();
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
			GameObject* obj = nullptr;
			for (int i = mcapacity; i < add_cnt; i++)
			{
				if (dynamic_cast<Rectangle*>(mOrigin) != nullptr)
				{
					obj = GameObject::Instantiate<Rectangle>();
				}
				else
				{
					obj = GameObject::Instantiate<GameObject>();
				}
				obj->AddComponent<T>();
				mpools.push(obj);
			}


			mcapacity = add_cnt;
			return true;
		}
	}
}


