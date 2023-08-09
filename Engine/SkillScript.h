#pragma once
#include "Script.h"
#include "ContentEnums.h"
namespace roka
{
	class SkillScript : public Script
	{
	private:
		SkillScript();
		SkillScript(const SkillScript& ref);
		void Copy(Component* src);
	public:
		~SkillScript() {}
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(std::shared_ptr<Collider2D> other) {}
		virtual void OnCollisionStay(std::shared_ptr<Collider2D> other) {}
		virtual void OnCollisionExit(std::shared_ptr<Collider2D> other) {}

		EStunState GetStunType() { return mStunType; }
		void SetStunType(EStunState type) { mStunType = type;}
		PROPERTY(GetStunType, SetStunType) EStunState stun_type;
	private:
		friend class FactoryBase;
		friend class ScriptFactory;

		EStunState mStunType;
	};
}


