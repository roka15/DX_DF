#include "UI.h"

#include "Transform.h"
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
        if (mTarget.expired() == true)
            return;
        Vector3 pos =   mTarget.lock()->GetComponent<Transform>()->position;
        GetComponent<Transform>()->position = pos + Vector3(-0.15f,-0.1f,0.0f);
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