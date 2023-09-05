#pragma once
#include "GameObject.h"
#include "Transform.h"
#include "Object.h"
namespace roka::pool
{
	template <typename T>
	class ObjectPool 
	{
	public:
		ObjectPool() :
			mcapacity(0),
			mlimit_capacity(0),
			mpools(),
			mOrigin()
		{

		}
		virtual ~ObjectPool()
		{
			while (mpools.empty() == false)
			{
				T* obj = mpools.front();
				mpools.pop();
				delete obj;
			}
			mpools.~queue();
			if (mOrigin != nullptr)
			{
				mOrigin.reset();
			}
		}

		void Initialize(size_t _capacity = 100, size_t _max_capacity = 500)
		{
			mcapacity = _capacity;
			mlimit_capacity = _max_capacity;

			int temp_min = mcapacity < mlimit_capacity ? mcapacity : mlimit_capacity;

			for (int i = 0; i < temp_min; i++)
			{
				T* obj = new T();
				mpools.push(obj);
			}

			mOrigin = std::make_shared<T>(*(mpools.front()));
		}
		void Initialize(std::shared_ptr<T> _origin, size_t _capacity = 100, size_t _max_capacity = 500)
		{
			mcapacity = _capacity;
			mlimit_capacity = _max_capacity;
			mOrigin = std::make_shared<T>(*(_origin));
			int temp_min = mcapacity < mlimit_capacity ? mcapacity : mlimit_capacity;

			for (int i = 0; i < temp_min; i++)
			{
				T* obj = new T(*(_origin.get()));
				mpools.push(obj);
			}
		}
		void Release()
		{
			while (mpools.empty() == false)
			{
				T* obj = mpools.front();
				mpools.pop();
				delete obj;
			}
			mpools.~queue();
			if (mOrigin != nullptr)
			{
				//������ origin ������ ������ �ϵ��� �ϴ°� ���� ��.
				//prefab �� ��� prefab �����ϴ� ������ release �ϵ��� �ҷ��� �ϴµ�
				//���⼭ delete �ع����� �������� �������� �� ����.
				mOrigin.reset();
			}
		}
		std::shared_ptr<T> Spawn()
		{
			if (mpools.size() <= 0)
			{
				if (UpgradePoolSize() == false)
					return nullptr;
			}

			T* data = mpools.front();
			std::shared_ptr<T> obj(data, [this](T* obj)->void { DeSpawn(obj); });
			mpools.pop();
			obj->SetState(GameObject::EState::Active);
			obj->Initialize();
			return obj;
		}
		void DeSpawn(T* _obj)
		{
			if (_obj == nullptr)
				return;

			/*T* obj = dynamic_cast<T*>(_obj);
			if (obj == nullptr)
				return;*/
			std::shared_ptr<T> ptr = mOrigin;
			_obj->Copy(ptr.get());
			_obj->SetState(GameObject::EState::Paused);
			mpools.push(_obj);
		}
		
	private:
		bool UpgradePoolSize()
		{
			if (mpools.size() == 0)
			{
				int add_cnt = mcapacity == 1 ? mcapacity + 1 : mcapacity + (mcapacity / 2);

				if (add_cnt > mlimit_capacity)
					return false;
				T* obj = nullptr;
				for (int i = mcapacity; i < add_cnt; i++)
				{
					std::shared_ptr<T> ptr = mOrigin;
					obj = new T(*(ptr.get()));
					mpools.push(obj);
				}

				mcapacity = add_cnt;
				return true;
			}
		}
		
		
	private:
	    size_t mcapacity;
	    size_t mlimit_capacity;
	    std::queue<T*> mpools;
	    std::shared_ptr<T> mOrigin;
	};
}


