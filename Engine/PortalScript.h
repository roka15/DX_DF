#pragma once
#include "Script.h"
#include "ContentEnums.h"
namespace roka
{
	class PortalScript :
		public Script
	{
	private:
		PortalScript();
		PortalScript(const PortalScript& ref);
		void Copy(Component* src);
	public:
		virtual ~PortalScript() {}

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(std::shared_ptr<Collider2D> other)override;
		virtual void OnCollisionStay(std::shared_ptr<Collider2D> other)override;
		virtual void OnCollisionExit(std::shared_ptr<Collider2D> other)override;

		void SetType(EMapType type) { mType = type; }
	private:
		friend class FactoryBase;
		friend class ScriptFactory;
		EMapType mType;
	};
}


