#pragma once
#include "Component.h"
namespace roka
{
	class Script:public Component	
	{
	public:
		Script() = delete;
		Script(const Script& ref);
		Script(EScriptType type);
		virtual ~Script();
		virtual void Copy(Component* src)override;

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		EScriptType GetScriptType() { return mScriptType; }
		GET_PROPERTY(GetScriptType) EScriptType script_type;
	protected:
		EScriptType mScriptType;
	};

}

