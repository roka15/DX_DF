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
#include "Texture.h"
#include "Animator.h"

using namespace roka::graphics;
namespace roka
{
	ImageComponent::ImageComponent() :Component(EComponentType::Image),
		mMaterial(),
		mRenderIndex(-1)
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
		std::shared_ptr<Animator> ani = owner->GetComponent<Animator>();
		if (ani != nullptr)
			return;
		std::shared_ptr<MeshRenderer> mr = owner->GetComponent<MeshRenderer>();
		mr->mesh = Resources::Find<Mesh>(L"RectMesh");
		mr->material->Copy(Resources::Find<Material>(L"DefaultAtlasMaterial").get());
		mMaterial = mr->material;
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
		if (mRenderIndex == -1)
			return false;
		std::shared_ptr<MeshRenderer> mr = owner->GetComponent<MeshRenderer>();
		std::shared_ptr<Texture> texture = mr->material->texture;
		if (texture == nullptr)
			return false;
		texture->SetCurSpriteIndex(mRenderIndex);
		Sprite sprite = texture->GetSprite();
		renderer::AtlasCB data = {};
		data.SpriteLeftTop = sprite.lefttop;
		data.SpriteOffset = sprite.offset;
		data.SpriteSize = sprite.image_size;
		data.CanvasSize = sprite.canvas_size;
		data.Alpha = mr->alpha;
		if (EBSType::OneOne == mr->material->shader->bsstate)
			data.Flag |= 0x1;

		if (mr->GetChangeActiveAlpha() == true)
			data.Flag |= 0x2;

		ConstantBuffer* cb = renderer::constantBuffer[(UINT)ECBType::Atlas];
		cb->SetData(&data);

		cb->Bind(EShaderStage::VS);
		cb->Bind(EShaderStage::PS);
		return true;
	}
	
	void ImageComponent::SetMaterial(std::shared_ptr<Material> material)
	{
		mMaterial = material;
		std::shared_ptr<MeshRenderer> mr = owner->GetComponent<MeshRenderer>();
		mr->material = material;
	}
	void ImageComponent::SetTexture(std::shared_ptr<Texture>& texture)
	{
		mMaterial.lock()->texture = texture;
	}
}