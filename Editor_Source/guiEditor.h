#pragma once
#include "CommonInclude.h"
#include "RokaEngine.h"
#include "RokaGraphics.h"
#include "guiDebugObject.h"
#include "guiEditorObject.h"
#include "guiWidget.h"
namespace gui
{
	class Editor
	{
	public:
		static void Initialize();
		static void Run();

		static void Update();
		static void LateUpdate();
		static void Render();
		static void Release();

		static void DebugRender(const roka::graphics::DebugMesh& mesh);
	private:
		static std::vector<Widget*> mWidgets;
		static std::vector<EditorObject*> mEditorObjects;
		static std::vector<DebugObject*> mDebugObjects;
	};
}


