#include "Slot.h"
#include "GameObject.h"
#include "Collider2D.h"
#include "UI.h"
namespace roka
{
	Slot::Slot():Script(EScriptType::Slot)
	{
	}
	Slot::Slot(const Slot& ref):Script(ref)
	{
	}
	void Slot::Copy(Component* src)
	{
		Slot* soruce = dynamic_cast<Slot*>(src);
		if (soruce == nullptr)
			return;
	}
	void Slot::Initialize()
	{
		Script::Initialize();
		owner->AddComponent<Collider2D>();
		UI* ui = dynamic_cast<UI*>(owner);
		ui->ui_type = EUIType::Slot;
	}

	void Slot::Update()
	{
	}

	void Slot::LateUpdate()
	{
	}

	void Slot::Render()
	{
	}

	void Slot::OnPointerEnter(PointerEventData* data)
	{
	}

	void Slot::AddItem()
	{
	}

	void Slot::RemveItem()
	{
	}

}
