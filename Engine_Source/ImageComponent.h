#pragma once
#include "Component.h"

namespace roka::graphics
{
    class Material;
}
using namespace roka::graphics;
namespace roka
{
    class Sprite;
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

        bool Binds();

        void SetSprite(std::wstring npk_key, std::wstring pack_key, UINT index);
        const Sprite& GetSprite();
        void SetMaterial(std::shared_ptr<Material> material);
        
    private:
        friend class FactoryBase;
        friend class ComponentFactory;
        std::unique_ptr<Sprite> mSprite;
        std::weak_ptr<Material> mMaterial;
	};
}


