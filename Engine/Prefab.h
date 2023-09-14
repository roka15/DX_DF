#pragma once

#include "GameObject.h"
#include "MyResource.h"
namespace roka::prefab
{
	void RegisterPrefab(std::wstring key, roka::GameObject* obj);
	void Initialize();
	void LateInitialize();
	void Release();

	void NPKLoad();
	extern std::map<std::wstring, std::shared_ptr<roka::GameObject>> Prefabs;
	extern std::map<std::wstring, std::shared_ptr<roka::Resource>> Resources;
}