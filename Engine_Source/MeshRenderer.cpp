#include "MeshRenderer.h"
#include "GameObject.h"
#include "Transform.h"
#include "Renderer.h"
#include "ImageComponent.h"
#include "Animator.h"
namespace roka
{
	using namespace roka::graphics;
	MeshRenderer::MeshRenderer()
		:Component(EComponentType::MeshRenderer)
	{
	}
	MeshRenderer::MeshRenderer(const MeshRenderer& ref):Component(ref)
	{
		mMesh = ref.mMesh;
		mMaterial = ref.mMaterial;
	}
	void MeshRenderer::Copy(Component* src)
	{
		Component::Copy(src);
		MeshRenderer* source = dynamic_cast<MeshRenderer*>(src);
		if (source == nullptr)
			return;
		mMesh = source->mMesh;
		mMaterial = source->mMaterial;
	}
	MeshRenderer::~MeshRenderer()
	{
	}
	void MeshRenderer::Initialize()
	{
	}
	void MeshRenderer::Update()
	{
	}
	void MeshRenderer::LateUpdate()
	{
	}
	void MeshRenderer::Render()
	{
		GameObject* Owner = GetOwner();
		std::shared_ptr<Transform> tf = owner->GetComponent<Transform>();
		std::shared_ptr<ImageComponent> imageComp = owner->GetComponent<ImageComponent>();
		std::shared_ptr<Animator> animator = owner->GetComponent<Animator>();
		int flag = 0;
		if (imageComp != nullptr)
		{	
			if (imageComp->Binds() == true)
				flag++;
		}
		if (animator != nullptr)
		{
			if (animator->Binds())
				flag++;
		}

		if (flag > 0 || owner->is_debug == true)
		{
			tf->BindConstantBuffer();
			mMesh->BindBuffer();
			mMaterial->Binds();
			mMesh->Render();
			mMaterial->Clear();
		}
	}
}