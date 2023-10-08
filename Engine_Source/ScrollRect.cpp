#include "ScrollRect.h"
#include "GameObject.h"
#include "Transform.h"
#include "Collider2D.h"
#include "Application.h"
#include "UI.h"
#include "Camera.h"
extern roka::Application* focusApp;
namespace roka
{
	ScrollRect::ScrollRect() :Component(EComponentType::ScrollRect)
	{
	}
	ScrollRect::ScrollRect(const Component& ref) : Component(ref)
	{
	}
	ScrollRect::~ScrollRect()
	{
	}
	void ScrollRect::Copy(Component* src)
	{
		ScrollRect* source = dynamic_cast<ScrollRect*>(src);
		if (source == nullptr)
			return;
	}
	void ScrollRect::Initialize()
	{
	}
	void ScrollRect::Update()
	{
		std::shared_ptr<Collider2D> collider = owner->GetComponent<Collider2D>();

		std::shared_ptr<GameObject> viewport = mViewPort;
		Vector3 scale = viewport->GetComponent<Transform>()->scale;
		collider->SetSize(Vector2(scale.x, scale.y));
	}
	void ScrollRect::LateUpdate()
	{
	}
	void ScrollRect::Render()
	{
	}

	void ScrollRect::Bind()
	{
		focusApp->BindViewPort(mViewRect);
	}

	void ScrollRect::SetViewPort(std::shared_ptr<GameObject> obj)
	{
		mViewPort = obj;
		std::shared_ptr<Transform> tf = mViewPort->AddComponent<Transform>();
		Vector3 pos = tf->position;
		Vector3 scale = tf->scale;

		Viewport view;
		view.width = focusApp->GetWidth();
		view.height = focusApp->GetHeight();
		view.x = 0;
		view.y = 0;
		view.minDepth = 0.0f;
		view.maxDepth = 1.0f;

		pos = view.Project(pos, Camera::GetGpuProjectionMatrix(), Camera::GetGpuViewMatrix(), Matrix::Identity);


		Vector2 diff = Vector2(scale.x * RectMeshWindowRadius, scale.y * RectMeshWindowRadius);

		RECT rect = {};
		rect.left = pos.x - diff.x;
		rect.right = pos.x + diff.x;
		rect.top = pos.y - diff.y;
		rect.bottom = pos.y + diff.y;

		mViewRect = rect;
	}

	void ScrollRect::AddContent(std::shared_ptr<GameObject> obj)
	{
		mContent->AddChild(obj);
		std::shared_ptr<UI> ui = std::dynamic_pointer_cast<UI>(obj);
		ui->SetViewPortRect(mViewRect);
	}

	void ScrollRect::OnMouseWheel(PointerEventData* data)
	{
		std::vector<std::shared_ptr<GameObject>> contents =
			mContent->GetChilds();
		float offset = data->wheel_delta * 0.001f;
		for (auto obj : contents)
		{
			std::shared_ptr<Transform> tf = obj->GetComponent<Transform>();
			Vector3 pos = tf->position;
			pos.y += offset;
			tf->position = pos;
		}
	}
}