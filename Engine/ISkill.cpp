#include "ISkill.h"

#include "GameObject.h"
#include "Collider2D.h"
namespace roka
{
	void Skill::SetCollisionListener(std::shared_ptr<GameObject>& obj)
	{
		std::shared_ptr<Collider2D> collider = obj->GetComponent<Collider2D>();
		collider->SetCollisionListener(this);
	}
}