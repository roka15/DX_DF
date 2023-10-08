#include "UI.h"

namespace roka
{
    UI::UI() :GameObject(), mViewPortRect{}
    {
        mbRayCastTarget = false;
        layer_type = ELayerType::UI;
    }
    UI::UI(const UI& ref) : GameObject(ref), mViewPortRect{}
    {
    }
    void UI::Copy(GameObject* src)
    {
        UI* source = dynamic_cast<UI*>(src);
        if (source == nullptr)
            return;
        GameObject::Copy(src);
        mViewPortRect = {};
    }
    void UI::Initialize()
    {
        GameObject::Initialize();
    }
    void UI::Update()
    {
        GameObject::Update();
    }
    void UI::LateUpdate()
    {
        GameObject::LateUpdate();
    }
    void UI::Render()
    {
        GameObject::Render();
    }
    void UI::Release()
    {
        GameObject::Release();
    }
}