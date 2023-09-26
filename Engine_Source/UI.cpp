#include "UI.h"

namespace roka
{
    UI::UI():GameObject()
    {
        mbRayCastTarget = false;
    }
    UI::UI(const UI& ref):GameObject(ref)
    {
    }
    void UI::Copy(GameObject* src)
    {
        UI* source = dynamic_cast<UI*>(src);
        if (source == nullptr)
            return;
        GameObject::Copy(src);
    }
    void UI::Initialize()
    {
    }
    void UI::Update()
    {
    }
    void UI::LateUpdate()
    {
    }
    void UI::Render()
    {
    }
    void UI::Release()
    {
    }
}