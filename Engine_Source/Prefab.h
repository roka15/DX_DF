#pragma once

#include "GameObject.h"

namespace roka::prefab
{
	void RegisterPrefab(std::wstring key, roka::GameObject* obj);
	void Initialize();
	void Release();

	extern std::map<std::wstring, std::shared_ptr<roka::GameObject>> Prefabs;
}