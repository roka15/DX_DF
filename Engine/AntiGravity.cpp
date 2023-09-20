#include "AntiGravity.h"

#include "GameObject.h"
#include "User.h"
#include "AnimationObjectPool.h"
#include "SceneManager.h"
#include "NPK.h"
#include "Resources.h"
#include "RokaTime.h"

#include "Animator.h"
#include "Transform.h"

#include "PlayerScript.h"


namespace roka
{
	void AntiGravity::Execute(std::shared_ptr<GameObject> caster)
	{
		std::shared_ptr<PlayerScript> player = caster->GetComponent<PlayerScript>();
		player->player_state = EPlayerState::Skill;
		const info::User* user = player->GetUserInfo();
		UINT keycode = user->GetSkillKey01();
		const std::wstring aniKey = user->GetKeySkillName(keycode);
		player->SkillPartMotion(aniKey);
		Skill::Execute(caster);
	}
	void AntiGravity::SpawnEffect(std::shared_ptr<GameObject> caster, std::wstring key)
	{
		AnimationObjectPool* pool = ObjectPoolManager<AnimationObjectPool, GameObject>::GetInstance();
		std::shared_ptr<PlayerScript> player = caster->parent->parent->GetComponent<PlayerScript>();
		std::shared_ptr<Transform> tf = caster->GetComponent<Transform>();
		std::shared_ptr<GameObject> effectObj = nullptr;
		Animator* aniPtr = nullptr;
		Vector3 pos = tf->position;
		Vector3 offset = Vector3::Zero;
		Vector3 scale = Vector3::One;
		float dir = player->GetDir();
		if (key.compare(L"homonculouse") == 0)
		{
			effectObj = SceneManager::GetActiveScene()->FindGameObject(ELayerType::BackObject, key + L"Obj");
			if (effectObj != nullptr)
				return;
			effectObj = pool->GetPool(L"AniObject")->Spawn();
			effectObj->SetName(key + L"Obj");
			std::shared_ptr<Texture> texture1
				= Resources::Find<NPK>(L"homonculouse")->CreateAtlas(L"fluto.img", 39, 53, L"mage_homon_fluto");
			std::shared_ptr<Animator> ani = effectObj->GetComponent<Animator>();
			ani->Create(texture1, L"mage_antiGravity_homon1", 8, 14, 0.05f);
			ani->Create(texture1, L"mage_antiGravity_homon2", 12, 14, 0.05f);
			aniPtr = ani.get();
			ani->CompleteEvent(L"mage_antiGravity_homon1") = std::bind([aniPtr]()->void {aniPtr->PlayAnimation(L"mage_antiGravity_homon2"); });
			ani->PlayAnimation(L"mage_antiGravity_homon1");
			ani->CompleteEvent(L"mage_antiGravity_homon1") = std::bind(&AntiGravity::DeSpawnEffect, this, caster, key+L"_pluto");
			ani->CompleteEvent(L"mage_antiGravity_homon2") = std::bind(&AntiGravity::DeSpawnEffect, this, caster, key);
			SceneManager::GetActiveScene()->AddGameObject(ELayerType::BackObject, effectObj);

			scale.x = 1.15f;
			scale.y = 1.15f;
			offset.x = 0.65f;
			offset.y = -0.4f;
		}
		else if (key.compare(L"pluto") == 0)
		{
			effectObj = SceneManager::GetActiveScene()->FindGameObject(ELayerType::BackObject, key + L"Obj");
			if (effectObj != nullptr)
				return;
			effectObj = pool->GetPool(L"AniObject")->Spawn();
			effectObj->SetName(key + L"Obj");
			std::shared_ptr<Texture> texture1
				= Resources::Find<NPK>(L"mageAntiGravity")->CreateAtlas(L"pluto-normal.img", 0, 16, L"mage_antiGravity_pluto");
			std::shared_ptr<Animator> ani = effectObj->GetComponent<Animator>();
			ani->Create(texture1, L"mage_antiGravity_pluto_start", 0, 12, 0.01f);
			ani->Create(texture1, L"mage_antiGravity_pluto_middle", 12, 16, 0.06f);
			ani->PlayAnimation(L"mage_antiGravity_pluto_start");
			aniPtr = ani.get();
			ani->SetFrameEventListener(this);
			std::shared_ptr<Animation> animation = ani->FindAnimation(L"mage_antiGravity_pluto_start");
			animation->RegisterFrameEvent(L"mage_antiGravity_pluto_start", 11);
			animation->RegisterFrameEvent(L"mage_antiGravity_pluto_eye", 5);
			ani->CompleteEvent(L"mage_antiGravity_pluto_middle") = std::bind(&AntiGravity::DeSpawnEffect, this, caster, key);
			ani->ReverseCopleteEvent(L"mage_antiGravity_pluto_start") = std::bind(&AntiGravity::DeSpawnEffect, this, caster, key+L"_reverse");

			std::shared_ptr<Texture> eye_texture
				= Resources::Find<NPK>(L"mageAntiGravity")->CreateAtlas(L"pluto-eye.img", 0, 1, L"mage_antiGravity_pluto_eye");
			std::shared_ptr<GameObject> eye = pool->GetPool(L"AniEftObject")->Spawn();
			eye->SetName(L"plutoEyeObj");
			std::shared_ptr<Animator> eyeAni = eye->GetComponent<Animator>();
			eyeAni->Create(eye_texture, L"mage_anitGravity_pluto_eye", 0, 0, 0.0f);
			{
				std::shared_ptr<Transform> tf = eye->GetComponent<Transform>();
				tf->scale = Vector3(0.4f,0.3f,1.0f);
				tf->position = tf->position + Vector3(-0.1f, 0.0f, 0.0f);
			}

			effectObj->AddChild(eye);

			SceneManager::GetActiveScene()->AddGameObject(ELayerType::BackObject, effectObj);

			scale.x = 0.5f;
			scale.y = 0.6f;
			offset.x = 1.0f;
			offset.y = -0.4f;
		}
		if (effectObj != nullptr)
		{
			std::shared_ptr<Transform> tf = effectObj->GetComponent<Transform>();
			if (dir > 0)
				tf->position = pos + offset;
			else
			{
				pos.x -= offset.x;
				pos.y += offset.y;
				tf->position = pos;
			}
			tf->scale = scale;
		}
	}
	void AntiGravity::DeSpawnEffect(std::shared_ptr<GameObject> caster, std::wstring key)
	{
		std::wstring name;
		std::shared_ptr<GameObject> deleteObj;
		name = key + L"Obj";
		deleteObj = SceneManager::GetActiveScene()->FindGameObject(ELayerType::BackObject, name);
		std::shared_ptr<Animator> ani;
		bool mbActive = false;
		if (deleteObj != nullptr)
		{
			ani = deleteObj->GetComponent<Animator>();
		}
		if (key.compare(L"homonculouse_pluto") == 0)
		{
			SpawnEffect(caster, L"pluto");
			mbActive = true;
		}
		else if (key.compare(L"pluto") == 0)
		{
				ani->PlayReverseAnimation(L"mage_antiGravity_pluto_start");
				mbActive = true;
		}
		else if (key.compare(L"pluto_reverse") == 0)
		{
			deleteObj = SceneManager::GetActiveScene()->FindGameObject(ELayerType::BackObject, L"plutoObj");
			ani = deleteObj->GetComponent<Animator>();
		}
		if (mbActive == false && deleteObj !=nullptr)
		{
			ani->ActiveAnimationNull();
			deleteObj->active = GameObject::EState::Dead;
		}
	}
	void AntiGravity::SpawnCollider(std::shared_ptr<GameObject> caster)
	{
	}
	void AntiGravity::DeSpawnCollider(std::shared_ptr<GameObject> caster)
	{
	}
	void AntiGravity::EnableCollision(std::shared_ptr<GameObject> caster)
	{
	}
	void AntiGravity::DisableCollision(std::shared_ptr<GameObject> caster)
	{
	}
	void AntiGravity::Left(std::shared_ptr<GameObject> caster)
	{
	}
	void AntiGravity::Right(std::shared_ptr<GameObject> caster)
	{
	}
	void AntiGravity::Sound(std::wstring key)
	{
	}
	void AntiGravity::End(std::shared_ptr<GameObject> caster)
	{
	}
	void AntiGravity::OnAnimationFramEvent(std::shared_ptr<GameObject> caster, std::wstring frameEvent)
	{
		if (frameEvent.compare(L"SpawnHomonculouse") == 0)
		{
			SpawnEffect(caster, L"homonculouse");
		}
		else if (frameEvent.compare(L"mage_antiGravity_pluto_start") == 0)
		{
			std::shared_ptr<Animator> ani = caster->GetComponent<Animator>();
			Animator* aniPtr = ani.get();
			Time::CallBackTimerInfo callBack = {};
			callBack.endTime = 0.05f;
			Time::RequestEvent(callBack, std::bind([aniPtr]()->void {
				aniPtr->PlayAnimation(L"mage_antiGravity_pluto_middle"); 
				//aniPtr->owner->GetChild(L"plutoEyeObj")->GetComponent<Tra
				}));
		}
		else if (frameEvent.compare(L"mage_antiGravity_pluto_eye") == 0)
		{
			std::shared_ptr<GameObject> obj = caster->GetChild(L"plutoEyeObj");
			obj->GetComponent<Animator>()->PlayAnimation(L"mage_anitGravity_pluto_eye",true);
		}
	}
	void AntiGravity::OnCollisionEnter(std::shared_ptr<GameObject> caster, std::shared_ptr<GameObject> target)
	{
	}
	void AntiGravity::OnCollisionStay(std::shared_ptr<GameObject> caster, std::shared_ptr<GameObject> target)
	{
	}
	void AntiGravity::OnCollisionExit(std::shared_ptr<GameObject> caster, std::shared_ptr<GameObject> target)
	{
	}
	void AntiGravity::Release()
	{
	}
}