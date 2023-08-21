#pragma once
#include "MoveScript.h"
namespace roka
{
	using namespace math;
	class TargetMoveScript :
		public MoveScript
	{
	private:
		TargetMoveScript();
		TargetMoveScript(const TargetMoveScript& ref);
		void Copy(Component* src);
	public:
		~TargetMoveScript() {};
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(std::shared_ptr<Collider2D> other);
		virtual void OnCollisionStay(std::shared_ptr<Collider2D> other);
		virtual void OnCollisionExit(std::shared_ptr<Collider2D> other);

		void SetTargetPos(Vector2 pos) { mTargetPos = pos; }
		
	private:
		friend class FactoryBase;
		friend class ScriptFactory;

		Vector2 mTargetPos;

	};

}

