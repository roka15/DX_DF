#pragma once
#include "PlayerNormalAttackScript.h"
namespace roka
{
	class MageNormalAttackScript :
		public PlayerNormalAttackScript
	{
	protected:
		MageNormalAttackScript();
		MageNormalAttackScript(const MageNormalAttackScript& ref);
		virtual void Copy(Component* src);
	public:
		virtual ~MageNormalAttackScript() {}
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(std::shared_ptr<Collider2D> other) {}
		virtual void OnCollisionStay(std::shared_ptr<Collider2D> other) {}
		virtual void OnCollisionExit(std::shared_ptr<Collider2D> other) {}

		virtual void Play();
		virtual void Exit();

		virtual void Start();
		virtual void Middle();
		virtual void End();

		virtual void CreateColliderObject() {}
		virtual void DeleteColliderObject() {}
	private:
		friend class FactoryBase;
		friend class ScriptFactory;
	protected:
	};
}


