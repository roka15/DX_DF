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
	mState(ref.mState),
	mLayerType(ref.mLayerType)
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

void roka::GameObject::ChildDestroy()
{
	for(auto itr = mChild.begin(); itr!= mChild.end();)
	{
		std::shared_ptr<GameObject> child = (*itr);
		if (child->active == EState::Dead)
		{
			itr = mChild.erase(itr);
			continue;
		}
		else if (child->GetChildCont() != 0)
		{
			ChildDestroy(child);
		}
		itr++;
	}
}

void roka::GameObject::ChildDestroy(std::shared_ptr<GameObject> parrent)
{
	for (auto itr = parrent->mChild.begin(); itr != parrent->mChild.end();)
	{
		std::shared_ptr<GameObject> child = (*itr);
		if (child->active == EState::Dead)
		{
			itr = parrent->mChild.erase(itr);
			continue;
		}
		else if (child->GetChildCont() != 0)
		{
			ChildDestroy(child);
		}
		itr++;
	}
}

void roka::GameObject::AddChild(std::shared_ptr<GameObject> child)
{
	mChild.push_back(child);
	child->parent = GetSharedPtr();
	std::shared_ptr<Transform> tf = child->GetComponent<Transform>();
	std::shared_ptr<Transform> parentTf = GetComponent<Transform>();
	Vector3 pScale = parentTf->GetScale();
	Vector3 pPos = parentTf->GetPosition();

	Vector3 cScale = tf->GetLocalScale();
	cScale = cScale / pScale;
	Vector3 cPos = tf->GetLocalPosition();
	
	cPos = cPos + pPos;
	tf->SetScale(cScale);
	tf->SetPosition(cPos);
}

void roka::GameObject::InsertChild(std::shared_ptr<GameObject> child, int index)
{
	std::vector<std::shared_ptr<GameObject>>::iterator itr = mChild.begin();
	if (mChild.size() < index)
	{
		mChild.push_back(child);
	}
	else
	{
		for (int i = 0; i < index; i++)
		{
			itr++;
		}
		mChild.insert(itr, child);
	}
	child->parent = GetSharedPtr();

	std::shared_ptr<Transform> tf = child->GetComponent<Transform>();
	std::shared_ptr<Transform> parentTf = GetComponent<Transform>();
	Vector3 pScale = parentTf->GetScale();
	Vector3 pPos = parentTf->GetPosition();

	Vector3 cScale = tf->GetLocalScale();
	cScale = cScale / pScale;
	Vector3 cPos = tf->GetLocalPosition();

	cPos = cPos + pPos;
	tf->SetScale(cScale);
	tf->SetPosition(cPos);
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

void roka::GameObject::SetChildState(EState state,std::wstring key)
{
	for (auto& child : mChild)
	{
		if (child->GetName().compare(key) == 0)
		{
			child->active = state;
		}
	}
}

void roka::GameObject::RemoveChild(std::wstring key)
{
	for (auto& child : mChild)
	{
		if (child->GetName().compare(key) == 0) 
		{
			child.reset();
		}
	}
	mChild.erase(std::remove(mChild.begin(), mChild.end(), nullptr), mChild.end());
}

void roka::GameObject::RemoveChild(std::shared_ptr<GameObject> obj)
{
	auto itr = mChild.begin();
	while (itr != mChild.end()) 
	{
		if ((*itr)==obj) 
		{
			itr = mChild.erase(itr); 
		}
		else 
		{
			++itr;
		}
	}
}


roka::ELayerType roka::GameObject::GetLayerType()
{
	std::shared_ptr<GameObject> parrent = mParent.lock();
	/*if (parrent != nullptr)
		return parrent->layer_type;*/

	return mLayerType;
}

roka::GameObject::~GameObject()
{
	mComponents.clear();
	mScripts.clear();
	mChild.clear();
}

void roka::GameObject::Initialize()
{
	for (auto& child : mChild)
	{
		std::shared_ptr<GameObject> this_ptr = GetSharedPtr();
		child->parent = this_ptr;
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
	if (active != EState::Active)
		return;
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
	if (active != EState::Active)
		return;
	for (std::shared_ptr<Component>& comp : mComponents)
	{
		comp->LateUpdate();
	}
	for (std::shared_ptr<Script>& script : mScripts)
	{
		script->LateUpdate();
	}
	if (GetName().compare(L"Player") == 0)
		int a = 0;
	for (std::shared_ptr<GameObject>& child : mChild)
	{
		child->LateUpdate();
	}
}

void roka::GameObject::Render()
{
	if (active != EState::Active)
		return;
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

void roka::GameObject::Release()
{
	mComponents.clear();
	mScripts.clear();
	mChild.clear();
}
