#include "PlayerScript.h"
#include "GameObject.h"
#include "Input.h"
#include "RokaTime.h"
#include "Resources.h"
#include "NPK.h"

#include "Transform.h"
#include "Rigidbody.h"
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
		mRigid = owner->GetComponent<Rigidbody>();
		mAvatar = owner->GetChild<AvatarScript>()->GetComponent<AvatarScript>();
		mUser->Initialize();


		/*std::shared_ptr<MeshRenderer> mesh = mMeshRenderer.lock();
		mesh->mesh = Resources::Find<Mesh>(L"RectMesh");
		mesh->material = Resources::Find<Material>(L"DefaultAniMaterial");*/


		std::shared_ptr<AvatarScript> avatar = mAvatar.lock();
		//�ش� part�� �ִ� ����
		//skill ani�� ��� start event = DisableKeyInput �Լ� , end event = EnableKeyInput �Լ� ����
		//* ���� �Լ� �̱��� *
		avatar->CreatePartAni(EAvatarParts::Base, L"baseskin", mUser->base_avartar, L"PlayerBAIdle", 10, 14, 0.3f);
		avatar->CreatePartAni(EAvatarParts::Base, L"baseskin", mUser->base_avartar, L"PlayerBAWalk", 0, 10, 0.05f);
		avatar->CreatePartAni(EAvatarParts::Base, L"baseskin", mUser->base_avartar, L"PlayerBARun", 18, 21, 0.05f);
		avatar->CreatePartAni(EAvatarParts::Base, L"baseskin", mUser->base_avartar, L"PlayerBANomalAtk", 109, 120, 0.05f);
		
		std::shared_ptr<NPK> baseskin_npk = Resources::Find<NPK>(L"baseskin");
		std::shared_ptr<Texture> jump_texture = baseskin_npk->CreateAtlas(mUser->base_avartar, 76, 85, L"PlayerBAJump");
		
		avatar->CreatePartAni(EAvatarParts::Base, jump_texture, L"PlayerBAJump1", 0, 4, 0.185f);
		avatar->CreatePartAni(EAvatarParts::Base, jump_texture, L"PlayerBAJump2", 4, 7, 0.20755f);
		avatar->CreatePartAni(EAvatarParts::Base, jump_texture, L"PlayerBAJump3", 7, 9, 0.04f);
		//avatar->CreatePartAni(EAvatarParts::Base, L"baseskin", mUser->base_avartar, L"PlayerBAJump1",76,80,0.185f);
		//avatar->CreatePartAni(EAvatarParts::Base, L"baseskin", mUser->base_avartar, L"PlayerBAJump2", 80, 83, 0.20755f);
		//avatar->CreatePartAni(EAvatarParts::Base, L"baseskin", mUser->base_avartar, L"PlayerBAJump3", 83, 86, 0.04f);

		//player state �� ���� ����� �ִ� ���� ���
		avatar->InsertStateAniInfo(EPlayerState::Idle, EAvatarParts::Base, L"PlayerBAIdle");
		avatar->InsertStateAniInfo(EPlayerState::Walk, EAvatarParts::Base, L"PlayerBAWalk");
		avatar->InsertStateAniInfo(EPlayerState::Run, EAvatarParts::Base, L"PlayerBARun");
		avatar->InsertStateAniInfo(EPlayerState::NomalAtk, EAvatarParts::Base, L"PlayerBANomalAtk");
		avatar->InsertStateAniInfo(EPlayerState::Jump, EAvatarParts::Base, L"PlayerBAJump1");
		avatar->InsertStateAniInfo(EPlayerState::Jump, EAvatarParts::Base, L"PlayerBAJump2");
		avatar->InsertStateAniInfo(EPlayerState::Jump, EAvatarParts::Base, L"PlayerBAJump3");
	
		avatar->SetCompleteEventAnimation(EPlayerState::Jump,0,1);
		
		/*avatar->EndEventAnimation(EPlayerState::Jump, 1, std::bind([this]()->void { mRigid.lock()->SetGround(true); }));*/
		avatar->SetStartEventAnimation(EPlayerState::Jump, 2, std::bind([this]()->void { mMoveScript.lock()->is_active = false; }));
		avatar->CompleteEventAnimation(EPlayerState::Jump, 2, std::bind([this]()->void { NextState(); }));
		mPlayerState = EPlayerState::Idle;
		//���� idle ���� �ִ� ���.
		avatar->PlayPartsMotion();

		std::shared_ptr<MoveScript> ms = mMoveScript.lock();
		ms->SetSpeed(0.8f);


		Time::RegisterEvent(L"PlayerFallCompEvent",&PlayerScript::FallCompleteEvent);
		Time::RegisterEvent(L"PlayerJumpDashCompEvent", &PlayerScript::JumpDashCompleteEvent);
	}
	void PlayerScript::Update()
	{
		mTime += Time::DeltaTime();
	}
	void PlayerScript::LateUpdate()
	{
		if (mPlayerState >= EPlayerState::Jump
			&& mRigid.lock()->is_ground == true)
		{
			mPlayerState = EPlayerState::Idle;
			std::shared_ptr<AvatarScript> as = mAvatar.lock();
			as->StartAni();
			as->PlayPartsMotion(EPlayerState::Jump,2,false);
		}
	}
	void PlayerScript::Render()
	{
	}

	void PlayerScript::LeftBtnDown()
	{
		std::shared_ptr<MoveScript> ms = mMoveScript.lock();
		std::shared_ptr<AvatarScript> as = mAvatar.lock();
		std::shared_ptr<Rigidbody> rigid = mRigid.lock();
		mRightTime = 0.0;
		
		if (mPlayerState < EPlayerState::Jump)
		{
			if (ms->is_active == false)
				ms->is_active = true;
			if (mCurDir > 0.0f && mPlayerState == EPlayerState::Run)
			{
				mPlayerState = EPlayerState::Walk;
				ms->ResetSpeed();
			}
			else if (mPlayerState != EPlayerState::Run)
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
			as->PlayPartsMotion();
		}
		else
		{
			if (mTime - mLeftTime <= mDiff)
			{
				as->PlayPartsMotion(EPlayerState::Run, 0, true);
				rigid->is_active = false;
				ms->AddSpeed(3.0f);
				mPlayerState = EPlayerState::JumpRun;
				Time::CallBackTimerInfo info = {};
				info.endTime = 1.0;
				std::wstring key = L"PlayerJumpDashCompEvent";
				size_t str_length = key.size();
				std::wcsncpy(info.key, key.c_str(), str_length);
				Time::RequestEvent(info, owner->GetSharedPtr());
			}
		}
		as->SettingLeftMaterial();
		mCurDir = -1.0f;
		ms->SetDirX(-1.0f);
	}

	void PlayerScript::RightBtnDown()
	{
		std::shared_ptr<MoveScript> ms = mMoveScript.lock();
		std::shared_ptr<AvatarScript> as = mAvatar.lock();
		std::shared_ptr<Rigidbody> rigid = mRigid.lock();
		mLeftTime = 0.0;
		
	
		if (mPlayerState < EPlayerState::Jump)
		{
			if (ms->is_active == false)
				ms->is_active = true;

			if (mCurDir < 0.0f && mPlayerState == EPlayerState::Run)
			{
				mPlayerState = EPlayerState::Walk;
				ms->ResetSpeed();
			}
			else if (mPlayerState != EPlayerState::Run)
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
			as->PlayPartsMotion();
		}
		else
		{
			if (mTime - mRightTime <= mDiff)
			{
				as->PlayPartsMotion(EPlayerState::Run,0,true);
				rigid->is_active = false;
				ms->AddSpeed(3.0f);
				mPlayerState = EPlayerState::JumpRun;
				Time::CallBackTimerInfo info = {};
				info.endTime = 1.0;
				std::wstring key = L"PlayerJumpDashCompEvent";
				size_t str_length = key.size();
				std::wcsncpy(info.key, key.c_str(), str_length);
				Time::RequestEvent(info, owner->GetSharedPtr());
			}
		}
		
		as->SettingRightMaterial();
		mCurDir = 1.0f;
		ms->SetDirX(1.0f);
	}

	void PlayerScript::UpBtnDown()
	{
		std::shared_ptr<MoveScript> ms = mMoveScript.lock();
		std::shared_ptr<AvatarScript> as = mAvatar.lock();
		if (mPlayerState < EPlayerState::Jump)
		{
			if (ms->is_active == false)
				ms->is_active = true;
			if (mPlayerState != EPlayerState::Run)
				mPlayerState = EPlayerState::Walk;
			as->PlayPartsMotion();
		}
		ms->SetDirY(1.0f);
	}

	void PlayerScript::DownBtnDown()
	{
		std::shared_ptr<MoveScript> ms = mMoveScript.lock();
		std::shared_ptr<AvatarScript> as = mAvatar.lock();
		if (mPlayerState < EPlayerState::Jump)
		{
			if (ms->is_active == false)
				ms->is_active = true;
			if (mPlayerState != EPlayerState::Run)
				mPlayerState = EPlayerState::Walk;
			as->PlayPartsMotion();
		}
		ms->SetDirY(-1.0f);
	}

	void PlayerScript::LeftBtnUp()
	{
		std::shared_ptr<MoveScript> ms = mMoveScript.lock();
		std::shared_ptr<AvatarScript> as = mAvatar.lock();
		std::shared_ptr<Rigidbody> rigid = mRigid.lock();
		mLeftTime = mTime;
		
		if (mPlayerState == EPlayerState::JumpRun && mCurDir == -1.0f)
		{
			if (rigid->is_active == false)
				rigid->is_active = true;
			ms->SetDirX(0.0f);
			ms->ResetSpeed();
			as->PlayPartsMotion(EPlayerState::Jump, 1, false);
			Time::CallBackTimerInfo info = {};
			info.endTime = 0.0;
			std::wstring key = L"PlayerFallCompEvent";
			size_t str_length = key.size();
			std::wcsncpy(info.key, key.c_str(), str_length);
			Time::RequestEvent(info, owner->GetSharedPtr());
			return;
		}
		else
		{
			if (Input::GetKey((EKeyCode)mUser->right_key))
			{
				if (ms->is_active == false)
					ms->is_active = true;
				if (mPlayerState != EPlayerState::Jump && mPlayerState != EPlayerState::JumpHold)
				{
					mPlayerState = EPlayerState::Walk;
					ms->ResetSpeed();
				}
				ms->SetDirX(1.0f);
				as->SettingRightMaterial();
			}
			else
				ms->SetDirX(0.0f);
		}
		

		
		if (ms->is_stop)
		{
			//idle;
			if (mPlayerState < EPlayerState::Jump)
			{
				mPlayerState = EPlayerState::Idle;
				ms->ResetSpeed();
				as->PlayPartsMotion();
			}
		}
	}

	void PlayerScript::RightBtnUp()
	{
		std::shared_ptr<MoveScript> ms = mMoveScript.lock();
		std::shared_ptr<AvatarScript> as = mAvatar.lock();
		std::shared_ptr<Rigidbody> rigid = mRigid.lock();
		mRightTime = mTime;
		if (mPlayerState == EPlayerState::JumpRun && mCurDir == 1.0f)
		{
			if (rigid->is_active == false)
				rigid->is_active = true;
			ms->SetDirX(0.0f);
			ms->ResetSpeed();
			as->PlayPartsMotion(EPlayerState::Jump, 1, false);
			Time::CallBackTimerInfo info = {};
			info.endTime = 0.0;
			std::wstring key = L"PlayerFallCompEvent";
			size_t str_length = key.size();
			std::wcsncpy(info.key, key.c_str(), str_length);
			Time::RequestEvent(info, owner->GetSharedPtr());
			return;
		}
		else
		{
			if (Input::GetKey((EKeyCode)mUser->left_key))
			{
				if (ms->is_active == false)
					ms->is_active = true;
				if (mPlayerState < EPlayerState::Jump)
				{
					mPlayerState = EPlayerState::Walk;
					ms->ResetSpeed();
				}
				ms->SetDirX(-1.0f);
				as->SettingLeftMaterial();
			}
			else
				ms->SetDirX(0.0f);
		}
		

		if (ms->is_stop)
		{
			//idle
			if (mPlayerState < EPlayerState::Jump)
			{
				mPlayerState = EPlayerState::Idle;
				ms->ResetSpeed();
				as->PlayPartsMotion();
			}
		}
	}

	void PlayerScript::UpBtnUp()
	{
		std::shared_ptr<MoveScript> ms = mMoveScript.lock();
		mRightTime = 0.0;
		mLeftTime = 0.0;
		

		if (Input::GetKey((EKeyCode)mUser->down_key))
		{
			if (ms->is_active == false)
				ms->is_active = true;
			ms->SetDirY(-1.0f);
		}
		else
			ms->SetDirY(0.0f);


		if (ms->is_stop)
		{
			if (mPlayerState < EPlayerState::Jump)
			{
				//idle
				mPlayerState = EPlayerState::Idle;
				std::shared_ptr<AvatarScript> as = mAvatar.lock();
				ms->ResetSpeed();
				as->PlayPartsMotion();
			}
		}
	}

	void PlayerScript::DownBtnUp()
	{
		std::shared_ptr<MoveScript> ms = mMoveScript.lock();
		mRightTime = 0.0;
		mLeftTime = 0.0;

		if (Input::GetKey((EKeyCode)mUser->up_key))
		{
			if (ms->is_active == false)
				ms->is_active = true;
			ms->SetDirY(1.0f);
		}
		else
			ms->SetDirY(0.0f);


		if (ms->is_stop)
		{
			if (mPlayerState < EPlayerState::Jump)
			{
				//idle
				mPlayerState = EPlayerState::Idle;
				std::shared_ptr<AvatarScript> as = mAvatar.lock();
				ms->ResetSpeed();
				as->PlayPartsMotion();
			}
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
		std::shared_ptr<AvatarScript> as = mAvatar.lock();
		std::shared_ptr<Rigidbody> rigid = mRigid.lock();
		std::shared_ptr<MoveScript> ms = mMoveScript.lock();
		if (rigid->is_active == false)
			rigid->is_active = true;
		if (mPlayerState == EPlayerState::Jump || mPlayerState ==EPlayerState::JumpRun)
		{
			mPlayerState = EPlayerState::JumpHold;
			as->PlayPartsMotion(EPlayerState::Jump, 1, false);
			as->StopAni();
			rigid->DecreaseGravity(true);
			ms->ResetSpeed();
			Time::CallBackTimerInfo info = {};
			info.endTime = 1.5;
			std::wstring key = L"PlayerFallCompEvent";
			size_t str_length = key.size();
			std::wcsncpy(info.key, key.c_str(), str_length);
			Time::RequestEvent(info, owner->GetSharedPtr());
		}
		else
		{
			mPlayerState = EPlayerState::Jump;
			std::shared_ptr<Transform> tf = owner->GetComponent<Transform>();
			std::shared_ptr<Rigidbody> rigid = owner->GetComponent<Rigidbody>();
			std::shared_ptr<MoveScript> ms = mMoveScript.lock();
			
			rigid->SetVelocity(Vector2(0.0f, 1400.0f));
			rigid->disableGround();
			rigid->SetLandingPoint(Vector2(tf->position.x, tf->position.y));
			as->PlayPartsMotion();
			ms->ResetSpeed();
		}
	}

	void PlayerScript::NextState()
	{
		std::shared_ptr<AvatarScript> as = mAvatar.lock();
		std::shared_ptr<Rigidbody> rigid = mRigid.lock();
		std::shared_ptr<MoveScript> ms = mMoveScript.lock();
		if (Input::GetKey(EKeyCode::SPACE))
		{
			mPlayerState = EPlayerState::Idle;
		}
		else
		{
			if (Input::GetAniKey() == false)
			{
				mPlayerState = EPlayerState::Idle;
			}
			else if (Input::GetKey(EKeyCode::LEFT))
			{
				mPlayerState = EPlayerState::Walk;
				as->SettingLeftMaterial();
			}
			else if (Input::GetKey(EKeyCode::RIGHT))
			{
				mPlayerState = EPlayerState::Walk;
				as->SettingRightMaterial();
			}
			else if (Input::GetKey(EKeyCode::UP) || Input::GetKey(EKeyCode::DOWN))
			{
				mPlayerState = EPlayerState::Walk;
			}
		}
		

		if (ms->is_active == false)
		{
			ms->is_active = true;
		}
		as->PlayPartsMotion();
	}

	void PlayerScript::FallCompleteEvent(std::weak_ptr<void> ptr)
	{
		std::shared_ptr<void> Ptr = ptr.lock();
		GameObject* owner = reinterpret_cast<GameObject*>(Ptr.get());
		std::shared_ptr<PlayerScript> ps = owner->GetComponent<PlayerScript>();
		ps->mRigid.lock()->CompleteFallEvent();
	}

	void PlayerScript::JumpDashCompleteEvent(std::weak_ptr<void> ptr)
	{
		std::shared_ptr<void> Ptr = ptr.lock();
		GameObject* owner = reinterpret_cast<GameObject*>(Ptr.get());
		std::shared_ptr<PlayerScript> ps = owner->GetComponent<PlayerScript>();
		std::shared_ptr<AvatarScript> as = ps->mAvatar.lock();
		std::shared_ptr<Rigidbody> rigid = ps->mRigid.lock();
		std::shared_ptr<MoveScript> ms = ps->mMoveScript.lock();

		if ((ps->mCurDir == 1.0f && Input::GetKey(EKeyCode::RIGHT) && ps->mPlayerState == EPlayerState::JumpRun)
	        || (ps->mCurDir == -1.0f && Input::GetKey(EKeyCode::LEFT) && ps->mPlayerState == EPlayerState::JumpRun))
		{
			rigid->is_active = true;
			rigid->CompleteFallEvent();
			ms->ResetSpeed();
			as->PlayPartsMotion(EPlayerState::Jump, 1, false);
		}
	}
	
}