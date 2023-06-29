#pragma once
#include "Scene.h"
namespace roka
{
	class WestcoastScene :public Scene
	{
	public:
		WestcoastScene();
		~WestcoastScene();

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

