#include "ImageComponent.h"
#include "Resources.h"
#include "Renderer.h"
#include "MeshRenderer.h"
#include "Material.h"
#include "Sprite.h"
#include "..\\Engine\\Prefab.h"
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
		Component::Initialize();
		auto default_material = prefab::Resources.find(L"DefaultMaterial");
		if (default_material == prefab::Resources.end())
			return;

		std::shared_ptr<MeshRenderer> mr = owner->GetComponent<MeshRenderer>();
		if (mr->material == nullptr)
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
	bool ImageComponent::Binds()
	{
		std::shared_ptr<MeshRenderer> mr = owner->GetComponent<MeshRenderer>();
		if (mr->material->IsNullTexture()==false)
			return true;
		if (mSprite == nullptr)
			return false;
		std::shared_ptr<NPK> npk = Resources::Find<NPK>(mSprite->npk_key);
		
		if (npk == nullptr)
			return false;
		std::shared_ptr<Texture> texture = npk->GetTexture(mSprite->pack_key, mSprite->index);
	
		if (texture == nullptr)
			texture = npk->Create(mSprite->pack_key, mSprite->index);
		texture->BindShaderResource(EShaderStage::PS, 0);
		return true;
	}
	void ImageComponent::SetSprite(std::wstring npk_key, std::wstring pack_key, UINT index)
	{
		mSprite->Create(npk_key, pack_key, index);
	}
	const Sprite& ImageComponent::GetSprite()
	{
		return *(mSprite.get());
	}
	void ImageComponent::SetMaterial(std::shared_ptr<Material> material)
	{
		mMaterial = material;
		std::shared_ptr<MeshRenderer> mr = owner->GetComponent<MeshRenderer>();
		mr->material = material;
	}
}