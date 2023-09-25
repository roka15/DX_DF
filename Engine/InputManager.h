#pragma once
#include "SingleTon.h"
#include "Input.h"
namespace roka
{
	class GameObject;
}
namespace roka::manager
{
	class InputManager: public Singleton<InputManager>
	{
	protected:
		InputManager();
	public:
		~InputManager();
		void Initialize();
		void Update();
		void LateUpdate();
		void Release();

		void SetCursor(std::shared_ptr<GameObject> cursor) { mCursor = cursor; }
		void RegisterKeyEvent(UINT key1,EKeyState key2, std::function<void()> key_event);
		void OnEvent(EKeyCode key1, EKeyState key2);
	private:
		friend class Singleton<InputManager>;
	private:
		std::map<EKeyCode,std::map<EKeyState,std::vector<std::function<void()>>>> mKeyEvents;
		std::weak_ptr<GameObject> mCursor;
	};
}


