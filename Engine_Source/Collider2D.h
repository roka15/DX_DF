#pragma once
#include "Component.h"

namespace roka
{
	class Transform;
	class Collider2D :public Component
	{
	private:
		Collider2D();
		Collider2D(const Collider2D& ref);
		virtual void Copy(Component* src)override;
	public:
		~Collider2D();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void OnCollisionEnter(std::shared_ptr<Collider2D> other);
		void OnCollisionStay(std::shared_ptr<Collider2D> other);
		void OnCollisionExit(std::shared_ptr<Collider2D> other);

		void SetType(EColliderType type) { mColType = type; }
		void SetSize(Vector2 size) { mSize = size; }
		void SetCenter(Vector2 size) { mCenter = size; }
		UINT GetColliderID() { return mColliderID; }

		GET_PROPERTY(GetColliderID) UINT collider_id;
	private:
		friend class FactoryBase;
		friend class ComponentFactory;

		static UINT mColliderNumber;
		UINT mColliderID;
		EColliderType mColType;
		std::weak_ptr<Transform> mTransform;

		Vector3 mPosition;
		Vector2 mSize;
		Vector2 mCenter;
	};
}


