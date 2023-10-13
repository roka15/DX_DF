#pragma once
#include "Script.h"
namespace roka
{
    class Slot :
        public Script
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
    private:
        friend class FactoryBase;
        friend class ScriptFactory;
    private:
    };

}


