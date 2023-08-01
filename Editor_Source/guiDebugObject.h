#pragma once
#include "GameObject.h"

namespace roka
{
	using namespace math;
}
namespace gui
{
	
	class DebugObject : public roka::GameObject
	{
	public:
		DebugObject();
		virtual ~DebugObject();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		virtual void Copy(GameObject* src);

		void SetColor(roka::math::Vector4 color);
	private:
		Vector4 mColor;
	};
}


