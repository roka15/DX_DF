#include "TairangSkill01.h"

#include "GameObject.h"
#include "RokaTime.h"
#include "AnimationObjectPool.h"
#include "WarningObjectPool.h"
#include "SceneManager.h"
#include "CollisionManager.h"

#include "Transform.h"
#include "Animator.h"
#include "Collider2D.h"
#include "MeshRenderer.h"
#include "TairangMonsterScript.h"
#include "TargetMoveScript.h"
#include "WarningScript.h"
#include "PlayerScript.h"
#include "Resources.h"

namespace roka
{
	void TairangSkill01::Execute(std::shared_ptr<GameObject> caster)
	{
		std::shared_ptr<MonsterScript> monster = caster->GetComponent<MonsterScript>();
		std::shared_ptr<Animator> ani = caster->GetComponent<Animator>();
		std::shared_ptr<Animation> animation = ani->FindAnimation(L"Skill01_Start");

		mSpawnflag = false;
		ani->PlayAnimation(L"Skill01_Start", false);
		ani->SetFrameEventListener(this);
		monster->DisableNextState();

		CreateWarning(caster);

	}

	void TairangSkill01::SpawnEffect(std::shared_ptr<GameObject> caster, std::wstring key)
	{
		AnimationObjectPool* pool = ObjectPoolManager<AnimationObjectPool, GameObject>::GetInstance();
		std::shared_ptr<Transform> tirangtf = caster->GetComponent<Transform>();
		Vector3 tirangPos = tirangtf->position;
		Vector3 tirangScale = tirangtf->scale;
		std::shared_ptr<MonsterScript> monster = caster->GetComponent<MonsterScript>();
		EDir4Type dir = monster->GetDir();
		if (mSpawnflag == true)
			return;
		if (key.compare(L"Effect1") == 0)
		{
			std::shared_ptr<GameObject> Eft01 = pool->Spawn(L"AniEftObject");
			{
				std::shared_ptr<Transform> tf = Eft01->GetComponent<Transform>();
				tf->position = -tirangPos;
				tf->scale = tirangScale;
				std::shared_ptr<Animator> ani = Eft01->GetComponent<Animator>();
				ani->Create(L"tairnag_eft", L"attack3slashglow.img", L"tairang_skill1glow", 0, 12, 0.05f);
				MeshRenderer* meshRenderer = Eft01->GetComponent<MeshRenderer>().get();
				ani->CompleteEvent(L"tairang_skill1glow") = std::bind([meshRenderer]()->void {meshRenderer->is_active = false; });
				ani->PlayAnimation(L"tairang_skill1glow", false);
			}
			std::shared_ptr<GameObject> Eft02 = pool->Spawn(L"AniEftObject");
			{
				std::shared_ptr<Transform> tf = Eft02->GetComponent<Transform>();
				tf->position = -tirangPos;
				tf->scale = tirangScale;
				std::shared_ptr<Animator> ani = Eft02->GetComponent<Animator>();
				ani->Create(L"tairnag_eft", L"attack3trail.img", L"tairang_skill1trail", 0, 12, 0.05f);
				MeshRenderer* meshRenderer = Eft02->GetComponent<MeshRenderer>().get();
				ani->CompleteEvent(L"tairang_skill1trail") = std::bind([meshRenderer]()->void {meshRenderer->is_active = false; });
				ani->PlayAnimation(L"tairang_skill1trail", false);
			}
		
			std::shared_ptr<GameObject> Eft03 = pool->Spawn(L"AniEftObject");
			{

				std::shared_ptr<Animator> ani = Eft03->GetComponent<Animator>();
				std::shared_ptr<Transform> tf = Eft03->GetComponent<Transform>();
				tf->position = -tirangPos + Vector3(-0.03f, -0.1f, 0.0f);
				tf->scale = Vector3(1.0f, 1.0f, 1.0f);

				ani->Create(L"tairnag_eft", L"attack3purppleglow.img", L"tairang_skill1purppleglow", 0, 6, 0.05f);
				MeshRenderer* meshRenderer = Eft03->GetComponent<MeshRenderer>().get();
				ani->CompleteEvent(L"tairang_skill1purppleglow") = std::bind([meshRenderer]()->void {meshRenderer->is_active = false; });
				ani->PlayAnimation(L"tairang_skill1purppleglow", false);
			}	
			std::shared_ptr<GameObject> Eft04 = pool->Spawn(L"AniEftObject");
			{
				std::shared_ptr<Animator> ani = Eft04->GetComponent<Animator>();
				std::shared_ptr<Transform> tf = Eft04->GetComponent<Transform>();
				tf->position = -tirangPos+Vector3(-0.1f, -0.11f, 0.0f);
				tf->scale = Vector3(1.0f, 1.0f, 1.0f);
				ani->Create(L"tairnag_eft", L"attack3purppleglow.img", L"tairang_skill1purppleglow", 0, 6, 0.05f);
				MeshRenderer* meshRenderer = Eft04->GetComponent<MeshRenderer>().get();
				ani->CompleteEvent(L"tairang_skill1purppleglow") = std::bind([meshRenderer]()->void {meshRenderer->is_active = false; });
				ani->PlayAnimation(L"tairang_skill1purppleglow", false);
			}
			std::shared_ptr<GameObject> Eft05 = pool->Spawn(L"AniEftObject");
			{
				std::shared_ptr<Animator> ani = Eft05->GetComponent<Animator>();
				std::shared_ptr<Transform> tf = Eft05->GetComponent<Transform>();
				tf->position = -tirangPos+Vector3(-0.19f, -0.13f, 0.0f);
				tf->scale = Vector3(1.0f, 1.0f, 1.0f);
				ani->Create(L"tairnag_eft", L"attack3purppleglow.img", L"tairang_skill1purppleglow", 0, 6, 0.05f);
				MeshRenderer* meshRenderer = Eft05->GetComponent<MeshRenderer>().get();
				ani->CompleteEvent(L"tairang_skill1purppleglow") = std::bind([meshRenderer]()->void {meshRenderer->is_active = false; });
				ani->PlayAnimation(L"tairang_skill1purppleglow", false);
			}
			std::shared_ptr<GameObject> Eft06 = pool->Spawn(L"AniEftObject");
			{
				std::shared_ptr<Animator> ani = Eft06->GetComponent<Animator>();
				std::shared_ptr<Transform> tf = Eft06->GetComponent<Transform>();
				tf->position = -tirangPos+ Vector3(-0.05f, -0.1f, 0.0f);
				tf->scale = Vector3(1.0f, 1.0f, 1.0f);
				ani->Create(L"tairnag_eft", L"attack3purppleglow.img", L"tairang_skill1purppleglow", 0, 6, 0.05f);
				MeshRenderer* meshRenderer = Eft06->GetComponent<MeshRenderer>().get();
				ani->CompleteEvent(L"tairang_skill1purppleglow") = std::bind([meshRenderer]()->void {meshRenderer->is_active = false; });
				ani->PlayAnimation(L"tairang_skill1purppleglow", false);
			}
			std::shared_ptr<GameObject> Eft07 = pool->Spawn(L"AniEftObject");
			{
				std::shared_ptr<Animator> ani = Eft07->GetComponent<Animator>();
				std::shared_ptr<Transform> tf = Eft07->GetComponent<Transform>();
				tf->position = -tirangPos+Vector3(-0.1f, -0.11f, 0.01f);
				tf->scale = Vector3(1.0f, 1.0f, 1.0f);
				ani->Create(L"tairnag_eft", L"attack3purppleglow.img", L"tairang_skill1purppleglow", 0, 6, 0.05f);
				MeshRenderer* meshRenderer = Eft07->GetComponent<MeshRenderer>().get();
				ani->CompleteEvent(L"tairang_skill1purppleglow") = std::bind([meshRenderer]()->void {meshRenderer->is_active = false; });
				ani->PlayAnimation(L"tairang_skill1purppleglow", false);
			}
			std::shared_ptr<GameObject> Eft08 = pool->Spawn(L"AniEftObject");
			{
				std::shared_ptr<Animator> ani = Eft08->GetComponent<Animator>();
				std::shared_ptr<Transform> tf = Eft08->GetComponent<Transform>();
				tf->position = -tirangPos+Vector3(-0.2f, -0.13f, 0.0f);
				tf->scale = Vector3(1.0f, 1.0f, 1.0f);
				ani->Create(L"tairnag_eft", L"attack3purppleglow.img", L"tairang_skill1purppleglow", 0, 6, 0.05f);
				MeshRenderer* meshRenderer = Eft08->GetComponent<MeshRenderer>().get();
				ani->CompleteEvent(L"tairang_skill1purppleglow") = std::bind([meshRenderer]()->void {meshRenderer->is_active = false; });
				ani->PlayAnimation(L"tairang_skill1purppleglow", false);
			}
			if (dir == EDir4Type::LEFT)
			{
				Eft01->GetComponent<MeshRenderer>()->material->shader = Resources::Find<Shader>(L"VerticalInverterEftAtlasShader");
				Eft02->GetComponent<MeshRenderer>()->material->shader = Resources::Find<Shader>(L"VerticalInverterEftAtlasShader");
				Eft03->GetComponent<MeshRenderer>()->material->shader = Resources::Find<Shader>(L"VerticalInverterEftAtlasShader");
				Eft04->GetComponent<MeshRenderer>()->material->shader = Resources::Find<Shader>(L"VerticalInverterEftAtlasShader");
				Eft05->GetComponent<MeshRenderer>()->material->shader = Resources::Find<Shader>(L"VerticalInverterEftAtlasShader");
				Eft06->GetComponent<MeshRenderer>()->material->shader = Resources::Find<Shader>(L"VerticalInverterEftAtlasShader");
				Eft07->GetComponent<MeshRenderer>()->material->shader = Resources::Find<Shader>(L"VerticalInverterEftAtlasShader");
				Eft08->GetComponent<MeshRenderer>()->material->shader = Resources::Find<Shader>(L"VerticalInverterEftAtlasShader");
			}
			else
			{
				Eft01->GetComponent<MeshRenderer>()->material->shader = Resources::Find<Shader>(L"EffectAtlasShader");
				Eft02->GetComponent<MeshRenderer>()->material->shader = Resources::Find<Shader>(L"EffectAtlasShader");
				Eft03->GetComponent<MeshRenderer>()->material->shader = Resources::Find<Shader>(L"EffectAtlasShader");
				Eft04->GetComponent<MeshRenderer>()->material->shader = Resources::Find<Shader>(L"EffectAtlasShader");
				Eft05->GetComponent<MeshRenderer>()->material->shader = Resources::Find<Shader>(L"EffectAtlasShader");
				Eft06->GetComponent<MeshRenderer>()->material->shader = Resources::Find<Shader>(L"EffectAtlasShader");
				Eft07->GetComponent<MeshRenderer>()->material->shader = Resources::Find<Shader>(L"EffectAtlasShader");
				Eft08->GetComponent<MeshRenderer>()->material->shader = Resources::Find<Shader>(L"EffectAtlasShader");
			}
			Eft01->SetName(L"Eft01");
			Eft02->SetName(L"Eft02");
			Eft03->SetName(L"Eft03");
			Eft04->SetName(L"Eft04");
			Eft05->SetName(L"Eft05");
			Eft06->SetName(L"Eft06");
			Eft07->SetName(L"Eft07");
			Eft08->SetName(L"Eft08");

			caster->AddChild(Eft01);
			caster->AddChild(Eft02);
			caster->AddChild(Eft03);
			caster->AddChild(Eft04);
			caster->AddChild(Eft05);
			caster->AddChild(Eft06);
			caster->AddChild(Eft07);
			caster->AddChild(Eft08);
			
		}
		else if (key.compare(L"Effect2") == 0)
		{
			std::shared_ptr<GameObject> Eft01 = pool->Spawn(L"AniEftObject");
			{
				std::shared_ptr<Animator> ani = Eft01->GetComponent<Animator>();
				ani->Create(L"tairnag_eft", L"attack3line.img", L"tairang_skill1line", 0, 3, 0.08);
				ani->PlayAnimation(L"tairang_skill1line", false);

				std::shared_ptr<Transform> tf = Eft01->GetComponent<Transform>();
			
				tf->scale = tirangScale;
				tf->rotation = Vector3(0.0f, 0.0f, Deg2Rad(90));
				tf->position = -tirangPos +Vector3(-0.2f, 0.2f, 0.01f);

				MeshRenderer* meshRenderer = Eft01->GetComponent<MeshRenderer>().get();
				ani->CompleteEvent(L"tairang_skill1line") = std::bind([meshRenderer]()->void {meshRenderer->is_active = false; });
			}
			std::shared_ptr<GameObject> Eft02 = pool->Spawn(L"AniEftObject");
			{
				std::shared_ptr<Animator> ani = Eft02->GetComponent<Animator>();
				ani->Create(L"tairnag_eft", L"attack3booster.img", L"tairang_skill1booster", 0, 12, 0.08);
				ani->PlayAnimation(L"tairang_skill1booster", false);

				std::shared_ptr<Transform> tf = Eft02->GetComponent<Transform>();
				tf->scale = tirangScale;
				if (dir == EDir4Type::LEFT)
				{
					tf->position = -tirangPos + Vector3(-0.05f, 0.2f, 0.01f);
				}
				else
				tf->position = -tirangPos +Vector3(0.05f, 0.2f, 0.01f);

				MeshRenderer* meshRenderer = Eft02->GetComponent<MeshRenderer>().get();
				ani->CompleteEvent(L"tairang_skill1booster") = std::bind([meshRenderer]()->void {meshRenderer->is_active = false; });
			}
			std::shared_ptr<GameObject> Eft03 = pool->Spawn(L"AniEftObject");
			{
				std::shared_ptr<Animator> ani = Eft03->GetComponent<Animator>();
				ani->Create(L"tairnag_eft", L"abyssbombsmall.img", L"tairang_skill1abyss_explosion", 0, 12, 0.08);

				std::shared_ptr<Transform> tf = Eft03->GetComponent<Transform>();
				tf->scale = Vector3(1.0f, 1.0f, 1.0f);
				tf->position = -tirangPos;// +Vector3(0.0f, 0.4f, 0.01f);
			}/**/
			if (dir == EDir4Type::LEFT)
			{
				Eft01->GetComponent<MeshRenderer>()->material->shader = Resources::Find<Shader>(L"VerticalInverterEftAtlasShader");
				Eft02->GetComponent<MeshRenderer>()->material->shader = Resources::Find<Shader>(L"VerticalInverterEftAtlasShader");
				Eft03->GetComponent<MeshRenderer>()->material->shader = Resources::Find<Shader>(L"VerticalInverterEftAtlasShader");
			}
			else
			{
				Eft01->GetComponent<MeshRenderer>()->material->shader = Resources::Find<Shader>(L"EffectAtlasShader");
				Eft02->GetComponent<MeshRenderer>()->material->shader = Resources::Find<Shader>(L"EffectAtlasShader");
				Eft03->GetComponent<MeshRenderer>()->material->shader = Resources::Find<Shader>(L"EffectAtlasShader");
			}
			Eft01->SetName(L"Eft09");
			Eft02->SetName(L"Eft10");
			Eft03->SetName(L"Eft11");/**/
			caster->AddChild(Eft01);
			caster->AddChild(Eft02);
			caster->AddChild(Eft03);/**/
		}
		else if (key.compare(L"Effect2_2") == 0)
		{
			caster->GetChild(L"Eft11")->GetComponent<Animator>()->PlayAnimation(L"tairang_skill1abyss_explosion", false);
		}
		else if (key.compare(L"Effect3") == 0)
		{
			std::shared_ptr<GameObject> Eft01 = pool->Spawn(L"AniObject");
			{
				std::shared_ptr<Animator> ani = Eft01->GetComponent<Animator>();
				ani->Create(L"tairnag_eft", L"lightning01a.img", L"tairang_skill1lightning", 0, 9, 0.08);
				ani->PlayAnimation(L"tairang_skill1lightning", false);
				MeshRenderer* meshRenderer = Eft01->GetComponent<MeshRenderer>().get();
				meshRenderer->is_active = true;
				ani->CompleteEvent(L"tairang_skill1lightning") = std::bind([meshRenderer]()->void {meshRenderer->is_active = false; });

				std::shared_ptr<Transform> tf = Eft01->GetComponent<Transform>();
				tf->scale = Vector3(1.0f, tirangScale.y, 1.0f);
				tf->position = -tirangPos;//+Vector3(0.0f, -0.05f, 0.0f);
			}
			std::shared_ptr<GameObject> Eft02 = pool->Spawn(L"AniObject");
			{
				std::shared_ptr<Animator> ani = Eft02->GetComponent<Animator>();
				ani->Create(L"tairnag_eft", L"abyssbombmiddlen.img", L"tairang_skill1abyssBomb", 0, 20, 0.01);
				ani->PlayAnimation(L"tairang_skill1abyssBomb", false);
				MeshRenderer* meshRenderer = Eft02->GetComponent<MeshRenderer>().get();
				ani->CompleteEvent(L"tairang_skill1abyssBomb") = std::bind([meshRenderer]()->void {meshRenderer->is_active = false; });

				std::shared_ptr<Transform> tf = Eft02->GetComponent<Transform>();
				tf->scale = Vector3(tirangScale.x* 0.8f, tirangScale.y*0.25f, 1.0f);
				tf->position = -tirangPos +Vector3(0.0f, -0.2f, 0.0f);
			}
			std::shared_ptr<GameObject> Eft03 = pool->Spawn(L"AniObject");
			{
				std::shared_ptr<Animator> ani = Eft03->GetComponent<Animator>();
				ani->Create(L"tairnag_eft", L"jump_dust04.img", L"tairang_skill1dust", 0, 8, 0.01);
				ani->PlayAnimation(L"tairang_skill1dust", false);
				MeshRenderer* meshRenderer = Eft03->GetComponent<MeshRenderer>().get();
				ani->CompleteEvent(L"tairang_skill1dust") = std::bind([meshRenderer]()->void {meshRenderer->is_active = false; });

				std::shared_ptr<Transform> tf = Eft03->GetComponent<Transform>();
				tf->scale = tirangScale;
				tf->position = -tirangPos;
			}
			std::shared_ptr<GameObject> Eft04 = pool->Spawn(L"AniObject");
			{
				std::shared_ptr<Animator> ani = Eft04->GetComponent<Animator>();
				ani->Create(L"tairnag_eft", L"bolt01.img", L"tairang_skill1bolt", 0, 13, 0.05);
				ani->PlayAnimation(L"tairang_skill1bolt", false);
				MeshRenderer* meshRenderer = Eft04->GetComponent<MeshRenderer>().get();
				ani->CompleteEvent(L"tairang_skill1bolt") = std::bind([meshRenderer]()->void {meshRenderer->is_active = false; });

				std::shared_ptr<Transform> tf = Eft04->GetComponent<Transform>();
				tf->scale = tirangScale;
				tf->position = -tirangPos+ Vector3(-0.05f, -0.05f, 0.0f);
			}
			
			Eft01->SetName(L"Eft12");
			Eft02->SetName(L"Eft13");
			Eft03->SetName(L"Eft14");
			Eft04->SetName(L"Eft15");

			caster->AddChild(Eft01);
			caster->AddChild(Eft02);
			caster->AddChild(Eft03);
			caster->AddChild(Eft04);
		}

		mSpawnflag = true;
	}

