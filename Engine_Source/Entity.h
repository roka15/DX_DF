#pragma once
#include "RokaEngine.h"
namespace roka
{
	class Entity
	{
	public:
		Entity();
		Entity(const Entity& ref);
		void Copy(Entity* ref);
		virtual ~Entity();

		void SetName(const std::wstring& name) { mName = name; }
		std::wstring& GetName() { return mName; }
		void SetID(UINT64 id) { mID = id; }
		UINT64 GetID() { return mID; }
	private:
		std::wstring mName;
		UINT64 mID;
	};
}


