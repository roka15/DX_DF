#include "GameObject.h"
#include "Renderer.h"
#include "RokaGraphicDevice_Dx11.h"
roka::GameObject::GameObject()
	:mState(EState::Active)
{
}

roka::GameObject::~GameObject()
{
}

void roka::GameObject::Initialize()
{
}

void roka::GameObject::Update()
{
}

void roka::GameObject::LateUpdate()
{
}

void roka::GameObject::Render()
{
	renderer::mesh->BindBuffer();
	renderer::shader->Binds();
	graphics::GetDevice()->DrawIndexed(renderer::mesh->GetIndexCount(), 0, 0);
}
