#pragma once
#include "GameObject.h"
namespace roka
{
	class UI :
		public GameObject
	{
	public:
		UI();
		UI(const UI& ref);
		virtual ~UI() {}

		virtual void Copy(GameObject* src);
		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();
		virtual void Release();

		void SetRayCastTarget(bool flag) { mbRayCastTarget = flag; }

	private:
		bool mbRayCastTarget;
	};
}


