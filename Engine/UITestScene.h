#pragma once
#include "Scene.h"
namespace roka
{
	class UITestScene :
		public Scene
	{
	public:
		UITestScene(); 
		virtual ~UITestScene();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();
		virtual void Release();
		virtual void Destroy();

		virtual void OnExit();
		virtual void OnEnter();

		virtual void Loading();
	private:

	};
}


