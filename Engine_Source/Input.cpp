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
	EMouseBtnType Input::mMouseType = EMouseBtnType::NONE;
	EKeyState Input::mMouseState = EKeyState::None;
	double Input::mMouseLBUpTime=0.0;
	double Input::mMouseRBUpTime=0.0;
	const double Input::mDoubleClickTime = 1.0;
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
	void Input::MouseBtnDown(PointerEventData* data)
	{
		if (mTime - mMouseLBUpTime <= mDoubleClickTime)
		{
			//double click
			data->click_cnt++;
		}
		else if (mMouseState == EKeyState::Down)
		{
			//state-> pressed
			mMouseState = EKeyState::Pressed;
			data->click_cnt = 1;
		}
	}
	void Input::MouseBtnUp(PointerEventData* data)
	{
		data->button = mMouseType;
		mMouseLBUpTime = mTime;
	}
	
	void Input::KeyUpdate()
	{
		for (UINT i = 0; i < (UINT)EKeyCode::END; i++)
		{
			if (GetAsyncKeyState(ASCII[i]) & 0x8000)
			{
				// 이전 프레임에도 눌려 있었다
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
			else // 현재 프레임에 키가 눌려있지 않다.
			{
				// 이전 프레임에 내키가 눌려있엇다.
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
		Vector2 delta = Vector2::Zero;
		Vector3 Pos = { (float)cursorPos.x,(float)cursorPos.y,0.0f };
		Pos = view.Unproject(Pos, Camera::GetGpuProjectionMatrix(), Camera::GetGpuViewMatrix(), Matrix::Identity);
		if (mMousePos.x == Pos.x && mMousePos.y == Pos.y)
			mMousePosSameCheck++;
		else
			mMousePosSameCheck = 0;

		delta = mMousePos;

		mMousePos.x = Pos.x;
		mMousePos.y = Pos.y;

		PointerEventData* data = new PointerEventData();
		data->button = mMouseType;
		data->btn_state = mMouseState;
		data->delta = delta;
		data->position = mMousePos;
		
		switch (mMouseState)
		{
		case EKeyState::Down:
			MouseBtnDown(data);
			break;
		case EKeyState::Up:
			MouseBtnUp(data);
			break;
		}

		M_Input->OnMouseEvent(data);
		delete data;
	}
}
