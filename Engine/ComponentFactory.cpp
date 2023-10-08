#include "ComponentFactory.h"
#include "MeshRenderer.h"
#include "Transform.h"
#include "Camera.h"
#include "ImageComponent.h"
#include "Collider2D.h"
#include "Animator.h"
#include "Rigidbody.h"
#include "Light.h"
#include "Cursor.h"
#include "ScrollRect.h"
#include "GridGroupLayout.h"

namespace roka
{
	void ComponentFactory::Initialize()
	{
		mFactories[EComponentType::Camera] = [](Component* component) {
			Camera* cam = dynamic_cast<Camera*>(component);
			return std::shared_ptr<Camera>(new Camera(*cam));
		};
		mFactories[EComponentType::MeshRenderer] = [](Component* component) {
			MeshRenderer* mr = dynamic_cast<MeshRenderer*>(component);
			return std::shared_ptr<MeshRenderer>(new MeshRenderer(*mr));
		};
		mFactories[EComponentType::Transform] = [](Component* component) {
			Transform* tr = dynamic_cast<Transform*>(component);
			return std::shared_ptr<Transform>(new Transform(*tr));
		};
		mFactories[EComponentType::Image] = [](Component* component) {
			ImageComponent* tr = dynamic_cast<ImageComponent*>(component);
			return std::shared_ptr<ImageComponent>(new ImageComponent(*tr));
		};
		mFactories[EComponentType::Collider] = [](Component* component) {
			Collider2D* col = dynamic_cast<Collider2D*>(component);
			return std::shared_ptr<Collider2D>(new Collider2D(*col));
		};
		mFactories[EComponentType::Animator] = [](Component* component) {
			Animator* ani = dynamic_cast<Animator*>(component);
			return std::shared_ptr<Animator>(new Animator(*ani));
		};
		mFactories[EComponentType::Rigidbody] = [](Component* component) {
			Rigidbody* rg = dynamic_cast<Rigidbody*>(component);
			return std::shared_ptr<Rigidbody>(new Rigidbody(*rg));
		};
		mFactories[EComponentType::Light] = [](Component* component) {
			Light* rg = dynamic_cast<Light*>(component);
			return std::shared_ptr<Light>(new Light(*rg));
		};
		mFactories[EComponentType::Cursor] = [](Component* component) {
			Cursor* rg = dynamic_cast<Cursor*>(component);
			return std::shared_ptr<Cursor>(new Cursor(*rg));
		};
		mFactories[EComponentType::ScrollRect] = [](Component* component) {
			ScrollRect* rg = dynamic_cast<ScrollRect*>(component);
			return std::shared_ptr<ScrollRect>(new ScrollRect(*rg));
		};
		mFactories[EComponentType::GridLayout] = [](Component* component) {
			GridGroupLayout* rg = dynamic_cast<GridGroupLayout*>(component);
			return std::shared_ptr<GridGroupLayout>(new GridGroupLayout(*rg));
		};
	}

	std::shared_ptr<Component> ComponentFactory::CreateNCopy(Component* comp)
	{
		EComponentType type = comp->GetType();
		std::shared_ptr<Component> newComp = mFactories[type](comp);
		return newComp;
	}
}

