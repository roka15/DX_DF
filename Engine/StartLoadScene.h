#pragma once
#include "Scene.h"
namespace roka
{
	class StartLoadScene :
		public Scene
	{
	public:
		StartLoadScene():Scene(ESceneType::StartLoad){}
		~StartLoadScene() {}
		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		virtual void OnExit();
		virtual void OnEnter();
		virtual void Loading()override;
	private:

	};
}

