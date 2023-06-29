#pragma once
#include "Scene.h"
namespace roka
{
	class SeriaGateScene :
		public Scene
	{
	public:
		SeriaGateScene();
		~SeriaGateScene();


		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

		virtual void OnExit()override;
		virtual void OnEnter()override;
		virtual void Loading()override;
	private:

	};
}


