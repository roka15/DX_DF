#pragma once
#include "SingleTon.h"


namespace roka
{
	struct ItemInfo;
	struct ExpendablesInfo;
	struct UserItemInfo;
	struct OwnItemInfo;
	struct AvatarPartInfo;
<<<<<<< HEAD
	struct AvatarSubInfo;
=======
	struct AvatarSubPartInfo;
>>>>>>> 196c08dd0ba6b6a4ccf9ed9808fde15bf7229f53
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
		void SetInventoryItem(std::shared_ptr<GameObject> inven,std::shared_ptr<GameObject> player);
		const ItemInfo& GetItemInfo(std::shared_ptr<GameObject> caster,int id);
		const ItemInfo& GetItemInfo(int id);
		const AvatarPartInfo& GetAvatarPartInfo(int id);
		bool UseItem(std::shared_ptr<GameObject> caster, int id);
	private:
		bool UseOwnItem(int user_id, int item_id);
		bool UseExpendablesItem(std::shared_ptr<GameObject> caster, int id);
		bool UseAvatarPartItem(std::shared_ptr<GameObject> caster,int id, int part_type);
		
		void ItemTextureLoad();
	private:
		std::map<unsigned int, UserItemInfo> mUserItemTable;
		std::map<unsigned int, std::vector<OwnItemInfo>> mOwnItemTable;

		std::map<unsigned int, ItemInfo> mItemTable;
		std::map<unsigned int, ExpendablesInfo> mExpendablesTable;
		std::map<unsigned int, AvatarPartInfo> mAvatarPartTable;
<<<<<<< HEAD
		std::map<unsigned int, std::vector<AvatarSubInfo>> mAvatarSubTable;
=======
		std::map<unsigned int, std::vector<AvatarSubPartInfo>> mAvatarSubPartTable;
>>>>>>> 196c08dd0ba6b6a4ccf9ed9808fde15bf7229f53
	};

}

