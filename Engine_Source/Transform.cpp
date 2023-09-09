#include "Transform.h"
#include "Camera.h"
#include "ConstantBuffer.h"
#include "Renderer.h"
#include "GameObject.h"
#include "Object.h"
#include "..\\Engine\\Prefab.h"
namespace roka
{
    using namespace roka::graphics;

    Transform::Transform()
        :Component(EComponentType::Transform)
        ,mPosition(Vector3::Zero)
        ,mRotation(Vector3::Zero)
        ,mScale(Vector3::One)
    {
    }
    Transform::Transform(const Transform& ref):Component(ref)
    {
       mPosition =ref.mPosition;
       mRotation=ref.mRotation;
       mScale=ref.mScale;

       mUp=ref.mUp;
       mForward=ref.mForward;
       mRight=ref.mRight;

       mWorld=ref.mWorld;
    }
    void Transform::Copy(Component* src)
    {
        Component::Copy(src);
        Transform* source = dynamic_cast<Transform*>(src);
        mPosition = source->mPosition;
        mRotation = source->mRotation;
        mScale = source->mScale;

        mUp = source->mUp;
        mForward = source->mForward;
        mRight = source->mRight;

        mWorld = source->mWorld;
    }
    Transform::~Transform()
    {
    }
    void Transform::Initialize()
    {
        Component::Initialize();
    }
    void Transform::Update()
    {
        //위치,크기,회전 적용
    }
    void Transform::LateUpdate()
    {
        //world space 적용
        mWorld = Matrix::Identity;

        Matrix scale = Matrix::CreateScale(mScale);
        Matrix rotation = Matrix::CreateRotationX(mRotation.x);
        rotation *= Matrix::CreateRotationY(mRotation.y);
        rotation *= Matrix::CreateRotationZ(mRotation.z);
        Matrix position; 
  
        position.Translation(mPosition);
        
        if (owner->GetName().compare(L"Monster1") == 0)
            int a = 0;
        mWorld = scale * rotation * position;

        std::shared_ptr<GameObject> parent = owner->parent;
        if(parent)
        {
            std::shared_ptr<Transform> tf = parent->GetComponent<Transform>();
            mWorld *= tf->mWorld;
        }

        mUp = Vector3::TransformNormal(Vector3::Up, rotation);
        mRight = Vector3::TransformNormal(Vector3::Right, rotation);
        mForward = Vector3::TransformNormal(Vector3::Forward, rotation);
    }
    void Transform::Render()
    {
    }
    void Transform::BindConstantBuffer()
    {
        GameObject* aowner = GetOwner();
        renderer::TransformCB trCB = {};
        trCB.mWorld = mWorld;
        Matrix CameraView = Camera::GetGpuViewMatrix();
        if (owner->ismove == false)
        {
            float depth = CameraView._43;
            CameraView = Matrix::Identity;
            CameraView._43 = depth;
        }
        trCB.mView = CameraView;
        trCB.mProjection = Camera::GetGpuProjectionMatrix();

        Matrix result = trCB.mWorld * trCB.mView * trCB.mProjection;
        ConstantBuffer* cb = renderer::constantBuffer[(UINT)ECBType::Transform];
       
        cb->SetData(&trCB);
        cb->Bind(EShaderStage::VS);
    }
    Vector3 Transform::GetPosition()
    {
        std::shared_ptr<GameObject> parent = owner->parent;
        if (parent != nullptr)
        {
            Vector3 value = parent->GetComponent<Transform>()->position;
            value += mPosition;
            return value;
        }
        else
        {
            return mPosition;
        }
    }
    Vector3 Transform::GetRotation()
    {
        std::shared_ptr<GameObject> parent = owner->parent;
        if (parent != nullptr)
        {
            Vector3 value = parent->GetComponent<Transform>()->rotation;
            value += mRotation;
            return value;
        }
        else
        {
            return mRotation;
        }
    }
    Vector3 Transform::GetScale()
    {
        std::shared_ptr<GameObject> parent = owner->parent;
        if (parent != nullptr)
        {
            Vector3 value = parent->GetComponent<Transform>()->scale;
            value += mScale;
            return value;
        }
        else
        {
            return mScale;
        }
    }
    float Transform::GetWorldZ()
    {
        return mWorld._43;
    }
}