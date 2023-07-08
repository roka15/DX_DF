#include "GridScript.h"
#include "GameObject.h"
#include "Transform.h"
#include "Application.h"
#include "Renderer.h"
extern roka::Application application;
namespace roka
{
	GridScript::GridScript()
		:mCamera(nullptr)
	{
	}

	GridScript::~GridScript()
	{
	}

	void GridScript::Initialize()
	{
	}

	void GridScript::Update()
	{
		if (mCamera == nullptr)
			return;

		GameObject* obj = mCamera->GetOwner();

		Transform* tf = obj->GetComponent<Transform>();
		Vector3 pos = tf->position;

		float size = mCamera->size;
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
		gridbuf.CameraPos = Vector4(pos.x,pos.y,pos.z,1.0f);
		gridbuf.CameraScale = scale;
		gridbuf.Resolution = resolution;

		cb->SetData(&gridbuf);
		cb->Bind(EShaderStage::VS);
		cb->Bind(EShaderStage::PS);
	}

	void GridScript::LateUpdate()
	{
	}

	void GridScript::Render()
	{
	}
}

