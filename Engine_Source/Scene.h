#pragma once
#include "Entity.h"
#include "Layer.h"
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

		virtual void OnExit();
		virtual void OnEnter();
		void AddGameObject(ELayerType type, GameObject* gameObj);
	private:
		std::vector<Layer> mLayers;
	};

}

