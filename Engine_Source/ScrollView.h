#pragma once
#include "UI.h"

namespace roka
{
	class ScrollView :
		public UI
	{
	public:
		ScrollView();
		virtual ~ScrollView();

		virtual void Copy(GameObject* src);
		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();
		virtual void Release();
	private:

	};
}


