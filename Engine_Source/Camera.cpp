#include "Camera.h"
#include "GameObject.h"
#include "Transform.h"
#include "Application.h"
#include "Renderer.h"

extern roka::Application application;
namespace roka
{
	Matrix Camera::mView = Matrix::Identity;
	Matrix Camera::mProjection = Matrix::Identity;

	Camera::Camera() :Component(EComponentType::Script)
		, mType(EProjectionType::OrthoGraphic)
		, mAspectRatio(1.0f)
		, mNear(1.0f)
		, mFar(1000.0f)
		, mSize(5.0f)
		, mLayerMask{}
		, mOpaqueGameObjects{}
		, mCutOutGameObjects{}
		, mTransparentObjects{}
	{
	}
	Camera::~Camera()
	{
	}
	void Camera::Initialize()
	{
		EnableLayerMasks();
	}
	void Camera::Update()
	{
	}
	void Camera::LateUpdate()
	{
		CreateViewMatrix();
		CreateProjectionMatrix(mType);
		RegisterCameraInRenderer();
	}
	void Camera::Render()
	{
		SortGameObjects();

		RenderOpaque();
		RenderCutOut();
		RenderTransparent();
	}
	bool Camera::CreateViewMatrix()
	{
		Transform* tf = owner->GetComponent<Transform>();
		Vector3 pos = tf->position;
		mView = Matrix::Identity;

		mView *= Matrix::CreateTranslation(-pos);

		Vector3 up = tf->up;
		Vector3 forword = tf->forward;
		Vector3 right = tf->right;

		Matrix rotationView = Matrix::Identity;

		rotationView._11 = right.x;
		rotationView._21 = right.y;
		rotationView._31 = right.z;

		rotationView._12 = up.x;
		rotationView._22 = up.y;
		rotationView._32 = up.z;

		rotationView._13 = forword.x;
		rotationView._23 = forword.y;
		rotationView._33 = forword.z;

		mView *= rotationView;

		return true;
	}
	bool Camera::CreateProjectionMatrix(EProjectionType type)
	{
		RECT rect = {};
		GetClientRect(application.GetHwnd(), &rect);

		float width = rect.right - rect.left;
		float height = rect.bottom - rect.top;
		mAspectRatio = width / height;

		if (type == EProjectionType::OrthoGraphic)
		{
			float orthoGraphicRatio = mSize / mFar;
			width *= orthoGraphicRatio;
			height *= orthoGraphicRatio;

			mProjection = Matrix::CreateOrthographicLH(width, height, mNear, mFar);
		}
		else
		{
			mProjection = Matrix::CreatePerspectiveFieldOfViewLH(XM_2PI / 6.0f, mAspectRatio, mNear, mFar);
		}
		return true;
	}
	void Camera::RegisterCameraInRenderer()
	{
		renderer::cameras.push_back(this);
	}
	void Camera::TurnLayerMask(ELayerType type, bool enable)
	{
		mLayerMask.set((UINT)type, enable);
	}
	void Camera::SortGameObjects()
	{
		
	}
	void Camera::RenderOpaque()
	{
		for (GameObject* obj : mOpaqueGameObjects)
		{
			if (obj == nullptr)
				continue;
			obj->Render();
		}
	}
	void Camera::RenderCutOut()
	{
		for (GameObject* obj : mCutOutGameObjects)
		{
			if (obj == nullptr)
				continue;
			obj->Render();
		}
	}
	void Camera::RenderTransparent()
	{
		for (GameObject* obj : mTransparentObjects)
		{
			if (obj == nullptr)
				continue;
			obj->Render();
		}
	}
}