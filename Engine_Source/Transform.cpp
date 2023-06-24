#include "Transform.h"
#include "Camera.h"
#include "ConstantBuffer.h"
#include "Renderer.h"

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

        mUp = Vector3::TransformNormal(Vector3::Up, rotation);
        mRight = Vector3::TransformNormal(Vector3::Right, rotation);
        mForward = Vector3::TransformNormal(Vector3::Forward, rotation);
    }
    void Transform::Render()
    {
    }
    void Transform::BindConstantBuffer()
    {
        renderer::TransformCB trCB = {};
        trCB.mWorld = mWorld;
        trCB.mView = Camera::GetViewMatrix();
        trCB.mProjection = Camera::GetProjectionMatrix();

        ConstantBuffer* cb = renderer::constantBuffer[(UINT)ECBType::Transform];
       
        cb->SetData(&trCB);
        cb->Bind(EShaderStage::VS);
    }
}