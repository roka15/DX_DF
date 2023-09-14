#include "PlayerScript.h"
#include "GameObject.h"
#include "Input.h"
#include "RokaTime.h"
#include "Resources.h"
#include "NPK.h"
#include "CollisionManager.h"
#include "SkillManager.h"

#include "ISkill.h"

#include "Transform.h"
#include "Rigidbody.h"
#include "Animator.h"
#include "MeshRenderer.h"
#include "Collider2D.h"

#include "MoveScript.h"
#include "AvatarScript.h"
#include "SkillScript.h"
#include "PlayerNormalAttackScript.h"
#include "PartScript.h"

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
		mCurDir = 1.0f;
	}
	PlayerScript::PlayerScript(const PlayerScript& ref) :Script(ref)
	{
		mUser = std::make_unique<User>(*(ref.mUser.get()));
		mLeftTime = 0.0;
		mRightTime = 0.0;
		mTime = 0.0;
		mDiff = 0.1;
		mCurDir = 1.0f;
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
		mCurDir = 1.0f;
		mStunState = EStunState::None;
	}
	void PlayerScript::Initialize()
	{
		Script::Initialize();
		owner->layer_type = ELayerType::Player;
		mTransform = owner->GetComponent<Transform>();
		mMoveScript = owner->GetComponent<MoveScript>();
		mRigid = owner->GetComponent<Rigidbody>();
		mAvatar = owner->GetChild<AvatarScript>()->GetComponent<AvatarScript>();
		mUser->Initialize();
		std::vector<std::shared_ptr<Collider2D>> vec
			= owner->GetChilds<Collider2D>();
		mTopCollider = vec[0];
		mBottomCollider = vec[1];

		//해당 part의 애니 생성
#pragma region base part
		//avatar->CreatePartAni(EAvatarParts::Base, L"baseskin", mUser->base_avartar, L"PlayerBAIdle", 10, 14, 0.3f);
		//avatar->CreatePartAni(EAvatarParts::Base, L"baseskin", mUser->base_avartar, L"PlayerBAWalk", 0, 10, 0.05f);
		//avatar->CreatePartAni(EAvatarParts::Base, L"baseskin", mUser->base_avartar, L"PlayerBARun", 18, 21, 0.05f);
		//avatar->CreatePartAni(EAvatarParts::Base, L"baseskin", mUser->base_avartar, L"PlayerBANomalAtk", 109, 127, 0.05f);

		//std::shared_ptr<NPK> baseskin_npk = Resources::Find<NPK>(L"baseskin");
		//std::shared_ptr<Texture> jump_texture = baseskin_npk->CreateAtlas(mUser->base_avartar, 76, 85, L"PlayerBAJump");

		//avatar->CreatePartAni(EAvatarParts::Base, jump_texture, L"PlayerBAJump1", 0, 4, 0.185f);
		//avatar->CreatePartAni(EAvatarParts::Base, jump_texture, L"PlayerBAJump2", 4, 7, 0.20755f);
		//avatar->CreatePartAni(EAvatarParts::Base, jump_texture, L"PlayerBAJump3", 7, 9, 0.04f);

		//std::shared_ptr<Texture> stun_texter = baseskin_npk->CreateAtlas(mUser->base_avartar, 128, 135, L"PlayerBAStun");
		//avatar->CreatePartAni(EAvatarParts::Base, stun_texter, L"PlayerBAStunStagger", 0, 2, 0.1f);
		//avatar->CreatePartAni(EAvatarParts::Base, stun_texter, L"PlayerBAStunDownStagger", 2, 4, 0.15f);
		//avatar->CreatePartAni(EAvatarParts::Base, stun_texter, L"PlayerBAStunDown", 4, 7, 0.15f);

		//avatar->CreatePartAni(EAvatarParts::Base, L"baseskin", mUser->base_avartar, L"PlayerBAStanding", 53, 54, 0.5f);

		////player state 에 따라 재생할 애니 정보 등록
		//avatar->InsertStateAniInfo(EPlayerState::Idle, EAvatarParts::Base, L"PlayerBAIdle");
		//avatar->InsertStateAniInfo(EPlayerState::Walk, EAvatarParts::Base, L"PlayerBAWalk");
		//avatar->InsertStateAniInfo(EPlayerState::Run, EAvatarParts::Base, L"PlayerBARun");
		//avatar->InsertStateAniInfo(EPlayerState::JumpRun, EAvatarParts::Base, L"PlayerBARun");
		//avatar->InsertStateAniInfo(EPlayerState::NomalAtk, EAvatarParts::Base, L"PlayerBANomalAtk");
		//avatar->InsertStateAniInfo(EPlayerState::Jump, EAvatarParts::Base, L"PlayerBAJump1");
		//avatar->InsertStateAniInfo(EPlayerState::Jump, EAvatarParts::Base, L"PlayerBAJump2");
		//avatar->InsertStateAniInfo(EPlayerState::Jump, EAvatarParts::Base, L"PlayerBAJump3");
		//avatar->InsertStateAniInfo(EPlayerState::Stun, EAvatarParts::Base, L"PlayerBAStunStagger");
		//avatar->InsertStateAniInfo(EPlayerState::Stun, EAvatarParts::Base, L"PlayerBAStunDownStagger");
		//avatar->InsertStateAniInfo(EPlayerState::Stun, EAvatarParts::Base, L"PlayerBAStunDown");
		//avatar->InsertStateAniInfo(EPlayerState::Standing, EAvatarParts::Base, L"PlayerBAStanding");
#pragma endregion
#pragma region weapon part
		/*avatar->CreatePartAni(EAvatarParts::Weapon, L"weapon", mUser->weapon_avatar1, L"PlayerWAIdle", 0, 10, 0.2f);
		avatar->CreatePartAni(EAvatarParts::Weapon, L"weapon", mUser->weapon_avatar1, L"PlayerWAWalkAndRun", 0, 10, 0.05f);
		avatar->CreatePartAni(EAvatarParts::Weapon, L"weapon", mUser->weapon_avatar1, L"PlayerWAJump", 11, 21, 0.1f);
		avatar->CreatePartAni(EAvatarParts::Weapon, L"weapon", mUser->weapon_avatar1, L"PlayerWAJumpRun", 178, 179, 0.1f);
		avatar->CreatePartAni(EAvatarParts::Weapon, L"weapon", mUser->weapon_avatar1, L"PlayerWADownStagger", 130, 131, 0.2f);
		avatar->CreatePartAni(EAvatarParts::Weapon, L"weapon", mUser->weapon_avatar1, L"PlayerWADown", 131, 135, 0.05f);
		avatar->CreatePartAni(EAvatarParts::Weapon, L"weapon", mUser->weapon_avatar1, L"PlayerWANormalAtk", 109, 127, 0.05f);


		avatar->InsertStateAniInfo(EPlayerState::Idle, EAvatarParts::Weapon, L"PlayerWAIdle");
		avatar->InsertStateAniInfo(EPlayerState::Walk, EAvatarParts::Weapon, L"PlayerWAWalkAndRun");
		avatar->InsertStateAniInfo(EPlayerState::Run, EAvatarParts::Weapon, L"PlayerWAWalkAndRun");
		avatar->InsertStateAniInfo(EPlayerState::Jump, EAvatarParts::Weapon, L"PlayerWAJump");
		avatar->InsertStateAniInfo(EPlayerState::JumpRun, EAvatarParts::Weapon, L"PlayerWAJumpRun");
		avatar->InsertStateAniInfo(EPlayerState::Stun, EAvatarParts::Weapon, L"PlayerWAIdle");
		avatar->InsertStateAniInfo(EPlayerState::Stun, EAvatarParts::Weapon, L"PlayerWADownStagger");
		avatar->InsertStateAniInfo(EPlayerState::Stun, EAvatarParts::Weapon, L"PlayerWADown");
		avatar->InsertStateAniInfo(EPlayerState::Standing, EAvatarParts::Weapon, L"PlayerWAIdle");*/
#pragma endregion

		//avatar->SetCompleteEventAnimation(EPlayerState::Jump, 0, 1);

		///*avatar->EndEventAnimation(EPlayerState::Jump, 1, std::bind([this]()->void { mRigid.lock()->SetGround(true); }));*/
		//avatar->SetStartEventAnimation(EPlayerState::Jump, 2, std::bind([this]()->void { mMoveScript.lock()->is_active = false; }));
		//avatar->CompleteEventAnimation(EPlayerState::Jump, 2, std::bind([this]()->void { NextState(); }));
		//avatar->CompleteEventAnimation(EPlayerState::Stun, 2, std::bind([this]()->void { DownEvent(); }));
		//avatar->CompleteEventAnimation(EPlayerState::Standing, 0, std::bind([this]()->void {EnableKeyInput(); NextState(); }));
		mPlayerState = EPlayerState::Idle;

		std::shared_ptr<MoveScript> ms = mMoveScript.lock();
		ms->SetSpeed(0.8f);

		std::shared_ptr<Rigidbody> rigid = mRigid.lock();
		rigid->FallEvent(std::bind(&PlayerScript::NormalFallEvent, this));
		Time::RegisterEvent(L"PlayerFallCompEvent", &PlayerScript::FallCompleteEvent);
		Time::RegisterEvent(L"PlayerJumpDashCompEvent", &PlayerScript::JumpDashCompleteEvent);
		Time::RegisterEvent(L"PlayerStunCompEvent", &PlayerScript::StunCompleteEvent);

		//mSkillList.resize((UINT)EPlayerSkillType::End);
		EquipPart(EAvatarParts::Base);
		EquipPart(EAvatarParts::Weapon);

		std::shared_ptr<AvatarScript> avatar = mAvatar.lock();
		avatar->PlayPartsMotion();
	}
	void PlayerScript::LateInitialize()
	{
		/*EquipPart(EAvatarParts::Base);
		EquipPart(EAvatarParts::Weapon);

		std::shared_ptr<AvatarScript> avatar = mAvatar.lock();
		avatar->PlayPartsMotion();*/
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
			if (mPlayerState == EPlayerState::FallDown)
			{
				mPlayerState = EPlayerState::Landing;
				as->StartAni();
				as->PlayPartsMotion();
				rigid->enableGround();
			}

			if (mPlayerState == EPlayerState::Down)
			{
				as->StartAni();
				EnableKeyInput();
			}

			if (mPlayerState == EPlayerState::Down)
			{
				//퀵스
				if (Input::GetKeyDown(EKeyCode::C))
				{
					mPlayerState = EPlayerState::Standing;
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
	void PlayerScript::Render()
	{
	}

	void PlayerScript::OnCollisionEnter(std::shared_ptr<Collider2D> other)
	{
	}

	void PlayerScript::OnCollisionStay(std::shared_ptr<Collider2D> other)
	{
	}

	void PlayerScript::OnCollisionExit(std::shared_ptr<Collider2D> other)
	{
	}

	void PlayerScript::BeAttacked(float damage, EStunState stun)
	{
		std::shared_ptr<MoveScript> ms = mMoveScript.lock();
		bool flag = false;
		EPlayerState befor_state = mPlayerState;

		switch (stun)
		{
		case EStunState::HardStagger:
			if (mStunState == stun)
				break;
		case EStunState::Stagger:
			mPlayerState = EPlayerState::Stagger;
			StunStagger(stun, 0.25f);
			flag = true;
			break;
		case EStunState::Down:
			mPlayerState = EPlayerState::Down;
			StunDown();
			flag = true;
			break;
		}


		if (flag == true)
		{
			DisableKeyInput();
			ms->Stop();
			ms->ResetSpeed();
			mStunState = stun;
		}
		else
		{
			mPlayerState = befor_state;
		}
	}

	void PlayerScript::EquipPart(EAvatarParts type)
	{
		std::shared_ptr<AvatarScript> avatar = mAvatar.lock();
		switch (type)
		{
		case EAvatarParts::Base:
			if (mUser->base_avartar.size() == 0)
				return;
			avatar->EquipPart(type, mUser->base_avartar);
			break;
		case EAvatarParts::Weapon:
			if (mUser->weapon_avatar1.size() == 0)
				return;
			avatar->EquipPart(type, mUser->weapon_avatar1);
			break;
		}
	}

	void PlayerScript::EquipPart(EAvatarParts type, std::wstring name)
	{
		switch (type)
		{
		case EAvatarParts::Base:
			if (mUser->base_avartar == name)
				return;
			mUser->base_avartar = name;
			break;
		case EAvatarParts::Weapon:
			if (mUser->weapon_avatar1 == name)
				return;
			mUser->weapon_avatar1 = name;
			break;
		}
		std::shared_ptr<AvatarScript> avatar = mAvatar.lock();
		avatar->EquipPart(type, name);
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
					rigid->is_active = false;
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
				ms->is_active = true;
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
					rigid->is_active = false;
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
				ms->is_active = true;
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

		if (mPlayerState == EPlayerState::JumpRun && mCurDir == -1.0f
			&& rigid->is_ground == false)
		{
			mPlayerState = EPlayerState::FallDown;
			if (rigid->is_active == false)
				rigid->is_active = true;
			ms->SetDirX(0.0f);
			ms->ResetSpeed();
			as->PlayPartsMotion();
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
		if (mPlayerState == EPlayerState::JumpRun && mCurDir == 1.0f &&
			rigid->is_ground == false)
		{
			mPlayerState = EPlayerState::FallDown;
			if (rigid->is_active == false)
				rigid->is_active = true;
			ms->SetDirX(0.0f);
			ms->ResetSpeed();
			as->PlayPartsMotion();
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
		if (mPlayerState == EPlayerState::NomalAtk)
			return;
		ISkill* skill = manager::SkillManager::GetInstance()->Find(ECharacterClassType::Mage, L"NormalAtk");
		skill->Execute(owner->GetSharedPtr());
	}
	void PlayerScript::JumpBtnDown()
	{
		std::shared_ptr<AvatarScript> as = mAvatar.lock();
		std::shared_ptr<Rigidbody> rigid = mRigid.lock();
		std::shared_ptr<MoveScript> ms = mMoveScript.lock();
		if (rigid->is_active == false)
			rigid->is_active = true;
		if (mPlayerState == EPlayerState::Jump ||
			(mPlayerState == EPlayerState::Run && rigid->is_ground == false) ||
			mPlayerState == EPlayerState::FallDown)
		{
			mPlayerState = EPlayerState::FallDown;
			as->PlayPartsMotion();
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
		else if (mPlayerState != EPlayerState::FallDown)
		{
			mPlayerState = EPlayerState::Jump;
			std::shared_ptr<Transform> tf = owner->GetComponent<Transform>();
			std::shared_ptr<Rigidbody> rigid = owner->GetComponent<Rigidbody>();
			std::shared_ptr<MoveScript> ms = mMoveScript.lock();

			rigid->SetVelocity(Vector2(0.0f, 1400.0f));
			rigid->EnalbeJump();
			rigid->disableGround();
			rigid->SetLandingPoint(Vector2(tf->position.x, tf->position.y));
			as->PlayPartsMotion();
			ms->ResetSpeed();
		}
	}

	void PlayerScript::NormalFallEvent()
	{
		std::shared_ptr<Rigidbody> rigid = mRigid.lock();
		if (rigid->is_ground == true)
			return;
		std::shared_ptr<AvatarScript> as = mAvatar.lock();
		mPlayerState = EPlayerState::FallDown;
		as->PlayPartsMotion();
	}

	void PlayerScript::StunStagger(EStunState stun, float endtime)
	{
		std::shared_ptr<Collider2D> collider = mTopCollider.lock();
		double befor_time = collider->time;
		double cur_time = CollisionManager::GetColliderTimer();
		double condition = 5.0f;
		std::shared_ptr<AvatarScript> as = mAvatar.lock();
		
		if (as->IsAniStop() == false)
		{
			as->StopAni();
			as->PlayPartsMotion();
		}
		
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
		as->PlayPartsMotion();


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
			if (mPlayerState == EPlayerState::Landing)
				mPlayerState = EPlayerState::Idle;
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
		Time::CallBackTimerInfo info = {};
		info.endTime = 2.0;
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
			ps->mPlayerState = EPlayerState::FallDown;
			as->PlayPartsMotion();
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

		switch (ps->mPlayerState)
		{
		case EPlayerState::Stagger:
			ps->NextState();
			break;

		case EPlayerState::Down:
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
		ps->mPlayerState = EPlayerState::None;
		ps->mStunState = EStunState::None;
	}

	void PlayerScript::SkillNormalAtk()
	{
	}

	void PlayerScript::PlayPartMotion()
	{
		std::shared_ptr<AvatarScript> avatar = mAvatar.lock();
		avatar->PlayPartsMotion();
	}

}