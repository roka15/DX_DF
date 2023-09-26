#pragma once
#include "RokaEngine.h"
#include "MemoryPool.h"
namespace roka
{
	using namespace math;
	
	enum class EMouseBtnType
	{
		None,
		Left,
		Right,
		End,
	};
	class PointerEventData:public stl::MemoryPool
	{
	public:
		Vector3 position;//event �߻� ������ pos
		Vector3 delta;//���� ������ ���� pos
		EMouseBtnType button;//�߻��� event�� ��ư
		int click_cnt; // ���� Ŭ�� 
		float scroll_delta;//��ũ�� �̵���
		bool ui_check;//���� ������Ʈ�� ui ���� ����
		std::shared_ptr<class GameObject> select_object;//���� ���õ� object ����
		unsigned int key;//�Էµ� Ű���� Ű (��Ʈ��+Ŭ�� ������ ���� �ʿ�)
	};
	class IPointerEnterHandler
	{
		virtual void OnPointerEnter(PointerEventData& data) = 0;
	};
	class IPointerExitHandler
	{
		virtual void OnPointerExit(PointerEventData& data) = 0;
	};
	class IPointerDownHandler
	{
		virtual void OnPointerDown(PointerEventData& data) = 0;
	};
	class IPointerUpHandler
	{
		virtual void OnPointerUp(PointerEventData& data) = 0;
	};
	class IBeginDragHandler
	{
		virtual void OnBeginDrag(PointerEventData& data) = 0;
	};
	class IDragHandler
	{
		virtual void OnDrag(PointerEventData& data) = 0;
	};
	class IDropHandler
	{
		virtual void OnDrop(PointerEventData& data) = 0;
	};
	class IEndDragHandler
	{
		virtual void OnEndDrag(PointerEventData& data) = 0;
	};
}


