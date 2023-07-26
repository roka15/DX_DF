#include "Transform.h"
#include "Camera.h"
#include "ConstantBuffer.h"
#include "Renderer.h"
#include "GameObject.h"
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

       mChild = ref.mChild;
       mParent = ref.mParent;
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

        mChild = source->mChild;
        mParent = source->mParent;
    }
    Transform::~Transform()
    {
    }
    void Transform::Initialize()
    {
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

        mWorld = scale * rotation * position;

        std::shared_ptr<Transform> parent = mParent.lock();
        if(parent)
        {
            mWorld *= parent->mWorld;
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
        if (aowner->GetName().compare(L"HPFilter") == 0)
        {
            int a = 0;
        }
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
    void Transform::AddChild(std::shared_ptr<Transform> child)
    {
        mChild.push_back(child);
        child->parent = owner->GetComponent<Transform>();
    }
}