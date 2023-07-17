#pragma once
#include "Component.h"

namespace roka
{
	class Transform;
	class Collider2D :public Component
	{
	public:
		Collider2D();
		~Collider2D();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void SetType(EColliderType type) { mType = type; }
		void SetSize(Vector2 size) { mSize = size; }
		void SetCenter(Vector2 size) { mCenter = size; }
	private:
		EColliderType mType;
		std::weak_ptr<Transform> mTransform;

		Vector2 mSize;
		Vector2 mCenter;
	};
}


