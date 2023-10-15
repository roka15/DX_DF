#pragma once
#include "Script.h"
#include "..\\Engine\\IMouseEvent.h"
namespace roka
{
    class Slot :
        public Script, public IPointerEnterHandler
    {
    protected:
        Slot();
        Slot(const Slot& ref);
        virtual void Copy(Component* src)override;

    public:
        virtual ~Slot() {}
        virtual void Initialize() override;
        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Render() override;

        virtual void OnPointerEnter(PointerEventData* data)override;

        void AddItem();
        void RemveItem();
    private:
        friend class FactoryBase;
        friend class ScriptFactory;
    private:
    };

}


