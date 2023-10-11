#include "Collider2D.h"
#include "RokaTime.h"
#include "Renderer.h"
#include "GameObject.h"
#include "Application.h"
#include "CollisionManager.h"
#include "Transform.h"
#include "UI.h"

extern roka::Application application;
namespace roka
{
	UINT Collider2D::mColliderNumber = 0;
	Collider2D::Collider2D() :
		Component(EComponentType::Collider),
		mTransform(),
		mPosition(Vector3::Zero),
		mRotationZ(0),
		mSize(Vector2::One),
		mCenter(Vector2::Zero),
		mbCollision(false),
		mbRender(true),
		mTime(0.0),
		mbColCehck(true)
	{
		mColliderNumber++;
		mColliderID = mColliderNumber;
		mCollisionListener = nullptr;
	}
	Collider2D::Collider2D(const Collider2D& ref) :
		Component(ref),
		mTransform(ref.mTransform.lock()),
		mPosition(ref.mPosition),
		mRotationZ(0),
		mColType(ref.mColType),
		mSize(ref.mSize),
		mCenter(ref.mCenter),
		mTime(0.0),
		mbRender(ref.mbRender),
		mbColCehck(true)
	{
		mColliderNumber++;
		mColliderID = mColliderNumber;
		mCollisionListener = nullptr;
		mHitType = ref.mHitType;
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
		mColliderNumber++;
		mColliderID = mColliderNumber;
		mTime = 0.0;
		mRotationZ = 0.0f;
		mbRender = source->mbRender;
		mbColCehck = true;
		mCollisionListener = nullptr;
		mHitType = source->mHitType;
	}

	Collider2D::~Collider2D()
	{
	}
	void Collider2D::Initialize()
	{
		Component::Initialize();
		mTransform = owner->GetComponent<Transform>();
		mbColCehck = true;
		mbCollision = false;
		mbRender = true;
		mCollisionListener = nullptr;
	}
	void Collider2D::Update()
	{
	}
	void Collider2D::LateUpdate()
	{
		if (is_active == false)
			return;
		if (mbRender == false)
			return;
		if (owner->GetName().compare(L"LayserObject") == 0)
			int a = 0;
		std::shared_ptr<Transform> tf = owner->GetComponent<Transform>();

		Vector3 scale = tf->GetLocalScale();
		scale.x *= mSize.x;
		scale.y *= mSize.y;

		Vector3 pos = tf->GetLocalPosition();

		Vector3 rotation = tf->GetLocalRotation();
		rotation.z += mRotationZ;

		float rotationZ = tf->rotation.z;
		if (rotationZ != 0.0f)
		{
			pos.x += (mCenter.x * cos(rotationZ)) - (mCenter.y * sin(rotationZ));
			pos.y += (mCenter.x * sin(rotationZ)) + (mCenter.y * cos(rotationZ));
		}
		else
		{
			pos.x += mCenter.x;
			pos.y += mCenter.y;
		}

		mPosition = pos;

		
		roka::graphics::DebugMesh mesh = {};
		mesh.parent = owner->parent;
		mesh.position = pos;
		mesh.rotation = rotation;
		mesh.scale = scale;
		mesh.type = EColliderType::Rect;
		if (mbCollision == true)
			mesh.color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
		else
			mesh.color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);

		if (owner->GetName().compare(L"TestImage") == 0)
		{
			int a = 0;
		}
		if (owner->layer_type == ELayerType::UI)
		{
			//mesh.viewPortRect = dynamic_cast<UI*>(owner)->GetViewPortRect();
		}

		renderer::PushDebugMeshAttribute(mesh);
	}
	void Collider2D::Render()
	{
	}
	void Collider2D::OnCollisionEnter(std::shared_ptr<Collider2D> other)
	{
		if (mbColCehck == false || other->mbColCehck == false)
		{
			std::shared_ptr<Collider2D> left = owner->GetComponent<Collider2D>();
			CollisionManager::DisableCollision(left, other);
			return;
		}
		mbCollision = true;
		const std::vector<std::shared_ptr<Script>>& scripts
			= owner->GetScripts();

		for (const std::shared_ptr<Script>& script : scripts)
		{
			script->OnCollisionEnter(other);
		}
		if (mCollisionListener != nullptr)
			mCollisionListener->OnCollisionEnter(owner->GetSharedPtr(),other->owner->GetSharedPtr());
	}
	void Collider2D::OnCollisionStay(std::shared_ptr<Collider2D> other)
	{
		if (mbColCehck == false || other->mbColCehck == false)
		{
			std::shared_ptr<Collider2D> left = owner->GetComponent<Collider2D>();
			CollisionManager::DisableCollision(left, other);
			return;
		}
		mbCollision = true;
		const std::vector<std::shared_ptr<Script>>& scripts
			= owner->GetScripts();

		for (const std::shared_ptr<Script>& script : scripts)
		{
			script->OnCollisionStay(other);
		}
		if (mCollisionListener != nullptr)
			mCollisionListener->OnCollisionStay(owner->GetSharedPtr(), other->owner->GetSharedPtr());
	}
	void Collider2D::OnCollisionExit(std::shared_ptr<Collider2D> other)
	{
		mbCollision = false;
		const std::vector<std::shared_ptr<Script>>& scripts
			= owner->GetComponents<Script>();

		for (const std::shared_ptr<Script>& script : scripts)
		{
			script->OnCollisionExit(other);
		}
		if (mCollisionListener != nullptr)
			mCollisionListener->OnCollisionExit(owner->GetSharedPtr(), other->owner->GetSharedPtr());
	}
}