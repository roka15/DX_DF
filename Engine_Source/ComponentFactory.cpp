#include "ComponentFactory.h"
#include "MeshRenderer.h"
#include "Transform.h"
#include "Camera.h"
namespace roka
{
	std::map<EComponentType, std::function<std::shared_ptr<Component>(Component*)>> ComponentFactory::mFactories;
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
	}

	std::shared_ptr<Component> ComponentFactory::CreateNCopyComponent(Component* comp)
	{
		EComponentType type = comp->GetType();
		std::shared_ptr<Component> newComp = mFactories[type](comp);
		return newComp;
	}
}

