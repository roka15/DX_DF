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

        void AddDragObject(std::shared_ptr<GameObject> obj) { mDragObjects.push_back(obj); }
        std::shared_ptr<GameObject> GetDragObject(int index);
        void DragObjectClear();

        bool GetDragState() { return mbDrag; }
        void SetDragState(bool flag) { mbDrag = flag; }
    private:
        friend class FactoryBase;
        friend class ComponentFactory;
    protected:
        std::vector<std::shared_ptr<GameObject>> mDragObjects;
        bool mbDrag;
    };
}


