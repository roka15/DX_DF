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
		void IsGravity(bool flag) { mbGravity = flag; }
		void SetVelocity(Vector2 velocity);
		void disableGround() { mbGround = false; }
		void DecreaseGravity(bool flag);
		static void CompleteFallEvent(void* ptr);
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

		float mFriction;
		bool mbGround;
		bool mbGravity;
		float mDecreaseGravity;
		float mIncreaseGravity;
		bool mbFall;
	};
}


 