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

		virtual void OnCollisionEnter(std::shared_ptr<Collider2D> other) {}
		virtual void OnCollisionStay(std::shared_ptr<Collider2D> other) {}
		virtual void OnCollisionExit(std::shared_ptr<Collider2D> other) {}

		void Move();

		EPlayerState GetState() { return mPlayerState; }
		void EnableKeyInput() { mIsActiveInput = true; }
		void DisableKeyInput() { mIsActiveInput = false; }

	
		GET_PROPERTY(GetState) EPlayerState player_state;
	protected:
		void SettingRightMaterial(std::shared_ptr<MeshRenderer> mr);
		void SettingLeftMaterial(std::shared_ptr<MeshRenderer> mr);
	private:
		friend class FactoryBase;
		friend class ScriptFactory;

		EPlayerState mPlayerState;
		bool mIsActiveInput;

		std::unique_ptr<info::User> mUser;
		std::weak_ptr<Transform> mTransform;
		std::weak_ptr<MeshRenderer> mMeshRenderer;
		std::weak_ptr<MoveScript> mMoveScript;
		std::weak_ptr<AvatarScript> mAvatar;
	};
}



