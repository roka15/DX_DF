#include "guiDebugObject.h"
#include "MeshRenderer.h"
#include "Renderer.h"
using namespace roka;
namespace gui
{
    DebugObject::DebugObject():GameObject()
    {
        mbDebugObject = true;
    }
    DebugObject::~DebugObject()
    {
    }
    void DebugObject::Initialize()
    {
    }
    void DebugObject::Update()
    {
    }
    void DebugObject::LateUpdate()
    {
        GameObject::LateUpdate();
    }
    void DebugObject::Render()
    {
        GameObject::Render();
    }
    void DebugObject::Copy(GameObject* src)
    {
        GameObject::Copy(src);
    }
    void DebugObject::SetColor(roka::math::Vector4 color)
    {
        graphics::ConstantBuffer* cb =
            renderer::constantBuffer[(UINT)ECBType::Material];

        renderer::MaterialCB materialbuf;
        materialbuf.Color = color;

        cb->SetData(&materialbuf);
        cb->Bind(EShaderStage::VS);
        cb->Bind(EShaderStage::PS);
    }
}