	void TairangSkill01::DeSpawnEffect(std::shared_ptr<GameObject> caster, std::wstring key)
	{
		if (key.compare(L"Effect01") == 0)
		{
			caster->SetChildState(GameObject::EState::Dead, L"Eft01");
			caster->SetChildState(GameObject::EState::Dead, L"Eft02");
			caster->SetChildState(GameObject::EState::Dead, L"Eft03");
			caster->SetChildState(GameObject::EState::Dead, L"Eft04");
			caster->SetChildState(GameObject::EState::Dead, L"Eft05");
			caster->SetChildState(GameObject::EState::Dead, L"Eft06");
			caster->SetChildState(GameObject::EState::Dead, L"Eft07");
			caster->SetChildState(GameObject::EState::Dead, L"Eft08");
		}
		else if (key.compare(L"Effect02") == 0)
		{
			caster->SetChildState(GameObject::EState::Dead, L"Eft09");
			caster->SetChildState(GameObject::EState::Dead, L"Eft10");
			caster->SetChildState(GameObject::EState::Dead, L"Eft11");
		}
		else if (key.compare(L"Effect03") == 0)
		{
			caster->SetChildState(GameObject::EState::Dead, L"Eft12");
			caster->SetChildState(GameObject::EState::Dead, L"Eft13");
			caster->SetChildState(GameObject::EState::Dead, L"Eft14");
			caster->SetChildState(GameObject::EState::Dead, L"Eft15");
		}
		mSpawnflag = false;
	}

