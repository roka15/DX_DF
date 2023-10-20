#pragma once
#include "PartScript.h"
namespace roka
{
	class GameObject;
	class SkinPartScript :
		public PartScript
	{
	protected:
		SkinPartScript();
		SkinPartScript(const SkinPartScript& ref);
		virtual void Copy(Component* src);
	public:
		virtual ~SkinPartScript() {}

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void JumpDash()override;

		virtual void SetEvent()override;
		virtual void Create(std::wstring npk, std::wstring pack)override;
	private:
		friend class FactoryBase;
		friend class ScriptFactory;
	protected:
		std::vector<std::weak_ptr<GameObject>> mParts;

	};
}


