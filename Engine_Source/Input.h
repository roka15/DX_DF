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

	class Input
	{
	public:
		struct Key
		{
			EKeyCode key;
			EKeyState state;
			bool bPressed;
		};

		static void Initialize();
		static void Update();
		static void Render(HDC hdc);

		inline static EKeyState GetKeyState(EKeyCode keyCode)
		{
			return mKeys[(UINT)keyCode].state;
		};

		//GetKey()		Ű�� ������ �ð���ŭ true�� ��ȯ
		//GetKeyDown()	Ű�� ������ ��, �� �ѹ� true�� ��ȯ
		//GetKeyUp()	Ű�� ������ ���� ��, �� �ѹ� true�� ��ȯ

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
		
		static __forceinline Vector2 GetMousePos() { return mMousePos; }

	private:
		static std::vector<Key> mKeys;
		static Vector2 mMousePos;
	};
}