	void TairangSkill01::SpawnCollider(std::shared_ptr<GameObject> caster)
	{
		std::shared_ptr<GameObject> colObj = 
			ObjectPoolManager<AnimationObjectPool, GameObject>::GetInstance()->Spawn(L"ColAniObject");
		std::shared_ptr<WarningScript> wr = mWarningObj->GetComponent<WarningScript>();
		Vector3 pos = wr->GetPos();
		colObj->SetName(L"ColObject");
		colObj->layer_type = ELayerType::Monster;
		std::shared_ptr<Collider2D> collider = colObj->GetComponent<Collider2D>();
		collider->SetHitType(EHitBoxType::Bottom);
		//collider->SetCenter(Vector2(0.5f, -0.75f));
		std::shared_ptr<Transform> col_tf = colObj->GetComponent<Transform>();
		std::shared_ptr<Transform> tf = caster->GetComponent<Transform>();
		col_tf->position = pos + Vector3(0.0f, -0.75f, 0.0f);
		col_tf->scale = Vector3(1.5f, 0.5f, 1.0f);
		
		EnableCollision(colObj);
		SceneManager::GetActiveScene()->AddGameObject(ELayerType::Monster, colObj);
	}

	void TairangSkill01::DeSpawnCollider(std::shared_ptr<GameObject> caster)
	{
		std::shared_ptr<GameObject> obj = SceneManager::GetActiveScene()->FindGameObject(ELayerType::Monster, L"ColObject");
		if (obj == nullptr)
			return;
		obj->active = GameObject::EState::Dead;
		DisableCollision(obj);
	}

