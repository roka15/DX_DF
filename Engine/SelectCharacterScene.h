#pragma once
#include "Scene.h"
namespace roka
{
	class SelectCharacterScene :
		public Scene
	{
	public:
		SelectCharacterScene();
		virtual ~SelectCharacterScene();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		virtual void OnExit();
		//virtual void OnEnter();

		virtual void Loading();
	};
}


