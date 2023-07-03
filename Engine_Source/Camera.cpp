#include "Camera.h"
#include "GameObject.h"
#include "Transform.h"
#include "Application.h"
#include "Renderer.h"
#include "SceneManager.h"
#include "MeshRenderer.h"
extern roka::Application application;
namespace roka
{
	Matrix Camera::View = Matrix::Identity;
	Matrix Camera::Projection = Matrix::Identity;

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
		, mView(Matrix::Identity)
		, mProjection(Matrix::Identity)
	{
		EnableLayerMasks();
	}
	Camera::~Camera()
	{
	}
	void Camera::Initialize()
	{
		
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
		View = mView;
		Projection = mProjection;

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
		mOpaqueGameObjects.clear();
		mCutOutGameObjects.clear();
		mTransparentObjects.clear();

		Scene* scene = SceneManager::GetActiveScene();
		for (size_t i = 0; i < (UINT)ELayerType::End; i++)
		{
			if (mLayerMask[i] == false)
				continue;

			Layer& layer = scene->GetLayer((ELayerType)i);

			const std::vector<GameObject*> objs = layer.GetGameObjects();

			for (GameObject* obj : objs)
			{
				MeshRenderer* mr = obj->GetComponent<MeshRenderer>();
				if (mr == nullptr)
					continue;
				ERenderMode mode = mr->material->GetRenderMode();
				switch (mode)
				{
				case ERenderMode::Opaque:
					mOpaqueGameObjects.push_back(obj);
					break;
				case ERenderMode::CutOut:
					mCutOutGameObjects.push_back(obj);
					break;
				case ERenderMode::Transparent:
					mTransparentObjects.push_back(obj);
					break;
				}
			}
			
			
		}
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