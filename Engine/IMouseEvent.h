#pragma once
#include "RokaEngine.h"
#include "MemoryPool.h"
namespace roka
{
	using namespace math;
	
	class PointerEventData:public stl::MemoryPool
	{
	public:
		Vector2 position;//event 발생 시점의 pos
		Vector2 delta;//이전 프레임 이후 pos
		EMouseBtnType button;//발생한 event의 버튼
		EKeyState btn_state; // 버튼의 상태
		int click_cnt; // 연속 클릭 
		float scroll_delta;//스크롤 이동량
		bool ui_check;//현재 오브젝트가 ui 인지 정보
		std::shared_ptr<class GameObject> select_object;//현재 선택된 object 정보
		unsigned int key;//입력된 키보드 키 (컨트롤+클릭 같은거 쓸때 필요)
	};
	class IPointerEnterHandler
	{
	public:
		virtual void OnPointerEnter(PointerEventData* data) = 0;
	};
	class IPointerExitHandler
	{
	public:
		virtual void OnPointerExit(PointerEventData* data) = 0;
	};
	class IPointerDownHandler
	{
	public:
		virtual void OnPointerDown(PointerEventData* data) = 0;
	};
	class IPointerUpHandler
	{
	public:
		virtual void OnPointerUp(PointerEventData* data) = 0;
	};
	class IPointerClickHandler
	{
	public:
		virtual void OnClick(PointerEventData* data) = 0;
	};
	class IBeginDragHandler
	{
	public:
		virtual void OnBeginDrag(PointerEventData* data) = 0;
	};
	class IDragHandler
	{
	public:
		virtual void OnDrag(PointerEventData* data) = 0;
	};
	class IDropHandler
	{
	public:
		virtual void OnDrop(PointerEventData* data) = 0;
	};
	class IEndDragHandler
	{
	public:
		virtual void OnEndDrag(PointerEventData* data) = 0;
	};
}


