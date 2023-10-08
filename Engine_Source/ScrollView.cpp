#include "ScrollView.h"
#include "Object.h"

#include "ScrollRect.h"
#include "Collider2D.h"
namespace roka
{
	ScrollView::ScrollView() :UI()
	{
		AddComponent<Collider2D>();
	}
	ScrollView::~ScrollView()
	{
	}
	void ScrollView::Copy(GameObject* src)
	{
		ScrollView* source = dynamic_cast<ScrollView*>(src);
		if (source == nullptr)
			return;
	}
	void ScrollView::Initialize()
	{
		UI::Initialize();
		std::shared_ptr<GameObject> viewport;
		std::shared_ptr<GameObject> content;
		std::shared_ptr<GameObject> vertical_scroll;
		std::shared_ptr<GameObject> horizontal_scroll;
		std::shared_ptr<ScrollRect> scroll;
	
		SetName(L"ScrollView");
		if (GetChildCont() == 0)
		{
			viewport = object::Instantiate<UI>();
			viewport->SetName(L"ViewPort");
			viewport->GetComponent<Transform>()->scale = Vector3(1.0f, 1.0f, 1.0f);
			content = object::Instantiate<UI>();
			content->SetName(L"Content");
			content->GetComponent<Transform>()->scale = Vector3(1.0f, 1.0f, 1.0f);
			vertical_scroll = object::Instantiate<UI>();
			vertical_scroll->SetName(L"VerticalScroll");
			horizontal_scroll = object::Instantiate<UI>();
			horizontal_scroll->SetName(L"HorizontalScroll");

			AddChild(viewport);
			viewport->AddChild(content);
			AddChild(vertical_scroll);
			AddChild(horizontal_scroll);

			scroll = AddComponent<ScrollRect>();
		}
	
		scroll = GetComponent<ScrollRect>();

		scroll->SetHorizontal(true);
		scroll->SetVertical(true);
		scroll->SetContent(content);
		scroll->SetViewPort(viewport);
	}
	void ScrollView::Update()
	{
		UI::Update();
	}
	void ScrollView::LateUpdate()
	{
		UI::LateUpdate();
	}
	void ScrollView::Render()
	{
		UI::Render();
	}
	void ScrollView::Release()
	{
		UI::Release();
	}
}