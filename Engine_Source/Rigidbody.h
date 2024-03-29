#pragma once
#include "Component.h"

namespace roka
{
	class Rigidbody :
		public Component
	{
	private:
		Rigidbody();
		Rigidbody(const Rigidbody& ref);
		virtual void Copy(Component* src);
	public: 
		virtual ~Rigidbody();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		void SetGround(bool flag) { mbGround = flag; }
		bool GetGround() { return mbGround; }
		void IsGravity(bool flag) { mbGravity = flag; }
		void SetVelocity(Vector2 velocity);
		void disableGround() { mbGround = false; }
		void enableGround() { mbGround = true; }
		void DecreaseGravity(bool flag);
		void CompleteFallEvent();
		void SetLandingPoint(Vector2 pos) { mLandingPoint = pos; }
		void AddLandingPoint(Vector2 add);

		void AddForce(Vector2 force) { mForce += force; }
		void FallEvent(std::function<void()> func) { mFallEvent = func; }
		void EnalbeJump() { mbJumpFlag = true; }
		PROPERTY(GetGround, SetGround) bool is_ground;
	private:
		friend class FactoryBase;
		friend class ComponentFactory;
		float mTime;
		float mMass;
		Vector2 mForce;
		Vector2 mAccelation;
		Vector2 mVelocity;
		Vector2 mLimitedVelocity;
		Vector2 mGravity;
		Vector2 mMaxVelocity;

		float mFriction;
		bool mbGround;
		bool mbGravity;
		bool mbJumpFlag;
		float mDecreaseGravity;
		float mIncreaseGravity;
		bool mbFall;
		Vector2 mLandingPoint;

		bool mbFallEvent;
		std::function<void()> mFallEvent;
	};
}


 