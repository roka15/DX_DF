#include "guiEditor.h"
#include "Renderer.h"

#include "Resources.h"
#include "Mesh.h"
#include "Material.h"

#include "Transform.h"
#include "MeshRenderer.h"
#include "GridScript.h"


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

		for (const roka::graphics::DebugMesh& mesh
			: roka::renderer::debugMeshs)
		{
			DebugRender(mesh);
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

	void Editor::DebugRender(const roka::graphics::DebugMesh& mesh)
	{
		DebugObject* debugObj = mDebugObjects[(UINT)mesh.type];


		debugObj->Render();
	}

}
