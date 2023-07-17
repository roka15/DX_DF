#pragma once
#include "Entity.h"
#include "FactoryManager.h"
#include "Script.h"
#include "Component.h"
namespace roka
{
	class GameObject : public Entity
	{
	public:
		enum class EState
		{
			Active,
			Paused,
			Dead,
		};
		GameObject();
		GameObject(const GameObject& ref);
	
		virtual ~GameObject();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		virtual void Copy(GameObject* src);

		template <typename T>
		std::shared_ptr<T> GetComponent()
		{
			std::shared_ptr<T> component;
			for (std::shared_ptr<Component> comp : mComponents)
			{
				component = std::dynamic_pointer_cast<T>(comp);
				if (component != nullptr)
					return component;
			}

			for (std::shared_ptr<Script> script : mScripts)
			{
				component = std::dynamic_pointer_cast<T>(script);
				if (component != nullptr)
					return component;
			}

			return nullptr;
		}

		std::shared_ptr<Component> GetComponent(enums::EComponentType type)
		{
			for (std::shared_ptr<Component> comp : mComponents)
			{
				if (comp->type == type)
					return comp;
				if (comp != nullptr)
					return nullptr;
			}
			return nullptr;
		}
		std::shared_ptr<Script> GetScript(enums::EScriptType type)
		{
			for (std::shared_ptr<Script> script : mScripts)
			{
				if (script->script_type == type)
					return script;
				if (script != nullptr)
					return nullptr;
			}
			return nullptr;
		}
		
		template <typename T>
		std::shared_ptr<T> AddComponent()
		{
			std::shared_ptr<T> component = GetComponent<T>();
			if (static_cast<bool>(component) == true)
				return component;
			ComponentFactoryBase* cfb = reinterpret_cast<ComponentFactoryBase*>(FactoryManager::GetFactory(EFactoryType::Component));
			component
				= cfb->Create<T>();
			mComponents.push_back(component);
			component->owner = this;
			return component;
		}
		
		template <typename T>
		std::shared_ptr<T> AddScript()
		{
			std::shared_ptr<T> component = GetComponent<T>();
			if (static_cast<bool>(component) == true)
				return component;
			ComponentFactoryBase* cfb = reinterpret_cast<ComponentFactoryBase*>(FactoryManager::GetFactory(EFactoryType::Script));
			component
				= cfb->Create<T>();
			mScripts.push_back(component);
			component->owner = this;
			return component;
		}
		void SetMoveFlag(bool flag) { mbMove = flag; }
		bool GetMoveFlag() { return mbMove; }
		PROPERTY(GetMoveFlag, SetMoveFlag) bool ismove;

		void SetState(EState state) { mState = state; }
		EState GetState() { return mState; }
		PROPERTY(GetState, SetState) EState active;
	
	private:
		bool mbMove;
		EState mState;
		std::vector<std::shared_ptr<Component>> mComponents;
		std::vector<std::shared_ptr<Script>> mScripts;
	};
}


