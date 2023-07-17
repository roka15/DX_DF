#include "Collider2D.h"
#include "Renderer.h"
#include "GameObject.h"

#include "Transform.h"

namespace roka
{
	UINT Collider2D::mColliderNumber = 0;
	Collider2D::Collider2D():
		Component(EComponentType::Collider),
		mTransform(),
		mPosition(Vector3::Zero),
		mSize(Vector2::One),
		mCenter(Vector2::Zero)
	{
		mColliderNumber++;
		mColliderID = mColliderNumber;
	}
	Collider2D::Collider2D(const Collider2D& ref):
		Component(ref),
		mTransform(ref.mTransform.lock()),
		mPosition(ref.mPosition),
		mColType(ref.mColType),
		mSize(ref.mSize),
		mCenter(ref.mCenter)
	{
	}
	void Collider2D::Copy(Component* src)
	{
		Component::Copy(src);
		Collider2D* source = dynamic_cast<Collider2D*>(src);
		if (source == nullptr)
			return;
		mTransform = source->mTransform.lock();
		mColType = source->mColType;
		mPosition = source->mPosition;
		mSize = source->mSize;
		mCenter = source->mCenter;
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
		std::shared_ptr<Transform> tf = owner->GetComponent<Transform>();
		
		Vector3 scale = tf->scale;
		scale.x *= mSize.x;
		scale.y *= mSize.y;
		
		Vector3 pos = tf->position;
		pos.x += mCenter.x;
		pos.y += mCenter.y;

		mPosition = pos;

		roka::graphics::DebugMesh mesh = {};
		mesh.position = pos;
		mesh.rotation = tf->rotation;
		mesh.scale = scale;
		mesh.type = EColliderType::Rect;

		renderer::PushDebugMeshAttribute(mesh);
	}
	void Collider2D::Render()
	{
	}
	void Collider2D::OnCollisionEnter(std::shared_ptr<Collider2D> other)
	{
		const std::vector<std::shared_ptr<Script>>& scripts
			=owner->GetComponents<Script>();

		for (const std::shared_ptr<Script>& script : scripts)
		{
			script->OnCollisionEnter(other);
		}
	}
	void Collider2D::OnCollisionStay(std::shared_ptr<Collider2D> other)
	{
		const std::vector<std::shared_ptr<Script>>& scripts
			= owner->GetComponents<Script>();

		for (const std::shared_ptr<Script>& script : scripts)
		{
			script->OnCollisionStay(other);
		}
	}
	void Collider2D::OnCollisionExit(std::shared_ptr<Collider2D> other)
	{
		const std::vector<std::shared_ptr<Script>>& scripts
			= owner->GetComponents<Script>();

		for (const std::shared_ptr<Script>& script : scripts)
		{
			script->OnCollisionExit(other);
		}
	}
}