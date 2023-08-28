#pragma once
#include "MonsterScript.h"
namespace roka
{
	class NamedMonsterScript :
		public MonsterScript
	{
	protected:
		NamedMonsterScript();
		NamedMonsterScript(EScriptType type);
		NamedMonsterScript(const NamedMonsterScript& ref);
		void Copy(Component* src);
	public:
		virtual ~NamedMonsterScript() {}
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

		void RegisterSkillFunc(std::function<void()> func);

	private:
		friend class FactoryBase;
		friend class ScriptFactory;
	protected:
		std::vector<std::function<void()>> mSkillStartList;
		int mBeforSkillIndex;
	};
}


