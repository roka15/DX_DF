#include "Input.h"
#include "Application.h"
#include "RokaTime.h"
#include "..\\Engine\\InputManager.h"
#include "Camera.h"
#include "..\\Engine\\IMouseEvent.h"
extern roka::Application application;

namespace roka
{
	static manager::InputManager* M_Input = manager::InputManager::GetInstance();
	int ASCII[(UINT)EKeyCode::END] =
	{
		'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',
		'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L',
		'Z', 'X', 'C', 'V', 'B', 'N', 'M',

		VK_UP, VK_DOWN, VK_LEFT ,VK_RIGHT, VK_SPACE,
		VK_LBUTTON, VK_RBUTTON,
	};

	std::vector<Input::Key> Input::mKeys;
	Vector2 Input::mMousePos = Vector2::Zero;
	double Input::mTime = 0.0;
	int Input::mMousePosSameCheck = 0;
	void Input::Initialize()
	{
		for (UINT i = 0; i < (UINT)EKeyCode::END; i++)
		{
			Key keyInfo;
			keyInfo.key = (EKeyCode)i;
			keyInfo.state = EKeyState::None;
			keyInfo.bPressed = false;
			keyInfo.beforPress = 0.0;
			keyInfo.curPress = 0.0;

			mKeys.push_back(keyInfo);
		}
	}

	void Input::Update()
	{
		mTime += Time::DeltaTime();

		if (GetFocus())
		{
			KeyUpdate();
			MouseUpdate();
		}
		else
		{
			for (UINT i = 0; i < (UINT)EKeyCode::END; i++)
			{
				if (EKeyState::Down == mKeys[i].state
					|| EKeyState::Pressed == mKeys[i].state)
				{
					mKeys[i].state = EKeyState::Up;
				}
				else if (EKeyState::Up == mKeys[i].state)
				{
					mKeys[i].state = EKeyState::None;
				}

				mKeys[i].bPressed = false;
			}
		}
	}

	void Input::Render(HDC hdc)
	{

	}
	void Input::KeyUpdate()
	{
		for (UINT i = 0; i < (UINT)EKeyCode::END; i++)
		{
			if (GetAsyncKeyState(ASCII[i]) & 0x8000)
			{
				// ���� �����ӿ��� ���� �־���
				if (mKeys[i].bPressed)
				{
					mKeys[i].state = EKeyState::Pressed;
				}
				else
				{
					mKeys[i].state = EKeyState::Down;
					mKeys[i].beforPress = mKeys[i].curPress;
					mKeys[i].curPress = mTime;
				}
				M_Input->OnEvent((EKeyCode)i, mKeys[i].state);
				mKeys[i].bPressed = true;
			}
			else // ���� �����ӿ� Ű�� �������� �ʴ�.
			{
				// ���� �����ӿ� ��Ű�� �����־���.
				if (mKeys[i].bPressed)
				{
					mKeys[i].state = EKeyState::Up;
					M_Input->OnEvent((EKeyCode)i, EKeyState::Up);
				}
				else
					mKeys[i].state = EKeyState::None;

				mKeys[i].bPressed = false;
			}
		}
	}
	void Input::MouseUpdate()
	{
		POINT cursorPos = {};
		GetCursorPos(&cursorPos);
		ScreenToClient(application.GetHwnd(), &cursorPos);


		Viewport view;

		view.width = application.GetWidth();
		view.height = application.GetHeight();
		view.x = 0;
		view.y = 0;
		view.minDepth = 0.0f;
		view.maxDepth = 1.0f;
		Vector3 Pos = { (float)cursorPos.x,(float)cursorPos.y,0.0f };
		Pos = view.Unproject(Pos, Camera::GetGpuProjectionMatrix(), Camera::GetGpuViewMatrix(), Matrix::Identity);
		if (mMousePos.x == Pos.x && mMousePos.y == Pos.y)
			mMousePosSameCheck++;
		else
			mMousePosSameCheck = 0;

		mMousePos.x = Pos.x;
		mMousePos.y = Pos.y;

		std::vector<PointerEventData*> vec = {};
		for (int i = 0; i < 300; i++)
		{
			vec.push_back(new PointerEventData());
		}

		for (auto& pointer : vec)
		{
			delete pointer;
		}
	
	}
}
