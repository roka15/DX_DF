#include "GameObject.h"
#include "Renderer.h"
#include "RokaGraphicDevice_Dx11.h"
#include "Transform.h"
#include "MeshRenderer.h"
#include "Script.h"
#include "FactoryManager.h"
#include "ComponentFactory.h"
#include "ScriptFactory.h"
roka::GameObject::GameObject()
	:mState(EState::Active)
	, mbMove(true)
{
	AddComponent<Transform>();
}

roka::GameObject::GameObject(const GameObject& ref) :
	Entity(ref),
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

}

void roka::GameObject::Copy(GameObject* src)
{

	mbMove = src->mbMove;
	mState = src->mState;

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
}

roka::GameObject::~GameObject()
{

}

void roka::GameObject::Initialize()
{
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
}

void roka::GameObject::Render()
{
	for (std::shared_ptr<Component>& comp : mComponents)
	{
		comp->Render();
	}
	for (std::shared_ptr<Script>& script : mScripts)
	{
		script->Render();
	}
}
