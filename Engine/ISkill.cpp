#include "ISkill.h"

#include "GameObject.h"
#include "Animator.h"
#include "Collider2D.h"

#include "PlayerScript.h"
#include "AvatarScript.h"
#include "SkinPartScript.h"
namespace roka
{
	void Skill::SetCollisionListener(std::shared_ptr<GameObject>& obj)
	{
		std::shared_ptr<Collider2D> collider = obj->GetComponent<Collider2D>();
		collider->SetCollisionListener(this);
	}
	void Skill::Execute(std::shared_ptr<GameObject> caster)
	{
		std::shared_ptr<PlayerScript> player = caster->GetComponent<PlayerScript>();
		if (player == nullptr)
		{
			std::shared_ptr<Animator> ani = caster->GetComponent<Animator>();
			ani->SetFrameEventListener(this);
		}
		else
		{
			std::shared_ptr<GameObject> avatarObj = caster->GetChild<AvatarScript>();
			std::shared_ptr<GameObject> skinObj = avatarObj->GetChild<SkinPartScript>();

			std::shared_ptr<Animator> ani = skinObj->GetComponent<Animator>();
			ani->SetFrameEventListener(this);
		}
	}
}