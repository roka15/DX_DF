#pragma once
#include "Component.h"
#include "..\\Engine\\ICollisionListener.h"
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
		Vector2 GetSize() { return mSize; }
		void SetCenter(Vector2 size) { mCenter = size; }
		Vector2 GetCenter() { return mCenter; }
		void SetRotation(float z) { mRotationZ = z; }
		float GetRotation() { return mRotationZ; }
		

		UINT GetColliderID() { return mColliderID; }
		EHitBoxType GetHitType() { return mHitType; }
		void SetHitType(EHitBoxType type) { mHitType = type; }
		
		void SetTime(double time) { mTime = time; }
		double GetTime() { return mTime; }
		void EnableRender() { mbRender = true; }
		void DisableRender() { mbRender = false; }

		void EnableColCheck() { mbColCehck = true; }
		void DisableColCheck() { mbColCehck = false; }

		PROPERTY(GetSize, SetSize) Vector2 size;
		PROPERTY(GetCenter, SetCenter) Vector2 center;

		GET_PROPERTY(GetColliderID) UINT collider_id;
		PROPERTY(GetTime,SetTime) double time;

		void SetCollisionListener(ICollisionListener* listener) { mCollisionListener = listener; }
		
	private:
		friend class FactoryBase;
		friend class ComponentFactory;

		static UINT mColliderNumber;
		UINT mColliderID;
		EColliderType mColType;
		std::weak_ptr<Transform> mTransform;


		Vector3 mPosition;
		float mRotationZ;
		Vector2 mSize;
		Vector2 mCenter;
		bool mbCollision;
		double mTime;
		bool mbRender;
		bool mbColCehck;

		EHitBoxType mHitType;
		ICollisionListener* mCollisionListener;
	};
}


