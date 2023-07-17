#pragma once
#include "GameObject.h"
namespace roka
{
	class MeshRenderer;
	class Image : public GameObject
	{
	public:
		Image();
		virtual ~Image();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

	private:
		MeshRenderer* mMeshRenderer;
	};
}


