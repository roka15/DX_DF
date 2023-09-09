#include "Script.h"

namespace roka
{
	Script::Script(const Script& ref)
		:Component(ref),
		mScriptType(ref.mScriptType)
	{
	}
	Script::Script(EScriptType type):Component(EComponentType::Script),mScriptType(type)
	{
	}

    Script::~Script()
	{
	}

	void Script::Copy(Component* src)
	{
		Component::Copy(src);
		Script* source = dynamic_cast<Script*>(src);
		if (source == nullptr)
			return;
		mScriptType = source->mScriptType;
	}

	void Script::Initialize()
	{
		Component::Initialize();
	}

	void Script::Update()
	{
	}

	void Script::LateUpdate()
	{
	}

	void Script::Render()
	{
	}

}
