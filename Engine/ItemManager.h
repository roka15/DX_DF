#pragma once
#include "SingleTon.h"


namespace roka
{
	struct ItemInfo;
	struct ExpendablesInfo;
	struct UserItemInfo;
	class GameObject;
}
namespace roka::manager
{
	class ItemManager :
		public Singleton<ItemManager>
	{
	public:
		ItemManager();
		~ItemManager();

		void Initialize();
		const UserItemInfo& GetUserItemInfo(int id);
		std::vector<UserItemInfo> GetUserItemInfos(int id);
		const ItemInfo& GetItemInfo(std::shared_ptr<GameObject> caster, int item_id);
		const ItemInfo& GetItemInfo(int id);
		bool UseItem(std::shared_ptr<GameObject> caster, int id);
	private:
		bool UseExpendablesItem(std::shared_ptr<GameObject> caster, int id);

		void ItemTextureLoad();
	private:
		std::map<unsigned int, UserItemInfo> mUserItemTable;
		std::map<unsigned int, ItemInfo> mItemTable;
		std::map<unsigned int, ExpendablesInfo> mExpendablesTable;
	};

}

