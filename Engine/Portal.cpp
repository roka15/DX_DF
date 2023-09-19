#include "Portal.h"
#include "SceneManager.h"
#include "GameObject.h"
#include "Collider2D.h"
#include "PlayerScript.h"
#include "PortalManager.h"
namespace roka
{
	void Portal::SetCollisionListener(std::shared_ptr<GameObject>& obj)
	{
		std::shared_ptr<Collider2D> collider = obj->GetComponent<Collider2D>();
		collider->SetCollisionListener(this);
	}
}
namespace roka
{
	void DirectPortal::OnCollisionEnter(std::shared_ptr<GameObject> caster, std::shared_ptr<GameObject> target)
	{
		std::shared_ptr<PlayerScript> player = target->parent->GetComponent<PlayerScript>();
		if (player == nullptr)
			return;
		Scene* scene = SceneManager::GetActiveScene();
	
		ESceneType nextScene = mConnectScene;
		
		Portal* nextPortal = manager::PortalManager::GetInstance()->Find(mConnectPortal);
		if (nextPortal != nullptr)
		{
			DirectPortal* direct = dynamic_cast<DirectPortal*>(nextPortal);
			if (direct != nullptr)
			{
				direct->SetConnectPortal(mCurPortal);
				direct->SetConnectScene(mCurScene);
			}
		}
		
		SceneManager::LoadScene(nextScene);
	}
	void DirectPortal::OnCollisionStay(std::shared_ptr<GameObject> caster, std::shared_ptr<GameObject> target)
	{
	}
	void DirectPortal::OnCollisionExit(std::shared_ptr<GameObject> caster, std::shared_ptr<GameObject> target)
	{
	}
}
namespace roka
{
	void SelectPortal::OnCollisionEnter(std::shared_ptr<GameObject> caster, std::shared_ptr<GameObject> target)
	{
	}
	void SelectPortal::OnCollisionStay(std::shared_ptr<GameObject> caster, std::shared_ptr<GameObject> target)
	{
	}
	void SelectPortal::OnCollisionExit(std::shared_ptr<GameObject> caster, std::shared_ptr<GameObject> target)
	{
	}
}

