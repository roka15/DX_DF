#pragma once
#include "Component.h"
namespace roka
{
	class ImageComponent :
		public Component
	{
    private:
        ImageComponent();
        ImageComponent(const ImageComponent& ref);
        virtual void Copy(Component* src)override;
    public:
        ~ImageComponent();
        virtual void Initialize()override;
        virtual void Update()override;
        virtual void LateUpdate()override;
        virtual void Render()override;

    private:
        friend class FactoryBase;
        friend class ComponentFactory;
	};
}


