#pragma once
#include "Script.h"
namespace roka
{
	using namespace math;
	class MoveScript : public Script
	{
	private:
		MoveScript();
		MoveScript(const MoveScript& ref);
		virtual void Copy(Component* src)override;
	public:
		~MoveScript();
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void AddSpeed(float value) { mSpeed *= value; }
		void ResetSpeed() { mSpeed = mOriginSpeed; }
		void SetSpeed(float speed) { mOriginSpeed =mSpeed= speed; }
		void SetDirX(float dir) { mDir.x = dir; }
		void SetDirY(float dir) { mDir.y = dir; }
		float GetDirX() { return mDir.x; }

		bool IsStop() { return mDir.x == 0.0f && mDir.y == 0.0f; }

		SET_PROPERTY(SetSpeed) float speed;
		GET_PROPERTY(IsStop) bool is_stop;
	private:
		friend class FactoryBase;
		friend class ScriptFactory;
		float mSpeed;
		float mOriginSpeed;
		Vector2 mDir;
		bool mbStop;
	};
}


