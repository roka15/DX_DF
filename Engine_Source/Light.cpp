#include "Light.h"
#include "GameObject.h"
#include "Transform.h"
#include "Renderer.h"
namespace roka
{
	Light::Light():Component(EComponentType::Light)
	{
	}
	Light::Light(const Light& ref):Component(ref)
	{
	}
	void Light::Copy(Component* src)
	{
		Component::Copy(src);

	}
	void Light::Initialize()
	{
	}
	void Light::Update()
	{
	}
	void Light::LateUpdate()
	{
		renderer::lights.push_back(owner->GetSharedPtr());

		std::shared_ptr<Transform> tf = owner->GetComponent<Transform>();
		Vector3 pos = tf->position;
		Vector3 forward = tf->Forward();
		mAttribute.position = Vector4(pos.x, pos.y, pos.z, 1.0f);
		mAttribute.direction = Vector4(forward.x, forward.y, forward.z, 1.0f);
	}
	void Light::Render()
	{
	}
}