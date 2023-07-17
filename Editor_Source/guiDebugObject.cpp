#include "guiDebugObject.h"

namespace gui
{
    DebugObject::DebugObject()
    {
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
}