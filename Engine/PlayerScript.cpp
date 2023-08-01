#include "PlayerScript.h"
#include "GameObject.h"
#include "Input.h"
#include "RokaTime.h"
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
		mLeftTime = 0.0;
		mRightTime = 0.0;
		mTime = 0.0;
		mDiff = 0.1;
		mCurDir = 0.0f;
	}
	PlayerScript::PlayerScript(const PlayerScript& ref) :Script(ref)
	{
		mUser = std::make_unique<User>(*(ref.mUser.get()));
		mLeftTime = 0.0;
		mRightTime = 0.0;
		mTime = 0.0;
		mDiff = 0.1;
		mCurDir = 0.0f;
	}
	PlayerScript::~PlayerScript()
	{
	}
	void PlayerScript::Copy(Component* src)
	{
		Script::Copy(src);
		PlayerScript* ps = dynamic_cast<PlayerScript*>(src);

		mUser->Copy(ps->mUser.get());

		mLeftTime = 0.0;
		mRightTime = 0.0;
		mTime = 0.0;
		mDiff = 0.1;
		mCurDir = 0.0f;
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
		avatar->CreatePartAni(EAvatarParts::Base, L"baseskin", mUser->base_avartar, L"PlayerBARun", 18, 21, 0.05f);
		avatar->CreatePartAni(EAvatarParts::Base, L"baseskin", mUser->base_avartar, L"PlayerBANomalAtk", 109, 120, 0.05f);

		//player state 에 따라 재생할 애니 정보 등록
		avatar->InsertStateAniInfo(EPlayerState::Idle, EAvatarParts::Base, L"PlayerBAIdle");
		avatar->InsertStateAniInfo(EPlayerState::Walk, EAvatarParts::Base, L"PlayerBAWalk");
		avatar->InsertStateAniInfo(EPlayerState::Run, EAvatarParts::Base, L"PlayerBARun");
		avatar->InsertStateAniInfo(EPlayerState::NomalAtk, EAvatarParts::Base, L"PlayerBANomalAtk");
		mPlayerState = EPlayerState::Idle;
		//현재 idle 상태 애니 재생.
		avatar->PlayPartsMotion();


		std::shared_ptr<MoveScript> ms = mMoveScript.lock();
		ms->SetSpeed(0.8f);
	}
	void PlayerScript::Update()
	{
		mTime += Time::DeltaTime();
	}
	void PlayerScript::LateUpdate()
	{
	}
	void PlayerScript::Render()
	{
	}

	void PlayerScript::LeftBtnDown()
	{
		std::shared_ptr<MoveScript> ms = mMoveScript.lock();
		std::shared_ptr<AvatarScript> as = mAvatar.lock();
		mRightTime = 0.0;

		if (mCurDir > 0.0f && mPlayerState == EPlayerState::Run)
		{
			mPlayerState = EPlayerState::Walk;
			ms->ResetSpeed();
		}
		else if(mPlayerState != EPlayerState::Run)
		{
			if (mTime - mLeftTime <= mDiff)
			{
				mPlayerState = EPlayerState::Run;
				ms->AddSpeed(2.0f);
			}
			else
			{
				mPlayerState = EPlayerState::Walk;
			}
		}
		mCurDir = -1.0f;
		ms->SetDirX(-1.0f);
		as->SettingLeftMaterial();
		as->PlayPartsMotion();
	}

	void PlayerScript::RightBtnDown()
	{
		std::shared_ptr<MoveScript> ms = mMoveScript.lock();
		std::shared_ptr<AvatarScript> as = mAvatar.lock();
		mLeftTime = 0.0;
		
		ms->SetDirX(1.0f);
		
		if (mCurDir < 0.0f && mPlayerState == EPlayerState::Run)
		{
			mPlayerState = EPlayerState::Walk;
			ms->ResetSpeed();
		}
		else if(mPlayerState != EPlayerState::Run)
		{
			if (mTime - mRightTime <= mDiff)
			{
				mPlayerState = EPlayerState::Run;
				ms->AddSpeed(2.0f);
			}
			else
			{
				mPlayerState = EPlayerState::Walk;
			}
		}
		mCurDir = 1.0f;
		as->SettingRightMaterial();
		as->PlayPartsMotion();
	}

	void PlayerScript::UpBtnDown()
	{
		std::shared_ptr<MoveScript> ms = mMoveScript.lock();
		std::shared_ptr<AvatarScript> as = mAvatar.lock();
		if (mPlayerState != EPlayerState::Run)
			mPlayerState = EPlayerState::Walk;
		ms->SetDirY(1.0f);
		as->PlayPartsMotion();
	}

	void PlayerScript::DownBtnDown()
	{
		std::shared_ptr<MoveScript> ms = mMoveScript.lock();
		std::shared_ptr<AvatarScript> as = mAvatar.lock();
		if (mPlayerState != EPlayerState::Run)
			mPlayerState = EPlayerState::Walk;
		ms->SetDirY(-1.0f);
		as->PlayPartsMotion();
	}

	void PlayerScript::LeftBtnUp()
	{
		std::shared_ptr<MoveScript> ms = mMoveScript.lock();
		std::shared_ptr<AvatarScript> as = mAvatar.lock();
		mLeftTime = mTime;
		

		if (Input::GetKey((EKeyCode)mUser->right_key))
		{
			mPlayerState = EPlayerState::Walk;
			ms->SetDirX(1.0f);
			ms->ResetSpeed();
			as->SettingRightMaterial();
		}
		else
			ms->SetDirX(0.0f);

		
		if (ms->is_stop)
		{
			//idle;
			mPlayerState = EPlayerState::Idle;
			ms->ResetSpeed();
			as->PlayPartsMotion();
		}
	}

	void PlayerScript::RightBtnUp()
	{
		std::shared_ptr<MoveScript> ms = mMoveScript.lock();
		std::shared_ptr<AvatarScript> as = mAvatar.lock();

		mRightTime = mTime;
		
		if (Input::GetKey((EKeyCode)mUser->left_key))
		{
			mPlayerState = EPlayerState::Walk;
			ms->SetDirX(-1.0f);
			ms->ResetSpeed();
			as->SettingLeftMaterial();
		}
		else
			ms->SetDirX(0.0f);

		if (ms->is_stop)
		{
			//idle
			mPlayerState = EPlayerState::Idle;
			ms->ResetSpeed();
			as->PlayPartsMotion();
		}
	}

	void PlayerScript::UpBtnUp()
	{
		std::shared_ptr<MoveScript> ms = mMoveScript.lock();
		mRightTime = 0.0;
		mLeftTime = 0.0;
		

		if (Input::GetKey((EKeyCode)mUser->down_key))
			ms->SetDirY(-1.0f);
		else
			ms->SetDirY(0.0f);


		if (ms->is_stop)
		{
			//idle
			mPlayerState = EPlayerState::Idle;
			std::shared_ptr<AvatarScript> as = mAvatar.lock();
			ms->ResetSpeed();
			as->PlayPartsMotion();
		}
	}

	void PlayerScript::DownBtnUp()
	{
		std::shared_ptr<MoveScript> ms = mMoveScript.lock();
		mRightTime = 0.0;
		mLeftTime = 0.0;

		if (Input::GetKey((EKeyCode)mUser->up_key))
			ms->SetDirY(1.0f);
		else
			ms->SetDirY(0.0f);


		if (ms->is_stop)
		{
			//idle
			mPlayerState = EPlayerState::Idle;
			std::shared_ptr<AvatarScript> as = mAvatar.lock();
			ms->ResetSpeed();
			as->PlayPartsMotion();
		}
	}
	void PlayerScript::NomalAtkBtnDown()
	{
		mPlayerState = EPlayerState::NomalAtk;
		std::shared_ptr<AvatarScript> as = mAvatar.lock();
		as->PlayPartsMotion();
	}
	void PlayerScript::JumpBtnDown()
	{
	}
	
}