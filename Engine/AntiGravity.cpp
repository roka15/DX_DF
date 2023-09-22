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
			std::shared_ptr<Animator> ani2 = Object->GetComponent<Animator>();
			ani2->ActiveAnimationNull();
			Object->active = GameObject::EState::Dead;

			Object = Active->FindGameObject(ELayerType::BackObject, L"AntiGravityCircleObj2");
			ani2 = Object->GetComponent<Animator>();
			ani2->ActiveAnimationNull();
			Object->active = GameObject::EState::Dead;
		}
		else if (key.compare(L"pluto_reverse") == 0)
		{
			Scene* Active = SceneManager::GetActiveScene();
			deleteObj =Active->FindGameObject(ELayerType::BackObject, L"plutoObj");
			ani = deleteObj->GetComponent<Animator>();
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
		
		std::shared_ptr<Shader> AniShader = Resources::Find<Shader>(L"AnimationShader");
		std::shared_ptr<Shader> EftShader = Resources::Find<Shader>(L"EffectAniShader");
		std::shared_ptr<Shader> VerticalAniShader = Resources::Find<Shader>(L"VerticalInverterAnimationShader");
		std::shared_ptr<Shader> VerticalAniEftShdaer = Resources::Find<Shader>(L"VerticalInverterEftAnimationShader");

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
			meshRenderer->material->shader = Resources::Find<Shader>(L"VerticalInverterAnimationShader");
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
		std::shared_ptr<Shader> AniShader = Resources::Find<Shader>(L"AnimationShader");
		std::shared_ptr<Shader> EftShader = Resources::Find<Shader>(L"EffectAniShader");
		std::shared_ptr<Shader> VerticalAniShader = Resources::Find<Shader>(L"VerticalInverterAnimationShader");
		std::shared_ptr<Shader> VerticalAniEftShdaer = Resources::Find<Shader>(L"VerticalInverterEftAnimationShader");

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
	}
	void AntiGravity::CreatePlutoEffect(std::shared_ptr<GameObject> caster, std::wstring key)
	{
		AnimationObjectPool* pool = ObjectPoolManager<AnimationObjectPool, GameObject>::GetInstance();
		std::shared_ptr<Transform> tf;
		Animator* aniPtr = nullptr;
		
		Vector3 offset = Vector3::Zero;
		Vector3 scale = Vector3::One;

		std::shared_ptr<Shader> AniShader = Resources::Find<Shader>(L"AnimationShader");
		std::shared_ptr<Shader> EftShader = Resources::Find<Shader>(L"EffectAniShader");
		std::shared_ptr<Shader> VerticalAniShader = Resources::Find<Shader>(L"VerticalInverterAnimationShader");
		std::shared_ptr<Shader> VerticalAniEftShdaer = Resources::Find<Shader>(L"VerticalInverterEftAnimationShader");

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

		std::shared_ptr<Shader> AniShader = Resources::Find<Shader>(L"AnimationShader");
		std::shared_ptr<Shader> EftShader = Resources::Find<Shader>(L"EffectAniShader");
		std::shared_ptr<Shader> VerticalAniShader = Resources::Find<Shader>(L"VerticalInverterAnimationShader");
		std::shared_ptr<Shader> VerticalAniEftShdaer = Resources::Find<Shader>(L"VerticalInverterEftAnimationShader");
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

		std::shared_ptr<Shader> AniShader = Resources::Find<Shader>(L"AnimationShader");
		std::shared_ptr<Shader> EftShader = Resources::Find<Shader>(L"EffectAniShader");
		std::shared_ptr<Shader> VerticalAniShader = Resources::Find<Shader>(L"VerticalInverterAnimationShader");
		std::shared_ptr<Shader> VerticalAniEftShdaer = Resources::Find<Shader>(L"VerticalInverterEftAnimationShader");
		std::shared_ptr<NPK> npk = Resources::Find<NPK>(L"mageAntiGravity");
		Vector3 plutoPos = SceneManager::GetActiveScene()->FindGameObject(ELayerType::BackObject, L"plutoObj")->GetComponent<Transform>()->position;
		Vector3 offset = Vector3(0.01f, -0.25f, 0.001f);
		std::shared_ptr<Texture> circleTexture = npk->CreateAtlas(L"magiccircle-normal.img", 0, 1, L"mage_antiGravity_circle-normal");
		
		std::shared_ptr<Animator> ani = circle->GetComponent<Animator>();
		ani->Create(circleTexture, L"mage_antiGravity_circle-normal", 0, 0, 0.0f);
		ani->PlayAnimation(L"mage_antiGravity_circle-normal");
		std::shared_ptr<ChangeSizeOverTime> change_size = circle->GetComponent<ChangeSizeOverTime>();
		change_size->SetOffset(Vector3(0.3f, 0.3f, 0.0f));
		change_size->EndTime(0.15);
	
		tf = circle->GetComponent<Transform>();
		tf->scale = Vector3(0.0f, 0.0f, 0.0f);
		tf->position = plutoPos+offset;
		tf->SetPivot(Vector3(1.0f, 0.5f, 0.0f));
		tf->EnablePivot();

		ani = circle2->GetComponent<Animator>();
		ani->Create(circleTexture, L"mage_antiGravity_circle-normal", 0, 0, 0.0f);
		ani->PlayAnimation(L"mage_antiGravity_circle-normal");
		change_size = circle2->GetComponent<ChangeSizeOverTime>();
		change_size->SetOffset(Vector3(0.3f, 0.3f, 0.0f));
		change_size->EndTime(0.15);
		
		tf = circle2->GetComponent<Transform>();
		tf->scale = Vector3(0.0f, 0.0f, 0.0f);
		tf->position = plutoPos+offset;
		tf->SetPivot(Vector3(0.0f, 0.5f, 0.0f));
		tf->EnablePivot();
		std::shared_ptr<MeshRenderer> mesh = circle2->GetComponent<MeshRenderer>();
		mesh->material->shader = VerticalAniEftShdaer;

		SceneManager::GetActiveScene()->AddGameObject(ELayerType::BackObject, circle);
		SceneManager::GetActiveScene()->AddGameObject(ELayerType::BackObject, circle2);
	}
}