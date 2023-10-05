#include "MeshRenderer.h"
#include "Resources.h"
#include "GameObject.h"
#include "Transform.h"
#include "Renderer.h"
#include "ImageComponent.h"
#include "Animator.h"
#include "UI.h"
#include "ScrollRect.h"
#include "Application.h"
extern roka::Application* focusApp;
namespace roka
{
	using namespace roka::graphics;
	MeshRenderer::MeshRenderer()
		:Component(EComponentType::MeshRenderer),
		mAlpha(1.0f)
	{
	}
	MeshRenderer::MeshRenderer(const MeshRenderer& ref) : Component(ref)
	{
		mMesh = ref.mMesh;
		mMaterial = std::make_shared<Material>(*(ref.mMaterial.get()));
		mAlpha = ref.mAlpha;
	}
	void MeshRenderer::Copy(Component* src)
	{
		Component::Copy(src);
		MeshRenderer* source = dynamic_cast<MeshRenderer*>(src);
		if (source == nullptr)
			return;
		mMesh = source->mMesh;
		mMaterial = std::make_shared<Material>(*(source->mMaterial.get()));
		mAlpha = source->mAlpha;
	}
	MeshRenderer::~MeshRenderer()
	{
	}
	void MeshRenderer::Initialize()
	{
		Component::Initialize();
		mAlpha = 1.0f;
		if (mMaterial == nullptr)
			mMaterial = std::make_shared<Material>();
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
		if (is_active == false)
			return;
		std::shared_ptr<ImageComponent> imageComp = owner->GetComponent<ImageComponent>();
		std::shared_ptr<Animator> animator = owner->GetComponent<Animator>();
		UI* ui;
		std::shared_ptr<ScrollRect> scroll;
		ui = dynamic_cast<UI*>(owner);
		int flag = 0;
		if (animator != nullptr)
		{
			if (animator->Binds())
			{
				Execute();
			}
			return;
		}

		if (imageComp != nullptr)
		{
			if (ui != nullptr)
			{
				if (ui->parent != nullptr && ui->parent->GetName().compare(L"Content") == 0)
				{
					scroll = ui->parent->parent->parent->GetComponent<ScrollRect>();
					scroll->Bind();
				}
			}
			if (imageComp->Binds())
			{
				Execute();
			}
			if (scroll != nullptr)
			{
				focusApp->BindViewPort();
			}
			return;
		}


		if (owner->is_debug)
		{
			Execute();
			return;
		}
	}
	void MeshRenderer::Execute()
	{
		std::shared_ptr<Transform> tf = owner->GetComponent<Transform>();

		tf->BindConstantBuffer();
		mMesh->BindBuffer();
		mMaterial->Binds();
		mMesh->Render();
		mMaterial->Clear();
	}
}