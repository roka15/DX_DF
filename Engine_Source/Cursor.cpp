#include "Cursor.h"
#include "GameObject.h"
#include "ImageComponent.h"
#include "..\\Engine\\PlayerScript.h"
namespace roka
{
	Cursor::Cursor():Component(EComponentType::Cursor)
	{
	}
	Cursor::Cursor(const Cursor& ref):Component(ref)
	{
	}
	void Cursor::Copy(Component* src)
	{
		Cursor* source = dynamic_cast<Cursor*>(src);
		if (source == nullptr)
			return;
		Component::Copy(src);
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
		//������ ui ������ ���� ���콺 Ŀ�� �̹����� �ٲ��� ��
		//  switch(data->ui����) cursor sprite ��ü.
		//�ϴ� �׽�Ʈ�� �׳� ��ο� ���� �ϱ�.
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
	}
	void Cursor::OnDrag(PointerEventData* data)
	{
	}
	void Cursor::OnEndDrag(PointerEventData* data)
	{
	}
	std::shared_ptr<GameObject> Cursor::GetDragObject()
	{
		std::shared_ptr<GameObject> obj = mDragObjects.front().lock();
		mDragObjects.pop();
		return obj;
	}
	void Cursor::DragObjectClear()
	{
		while (mDragObjects.empty() == false)
		{
			std::weak_ptr<GameObject> obj = mDragObjects.front();
			obj.reset();
			mDragObjects.pop();
		}
	}
}