#include "PlayerScript.h"
#include "GameObject.h"
#include "Input.h"
#include "Resources.h"

#include "Transform.h"
#include "MeshRenderer.h"
#include "MoveScript.h"
#include "AvatarScript.h"

#include "User.h"

using namespace roka::info;
namespace roka
{
	PlayerScript::PlayerScript() :Script(EScriptType::Player)
		, mUser(std::make_unique<User>())
		, mPlayerState(EPlayerState::Idle)
		, mIsActiveInput(true)
	{
	}
	PlayerScript::PlayerScript(const PlayerScript& ref) :Script(ref)
	{
		mUser = std::make_unique<User>(*(ref.mUser.get()));
	}
	PlayerScript::~PlayerScript()
	{
	}
	void PlayerScript::Copy(Component* src)
	{
		Script::Copy(src);
		PlayerScript* ps = dynamic_cast<PlayerScript*>(src);

		mUser->Copy(ps->mUser.get());
	}
	void PlayerScript::Initialize()
	{
		mTransform = owner->GetComponent<Transform>();
		mMoveScript = owner->GetComponent<MoveScript>();
		mAvatar = owner->GetChild<AvatarScript>()->GetComponent<AvatarScript>();
		mUser->Initialize();


		/*std::shared_ptr<MeshRenderer> mesh = mMeshRenderer.lock();
		mesh->mesh = Resources::Find<Mesh>(L"RectMesh");
		mesh->material = Resources::Find<Material>(L"DefaultAniMaterial");*/


		std::shared_ptr<AvatarScript> avatar = mAvatar.lock();
		//해당 part의 애니 생성
		//skill ani의 경우 start event = DisableKeyInput 함수 , end event = EnableKeyInput 함수 연결
		//* 연결 함수 미구현 *
		avatar->CreatePartAni(EAvatarParts::Base, L"baseskin", mUser->base_avartar, L"PlayerBAIdle", 10, 14, 0.3f);
		avatar->CreatePartAni(EAvatarParts::Base, L"baseskin", mUser->base_avartar, L"PlayerBAWalk", 0, 10, 0.05f);

		//player state 에 따라 재생할 애니 정보 등록
		avatar->InsertStateAniInfo(EPlayerState::Idle, EAvatarParts::Base, L"PlayerBAIdle");
		avatar->InsertStateAniInfo(EPlayerState::Walk, EAvatarParts::Base, L"PlayerBAWalk");

		mPlayerState = EPlayerState::Idle;
		//현재 idle 상태 애니 재생.
		avatar->PlayPartsMotion();


		std::shared_ptr<MoveScript> ms = mMoveScript.lock();
		ms->SetSpeed(0.8f);
	}
	void PlayerScript::Update()
	{
	}
	void PlayerScript::LateUpdate()
	{
	}
	void PlayerScript::Render()
	{
	}

	void PlayerScript::LeftBtnDown()
	{
		mPlayerState = EPlayerState::Walk;
		std::shared_ptr<MoveScript> ms = mMoveScript.lock();
		std::shared_ptr<AvatarScript> as = mAvatar.lock();
		ms->SetDirX(-1.0f);
		as->SettingLeftMaterial();
		as->PlayPartsMotion();
	}

	void PlayerScript::RightBtnDown()
	{
		mPlayerState = EPlayerState::Walk;
		std::shared_ptr<MoveScript> ms = mMoveScript.lock();
		std::shared_ptr<AvatarScript> as = mAvatar.lock();
		ms->SetDirX(1.0f);
		as->SettingRightMaterial();
		as->PlayPartsMotion();
	}

	void PlayerScript::UpBtnDown()
	{
		mPlayerState = EPlayerState::Walk;
		std::shared_ptr<MoveScript> ms = mMoveScript.lock();
		ms->SetDirY(1.0f);

		std::shared_ptr<AvatarScript> as = mAvatar.lock();
		as->PlayPartsMotion();
	}

	void PlayerScript::DownBtnDown()
	{
		mPlayerState = EPlayerState::Walk;
		std::shared_ptr<MoveScript> ms = mMoveScript.lock();
		ms->SetDirY(-1.0f);

		std::shared_ptr<AvatarScript> as = mAvatar.lock();
		as->PlayPartsMotion();
	}

	void PlayerScript::LeftBtnUp()
	{
		std::shared_ptr<MoveScript> ms = mMoveScript.lock();
		std::shared_ptr<AvatarScript> as = mAvatar.lock();
		if (Input::GetKey((EKeyCode)mUser->right_key))
		{
			ms->SetDirX(1.0f);
			as->SettingRightMaterial();
		}
		else
			ms->SetDirX(0.0f);

		if (ms->is_stop)
		{
			//idle;
			mPlayerState = EPlayerState::Idle;
			as->PlayPartsMotion();
		}
	}

	void PlayerScript::RightBtnUp()
	{
		std::shared_ptr<MoveScript> ms = mMoveScript.lock();
		std::shared_ptr<AvatarScript> as = mAvatar.lock();
		if (Input::GetKey((EKeyCode)mUser->left_key))
		{
			ms->SetDirX(-1.0f);
			as->SettingLeftMaterial();
		}
		else
			ms->SetDirX(0.0f);

		if (ms->is_stop)
		{
			//idle
			mPlayerState = EPlayerState::Idle;
			as->PlayPartsMotion();
		}
	}

	void PlayerScript::UpBtnUp()
	{
		std::shared_ptr<MoveScript> ms = mMoveScript.lock();
		if (Input::GetKey((EKeyCode)mUser->down_key))
			ms->SetDirY(-1.0f);
		else
			ms->SetDirY(0.0f);

		if (ms->is_stop)
		{
			//idle
			mPlayerState = EPlayerState::Idle;
			std::shared_ptr<AvatarScript> as = mAvatar.lock();
			as->PlayPartsMotion();
		}
	}

	void PlayerScript::DownBtnUp()
	{
		std::shared_ptr<MoveScript> ms = mMoveScript.lock();
		if (Input::GetKey((EKeyCode)mUser->up_key))
			ms->SetDirY(1.0f);
		else
			ms->SetDirY(0.0f);

		if (ms->is_stop)
		{
			//idle
			mPlayerState = EPlayerState::Idle;
			std::shared_ptr<AvatarScript> as = mAvatar.lock();
			as->PlayPartsMotion();
		}
	}
}