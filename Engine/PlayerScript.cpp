#include "PlayerScript.h"
#include "GameObject.h"
#include "Input.h"
#include "RokaTime.h"
#include "Resources.h"
#include "NPK.h"
#include "CollisionManager.h"
#include "SkillManager.h"
#include "InputManager.h"

#include "ISkill.h"

#include "Transform.h"
#include "Rigidbody.h"
#include "Animator.h"
#include "MeshRenderer.h"
#include "Collider2D.h"

#include "MoveScript.h"
#include "AvatarScript.h"
#include "PartScript.h"

#include "User.h"
#include "GaugeManager.h"
#include "ItemManager.h"


using namespace roka::info;
namespace roka
{
	manager::InputManager* M_Input = manager::InputManager::GetInstance();
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
		mHP = 100;
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
		mHP = 100;
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
		mHP = 100;
	}
	void PlayerScript::Initialize()
	{
		Script::Initialize();
		mHP = 100;
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

		mPlayerState = EPlayerState::Idle;

		std::shared_ptr<MoveScript> ms = mMoveScript.lock();
		ms->SetSpeed(0.8f);

		std::shared_ptr<Rigidbody> rigid = mRigid.lock();
		rigid->FallEvent(std::bind(&PlayerScript::NormalFallEvent, this));
		Time::RegisterEvent(L"PlayerFallCompEvent", &PlayerScript::FallCompleteEvent);
		Time::RegisterEvent(L"PlayerJumpDashCompEvent", &PlayerScript::JumpDashCompleteEvent);
		Time::RegisterEvent(L"PlayerStunCompEvent", &PlayerScript::StunCompleteEvent);

		//mSkillList.resize((UINT)EPlayerSkillType::End);

	}
	void PlayerScript::LateInitialize()
	{
		EquipPart(EAvatarParts::Base);
		EquipPart(EAvatarParts::Weapon);

		std::shared_ptr<AvatarScript> avatar = mAvatar.lock();
		avatar->PlayPartsMotion();
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
						/*cols[i]->SetRotation(radian);
						Vector2 center = cols[i]->center;
						center.y += 0.2f;
						cols[i]->center = center;*/
						cols[i]->is_active = true;
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

	void PlayerScript::RegisterKeyEvents()
	{
		M_Input->RegisterKeyEvent(mUser->left_key, EKeyState::Down, std::bind(&PlayerScript::LeftBtnDown, this));
		M_Input->RegisterKeyEvent(mUser->left_key, EKeyState::Up, std::bind(&PlayerScript::LeftBtnUp, this));
		M_Input->RegisterKeyEvent(mUser->right_key, EKeyState::Down, std::bind(&PlayerScript::RightBtnDown, this));
		M_Input->RegisterKeyEvent(mUser->right_key, EKeyState::Up, std::bind(&PlayerScript::RightBtnUp, this));
		M_Input->RegisterKeyEvent(mUser->down_key, EKeyState::Down, std::bind(&PlayerScript::DownBtnDown, this));
		M_Input->RegisterKeyEvent(mUser->down_key, EKeyState::Up, std::bind(&PlayerScript::DownBtnUp, this));
		M_Input->RegisterKeyEvent(mUser->up_key, EKeyState::Down, std::bind(&PlayerScript::UpBtnDown, this));
		M_Input->RegisterKeyEvent(mUser->up_key, EKeyState::Up, std::bind(&PlayerScript::UpBtnUp, this));
		M_Input->RegisterKeyEvent(mUser->normalAtk_key, EKeyState::Down, std::bind(&PlayerScript::NomalAtkBtnDown, this));
		M_Input->RegisterKeyEvent(mUser->jump_key, EKeyState::Down, std::bind(&PlayerScript::JumpBtnDown, this));
		M_Input->RegisterKeyEvent(mUser->skill01_key, EKeyState::Down, std::bind(&PlayerScript::Skill, this, mUser->skill01_key));
		M_Input->RegisterKeyEvent(mUser->inven_key, EKeyState::Down, std::bind(&PlayerScript::InvenOnOff, this));
		M_Input->RegisterKeyEvent(mUser->pickup_key, EKeyState::Down, std::bind(&PlayerScript::PickUpItem, this));
	}

	void PlayerScript::SettingInventory()
	{
		if (mInven != nullptr)
		{
			manager::ItemManager::GetInstance()->SetInventoryItem(mInven, owner->GetSharedPtr());
		}
	}

	void PlayerScript::BeAttacked(float damage, EStunState stun)
	{
		std::shared_ptr<MoveScript> ms = mMoveScript.lock();
		bool flag = false;
		EPlayerState befor_state = mPlayerState;
		GaugeManager::GetInstance()->UseGauge(EGaugeType::PlayerHP,-damage, 100);
		mHP -= damage;
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

	void PlayerScript::Recovery(float recovery)
	{
		GaugeManager::GetInstance()->UseGauge(EGaugeType::PlayerHP, recovery, 100);
		mHP += recovery;
		if (mHP >= 100)
			mHP = 100;
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
		case EAvatarParts::Hair:
			if (mUser->base_avartar.size() == 0)
				return;
			//avatar->EquipPart(type, mUser->);
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
	void PlayerScript::EquipPart(EAvatarParts type, std::vector<AvatarSubPartInfo> info)
	{
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
					//rigid->is_active = false;
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
				//rigid->is_active = false;
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
					//rigid->is_active = false;
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
				//rigid->is_active = false;
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
		std::vector<std::shared_ptr<Collider2D>> cols = owner->GetChilds<Collider2D>();
		for (auto col : cols)
		{
			bool flag = CollisionManager::CollisionCheck(col->owner->GetSharedPtr(), ELayerType::Item);
			if (flag == true)
				return;
		}
			
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

	void PlayerScript::InvenOnOff()
	{
		if (mInven->active == GameObject::EState::Paused)
		{
			mInven->active = GameObject::EState::Active;
		}
		else if(mInven->active == GameObject::EState::Active)
		{
			mInven->active = GameObject::EState::Paused;
		}
	}

	void PlayerScript::PickUpItem()
	{
		int a = 0;
	}

	void PlayerScript::Skill(UINT input)
	{
		if (mPlayerState >= EPlayerState::Skill)
			return;
		std::wstring skillName = mUser->GetKeySkillName(input);
		ISkill* skill = manager::SkillManager::GetInstance()->Find(ECharacterClassType::Mage, skillName);
		skill->Execute(owner->GetSharedPtr());
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
		std::shared_ptr<Transform> tf = owner->GetComponent<Transform>();
		std::shared_ptr<Rigidbody> rigid = owner->GetComponent<Rigidbody>();
		std::vector<std::shared_ptr<Collider2D>> cols;
		cols.push_back(mTopCollider.lock());
		cols.push_back(mBottomCollider.lock());

		float radian = Deg2Rad(90.0f);
		for (int i = 0; i < cols.size(); i++)
		{
			/*cols[i]->SetRotation(radian);
			Vector2 center = cols[i]->center;
			center.y -= 0.2f;
			cols[i]->center = center;*/
			cols[i]->is_active = false;
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
		rigid->SetLandingPoint(Vector2(tf->position.x, tf->position.y));
	}

	void PlayerScript::NextState()
	{
		std::shared_ptr<AvatarScript> as = mAvatar.lock();
		std::shared_ptr<Rigidbody> rigid = mRigid.lock();
		std::shared_ptr<MoveScript> ms = mMoveScript.lock();
		EnableKeyInput();
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
				/*cols[i]->SetRotation(radian);
				Vector2 center = cols[i]->center;
				center.y += 0.2f;
				cols[i]->center = center;*/
				cols[i]->is_active = true;
			}
			break;
		}
		ps->mPlayerState = EPlayerState::None;
		ps->mStunState = EStunState::None;
	}


	void PlayerScript::PlayPartMotion()
	{
		std::shared_ptr<AvatarScript> avatar = mAvatar.lock();
		avatar->PlayPartsMotion();
	}

	void PlayerScript::SkillPartMotion(std::wstring key)
	{
		std::shared_ptr<AvatarScript> avatar = mAvatar.lock();
		avatar->SkillPartsMotion(key);
	}

}