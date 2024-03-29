#pragma once
#include "Component.h"
#include "GameObject.h"
namespace roka
{ 
	//rect transform ���
	class Transform : public Component
	{
	private:
		Transform();
		Transform(const Transform& ref);
		virtual void Copy(Component* src)override;
	public:
		~Transform();
		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

		void BindConstantBuffer();

		void SetPosition(Vector3 position) {mPosition =  position; }
		void SetRotation(Vector3 rotation) { mRotation = rotation; }
		void SetScale(Vector3 scale) { mScale = scale; }

		void SetPosition(float x, float y, float z) {mPosition = Vector3(x, y, z); }
		void SetRotation(float x, float y, float z) { mRotation = Vector3(x, y, z); }
		void SetScale(float x, float y, float z) { mScale = Vector3(x, y, z); }

		void SetPosition(Vector2 position) { mPosition.x = position.x; mPosition.y = position.y; }
		void SetWorldPosition(Vector3 world);

		Vector3 GetLocalPosition() { return mPosition; }
		Vector3 GetLocalScale() { return mScale; }
		Vector3 GetLocalRotation() { return mRotation; }
		Vector3 GetPosition(); 
		Vector3 GetRotation(); 
		Vector3 GetScale(); 

		Vector3 Up() { return mUp; }
		Vector3 Right() { return mRight; }
		Vector3 Forward() { return mForward; }

		Matrix& GetMatrix() { return mWorld; }
		float GetWorldZ();

		void SetPivot(Vector3 pivot) { mPivot = pivot; }
		void EnablePivot();
		void DisablePivot(); 


		PROPERTY(GetPosition, SetPosition) Vector3 position;
		PROPERTY(GetRotation, SetRotation)Vector3 rotation;
		PROPERTY(GetScale, SetScale)Vector3 scale;

		GET_PROPERTY(Up) Vector3 up;
		GET_PROPERTY(Right) Vector3 right;
		GET_PROPERTY(Forward) Vector3 forward;
		
	
	private:
		friend class FactoryBase;
		friend class ComponentFactory;
		Vector3 mPosition;
		Vector3 mRotation;
		Vector3 mScale;

		Vector3 mWorldPosition;
		Vector3 mWorldRotation;
		Vector3 mWorldScale;

		Vector3 mUp;
		Vector3 mForward;
		Vector3 mRight;

		Vector3 mPivot;
		bool mbPivot;
		Vector3 mPivotOriginScale;
		Vector3 mPivotOriginPos;
		Matrix mWorld;
	};
}

