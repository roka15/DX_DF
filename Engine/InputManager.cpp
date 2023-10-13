#include "InputManager.h"

#include "GameObject.h"
#include "IMouseEvent.h"
#include "CollisionManager.h"
#include "Transform.h"
#include "Cursor.h"
#include "ScrollRect.h"

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
		if (mCursor.expired() == true)
			return;

		//�浹 object�� ��� �̾ƿ���
		std::vector<std::shared_ptr<GameObject>> objs = {};
		std::shared_ptr<GameObject> cursor = mCursor.lock();
		objs = CollisionManager::GetCollisionObjects(cursor);

		MouseEnter(data, objs);
		MouseExit(data, objs);

		switch (data->btn_state)
		{
		case EKeyState::Down:
		case EKeyState::Pressed:
			MouseDown(data, objs);
			break;
		case EKeyState::Up:
			MouseUp(data, objs);
			break;
		case EKeyState::Scroll:
			objs = CollisionManager::GetCollisionObjects(cursor);
			MouseScroll(data, objs);
			break;
		}

	}
	void InputManager::MouseDown(PointerEventData* data, std::vector<std::shared_ptr<GameObject>>& objs)
	{
		std::shared_ptr<Cursor> cursor = mCursor.lock()->GetComponent<Cursor>();
		if (data->btn_state == EKeyState::Pressed)//��������
		{
			if (data->button == EMouseBtnType::RIGHT)
				return;
			for (auto& obj : objs)
			{
				//z���� ���� �տ� �ִ� object ó��
				std::vector<std::shared_ptr<Script>> scripts = obj->GetScripts();
				for (auto& script : scripts)
				{
					IDragHandler* handler = dynamic_cast<IDragHandler*>(script.get());
					if (handler == nullptr)
						continue;

					handler->OnDrag(data);

					if (cursor->GetDragState() == false)
					{
						cursor->SetDragState(true);
						cursor->AddDragObject(obj);
						cursor->OnBeginDrag(data);
					}

					cursor->OnDrag(data);
					return;
				}
			}
		}
		else//�Ϲ� down
		{
			bool flag = false;
			//z���� ���� �տ� �ִ� object ó��
			for (auto& obj : objs)
			{
				std::vector<std::shared_ptr<Script>> scripts = obj->GetScripts();
				for (auto& script : scripts)
				{
					IPointerDownHandler* down_handler = dynamic_cast<IPointerDownHandler*>(script.get());
					IPointerClickHandler* click_handler = dynamic_cast<IPointerClickHandler*>(script.get());

					if (down_handler != nullptr)
					{
						down_handler->OnPointerDown(data);
						data->enter_object = obj;
						flag = true;
					}
					else if (click_handler != nullptr)
					{
						click_handler->OnClick(data);
						data->enter_object = obj;
						flag = true;
					}
					else
						continue;

				}
				if (flag == true)
					break;
			}
			if (objs.size() != 0)
			{
				std::shared_ptr<Cursor> cursor = mCursor.lock()->GetComponent<Cursor>();
				data->select_objects = objs;
				cursor->OnClick(data);
			}
		}
	}
	void InputManager::MouseUp(PointerEventData* data, std::vector<std::shared_ptr<GameObject>>& objs)
	{
		std::shared_ptr<Cursor> cursor = mCursor.lock()->GetComponent<Cursor>();
		bool flag = false;

		//z���� ���� �տ� �ִ� object ó��
		for (auto& obj : objs)
		{
			std::vector<std::shared_ptr<Script>> scripts = obj->GetScripts();
			for (auto& script : scripts)
			{
				IPointerUpHandler* handler = dynamic_cast<IPointerUpHandler*>(script.get());
				IDropHandler* drop_hendler = dynamic_cast<IDropHandler*>(script.get());
				if (handler != nullptr)
				{
					handler->OnPointerUp(data);
					flag = true;
				}
				else if (drop_hendler != nullptr)
				{
					drop_hendler->OnDrop(data);
					flag = true;
				}
				else
					continue;

				if (flag == true)
					break;
			}
		}
		if (cursor->GetDragState() == true)
		{
			cursor->SetDragState(false);
			cursor->OnEndDrag(data);
			cursor->DragObjectClear();
		}
	
	}

	void InputManager::MouseEnter(PointerEventData* data, std::vector<std::shared_ptr<GameObject>>& objs)
	{
		std::shared_ptr<Cursor> cursor = mCursor.lock()->GetComponent<Cursor>();
		bool flag = false;
		data->enter_object = nullptr;
		for (auto& obj : objs)
		{
			if (cursor->GetDragState() == true)
			{
				std::shared_ptr<GameObject> dragObj = cursor->GetDragObject(0);
				if (dragObj == obj)
				{
					continue;
				}
			}

			std::vector<std::shared_ptr<Script>> scripts = obj->GetScripts();
			for (auto& script : scripts)
			{
				IPointerEnterHandler* handler = dynamic_cast<IPointerEnterHandler*>(script.get());
				if (handler != nullptr)
				{
					handler->OnPointerEnter(data);
					data->enter_object = obj;
					flag = true;
					break;
				}
				else
					continue;
			}
			if (flag)
				break;
		}
		if (objs.size() != 0)
		{
			std::shared_ptr<Cursor> cursor = mCursor.lock()->GetComponent<Cursor>();
			cursor->OnPointerEnter(data);
		}
	}

	void InputManager::MouseExit(PointerEventData* data, std::vector<std::shared_ptr<GameObject>>& objs)
	{
		bool flag = false;
		for (auto& obj : objs)
		{
			//cursor�� obj�� �� �浹 ���¸� Ȯ�� �� exit ����.

			std::vector<std::shared_ptr<Script>> scripts = obj->GetScripts();
			for (auto& script : scripts)
			{
				IPointerExitHandler* handler = dynamic_cast<IPointerExitHandler*>(script.get());
				if (handler != nullptr)
				{
					handler->OnPointerExit(data);
					data->enter_object = obj;
					flag = true;
					break;
				}
				else
					continue;
			}
			if (flag)
				break;
		}
		if (objs.size() == 0)
		{
			std::shared_ptr<Cursor> cursor = mCursor.lock()->GetComponent<Cursor>();
			cursor->OnPointerExit(data);
		}
	}

	void InputManager::MouseScroll(PointerEventData* data, std::vector<std::shared_ptr<GameObject>>& objs)
	{
		bool flag = false;
		for (auto& obj : objs)
		{
			std::vector<std::shared_ptr<Script>> scripts = obj->GetScripts();
			for (auto& script : scripts)
			{
				IWheelHandler* handler = dynamic_cast<IWheelHandler*>(script.get());
				if (handler != nullptr)
				{
					handler->OnMouseWheel(data);
					data->enter_object = obj;
					flag = true;
					break;
				}
				else
					continue;
			}
			std::shared_ptr<Component> comp = obj->GetComponent<ScrollRect>();
			if (comp != nullptr)
			{
				IWheelHandler* handler = dynamic_cast<IWheelHandler*>(comp.get());
				if (handler != nullptr)
				{
					handler->OnMouseWheel(data);
					data->enter_object = obj;
					flag = true;
					break;
				}
				else
					continue;
			}

			if (flag)
				break;
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