#include "ImageComponent.h"
#include "Resources.h"
#include "Renderer.h"
#include "MeshRenderer.h"
#include "Material.h"
#include "Sprite.h"
#include "Prefab.h"
#include "NPK.h"
#include "Camera.h"
#include "Transform.h"

using namespace roka::graphics;
namespace roka
{
	ImageComponent::ImageComponent() :Component(EComponentType::Image),
		mSprite(std::make_unique<Sprite>()),
		mMaterial()
	{
	}
	ImageComponent::ImageComponent(const ImageComponent& ref) : Component(ref)
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
		auto default_material = prefab::Resources.find(L"DefaultMaterial");
		if (default_material == prefab::Resources.end())
			return;
		
		std::shared_ptr<MeshRenderer> mr = owner->GetComponent<MeshRenderer>();
		mr->material = std::dynamic_pointer_cast<Material>(default_material->second);
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
	void ImageComponent::Binds()
	{
		std::shared_ptr<NPK> npk = Resources::Find<NPK>(mSprite->npk_key);
		if (npk == nullptr)
			return;
		npk->GetTexture(mSprite->pack_key, mSprite->index)->BindShader(EShaderStage::PS, 0);
	}
	void ImageComponent::SetSprite(std::wstring npk_key, std::wstring pack_key, UINT index)
	{
		mSprite->Create(npk_key, pack_key, index);
	}
	void ImageComponent::SetMaterial(std::shared_ptr<Material> material)
	{
		mMaterial = material;
		std::shared_ptr<MeshRenderer> mr = owner->GetComponent<MeshRenderer>();
		mr->material = material;
	}
}