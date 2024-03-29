#include "AntiGravity.h"

#include "GameObject.h"
#include "User.h"
#include "AnimationObjectPool.h"
#include "WarningObjectPool.h"
#include "SceneManager.h"
#include "NPK.h"
#include "Resources.h"
#include "RokaTime.h"
#include "Shader.h"

#include "Animator.h"
#include "Transform.h"
#include "MeshRenderer.h"

#include "PlayerScript.h"
#include "ChangeSizeOverTime.h"

#include "AudioClip.h"
#include "AudioSource.h"
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

		std::shared_ptr<AudioClip> clip = Resources::Find<AudioClip>(L"mgAntiGravitySound");
		if (clip == nullptr)
		{
			clip = Resources::Load<AudioClip>(L"mgAntiGravitySound", L"..\\Resources\\Audio\\wz_antigravity_starter.ogg");
		}
		std::shared_ptr<AudioSource> audioSource = caster->GetComponent<AudioSource>();
		audioSource->Stop();
		audioSource->SetClip(clip);
		audioSource->Play();
	}
	void AntiGravity::SpawnEffect(std::shared_ptr<GameObject> caster, std::wstring key)
	{
		std::shared_ptr<PlayerScript> player = caster->parent->parent->GetComponent<PlayerScript>();
		mDir = player->GetDir();
		 
		if (key.compare(L"homonculouse") == 0)
		{
			CreateHomonculouse(caster,key);
		}
		else if (key.compare(L"pluto") == 0)
		{
			CreatePluto(caster, key);	
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
			Time::CallBackTimerInfo callBack = {};
			callBack.endTime = 0.25f;
			Time::RequestEvent(callBack, std::bind(&AntiGravity::DeSpawnEffect, this, caster, L"homonculouse"));
			mbActive = true;
		}
		else if (key.compare(L"pluto") == 0)
		{
			ani->PlayReverseAnimation(L"mage_antiGravity_pluto_start", 0.09f);
			PlutoSparkEffect(deleteObj);
			mbActive = true;

			Scene* Active = SceneManager::GetActiveScene();
			std::shared_ptr<GameObject> Object = Active->FindGameObject(ELayerType::BackObject, L"AntiGravityCircleObj");
			std::shared_ptr<ChangeSizeOverTime> cso = Object->GetComponent<ChangeSizeOverTime>();
			cso->SetAlphaType(EAlphaType::FadeOut);
			cso->SetAlphaOffset(0.15f);
			cso->EndTime(1.0f);
			cso->SetEndEvent() = std::bind(&AntiGravity::DeSpawnCircle,this,Object);
			cso->SetActive(true);

			Object = Active->FindGameObject(ELayerType::BackObject, L"AntiGravityCircleObj2");
			cso = Object->GetComponent<ChangeSizeOverTime>();
			cso->SetAlphaType(EAlphaType::FadeOut);
			cso->SetAlphaOffset(0.15f);
			cso->EndTime(1.0f);
			cso->SetEndEvent() = std::bind(&AntiGravity::DeSpawnCircle, this, Object);
			cso->SetActive(true);

			std::shared_ptr<AudioClip> clip = Resources::Find<AudioClip>(L"AntiGravitySteamSound");
			if (clip == nullptr)
			{
				clip = Resources::Load<AudioClip>(L"AntiGravitySteamSound", L"..\\Resources\\Audio\\antigravity_steam.ogg");
			}
			std::shared_ptr<AudioSource> audioSource = deleteObj->GetComponent<AudioSource>();
			audioSource->Stop();
			audioSource->SetClip(clip);
			audioSource->SetLoop(false);
			audioSource->Play();

			clip = Resources::Find<AudioClip>(L"AntiGravityExpSound");
			if (clip == nullptr)
			{
				clip = Resources::Load<AudioClip>(L"AntiGravityExpSound", L"..\\Resources\\Audio\\antigravity_exp.ogg");
			}
			audioSource->SetClip(clip);
			audioSource->SetLoop(false);
			audioSource->Play();
		}
		else if (key.compare(L"pluto_reverse") == 0)
		{
			Scene* Active = SceneManager::GetActiveScene();
			deleteObj =Active->FindGameObject(ELayerType::BackObject, L"plutoObj");
			ani = deleteObj->GetComponent<Animator>();

			CreateFamiliarEft(deleteObj);
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
			std::shared_ptr<AudioSource> audioSource = caster->GetComponent<AudioSource>();
			

			CreateSuccessTube(caster, L"tube", Vector3(-0.3f, -0.5f, -0.001f));
			CreateSuccessTube(caster, L"tube", Vector3(-1.2f, -0.2f, 0.0f));
			CreateSuccessTube(caster, L"tube", Vector3(0.55f, 0.0f, 0.001f));
			CreateSuccessTube(caster, L"tube", Vector3(1.5f, -0.2f, 0.0f));
			CreateCircle(caster, L"circle");
		}
		else if (frameEvent.compare(L"mage_antiGravity_pluto_effect2") == 0)
		{
			caster->GetChild(L"plutoEyeObj")->GetComponent<Animator>()->ActiveAnimationNull();
			caster->GetChild(L"plutoLightObj")->GetComponent<Animator>()->PlayAnimation(L"mage_anitGravity_pluto_light");
			caster->GetChild(L"plutoSmokeObj")->GetComponent<Animator>()->PlayAnimation(L"mage_antiGravity_pluto_smoke");
		}
		else if (frameEvent.compare(L"CreateFamiliar") == 0)
		{
			Vector3 pos = SceneManager::GetActiveScene()->FindGameObject(ELayerType::BackObject, L"FamiliarEftObj")->GetComponent<Transform>()->position;
			AntiGravity::CreateFamiliar(pos);
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
	void AntiGravity::CreateHomonculouse(std::shared_ptr<GameObject> caster, std::wstring key)
	{
		AnimationObjectPool* pool = ObjectPoolManager<AnimationObjectPool, GameObject>::GetInstance();
		
		std::shared_ptr<Transform> tf = caster->GetComponent<Transform>();
		std::shared_ptr<GameObject> effectObj = nullptr;
		Animator* aniPtr = nullptr;
		Vector3 pos = tf->position;
		Vector3 offset = Vector3::Zero;
		Vector3 scale = Vector3::One;
		
		std::shared_ptr<Shader> AniShader = Resources::Find<Shader>(L"AtlasShader");
		std::shared_ptr<Shader> EftShader = Resources::Find<Shader>(L"EffectAtlasShader");
		std::shared_ptr<Shader> VerticalAniShader = Resources::Find<Shader>(L"VerticalInverterAtlasShader");
		std::shared_ptr<Shader> VerticalAniEftShdaer = Resources::Find<Shader>(L"VerticalInverterEftAtlasShader");

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
		ani->CompleteEvent(L"mage_antiGravity_homon1") = std::bind([aniPtr]()->void {aniPtr->PlayAnimation(L"mage_antiGravity_homon2",true); });
		ani->PlayAnimation(L"mage_antiGravity_homon1");
		ani->CompleteEvent(L"mage_antiGravity_homon1") = std::bind(&AntiGravity::DeSpawnEffect, this, caster, key + L"_pluto");
		SceneManager::GetActiveScene()->AddGameObject(ELayerType::BackObject, effectObj);
		if (mDir < 0.0f)
		{
			std::shared_ptr<MeshRenderer> meshRenderer = effectObj->GetComponent<MeshRenderer>();
			meshRenderer->material->shader = VerticalAniEftShdaer;
		}


		scale.x = 1.15f;
		scale.y = 1.15f;
		offset.x = 0.65f;
		offset.y = -0.4f;

		tf = effectObj->GetComponent<Transform>();
		if (mDir > 0)
			tf->position = pos + offset;
		else
		{
			pos.x -= offset.x;
			pos.y += offset.y;
			tf->position = pos;
		}

		tf->scale = scale;
	}
	void AntiGravity::CreatePluto(std::shared_ptr<GameObject> caster, std::wstring key)
	{
		AnimationObjectPool* pool = ObjectPoolManager<AnimationObjectPool, GameObject>::GetInstance();
		std::shared_ptr<Transform> tf = caster->GetComponent<Transform>();
		std::shared_ptr<GameObject> effectObj = nullptr;
		Animator* aniPtr = nullptr;
		Vector3 pos = tf->position;
		Vector3 offset = Vector3::Zero;
		Vector3 scale = Vector3::One;
		std::shared_ptr<Shader> AniShader = Resources::Find<Shader>(L"AtlasShader");
		std::shared_ptr<Shader> EftShader = Resources::Find<Shader>(L"EffectAtlasShader");
		std::shared_ptr<Shader> VerticalAniShader = Resources::Find<Shader>(L"VerticalInverterAtlasShader");
		std::shared_ptr<Shader> VerticalAniEftShdaer = Resources::Find<Shader>(L"VerticalInverterEftAtlasShader");

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
		
		if (mDir < 0.0f)
		{
			std::shared_ptr<MeshRenderer> meshRenderer = effectObj->GetComponent<MeshRenderer>();
			meshRenderer->material->shader = AniShader;
		}
		else if (mDir > 0.0f)
		{
			std::shared_ptr<MeshRenderer> meshRenderer = effectObj->GetComponent<MeshRenderer>();
			meshRenderer->material->shader = VerticalAniShader;
		}


		CreatePlutoEffect(effectObj, key);
		SceneManager::GetActiveScene()->AddGameObject(ELayerType::BackObject, effectObj);

		scale.x = 0.5f;
		scale.y = 0.6f;
		offset.x = 1.0f;
		offset.y = -0.4f;
		offset.z = 0.001f;
		tf = effectObj->GetComponent<Transform>();
		if (mDir > 0)
			tf->position = pos + offset;
		else
		{
			pos.x -= offset.x;
			pos.y += offset.y;
			pos.z = offset.z;
			tf->position = pos;
		}

		tf->scale = scale;


		std::shared_ptr<AudioClip> clip = Resources::Find<AudioClip>(L"AntiGravityStartSound");
		if (clip == nullptr)
		{
			clip = Resources::Load<AudioClip>(L"AntiGravityStartSound", L"..\\Resources\\Audio\\antigravity_start.ogg");
		}
		std::shared_ptr<AudioSource> audioSource = effectObj->GetComponent<AudioSource>();
		audioSource->Stop();
		audioSource->SetClip(clip);
		audioSource->SetLoop(false);
		audioSource->Play();
		clip = Resources::Find<AudioClip>(L"AntiGravityLoopSound");
		if (clip == nullptr)
		{
			clip = Resources::Load<AudioClip>(L"AntiGravityLoopSound", L"..\\Resources\\Audio\\antigravity_loop.ogg");
		}
		audioSource->SetClip(clip);
		audioSource->SetLoop(false);
		audioSource->Play();
		
	}
	void AntiGravity::CreatePlutoEffect(std::shared_ptr<GameObject> caster, std::wstring key)
	{
		AnimationObjectPool* pool = ObjectPoolManager<AnimationObjectPool, GameObject>::GetInstance();
		std::shared_ptr<Transform> tf;
		Animator* aniPtr = nullptr;
		
		Vector3 offset = Vector3::Zero;
		Vector3 scale = Vector3::One;

		std::shared_ptr<Shader> AniShader = Resources::Find<Shader>(L"AtlasShader");
		std::shared_ptr<Shader> EftShader = Resources::Find<Shader>(L"EffectAtlasShader");
		std::shared_ptr<Shader> VerticalAniShader = Resources::Find<Shader>(L"VerticalInverterAtlasShader");
		std::shared_ptr<Shader> VerticalAniEftShdaer = Resources::Find<Shader>(L"VerticalInverterEftAtlasShader");

		std::shared_ptr<Texture> eye_texture
			= Resources::Find<NPK>(L"mageAntiGravity")->CreateAtlas(L"pluto-eye.img", 0, 1, L"mage_antiGravity_pluto_eye");
		std::shared_ptr<GameObject> eye = pool->Spawn(L"AniEftObject");
		eye->SetName(L"plutoEyeObj");
		std::shared_ptr<Animator> eyeAni = eye->GetComponent<Animator>();
		eyeAni->Create(eye_texture, L"mage_anitGravity_pluto_eye", 0, 0, 0.0f);
		{
			std::shared_ptr<Transform> tf = eye->GetComponent<Transform>();
			tf->scale = Vector3(0.45f, 0.3f, 1.0f);
			if (mDir > 0.0f)
			{
				offset.x = 0.1f;
			}
			else if (mDir < 0.0f)
			{
				offset.x = -0.1f;
			}
			tf->position = tf->position + offset;
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
			tf = smoke->GetComponent<Transform>();
			tf->scale = Vector3(4.0f, 3.5f, 1.0f);
			if (mDir > 0.0f)
				offset.x = 0.1f;
			else if (mDir < 0.0f)
				offset.x = -0.1f;
			offset.y = 0.55f;
			tf->position = tf->position + offset;
		}
		aniPtr = smokeAni.get();
		lightAni->CompleteEvent(L"mage_anitGravity_pluto_light") = std::bind([aniPtr]()->void {aniPtr->ActiveAnimationNull(); });


#pragma region shader setting
		
		if (mDir < 0.0f)
		{
			std::shared_ptr<MeshRenderer> meshRenderer = eye->GetComponent<MeshRenderer>();
			meshRenderer->material->shader = EftShader;
		}
		else if (mDir > 0.0f)
		{
			std::shared_ptr<MeshRenderer> meshRenderer = eye->GetComponent<MeshRenderer>();
			meshRenderer->material->shader = VerticalAniEftShdaer;
		}

		if (mDir < 0.0f)
		{
			std::shared_ptr<MeshRenderer> meshRenderer = spark->GetComponent<MeshRenderer>();
			meshRenderer->material->shader = EftShader;
		}
		else if (mDir > 0.0f)
		{
			std::shared_ptr<MeshRenderer> meshRenderer = spark->GetComponent<MeshRenderer>();
			meshRenderer->material->shader =VerticalAniEftShdaer;
		}
		if (mDir < 0.0f)
		{
			std::shared_ptr<MeshRenderer> meshRenderer = light->GetComponent<MeshRenderer>();
			meshRenderer->material->shader = EftShader;
		}
		else if (mDir > 0.0f)
		{
			std::shared_ptr<MeshRenderer> meshRenderer = light->GetComponent<MeshRenderer>();
			meshRenderer->material->shader = VerticalAniEftShdaer;
		}
		if (mDir < 0.0f)
		{
			std::shared_ptr<MeshRenderer> meshRenderer = smoke->GetComponent<MeshRenderer>();
			meshRenderer->material->shader = VerticalAniShader;
		}
		else if (mDir > 0.0f)
		{
			std::shared_ptr<MeshRenderer> meshRenderer = smoke->GetComponent<MeshRenderer>();
			meshRenderer->material->shader =AniShader;
		}

		caster->AddChild(eye);
		caster->AddChild(spark);
		caster->AddChild(light);
		caster->AddChild(smoke);
#pragma endregion

	}
	void AntiGravity::CreateSuccessTube(std::shared_ptr<GameObject> caster, std::wstring key, Vector3 offset)
	{
		AnimationObjectPool* pool = ObjectPoolManager<AnimationObjectPool, GameObject>::GetInstance();
		std::shared_ptr<Transform> tf;
		Animator* aniPtr = nullptr;
		Vector3 scale = Vector3::One;

		std::shared_ptr<Shader> AniShader = Resources::Find<Shader>(L"AtlasShader");
		std::shared_ptr<Shader> EftShader = Resources::Find<Shader>(L"EffectAtlasShader");
		std::shared_ptr<Shader> VerticalAniShader = Resources::Find<Shader>(L"VerticalInverterAtlasShader");
		std::shared_ptr<Shader> VerticalAniEftShdaer = Resources::Find<Shader>(L"VerticalInverterEftAtlasShader");
		std::shared_ptr<NPK> npk = Resources::Find<NPK>(L"mageAntiGravity");
		
		std::shared_ptr<Texture> dustTexture = npk->CreateAtlas(L"tube-dust.img", 0, 6, L"mage_antiGravity_tube-dust");

		std::shared_ptr<GameObject> dust = pool->Spawn(L"AniEftObject");
		dust->SetName(L"tubeDustObj");
		std::shared_ptr<Animator> dustAni = dust->GetComponent<Animator>();
		dustAni->Create(dustTexture, L"mage_antiGravity_tube-dust", 0, 6, 0.1f);
		{
			tf = dust->GetComponent<Transform>();
			tf->scale = Vector3(1.0f, 1.0f, 1.0f);
			tf->position = tf->position + offset;
		}
		aniPtr = dustAni.get();
		dustAni->PlayAnimation(L"mage_antiGravity_tube-dust", false);
		dustAni->CompleteEvent(L"mage_antiGravity_tube-dust") = std::bind([aniPtr]()->void {aniPtr->ActiveAnimationNull();});

		std::shared_ptr<Texture> greatTexture = npk->CreateAtlas(L"tube-great.img", 0, 1, L"mage_antiGravity_tube-great");

		std::shared_ptr<GameObject> great = pool->Spawn(L"AniEftObject");
		great->SetName(L"tubeGreatObj");
		std::shared_ptr<Animator> greatAni = great->GetComponent<Animator>();
		greatAni->Create(greatTexture, L"mage_antiGravity_tube-great", 0, 1, 0.0f);
		{
			tf = great->GetComponent<Transform>();
			tf->scale = Vector3(1.0f, 1.0f, 1.0f);
			tf->position = tf->position + offset;
		}
		aniPtr = greatAni.get();
		greatAni->PlayAnimation(L"mage_antiGravity_tube-great", false);
		Animator* gAni = greatAni.get();

		std::shared_ptr<Texture> successTexture = npk->CreateAtlas(L"tube-success.img", 0, 4, L"mage_antiGravity_tube-success");

		std::shared_ptr<GameObject> success = pool->Spawn(L"AniEftObject");
		success->SetName(L"tubeSuccessObj");
		std::shared_ptr<Animator> successAni = success->GetComponent<Animator>();
		successAni->Create(successTexture, L"mage_antiGravity_tube-success", 0, 4, 0.1f);
		{
			tf = success->GetComponent<Transform>();
			tf->scale = Vector3(1.0f, 1.0f, 1.0f);
			tf->position = tf->position + offset;
		}
		aniPtr = successAni.get();
		successAni->PlayAnimation(L"mage_antiGravity_tube-success");
		successAni->CompleteEvent(L"mage_antiGravity_tube-success") = std::bind([aniPtr, gAni]()->void {aniPtr->ActiveAnimationNull(); gAni->ActiveAnimationNull(); });

		std::shared_ptr<Texture> normalTexture = npk->CreateAtlas(L"tube-normal.img", 0, 4, L"mage_antiGravity_tube-normal");

		std::shared_ptr<GameObject> normal = pool->Spawn(L"AniObject");
		normal->SetName(L"tubeNormalObj");
		std::shared_ptr<Animator> normalAni = normal->GetComponent<Animator>();
		normalAni->Create(normalTexture, L"mage_antiGravity_tube-normal", 0, 4, 0.1f);
		{
			tf = normal->GetComponent<Transform>();
			tf->scale = Vector3(1.0f, 1.0f, 1.0f);
			offset.z += 0.001;
			tf->position = tf->position + offset;
		}
		aniPtr = normalAni.get();
		normalAni->PlayAnimation(L"mage_antiGravity_tube-normal");
		normalAni->CompleteEvent(L"mage_antiGravity_tube-normal") = std::bind([aniPtr]()->void {aniPtr->ActiveAnimationNull(); });
		
		
		std::shared_ptr<MeshRenderer> mesh = dust->GetComponent<MeshRenderer>();
		mesh->material->shader = EftShader;
		mesh = great->GetComponent<MeshRenderer>();
		mesh->material->shader = EftShader;
		mesh = success->GetComponent<MeshRenderer>();
		mesh->material->shader = EftShader;
		mesh = normal->GetComponent<MeshRenderer>();
		mesh->material->shader = AniShader;

		caster->AddChild(dust);
		caster->AddChild(great);
		caster->AddChild(normal);
		caster->AddChild(success);
	}
	void AntiGravity::CreateCircle(std::shared_ptr<GameObject> caster, std::wstring key)
	{
		std::shared_ptr<GameObject> circle = ObjectPoolManager<WarningObjectPool, GameObject>::GetInstance()->Spawn(L"ChangeSizeOverTimeEftObject");
		std::shared_ptr<GameObject> circle2 = ObjectPoolManager<WarningObjectPool, GameObject>::GetInstance()->Spawn(L"ChangeSizeOverTimeEftObject");
		
		circle->SetName(L"AntiGravityCircleObj");
		circle2->SetName(L"AntiGravityCircleObj2");
		
		std::shared_ptr<Transform> tf;
		Animator* aniPtr = nullptr;
		Vector3 scale = Vector3::One;

		std::shared_ptr<Shader> AniShader = Resources::Find<Shader>(L"AtlasShader");
		std::shared_ptr<Shader> EftShader = Resources::Find<Shader>(L"EffectAtlasShader");
		std::shared_ptr<Shader> VerticalAniShader = Resources::Find<Shader>(L"VerticalInverterAtlasShader");
		std::shared_ptr<Shader> VerticalAniEftShdaer = Resources::Find<Shader>(L"VerticalInverterEftAtlasShader");
		std::shared_ptr<NPK> npk = Resources::Find<NPK>(L"mageAntiGravity");
		std::shared_ptr<GameObject> pluto = SceneManager::GetActiveScene()->FindGameObject(ELayerType::BackObject, L"plutoObj");
		Vector3 plutoPos = pluto->GetComponent<Transform>()->position;
		Vector3 offset = Vector3(0.0f, 0.0f, 0.001f);
		std::shared_ptr<Texture> circleTexture = npk->CreateAtlas(L"magiccircle-normal.img", 0, 1, L"mage_antiGravity_circle-normal");
		
		std::shared_ptr<Animator> ani = circle->GetComponent<Animator>();
		ani->Create(circleTexture, L"mage_antiGravity_circle-normal", 0, 0, 0.0f);
		ani->PlayAnimation(L"mage_antiGravity_circle-normal");
		std::shared_ptr<ChangeSizeOverTime> change_size = circle->GetComponent<ChangeSizeOverTime>();
		change_size->SetOffset(Vector3(0.3f, 0.25f, 0.0f));
		change_size->EndTime(0.15);
		change_size->SetActive(true);
		
	
		tf = circle->GetComponent<Transform>();
		tf->scale = Vector3(0.0f, 0.0f, 0.0f);
		tf->position = plutoPos+offset;
		tf->SetPivot(Vector3(1.0f, 0.5f, 0.0f));
		tf->EnablePivot();

		ani = circle2->GetComponent<Animator>();
		ani->Create(circleTexture, L"mage_antiGravity_circle-normal", 0, 0, 0.0f);
		ani->PlayAnimation(L"mage_antiGravity_circle-normal");
		change_size = circle2->GetComponent<ChangeSizeOverTime>();
		change_size->SetOffset(Vector3(0.3f, 0.25f, 0.0f));
		change_size->EndTime(0.15);
		change_size->SetActive(true);
		change_size->SetEndEvent() = std::bind(&AntiGravity::CreateCircleEft, this, pluto);

		tf = circle2->GetComponent<Transform>();
		tf->scale = Vector3(0.0f, 0.0f, 0.0f);
		tf->position = plutoPos+offset;
		tf->SetPivot(Vector3(0.0f, 0.5f, 0.0f));
		tf->EnablePivot();
		std::shared_ptr<MeshRenderer> mesh = circle->GetComponent<MeshRenderer>();
		mesh->material->shader = EftShader;
		mesh = circle2->GetComponent<MeshRenderer>();
		mesh->material->shader = VerticalAniEftShdaer;

		

		SceneManager::GetActiveScene()->AddGameObject(ELayerType::BackObject, circle);
		SceneManager::GetActiveScene()->AddGameObject(ELayerType::BackObject, circle2);
		
	}
	void AntiGravity::CreateCircleEft(std::shared_ptr<GameObject> caster)
	{
		std::shared_ptr<NPK> npk = Resources::Find<NPK>(L"mageAntiGravity");
		std::shared_ptr<Animator> ani;
		std::shared_ptr<Shader> AniShader = Resources::Find<Shader>(L"AtlasShader");
		std::shared_ptr<Shader> EftShader = Resources::Find<Shader>(L"EffectAtlasShader");
		std::shared_ptr<Shader> VerticalAniShader = Resources::Find<Shader>(L"VerticalInverterAtlasShader");
		std::shared_ptr<Shader> VerticalAniEftShdaer = Resources::Find<Shader>(L"VerticalInverterEftAtlasShader");
		std::shared_ptr<GameObject> circleEft = ObjectPoolManager<WarningObjectPool, GameObject>::GetInstance()->Spawn(L"ChangeSizeOverTimeEftObject");
		std::shared_ptr<GameObject> circleEft2 = ObjectPoolManager<WarningObjectPool, GameObject>::GetInstance()->Spawn(L"ChangeSizeOverTimeEftObject");
		circleEft->SetName(L"AntiGravityCircleEftObj");
		circleEft2->SetName(L"AntiGravityCircleEftObj2");
		std::shared_ptr<Texture> eftTexture = npk->CreateAtlas(L"magiccircle-aura3.img", 0, 2, L"mage_antiGravity_circle-aura3");
		ani = circleEft->GetComponent<Animator>();
		ani->Create(eftTexture, L"mage_antiGravity_circle-aura3", 0, 1, 0.0f);
		ani->PlayAnimation(L"mage_antiGravity_circle-aura3");

		std::shared_ptr<ChangeSizeOverTime> cso = circleEft->GetComponent<ChangeSizeOverTime>();
		cso->SetOffset(Vector3::Zero);
		cso->SetAlphaType(EAlphaType::FadeOut);
		cso->SetAlphaOffset(0.15f);
		cso->EndTime(1.0f);
		cso->SetEndEvent() = std::bind(&AntiGravity::DeSpawnCircle, this, circleEft);
		cso->SetActive(true);

		Vector3 pos = caster->GetComponent<Transform>()->position;
		std::shared_ptr<Transform> tf = circleEft->GetComponent<Transform>();
		tf->scale = Vector3(8.0f, 8.0f, 1.0f);
		tf->position = Vector3(-pos.x-0.6, pos.y+4.5f, 0.0f);

	
		ani = circleEft2->GetComponent<Animator>();
		ani->Create(eftTexture, L"mage_antiGravity_circle-aura3", 1, 2, 0.0f);
		ani->PlayAnimation(L"mage_antiGravity_circle-aura3");

		cso = circleEft2->GetComponent<ChangeSizeOverTime>();
		cso->SetOffset(Vector3::Zero);
		cso->SetAlphaType(EAlphaType::FadeOut);
		cso->SetAlphaOffset(0.15f);
		cso->EndTime(1.0f);
		cso->SetEndEvent() = std::bind(&AntiGravity::DeSpawnCircle, this, circleEft2);
		cso->SetActive(true);

		tf = circleEft2->GetComponent<Transform>();
		tf->scale = Vector3(8.0f, 8.0f, 1.0f);
		tf->position = Vector3(-pos.x+0.5f ,3.0f, 0.0f);

		std::shared_ptr<MeshRenderer> mesh = circleEft->GetComponent<MeshRenderer>();
		mesh->material->shader = VerticalAniEftShdaer;
		mesh = circleEft2->GetComponent<MeshRenderer>();
		mesh->material->shader = EftShader;

		caster->AddChild(circleEft);
		caster->AddChild(circleEft2);
	}
	void AntiGravity::CreateFamiliarEft(std::shared_ptr<GameObject> caster)
	{
		std::shared_ptr<Shader> AniShader = Resources::Find<Shader>(L"AtlasShader");
		std::shared_ptr<Shader> EftShader = Resources::Find<Shader>(L"EffectAtlasShader");
		std::shared_ptr<Shader> VerticalAniShader = Resources::Find<Shader>(L"VerticalInverterAtlasShader");
		std::shared_ptr<Shader> VerticalAniEftShdaer = Resources::Find<Shader>(L"VerticalInverterEftAtlasShader");

		Vector3 pos = caster->GetComponent<Transform>()->position;
		std::shared_ptr<GameObject> eft = ObjectPoolManager<AnimationObjectPool, GameObject>::GetInstance()->Spawn(L"AniEftObject");
		std::shared_ptr<NPK> npk = Resources::Find<NPK>(L"mage_familiar");
		std::shared_ptr<Texture> Texture = npk->CreateAtlas(L"hit01d.img", 0, 21, L"mage_antiGravity_familiar_blackcat_eft");
		eft->SetName(L"FamiliarEftObj");
		std::shared_ptr<Animator> ani = eft->GetComponent<Animator>();
		ani->Create(Texture, L"mage_antiGravity_familiar_blackcat_eft", 0, 21, 0.1f);
		ani->PlayAnimation(L"mage_antiGravity_familiar_blackcat_eft",false);
		ani->CompleteEvent(L"mage_antiGravity_familiar_blackcat_eft") = std::bind(&AntiGravity::DeSpawnFamiliarEft, this);
		std::shared_ptr<Transform> tf = eft->GetComponent<Transform>();
		tf->position = pos;
		tf->scale = Vector3(0.5f, 0.5f, 1.0f);

		std::shared_ptr<GameObject> eft2 = ObjectPoolManager<AnimationObjectPool, GameObject>::GetInstance()->Spawn(L"AniObject");
		Texture = npk->CreateAtlas(L"particlea.img", 0, 15, L"mage_antiGravity_familiar_blackcat_eft2");
		eft2->SetName(L"FamiliarEftObj2");
		ani = eft2->GetComponent<Animator>();
		ani->Create(Texture, L"mage_antiGravity_familiar_blackcat_eft2", 0, 15, 0.1f);
		ani->PlayAnimation(L"mage_antiGravity_familiar_blackcat_eft2", false);
		std::shared_ptr<Animation> animation = ani->FindAnimation(L"mage_antiGravity_familiar_blackcat_eft2");
		animation->RegisterFrameEvent(L"CreateFamiliar", 2);
		ani->SetFrameEventListener(this);
		
		tf = eft2->GetComponent<Transform>();
		tf->position = pos;
		std::shared_ptr<MeshRenderer> mesh = eft->GetComponent<MeshRenderer>();
		mesh->material->shader = EftShader;
		mesh = eft2->GetComponent<MeshRenderer>();
		mesh->alpha = 0.8f;
		mesh->material->shader = AniShader;
		

		Scene* Active = SceneManager::GetActiveScene();
		Active->AddGameObject(ELayerType::BackObject, eft);
		Active->AddGameObject(ELayerType::BackObject, eft2);
	}
	void AntiGravity::CreateFamiliar(Vector3 pos)
	{
		DeSpawnFamiliarEft();
		std::shared_ptr<NPK> npk = Resources::Find<NPK>(L"mage_familiar");
		std::shared_ptr<GameObject> eft = ObjectPoolManager<WarningObjectPool, GameObject>::GetInstance()->Spawn(L"ChangeSizeOverTimeObject");
		std::shared_ptr<Texture> Texture= npk->CreateAtlas(L"great_n.img", 0, 2, L"mage_antiGravity_familiar_blackcat_eft3");
		eft->SetName(L"FamiliarEftObj3");
		std::shared_ptr<Animator>ani = eft->GetComponent<Animator>();
		ani->Create(Texture, L"mage_antiGravity_familiar_blackcat_eft3", 0, 2, 0.1f);
		ani->PlayAnimation(L"mage_antiGravity_familiar_blackcat_eft3", true);

		std::shared_ptr<Transform> tf = eft->GetComponent<Transform>();
		tf->position = pos;
		tf->scale = Vector3(0.25f, 0.25f, 1.0f);

		Time::CallBackTimerInfo callBack = {};
		callBack.endTime = 1.0f;
		Time::RequestEvent(callBack, std::bind(&AntiGravity::DeSpawnFamiliar,this,eft));
		

		Scene* Active = SceneManager::GetActiveScene();
		Active->AddGameObject(ELayerType::BackObject, eft);
	}
	void AntiGravity::DeSpawnCircle(std::shared_ptr<GameObject> caster)
	{
		caster->active = GameObject::EState::Dead;
	}
	void AntiGravity::DeSpawnFamiliarEft()
	{
		Scene* Active = SceneManager::GetActiveScene();
		std::shared_ptr<GameObject> Object = Active->FindGameObject(ELayerType::BackObject, L"FamiliarEftObj");
		std::shared_ptr<Animator> ani = Object->GetComponent<Animator>();
		ani->ActiveAnimationNull();
		Object->active = GameObject::EState::Dead;

		Object = Active->FindGameObject(ELayerType::BackObject, L"FamiliarEftObj2");
		ani->ActiveAnimationNull();
		Object->active = GameObject::EState::Dead;
		
	}
	void AntiGravity::DeSpawnFamiliar(std::shared_ptr<GameObject> caster)
	{
		std::shared_ptr<ChangeSizeOverTime> cso = caster->GetComponent<ChangeSizeOverTime>();
		cso->SetOffset(Vector3::Zero);
		cso->SetAlphaType(EAlphaType::FadeOut);
		cso->SetAlphaOffset(0.01f);
		cso->EndTime(1.0f);
		cso->SetEndEvent() = std::bind(&AntiGravity::DeSpawnCircle, this, caster);
		cso->SetActive(true);
	}
}