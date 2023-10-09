#pragma once
#include "Component.h"
#include "FontWrapper.h"
namespace roka
{
	using namespace math;
	class Text :
		public Component
	{
	protected:
		Text();
		Text(const Text& ref);
		virtual void Copy(Component* src);
	public:
		virtual ~Text();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		void Create(std::wstring text, int r, int g, int b, int a, float size);
		void SetText(std::wstring text) { mText = text; }
		void SetColor(int r, int g, int b, int a) { mColor = FONT_RGBA(r, g, b, a); }
		void SetSize(float size) { mSize = size; }
	private:
		friend class FactoryBase;
		friend class ComponentFactory;
	private:
		std::wstring mText;
		UINT mColor;
		float mSize;
	};
}


