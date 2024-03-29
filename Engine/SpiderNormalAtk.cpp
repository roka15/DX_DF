#include "SpiderNormalAtk.h"

#include "GameObject.h"
#include "NPK.h"
#include "Resources.h"
#include "CollisionManager.h"

#include "Animator.h"
#include "MeshRenderer.h"

#include "GameObject.h"
#include "AnimationObjectPool.h"

#include "Collider2D.h"
#include "SpiderMonsterScript.h"
#include "PlayerScript.h"
namespace roka
{
	SpiderNormalAtk::SpiderNormalAtk(const UINT& damage) :Skill(damage)
	{
	}

	SpiderNormalAtk::~SpiderNormalAtk()
	{
	}

	void SpiderNormalAtk::Execute(std::shared_ptr<GameObject> caster)
	{
		std::shared_ptr<MonsterScript> monster = caster->GetComponent<MonsterScript>();
		std::shared_ptr<Animator> ani = caster->GetComponent<Animator>();
		ani->PlayAnimation(L"Skill01", false);
		ani->SetFrameEventListener(this);
		monster->DisableNextState();
	}

	void SpiderNormalAtk::SpawnEffect(std::shared_ptr<GameObject> caster, std::wstring key)
	{
		std::shared_ptr<MonsterScript> monster = caster->GetComponent<MonsterScript>();
		std::shared_ptr<GameObject> Effect = monster->owner->GetChild(key);
		if (Effect != nullptr)
			return;
		
		Effect = manager::ObjectPoolManager<AnimationObjectPool, GameObject>::GetInstance()->Spawn(L"ColAniEftObject");
		Effect->SetName(key);
		Effect->layer_type = ELayerType::Monster;
		std::shared_ptr<Transform> tf = caster->GetComponent<Transform>();
		std::shared_ptr<MeshRenderer> mesh = Effect->GetComponent<MeshRenderer>();
		std::shared_ptr<Animator> ani = Effect->GetComponent<Animator>();
		std::shared_ptr<Texture> texture = Resources::Find<Texture>(L"LaserEft01AtlasTexture");
		if (texture == nullptr)
		{
			std::shared_ptr<NPK> npk = Resources::Find<NPK>(L"monster_eft");
			texture = npk->CreateAtlas(L"laser009_eft.img", 0, 19, L"LaserEft01");
		}
		ani->Create(texture, L"LaserEft", 0, 20, 0.1f);
		ani->PlayAnimation(L"LaserEft", false);
		std::shared_ptr<Transform> transform = Effect->GetComponent<Transform>();
		Vector3 pos = tf->position;
		transform->scale = Vector3(8.0f, 0.5f, 1.0f);
		EDir4Type dir = monster->GetDir();
		switch (dir)
		{
		case EDir4Type::LEFT:
			transform->position = -pos + Vector3(-2.0f, 0.025f, 0.8f);
			break;
		case EDir4Type::RIGHT:
			transform->position = -pos + Vector3(2.0f, 0.025f, 0.8f);
			break;
		}
		caster->AddChild(Effect);
	}

	void SpiderNormalAtk::DeSpawnEffect(std::shared_ptr<GameObject> caster, std::wstring key)
	{
		std::shared_ptr<GameObject> colObj = caster->GetChild(key);
		if (colObj == nullptr)
			return;
		std::shared_ptr<Collider2D> collider = colObj->GetComponent<Collider2D>();
		collider->SetCollisionListener(nullptr);
		colObj->active = GameObject::EState::Dead;
	}

	void SpiderNormalAtk::SpawnCollider(std::shared_ptr<GameObject> caster)
	{
		std::shared_ptr<GameObject> colObj = caster->GetChild(L"LayserObject");
		if (colObj == nullptr)
			return;
		std::shared_ptr<Collider2D> collider = colObj->GetComponent<Collider2D>();
		collider->SetCollisionListener(this);
		collider->EnableColCheck();
		collider->SetHitType(EHitBoxType::Top);
		std::shared_ptr<MonsterScript> monster = caster->GetComponent<MonsterScript>();

		EDir4Type dir = monster->GetDir();
		std::shared_ptr<Transform> spiderTf = caster->GetComponent<Transform>();
		Vector3 pos = spiderTf->position;
		Vector3 scale = spiderTf->scale;

		std::shared_ptr<Transform> transform = collider->owner->GetComponent<Transform>();
		

		Vector2 colCenter = collider->center;

		switch (dir)
		{
		case EDir4Type::LEFT:
			colCenter.x = -0.1f;
			break;
		case EDir4Type::RIGHT:
			colCenter.x = 0.1f;
			break;
		}

		colCenter.y = 0.0f;
		collider->center = colCenter;
		collider->size = Vector2(1.0f, 0.1f);
	}

	void SpiderNormalAtk::DeSpawnCollider(std::shared_ptr<GameObject> caster)
	{
		std::shared_ptr<GameObject> colObj = caster->GetChild(L"LayserObject");
		if (colObj == nullptr)
			return;
		std::shared_ptr<Collider2D> collider = colObj->GetComponent<Collider2D>();
		collider->DisableColCheck();
	}

	void SpiderNormalAtk::EnableCollision(std::shared_ptr<GameObject> caster)
	{
	}

	void SpiderNormalAtk::DisableCollision(std::shared_ptr<GameObject> caster)
	{
	}

	void SpiderNormalAtk::Left(std::shared_ptr<GameObject> caster)
	{
	}

	void SpiderNormalAtk::Right(std::shared_ptr<GameObject> caster)
	{
	}

	void SpiderNormalAtk::Sound(std::wstring key)
	{
	}

	void SpiderNormalAtk::End(std::shared_ptr<GameObject> caster)
	{
		std::shared_ptr<MonsterScript> monster = caster->GetComponent<MonsterScript>();
		monster->EnableNextState();
	}

	void SpiderNormalAtk::OnAnimationFramEvent(std::shared_ptr<GameObject> caster, std::wstring frameEvent)
	{
		if (frameEvent.compare(L"SpawnEffect01")==0)
		{
			SpawnEffect(caster, L"LayserObject");
			SpawnCollider(caster);
		}
		else if (frameEvent.compare(L"DeSpawnEffect01")==0)
		{
			DeSpawnCollider(caster);
		
		}
		else if (frameEvent.compare(L"NextState") == 0)
		{
			End(caster);
			DeSpawnEffect(caster, L"LayserObject");
		}
	}

	void SpiderNormalAtk::OnCollisionEnter(std::shared_ptr<GameObject> caster, std::shared_ptr<GameObject> target)
	{
	}

	void SpiderNormalAtk::OnCollisionStay(std::shared_ptr<GameObject> caster, std::shared_ptr<GameObject> target)
	{
		std::shared_ptr<MonsterScript> monster = caster->GetComponent<MonsterScript>();
		std::shared_ptr<PlayerScript> player = target->parent->GetComponent<PlayerScript>();
		std::shared_ptr<Collider2D> player_collider = target->GetComponent<Collider2D>();
		if (player_collider->GetHitType() == EHitBoxType::Top)
		{
			player->BeAttacked(mDamage, EStunState::HardStagger);
		}
	}

	void SpiderNormalAtk::OnCollisionExit(std::shared_ptr<GameObject> caster, std::shared_ptr<GameObject> target)
	{
		int a = 0;
	}
	void SpiderNormalAtk::Release()
	{
	}
}
