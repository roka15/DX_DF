#include "ItemManager.h"
#include "Item.h"

#include "GameObject.h"
#include "PlayerScript.h"
#include "User.h"
#include "Resources.h"
#include "NPK.h"
#include "..\\Engine_Source\\Texture.h"
using namespace roka::graphics;
namespace roka::manager
{
	ItemManager::ItemManager()
	{
		UserItemInfo user = { 1000,5 };
		mUserItemTable.insert(std::make_pair(1, user));

		ItemInfo item = { 1000,(UINT)EItemType::Expendables,(UINT)EItemRankType::Normal,
		L"호랑이 기운이 쑥쑥",5.0,L"ItemFieldAtlasTexture",1,L"ItemIconAtlasTexture",1,L"호랑이 기운이 솟아나 체력이 30 회복 됩니다." };
		mItemTable.insert(std::make_pair(1000, item));

		ExpendablesInfo expendables = { 3000,1000,(UINT)EExpendablesType::HPRecovery,30 };
		mExpendablesTable.insert(std::make_pair(3000, expendables));
	}

	ItemManager::~ItemManager()
	{
	}

	void ItemManager::Initialize()
	{
		ItemTextureLoad();
	}

	const UserItemInfo& ItemManager::GetUserItemInfo(int id)
	{
		static roka::UserItemInfo info = { -1 };
		auto itr = mUserItemTable.find(id);
		if (itr == mUserItemTable.end())
			return info;
		// 밖에서 받아온 info id 가 -1인지 체크하거나 아니면 여기서 runtime error 같은 처리 해주거나
		// c++ 17 optional 명령어 써서 처리.

		return itr->second;
	}

	std::vector<UserItemInfo> ItemManager::GetUserItemInfos(int id)
	{
		std::vector<UserItemInfo> vec = {};

		for (auto& tuple : mUserItemTable)
		{
			vec.push_back(tuple.second);
		}

		return vec;
	}

	const ItemInfo& ItemManager::GetItemInfo(std::shared_ptr<GameObject> caster, int item_id)
	{
		static roka::ItemInfo info = { -1 };
		std::shared_ptr<PlayerScript> player = caster->GetComponent<PlayerScript>();
		if (player == nullptr)
			return info;
		const int user_id = player->GetUserInfo()->id;
		std::vector<UserItemInfo> vec = GetUserItemInfos(user_id);

		for (auto userItem : vec)
		{
			if (userItem.foreignkey == item_id && userItem.count != 0)
			{
				auto itr = mItemTable.find(item_id);
				if (itr == mItemTable.end())
					return info;

				return itr->second;
			}
		}

	}

	const ItemInfo& ItemManager::GetItemInfo(int id)
	{
		static roka::ItemInfo info = { -1 };
		auto itr = mItemTable.find(id);
		if (itr == mItemTable.end())
			return info;

		return itr->second;
	}

	bool ItemManager::UseItem(std::shared_ptr<GameObject> caster, int id)
	{
		std::shared_ptr<PlayerScript> player = caster->GetComponent<PlayerScript>();
		if (player == nullptr)
			return false;
		const int user_id = player->GetUserInfo()->id;
		std::vector<UserItemInfo> vec = GetUserItemInfos(user_id);
		for (auto userItem : vec)
		{
			if (userItem.foreignkey == id && userItem.count != 0)
			{
				auto itr = mItemTable.find(id);
				if (itr == mItemTable.end())
					return false;

				const ItemInfo& item = itr->second;
				switch (item.item_type)
				{
				case (UINT)EItemType::Expendables:
					UseExpendablesItem(caster, id);
					break;
				}

			}
		}
	}

	bool ItemManager::UseExpendablesItem(std::shared_ptr<GameObject> caster, int id)
	{
		std::shared_ptr<PlayerScript> player = caster->GetComponent<PlayerScript>();
		if (player == nullptr)
			return false;

		bool flag = false;
		for (auto tuple : mExpendablesTable)
		{
			const ExpendablesInfo& info = tuple.second;
			if (info.foreignkey == id)
			{
				switch (info.expendables_type)
				{
				case (UINT)EExpendablesType::HPRecovery:
					player->Recovery(info.value);
					break;
				}
				flag = true;
			}
		}

		if (flag == true)
			return true;

		return false;
	}

	void ItemManager::ItemTextureLoad()
	{
		std::shared_ptr<NPK> npk = Resources::Find<NPK>(L"item");

		std::shared_ptr<Texture> texture = npk->CreateAtlas(L"field_material.img", 0, 3, L"ItemField");
		texture = npk->CreateAtlas(L"icon_material.img", 0, 2, L"ItemIcon");
	}

}
