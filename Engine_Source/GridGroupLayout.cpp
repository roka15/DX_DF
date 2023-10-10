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
		Vector3 scale = tf->GetLocalScale();
		Vector2 cellSize = mCellSize*scale;
		cellSize.y *= -1;
		mOffset.x += cellSize.x * 0.5f;
		mOffset.y += cellSize.y * 0.5f;
		Vector3 leftTop = Vector3::Zero;
		SetLeftTop(leftTop);
		leftTop.x += mOffset.x;
		leftTop.y += mOffset.y;// +(cellSize.y * scale.y * 0.5f);

		//Vector2 radius =Vector2(RectMeshDXRadius*scale.x, RectMeshDXRadius*scale.y);
		//radius.y *= -1;

		const Vector2 OriginLT(leftTop.x, leftTop.y);
		int i = 0;
		int j = 0;


		for (auto obj : objs)
		{
			std::shared_ptr<Transform> tf = obj->GetComponent<Transform>();
			std::shared_ptr<Collider2D> collider = obj->GetComponent<Collider2D>();
			Vector3 localPos = tf->GetLocalPosition();
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
		//런타임중 정렬 미구현
		//int cnt = mIndexPos.x * mIndexPos.y;
		//int size = objs.size();
		//if (cnt < size)
		//{
		//	int diff = size - cnt;
		//	int y = size / mVerticalCnt;
		//	int x = size % mHorizontalCnt;
		//	int i = 0;
		//	for (i = cnt; i < size; i++);
		//	{
		//		if (mIndexPos.x == mHorizontalCnt)
		//		{
		//			if (mIndexPos.y == mVerticalCnt)
		//				return;
		//			//아래로 내리기
		//			mIndexPos.y++;
		//			mIndexPos.x = 0;
		//		}

		//		std::shared_ptr<Transform> tf = objs[i]->GetComponent<Transform>();
		//		Vector2 offset = Vector2(mDistance.x * mIndexPos.x + mOffset.x, mDistance.y * mIndexPos.y + mOffset.y);
		//		Vector3 pos = tf->position;
		//		Vector3 localPos = tf->GetLocalPosition();
		//		tf->SetPosition(Vector2(localPos.x+offset.x, localPos.y+offset.y));
		//	}
		//}
	}
}

void roka::GridGroupLayout::LateUpdate()
{
}

void roka::GridGroupLayout::Render()
{
}

void roka::GridGroupLayout::SetLeftTop(Vector3& pos)
{
	std::shared_ptr<Transform> gridTf = owner->GetComponent<Transform>();
	Vector3 lscale = gridTf->GetLocalScale();
	Vector3 wscale = gridTf->scale;
	Vector3 gpos = Vector3::Zero;//gridTf->position;

	Vector2 diff = Vector2::One;
	if (owner->parent != nullptr)
	{
		Matrix scaleMat = Matrix::CreateScale(lscale);
		scaleMat = scaleMat.Invert();

		diff.x = scaleMat._11;
		diff.y = scaleMat._22;
	}

	gpos.x -= wscale.x * 0.5f*diff.x;
	gpos.y += wscale.y * 0.5f*diff.y;
	pos = gpos;
}

void roka::GridGroupLayout::SetRightTop(Vector3& pos)
{
}

void roka::GridGroupLayout::SetLeftBottom(Vector3& pos)
{
}

void roka::GridGroupLayout::SetRightBottom(Vector3& pos)
{
}
