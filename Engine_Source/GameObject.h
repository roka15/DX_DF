#pragma once
#include "Entity.h"
namespace roka
{
	class GameObject : public Entity
	{
	public:
		enum EState
		{
			Active,
			Paused,
			Dead,
		};
		GameObject();
		virtual ~GameObject();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();
	private:
		EState mState;
	};
}


