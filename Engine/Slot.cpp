#include "Slot.h"

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

}
