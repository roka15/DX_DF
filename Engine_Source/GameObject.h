#pragma once
#include "Entity.h"
#include "Component.h"
#include "Script.h"
namespace roka
{
	class GameObject : public Entity
	{
	public:
		enum EState
		{
			Active,
			Paused,
			Dead,
		};
		GameObject();
		virtual ~GameObject();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		template <typename T>
		T* GetComponent()
		{
			T* component;
			for (Component* comp : mComponents)
			{
				component = dynamic_cast<T*>(comp);
				if (component != nullptr)
					return component;
			}

			for (Script* script : mScripts)
			{
				component = dynamic_cast<T*>(script);
				if (component != nullptr)
					return component;
			}

			return nullptr;
		}
		template <typename T>
		T* AddComponent()
		{
			T* component = GetComponent<T>();
			if (component != nullptr)
				return component;

			component = new T();

			Component* buff = dynamic_cast<Component*>(component);
			Script* script = dynamic_cast<Script*>(component);

			if (buff == nullptr)
				return nullptr;

			if (script == nullptr)
				mComponents.push_back(buff);
			else
				mScripts.push_back(script);

			buff->owner = this;
			return component;
		}
	private:
		EState mState;
		std::vector<Component*> mComponents;
		std::vector<Script*> mScripts;
	};
}


