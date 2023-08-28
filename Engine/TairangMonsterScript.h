#pragma once
#include "NamedMonsterScript.h"
namespace roka
{
	class TairangMonsterScript :
		public NamedMonsterScript
	{
	protected:
		TairangMonsterScript();
		TairangMonsterScript(const TairangMonsterScript& ref);
		void Copy(Component* src);
	public:
		virtual ~TairangMonsterScript() {}
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(std::shared_ptr<Collider2D> other)override;
		virtual void OnCollisionStay(std::shared_ptr<Collider2D> other)override;
		virtual void OnCollisionExit(std::shared_ptr<Collider2D> other)override;

		virtual void Ready()override;
		virtual void Idle()override;
		virtual void Move()override;
		virtual void Attack()override;

		virtual void SetTargetPos(Vector2& outDir, Vector2& outTargetPos)override;

		virtual void Skill01();
		virtual void Skill02();
		virtual void Skill03();
		virtual void Skill04();

		void Skill01SetPos();
	private:				  
		friend class FactoryBase;
		friend class ScriptFactory;
	protected:
	};
}


