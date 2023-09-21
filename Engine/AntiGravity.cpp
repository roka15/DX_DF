#include "AntiGravity.h"

#include "GameObject.h"
#include "User.h"
#include "AnimationObjectPool.h"
#include "SceneManager.h"
#include "NPK.h"
#include "Resources.h"
#include "RokaTime.h"
#include "Shader.h"

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
		std::shared_ptr<Shader> VerticalAniShader = Resources::Find<Shader>(L"VerticalInverterAnimationShader");
		std::shared_ptr<Shader> VerticalAniEftShdaer = Resources::Find<Shader>(L"VerticalInverterEftAnimationShader");
		if (key.compare(L"homonculouse") == 0)
		{
			effectObj = SceneManager::GetActiveScene()->FindGameObject(ELayerType::BackObject, key + L"Obj");
			if (effectObj != nullptr)
				return;
			effectObj = pool->Spawn(L"AniObject");
			effectObj->SetName(key + L"Obj");
			std::shared_ptr<Texture> texture1
				= Resources::Find<NPK>(L"homonculouse")->CreateAtlas(L"fluto.img", 39, 53, L"mage_homon_fluto");
			std::shared_ptr<Animator> ani = effectObj->GetComponent<Animator>();
			ani->Create(texture1, L"mage_antiGravity_homon1", 8, 14, 0.05f);
			ani->Create(texture1, L"mage_antiGravity_homon2", 12, 14, 0.05f);
			aniPtr = ani.get();
			ani->CompleteEvent(L"mage_antiGravity_homon1") = std::bind([aniPtr]()->void {aniPtr->PlayAnimation(L"mage_antiGravity_homon2"); });
			ani->PlayAnimation(L"mage_antiGravity_homon1");
			ani->CompleteEvent(L"mage_antiGravity_homon1") = std::bind(&AntiGravity::DeSpawnEffect, this, caster, key + L"_pluto");
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
			effectObj = pool->Spawn(L"AniObject");
			effectObj->SetName(key + L"Obj");
			std::shared_ptr<Texture> texture1
				= Resources::Find<NPK>(L"mageAntiGravity")->CreateAtlas(L"pluto-normal.img", 0, 16, L"mage_antiGravity_pluto");
			std::shared_ptr<Animator> ani = effectObj->GetComponent<Animator>();
			ani->Create(texture1, L"mage_antiGravity_pluto_start", 0, 12, 0.01f);
			ani->Create(texture1, L"mage_antiGravity_pluto_middle", 12, 16, 0.06f);
			PlutoAniType1(effectObj);
			
			ani->SetFrameEventListener(this);
			std::shared_ptr<Animation> animation = ani->FindAnimation(L"mage_antiGravity_pluto_start");
			animation->RegisterFrameEvent(L"mage_antiGravity_pluto_start", 11);
			animation->RegisterFrameEvent(L"mage_antiGravity_pluto_effect1", 5);
		
			animation = ani->FindAnimation(L"mage_antiGravity_pluto_middle");
			animation->RegisterFrameEvent(L"mage_antiGravity_pluto_effect2", 14);
			ani->CompleteEvent(L"mage_antiGravity_pluto_middle") = std::bind(&AntiGravity::DeSpawnEffect, this, caster, key);
			ani->ReverseCopleteEvent(L"mage_antiGravity_pluto_start") = std::bind(&AntiGravity::DeSpawnEffect, this, caster, key + L"_reverse");
#pragma region child effect
			std::shared_ptr<Texture> eye_texture
				= Resources::Find<NPK>(L"mageAntiGravity")->CreateAtlas(L"pluto-eye.img", 0, 1, L"mage_antiGravity_pluto_eye");
			std::shared_ptr<GameObject> eye = pool->Spawn(L"AniEftObject");
			eye->SetName(L"plutoEyeObj");
			std::shared_ptr<Animator> eyeAni = eye->GetComponent<Animator>();
			eyeAni->Create(eye_texture, L"mage_anitGravity_pluto_eye", 0, 0, 0.0f);
			{
				std::shared_ptr<Transform> tf = eye->GetComponent<Transform>();
				tf->scale = Vector3(0.45f, 0.3f, 1.0f);
				tf->position = tf->position + Vector3(-0.1f, 0.0f, 0.0f);
				mEyeOriginPos = tf->position;
			}

			std::shared_ptr<Texture> spark_texture
				= Resources::Find<NPK>(L"mageAntiGravity")->CreateAtlas(L"pluto-spark.img", 0, 6, L"mage_antiGravity_pluto_spark");
			std::shared_ptr<GameObject> spark = pool->Spawn(L"AniEftObject");
			spark->SetName(L"plutoSparkObj");
			std::shared_ptr<Animator> sparkAni = spark->GetComponent<Animator>();
			sparkAni->Create(spark_texture, L"mage_anitGravity_pluto_spark", 0, 6, 0.05f);
			{
				std::shared_ptr<Transform> tf = spark->GetComponent<Transform>();
				tf->scale = Vector3(1.0f, 1.0f, 1.0f);
				tf->position = tf->position + Vector3(-0.0f, 0.0f, 0.0f);
			}
			aniPtr = sparkAni.get();
			sparkAni->CompleteEvent(L"mage_anitGravity_pluto_spark") = std::bind([aniPtr]()->void {aniPtr->ActiveAnimationNull(); });
			

			std::shared_ptr<Texture> light_texture
				= Resources::Find<NPK>(L"mageAntiGravity")->CreateAtlas(L"pluto-light.img", 0, 4, L"mage_antiGravity_pluto_light");
			std::shared_ptr<GameObject> light = pool->Spawn(L"AniEftObject");
			light->SetName(L"plutoLightObj");
			std::shared_ptr<Animator> lightAni = light->GetComponent<Animator>();
			lightAni->Create(light_texture, L"mage_anitGravity_pluto_light", 0, 4, 0.05f);
			{
				std::shared_ptr<Transform> tf = light->GetComponent<Transform>();
				tf->scale = Vector3(1.0f, 1.0f, 1.0f);
				tf->position = tf->position + Vector3(-0.0f, 0.0f, 0.0f);
			}
			aniPtr = lightAni.get();
			lightAni->CompleteEvent(L"mage_anitGravity_pluto_light") = std::bind([aniPtr]()->void {aniPtr->ActiveAnimationNull(); });

			std::shared_ptr<Texture> smoke_texture
				= Resources::Find<NPK>(L"mageAntiGravity")->CreateAtlas(L"smoke1.img", 0, 6, L"mage_antiGravity_pluto_smoke");
			std::shared_ptr<GameObject> smoke = pool->Spawn(L"AniObject");
			smoke->SetName(L"plutoSmokeObj");
			std::shared_ptr<Animator> smokeAni = smoke->GetComponent<Animator>();
			smokeAni->Create(smoke_texture, L"mage_antiGravity_pluto_smoke", 0, 6, 0.05f);
			{
				std::shared_ptr<Transform> tf = smoke->GetComponent<Transform>();
				tf->scale = Vector3(4.0f, 4.0f, 1.0f);
				tf->position = tf->position + Vector3(-0.0f, 0.0f, 0.0f);
			}
			aniPtr = smokeAni.get();
			lightAni->CompleteEvent(L"mage_anitGravity_pluto_light") = std::bind([aniPtr]()->void {aniPtr->ActiveAnimationNull(); });

			effectObj->AddChild(eye);
			effectObj->AddChild(spark);
			effectObj->AddChild(light);
			effectObj->AddChild(smoke);
#pragma endregion	
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
			PlutoSparkEffect(deleteObj);
		}
		if (mbActive == false && deleteObj != nullptr)
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
			Time::RequestEvent(callBack, std::bind(&AntiGravity::PlutoAniType2, this, caster));
		}
		else if (frameEvent.compare(L"mage_antiGravity_pluto_effect1") == 0)
		{
			EyeType1(caster);
			PlutoSparkEffect(caster);
		}
		else if (frameEvent.compare(L"mage_antiGravity_pluto_effect2") == 0)
		{
			caster->GetChild(L"plutoEyeObj")->GetComponent<Animator>()->ActiveAnimationNull();
			caster->GetChild(L"plutoLightObj")->GetComponent<Animator>()->PlayAnimation(L"mage_anitGravity_pluto_light");
			caster->GetChild(L"plutoSmokeObj")->GetComponent<Animator>()->PlayAnimation(L"mage_antiGravity_pluto_smoke");
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
	void AntiGravity::PlutoAniType1(std::shared_ptr<GameObject> caster)
	{
		std::shared_ptr<Animator> ani = caster->GetComponent<Animator>();
		ani->PlayAnimation(L"mage_antiGravity_pluto_start");
	}
	void AntiGravity::PlutoAniType2(std::shared_ptr<GameObject> caster)
	{
		std::shared_ptr<Animator> ani = caster->GetComponent<Animator>();
		ani->PlayAnimation(L"mage_antiGravity_pluto_middle");
		ani->SetFrameEventListener(this);
		EyeType2(caster);
	}
	void AntiGravity::EyeType1(std::shared_ptr<GameObject> caster)
	{
		std::shared_ptr<GameObject> obj = caster->GetChild(L"plutoEyeObj");
		obj->GetComponent<Animator>()->PlayAnimation(L"mage_anitGravity_pluto_eye", true);
		std::shared_ptr<Transform> tf = obj->GetComponent<Transform>();
		tf->position = mEyeOriginPos;
	}
	void AntiGravity::EyeType2(std::shared_ptr<GameObject> caster)
	{
		std::shared_ptr<GameObject> obj = caster->GetChild(L"plutoEyeObj");
		std::shared_ptr<Transform> tf = obj->GetComponent<Transform>();
		tf->position = mEyeOriginPos + Vector3(0.0f, 0.05f, 0.0f);
	}
	void AntiGravity::PlutoSparkEffect(std::shared_ptr<GameObject> caster)
	{
		std::shared_ptr<GameObject> spark = caster->GetChild(L"plutoSparkObj");
		spark->GetComponent<Animator>()->PlayAnimation(L"mage_anitGravity_pluto_spark", false);
	}
}