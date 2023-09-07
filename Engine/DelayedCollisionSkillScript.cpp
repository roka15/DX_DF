#include "DelayedCollisionSkillScript.h"

#include "GameObject.h"
#include "AnimationObjectPool.h"
#include "SceneManager.h"
#include "RokaTime.h"

#include "Transform.h"
#include "Animator.h"
namespace roka
{
	DelayedCollisionSkillScript::DelayedCollisionSkillScript():SkillScript(EScriptType::SkillDelayCollider),
		mWarningFollowTime(0.0),
		mWarningEnableTime(0.0)
	{
	}
	DelayedCollisionSkillScript::DelayedCollisionSkillScript(EScriptType type):SkillScript(type),
		mWarningFollowTime(0.0),
		mWarningEnableTime(0.0)
	{
	}
	DelayedCollisionSkillScript::DelayedCollisionSkillScript(const DelayedCollisionSkillScript& ref):SkillScript(ref)
	{
		mWarningFollowTime = ref.mWarningFollowTime;
		mWarningEnableTime = 0.0;
	}
	void DelayedCollisionSkillScript::Copy(Component* src)
	{
		SkillScript::Copy(src);
		DelayedCollisionSkillScript* source = dynamic_cast<DelayedCollisionSkillScript*>(src);
		if (source == nullptr)
			return;
		mWarningFollowTime = source->mWarningFollowTime;
		mWarningEnableTime = 0.0;
	}
	void DelayedCollisionSkillScript::Initialize()
	{
	}
	void DelayedCollisionSkillScript::Update()
	{
		if (mWarningObj != nullptr)
		{
			mWarningEnableTime += Time::DeltaTime();
			if (mWarningFollowTime > mWarningEnableTime)
			{
				MoveWarningObject();
			}
		}
	}
	void DelayedCollisionSkillScript::LateUpdate()
	{
	}
	void DelayedCollisionSkillScript::Render()
	{
	}
	void DelayedCollisionSkillScript::Play()
	{
		SkillScript::Play();
		CreateWarningObject();
	}
	void DelayedCollisionSkillScript::Exit()
	{
		SkillScript::Exit();
		Scene* ActiveScene = SceneManager::GetActiveScene();
		ActiveScene->RemoveGameObject(ELayerType::Skill, mColObj);
		mColObj.reset();
	}
	void DelayedCollisionSkillScript::CreateColliderObject()
	{
		Scene* ActiveScene = SceneManager::GetActiveScene();
		pool::AnimationObjectPool* AniPool = pool::AnimationObjectPool::GetInstance();
		mColObj = AniPool->GetPool(L"ColAniEftObject")->Spawn();

		ActiveScene->AddGameObject(ELayerType::Skill,mColObj);
	}
	void DelayedCollisionSkillScript::CreateWarningObject()
	{
		mWarningEnableTime = 0.0;

		Scene* ActiveScene = SceneManager::GetActiveScene();
		pool::AnimationObjectPool* AniPool = pool::AnimationObjectPool::GetInstance();
		mWarningObj = AniPool->GetPool(L"AniObject")->Spawn();

		ActiveScene->AddGameObject(ELayerType::Skill, mWarningObj);
	}
	void DelayedCollisionSkillScript::DeleteWarningObject()
	{
		Scene* ActiveScene = SceneManager::GetActiveScene();
		ActiveScene->RemoveGameObject(ELayerType::Skill,mWarningObj);
		mWarningObj.reset();
	}
	void DelayedCollisionSkillScript::StopWarningAniEvent()
	{
		std::shared_ptr<Animator> ani = mWarningObj->GetComponent<Animator>();
		ani->Stop();
	}
	void DelayedCollisionSkillScript::ContinueWarningAniEvent()
	{
		std::shared_ptr<Animator> ani = mWarningObj->GetComponent<Animator>();
		ani->Play();
	}
	void DelayedCollisionSkillScript::MoveWarningObject()
	{
		std::shared_ptr<GameObject> target = mTarget.lock();
		std::shared_ptr<Transform> target_tf = target->GetComponent<Transform>();
		Vector3 target_pos = target_tf->position;

		std::shared_ptr<Transform> warning_tf = mWarningObj->GetComponent<Transform>();
		warning_tf->position = target_pos;
	}
}