#pragma once
#include "Component.h"
#include "..\\Engine\\IMouseEvent.h"
namespace roka
{
    class ScrollRect :
        public Component,public IWheelHandler
    {
    public:
        ScrollRect();
        ScrollRect(const Component& ref);
        virtual ~ScrollRect();
        virtual void Copy(Component* src);

        virtual void Initialize();
        virtual void Update();
        virtual void LateUpdate();
        virtual void Render();
        virtual void Bind();


        void SetHorizontal(bool flag) { mbHorizontal = flag; }
        void SetVertical(bool flag) { mbVertical = flag; }
        void SetContent(std::shared_ptr<GameObject> obj) { mContent = obj; }
        void SetViewPort(std::shared_ptr<GameObject> obj) { mViewPort = obj; }
        
        void AddContent(std::shared_ptr<GameObject> obj); 
        void OnMouseWheel(PointerEventData* data);
    private:
        bool mbHorizontal;
        bool mbVertical;
        std::shared_ptr<GameObject> mContent;
        std::shared_ptr<GameObject> mViewPort;
    };
}


