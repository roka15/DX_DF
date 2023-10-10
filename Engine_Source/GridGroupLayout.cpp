#include "GridGroupLayout.h"

#include "GameObject.h"
#include "Transform.h"
#include "Collider2D.h"
#include "UI.h"
#include "Camera.h"
#include "Application.h"
extern roka::Application* focusApp;
roka::GridGroupLayout::GridGroupLayout() :GroupLayout(EComponentType::GridLayout)
{
}

roka::GridGroupLayout::GridGroupLayout(const GridGroupLayout& ref) : GroupLayout(ref)
{
}

void roka::GridGroupLayout::Copy(Component* src)
{
	GridGroupLayout* source = dynamic_cast<GridGroupLayout*>(src);

	if (source == nullptr)
		return;
}

roka::GridGroupLayout::~GridGroupLayout()
{
}

void roka::GridGroupLayout::Initialize()
{
}

void roka::GridGroupLayout::Update()
{
	std::vector<std::shared_ptr<GameObject>> objs = owner->GetChilds();
	if (mbUpdateRequest == true)
	{
		std::shared_ptr<Transform> tf = owner->GetComponent<Transform>();
		Vector3 scale = tf->GetScale();
		Vector2 cellSize = mCellSize * scale;
		cellSize.y *= -1;
		tf->SetPivot(Vector3(1.0f, 1.0f, 0.0f));
		Vector3 leftTop = Vector3::Zero;
		Vector2 radius = tf->GetRadius();
		leftTop.x = mOffset.x; //+ (cellSize.x / 2.0f);
		leftTop.y = mOffset.y; //+(cellSize.y / 2.0f);
		//leftTop.y *= -1;

		//Vector2 radius =Vector2(RectMeshDXRadius*scale.x, RectMeshDXRadius*scale.y);
		//radius.y *= -1;

		const Vector2 OriginLT(leftTop.x, leftTop.y);
		int i = 0;
		int j = 0;


		for (auto obj : objs)
		{
			std::shared_ptr<Transform> tf = obj->GetComponent<Transform>();
			std::shared_ptr<Collider2D> collider = obj->GetComponent<Collider2D>();

			if (i == 0 && j == 0)
			{
				tf->position = leftTop;
				j++;
				/*if (j == mHorizontalCnt)
				{
					i++;
					j = 0;
					continue;
				}*/
			}
			else
			{
				if (j == mHorizontalCnt)
				{
					i++;
					j = 1;
					leftTop.y += (mDistance.y + cellSize.y);
					tf->position = leftTop;
					leftTop.x = OriginLT.x;
				}
				else
				{
					leftTop.x += (mDistance.x + cellSize.x);
					j++;
				}
				tf->position = leftTop;
			}
		}
		mIndexPos.x = j + 1;
		mIndexPos.y = i + 1;
		mbUpdateRequest = false;
	}
	else
	{
		int cnt = mIndexPos.x * mIndexPos.y;
		int size = objs.size();
		if (cnt < size)
		{
			int diff = size - cnt;
			int y = size / mVerticalCnt;
			int x = size % mHorizontalCnt;
			int i = 0;
			for (i = cnt; i < size; i++);
			{
				if (mIndexPos.x == mHorizontalCnt)
				{
					if (mIndexPos.y == mVerticalCnt)
						return;
					//아래로 내리기
					mIndexPos.y++;
					mIndexPos.x = 0;
				}

				std::shared_ptr<Transform> tf = objs[i]->GetComponent<Transform>();
				Vector2 offset = Vector2(mDistance.x * mIndexPos.x + mOffset.x, mDistance.y * mIndexPos.y + mOffset.y);
				Vector3 pos = tf->position;
				tf->SetPosition(Vector2(pos.x - offset.x, pos.y - offset.y));
			}
		}
	}
}

void roka::GridGroupLayout::LateUpdate()
{
}

void roka::GridGroupLayout::Render()
{
}
