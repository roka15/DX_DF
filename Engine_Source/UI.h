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
		void SetViewPortRect(RECT rect) { mViewPortRect = rect; }
		RECT GetViewPortRect() { return mViewPortRect; }

		void SetUIType(EUIType type) { mUIType = type; }
		const EUIType& GetUIType() { return mUIType; }
		PROPERTY(GetUIType,SetUIType) EUIType ui_type;
		
		void SetTarget(std::shared_ptr<GameObject> target) { mTarget = target; }
	private:
		bool mbRayCastTarget;
		RECT mViewPortRect;
		EUIType mUIType;
		std::weak_ptr<GameObject> mTarget;
	};
}


