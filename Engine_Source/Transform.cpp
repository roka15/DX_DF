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
		LateUpdate();
	}
	void Transform::Update()
	{
		//위치,크기,회전 적용
	}
	void Transform::LateUpdate()
	{
		//world space 적용
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
			//중점에서 pivot까지의 거리
			Vector2 offset = Vector2::Zero;
			offset.x = fabs(0.5f - mPivot.x);
			offset.y = fabs(0.5f - mPivot.y);

			//pivot 킨 순간 원본의 기준으로 중심에서 pivot까지의 거리
			Vector2 diff = Vector2(mPivotOriginScale.x, mPivotOriginScale.y);
			diff.x = diff.x * offset.x;
			diff.y = diff.y * offset.y;

			//현재 scale 기준 중심에서 해당 scale 기준 pivot까지의 거리
			Vector2 diff2 = Vector2(mScale.x, mScale.y);
			diff2.x = diff2.x * offset.x;
			diff2.y = diff2.y * offset.y;

			Vector2 result_diff = Vector2::Zero;
			result_diff.x = fabs(diff.x - diff2.x) * sign.x;
			result_diff.y = fabs(diff.y - diff2.y) * sign.y;

			mPosition.x = mPivotOriginPos.x + result_diff.x;
			mPosition.y = mPivotOriginPos.y + result_diff.y;
		}
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
			if (mPosition.x == 1.0f && mPosition.y == 0.025f)
				int a = 0;
			std::shared_ptr<Transform> tf = parent->GetComponent<Transform>();
			mWorld *= tf->mWorld;
			if (owner->GetName().compare(L"Eft01") == 0)
				int a = 0;
			//mWorld = mWorld*tf->mWorld.Invert();
		}
		mWorldPosition = Vector3(mWorld._41, mWorld._42, mWorld._43);
		mWorldScale = Vector3(mWorld._11, mWorld._22, mWorld._33);

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
	void Transform::SetWorldPosition(Vector3 world)
	{
		if (owner->parent == nullptr)
		{
			mPosition = world;
			return;
		}
		
		std::shared_ptr<Transform> parentTf = owner->parent->GetComponent<Transform>();
		Matrix Invert_parentMat = parentTf->GetMatrix().Invert();
		Matrix worldMat = Matrix::CreateTranslation(world);
		Matrix localMat = Invert_parentMat * worldMat;

		mPosition = Vector3(localMat._41, localMat._42, localMat._43);
	}
	Vector3 Transform::GetPosition()
	{
		/*std::shared_ptr<GameObject> parent = owner->parent;
		if (parent != nullptr)
		{
			Vector3 value = parent->GetComponent<Transform>()->position;
			value += mPosition;
			return value;
		}
		else
		{
			return mPosition;
		}*/
		//LateUpdate();
		Matrix scale = Matrix::CreateScale(mScale);
		Matrix rotation = Matrix::CreateRotationX(mRotation.x);
		rotation *= Matrix::CreateRotationY(mRotation.y);
		rotation *= Matrix::CreateRotationZ(mRotation.z);
		Matrix position;

		position.Translation(mPosition);

		mWorld = scale * rotation * position;

		std::shared_ptr<GameObject> parent = owner->parent;
		if (parent)
		{
			if (mPosition.x == 1.0f && mPosition.y == 0.025f)
				int a = 0;
			std::shared_ptr<Transform> tf = parent->GetComponent<Transform>();
			mWorld *= tf->mWorld;
			if (owner->GetName().compare(L"Eft01") == 0)
				int a = 0;
			//mWorld = mWorld*tf->mWorld.Invert();
		}
		
		return Vector3(mWorld._41,mWorld._42,mWorld._43);
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
			/*std::shared_ptr<GameObject> parent = owner->parent;
			if (parent != nullptr)
			{
				Vector3 value = parent->GetComponent<Transform>()->scale;
				value *= mScale;
				return value;
			}
			else
			{
				return mScale;
			}*/
		//LateUpdate();
		Matrix scale = Matrix::CreateScale(mScale);
		Matrix rotation = Matrix::CreateRotationX(mRotation.x);
		rotation *= Matrix::CreateRotationY(mRotation.y);
		rotation *= Matrix::CreateRotationZ(mRotation.z);
		Matrix position;

		position.Translation(mPosition);

		mWorld = scale * rotation * position;

		std::shared_ptr<GameObject> parent = owner->parent;
		if (parent)
		{
			if (mPosition.x == 1.0f && mPosition.y == 0.025f)
				int a = 0;
			std::shared_ptr<Transform> tf = parent->GetComponent<Transform>();
			mWorld *= tf->mWorld;
			if (owner->GetName().compare(L"Eft01") == 0)
				int a = 0;
			//mWorld = mWorld*tf->mWorld.Invert();
		}
		return Vector3(mWorld._11,mWorld._22,mWorld._33);
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

}