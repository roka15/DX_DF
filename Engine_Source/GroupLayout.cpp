#include "GroupLayout.h"
#include "Transform.h"
namespace roka
{
    GroupLayout::GroupLayout() :Component(EComponentType::GroupLayout),
        mOffset(Vector2::Zero),
        mDistance(Vector2::Zero),
        mHorizontalCnt(0),
        mVerticalCnt(0),
        mIndexPos(Vector2::Zero),
        mbUpdateRequest(false)
    {
    }
    GroupLayout::GroupLayout(EComponentType type):Component(type)
    {
    }
    GroupLayout::~GroupLayout()
    {
    }
    void GroupLayout::Copy(Component* src)
    {
    }
    void GroupLayout::Initialize()
    {
        Component::Initialize();
        
    }
    void GroupLayout::Update()
    {
        Component::Update();
    }
    void GroupLayout::LateUpdate()
    {
        Component::LateUpdate();
    }
    void GroupLayout::Render()
    {
        Component::Render();
    }
    void GroupLayout::SetInfo(Vector2 offset, Vector2 distance, int vcnt, int hcnt)
    {
        mOffset = offset;
        mDistance = distance;
        mDistance.y *= -1;
        mVerticalCnt = vcnt;
        mHorizontalCnt = hcnt;
        mbUpdateRequest = true;
        mCellSize = Vector2(1.0f, 1.0f);
    }
    void GroupLayout::SetCellSize(Vector2 cellsize)
    {
        mCellSize = Vector2(cellsize.x, cellsize.y);
    }
}