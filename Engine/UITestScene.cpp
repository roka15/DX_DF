#include "UITestScene.h"
#include "Resources.h"

#include "RokaTime.h"
#include "Object.h"
#include "Image.h"
#include "Light.h"
#include "CollisionManager.h"
#include "PortalManager.h"

#include "Mesh.h"
#include "Material.h"

#include "NPK.h"
#include "Prefab.h"
#include "Input.h"
#include "Renderer.h"

#include "Collider2D.h"
#include "MeshRenderer.h"
#include "Transform.h"
#include "Camera.h"
#include "CameraScript.h"
#include "GridScript.h"
#include "ImageComponent.h"
#include "Animator.h"
#include "PlayerScript.h"
#include "ChangeSizeOverTime.h"
#include "ScrollView.h"
#include "ScrollRect.h"
#include "GridGroupLayout.h"
#include "AudioListener.h"
#include "FontWrapper.h"
#include "Text.h"
namespace roka
{
	UITestScene::UITestScene():Scene(ESceneType::UITestScene)
	{
	}
	UITestScene::~UITestScene()
	{
	}
	void UITestScene::Initialize()
	{
		Scene::Initialize();
		std::shared_ptr<NPK> inven_npk = Resources::Find<NPK>(L"inventory");
		//std::shared_ptr<ScrollView> scrollTest = object::Instantiate<ScrollView>();
	 //   std::shared_ptr<Texture> texture = inven_npk->CreateAtlas(L"inventory.img", 49, 50, L"InvenSlot");
		//std::shared_ptr<Transform> tf = scrollTest->GetComponent<Transform>();
		//std::shared_ptr<ScrollRect> rect = scrollTest->GetComponent<ScrollRect>();
		//{
		//	std::shared_ptr<roka::Image> testimg = object::Instantiate<roka::Image>();
		//	testimg->SetName(L"TestImage");
		//	testimg->AddComponent <Collider2D>();
		//	std::shared_ptr<Transform> tf = testimg->GetComponent<Transform>();
		//	tf->scale = Vector3(0.25f, 0.25f, 1.0f);
		//	std::shared_ptr<MeshRenderer> mesh = testimg->GetComponent<MeshRenderer>();
		//	mesh->mesh = Resources::Find<Mesh>(L"RectMesh");
		//	mesh->material->shader = Resources::Find<Shader>(L"AtlasShader");
		//	mesh->material->texture = texture;
		//	std::shared_ptr<ImageComponent> imageComp = testimg->GetComponent<ImageComponent>();
		//	imageComp->SetSprite(0);
		//	rect->AddContent(testimg);
		//}
		//{
		//	std::shared_ptr<roka::Image> testimg = object::Instantiate<roka::Image>();
		//	testimg->layer_type = ELayerType::UI;
		//	testimg->SetName(L"TestImage");
		//	testimg->AddComponent <Collider2D>();
		//	std::shared_ptr<Transform> tf = testimg->GetComponent<Transform>();
		//	tf->scale = Vector3(0.25f, 0.25f, 1.0f);
		//	std::shared_ptr<MeshRenderer> mesh = testimg->GetComponent<MeshRenderer>();
		//	mesh->mesh = Resources::Find<Mesh>(L"RectMesh");
		//	mesh->material->shader = Resources::Find<Shader>(L"AtlasShader");
		//	mesh->material->texture = texture;
		//	std::shared_ptr<ImageComponent> imageComp = testimg->GetComponent<ImageComponent>();
		//	imageComp->SetSprite(0);

		//	rect->AddContent(testimg);
		//}
		//{
		//	std::shared_ptr<roka::Image> testimg = object::Instantiate<roka::Image>();
		//	testimg->layer_type = ELayerType::UI;
		//	testimg->SetName(L"TestImage");
		//	testimg->AddComponent <Collider2D>();
		//	std::shared_ptr<Transform> tf = testimg->GetComponent<Transform>();
		//	tf->scale = Vector3(0.25f, 0.25f, 1.0f);
		//	std::shared_ptr<MeshRenderer> mesh = testimg->GetComponent<MeshRenderer>();
		//	mesh->mesh = Resources::Find<Mesh>(L"RectMesh");
		//	mesh->material->shader = Resources::Find<Shader>(L"AtlasShader");
		//	mesh->material->texture = texture;
		//	std::shared_ptr<ImageComponent> imageComp = testimg->GetComponent<ImageComponent>();
		//	imageComp->SetSprite(0);

		//	rect->AddContent(testimg);
		//}
		//{
		//	std::shared_ptr<roka::Image> testimg = object::Instantiate<roka::Image>();
		//	testimg->layer_type = ELayerType::UI;
		//	testimg->SetName(L"TestImage");
		//	testimg->AddComponent <Collider2D>();
		//	std::shared_ptr<Transform> tf = testimg->GetComponent<Transform>();
		//	tf->scale = Vector3(0.25f, 0.25f, 1.0f);
		//	std::shared_ptr<MeshRenderer> mesh = testimg->GetComponent<MeshRenderer>();
		//	mesh->mesh = Resources::Find<Mesh>(L"RectMesh");
		//	mesh->material->shader = Resources::Find<Shader>(L"AtlasShader");
		//	mesh->material->texture = texture;
		//	std::shared_ptr<ImageComponent> imageComp = testimg->GetComponent<ImageComponent>();
		//	imageComp->SetSprite(0);

		//	rect->AddContent(testimg);
		//}


		//std::shared_ptr<GameObject> content = rect->GetContent();
		//std::shared_ptr<GridGroupLayout> grid_layout = content->AddComponent<GridGroupLayout>();
		//grid_layout->SetInfo(Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), 3, 2);
		////grid_layout->SetCellSize(Vector2(2.0f, 3.0f));

		//SceneManager::DontDestroy(scrollTest);

		
	}
	void UITestScene::Update()
	{
		Scene::Update();
	}
	void UITestScene::LateUpdate()
	{
		Scene::LateUpdate();
	}
	void UITestScene::Render()
	{
		Scene::Render();
		FontWrapper::DrawFont(L"Test", 100, 100, 100, FONT_RGBA(255, 255, 255, 255));
	}
	void UITestScene::Release()
	{
		Scene::Release();
	}
	void UITestScene::Destroy()
	{
		Scene::Destroy();
	}
	void UITestScene::OnExit()
	{
		Scene::OnExit();
	}
	void UITestScene::OnEnter()
	{
		Scene::OnEnter();
		std::shared_ptr<GameObject> light = object::Instantiate<GameObject>();
		light->SetName(L"main_light");
		AddGameObject(ELayerType::Light, light);
		std::shared_ptr<Light> lightComp = light->AddComponent<Light>();
		lightComp->SetType(ELightType::Directional);
		lightComp->SetColor(Vector4(0.5f, 0.5f, 0.5f, 1.0f));


		std::shared_ptr<GameObject> UIcamera = object::Instantiate<GameObject>(
			Vector3(0.0f, 0.0f, -10.0f),
			ELayerType::UI);
		{
			UIcamera->SetName(L"UICamera");
			std::shared_ptr<Camera> cameraComp = UIcamera->AddComponent<Camera>();
			cameraComp->DisableLayerMasks();
			cameraComp->TurnLayerMask(ELayerType::UI, true);
			cameraComp->TurnLayerMask(ELayerType::Raycast, true);
			
			renderer::MainCamera = cameraComp;
			UIcamera->AddComponent<AudioListener>();
		}
		CollisionManager::SetLayer(ELayerType::Raycast, ELayerType::UI, true);
	}
	void UITestScene::Loading()
	{
		Scene::Loading();
	}
}