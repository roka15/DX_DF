#include "ImageComponent.h"

namespace roka
{
	ImageComponent::ImageComponent():Component(EComponentType::Image)
	{
	}
	ImageComponent::ImageComponent(const ImageComponent& ref):Component(ref)
	{
	}
	void ImageComponent::Copy(Component* src)
	{
		Component::Copy(src);
	}
	ImageComponent::~ImageComponent()
	{
	}
	void ImageComponent::Initialize()
	{
	}
	void ImageComponent::Update()
	{
	}
	void ImageComponent::LateUpdate()
	{
	}
	void ImageComponent::Render()
	{
	}
}