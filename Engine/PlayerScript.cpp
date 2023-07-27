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
		mMeshRenderer = owner->AddComponent<MeshRenderer>();
		mMoveScript = owner->AddComponent<MoveScript>();
		mAvatar = owner->AddComponent<AvatarScript>();

		mUser->Initialize();


		std::shared_ptr<MeshRenderer> mesh = mMeshRenderer.lock();
		mesh->mesh = Resources::Find<Mesh>(L"RectMesh");
		mesh->material = Resources::Find<Material>(L"DefaultAniMaterial");


		std::shared_ptr<AvatarScript> avatar = mAvatar.lock();
		//해당 part의 애니 생성
		//skill ani의 경우 start event = DisableKeyInput 함수 , end event = EnableKeyInput 함수 연결
		//* 연결 함수 미구현 *
		avatar->CreatePartAni(EAvatarParts::Base, L"baseskin", mUser->base_avartar, L"PlayerBAIdle", 10, 14, 0.3f);
		avatar->CreatePartAni(EAvatarParts::Base, L"baseskin", mUser->base_avartar, L"PlayerBAWalk", 0, 10, 0.05f);

		//player state 에 따라 재생할 애니 정보 등록
		avatar->InsertStateAniInfo(EPlayerState::Idle, EAvatarParts::Base, L"PlayerBAIdle");
		avatar->InsertStateAniInfo(EPlayerState::Walk, EAvatarParts::Base, L"PlayerBAWalk");

		//현재 idle 상태 애니 재생.
		avatar->PlayPartsMotion();


		std::shared_ptr<MoveScript> ms = mMoveScript.lock();
		ms->SetSpeed(0.8f);
		ms->SetKeys(mUser->GetRightKey(), mUser->GetLeftKey(), mUser->GetUpKey(), mUser->GetDownKey());
	}
	void PlayerScript::Update()
	{
		Move();
	}
	void PlayerScript::LateUpdate()
	{
	}
	void PlayerScript::Render()
	{
	}
	void PlayerScript::Move()
	{
		if (mIsActiveInput == false)
			return;
		std::shared_ptr<MoveScript> ms = mMoveScript.lock();
		std::shared_ptr<MeshRenderer> mr = mMeshRenderer.lock();
		UINT rightkey = mUser->GetRightKey();
		UINT leftkey = mUser->GetLeftKey();
		UINT upkey = mUser->GetUpKey();
		UINT downkey = mUser->GetDownKey();

		int active_vertical = -1;
		int active_horizontal = -1;

		bool keydown = false;
		if (Input::GetKeyDown((EKeyCode)rightkey))
		{
			ms->VerticalMove(rightkey);
			active_vertical = rightkey;
			keydown = true;
		}
		if (Input::GetKeyDown((EKeyCode)leftkey))
		{
			ms->VerticalMove(leftkey);
			active_vertical = leftkey;
			keydown = true;
		}
		if (Input::GetKeyDown((EKeyCode)upkey))
		{
			ms->HorizontalMove(upkey);
			active_horizontal = upkey;
			keydown = true;
		}
		if (Input::GetKeyDown((EKeyCode)downkey))
		{
			ms->HorizontalMove(downkey);
			active_horizontal = downkey;
			keydown = true;
		}

		bool keyup_flag = false;
		if (Input::GetKeyUp((EKeyCode)rightkey))
		{
			ms->VerticalStop(rightkey);
			keyup_flag = true;
		}
		if (Input::GetKeyUp((EKeyCode)leftkey))
		{
			ms->VerticalStop(leftkey);
			keyup_flag = true;
		}
		if (Input::GetKeyUp((EKeyCode)upkey))
		{
			ms->HorizontalStop(upkey);
			keyup_flag = true;
		}
		if (Input::GetKeyUp((EKeyCode)downkey))
		{
			ms->HorizontalStop(downkey);
			keyup_flag = true;
		}
		std::shared_ptr<AvatarScript> avatar = mAvatar.lock();
		if (keydown == true)
		{
			if (active_vertical == rightkey || active_vertical == leftkey
				|| active_horizontal == upkey || active_horizontal == downkey)
			{
				mPlayerState = EPlayerState::Walk;
				if (active_vertical == rightkey)
				{
					SettingRightMaterial(mr);
				}
				if (active_vertical == leftkey)
				{
					SettingLeftMaterial(mr);
				}
			}
			avatar->update_flag = true;
		}
		else
		{
			if (active_vertical == -1 && active_horizontal == -1)
			{
				if (keyup_flag == true)
				{
					if (Input::GetKey((EKeyCode)rightkey) == false && Input::GetKey((EKeyCode)leftkey) == false
						&& Input::GetKey((EKeyCode)upkey) == false && Input::GetKey((EKeyCode)downkey) == false)
					{
						//아무입력 X
						mPlayerState = EPlayerState::Idle;
						avatar->update_flag = true;
					}
					else if (Input::GetKey((EKeyCode)rightkey))
					{
						SettingRightMaterial(mr);
						ms->VerticalMove(rightkey);
					}
					else if (Input::GetKey((EKeyCode)leftkey))
					{
						SettingLeftMaterial(mr);
						ms->VerticalMove(leftkey);
					}
				}
			}
		}
	}
	void PlayerScript::SettingRightMaterial(std::shared_ptr<MeshRenderer> mr)
	{
		mr->material = Resources::Find<Material>(L"DefaultAniMaterial");
	}
	void PlayerScript::SettingLeftMaterial(std::shared_ptr<MeshRenderer> mr)
	{
		mr->material = Resources::Find<Material>(L"DefaultVInverterAniMaterial");
	}
}