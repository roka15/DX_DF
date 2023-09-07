#include "SpiderLayserSkillScript.h"

#include "GameObject.h"

#include "Animator.h"
#include "MeshRenderer.h"
#include "Collider2D.h"
#include "Transform.h"

#include "MonsterScript.h"
#include "PlayerScript.h"
#include "HitBoxScript.h"

#include "Resources.h"
#include "NPK.h"
#include "Texture.h"
#include "Sprite.h"
namespace roka
{
	SpiderLayserSkillScript::SpiderLayserSkillScript():LayserSkillScript(EScriptType::SkillSpiderLayser)
	{
	}
	SpiderLayserSkillScript::SpiderLayserSkillScript(const SpiderLayserSkillScript& ref)
	{
	}
	void SpiderLayserSkillScript::Copy(Component* src)
	{
	}
	void SpiderLayserSkillScript::Initialize()
	{
		std::shared_ptr<Animator> ani = owner->GetComponent<Animator>();
		ani->Create(L"monster", L"web_spider_z.img", L"web_spider_Skill1", 28, 46, 0.1f);
		
		std::shared_ptr<Animation> animation = ani->FindAnimation(L"web_spider_Skill1");
		Animation::AnimationEvent timeEvent = {};
		timeEvent.mNormalFunc = std::bind(&SpiderLayserSkillScript::CreateLayser, this);
		timeEvent.mTime = 1.3f;
		animation->AddTimeLineEvent(timeEvent);

		ani->CompleteEvent(L"web_spider_Skill1") = std::bind([this]()->void {
			Exit();
			});

		mStartKey = L"web_spider_Skill1";
	}
	void SpiderLayserSkillScript::Update()
	{
	}
	void SpiderLayserSkillScript::LateUpdate()
	{
	}
	void SpiderLayserSkillScript::Render()
	{
	}
	void SpiderLayserSkillScript::OnCollisionEnter(std::shared_ptr<Collider2D> other)
	{
		std::shared_ptr<HitBoxScript> hitbox = other->owner->GetComponent<HitBoxScript>();
		std::shared_ptr<GameObject> hitboxOwner = hitbox->hitbox_owner;
		if (hitboxOwner == nullptr)
			return;
		std::shared_ptr<PlayerScript> player = hitboxOwner->GetComponent<PlayerScript>();
		if (player == nullptr)
			return;

		float damage = 1;
		player->BeAttacked(damage, mStunType);
	}
	void SpiderLayserSkillScript::OnCollisionStay(std::shared_ptr<Collider2D> other)
	{
		std::shared_ptr<HitBoxScript> hitbox = other->owner->GetComponent<HitBoxScript>();
		std::shared_ptr<GameObject> hitboxOwner= hitbox->hitbox_owner;
		if (hitboxOwner == nullptr)
			return;
		std::shared_ptr<PlayerScript> player = hitboxOwner->GetComponent<PlayerScript>();
		if (player == nullptr)
			return;

		float damage = 1;
		player->BeAttacked(damage, mStunType);
	}
	void SpiderLayserSkillScript::OnCollisionExit(std::shared_ptr<Collider2D> other)
	{
		int a = 0;
	}
	void SpiderLayserSkillScript::Play()
	{
		LayserSkillScript::Play();
	}
	void SpiderLayserSkillScript::Exit()
	{
		LayserSkillScript::Exit();
	}
	void SpiderLayserSkillScript::Start()
	{
	}
	void SpiderLayserSkillScript::Middle()
	{
	}
	void SpiderLayserSkillScript::End()
	{
	}
	void SpiderLayserSkillScript::CreateLayser()
	{
		LayserSkillScript::CreateLayser();
		std::shared_ptr<GameObject> layser = mLayserObj;
		std::shared_ptr<Animator> OwnerAni = owner->GetComponent<Animator>();
		std::shared_ptr<MonsterScript> OwnerMonsterScript = owner->GetComponent<MonsterScript>();
		std::shared_ptr<Animation> start = OwnerAni->FindAnimation(mStartKey);
		std::shared_ptr<Animator> LayserAni = layser->GetComponent<Animator>();

		std::shared_ptr<NPK> npk = Resources::Find<NPK>(L"monster_eft");
		std::shared_ptr<Texture> texture = npk->CreateAtlas(L"laser009_eft.img", 0, 20, L"SkillspiderLayser");
		LayserAni->Create(texture, L"SkillspiderLayser", 0, 20, 0.1f);

		Animation::AnimationEvent AniEvent = {};
		//AniEvent.
		//start->AddTimeLineEvent()
		LayserAni->PlayAnimation(L"SkillspiderLayser", false);

		EDir4Type dirType = OwnerMonsterScript->GetDir();
		std::shared_ptr<Transform> layserTf = layser->GetComponent<Transform>();
		layserTf->scale = Vector3(5.0f, 0.25f, 1.0f);


		Vector2 center = Vector2::Zero;

		Vector3 pos = Vector3::Zero;
		switch (dirType)
		{
		case EDir4Type::LEFT:
			pos = Vector3(-2.25f, 0.025f, 0.0f);
			center.x = -3.0f;
			break;
		case EDir4Type::RIGHT:
			pos = Vector3(2.25f, 0.025f, 0.0f);
			center.x = 3.0f;
			break;
		}

		layserTf->position = pos;

		std::shared_ptr<Collider2D> layserCol = layser->GetComponent<Collider2D>();
		Vector2 colSize = layserCol->size;
		colSize.x = 1.5f;
		colSize.y = 0.05f;
		layserCol->size = colSize;

		Vector2 colCenter = layserCol->center;
		colCenter.x = center.x;
		colCenter.y = pos.y;
		layserCol->center = colCenter;
	}
}