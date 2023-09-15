#include "PortalScript.h"
#include "SceneManager.h"
#include "GameObject.h"

#include "PlayerScript.h"
#include "Collider2D.h"
namespace roka
{
	PortalScript::PortalScript() : Script(EScriptType::Portal),
		mType(EMapType::None)
	{
	}
	PortalScript::PortalScript(const PortalScript& ref):Script(ref)
	{
		mType = ref.mType;
	}
	void PortalScript::Copy(Component* src)
	{
		PortalScript* source = dynamic_cast<PortalScript*>(src);
		mType = source->mType;
	}
	void PortalScript::Initialize()
	{
		Script::Initialize();
	}
	void PortalScript::Update()
	{
	}
	void PortalScript::LateUpdate()
	{
	}
	void PortalScript::Render()
	{
	}
	void PortalScript::OnCollisionEnter(std::shared_ptr<Collider2D> other)
	{
		std::shared_ptr<PlayerScript> player = other->owner->parent->GetComponent<PlayerScript>();
		if (player == nullptr)
			return;
		std::wstring key = L"";
		switch (mType)
		{
		case EMapType::SeriaRoom:
			key =L"SeriaGateScene";
			break;
		case EMapType::PlayTestScene:
			key = L"PlayScene";
			break;
		}
		SceneManager::LoadScene(key);
	}
	void PortalScript::OnCollisionStay(std::shared_ptr<Collider2D> other)
	{
	}
	void PortalScript::OnCollisionExit(std::shared_ptr<Collider2D> other)
	{
	}
}