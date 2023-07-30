#pragma once
#include "GameObject.h"
namespace roka
{
	class MeshRenderer;
	class Transform;
	class ImageComponent;
	class Image : public GameObject
	{
	public:
		Image();
		Image(const Image& ref);
		virtual void Copy(GameObject* src)override;
		virtual ~Image();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;
	private:
		std::weak_ptr<MeshRenderer> mMeshRender;
		std::weak_ptr<Transform> mTransform;
		std::weak_ptr<ImageComponent> mImage;
	};
}


