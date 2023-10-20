#include "MgNormalAtk.h"

#include "RokaEngine.h"
#include "GameObject.h"
#include "Input.h"
#include "User.h"
#include "RokaTime.h"
#include "Object.h"
#include "AnimationObjectPool.h"
#include "CollisionManager.h"

#include "Animator.h"
#include "Transform.h"
#include "Collider2D.h"
#include "SkinPartScript.h"
#include "AvatarScript.h"
#include "PlayerScript.h"
#include "MonsterScript.h"
#include "MoveScript.h"
#include "AudioSource.h"
#include "AudioClip.h"
#include "Resources.h"
namespace roka
{
	MgNormalAtk::MgNormalAtk(const UINT& damage) :Skill(damage)
	{
	}
	void MgNormalAtk::Execute(std::shared_ptr<GameObject> caster)
	{
		std::shared_ptr<PlayerScript> player = caster->GetComponent<PlayerScript>();
		player->player_state = EPlayerState::NomalAtk;
		player->PlayPartMotion();
		player->DisableKeyInput();
		std::shared_ptr<MoveScript> move = caster->GetComponent<MoveScript>();
		move->Stop();
		move->ResetSpeed();


		std::shared_ptr<GameObject> avatarObj = caster->GetChild<AvatarScript>();
		std::shared_ptr<GameObject> skinObj = avatarObj->GetChild<SkinPartScript>();

		std::shared_ptr<Animator> ani = skinObj->GetComponent<Animator>();
		ani->SetFrameEventListener(this);

		SpawnCollider(caster);
		std::shared_ptr<AudioClip> clip = Resources::Find<AudioClip>(L"mgAtkSound1");
		if (clip == nullptr)
		{
			clip = Resources::Load<AudioClip>(L"mgAtkSound1", L"..\\Resources\\Audio\\wz_atk_01.ogg");
		}
		std::shared_ptr<AudioSource> audioSource = caster->GetComponent<AudioSource>();
		audioSource->Stop();
		audioSource->SetClip(clip);
		audioSource->Play();
	}

	void MgNormalAtk::SpawnEffect(std::shared_ptr<GameObject> caster, std::wstring key)
	{
	}

	void MgNormalAtk::DeSpawnEffect(std::shared_ptr<GameObject> caster, std::wstring key)
	{
	}

	void MgNormalAtk::SpawnCollider(std::shared_ptr<GameObject> caster)
	{
		std::shared_ptr<PlayerScript> player = caster->GetComponent<PlayerScript>();
		std::shared_ptr<GameObject> colObject = manager::ObjectPoolManager<AnimationObjectPool, GameObject>::GetInstance()->Spawn(L"ColAniObject");
		colObject->SetName(L"MgNormalAtkColObject");
		std::shared_ptr<Collider2D> collider = colObject->AddComponent<Collider2D>();
		std::shared_ptr<Transform> transform = colObject->GetComponent<Transform>();
		Vector3 pos = player->owner->GetComponent<Transform>()->position;
		transform->position = Vector3(-pos.x, -pos.y, -pos.z);
		transform->scale = Vector3(0.1f, 0.1f, 1.0f);
		

		float dir = player->GetDir();
		if (dir == -1.0f)
		{
			Left(colObject);
		}
		else if (dir == 1.0f)
		{
			Right(colObject);
		}
		collider->SetCollisionListener(this);
		SceneManager::AddGameObject(ELayerType::FrontObject, colObject);
	}

	void MgNormalAtk::DeSpawnCollider(std::shared_ptr<GameObject> caster)
	{
		std::shared_ptr<GameObject> playerObj = caster;
		std::shared_ptr<Collider2D> collider = SceneManager::FindGameObject(ELayerType::FrontObject, L"MgNormalAtkColObject")->GetComponent<Collider2D>();
		collider->SetCollisionListener(nullptr);
		collider->owner->active = GameObject::EState::Dead;
	}

	void MgNormalAtk::EnableCollision(std::shared_ptr<GameObject> caster)
	{
		std::shared_ptr<GameObject> playerObj = caster;
		std::shared_ptr<GameObject> colObj = SceneManager::FindGameObject(ELayerType::FrontObject, L"MgNormalAtkColObject");
		std::shared_ptr<Collider2D> collider = colObj->GetComponent<Collider2D>();
		collider->EnableColCheck();
	}

	void MgNormalAtk::DisableCollision(std::shared_ptr<GameObject> caster)
	{
		std::shared_ptr<GameObject> playerObj = caster;
		std::shared_ptr<GameObject> colObj = SceneManager::FindGameObject(ELayerType::FrontObject, L"MgNormalAtkColObject");
		std::shared_ptr<Collider2D> collider = colObj->GetComponent<Collider2D>();
		collider->DisableColCheck();
	}

