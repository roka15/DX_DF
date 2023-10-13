#pragma once
#include "Script.h"
#include "IMouseEvent.h"
namespace roka
{
	class ItemScript :
		public Script,public IPointerClickHandler,public IDragHandler, public IDropHandler
	{
	protected:
		ItemScript();
		ItemScript(const ItemScript& ref);
		virtual void Copy(Component* src)override;
	public:
		virtual ~ItemScript() {}

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void SetMode(std::shared_ptr<GameObject> caster,EItemModeType type);
		void SetUseOwner(std::shared_ptr<GameObject> owner) { mUseOwner=owner; }
		void SetItem(unsigned int id);


		virtual void OnClick(PointerEventData* data)override;
		virtual void OnDrag(PointerEventData* data) override;
		virtual void OnDrop(PointerEventData* data) override;
	private:
		friend class FactoryBase;
		friend class ScriptFactory;
	private:
		std::shared_ptr<GameObject> mUseOwner;
		int mItemID;
		EItemModeType mModeType;
	};
}


