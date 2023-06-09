#pragma once
#include "Component.h"

namespace roka
{
    class Transform : public Component
    {
    private:
        Transform();
        Transform(const Transform& ref);
        virtual void Copy(Component* src)override;
    public:
        ~Transform();
        virtual void Initialize()override;
        virtual void Update()override;
        virtual void LateUpdate()override;
        virtual void Render()override;

        void BindConstantBuffer();

        void SetPosition(Vector3 position) { mPosition = position; }
        void SetRotation(Vector3 rotation) { mRotation = rotation; }
        void SetScale(Vector3 scale) { mScale = scale; }

        void SetPosition(float x, float y, float z) { mPosition = Vector3(x, y, z); }
        void SetRotation(float x, float y, float z) { mRotation = Vector3(x, y, z); }
        void SetScale(float x, float y, float z) { mScale = Vector3(x, y, z); }

        Vector3 GetPosition() { return mPosition; }
        Vector3 GetRotation() { return mRotation; }
        Vector3 GetScale() { return mScale; }

        Vector3 Up() { return mUp; }
        Vector3 Right() { return mRight; }
        Vector3 Forward() { return mForward; }

        void AddChild(std::shared_ptr<Transform> child);
        void SetParent(std::weak_ptr<Transform> parent) { mParent = parent; }
        std::shared_ptr<Transform> GetParent() { return mParent.lock(); }

        PROPERTY(GetPosition, SetPosition) Vector3 position;
        PROPERTY(GetRotation, SetRotation)Vector3 rotation;
        PROPERTY(GetScale, SetScale)Vector3 scale;

        GET_PROPERTY(Up) Vector3 up;
        GET_PROPERTY(Right) Vector3 right;
        GET_PROPERTY(Forward) Vector3 forward;

        PROPERTY(GetParent, SetParent)  std::shared_ptr<Transform> parent;

    private:
        friend class ComponentFactory;
        Vector3 mPosition;
        Vector3 mRotation;
        Vector3 mScale;
        
        Vector3 mUp;
        Vector3 mForward;
        Vector3 mRight;

        Matrix mWorld;

        std::vector<std::shared_ptr<Transform>> mChild;
        std::weak_ptr<Transform> mParent;
    };
}

