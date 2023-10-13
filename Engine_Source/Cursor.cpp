#include "Cursor.h"
#include "GameObject.h"
#include "ImageComponent.h"
#include "..\\Engine\\PlayerScript.h"
#include "Transform.h"
#include "..\\Engine\\ItemScript.h"
#include "MeshRenderer.h"
#include "..\\Engine\\InputManager.h"
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
			obj->parent->RemoveChild(obj);
			obj->parent = nullptr;
		}
	}
	void Cursor::OnDrag(PointerEventData* data)
	{
		std::shared_ptr<Transform> cursorTf = owner->GetComponent<Transform>();
		Vector3 pos = cursorTf->position;
		for(auto obj : mDragObjects)
		{
			std::shared_ptr<Transform> tf = obj->GetComponent<Transform>();
			tf->SetWorldPosition(pos);
		}
	}
	void Cursor::OnEndDrag(PointerEventData* data)
	{
		std::shared_ptr<GameObject> enter_obj = data->enter_object;
	    
		if (enter_obj == nullptr)
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
			}
		}
		else
		{
			//enter obj 가 slot면 옮겨주고 item 이면 둘이 swap
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