#include "HitBoxScript.h"

#include "GameObject.h"

#include"Collider2D.h"
roka::HitBoxScript::HitBoxScript():Script(EScriptType::HitBox)
{
}

roka::HitBoxScript::HitBoxScript(const HitBoxScript& ref):Script(ref)
{
	mHitBoxType = ref.mHitBoxType;
}

void roka::HitBoxScript::Copy(Component* src)
{
	HitBoxScript* source = dynamic_cast<HitBoxScript*>(src);
	if (source == nullptr)
		return;

}

void roka::HitBoxScript::Initialize()
{
	Script::Initialize();
	mHitBoxOwner = owner->GetSharedPtr();
}

void roka::HitBoxScript::Update()
{
}

void roka::HitBoxScript::LateUpdate()
{
}

void roka::HitBoxScript::Render()
{
}

void roka::HitBoxScript::OnCollisionEnter(std::shared_ptr<Collider2D> other)
{
	std::shared_ptr<HitBoxScript> otherHitBox = other->owner->GetComponent<HitBoxScript>();
	if (otherHitBox == nullptr)
		return;
	if (mHitBoxType == otherHitBox->hitbox&&
		owner->layer_type == ELayerType::Skill)
	{
		std::vector<std::shared_ptr<Script>> scripts = mHitBoxOwner.lock()->GetScripts();

		for (auto script : scripts)
		{
			std::shared_ptr<HitBoxScript> hitbox = std::dynamic_pointer_cast<HitBoxScript>(script);
			if (hitbox != nullptr)
				continue;
			script->OnCollisionEnter(other);
		}
	}
}

void roka::HitBoxScript::OnCollisionStay(std::shared_ptr<Collider2D> other)
{
	std::shared_ptr<HitBoxScript> otherHitBox = other->owner->GetComponent<HitBoxScript>();
	if (otherHitBox == nullptr)
		return;
	if (mHitBoxType == otherHitBox->hitbox &&
		owner->layer_type == ELayerType::Skill)
	{
		std::vector<std::shared_ptr<Script>> scripts = mHitBoxOwner.lock()->GetScripts();

		for (auto script : scripts)
		{
			std::shared_ptr<HitBoxScript> hitbox = std::dynamic_pointer_cast<HitBoxScript>(script);
			if (hitbox != nullptr)
				continue;
			script->OnCollisionStay(other);
		}
	}
}

void roka::HitBoxScript::OnCollisionExit(std::shared_ptr<Collider2D> other)
{
	std::shared_ptr<HitBoxScript> otherHitBox = other->owner->GetComponent<HitBoxScript>();
	if (otherHitBox == nullptr)
		return;
	if (mHitBoxType == otherHitBox->hitbox &&
		owner->layer_type == ELayerType::Skill)
	{
		std::vector<std::shared_ptr<Script>> scripts = mHitBoxOwner.lock()->GetScripts();

		for (auto script : scripts)
		{
			std::shared_ptr<HitBoxScript> hitbox = std::dynamic_pointer_cast<HitBoxScript>(script);
			if (hitbox != nullptr)
				continue;
			script->OnCollisionExit(other);
		}
	}
}