	void TairangSkill01::EnableCollision(std::shared_ptr<GameObject> caster)
	{
		std::shared_ptr<Collider2D> collider = caster->GetComponent<Collider2D>();
		collider->SetCollisionListener(this);
	}

	void TairangSkill01::DisableCollision(std::shared_ptr<GameObject> caster)
	{
		std::shared_ptr<Collider2D> collider = caster->GetComponent<Collider2D>();
		collider->SetCollisionListener(nullptr);
	}

	void TairangSkill01::Left(std::shared_ptr<GameObject> caster)
	{
	}

	void TairangSkill01::Right(std::shared_ptr<GameObject> caster)
	{
	}

	void TairangSkill01::Sound(std::wstring key)
	{
	}

	void TairangSkill01::End(std::shared_ptr<GameObject> caster)
	{
		std::shared_ptr<MonsterScript> monster = caster->GetComponent<MonsterScript>();
		monster->EnableNextState();

		DeSpawnEffect(caster, L"Effect3");
		DeSpawnCollider(caster);
	}

	void TairangSkill01::OnAnimationFramEvent(std::shared_ptr<GameObject> caster, std::wstring frameEvent)
	{
		std::shared_ptr<MonsterScript> monster = caster->GetComponent<MonsterScript>();
		std::shared_ptr<Animator> ani = caster->GetComponent<Animator>();
		if (frameEvent.compare(L"Effect1") == 0)
		{
			SpawnEffect(caster, frameEvent);
		}
		else if (frameEvent.compare(L"Effect2") == 0)
		{
			SpawnEffect(caster, frameEvent);
		}
		else if (frameEvent.compare(L"Effect3") == 0)
		{
			SpawnEffect(caster, frameEvent);
		}
		else if (frameEvent.compare(L"WarningObjStop") == 0)
		{
			//여기서의 caster 는 warning object 이다.
			WarningStop(caster);
		}
		else if (frameEvent.compare(L"NextMotion01") == 0)
		{
			Time::CallBackTimerInfo callBack = {};
			callBack.endTime = 1.0f;
			Time::RequestEvent(callBack, std::bind(&TairangSkill01::PlayMiddleMotion, this, caster));
		}
		else if (frameEvent.compare(L"NextMotion02") == 0)
		{
			DeSpawnEffect(caster,L"Effect2Disable");
			SpawnEffect(caster, L"Effect2_2");
			caster->GetComponent<MeshRenderer>()->is_active = false;
			Time::CallBackTimerInfo callBack = {};
			callBack.endTime = 4.0f;
			Time::RequestEvent(callBack, std::bind(&TairangSkill01::PlayEndMotion, this, caster));
		}
		else if (frameEvent.compare(L"EndEvent") == 0)
		{
			End(caster);
		}
	}

