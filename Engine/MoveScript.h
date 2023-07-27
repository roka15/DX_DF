#pragma once
#include "Script.h"
namespace roka
{
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

		void SetSpeed(float speed) { mSpeed = speed; }
		void SetKeys(UINT right, UINT left, UINT up, UINT down);

		void VerticalMove(UINT vertical);
		void HorizontalMove(UINT horizontal);
		void VerticalStop(UINT vertical);
		void HorizontalStop(UINT horizontal);
		SET_PROPERTY(SetSpeed) float speed;
	private:
		friend class FactoryBase;
		friend class ScriptFactory;
		float mSpeed;

		UINT mVerticalActiveKey;
		UINT mHorizontalActiveKey;
		bool mIsVertical;
		bool mIsHorizontal;

		UINT mRightKey;
		UINT mLeftKey;
		UINT mUpKey;
		UINT mDownKey;
	};
}


