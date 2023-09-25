#pragma once
#include "Entity.h"
#include "..\\Engine\\FactoryManager.h"
#include "Script.h"
#include "Component.h"
namespace roka
{
	class GameObject : public Entity, public std::enable_shared_from_this<GameObject>
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
		virtual void Release();


		virtual void Copy(GameObject* src);
		virtual void ChildDestroy();
		virtual void ChildDestroy(std::shared_ptr<GameObject> parrent);

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
		template <typename T>
		const std::vector<std::shared_ptr<T>> GetComponents()
		{
			std::vector<std::shared_ptr<T>> comps;

			std::shared_ptr<T> component;
			for (auto& comp : mComponents)
			{
				component = std::dynamic_pointer_cast<T>(comp);
				if (component != nullptr)
					comps.push_back(component);
			}

			return comps;
		}
		template <typename T>
		const std::vector<std::shared_ptr<T>> GetChildComponents()
		{
			std::vector<std::shared_ptr<T>> comps;

			std::shared_ptr<T> component;
			for (auto& comp : mComponents)
			{
				component = std::dynamic_pointer_cast<T>(comp);
				if (component != nullptr)
					comps.push_back(component);
			}

			for (auto& child : mChild)
			{
				const std::vector<std::shared_ptr<T>>& child_comps = child->GetChildComponents<T>();
				for (auto& comp : child_comps)
					comps.push_back(comp);
			}

			return comps;
		}
		const std::vector<std::shared_ptr<Script>>& GetScripts()
		{
			return mScripts;
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
			component->Initialize();
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
			component->Initialize();
			return component;
		}

		void AddChild(std::shared_ptr<GameObject> child);
		void InsertChild(std::shared_ptr<GameObject> child, int index);
		void SetParent(std::weak_ptr<GameObject> parent) { mParent = parent; }
		std::shared_ptr<GameObject> GetParent() { return mParent.lock(); }

		std::shared_ptr<GameObject> GetChild(std::wstring name);
		std::vector<std::shared_ptr<GameObject>> GetChilds();
		template <typename T>
		std::vector<std::shared_ptr<T>> GetChilds()
		{
			std::vector<std::shared_ptr<T>> value = {};
			for (auto& child : mChild)
			{
				std::shared_ptr<T> comp = child->GetComponent<T>();
				if (comp != nullptr)
					value.push_back(comp);
			}
			return value;
		}
		template <typename T>
		std::shared_ptr<GameObject> GetChild()
		{
			for (auto& child : mChild)
			{
				std::shared_ptr<T> comp = child->GetComponent<T>();
				if (comp != nullptr)
				{
					return child;
				}
			}
			return nullptr;
		}

		void SwapRemoveChild(std::shared_ptr<GameObject> find, std::shared_ptr<GameObject> swap)
		{
			int index = 0;
			for (auto& child : mChild)
			{
				if (child == find)
				{
					mChild[index].reset();
					mChild[index] = swap;
					swap->parent = GetSharedPtr();
					return;
				}
				index++;
			}
		}
		void SwapRemoveChild(std::wstring find, std::shared_ptr<GameObject> swap)
		{
			int index = 0;
			for (auto& child : mChild)
			{
				if (child->GetName().compare(find)==0)
				{
					mChild[index].reset();
					mChild[index] = swap;
					swap->parent = GetSharedPtr();
					return;
				}
				index++;
			}
		}
		void SetChildState(EState state,std::wstring key);
		void RemoveChild(std::wstring key);
		void RemoveChild(std::shared_ptr<GameObject> obj);
		
		UINT GetChildCont() { return mChild.size(); }


		bool IsDebugObject() { return mbDebugObject; }

		void SetMoveFlag(bool flag) { mbMove = flag; }
		bool GetMoveFlag() { return mbMove; }

		void SetState(EState state) { mState = state; }
		EState GetState() { return mState; }

		void SetLayerType(ELayerType layer) { mLayerType = layer; }
		ELayerType GetLayerType();

		std::shared_ptr<GameObject> GetSharedPtr() { return shared_from_this(); }

		GET_PROPERTY(IsDebugObject) bool is_debug;
		PROPERTY(GetParent, SetParent)  std::shared_ptr<GameObject> parent;
		PROPERTY(GetMoveFlag, SetMoveFlag) bool ismove;
		PROPERTY(GetState, SetState) EState active;
		PROPERTY(GetLayerType, SetLayerType) ELayerType layer_type;
	protected:
		bool mbDebugObject;
	private:
		bool mbMove;
		EState mState;
		ELayerType mLayerType;
		std::vector<std::shared_ptr<Component>> mComponents;
		std::vector<std::shared_ptr<Script>> mScripts;

		std::vector<std::shared_ptr<GameObject>> mChild;
		std::weak_ptr<GameObject> mParent;
	};
}


