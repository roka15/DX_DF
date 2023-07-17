#include "ComponentFactory.h"
#include "MeshRenderer.h"
#include "Transform.h"
#include "Camera.h"
#include "ImageComponent.h"
#include "Collider2D.h"
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
	}

	std::shared_ptr<Component> ComponentFactory::CreateNCopy(Component* comp)
	{
		EComponentType type = comp->GetType();
		std::shared_ptr<Component> newComp = mFactories[type](comp);
		return newComp;
	}
}

