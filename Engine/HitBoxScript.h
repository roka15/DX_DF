#pragma once
#include "Script.h"
namespace roka
{
    class HitBoxScript :public Script
    {
    private:
        HitBoxScript();
        HitBoxScript(const HitBoxScript& ref);
        void Copy(Component* src);
    public:
        ~HitBoxScript() {}
        enum class EHitBoxType
        {
            Top,
            Bottom,
            End,
        };

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Render() override;

        virtual void OnCollisionEnter(std::shared_ptr<Collider2D> other)override;
        virtual void OnCollisionStay(std::shared_ptr<Collider2D> other)override;
        virtual void OnCollisionExit(std::shared_ptr<Collider2D> other)override;

        void SetHitBoxType(EHitBoxType type) { mHitBoxType = type; }
        EHitBoxType GetHitBoxType() { return mHitBoxType; }

        void SetHitBoxOwner(std::shared_ptr<GameObject> owner) { mHitBoxOwner = owner; }

        PROPERTY(GetHitBoxType, SetHitBoxType)EHitBoxType hitbox;
        SET_PROPERTY(SetHitBoxOwner) std::weak_ptr<GameObject> hitbox_owner;
    private:
        friend class FactoryBase;
        friend class ScriptFactory;

        EHitBoxType mHitBoxType;
        std::weak_ptr<GameObject> mHitBoxOwner;
    };
}


