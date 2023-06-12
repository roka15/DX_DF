#pragma once
#include "Entity.h"
#include "GameObject.h"
namespace roka
{
	class Scene : public Entity
	{
	public:
		Scene();
		virtual ~Scene();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();
	private:
		std::vector<GameObject*> mGameObjects;
	};

}

