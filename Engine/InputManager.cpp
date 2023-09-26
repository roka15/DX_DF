#include "InputManager.h"

#include "GameObject.h"
#include "IMouseEvent.h"

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
		int same_cnt = Input::GetMouseSameCnt();
		std::shared_ptr<GameObject> cursor = mCursor.lock();
		if (same_cnt >= 500)
		{
			DisableCursor();
			return;
		}
		EnableCursor();
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
			mKeyEvents.insert(std::make_pair(key, std::map<EKeyState, std::vector<std::function<void()>>>()));
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
	void InputManager::OnMouseEvent(PointerEventData* data)
	{
		//충돌 object들 모두 뽑아오기
		std::vector<std::shared_ptr<GameObject>> objs = {};
		switch (data->btn_state)
		{
		case EKeyState::Down:
		case EKeyState::Pressed:
			MouseDown(data, objs);
			break;
		case EKeyState::Up:
			MouseUp(data, objs);
			break;
		}
		MouseEnter(data, objs);
		MouseExit(data, objs);
	}
	void InputManager::MouseDown(PointerEventData* data, std::vector<std::shared_ptr<GameObject>>& objs)
	{
		if (data->btn_state == EKeyState::Pressed)//누르는중
		{
			for (auto& obj : objs)
			{
				std::vector<std::shared_ptr<Script>> scripts = obj->GetScripts();
				for (auto& script : scripts)
				{
					IDragHandler* handler = dynamic_cast<IDragHandler*>(script.get());
					if (handler == nullptr)
						return;
					handler->OnDrag(data);
				}
			}
		}
		else//일반 down
		{
			for (auto& obj : objs)
			{
				std::vector<std::shared_ptr<Script>> scripts = obj->GetScripts();
				for (auto& script : scripts)
				{
					IPointerDownHandler* down_handler = dynamic_cast<IPointerDownHandler*>(script.get());
					IPointerClickHandler* click_handler = dynamic_cast<IPointerClickHandler*>(script.get());
					if (down_handler != nullptr)
						down_handler->OnPointerDown(data);
					if (click_handler != nullptr)
						click_handler->OnClick(data);
				}
			}
		}
	}
	void InputManager::MouseUp(PointerEventData* data, std::vector<std::shared_ptr<GameObject>>& objs)
	{
		for (auto& obj : objs)
		{
			std::vector<std::shared_ptr<Script>> scripts = obj->GetScripts();
			for (auto& script : scripts)
			{
				IPointerUpHandler* handler = dynamic_cast<IPointerUpHandler*>(script.get());
				if (handler != nullptr)
					handler->OnPointerUp(data);
			}
		}
	}

	void InputManager::MouseEnter(PointerEventData* data, std::vector<std::shared_ptr<GameObject>>& objs)
	{
		for (auto& obj : objs)
		{
			std::vector<std::shared_ptr<Script>> scripts = obj->GetScripts();
			for (auto& script : scripts)
			{
				IPointerEnterHandler* handler = dynamic_cast<IPointerEnterHandler*>(script.get());
				if (handler != nullptr)
					handler->OnPointerEnter(data);
			}
		}
	}

	void InputManager::MouseExit(PointerEventData* data, std::vector<std::shared_ptr<GameObject>>& objs)
	{
		for (auto& obj : objs)
		{
			//cursor와 obj의 현 충돌 상태를 확인 후 exit 수행.

			std::vector<std::shared_ptr<Script>> scripts = obj->GetScripts();
			for (auto& script : scripts)
			{
				IPointerExitHandler* handler = dynamic_cast<IPointerExitHandler*>(script.get());
				if (handler != nullptr)
					handler->OnPointerExit(data);
			}
		}
	}

	void InputManager::EnableCursor()
	{
		std::shared_ptr<GameObject> cursor = mCursor.lock();
		cursor->active = GameObject::EState::Active;
	}
	void InputManager::DisableCursor()
	{
		std::shared_ptr<GameObject> cursor = mCursor.lock();
		cursor->active = GameObject::EState::Paused;
	}
}