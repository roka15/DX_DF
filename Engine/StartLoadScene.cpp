#include "StartLoadScene.h"
#include "Object.h"
#include "Prefab.h"
#include "InputManager.h"

#include "GameObject.h"
#include "Image.h"
#include "Texture.h"
#include "NPK.h"
#include "Resources.h"
#include "Transform.h"
#include "MeshRenderer.h"
#include "Collider2D.h"
#include "ImageComponent.h"
#include "PlayerScript.h"



namespace roka
{
    manager::InputManager* MInput = manager::InputManager::GetInstance();
    void StartLoadScene::Initialize()
    {
        std::shared_ptr<GameObject> origin = prefab::Prefabs[L"PlayerObject"];
        std::shared_ptr<GameObject> player = object::Instantiate<GameObject>(origin);
        player->SetName(L"Player");
        std::shared_ptr<PlayerScript> playerScript = player->GetComponent<PlayerScript>();
        playerScript->LateInitialize();
        playerScript->RegisterKeyEvents();
        player->GetComponent<Transform>()->position = Vector3(0.0f, 0.0f, 0.3f);
        SceneManager::DontDestroy(player);

        std::shared_ptr<NPK> npk = Resources::Find<NPK>(L"infoBtn");
        std::shared_ptr<Texture> texture = npk->CreateAtlas(L"mouseIcon.img", 0, 3, L"MouseBtn");
        std::shared_ptr<roka::Image> Cursor = object::Instantiate<roka::Image>(Vector3(0.0f,0.0f,-10.0f),Vector3::Zero,Vector3(0.12f,0.12f,1.0f));
        Cursor->SetName(L"Cursor");
        Cursor->layer_type = ELayerType::Raycast;
        std::shared_ptr<MeshRenderer> mesh = Cursor->AddComponent<MeshRenderer>();
        mesh->material->texture = texture;
        mesh->mesh = Resources::Find<Mesh>(L"RectMesh");
      
        std::shared_ptr<ImageComponent> image = Cursor->GetComponent<ImageComponent>();
        image->SetSprite(1);
        std::shared_ptr<Collider2D> collider = Cursor->AddComponent<Collider2D>();
        
        MInput->SetCursor(Cursor);
        SceneManager::DontDestroy(Cursor);
    }
    void StartLoadScene::Update()
    {
    }
    void StartLoadScene::LateUpdate()
    {
    }
    void StartLoadScene::Render()
    {
    }
    void StartLoadScene::OnExit()
    {
    }
    void StartLoadScene::OnEnter()
    {
        SceneManager::LoadScene(ESceneType::SeriaRoom);
    }
    void StartLoadScene::Loading()
    {
    }
}