	void TairangSkill01::OnCollisionEnter(std::shared_ptr<GameObject> caster, std::shared_ptr<GameObject> target)
	{
		std::shared_ptr<PlayerScript> player = target->parent->GetComponent<PlayerScript>();
		if (player == nullptr)
			return;
		
		std::shared_ptr<Collider2D> caster_col = caster->GetComponent<Collider2D>();
		std::shared_ptr<Collider2D> target_col = target->GetComponent<Collider2D>();
		CollisionManager::DisableCollision(caster_col, target_col);

		EHitBoxType hitboxType = target_col->GetHitType();
		if (hitboxType != EHitBoxType::Bottom)
			return;
		player->BeAttacked(mDamage, EStunState::Down);
		DeSpawnCollider(caster);
	}

	void TairangSkill01::OnCollisionStay(std::shared_ptr<GameObject> caster, std::shared_ptr<GameObject> target)
	{
	}

	void TairangSkill01::OnCollisionExit(std::shared_ptr<GameObject> caster, std::shared_ptr<GameObject> target)
	{
	}

	void TairangSkill01::PlayMiddleMotion(std::shared_ptr<GameObject> caster)
	{
		std::shared_ptr<Animator> ani = caster->GetComponent<Animator>();
		ani->PlayAnimation(L"Skill01_Middle");
		ani->SetFrameEventListener(this);
		DeSpawnEffect(caster, L"Effect01");

		Jump(caster);
	}

