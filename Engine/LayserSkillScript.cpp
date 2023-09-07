#include "LayserSkillScript.h"

#include "AnimationObjectPool.h"
#include "CollisionManager.h"
#include "SceneManager.h"

#include "HitBoxScript.h"
#include "Collider2D.h"
namespace roka
{
	LayserSkillScript::LayserSkillScript() :SkillScript(EScriptType::SkillLayser)
	{
	}
	LayserSkillScript::LayserSkillScript(EScriptType type) : SkillScript(type)
	{
	}
	LayserSkillScript::LayserSkillScript(const LayserSkillScript& ref)
	{
	}
	void LayserSkillScript::Copy(Component* src)
	{
		LayserSkillScript* source = dynamic_cast<LayserSkillScript*>(src);
		if (source == nullptr)
			return;
	}
	LayserSkillScript::~LayserSkillScript()
	{
		if (mColObj != nullptr)
		{
			owner->RemoveChild(mColObj);
			mColObj.reset();
		}
	}
	void LayserSkillScript::Initialize()
	{
	}
	void LayserSkillScript::Update()
	{
	}
	void LayserSkillScript::LateUpdate()
	{
	}
	void LayserSkillScript::Render()
	{
	}
	void LayserSkillScript::Play()
	{
		SkillScript::Play();
	}
	void LayserSkillScript::Exit()
	{
		SkillScript::Exit();
		std::shared_ptr<Collider2D> skill = mColObj->GetComponent<Collider2D>();
		std::shared_ptr<GameObject> playerObj = SceneManager::GetActiveScene()->FindGameObject(ELayerType::Player, L"Player");
		if (playerObj == nullptr)
			return;
		std::vector<std::shared_ptr<Collider2D>> vec = playerObj->GetChilds<Collider2D>();

		for (auto player : vec)
		{
			CollisionManager::DisableCollision(skill, player);
		}
	
		owner->RemoveChild(mColObj);
		mColObj.reset();
	}
	void LayserSkillScript::CreateColliderObject()
	{
		pool::AnimationObjectPool* AniPool = pool::AnimationObjectPool::GetInstance();
		mColObj = AniPool->GetPool(L"ColAniEftObject")->Spawn();
		owner->AddChild(mColObj);
		mColObj->layer_type = ELayerType::Skill;

		mStunType = EStunState::HardStagger;

		std::shared_ptr<HitBoxScript> hitBox = mColObj->GetComponent<HitBoxScript>();
		hitBox->hitbox = HitBoxScript::EHitBoxType::Top;
		hitBox->hitbox_owner = owner->GetSharedPtr();
	}
}