#pragma once
#include "Component.h"
namespace roka
{
	class GroupLayout :
		public Component
	{
	public:
		GroupLayout();
		GroupLayout(EComponentType type);

		virtual ~GroupLayout();

		virtual void Copy(Component* src);

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		void SetInfo(Vector2 offset, Vector2 distance, int vcnt, int hcnt);
		void SetCellSize(Vector2 cellsize);
	protected:
		Vector2 mCellSize;
		Vector2 mOffset;//���� �������� offset.
		Vector2 mDistance;//content ���� ����.

		int mHorizontalCnt;
		int mVerticalCnt;
		Vector2 mIndexPos;
		bool mbUpdateRequest;
	};
}


