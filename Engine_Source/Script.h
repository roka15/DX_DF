#pragma once
#include "Component.h"
namespace roka
{
	class Script:public Component	
	{
	public:
		Script();
		virtual ~Script();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;
	private:
	};

}

