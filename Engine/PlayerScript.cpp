#include "PlayerScript.h"
#include "GameObject.h"
#include "Input.h"
#include "RokaTime.h"
#include "Resources.h"
#include "NPK.h"
#include "CollisionManager.h"

#include "Transform.h"
#include "Rigidbody.h"
#include "Animator.h"
#include "MeshRenderer.h"
#include "Collider2D.h"
#include "MoveScript.h"
#include "AvatarScript.h"
#include "SkillScript.h"
#include "WeaponScript.h"


#include "User.h"


using namespace roka::info;
namespace roka
{
	PlayerScript::PlayerScript() :Script(EScriptType::Player)
		, mUser(std::make_unique<User>())
		, mPlayerState(EPlayerState::Idle)
		, mStunState(EStunState::None)
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
		mStunState = EStunState::None;
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
		mStunState = EStunState::None;
	}
	void PlayerScript::Initialize()
	{
		mTransform = owner->GetComponent<Transform>();
		mMoveScript = owner->GetComponent<MoveScript>();
		mRigid = owner->GetComponent<Rigidbody>();
		mAvatar = owner->GetChild<AvatarScript>()->GetComponent<AvatarScript>();
		mUser->Initialize();
		std::vector<std::shared_ptr<Collider2D>> vec
			= owner->GetChilds<Collider2D>();
		mTopCollider = vec[0];
		mBottomCollider = vec[1];

		std::shared_ptr<AvatarScript> avatar = mAvatar.lock();
		//해당 part의 애니 생성
#pragma region base part
		avatar->CreatePartAni(EAvatarParts::Base, L"baseskin", mUser->base_avartar, L"PlayerBAIdle", 10, 14, 0.3f);
		avatar->CreatePartAni(EAvatarParts::Base, L"baseskin", mUser->base_avartar, L"PlayerBAWalk", 0, 10, 0.05f);
		avatar->CreatePartAni(EAvatarParts::Base, L"baseskin", mUser->base_avartar, L"PlayerBARun", 18, 21, 0.05f);
		avatar->CreatePartAni(EAvatarParts::Base, L"baseskin", mUser->base_avartar, L"PlayerBANomalAtk", 109, 120, 0.05f);

		std::shared_ptr<NPK> baseskin_npk = Resources::Find<NPK>(L"baseskin");
		std::shared_ptr<Texture> jump_texture = baseskin_npk->CreateAtlas(mUser->base_avartar, 76, 85, L"PlayerBAJump");

		avatar->CreatePartAni(EAvatarParts::Base, jump_texture, L"PlayerBAJump1", 0, 4, 0.185f);
		avatar->CreatePartAni(EAvatarParts::Base, jump_texture, L"PlayerBAJump2", 4, 7, 0.20755f);
		avatar->CreatePartAni(EAvatarParts::Base, jump_texture, L"PlayerBAJump3", 7, 9, 0.04f);

		std::shared_ptr<Texture> stun_texter = baseskin_npk->CreateAtlas(mUser->base_avartar, 128, 135, L"PlayerBAStun");
		avatar->CreatePartAni(EAvatarParts::Base, stun_texter, L"PlayerBAStunStagger", 0, 2, 0.1f);
		avatar->CreatePartAni(EAvatarParts::Base, stun_texter, L"PlayerBAStunDownStagger", 2, 4, 0.15f);
		avatar->CreatePartAni(EAvatarParts::Base, stun_texter, L"PlayerBAStunDown", 4, 7, 0.15f);

		avatar->CreatePartAni(EAvatarParts::Base, L"baseskin", mUser->base_avartar, L"PlayerBAStanding", 53, 54, 0.5f);

		//player state 에 따라 재생할 애니 정보 등록
		avatar->InsertStateAniInfo(EPlayerState::Idle, EAvatarParts::Base, L"PlayerBAIdle");
		avatar->InsertStateAniInfo(EPlayerState::Walk, EAvatarParts::Base, L"PlayerBAWalk");
		avatar->InsertStateAniInfo(EPlayerState::Run, EAvatarParts::Base, L"PlayerBARun");
		avatar->InsertStateAniInfo(EPlayerState::JumpRun, EAvatarParts::Base, L"PlayerBARun");
		avatar->InsertStateAniInfo(EPlayerState::NomalAtk, EAvatarParts::Base, L"PlayerBANomalAtk");
		avatar->InsertStateAniInfo(EPlayerState::Jump, EAvatarParts::Base, L"PlayerBAJump1");
		avatar->InsertStateAniInfo(EPlayerState::Jump, EAvatarParts::Base, L"PlayerBAJump2");
		avatar->InsertStateAniInfo(EPlayerState::Jump, EAvatarParts::Base, L"PlayerBAJump3");
		avatar->InsertStateAniInfo(EPlayerState::Stun, EAvatarParts::Base, L"PlayerBAStunStagger");
		avatar->InsertStateAniInfo(EPlayerState::Stun, EAvatarParts::Base, L"PlayerBAStunDownStagger");
		avatar->InsertStateAniInfo(EPlayerState::Stun, EAvatarParts::Base, L"PlayerBAStunDown");
		avatar->InsertStateAniInfo(EPlayerState::Standing, EAvatarParts::Base, L"PlayerBAStanding");
#pragma endregion
#pragma region weapon part
		avatar->CreatePartAni(EAvatarParts::Weapon, L"weapon", mUser->weapon_avatar1, L"PlayerWAIdle", 0, 10, 0.2f);
		avatar->CreatePartAni(EAvatarParts::Weapon, L"weapon", mUser->weapon_avatar1, L"PlayerWAWalkAndRun", 0, 10, 0.05f);
		avatar->CreatePartAni(EAvatarParts::Weapon, L"weapon", mUser->weapon_avatar1, L"PlayerWAJump", 11, 21, 0.1f);
		avatar->CreatePartAni(EAvatarParts::Weapon, L"weapon", mUser->weapon_avatar1, L"PlayerWAJumpRun", 178, 179, 0.1f);
		avatar->CreatePartAni(EAvatarParts::Weapon, L"weapon", mUser->weapon_avatar1, L"PlayerWADownStagger", 130, 131, 0.2f);
		avatar->CreatePartAni(EAvatarParts::Weapon, L"weapon", mUser->weapon_avatar1, L"PlayerWADown", 131, 135, 0.05f);


		avatar->InsertStateAniInfo(EPlayerState::Idle, EAvatarParts::Weapon, L"PlayerWAIdle");
		avatar->InsertStateAniInfo(EPlayerState::Walk, EAvatarParts::Weapon, L"PlayerWAWalkAndRun");
		avatar->InsertStateAniInfo(EPlayerState::Run, EAvatarParts::Weapon, L"PlayerWAWalkAndRun");
		avatar->InsertStateAniInfo(EPlayerState::Jump, EAvatarParts::Weapon, L"PlayerWAJump");
		avatar->InsertStateAniInfo(EPlayerState::JumpRun, EAvatarParts::Weapon, L"PlayerWAJumpRun");
		avatar->InsertStateAniInfo(EPlayerState::Stun, EAvatarParts::Weapon, L"PlayerWAIdle");
		avatar->InsertStateAniInfo(EPlayerState::Stun, EAvatarParts::Weapon, L"PlayerWADownStagger");
		avatar->InsertStateAniInfo(EPlayerState::Stun, EAvatarParts::Weapon, L"PlayerWADown");
		avatar->InsertStateAniInfo(EPlayerState::Standing, EAvatarParts::Weapon, L"PlayerWAIdle");
#pragma endregion


		avatar->SetCompleteEventAnimation(EPlayerState::Jump, 0, 1);

		/*avatar->EndEventAnimation(EPlayerState::Jump, 1, std::bind([this]()->void { mRigid.lock()->SetGround(true); }));*/
		avatar->SetStartEventAnimation(EPlayerState::Jump, 2, std::bind([this]()->void { mMoveScript.lock()->is_active = false; }));
		avatar->CompleteEventAnimation(EPlayerState::Jump, 2, std::bind([this]()->void { NextState(); }));
		avatar->CompleteEventAnimation(EPlayerState::Stun, 2, std::bind([this]()->void { DownEvent(); }));
		avatar->CompleteEventAnimation(EPlayerState::Standing, 0, std::bind([this]()->void {EnableKeyInput(); NextState(); }));
		mPlayerState = EPlayerState::Idle;
		//현재 idle 상태 애니 재생.
		avatar->PlayPartsMotion();

		std::shared_ptr<MoveScript> ms = mMoveScript.lock();
		ms->SetSpeed(0.8f);


		Time::RegisterEvent(L"PlayerFallCompEvent", &PlayerScript::FallCompleteEvent);
		Time::RegisterEvent(L"PlayerJumpDashCompEvent", &PlayerScript::JumpDashCompleteEvent);
		Time::RegisterEvent(L"PlayerStunCompEvent", &PlayerScript::StunCompleteEvent);
	}
	void PlayerScript::Update()
	{
		mTime += Time::DeltaTime();
	}
	void PlayerScript::LateUpdate()
	{
		std::shared_ptr<Rigidbody> rigid = mRigid.lock();
		std::shared_ptr<MoveScript> ms = mMoveScript.lock();
		std::shared_ptr<AvatarScript> as = mAvatar.lock();
		if (rigid->is_ground == true)
		{
			if (mPlayerState >= EPlayerState::Jump &&
				mPlayerState <= EPlayerState::JumpRun)
			{
				mPlayerState = EPlayerState::Idle;
				as->StartAni();
				as->PlayPartsMotion(EPlayerState::Jump, 2, false);
			}

			if (mPlayerState == EPlayerState::Stun &&
				mStunState == EStunState::Down)
			{
				mPlayerState = EPlayerState::None;
				as->PlayPartsMotion(EPlayerState::Stun, 2, false);
			}

			if (mPlayerState == EPlayerState::Standing)
			{
				//퀵스
				if (mStunState == EStunState::Down)
				{
					if (Input::GetKeyDown(EKeyCode::C))
					{
						mStunState = EStunState::None;
						as->PlayPartsMotion();
						std::vector<std::shared_ptr<Collider2D>> cols;
						cols.push_back(mTopCollider.lock());
						cols.push_back(mBottomCollider.lock());

						float radian = Deg2Rad(0.0f);
						for (int i = 0; i < cols.size(); i++)
						{
							cols[i]->SetRotation(radian);
							Vector2 center = cols[i]->center;
							center.y += 0.2f;
							cols[i]->center = center;
						}
						return;
					}
				}
			}
		}



	}
	void PlayerScript::Render()
	{
	}

	void PlayerScript::OnCollisionEnter(std::shared_ptr<Collider2D> other)
	{
		GameObject* other_owner = other->owner;
		std::shared_ptr<SkillScript> ss = other_owner->GetComponent<SkillScript>();
		if (ss == nullptr)
			return;
		std::shared_ptr<MoveScript> ms = mMoveScript.lock();
		bool flag = false;
		EPlayerState befor_state = mPlayerState;
		
		switch (ss->stun_type)
		{
		case EStunState::Stagger:
			mPlayerState = EPlayerState::Stun;
			StunStagger(ss->stun_type,0.5f);
			flag = true;
			break;
		case EStunState::Down:
			mPlayerState = EPlayerState::Stun;
			StunDown();
			flag = true;
			break;
		}
		if (flag == true)
		{
			DisableKeyInput();
			ms->Stop();
			ms->ResetSpeed();
			mStunState = ss->stun_type;
		}
		else
		{
			mPlayerState = befor_state;
		}
	}

	void PlayerScript::OnCollisionStay(std::shared_ptr<Collider2D> other)
	{
		GameObject* other_owner = other->owner;
		std::shared_ptr<SkillScript> ss = other_owner->GetComponent<SkillScript>();
		if (ss == nullptr)
			return;
		std::shared_ptr<MoveScript> ms = mMoveScript.lock();
		bool flag = false;
		EPlayerState befor_state = mPlayerState;
		if (mPlayerState != EPlayerState::Stun)
		{
			mPlayerState = EPlayerState::Stun;
			switch (ss->stun_type)
			{
			case EStunState::HardStagger:
				if (mStunState == ss->stun_type)
					break;
				StunStagger(ss->stun_type,0.25f);
				flag = true;
				break;
			}

			if (flag == true)
			{
				DisableKeyInput();
				ms->Stop();
				ms->ResetSpeed();
				mStunState = ss->stun_type;
			}
			else
			{
				mPlayerState = befor_state;
			}
		}
		
	}

	void PlayerScript::OnCollisionExit(std::shared_ptr<Collider2D> other)
	{
		GameObject* other_owner = other->owner;
		std::shared_ptr<SkillScript> ss = other_owner->GetComponent<SkillScript>();
		if (ss == nullptr)
			return;
		std::shared_ptr<MoveScript> ms = mMoveScript.lock();
		bool flag = false;
		
		switch ((UINT)mStunState)
		{
		case (UINT)EStunState::Stagger|(UINT)EStunState::HardStagger:
			/*ps->EnableKeyInput();
			as->StartAni();*/
			break;
		}
	}

	void PlayerScript::LeftBtnDown()
	{
		std::shared_ptr<MoveScript> ms = mMoveScript.lock();
		std::shared_ptr<AvatarScript> as = mAvatar.lock();
		std::shared_ptr<Rigidbody> rigid = mRigid.lock();
		mRightTime = 0.0;

		if (mIsActiveInput == false)
			return;
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
				rigid->is_active = false;
				ms->AddSpeed(3.0f);
				mPlayerState = EPlayerState::JumpRun;
				as->PlayPartsMotion();
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

		if (mIsActiveInput == false)
			return;
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
				rigid->is_active = false;
				ms->AddSpeed(3.0f);
				mPlayerState = EPlayerState::JumpRun;
				as->PlayPartsMotion();
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
		if (mIsActiveInput == false)
			return;
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
		if (mIsActiveInput == false)
			return;
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

		if (mIsActiveInput == false)
			return;

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
		if (mIsActiveInput == false)
			return;

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
		if (mIsActiveInput == false)
			return;

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

		if (mIsActiveInput == false)
			return;

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
		if (mPlayerState == EPlayerState::Jump || mPlayerState == EPlayerState::JumpRun)
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

	void PlayerScript::StunStagger(EStunState stun, float endtime)
	{
		std::shared_ptr<Collider2D> collider = mTopCollider.lock();
		double befor_time = collider->time;
		double cur_time = CollisionManager::GetColliderTimer();
		double condition = 5.0f;
		std::shared_ptr<AvatarScript> as = mAvatar.lock();

		as->StopAni();
		as->PlayPartsSprite(mPlayerState, (UINT)EStunState::Stagger - 1);
		if (cur_time - befor_time <= condition)
		{
			as->AddSpriteIndex();
		}

		Time::CallBackTimerInfo info = {};
		info.endTime = endtime;
		std::wstring key = L"PlayerStunCompEvent";
		size_t str_length = key.size();
		std::wcsncpy(info.key, key.c_str(), str_length);
		Time::RequestEvent(info, owner->GetSharedPtr());
	}

	void PlayerScript::StunDown()
	{
		std::shared_ptr<AvatarScript> as = mAvatar.lock();
		std::shared_ptr<Rigidbody> rigid = owner->GetComponent<Rigidbody>();
		std::vector<std::shared_ptr<Collider2D>> cols;
		cols.push_back(mTopCollider.lock());
		cols.push_back(mBottomCollider.lock());

		float radian = Deg2Rad(90.0f);
		for (int i = 0; i < cols.size(); i++)
		{
			cols[i]->SetRotation(radian);
			Vector2 center = cols[i]->center;
			center.y -= 0.2f;
			cols[i]->center = center;
		}
		as->PlayPartsMotion(EPlayerState::Stun, 1, false);


		if (mCurDir > 0)
		{
			rigid->AddForce(Vector2(-30.0f, 60 * 980.0f));
		}
		else if (mCurDir < 0)
		{
			rigid->AddForce(Vector2(30.0f, 60 * 980.0f));
		}

		rigid->disableGround();

	}

	void PlayerScript::NextState()
	{
		std::shared_ptr<AvatarScript> as = mAvatar.lock();
		std::shared_ptr<Rigidbody> rigid = mRigid.lock();
		std::shared_ptr<MoveScript> ms = mMoveScript.lock();
		if (Input::GetKey(EKeyCode::SPACE))
		{
			//mPlayerState = EPlayerState::Idle;
		}
		else
		{
			if (Input::GetKey(EKeyCode::LEFT) || Input::GetKeyDown(EKeyCode::LEFT))
			{
				mPlayerState = EPlayerState::Walk;
				LeftBtnDown();
			}
			else if (Input::GetKey(EKeyCode::RIGHT) || Input::GetKeyDown(EKeyCode::RIGHT))
			{
				mPlayerState = EPlayerState::Walk;
				RightBtnDown();
			}
			else if (Input::GetKey(EKeyCode::UP) || Input::GetKeyDown(EKeyCode::UP))
			{
				mPlayerState = EPlayerState::Walk;
				UpBtnDown();
			}
			else if (Input::GetKey(EKeyCode::DOWN) || Input::GetKeyDown(EKeyCode::DOWN))
			{
				mPlayerState = EPlayerState::Walk;
				DownBtnDown();
			}
			else if (Input::GetAniKeyDown() == false)
			{
				mPlayerState = EPlayerState::Idle;
			}
		}


		if (ms->is_active == false)
		{
			ms->is_active = true;
		}
		as->PlayPartsMotion();
	}

	void PlayerScript::DownEvent()
	{
		mPlayerState = EPlayerState::Standing;
		Time::CallBackTimerInfo info = {};
		info.endTime = 1.0;
		std::wstring key = L"PlayerStunCompEvent";
		size_t str_length = key.size();
		std::wcsncpy(info.key, key.c_str(), str_length);
		Time::RequestEvent(info, owner->GetSharedPtr());
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

	void PlayerScript::StunCompleteEvent(std::weak_ptr<void> ptr)
	{
		std::shared_ptr<GameObject> obj = std::reinterpret_pointer_cast<GameObject>(ptr.lock());
		std::shared_ptr<PlayerScript> ps = obj->GetComponent<PlayerScript>();
		std::shared_ptr<MoveScript> ms = ps->mMoveScript.lock();
		std::shared_ptr<AvatarScript> as = ps->mAvatar.lock();

		if (ps->mStunState == EStunState::None)
			return;
		ps->EnableKeyInput();
		as->StartAni();

		switch (ps->mStunState)
		{
		case EStunState::Stagger:
		case EStunState::HardStagger:
			ps->NextState();
			break;

		case EStunState::Down:
			//스탠딩 모션 후 일어나기.
			ps->mPlayerState = EPlayerState::Standing;
			as->PlayPartsMotion();
			std::vector<std::shared_ptr<Collider2D>> cols;
			cols.push_back(ps->mTopCollider.lock());
			cols.push_back(ps->mBottomCollider.lock());

			float radian = Deg2Rad(0.0f);
			for (int i = 0; i < cols.size(); i++)
			{
				cols[i]->SetRotation(radian);
				Vector2 center = cols[i]->center;
				center.y += 0.2f;
				cols[i]->center = center;
			}
			break;
		}
		ps->mStunState = EStunState::None;
	}

}