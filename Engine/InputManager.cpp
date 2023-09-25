#include "InputManager.h"

#include "GameObject.h"

#include "Transform.h"
namespace roka::manager
{
	InputManager::InputManager()
	{
	}
	InputManager::~InputManager()
	{
	}
	void InputManager::Initialize()
	{
	}
	void InputManager::Update()
	{
		Vector2 mouse_pos = Input::GetMousePos();
		Vector2 setting_pos = mouse_pos;
		setting_pos.y -= 0.05f;

		mCursor.lock()->GetComponent<Transform>()->SetPosition(setting_pos);
	}
	void InputManager::LateUpdate()
	{
	}
	void InputManager::Release()
	{
	}
	void InputManager::RegisterKeyEvent(UINT key1, EKeyState key2, std::function<void()> key_event)
	{
		EKeyCode key = (EKeyCode)key1;
		auto itr = mKeyEvents.find(key);
		if (itr == mKeyEvents.end())
		{
			mKeyEvents.insert(std::make_pair(key, std::map<EKeyState,std::vector<std::function<void()>>>()));
		}
		auto itr2 = mKeyEvents[key].find(key2);
		if (itr2 == mKeyEvents[key].end())
		{
			mKeyEvents[key].insert(std::make_pair(key2, std::vector<std::function<void()>>()));
		}
		mKeyEvents[key][key2].push_back(key_event);
	}
	void InputManager::OnEvent(EKeyCode key1, EKeyState key2)
	{
		if (mKeyEvents.find(key1) == mKeyEvents.end())
			return;
		if (mKeyEvents[key1].find(key2) == mKeyEvents[key1].end())
			return;

		std::vector<std::function<void()>>& funcs = mKeyEvents[key1][key2];
		for (auto& func : funcs)
		{
			func();
		}
	}
}