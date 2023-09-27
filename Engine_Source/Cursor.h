#pragma once
#include "Component.h"
#include "..\\Engine\\IMouseEvent.h"
namespace roka
{
    class Cursor :
        public Component, public IPointerEnterHandler,public IPointerExitHandler,public IPointerClickHandler,public IDragHandler,public IBeginDragHandler,public IEndDragHandler
    {
    protected:
        Cursor();
        Cursor(const Cursor& ref);
        virtual void Copy(Component* src);
    public:
        virtual ~Cursor();

        virtual void Initialize();
        virtual void Update();
        virtual void LateUpdate();
        virtual void Render();

        virtual void OnPointerEnter(PointerEventData* data)override;
        virtual void OnPointerExit(PointerEventData* data)override;
        virtual void OnClick(PointerEventData* data)override;
        virtual void OnBeginDrag(PointerEventData* data)override;
        virtual void OnDrag(PointerEventData* data)override;
        virtual void OnEndDrag(PointerEventData* data)override;

        void AddDragObject(std::shared_ptr<GameObject> obj) { mDragObjects.push(obj); }
        std::shared_ptr<GameObject> GetDragObject();
        void DragObjectClear();
    private:
        friend class FactoryBase;
        friend class ComponentFactory;
    protected:
        std::queue<std::weak_ptr<GameObject>> mDragObjects;
    };
}


