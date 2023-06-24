#include "GameObject.h"
#include "Renderer.h"
#include "RokaGraphicDevice_Dx11.h"
#include "Transform.h"
roka::GameObject::GameObject()
	:mState(EState::Active)
{
	AddComponent<Transform>();
}

roka::GameObject::~GameObject()
{
	for (Component* comp : mComponents)
	{
		if (comp == nullptr)
			continue;
		delete comp;
		comp = nullptr;
	}
	for (Script* script : mScripts)
	{
		if (script == nullptr)
			continue;
		delete script;
		script = nullptr;
	}
}

void roka::GameObject::Initialize()
{
	
}

void roka::GameObject::Update()
{
	for (Component* comp : mComponents)
	{
		comp->Update();
	}
	for (Script* script : mScripts)
	{
		script->Update();
	}
}

void roka::GameObject::LateUpdate()
{
	for (Component* comp : mComponents)
	{
		comp->LateUpdate();
	}
	for (Script* script : mScripts)
	{
		script->LateUpdate();
	}
}

void roka::GameObject::Render()
{
	for (Component* comp : mComponents)
	{
		comp->Render();
	}
	for (Script* script : mScripts)
	{
		script->Render();
	}
}