	void TairangSkill01::PlayEndMotion(std::shared_ptr<GameObject> caster)
	{
		if (mWarningObj == nullptr)
			return;
		SpawnCollider(caster);
		caster->GetComponent<MeshRenderer>()->is_active = true;
		std::shared_ptr<WarningScript> wr = mWarningObj->GetComponent<WarningScript>();
		wr->SetTarget(nullptr);
		std::shared_ptr<Transform> tf = caster->GetComponent<Transform>();
		tf->position = (mWarningObj->GetComponent<WarningScript>()->GetPos());

		std::shared_ptr<Animator> ani = caster->GetComponent<Animator>();
		ani->PlayAnimation(L"Skill01_End");
		ani->SetFrameEventListener(this);
		DeSpawnEffect(caster, L"Effect02");
		DeleteWarning(caster);
	}

	void TairangSkill01::Jump(std::shared_ptr<GameObject> caster)
	{
		std::shared_ptr<TairangMonsterScript> monster = caster->GetComponent<TairangMonsterScript>();
		EDir4Type dir = monster->GetDir();
		Vector3 diff = Vector3(0.0f, -0.4f, 0.0f);
		Vector3 distance = Vector3(0.3f, 0.5f, 0.0f);
		float speed = 1.5f;
		std::shared_ptr<Transform> tf = caster->GetComponent<Transform>();
		Vector3 CurPos = tf->position + diff;
		tf->position = CurPos;
		Vector3 TargetPos = {};
		switch (dir)
		{
		case EDir4Type::LEFT:
			TargetPos.x = CurPos.x - distance.x;
			TargetPos.y = CurPos.y + distance.y;
			break;
		case EDir4Type::RIGHT:
			TargetPos.x = CurPos.x + distance.x;
			TargetPos.y = CurPos.y + distance.y;
			break;
		}

		std::shared_ptr<TargetMoveScript> targetMove = caster->GetComponent<TargetMoveScript>();
		targetMove->SetSpeed(speed);
		targetMove->SetDirX(distance.x);
		targetMove->SetDirY(distance.y);
		targetMove->SetTargetPos(Vector2(TargetPos.x, TargetPos.y));
	}

