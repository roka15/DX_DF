#pragma once
#include "RokaEngine.h"
#include "MemoryPool.h"
namespace roka
{
	using namespace math;
	enum class EMouseBtnType : int;
	enum class EKeyState : int;

	class PointerEventData:public stl::MemoryPool
	{
	public:
		Vector2 position;//event �߻� ������ pos
		Vector2 delta;//���� ������ ���� pos
		float wheel_delta;//�� �̵���
		EMouseBtnType button;//�߻��� event�� ��ư
		EKeyState btn_state; // ��ư�� ����
		int click_cnt; // ���� Ŭ�� 
		float scroll_delta;//��ũ�� �̵���
		bool ui_check;//���� ������Ʈ�� ui ���� ����
		std::shared_ptr<class GameObject> enter_object;//���� ���õ� object ����
		std::vector<std::shared_ptr<class GameObject>> select_objects;//���� ����
		std::shared_ptr<class GameObject> drag_object;
		unsigned int key;//�Էµ� Ű���� Ű (��Ʈ��+Ŭ�� ������ ���� �ʿ�)
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
	//�巡�� ����.
	class IBeginDragHandler
	{
	public:
		virtual void OnBeginDrag(PointerEventData* data) = 0;
	};
	//�巡�� ��
	class IDragHandler
	{
	public:
		virtual void OnDrag(PointerEventData* data) = 0;
	};
	//��ӵǴ� ��󿡼� ȣ�� (ex slot)
	class IDropHandler
	{
	public:
		virtual void OnDrop(PointerEventData* data) = 0;
	};
	//�巡�� ����
	class IEndDragHandler
	{
	public:
		virtual void OnEndDrag(PointerEventData* data) = 0;
	};
	class IWheelHandler
	{
	public:
		virtual void OnMouseWheel(PointerEventData* data) = 0;
	};
}


