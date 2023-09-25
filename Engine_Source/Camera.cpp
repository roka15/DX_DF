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
	bool CompareZSort(std::shared_ptr<GameObject> obj1, std::shared_ptr<GameObject> obj2)
	{
		if (obj1->GetComponent<Transform>()->GetWorldZ()
			<= obj2->GetComponent<Transform>()->GetWorldZ())
			return false;

		return true;
	}
	Matrix Camera::View = Matrix::Identity;
	Matrix Camera::Projection = Matrix::Identity;

	Camera::Camera() :Component(EComponentType::Camera)
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
	Camera::Camera(const Camera& ref) :Component(ref)
	{
		mView = ref.mView;
		mProjection = ref.mProjection;
		mAspectRatio = ref.mAspectRatio;
		mNear = ref.mNear;
		mFar = ref.mFar;
		mSize = ref.mSize;
		mType = ref.mType;
		mOpaqueGameObjects = ref.mOpaqueGameObjects;
		mCutOutGameObjects = ref.mCutOutGameObjects;
		mTransparentObjects = ref.mTransparentObjects;
	}
	Camera::~Camera()
	{
		mOpaqueGameObjects.clear();
		mCutOutGameObjects.clear();
		mTransparentObjects.clear();
	}
	void Camera::Initialize()
	{
		Component::Initialize();
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

		AlphaSortGameObjects();
		ZSortTransparencyGameObjects();

		RenderOpaque();
		DisableDepthStencilState();
		RenderCutOut();
		RenderTransparent();
		EnableDepthStencilState();
	}
	void Camera::Release()
	{
		mOpaqueGameObjects.clear();
		mCutOutGameObjects.clear();
		mTransparentObjects.clear();
	}
	void Camera::Copy(Component* src)
	{
		Component::Copy(src);
		Camera* source = dynamic_cast<Camera*>(src);
		if (source == nullptr)
			return;
		mView = source->mView;
		mProjection = source->mProjection;
		mAspectRatio = source->mAspectRatio;
		mNear = source->mNear;
		mFar = source->mFar;
		mSize = source->mSize;
		mType = source->mType;
		mOpaqueGameObjects = source->mOpaqueGameObjects;
		mCutOutGameObjects = source->mCutOutGameObjects;
		mTransparentObjects = source->mTransparentObjects;
	}
	bool Camera::CreateViewMatrix()
	{
		std::shared_ptr<Transform> tf = owner->GetComponent<Transform>();
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
		renderer::cameras.push_back(shared_from_this());
	}
	void Camera::TurnLayerMask(ELayerType type, bool enable)
	{
		mLayerMask.set((UINT)type, enable);
	}
	void Camera::AlphaSortGameObjects()
	{
		mOpaqueGameObjects.clear();
		mCutOutGameObjects.clear();
		mTransparentObjects.clear();

		const std::vector<std::shared_ptr<GameObject>> objs = SceneManager::GetGameObjects(mLayerMask);
		DivideAlphaBlendGameObjects(objs);

	}
	void Camera::ZSortTransparencyGameObjects()
	{
		std::sort(mCutOutGameObjects.begin(), mCutOutGameObjects.end(), CompareZSort);
		std::sort(mTransparentObjects.begin(), mTransparentObjects.end(), CompareZSort);
	}
	void Camera::DivideAlphaBlendGameObjects(const std::vector<std::shared_ptr<GameObject>> objs)
	{
		for (std::shared_ptr<GameObject> obj : objs)
		{
			std::shared_ptr<MeshRenderer> mr = obj->GetComponent<MeshRenderer>();
			if (mr != nullptr)
			{
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
			if (obj->GetChildCont() != 0)
				DivideAlphaBlendGameObjects(obj->GetChilds());
		}
	}
	void Camera::RenderOpaque()
	{
		for (std::shared_ptr<GameObject> obj : mOpaqueGameObjects)
		{
			if (obj == nullptr)
				continue;
			if (obj->GetState() != GameObject::EState::Active)
				continue;
			obj->Render();
		}
	}
	void Camera::RenderCutOut()
	{
		for (std::shared_ptr<GameObject> obj : mCutOutGameObjects)
		{
			if (obj == nullptr)
				continue;
			if (obj->GetState() != GameObject::EState::Active)
				continue;
			obj->Render();
		}
	}
	void Camera::RenderTransparent()
	{
		int index = 0;
		for (std::shared_ptr<GameObject> obj : mTransparentObjects)
		{
			if (obj == nullptr)
				continue;
			if (obj->GetState() != GameObject::EState::Active)
				continue;
			if (obj->GetName().compare(L"Base") == 0 ||
				obj->GetName().compare(L"MGateRight") == 0)
			{
				int a = 0;
			}
			obj->Render();
			index++;
		}
	}
	void Camera::EnableDepthStencilState()
	{
		GetDevice()->BindDepthStencilState(renderer::depthstencilStates[(UINT)EDSType::LessEqual].Get());
	}
	void Camera::DisableDepthStencilState()
	{
		GetDevice()->BindDepthStencilState(renderer::depthstencilStates[(UINT)EDSType::None].Get());
	}
}