#include "Collider2D.h"
#include "GameObject.h"

#include "Transform.h"

namespace roka
{
	Collider2D::Collider2D():
		Component(EComponentType::Collider),
		mTransform(),
		mSize(Vector2::One),
		mCenter(Vector2::Zero)
	{
	}
	Collider2D::~Collider2D()
	{
	}
	void Collider2D::Initialize()
	{
		mTransform = owner->GetComponent<Transform>();
	}
	void Collider2D::Update()
	{
	}
	void Collider2D::LateUpdate()
	{
	}
	void Collider2D::Render()
	{
	}
}