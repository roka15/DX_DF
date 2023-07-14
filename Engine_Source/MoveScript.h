#pragma once
#include "Script.h"
namespace roka
{
	class MoveScript : public Script
	{
	private:
		MoveScript();
		MoveScript(const MoveScript& ref);
		virtual void Copy(Component* src)override;
	public:
		~MoveScript();
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;
	private:
		friend class ScriptFactory;
	};
}


