#include "guiEditorObject.h"

namespace gui
{
	EditorObject::EditorObject()
	{
	}

	EditorObject::~EditorObject()
	{
	}

	void EditorObject::Initialize()
	{
	}

	void EditorObject::Update()
	{
		GameObject::Update();
	}

	void EditorObject::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void EditorObject::Render()
	{
		GameObject::Render();
	}

	void EditorObject::Copy(GameObject* src)
	{
		GameObject::Copy(src);
	}

}

