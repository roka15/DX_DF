#pragma once
#include "..\Engine_Source\Scene.h"
namespace roka
{
	class PlayScene : public Scene
	{
	public:
		PlayScene();
		~PlayScene();
		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;
		virtual void Loading()override;
	private:

	};
}


