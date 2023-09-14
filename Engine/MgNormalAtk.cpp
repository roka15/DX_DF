#include "MgNormalAtk.h"

#include "RokaEngine.h"
#include "GameObject.h"
#include "Input.h"
#include "User.h"
#include "RokaTime.h"

#include "Animator.h"
#include "SkinPartScript.h"
#include "AvatarScript.h"
#include "PlayerScript.h"
namespace roka
{
	MgNormalAtk::MgNormalAtk():Skill()
	{
	}
	void MgNormalAtk::Execute(std::shared_ptr<GameObject> caster)
	{
		std::shared_ptr<PlayerScript> player = caster->GetComponent<PlayerScript>();
		player->player_state = EPlayerState::NomalAtk;
		player->PlayPartMotion();
		
		
		std::shared_ptr<GameObject> avatarObj = caster->GetChild<AvatarScript>();
		std::shared_ptr<GameObject> skinObj = avatarObj->GetChild<SkinPartScript>();

		std::shared_ptr<Animator> ani = skinObj->GetComponent<Animator>();
		ani->SetFrameEventListener(this);
	}

	void MgNormalAtk::SpawnEffect(std::shared_ptr<GameObject> caster, std::wstring key)
	{
	}

	void MgNormalAtk::SpawnCollider(std::shared_ptr<GameObject> caster)
	{
	}

	void MgNormalAtk::SpawnCollider(Vector3 target)
	{
	}

	void MgNormalAtk::Sound(std::wstring key)
	{
	}

	void MgNormalAtk::OnAnimationFramEvent(std::shared_ptr<GameObject> caster, std::wstring frameEvent)
	{
		std::shared_ptr<GameObject> playerObj = caster->parent->parent;
		std::shared_ptr<PlayerScript> player = playerObj->GetComponent<PlayerScript>();
		std::shared_ptr<GameObject> avatarObj = playerObj->GetChild<AvatarScript>();
		std::shared_ptr<AvatarScript> avatar = avatarObj->GetComponent<AvatarScript>();
		if (frameEvent.compare(L"NextState") == 0)
		{
			EKeyCode key = (EKeyCode)player->GetUserInfo()->GetNormalAtkKey();
			if (Input::GetKey(key) || Input::GetKeyDown(key))
			{
				if (mbCallbackEvent == false)
				{
					avatar->StopAni();
					Time::CallBackTimerInfo callBack = {};
					callBack.endTime = 0.05f;
					Time::RequestEvent(callBack, std::bind(&AvatarScript::StartAni, avatar));
					Time::RequestEvent(callBack, std::bind([this]()->void {mbCallbackEvent = false; }));
					mbCallbackEvent = true;
				}
			
				return;
			}
			else
			{
				if (mbCallbackEvent == false)
				{
					avatar->StopAni();
					Time::CallBackTimerInfo callBack = {};
					callBack.endTime = 0.1f;
					Time::RequestEvent(callBack, std::bind(&PlayerScript::NextState,player));
					Time::RequestEvent(callBack, std::bind([this]()->void {mbCallbackEvent = false; }));
					mbCallbackEvent = true;
				}	
			}
		}
	}
}


