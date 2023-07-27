#pragma once
#include "..\Engine_Source\Scene.h"

namespace roka
{
	class HendonmyreScene :public Scene
	{
	public:
		HendonmyreScene();
		~HendonmyreScene();

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


