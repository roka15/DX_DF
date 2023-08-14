#include "GameObject.h"
#include "Renderer.h"
#include "RokaGraphicDevice_Dx11.h"
#include "Transform.h"
#include "MeshRenderer.h"
#include "Script.h"
#include "Object.h"
#include "Image.h"

#include "..\\Engine\\ComponentFactory.h"
#include "..\\Engine\\ScriptFactory.h"
roka::GameObject::GameObject()
	:mState(EState::Active)
	, mbDebugObject(false)
	, mbMove(true)
	, mLayerType(ELayerType::End)
{
	AddComponent<Transform>();
}

roka::GameObject::GameObject(const GameObject& ref) :
	Entity(ref),
	mbDebugObject(ref.mbDebugObject),
	mbMove(ref.mbMove),
	mState(ref.mState)
{
	for (auto& comp : ref.mComponents)
	{
		std::shared_ptr<Component> newComp = GetComponent(comp->type);
		if (newComp != nullptr)
		{
			newComp->Copy(comp.get());
			continue;
		}

		newComp
			= reinterpret_cast<ComponentFactoryBase*>(FactoryManager::GetFactory(EFactoryType::Component))->CreateNCopy(comp.get());
		newComp->owner = this;
		mComponents.push_back(std::move(newComp));
	}

	for (auto& script : ref.mScripts)
	{
		EScriptType type = script->script_type;
		std::shared_ptr<Script> newScript = GetScript(script->script_type);
		if (newScript != nullptr)
		{
			newScript->Copy(script.get());
			continue;
		}
		std::shared_ptr<Component> comp
			= reinterpret_cast<ComponentFactoryBase*>(FactoryManager::GetFactory(EFactoryType::Script))->CreateNCopy(script.get());
		newScript = std::reinterpret_pointer_cast<Script>(comp);
		newScript->owner = this;
		mScripts.push_back(std::move(newScript));
	}

	for (auto& child : ref.mChild)
	{
		std::shared_ptr<roka::Image> image = std::dynamic_pointer_cast<roka::Image>(child);
		if (image != nullptr)
		{
			std::shared_ptr<roka::Image> obj(new roka::Image());
			obj->Copy(child.get());

			mChild.push_back(obj);
		}
		else
		{
			std::shared_ptr<GameObject> obj(new roka::GameObject());
			obj->Copy(child.get());
			mChild.push_back(obj);
		}
	}
}

void roka::GameObject::Copy(GameObject* src)
{
	Entity::Copy(src);
	mbMove = src->mbMove;
	mState = src->mState;
	mbDebugObject = src->mbDebugObject;
	for (auto& comp : src->mComponents)
	{
		std::shared_ptr<Component> newComp = GetComponent(comp->type);
		if (newComp != nullptr)
		{
			newComp->Copy(comp.get());
			continue;
		}
		newComp
			= reinterpret_cast<ComponentFactoryBase*>(FactoryManager::GetFactory(EFactoryType::Component))->CreateNCopy(comp.get());
		newComp->owner = this;
		mComponents.push_back(std::move(newComp));
	}

	for (auto& script : src->mScripts)
	{
		EScriptType type = script->script_type;
		std::shared_ptr<Script> newScript = GetScript(script->script_type);
		if (newScript != nullptr)
		{
			newScript->Copy(script.get());
			continue;
		}
		std::shared_ptr<Component> comp
			= reinterpret_cast<ComponentFactoryBase*>(FactoryManager::GetFactory(EFactoryType::Script))->CreateNCopy(script.get());
		newScript = std::reinterpret_pointer_cast<Script>(comp);
		newScript->owner = this;
		mScripts.push_back(std::move(newScript));
	}

	for (auto& child : src->mChild)
	{
		std::shared_ptr<roka::Image> image = std::dynamic_pointer_cast<roka::Image>(child);
		if (image != nullptr)
		{
			std::shared_ptr<roka::Image> obj(new roka::Image());
			obj->Copy(child.get());
			mChild.push_back(obj);
		}
		else
		{
			std::shared_ptr<GameObject> obj(new roka::GameObject());
			obj->Copy(child.get());
			mChild.push_back(obj);
		}
	}
}

void roka::GameObject::AddChild(std::shared_ptr<GameObject> child)
{
	mChild.push_back(child);
	child->parent = GetSharedPtr();
}

std::shared_ptr<roka::GameObject> roka::GameObject::GetChild(std::wstring name)
{
	for (auto& child : mChild)
	{
		if (child->GetName().compare(name) == 0)
			return child;
	}

	return nullptr;
}

std::vector<std::shared_ptr<roka::GameObject>> roka::GameObject::GetChilds()
{
	std::vector<std::shared_ptr<GameObject>> vec;
	for (auto& child : mChild)
	{
		vec.push_back(child);
	}
	return vec;
}

roka::ELayerType roka::GameObject::GetLayerType()
{
	std::shared_ptr<GameObject> parrent = mParent.lock();
	if (parrent != nullptr)
		return parrent->layer_type;

	return mLayerType;
}

roka::GameObject::~GameObject()
{

}

void roka::GameObject::Initialize()
{
	for (auto& child : mChild)
	{
		child->parent = GetSharedPtr();
		child->Initialize();
	}
	for (std::shared_ptr<Component>& comp : mComponents)
	{
		comp->Initialize();
	}
	for (std::shared_ptr<Script>& script : mScripts)
	{
		script->Initialize();
	}
}

void roka::GameObject::Update()
{
	for (std::shared_ptr<Component>& comp : mComponents)
	{
		comp->Update();
	}
	for (std::shared_ptr<Script>& script : mScripts)
	{
		script->Update();
	}

	for (std::shared_ptr<GameObject>& child : mChild)
	{
		child->Update();
	}
}

void roka::GameObject::LateUpdate()
{
	for (std::shared_ptr<Component>& comp : mComponents)
	{
		comp->LateUpdate();
	}
	for (std::shared_ptr<Script>& script : mScripts)
	{
		script->LateUpdate();
	}
	for (std::shared_ptr<GameObject>& child : mChild)
	{
		child->LateUpdate();
	}
}

void roka::GameObject::Render()
{

	std::shared_ptr<MeshRenderer> mr = nullptr;
	for (std::shared_ptr<Component>& comp : mComponents)
	{
		/*if (mr == nullptr)
			mr = std::dynamic_pointer_cast<MeshRenderer>(comp);
		if (mr != nullptr)
		{
			continue;
		}*/
		comp->Render();
	}
	
	for (std::shared_ptr<Script>& script : mScripts)
	{
		script->Render();
	}
	/*for (std::shared_ptr<GameObject>& child : mChild)
	{
		child->Render();
	}*/
	/*if (mr != nullptr)
		mr->Render();*/
}
