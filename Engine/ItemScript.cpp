#include "ItemScript.h"

#include "ItemManager.h"
#include "GameObject.h"
#include "Resources.h"
#include "ImageComponent.h"
#include "Item.h"
#include "Texture.h"
#include "Collider2D.h"
#include "Cursor.h"
#include "Input.h"
#include "CollisionManager.h"
#include "SceneManager.h"
using namespace roka::graphics;
namespace roka
{
	ItemScript::ItemScript() :Script(EScriptType::Item),
		mItemID(-1),
		mUseOwner(nullptr),
		mModeType(EItemModeType::None)
	{
	}
	ItemScript::ItemScript(const ItemScript& ref) :Script(ref)
	{
	}
	void ItemScript::Copy(Component* src)
	{
		ItemScript* source = dynamic_cast<ItemScript*>(src);
		if (source == nullptr)
			return;
	}
	void ItemScript::Initialize()
	{
		owner->AddComponent<Collider2D>();
	}
	void ItemScript::Update()
	{
	}
	void ItemScript::LateUpdate()
	{
	}
	void ItemScript::Render()
	{
	}
	void ItemScript::SetMode(std::shared_ptr<GameObject> caster, EItemModeType type)
	{
		if (mItemID == -1)
			return;
		mModeType = type;
		const ItemInfo& info = manager::ItemManager::GetInstance()->GetItemInfo(mUseOwner, mItemID);
		std::shared_ptr<ImageComponent> image = owner->GetComponent<ImageComponent>();
		std::shared_ptr<Collider2D> col = owner->GetComponent<Collider2D>();
		std::shared_ptr<Collider2D> casterCol = caster->GetComponent<Collider2D>();
		std::wstring Name;
		int index;
		switch (mModeType)
		{
		case EItemModeType::Field:
			Name = info.field;
			index = info.field_index;
			owner->layer_type = ELayerType::Item;
			break;
		case EItemModeType::Icon:
			Name = info.icon;
			index = info.icon_index;
			owner->layer_type = ELayerType::UI;
			break;
		}
		CollisionManager::DisableCollision(col, casterCol);
		std::shared_ptr<Texture> texture = Resources::Find<Texture>(Name);
		image->SetSprite(index);
		image->SetTexture(texture);
	}
	void ItemScript::SetItem(unsigned int id)
	{
		mItemID = id;
	}
	void ItemScript::OnClick(PointerEventData* data)
	{
		if (data->button == EMouseBtnType::RIGHT)
		{
			if (mUseOwner != nullptr && mItemID != -1)
			{
				manager::ItemManager::GetInstance()->UseItem(mUseOwner, mItemID);
			}
		}
	}
	void ItemScript::OnDrag(PointerEventData* data)
	{
		int a = 0;
	}
	void ItemScript::OnDrop(PointerEventData* data)
	{
		int a = 0;
	}
}