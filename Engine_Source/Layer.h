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

		void AddGameObject(GameObject* gameObj);
		GameObject* FindGameObject(std::wstring name);
	private:
		std::vector<GameObject*> mGameObjects;
	};
}


