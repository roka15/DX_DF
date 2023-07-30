#pragma once
#include "Script.h"
#include "ContentEnums.h"
namespace roka
{
	class PartScript :
		public Script
	{
	private:
		PartScript();
		PartScript(const PartScript& ref);
		void Copy(Component* src);
	public:
		~PartScript();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void SetPartType(EAvatarParts type) { mPartType = type; }
		EAvatarParts GetPartType() { return mPartType; }

		PROPERTY(GetPartType,SetPartType) EAvatarParts part_type;
	private:
		friend class FactoryBase;
		friend class ScriptFactory;
		EAvatarParts mPartType;
	};
}


