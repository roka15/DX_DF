#include "guiEditor.h"
#include "Renderer.h"

#include "Resources.h"
#include "Mesh.h"
#include "Material.h"

#include "Transform.h"
#include "MeshRenderer.h"
#include "..\\Engine\\GridScript.h"
#include "..\\Engine_Source\\Application.h"
#include "..\\Editor_Source\\TileMapToolApplication.h"

extern roka::Application application;
extern roka::Application* applications[2];
extern roka::Application* focusApp;
namespace gui
{
	using namespace roka::enums;
	std::vector<Widget*> Editor::mWidgets = {};
	std::vector<EditorObject*> Editor::mEditorObjects = {};
	std::vector<DebugObject*> Editor::mDebugObjects = {};


	void Editor::Initialize()
	{
		mDebugObjects.resize((UINT)EColliderType::End);
		std::shared_ptr<roka::Mesh> mesh
			= roka::Resources::Find<roka::Mesh>(L"DebugRect");
		std::shared_ptr<roka::Material> material
			= roka::Resources::Find<roka::Material>(L"DebugMaterial");

		DebugObject* debugObj = new DebugObject();
		debugObj->AddComponent<roka::Transform>();
		std::shared_ptr<roka::MeshRenderer> mr = debugObj->AddComponent<roka::MeshRenderer>();
		mr->material = material;
		mr->mesh = mesh;
		mDebugObjects[(UINT)EColliderType::Rect] = debugObj;

		EditorObject* grid = new EditorObject();
		grid->SetName(L"Grid");

		mr = grid->AddComponent<roka::MeshRenderer>();
		mr->SetMesh(roka::Resources::Find<roka::Mesh>(L"RectMesh"));
		mr->SetMaterial(roka::Resources::Find<roka::Material>(L"GridMaterial"));
		std::shared_ptr<roka::GridScript> gridsc = grid->AddComponent<roka::GridScript>();
		gridsc->camera = roka::renderer::MainCamera;

		mEditorObjects.push_back(grid);
	}

	void Editor::Run()
	{
		Update();
		LateUpdate();
		Render();
	}

	void Editor::Update()
	{
		for (EditorObject* obj : mEditorObjects)
		{
			obj->Update();
			std::shared_ptr<roka::GridScript> gridsc = obj->GetComponent<roka::GridScript>();
			if (gridsc == nullptr)
				continue;
			if (gridsc->IsCamera() == false)
			{
				gridsc->camera = roka::renderer::MainCamera;
			}
		}
	}

	void Editor::LateUpdate()
	{
		for (EditorObject* obj : mEditorObjects)
		{
			obj->LateUpdate();
		}
	}

	void Editor::Render()
	{
		for (EditorObject* obj : mEditorObjects)
		{
			obj->Render();
		}
	}

	void Editor::Release()
	{
		for (auto widget : mWidgets)
		{
			delete widget;
			widget = nullptr;
		}

		for (auto editorObj : mEditorObjects)
		{
			delete editorObj;
			editorObj = nullptr;
		}

		for (auto debugObj : mDebugObjects)
		{
			delete debugObj;
			debugObj = nullptr;
		}
	}

	void Editor::DebugRender()
	{
		for (const roka::graphics::DebugMesh* mesh
			: roka::renderer::debugMeshs)
		{
			DebugRender(mesh);
			delete mesh;
		}
		roka::renderer::debugMeshs.clear();
	}

	void Editor::DebugRender(const roka::graphics::DebugMesh* mesh)
	{
		DebugObject* debugObj = mDebugObjects[(UINT)mesh->type];

		std::shared_ptr<roka::Transform> tf = debugObj->GetComponent<roka::Transform>();
		Vector3 pos = mesh->position;
		pos.z = -1.00f;
		if (mesh->parent!=nullptr &&mesh->parent->GetName().compare(L"Monster0") == 0)
			int a = 0;
		debugObj->SetParent(mesh->parent);
		tf->SetPosition(pos);
		tf->SetScale(mesh->scale);
		tf->SetRotation(mesh->rotation);
		tf->LateUpdate();

		debugObj->SetColor(mesh->color);

		std::shared_ptr<roka::Camera> mainCamera = roka::renderer::MainCamera;
		roka::Camera::SetGpuViewMatrix(mainCamera->GetViewMatrix());
		roka::Camera::SetGpuProjectionMatrix(mainCamera->GetProjectionMatrix());
		debugObj->Render();
	}

}
