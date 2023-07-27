#include "GridScript.h"
#include "GameObject.h"
#include "Transform.h"
#include "Application.h"
#include "Renderer.h"

extern roka::Application application;
namespace roka
{
	GridScript::GridScript()
		:Script(EScriptType::Grid),
         mCamera()
	{
	}

	GridScript::GridScript(const GridScript& ref):Script(ref)
	{
		mCamera = ref.mCamera;
	}

	void GridScript::Copy(Component* src)
	{
		Script::Copy(src);
		GridScript* source = dynamic_cast<GridScript*>(src);
		if (source == nullptr)
			return;
		mCamera = source->mCamera;
	}

	GridScript::~GridScript()
	{
	}

	void GridScript::Initialize()
	{
		Script::Initialize();
	}

	void GridScript::Update()
	{
		Script::Update();
		std::shared_ptr<Camera> cam = mCamera.lock();
		if (!cam)
			return;

		GameObject* obj = cam->GetOwner();

		std::shared_ptr<Transform> tf = obj->GetComponent<Transform>();
		Vector3 pos = tf->position;

		float size = cam->size;
		Vector2 scale(size, size);

		HWND hwnd = application.GetHwnd();
		RECT winRect = {};
		GetClientRect(hwnd, &winRect);

		float width = winRect.right - winRect.left;
		float height = winRect.bottom - winRect.top;
		Vector2 resolution(width, height);

		graphics::ConstantBuffer* cb =
			renderer::constantBuffer[(UINT)ECBType::Grid];

		renderer::GridCB gridbuf;
		gridbuf.CameraPos = Vector4(pos.x,pos.y,pos.z,1.00f);
		gridbuf.CameraScale = scale;
		gridbuf.Resolution = resolution;

		cb->SetData(&gridbuf);
		cb->Bind(EShaderStage::VS);
		cb->Bind(EShaderStage::PS);
	}

	void GridScript::LateUpdate()
	{
		Script::LateUpdate();
	}

	void GridScript::Render()
	{
		Script::Render();
	}
}

