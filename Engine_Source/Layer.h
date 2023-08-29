#pragma once
#include "GameObject.h"
namespace roka
{
	class Layer
	{
	public:
		Layer();
		~Layer();
		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();
		virtual void Destroy();
		void AddGameObject(std::shared_ptr<GameObject> gameObj);

		void Clear();
		std::shared_ptr<GameObject> FindGameObject(std::wstring name);

		const std::vector<std::shared_ptr<GameObject>>& GetGameObjects() { return mGameObjects; }
	private:
		std::vector<std::shared_ptr<GameObject>> mGameObjects;
	};
}


