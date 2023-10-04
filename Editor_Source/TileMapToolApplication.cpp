#include "TileMapToolApplication.h"
#include "guiEditorObject.h"
#include "Renderer.h"
#include "Transform.h"
#include "MeshRenderer.h"
#include "Resources.h"
#include "NPK.h"
#include "Texture.h"
#include "Camera.h"
namespace roka
{
	TileMapToolApplication::TileMapToolApplication() :Application()
	{
		mType = EApplicationType::TileTool;
		mNPKKey = L"baseskin";
	}
	void TileMapToolApplication::Run()
	{
		if (mbActive == false)
			return;
		Update();
		LateUpdate();
		Render();
		Destroy();
	}
	void TileMapToolApplication::Initialize()
	{
		int a = 0;
	}
	void TileMapToolApplication::Update()
	{
		if (mbActive == false)
			return;
	}
	void TileMapToolApplication::LateUpdate()
	{
		if (mbActive == false)
			return;
	}
	void TileMapToolApplication::Render()
	{
		if (mbActive == false)
			return;
		ClearTarget();
		roka::graphics::GetDevice()->UpdateViewPort(mType);
		std::shared_ptr<gui::EditorObject> TestObj = std::make_shared<gui::EditorObject>();
		std::shared_ptr<Transform> tf = TestObj->AddComponent<Transform>();
		std::shared_ptr<MeshRenderer> mr = TestObj->AddComponent<MeshRenderer>();
		mr->mesh = Resources::Find<Mesh>(L"RectMesh");
		mr->material->shader = Resources::Find<Shader>(L"AtlasShader");
		std::shared_ptr<NPK> npk = Resources::Find<NPK>(mNPKKey);
		std::shared_ptr<Texture> texture = npk->CreateAtlas(L"mg_body80500.img", 0, 1, L"TestTexture");
		mr->material->texture = texture;

		TestObj->Render();

	}
	void TileMapToolApplication::Release()
	{
	}
	void TileMapToolApplication::Destroy()
	{
	}
}