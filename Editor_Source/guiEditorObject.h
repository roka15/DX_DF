#pragma once
#include "GameObject.h"

namespace gui
{
	class EditorObject:public roka::GameObject
	{
	public:
		EditorObject();
		virtual ~EditorObject();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		virtual void Copy(GameObject* src);
		
	};

}

