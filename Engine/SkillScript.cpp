#include "SkillScript.h"
#include "RokaTime.h"
#include "GameObject.h"

#include "Animator.h"
#include "MeshRenderer.h"
#include "Collider2D.h"
#include "Transform.h"

namespace roka
{
	SkillScript::SkillScript() :Script(EScriptType::SkillBase)
	{
	}
	SkillScript::SkillScript(EScriptType type) : Script(type)
	{
	}
	SkillScript::SkillScript(const SkillScript& ref) : Script(ref)
	{
		mStunType = ref.mStunType;
		mStartKey = ref.mStartKey;
		mRange = ref.mRange;
		mDistance = ref.mDistance;
		mStartPos = ref.mStartPos;
		mDeleteTime = ref.mDeleteTime;

	}
	void SkillScript::Copy(Component* src)
	{
		SkillScript* source = dynamic_cast<SkillScript*>(src);
		mStunType = source->mStunType;
		mStartKey = source->mStartKey;
		mRange = source->mRange;
		mDistance = source->mDistance;
		mStartPos = source->mStartPos;
		mDeleteTime = source->mDeleteTime;
	}
	void SkillScript::Initialize()
	{
		Time::RegisterEvent(L"SkillEndEvent", SkillEndEvent);
	}
	void SkillScript::Update()
	{
	}
	void SkillScript::LateUpdate()
	{
	}
	void SkillScript::Render()
	{
	}
	void SkillScript::Play(EDir4Type dir)
	{
		std::shared_ptr<Animator> ani = owner->GetComponent<Animator>();
		//test
		if (ani != nullptr)
			ani->PlayAnimation(mStartKey, false);

		std::shared_ptr<MeshRenderer> mr = owner->GetComponent<MeshRenderer>();
		mr->is_active = true;
		std::shared_ptr<Collider2D>col = owner->GetComponent<Collider2D>();

		Vector2 colCenter = mDistance;
		Vector2 startPos = mStartPos;

		if (dir == EDir4Type::LEFT)
		{
			colCenter.x *= -1;
			startPos.x *= -1;
		}
		//test
		if (col != nullptr)
		{
			col->is_active = true;
			col->EnableRender();
			col->SetSize(mRange);


			col->SetCenter(colCenter);
		}

		std::shared_ptr<Transform> tf = owner->GetComponent<Transform>();
		float z = tf->position.x;
		tf->position = Vector3(startPos.x, startPos.y, z);


		Time::CallBackTimerInfo  info = {};
		info.endTime = mDeleteTime;
		std::wstring key = L"SkillEndEvent";
		size_t str_length = key.size();
		std::wcsncpy(info.key, key.c_str(), str_length);

		Time::RequestEvent(info, owner->GetSharedPtr());
	}
	void SkillScript::End()
	{
		std::shared_ptr<MeshRenderer> mr = owner->GetComponent<MeshRenderer>();
		mr->is_active = false;
		std::shared_ptr<Collider2D> col = owner->GetComponent<Collider2D>();
		//test
		if (col != nullptr)
		{
			col->SetSize(Vector2::Zero);
			col->SetCenter(Vector2(100.0f, 100.0f));
			col->DisableRender();
		}
	}
	void SkillScript::SkillEndEvent(std::weak_ptr<void> ptr)
	{
		std::shared_ptr<GameObject> obj = std::reinterpret_pointer_cast<GameObject>(ptr.lock());
		std::shared_ptr<SkillScript> skill = obj->GetComponent<SkillScript>();
		skill->End();
	}
}