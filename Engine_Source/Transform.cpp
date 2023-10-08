#include "Transform.h"
#include "Camera.h"
#include "ConstantBuffer.h"
#include "Renderer.h"
#include "GameObject.h"
#include "Object.h"
#include "UI.h"
#include "..\\Engine\\Prefab.h"
namespace roka
{
	using namespace roka::graphics;

	Transform::Transform()
		:Component(EComponentType::Transform)
		, mPosition(Vector3::Zero)
		, mRotation(Vector3::Zero)
		, mScale(Vector3::One)
		, mPivot(Vector3::Zero)
		, mbPivot(false)
	{
	}
	Transform::Transform(const Transform& ref) :Component(ref)
	{
		mPosition = ref.mPosition;
		mRotation = ref.mRotation;
		mScale = ref.mScale;
		mPivot = ref.mPivot;
		mbPivot = ref.mbPivot;

		mUp = ref.mUp;
		mForward = ref.mForward;
		mRight = ref.mRight;

		mWorld = ref.mWorld;
	}
	void Transform::Copy(Component* src)
	{
		Component::Copy(src);
		Transform* source = dynamic_cast<Transform*>(src);
		mPosition = source->mPosition;
		mRotation = source->mRotation;
		mScale = source->mScale;
		mPivot = source->mPivot;
		mbPivot = source->mbPivot;

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
		//��ġ,ũ��,ȸ�� ����
	}
	void Transform::LateUpdate()
	{
		//world space ����
		mWorld = Matrix::Identity;

		if (mbPivot == true)
		{
			Vector2 sign = Vector2::Zero;

			if (mPivot.x < 0.5)
			{
				sign.x = 1.0f;
			}
			else if (mPivot.x > 0.5)
			{
				sign.x = -1.0f;
			}
			if (mPivot.y < 0.5)
			{
				sign.y = 1.0f;
			}
			else if (mPivot.y > 0.5)
			{
				sign.y = -1.0f;
			}
			//�������� pivot������ �Ÿ�
			Vector2 offset = Vector2::Zero;
			offset.x = fabs(0.5f - mPivot.x);
			offset.y = fabs(0.5f - mPivot.y);

			//pivot Ų ���� ������ �������� �߽ɿ��� pivot������ �Ÿ�
			Vector2 diff = Vector2(mPivotOriginScale.x, mPivotOriginScale.y);
			diff.x = diff.x * offset.x;
			diff.y = diff.y * offset.y;

			//���� scale ���� �߽ɿ��� �ش� scale ���� pivot������ �Ÿ�
			Vector2 diff2 = Vector2(mScale.x, mScale.y);
			diff2.x = diff2.x * offset.x;
			diff2.y = diff2.y * offset.y;

			Vector2 result_diff = Vector2::Zero;
			result_diff.x = fabs(diff.x - diff2.x) * sign.x;
			result_diff.y = fabs(diff.y - diff2.y) * sign.y;

			mPosition.x = mPivotOriginPos.x + result_diff.x;
			mPosition.y = mPivotOriginPos.y + result_diff.y;
		}
		Vector3 worldScale = GetScale();
		Matrix scale;

		scale = Matrix::CreateScale(mScale);


		Matrix rotation = Matrix::CreateRotationX(mRotation.x);
		rotation *= Matrix::CreateRotationY(mRotation.y);
		rotation *= Matrix::CreateRotationZ(mRotation.z);
		Matrix position;

		position.Translation(mPosition);

		mWorld = scale * rotation * position;

		std::shared_ptr<GameObject> parent = owner->parent;
		if (parent)
		{
			if (owner->GetName().compare(L"WeaponSubPart") == 0)
				int a = 0;
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
		bool flag = false;
		if (owner->layer_type == ELayerType::UI)
		{
			UI* ui = dynamic_cast<UI*>(owner);
			if (ui != nullptr)
			{
				RECT viewPort = {};
				viewPort = ui->GetViewPortRect();
				if (viewPort.left != 0.0f && viewPort.top != 0.0f &&
					viewPort.right != 0.0f && viewPort.bottom != 0.0f)
				{
					trCB.mProjection = Camera::GetProjectionCalculate(viewPort);
					flag = true;
				}
			}
		}
		if (flag == false)
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
			value *= mScale;
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
	void Transform::EnablePivot()
	{
		mbPivot = true;
		mPivotOriginScale = mScale;
		mPivotOriginPos = mPosition;
	}
	void Transform::DisablePivot()
	{
		mbPivot = false;
	}
	Vector3 Transform::GetLeftTop()
	{
		Vector2 distance = GetRadius();//* 2.0f;
		return  Vector3(mPosition.x - distance.x, mPosition.y + distance.y, mPosition.z);
	}
	Vector3 Transform::GetRightTop()
	{
		Vector2 distance = GetRadius();
		return  Vector3(mPosition.x + distance.x, mPosition.y + distance.y, mPosition.z);
	}
	Vector3 Transform::GetLeftBottom()
	{
		Vector2 distance = GetRadius();
		return  Vector3(mPosition.x - distance.x, mPosition.y - distance.y, mPosition.z);
	}
	Vector3 Transform::GetRightBottom()
	{
		Vector2 distance = GetRadius();
		return  Vector3(mPosition.x + distance.x, mPosition.y - distance.y, mPosition.z);
	}
	Vector2 Transform::GetRadius()
	{
		Vector3 scale = GetScale();
		Vector2 radius = Vector2(scale.x * 0.5f, scale.y * 0.5f);
		return radius;
	}
}