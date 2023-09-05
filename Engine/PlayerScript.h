#pragma once
#include "Script.h"
#include "ContentEnums.h"
namespace roka::info
{
	class User;
}
namespace roka
{
	class Transform;
	class Animator;
	class MeshRenderer;
	class MoveScript;
	class AvatarScript;
	class Rigidbody;

	class PlayerScript :
		public Script
	{
	private:
		PlayerScript();
		PlayerScript(const PlayerScript& ref);
		virtual void Copy(Component* src)override;
	public:
		virtual ~PlayerScript();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(std::shared_ptr<Collider2D> other);
		virtual void OnCollisionStay(std::shared_ptr<Collider2D> other);
		virtual void OnCollisionExit(std::shared_ptr<Collider2D> other);

		virtual void BeAttacked(float damage,EStunState stun);

		void Move();
		// input system 적용시 사용
		void LeftBtnDown();
		void RightBtnDown();
		void UpBtnDown();;
		void DownBtnDown();

		void LeftBtnUp();
		void RightBtnUp();
		void UpBtnUp();
		void DownBtnUp();
		void NomalAtkBtnDown();
		void JumpBtnDown();

		void StunStagger(EStunState stun,float endtime);
		void StunDown();

		void NextState();
		void DownEvent();

		EPlayerState GetState() { return mPlayerState; }
		void EnableKeyInput() { mIsActiveInput = true; }
		void DisableKeyInput() { mIsActiveInput = false; }

		static void FallCompleteEvent(std::weak_ptr<void> ptr);
		static void JumpDashCompleteEvent(std::weak_ptr<void> ptr);
		static void StunCompleteEvent(std::weak_ptr<void> ptr);

		
		GET_PROPERTY(GetState) EPlayerState player_state;
	protected:
		
	private:
		friend class FactoryBase;
		friend class ScriptFactory;

		EPlayerState mPlayerState;
		EStunState mStunState;
		bool mIsActiveInput;

		std::unique_ptr<info::User> mUser;
		std::weak_ptr<Transform> mTransform;
		std::weak_ptr<MoveScript> mMoveScript;
		std::weak_ptr<AvatarScript> mAvatar;
		std::weak_ptr<Rigidbody> mRigid;
		std::weak_ptr<Collider2D> mTopCollider;
		std::weak_ptr<Collider2D> mBottomCollider;
	

		double mLeftTime;
		double mRightTime;
		double mTime;
		double mDiff;

		float mCurDir;
	};
}



