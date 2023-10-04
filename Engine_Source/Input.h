#pragma once
#include "RokaEngine.h"

namespace roka
{
	using namespace roka::math;
	enum class EKeyCode
	{
		Q, W, E, R, T, Y, U, I, O, P,
		A, S, D, F, G, H, J, K, L,
		Z, X, C, V, B, N, M,

		UP, DOWN, LEFT, RIGHT, SPACE,
		LBUTTON, RBUTTON,
		END,
	};

	enum class EKeyState
	{
		Down,
		Pressed,
		Up,
		None,
	};

	enum class EMouseBtnType
	{
		LEFT,
		RIGHT,
		NONE,
	};

	class Input
	{
	public:
		struct Key
		{
			EKeyCode key;
			EKeyState state;
			bool bPressed;
			double beforPress;
			double curPress;
		};

		static void Initialize();
		static void Update();
		static void Render(HDC hdc);

		inline static EKeyState GetKeyState(EKeyCode keyCode)
		{
			return mKeys[(UINT)keyCode].state;
		};

		//GetKey()		키를 누르는 시간만큼 true를 반환
		//GetKeyDown()	키를 눌렀을 때, 딱 한번 true를 반환
		//GetKeyUp()	키를 누르다 땠을 때, 딱 한번 true를 반환

		static __forceinline bool GetKey(EKeyCode keyCode)
		{
			return mKeys[static_cast<UINT>(keyCode)].state == EKeyState::Pressed;
		}

		static __forceinline bool GetKeyDown(EKeyCode keyCode)
		{
			return mKeys[static_cast<UINT>(keyCode)].state == EKeyState::Down;
		}

		static __forceinline bool GetKeyUp(EKeyCode keyCode)
		{
			return mKeys[static_cast<UINT>(keyCode)].state == EKeyState::Up;
		}
		
		static __forceinline bool GetAniKey()
		{
			for (auto key : mKeys)
			{
				if (key.state == EKeyState::Pressed || key.state == EKeyState::Down)
					return true;
			}
			return false;
		}
		static __forceinline bool GetAniKeyDown()
		{
			for (auto key : mKeys)
			{
				if (key.state == EKeyState::Down)
					return true;
			}
			return false;
		}
		static __forceinline Vector2 GetMousePos() { return mMousePos; }
		static __forceinline int GetMouseSameCnt() { return mMousePosSameCheck; }
		static __forceinline void SetMouseState(EMouseBtnType type, EKeyState state) { mMouseType = type; mMouseState = state; }

		static void MouseBtnDown(class PointerEventData* data);
		static void MouseBtnUp(class PointerEventData* data);
	private:
		static void KeyUpdate();
		static void MouseUpdate(HWND hWnd);
	private:
		static std::vector<Key> mKeys;
		static Vector2 mMousePos;
		static int mMousePosSameCheck;
		static EMouseBtnType mMouseType;
		static EKeyState mMouseState;
		static double mMouseLBUpTime;
		static double mMouseRBUpTime;
		static const double mDoubleClickTime;

		static double mTime;
	};
}
