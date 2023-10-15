#include "Cursor.h"
#include "GameObject.h"
#include "ImageComponent.h"
#include "..\\Engine\\PlayerScript.h"
#include "Transform.h"
#include "..\\Engine\\ItemScript.h"
#include "MeshRenderer.h"
#include "..\\Engine\\InputManager.h"
#include "CollisionManager.h"
#include "UI.h"
#include "Collider2D.h"
#include "SceneManager.h"
namespace roka
{
	Cursor::Cursor():Component(EComponentType::Cursor),
		mbDrag(false)
	{
	}
	Cursor::Cursor(const Cursor& ref):Component(ref),
		mbDrag(false)
	{
	}
	void Cursor::Copy(Component* src)
	{
		Cursor* source = dynamic_cast<Cursor*>(src);
		if (source == nullptr)
			return;
		Component::Copy(src);
		mbDrag = false;
	}
	Cursor::~Cursor()
	{
	}
	void Cursor::Initialize()
	{
	}
	void Cursor::Update()
	{
	}
	void Cursor::LateUpdate()
	{
	}
	void Cursor::Render()
	{
	}
	void Cursor::OnPointerEnter(PointerEventData* data)
	{
		//원래는 ui 정보에 따라 마우스 커서 이미지가 바뀌어야 함
		//  switch(data->ui정보) cursor sprite 교체.
		//일단 테스트로 그냥 어두워 지게 하기.
		std::shared_ptr<ImageComponent> image = owner->GetComponent<ImageComponent>();
		image->SetSprite(2);
	}
	void Cursor::OnPointerExit(PointerEventData* data)
	{
		std::shared_ptr<ImageComponent> image = owner->GetComponent<ImageComponent>();
		image->SetSprite(1);
	}
	void Cursor::OnClick(PointerEventData* data)
	{
		std::shared_ptr<GameObject> player;
		for (auto obj : data->select_objects)
		{
			if (obj->GetName().compare(L"PlayerTopCol") == 0)
			{
				obj->parent->GetComponent<PlayerScript>()->BeAttacked(10, EStunState::None);
			}
			if (obj->GetName().compare(L"PlayerBottomCol") == 0)
			{
				obj->parent->GetComponent<PlayerScript>()->Recovery(20);
			}
		}
	}
	void Cursor::OnBeginDrag(PointerEventData* data)
	{
		for (auto obj : mDragObjects)
		{
			std::shared_ptr<MeshRenderer> mr = obj->GetComponent<MeshRenderer>();
			mr->alpha = 0.5f;
			mr->EnableChangeAlpha();
			if (obj->parent == nullptr)
				continue;
			Vector3 pScale = obj->parent->GetComponent<Transform>()->scale;
			obj->parent->RemoveChild(obj);
			obj->parent = nullptr;
			std::shared_ptr<Transform> tf = obj->GetComponent<Transform>();
		Vector3 pos = -(owner->GetComponent<Transform>()->position);
			pos.z -= 0.5f;
			tf->position = pos;
			owner->AddChild(obj);
		
			
			obj->GetComponent<Transform>()->scale = Vector3(2.0f,2.0f,1.0f);	
		}
	}
	void Cursor::OnDrag(PointerEventData* data)
	{
		std::shared_ptr<Transform> cursorTf = owner->GetComponent<Transform>();
		Vector3 pos = cursorTf->position;
		for(auto obj : mDragObjects)
		{
			std::shared_ptr<Transform> tf = obj->GetComponent<Transform>();
			//tf->SetWorldPosition(pos);
		}
	}
	void Cursor::OnEndDrag(PointerEventData* data)
	{
		std::shared_ptr<UI> enter_obj = std::dynamic_pointer_cast<UI>(data->enter_object);

		bool flag = false;
		if (enter_obj == nullptr && data->enter_object == nullptr)
		{
			//field drop
			for (auto drop : mDragObjects)
			{
				std::shared_ptr<MeshRenderer> mr = drop->GetComponent<MeshRenderer>();
				std::shared_ptr<ItemScript> item = drop->GetComponent<ItemScript>();
				if (item != nullptr)
				{
					item->SetMode(owner->GetSharedPtr(),EItemModeType::Field);
				}
				mr->alpha = 1.0f;
				mr->DisableChangeAlpha();
				SceneManager::AddGameObject(ELayerType::Item, drop);
			}
			flag = true;
		}
		else if(enter_obj!=nullptr)
		{
			//enter obj 가 slot면 옮겨주고 item 이면 둘이 swap
			if (enter_obj->ui_type == EUIType::Slot)
			{
				std::shared_ptr<Transform> slotTf = enter_obj->GetComponent<Transform>();
				Vector3 slot_pos = slotTf->position;

				for (auto drop : mDragObjects)
				{
					std::shared_ptr<MeshRenderer> mr = drop->GetComponent<MeshRenderer>();
					std::shared_ptr<Transform> tf = drop->GetComponent<Transform>();
					Vector3 pScale = enter_obj->GetComponent<Transform>()->scale;
					mr->alpha = 1.0f;
					mr->DisableChangeAlpha();
					Vector3 pos = -slot_pos;
					pos.z -= 0.5f;
					tf->position = pos;
					tf->scale = pScale;
					enter_obj->AddChild(drop);

					

					owner->RemoveChild(drop);
				}
				flag = true;
			}
		}

		if (flag == true)
		{
			std::shared_ptr<Collider2D> left = owner->GetComponent<Collider2D>();
			for (auto drop : mDragObjects)
			{
				std::shared_ptr<Collider2D> right = drop->GetComponent<Collider2D>();
				CollisionManager::DisableCollision(left, right);
				CollisionManager::DisableCollision(right, left);
			}
		}
	}
	std::shared_ptr<GameObject> Cursor::GetDragObject(int index)
	{
		return mDragObjects[index];
	}
	void Cursor::DragObjectClear()
	{
		mDragObjects.clear();
	}
}