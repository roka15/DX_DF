#pragma once
#include "Script.h"
namespace roka
{
	class CameraScript : public Script
	{
	private:
		CameraScript();
		CameraScript(const CameraScript& ref);
		virtual void Copy(Component* src)override;
	public:
		virtual ~CameraScript();
		virtual void Initialize()override;
		virtual void Update()override;
	private:
		friend class FactoryBase;
		friend class ScriptFactory;

	};
}


