#include "Image.h"
#include "Resources.h"
#include "Transform.h"
#include "MeshRenderer.h"
#include "ImageComponent.h"

namespace roka
{
	Image::Image()
	{
		
	}
	Image::~Image()
	{
	}
	void Image::Initialize()
	{
		mTransform = GetComponent<Transform>();
		mMeshRender = AddComponent<MeshRenderer>();
		mImage = AddComponent<ImageComponent>();

		std::shared_ptr<MeshRenderer> mr = mMeshRender.lock();
		mr->mesh = Resources::Find<Mesh>(L"RectMesh");
		GameObject::Initialize();
	}
	void Image::Update()
	{
		GameObject::Update();
	}
	void Image::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Image::Render()
	{
		GameObject::Render();
	}
}