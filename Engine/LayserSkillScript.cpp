#include "LayserSkillScript.h"

#include "AnimationObjectPool.h"
#include "CollisionManager.h"
#include "SceneManager.h"

#include "HitBoxScript.h"
#include "Collider2D.h"
namespace roka
{
	LayserSkillScript::LayserSkillScript() :SkillScript(EScriptType::SkillLayser)
		, mLayserSize(Vector3::Zero)
		, mLayserSpawnPos(Vector3::Zero)
	{
	}
	LayserSkillScript::LayserSkillScript(EScriptType type) : SkillScript(type)
		, mLayserSize(Vector3::Zero)
		, mLayserSpawnPos(Vector3::Zero)
	{
	}
	LayserSkillScript::LayserSkillScript(const LayserSkillScript& ref)
	{
		mLayserSize = ref.mLayserSize;
		mLayserSpawnPos = ref.mLayserSpawnPos;
	}
	void LayserSkillScript::Copy(Component* src)
	{
		LayserSkillScript* source = dynamic_cast<LayserSkillScript*>(src);
		if (source == nullptr)
			return;

		mLayserSize = source->mLayserSize;
		mLayserSpawnPos = source->mLayserSpawnPos;
	}
	LayserSkillScript::~LayserSkillScript()
	{
		if (mLayserObj != nullptr)
		{
			owner->RemoveChild(mLayserObj);
			mLayserObj.reset();
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
		pool::AnimationObjectPool* AniPool = pool::AnimationObjectPool::GetInstance();
		mLayserObj = AniPool->GetPool(L"ColAniEftObject")->Spawn();
		owner->AddChild(mLayserObj);
		mLayserObj->layer_type = ELayerType::Skill;

		mStunType = EStunState::HardStagger;

		std::shared_ptr<HitBoxScript> hitBox = mLayserObj->GetComponent<HitBoxScript>();
		hitBox->hitbox = HitBoxScript::EHitBoxType::Top;
		hitBox->hitbox_owner = owner->GetSharedPtr();
	}
	void LayserSkillScript::Exit()
	{
		SkillScript::Exit();
		std::shared_ptr<Collider2D> skill = mLayserObj->GetComponent<Collider2D>();
		std::shared_ptr<GameObject> playerObj = SceneManager::GetActiveScene()->FindGameObject(ELayerType::Player, L"Player");
		if (playerObj == nullptr)
			return;
		std::vector<std::shared_ptr<Collider2D>> vec = playerObj->GetChilds<Collider2D>();

		for (auto player : vec)
		{
			CollisionManager::DisableCollision(skill, player);
		}
	
		owner->RemoveChild(mLayserObj);
		mLayserObj.reset();
	}
}