#pragma once
#include "GameObject.h"
#include "SceneManager.h"
#include "Transform.h"
namespace roka::object
{
	template<typename T>
	static __forceinline std::shared_ptr<T> Instantiate(std::shared_ptr<GameObject> src)
	{
		std::shared_ptr<T> source = std::dynamic_pointer_cast<T>(src);
		if (source == nullptr)
			return nullptr;
		std::shared_ptr<T> ptr = std::make_shared<T>(*(source.get()));
		ptr->Initialize();
		return ptr;
	}
	template<typename T>
	static __forceinline std::shared_ptr<T> Instantiate()
	{
		std::shared_ptr<T> ptr = std::make_shared<T>();
		ptr->Initialize();
		return ptr;
	}
	template<typename T>
	static __forceinline std::shared_ptr<T> Instantiate(Vector3 pos)
	{
		std::shared_ptr<T> obj = std::make_shared<T>();
		std::shared_ptr<Transform> tf = obj->GetComponent<Transform>();
		tf->position = pos;
		obj->Initialize();
		return obj;
	}
	template<typename T>
	static __forceinline std::shared_ptr<T> Instantiate(Vector3 pos, Vector3 rotate)
	{
		std::shared_ptr<T> obj = std::make_shared<T>();
		std::shared_ptr<Transform> tf = obj->GetComponent<Transform>();
		tf->position = pos;
		tf->rotation = rotate;
		obj->Initialize();
		return obj;
	}
	template<typename T>
	static __forceinline std::shared_ptr<T> Instantiate(Vector3 pos, Vector3 rotate, Vector3 scale)
	{
		std::shared_ptr<T> obj = std::make_shared<T>();
		std::shared_ptr<Transform> tf = obj->GetComponent<Transform>();
		tf->position = pos;
		tf->rotation = rotate;
		tf->scale = scale;
		obj->Initialize();
		return obj;
	}
	template<typename T>
	static __forceinline std::shared_ptr<T> Instantiate(enums::ELayerType layer)
	{
		std::shared_ptr<T> obj = std::make_shared<T>();
		Scene* scene = SceneManager::GetActiveScene();
		scene->AddGameObject(layer, obj);
		obj->Initialize();
		obj->layer_type = layer;
		return obj;
	}
	template<typename T>
	static __forceinline std::shared_ptr<T> Instantiate(std::shared_ptr<GameObject> src,enums::ELayerType layer)
	{
		std::shared_ptr<T> source = std::dynamic_pointer_cast<T>(src);
		if (source == nullptr)
			return nullptr;

		std::shared_ptr<T> obj = std::make_shared<T>(*(source.get()));
		Scene* scene = SceneManager::GetActiveScene();
		scene->AddGameObject(layer, obj);
		obj->Initialize();
		obj->layer_type = layer;
		return obj;
	}
	template<typename T>
	static __forceinline std::shared_ptr<T> Instantiate(Vector3 pos,enums::ELayerType layer)
	{
		std::shared_ptr<T> obj = std::make_shared<T>();
		obj->GetComponent<Transform>()->position = pos;
		Scene* scene = SceneManager::GetActiveScene();
		scene->AddGameObject(layer, obj);
		obj->Initialize();
		obj->layer_type = layer;
		return obj;
	}
	template<typename T>
	static __forceinline std::shared_ptr<T> Instantiate(Vector3 pos,Vector3 rotate, enums::ELayerType layer)
	{
		std::shared_ptr<T> obj = std::make_shared<T>();
		std::shared_ptr<Transform> tf = obj->GetComponent<Transform>();
		tf->position = pos;
		tf->rotation = rotate;
		Scene* scene = SceneManager::GetActiveScene();
		scene->AddGameObject(layer, obj);
		obj->Initialize();
		obj->layer_type = layer;
		return obj;
	}
	template<typename T>
	static __forceinline std::shared_ptr<T> Instantiate(Vector3 pos, Vector3 rotate,Vector3 scale, enums::ELayerType layer)
	{
		std::shared_ptr<T> obj = std::make_shared<T>();
		std::shared_ptr<Transform> tf = obj->GetComponent<Transform>();
		tf->position = pos;
		tf->rotation = rotate;
		tf->scale = scale;
		Scene* scene = SceneManager::GetActiveScene();
		scene->AddGameObject(layer, obj);
		obj->Initialize();
		obj->layer_type = layer;
		return obj;
	}

	static __forceinline void Destroy(std::shared_ptr<GameObject> obj)
	{
		obj->SetState(roka::GameObject::EState::Dead);
	}
}