	void MgNormalAtk::Left(std::shared_ptr<GameObject> caster)
	{
		std::shared_ptr<Transform> transform = caster->GetComponent<Transform>();
		transform->position = Vector3(-0.35f, -0.4f, 0.0f);
	}

	void MgNormalAtk::Right(std::shared_ptr<GameObject> caster)
	{
		std::shared_ptr<Transform> transform = caster->GetComponent<Transform>();
		transform->position = Vector3(0.35f, -0.4f, 0.0f);
	}

	void MgNormalAtk::Sound(std::wstring key)
	{
	}

	void MgNormalAtk::End(std::shared_ptr<GameObject> caster)
	{
		std::shared_ptr<GameObject> playerObj = caster;
		std::shared_ptr<GameObject> avatarObj = playerObj->GetChild<AvatarScript>();
		std::shared_ptr<PlayerScript> player = playerObj->GetComponent<PlayerScript>();
		std::shared_ptr<AvatarScript> avatar = avatarObj->GetComponent<AvatarScript>();
		if (mbCallbackEvent == false)
		{
			avatar->StopAni();
			Time::CallBackTimerInfo callBack = {};
			callBack.endTime = 0.1f;
			Time::RequestEvent(callBack, std::bind(&PlayerScript::NextState, player));
			Time::RequestEvent(callBack, std::bind([this]()->void {mbCallbackEvent = false; }));
			mbCallbackEvent = true;
			DeSpawnCollider(playerObj);
		}
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
			std::shared_ptr<GameObject> colObj = SceneManager::FindGameObject(ELayerType::FrontObject,L"MgNormalAtkColObject");
			if (colObj == nullptr)
				return;
			DisableCollision(playerObj);
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
				std::shared_ptr<AudioSource> audioSource = playerObj->GetComponent<AudioSource>();
				std::shared_ptr<AudioClip> clip= audioSource->GetClip();
				if (clip == nullptr)
					return;
				if (clip->GetKey().compare(L"mgAtkSound1") == 0)
				{
					clip = Resources::Find<AudioClip>(L"mgAtkSound2");
					if (clip == nullptr)
					{
						clip = Resources::Load<AudioClip>(L"mgAtkSound2", L"..\\Resources\\Audio\\wz_atk_02.ogg");
					}
				}
				else if (clip->GetKey().compare(L"mgAtkSound2") == 0)
				{
					clip = Resources::Find<AudioClip>(L"mgAtkSound3");
					if (clip == nullptr)
					{
						clip = Resources::Load<AudioClip>(L"mgAtkSound3", L"..\\Resources\\Audio\\wz_atk_03.ogg");
					}
				}
				else if (clip->GetKey().compare(L"mgAtkSound3") == 0)
				{
					clip = Resources::Find<AudioClip>(L"mgAtkSound1");
					if (clip == nullptr)
					{
						clip = Resources::Load<AudioClip>(L"mgAtkSound1", L"..\\Resources\\Audio\\wz_atk_01.ogg");
					}
				}

				
				audioSource->Stop();
				audioSource->SetClip(clip);
				audioSource->Play();
				return;
			}
			else
			{
				End(playerObj);
			}
		}
		else if (frameEvent.compare(L"ActiveCollider") == 0)
		{
			EnableCollision(playerObj);
		}
		else if (frameEvent.compare(L"DisableCollision") == 0)
		{
			DisableCollision(playerObj);
		}
	}
	void MgNormalAtk::OnCollisionEnter(std::shared_ptr<GameObject> caster, std::shared_ptr<GameObject> target)
	{
		std::shared_ptr<GameObject> colObj = caster;
		std::shared_ptr<MonsterScript> monster = target->parent->GetComponent<MonsterScript>();
		if (monster == nullptr)
			return;
		std::shared_ptr<Collider2D> left = colObj->GetComponent<Collider2D>();
		std::shared_ptr<Collider2D> right = target->GetComponent<Collider2D>();
		if (left->GetHitType() == right->GetHitType())
		{
			monster->TakeDamage(mDamage);
			monster->PlayStun(EStunState::Stagger);

			CollisionManager::DisableCollision(left, right);
			left->DisableColCheck();
		}
	}
	void MgNormalAtk::OnCollisionStay(std::shared_ptr<GameObject> caster, std::shared_ptr<GameObject> target)
	{
	}
	void MgNormalAtk::OnCollisionExit(std::shared_ptr<GameObject> caster, std::shared_ptr<GameObject> target)
	{
	}
	void MgNormalAtk::Release()
	{
	}
}