	void TairangSkill01::WarningStop(std::shared_ptr<GameObject> caster)
	{
		std::shared_ptr<Animator> ani = caster->GetComponent<Animator>();
		ani->Stop();
		Time::CallBackTimerInfo callBack = {};
		callBack.endTime = 5.5f;
		Time::RequestEvent(callBack, std::bind(&TairangSkill01::WarningPlay, this, caster));
	}

	void TairangSkill01::WarningPlay(std::shared_ptr<GameObject> caster)
	{
		caster->GetComponent<Animator>()->Play();
	}

	void TairangSkill01::CreateWarning(std::shared_ptr<GameObject> caster)
	{
		std::shared_ptr<MonsterScript> monster = caster->GetComponent<MonsterScript>();
		Scene* ActiveScene = SceneManager::GetActiveScene();
		WarningObjectPool* pool = ObjectPoolManager<WarningObjectPool, GameObject>::GetInstance();
		mWarningObj = pool->Spawn(L"WarningObject");
		std::shared_ptr<Animator> wani = mWarningObj->GetComponent<Animator>();
		wani->Create(L"warning", L"warningfloor_circle500.img", L"ellipse_warning1", 0, 12, 0.1f);
		wani->PlayAnimation(L"ellipse_warning1", false);
		std::shared_ptr<Animation> animation = wani->FindAnimation(L"ellipse_warning1");
		animation->RegisterFrameEvent(L"WarningObjStop", 5);
		animation->RegisterFrameEvent(L"WarningObjDelete", 11);
		wani->SetFrameEventListener(this);

		std::shared_ptr<WarningScript> wr = mWarningObj->GetComponent<WarningScript>();
		wr->SetWarningSize(Vector3(2.5f, 2.0f, 1.0f));
		wr->SetWarningCenter(Vector3(0.0f, -0.32f, 0.0f));
		wr->SetTarget(monster->GetTarget());
		wr->SetActiveTime(1.0);

		ActiveScene->AddGameObject(ELayerType::BackObject, mWarningObj);
	}

	void TairangSkill01::DeleteWarning(std::shared_ptr<GameObject> caster)
	{
		Scene* ActiveScene = SceneManager::GetActiveScene();
		mWarningObj->active = GameObject::EState::Dead;
		mWarningObj.reset();
	}

	void TairangSkill01::Release()
	{
		mWarningObj.reset();
	}

}
