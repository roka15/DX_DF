#include "Text.h"
#include "Transform.h"
#include "Camera.h"
#include "Application.h"
extern roka::Application* focusApp;
namespace roka
{
	Text::Text() :Component(EComponentType::Text)
	{
	}
	Text::Text(const Text& ref) : Component(ref)
	{
	}
	void Text::Copy(Component* src)
	{
	}
	Text::~Text()
	{
	}
	void Text::Initialize()
	{
		Component::Initialize();
	}
	void Text::Update()
	{
		Component::Update();
	}
	void Text::LateUpdate()
	{
		Component::LateUpdate();
	}
	void Text::Render()
	{
		Component::Render();
		std::shared_ptr<Transform> tf = owner->GetComponent<Transform>();
		Vector3 pos = tf->position;
		Viewport viewport = {};
		viewport.width = focusApp->GetWidth();
		viewport.height = focusApp->GetHeight();
		viewport.x = 0;
		viewport.y = 0;
		viewport.minDepth = 0.0f;
		viewport.maxDepth = 1.0f;

		pos = viewport.Project(pos, Camera::GetGpuProjectionMatrix(), Camera::GetGpuViewMatrix(), Matrix::Identity);

		FontWrapper::DrawFont(mText.c_str(), pos.x, pos.y, mSize, mColor);
	}
	void Text::Create(std::wstring text, int r, int g, int b, int a, float size)
	{
		SetText(text);
		SetColor(r, g, b, a);
		SetSize(size);
	}
}