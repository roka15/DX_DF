#pragma once
#include "GameObject.h"
#include "SceneManager.h"
#include "Transform.h"
namespace roka::object
{
	template<typename T>
	static __forceinline T* Instantiate(enums::ELayerType layer)
	{
		T* obj = new T();
		Scene* scene = SceneManager::GetActiveScene();
		scene->AddGameObject(layer, obj);

		return obj;
	}
	template<typename T>
	static __forceinline T* Instantiate(GameObject* src,enums::ELayerType layer)
	{
		T* source = dynamic_cast<T*>(src);
		T* obj = new T(*source);
		Scene* scene = SceneManager::GetActiveScene();
		scene->AddGameObject(layer, obj);
		
		return obj;
	}
	template<typename T>
	static __forceinline T* Instantiate(Vector3 pos,enums::ELayerType layer)
	{
		T* obj = new T();
		obj->GetComponent<Transform>()->position = pos;

		Scene* scene = SceneManager::GetActiveScene();
		scene->AddGameObject(layer, obj);

		return obj;
	}
	template<typename T>
	static __forceinline T* Instantiate(Vector3 pos,Vector3 rotate, enums::ELayerType layer)
	{
		T* obj = new T();
		std::shared_ptr<Transform> tf = obj->GetComponent<Transform>();
		tf->position = pos;
		tf->rotation = rotate;
		
		Scene* scene = SceneManager::GetActiveScene();
		scene->AddGameObject(layer, obj);

		return obj;
	}
	template<typename T>
	static __forceinline T* Instantiate(Vector3 pos, Vector3 rotate,Vector3 scale, enums::ELayerType layer)
	{
		T* obj = new T();
		std::shared_ptr<Transform> tf = obj->GetComponent<Transform>();
		tf->position = pos;
		tf->rotation = rotate;
		tf->scale = scale;

		Scene* scene = SceneManager::GetActiveScene();
		scene->AddGameObject(layer, obj);

		return obj;
	}

	static __forceinline void Destroy(GameObject* obj)
	{
		obj->SetState(roka::GameObject::EState::Dead);
	}
}