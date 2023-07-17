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

		return std::make_shared<T>(*(source.get()));
	}
	template<typename T>
	static __forceinline std::shared_ptr<T> Instantiate()
	{
		return std::make_shared<T>();
	}
	template<typename T>
	static __forceinline std::shared_ptr<T> Instantiate(Vector3 pos)
	{
		std::shared_ptr<T> obj = std::make_shared<T>();
		std::shared_ptr<Transform> tf = obj->GetComponent<Transform>();
		tf->position = pos;
		return obj;
	}
	template<typename T>
	static __forceinline std::shared_ptr<T> Instantiate(Vector3 pos, Vector3 rotate)
	{
		std::shared_ptr<T> obj = std::make_shared<T>();
		std::shared_ptr<Transform> tf = obj->GetComponent<Transform>();
		tf->position = pos;
		tf->rotation = rotate;
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
		return obj;
	}
	template<typename T>
	static __forceinline std::shared_ptr<T> Instantiate(enums::ELayerType layer)
	{
		std::shared_ptr<T> obj = std::make_shared<T>();
		Scene* scene = SceneManager::GetActiveScene();
		scene->AddGameObject(layer, obj);

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
		
		return obj;
	}
	template<typename T>
	static __forceinline std::shared_ptr<T> Instantiate(Vector3 pos,enums::ELayerType layer)
	{
		std::shared_ptr<T> obj = std::make_shared<T>();
		obj->GetComponent<Transform>()->position = pos;

		Scene* scene = SceneManager::GetActiveScene();
		scene->AddGameObject(layer, obj);

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

		return obj;
	}

	static __forceinline void Destroy(std::shared_ptr<GameObject> obj)
	{
		obj->SetState(roka::GameObject::EState::Dead);
	}
}