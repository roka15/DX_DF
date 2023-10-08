#pragma once
#include "GroupLayout.h"
namespace roka
{
    class GridGroupLayout :
        public GroupLayout
    {
    protected:
        GridGroupLayout();
        GridGroupLayout(const GridGroupLayout& ref);
        virtual void Copy(Component* src);
    public:
        virtual ~GridGroupLayout();

        virtual void Initialize();
        virtual void Update();
        virtual void LateUpdate();
        virtual void Render();

    private:
        friend class FactoryBase;
        friend class ComponentFactory;
    };
}


