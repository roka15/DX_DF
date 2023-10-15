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

        void SetScale(Vector3 scale);
        void SetTransform(Vector3 position);
        void SetHorizontal(bool flag) { mbHorizontal = flag; }
        void SetVertical(bool flag) { mbVertical = flag; }
        void SetContent(std::shared_ptr<GameObject> obj) { mContent = obj; }
        void SetViewPort(std::shared_ptr<GameObject> obj);
        void SetViewPort();
        
        void AddContent(std::shared_ptr<GameObject> obj); 
        std::shared_ptr<GameObject> GetContent() { return mContent; }
        std::shared_ptr<GameObject> GetViewPort() { return mViewPort; }
        void OnMouseWheel(PointerEventData* data);
     
        RECT GetViewPortRect() { return mViewRect; }
    private:
        bool mbHorizontal;
        bool mbVertical;
        std::shared_ptr<GameObject> mContent;
        std::shared_ptr<GameObject> mViewPort;
        RECT mViewRect;
    };
}


