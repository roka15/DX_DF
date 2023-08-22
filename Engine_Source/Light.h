#pragma once
#include "Component.h"
#include "RokaGraphics.h"
namespace roka
{
    using namespace graphics;

    class Light :
        public Component
    {
    private:
        Light();
        Light(const Light& ref);
        void Copy(Component* src)override;
    public:
        ~Light() {}
        
        virtual void Initialize() override;
        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Render() override;

        LightAttribute GetAttribute() { return mAttribute; }
        void SetType(ELightType type) { mAttribute.type = type; }
        void SetRadius(float radius) { mAttribute.radius = radius; }
        void SetAngle(float angle) { mAttribute.angle = angle; }
        void SetColor(Vector4 color) { mAttribute.color = color; }
        ELightType GetLightType() { return mAttribute.type; }
        float GetRadius() { return mAttribute.radius; }
        float GetAngle() { return mAttribute.angle; }

    private:
        friend class FactoryBase;
        friend class ComponentFactory;

        LightAttribute mAttribute;
    };
}

