#include "ItemManager.h"
#include "Item.h"

#include "GameObject.h"
#include "PlayerScript.h"
#include "User.h"
#include "Resources.h"
#include "NPK.h"
#include "..\\Engine_Source\\Texture.h"
#include "Image.h"
#include "Object.h"
#include "ItemScript.h"
#include "InputManager.h"
#include "ScrollRect.h"
#include "AvatarScript.h"
#include "SkinPartScript.h"
#include "Prefab.h"
using namespace roka::graphics;
namespace roka::manager
{
	ItemManager::ItemManager()
	{
		UserItemInfo user = {};
		user.OwnItemInfoTableKey = 1;
		mUserItemTable.insert(std::make_pair(1, user));

		OwnItemInfo own = {};

		/*
		* 1. user id 로 owner table 찾기
		* 2. owner table에서 item 목록 확인
		* 3. item id로 item table에서 확인
		* 4. item type에 따라 소모품 table, 파츠 table, 아바타 table 로 이동
		* 5. 해당하는 table 에서 item table 에서 얻은 참조키로 검색
		* 6. 원하는 동작 수행.
		*/
#pragma region 소모품
		own.id = 1000;
		own.count = 5;
		mOwnItemTable.insert(std::make_pair(user.OwnItemInfoTableKey, std::vector<OwnItemInfo>()));
		mOwnItemTable[user.OwnItemInfoTableKey].push_back(own);

		ItemInfo item = {};
		item.id = 1000;
		item.reference_key = 3000;
		item.item_type = (UINT)EItemType::Expendables;
		item.rank = (UINT)EItemRankType::Normal;
		wcscpy(item.name, L"호랑이 기운이 쑥쑥");
		item.cooltime = 5.0f;
		wcscpy(item.field, L"ItemFieldAtlasTexture");
		item.field_index = 1;
		wcscpy(item.icon, L"ItemIconAtlasTexture");
		item.icon_index = 1;
		wcscpy(item.desc, L"호랑이 기운이 솟아나 체력이 30 회복 됩니다.");

		mItemTable.insert(std::make_pair(1000, item));

		ExpendablesInfo expendables = {};
		expendables.id = 3000;
		expendables.expendables_type = (UINT)EExpendablesType::HPRecovery;
		expendables.value = 30;

		mExpendablesTable.insert(std::make_pair(expendables.id, expendables));

#pragma endregion 

#pragma region avatar ui
#pragma region register own
		//avatar ui belt
		own.id = 6000;
		own.count = 1;
		mOwnItemTable[user.OwnItemInfoTableKey].push_back(own);

		own.id = 6001;
		own.count = 1;
		mOwnItemTable[user.OwnItemInfoTableKey].push_back(own);

		//avatar ui body
		own.id = 6002;
		own.count = 1;
		mOwnItemTable[user.OwnItemInfoTableKey].push_back(own);

		own.id = 6003;
		own.count = 1;
		mOwnItemTable[user.OwnItemInfoTableKey].push_back(own);

		//avatar ui coat
		own.id = 6004;
		own.count = 1;
		mOwnItemTable[user.OwnItemInfoTableKey].push_back(own);

		own.id = 6005;
		own.count = 1;
		mOwnItemTable[user.OwnItemInfoTableKey].push_back(own);

		//avatar ui cap
		own.id = 6006;
		own.count = 1;
		mOwnItemTable[user.OwnItemInfoTableKey].push_back(own);

		own.id = 6007;
		own.count = 1;
		mOwnItemTable[user.OwnItemInfoTableKey].push_back(own);

		//avatar ui face
		own.id = 6008;
		own.count = 1;
		mOwnItemTable[user.OwnItemInfoTableKey].push_back(own);

		own.id = 6009;
		own.count = 1;
		mOwnItemTable[user.OwnItemInfoTableKey].push_back(own);

		//avatar ui hair
		own.id = 6010;
		own.count = 1;
		mOwnItemTable[user.OwnItemInfoTableKey].push_back(own);

		own.id = 6011;
		own.count = 1;
		mOwnItemTable[user.OwnItemInfoTableKey].push_back(own);

		//avatar ui neck
		own.id = 6012;
		own.count = 1;
		mOwnItemTable[user.OwnItemInfoTableKey].push_back(own);

		own.id = 6013;
		own.count = 1;
		mOwnItemTable[user.OwnItemInfoTableKey].push_back(own);

		//avatar ui pants
		own.id = 6014;
		own.count = 1;
		mOwnItemTable[user.OwnItemInfoTableKey].push_back(own);

		own.id = 6015;
		own.count = 1;
		mOwnItemTable[user.OwnItemInfoTableKey].push_back(own);

		//avatar ui shoes
		own.id = 6016;
		own.count = 1;
		mOwnItemTable[user.OwnItemInfoTableKey].push_back(own);

		own.id = 6017;
		own.count = 1;
		mOwnItemTable[user.OwnItemInfoTableKey].push_back(own);

#pragma endregion

#pragma region register item 
		//belt
		item.id = 6000;
		item.reference_key = 7000;
		item.item_type = (UINT)EItemType::AvatarPart;
		item.rank = (UINT)EItemRankType::Normal;
		wcscpy(item.name, L"이키더비키 벨트");
		item.cooltime = 5.0f;
		wcscpy(item.field, L"");
		item.field_index = 0;
		wcscpy(item.icon, L"mg_abeltAtlasTexture");
		item.icon_index = 0;
		wcscpy(item.desc, L"이키더비키 벨트");

		mItemTable.insert(std::make_pair(6000, item));

		item.id = 6001;
		item.reference_key = 7000;
		item.item_type = (UINT)EItemType::AvatarPart;
		item.rank = (UINT)EItemRankType::Normal;
		wcscpy(item.name, L"차원의 별자리 벨트");
		item.cooltime = 5.0f;
		wcscpy(item.field, L"");
		item.field_index = 1;
		wcscpy(item.icon, L"mg_abeltAtlasTexture");
		item.icon_index = 1;
		wcscpy(item.desc, L"차원의 별자리 벨트");

		mItemTable.insert(std::make_pair(6001, item));

		//body
		item.id = 6002;
		item.reference_key = 7001;
		item.item_type = (UINT)EItemType::AvatarPart;
		item.rank = (UINT)EItemRankType::Normal;
		wcscpy(item.name, L"이키더비키 피부");
		item.cooltime = 5.0f;
		wcscpy(item.field, L"");
		item.field_index = 0;
		wcscpy(item.icon, L"mg_abodyAtlasTexture");
		item.icon_index = 0;
		wcscpy(item.desc, L"이키더비키 피부");

		mItemTable.insert(std::make_pair(6002, item));

		item.id = 6003;
		item.reference_key = 7001;
		item.item_type = (UINT)EItemType::AvatarPart;
		item.rank = (UINT)EItemRankType::Normal;
		wcscpy(item.name, L"차원의 별자리 피부");
		item.cooltime = 5.0f;
		wcscpy(item.field, L"");
		item.field_index = 1;
		wcscpy(item.icon, L"mg_abodyAtlasTexture");
		item.icon_index = 1;
		wcscpy(item.desc, L"차원의 별자리 피부");

		mItemTable.insert(std::make_pair(6003, item));

		//coat
		item.id = 6004;
		item.reference_key = 7002;
		item.item_type = (UINT)EItemType::AvatarPart;
		item.rank = (UINT)EItemRankType::Normal;
		wcscpy(item.name, L"이키더비키 코트");
		item.cooltime = 5.0f;
		wcscpy(item.field, L"");
		item.field_index = 0;
		wcscpy(item.icon, L"mg_acoatAtlasTexture");
		item.icon_index = 0;
		wcscpy(item.desc, L"이키더비키 코트");

		mItemTable.insert(std::make_pair(6004, item));

		item.id = 6005;
		item.reference_key = 7002;
		item.item_type = (UINT)EItemType::AvatarPart;
		item.rank = (UINT)EItemRankType::Normal;
		wcscpy(item.name, L"차원의 별자리 코트");
		item.cooltime = 5.0f;
		wcscpy(item.field, L"");
		item.field_index = 1;
		wcscpy(item.icon, L"mg_acoatAtlasTexture");
		item.icon_index = 1;
		wcscpy(item.desc, L"차원의 별자리 코트");

		mItemTable.insert(std::make_pair(6005, item));


		//cap
		item.id = 6006;
		item.reference_key = 7003;
		item.item_type = (UINT)EItemType::AvatarPart;
		item.rank = (UINT)EItemRankType::Normal;
		wcscpy(item.name, L"이키더비키 모자");
		item.cooltime = 5.0f;
		wcscpy(item.field, L"");
		item.field_index = 0;
		wcscpy(item.icon, L"mg_acapAtlasTexture");
		item.icon_index = 0;
		wcscpy(item.desc, L"이키더비키 모자");

		mItemTable.insert(std::make_pair(6006, item));

		item.id = 6007;
		item.reference_key = 7003;
		item.item_type = (UINT)EItemType::AvatarPart;
		item.rank = (UINT)EItemRankType::Normal;
		wcscpy(item.name, L"차원의 별자리 모자");
		item.cooltime = 5.0f;
		wcscpy(item.field, L"");
		item.field_index = 1;
		wcscpy(item.icon, L"mg_acapAtlasTexture");
		item.icon_index = 1;
		wcscpy(item.desc, L"차원의 별자리 모자");

		mItemTable.insert(std::make_pair(6007, item));

		//face
		item.id = 6008;
		item.reference_key = 7004;
		item.item_type = (UINT)EItemType::AvatarPart;
		item.rank = (UINT)EItemRankType::Normal;
		wcscpy(item.name, L"이키더비키 얼굴");
		item.cooltime = 5.0f;
		wcscpy(item.field, L"");
		item.field_index = 0;
		wcscpy(item.icon, L"mg_afaceAtlasTexture");
		item.icon_index = 0;
		wcscpy(item.desc, L"이키더비키 얼굴");

		mItemTable.insert(std::make_pair(6008, item));

		item.id = 6009;
		item.reference_key = 7004;
		item.item_type = (UINT)EItemType::AvatarPart;
		item.rank = (UINT)EItemRankType::Normal;
		wcscpy(item.name, L"차원의 별자리 얼굴");
		item.cooltime = 5.0f;
		wcscpy(item.field, L"");
		item.field_index = 1;
		wcscpy(item.icon, L"mg_afaceAtlasTexture");
		item.icon_index = 1;
		wcscpy(item.desc, L"차원의 별자리 얼굴");

		mItemTable.insert(std::make_pair(6009, item));

		//hair
		item.id = 6010;
		item.reference_key = 7005;
		item.item_type = (UINT)EItemType::AvatarPart;
		item.rank = (UINT)EItemRankType::Normal;
		wcscpy(item.name, L"이키더비키 머리");
		item.cooltime = 5.0f;
		wcscpy(item.field, L"");
		item.field_index = 0;
		wcscpy(item.icon, L"mg_ahairAtlasTexture");
		item.icon_index = 0;
		wcscpy(item.desc, L"이키더비키 머리");

		mItemTable.insert(std::make_pair(6010, item));

		item.id = 6011;
		item.reference_key = 7005;
		item.item_type = (UINT)EItemType::AvatarPart;
		item.rank = (UINT)EItemRankType::Normal;
		wcscpy(item.name, L"차원의 별자리 머리");
		item.cooltime = 5.0f;
		wcscpy(item.field, L"");
		item.field_index = 1;
		wcscpy(item.icon, L"mg_ahairAtlasTexture");
		item.icon_index = 1;
		wcscpy(item.desc, L"차원의 별자리 머리");

		mItemTable.insert(std::make_pair(6011, item));

		//neck
		item.id = 6012;
		item.reference_key = 7006;
		item.item_type = (UINT)EItemType::AvatarPart;
		item.rank = (UINT)EItemRankType::Normal;
		wcscpy(item.name, L"이키더비키 목");
		item.cooltime = 5.0f;
		wcscpy(item.field, L"");
		item.field_index = 0;
		wcscpy(item.icon, L"mg_aneckAtlasTexture");
		item.icon_index = 0;
		wcscpy(item.desc, L"이키더비키 목");

		mItemTable.insert(std::make_pair(6012, item));

		item.id = 6013;
		item.reference_key = 7006;
		item.item_type = (UINT)EItemType::AvatarPart;
		item.rank = (UINT)EItemRankType::Normal;
		wcscpy(item.name, L"차원의 별자리 목");
		item.cooltime = 5.0f;
		wcscpy(item.field, L"");
		item.field_index = 1;
		wcscpy(item.icon, L"mg_aneckAtlasTexture");
		item.icon_index = 1;
		wcscpy(item.desc, L"차원의 별자리 목");

		mItemTable.insert(std::make_pair(6013, item));

		//pants
		item.id = 6014;
		item.reference_key = 7007;
		item.item_type = (UINT)EItemType::AvatarPart;
		item.rank = (UINT)EItemRankType::Normal;
		wcscpy(item.name, L"이키더비키 바지");
		item.cooltime = 5.0f;
		wcscpy(item.field, L"");
		item.field_index = 0;
		wcscpy(item.icon, L"mg_apantsAtlasTexture");
		item.icon_index = 0;
		wcscpy(item.desc, L"이키더비키 바지");

		mItemTable.insert(std::make_pair(6014, item));

		item.id = 6015;
		item.reference_key = 7007;
		item.item_type = (UINT)EItemType::AvatarPart;
		item.rank = (UINT)EItemRankType::Normal;
		wcscpy(item.name, L"차원의 별자리 바지");
		item.cooltime = 5.0f;
		wcscpy(item.field, L"");
		item.field_index = 1;
		wcscpy(item.icon, L"mg_apantsAtlasTexture");
		item.icon_index = 1;
		wcscpy(item.desc, L"차원의 별자리 바지");

		mItemTable.insert(std::make_pair(6015, item));

		//pants
		item.id = 6016;
		item.reference_key = 7008;
		item.item_type = (UINT)EItemType::AvatarPart;
		item.rank = (UINT)EItemRankType::Normal;
		wcscpy(item.name, L"이키더비키 신발");
		item.cooltime = 5.0f;
		wcscpy(item.field, L"");
		item.field_index = 0;
		wcscpy(item.icon, L"mg_ashoesAtlasTexture");
		item.icon_index = 0;
		wcscpy(item.desc, L"이키더비키 신발");

		mItemTable.insert(std::make_pair(6016, item));

		item.id = 6017;
		item.reference_key = 7008;
		item.item_type = (UINT)EItemType::AvatarPart;
		item.rank = (UINT)EItemRankType::Normal;
		wcscpy(item.name, L"차원의 별자리 신발");
		item.cooltime = 5.0f;
		wcscpy(item.field, L"");
		item.field_index = 1;
		wcscpy(item.icon, L"mg_ashoesAtlasTexture");
		item.icon_index = 1;
		wcscpy(item.desc, L"차원의 별자리 신발");

		mItemTable.insert(std::make_pair(6017, item));
#pragma endregion

#pragma region register avatar type
		// belt
		AvatarPartInfo avatar = {};
		avatar.id = 7000;
		avatar.part_type = (UINT)EAvatarParts::Belt;
		mAvatarPartTable.insert(std::make_pair(7000, avatar));
		//body
		avatar.id = 7001;
		avatar.part_type = (UINT)EAvatarParts::Base;
		mAvatarPartTable.insert(std::make_pair(7001, avatar));
		//coat
		avatar.id = 7002;
		avatar.part_type = (UINT)EAvatarParts::Coat;
		mAvatarPartTable.insert(std::make_pair(7002, avatar));

		//cap
		avatar.id = 7003;
		avatar.part_type = (UINT)EAvatarParts::Cap;
		mAvatarPartTable.insert(std::make_pair(7003, avatar));

		//face
		avatar.id = 7004;
		avatar.part_type = (UINT)EAvatarParts::Face;
		mAvatarPartTable.insert(std::make_pair(7004, avatar));

		//hair
		avatar.id = 7005;
		avatar.part_type = (UINT)EAvatarParts::Hair;
		mAvatarPartTable.insert(std::make_pair(7005, avatar));

		//neck
		avatar.id = 7006;

		avatar.part_type = (UINT)EAvatarParts::Neck;
		mAvatarPartTable.insert(std::make_pair(7006, avatar));

		//pants
		avatar.id = 7007;
		avatar.part_type = (UINT)EAvatarParts::Pants;
		mAvatarPartTable.insert(std::make_pair(7007, avatar));

		//shoes
		avatar.id = 7008;
		avatar.part_type = (UINT)EAvatarParts::Pants;
		mAvatarPartTable.insert(std::make_pair(7008, avatar));
#pragma endregion

#pragma region avatar sub info

#pragma endregion
		AvatarSubInfo sub_info = {};

		//cap 
		sub_info.id = 6006;
		sub_info.z_pos = -0.002f;
		wcscpy(sub_info.field, L"mg_cap25800a.img");
		mAvatarSubTable.insert(std::make_pair(sub_info.id, std::vector<AvatarSubInfo>()));
		mAvatarSubTable[sub_info.id].push_back(sub_info);

		sub_info.id = 6006;
		sub_info.z_pos = -0.002f;
		wcscpy(sub_info.field, L"mg_cap25800b.img");
		mAvatarSubTable[sub_info.id].push_back(sub_info);
		sub_info.id = 6006;
		sub_info.z_pos = -0.002f;
		wcscpy(sub_info.field, L"mg_cap25800c.img");
		mAvatarSubTable[sub_info.id].push_back(sub_info);

		sub_info.id = 6007;
		sub_info.z_pos = -0.002f;
		wcscpy(sub_info.field, L"mg_cap33200c.img");
		mAvatarSubTable.insert(std::make_pair(sub_info.id, std::vector<AvatarSubInfo>()));
		mAvatarSubTable[sub_info.id].push_back(sub_info);

		/*sub_info.id = 6007;
		sub_info.flag = 1;
		wcscpy(sub_info.field, L"mg_cap33200cf.img");
		mAvatarSubTable[sub_info.id].push_back(sub_info);

		sub_info.id = 6007;
		sub_info.flag = 1;
		wcscpy(sub_info.field, L"mg_cap33200kf.img");
		mAvatarSubTable[sub_info.id].push_back(sub_info);*/

		sub_info.id = 6007;
		sub_info.z_pos = -0.002f;
		wcscpy(sub_info.field, L"mg_cap33200k.img");
		mAvatarSubTable[sub_info.id].push_back(sub_info);

		//coat
		sub_info.id = 6004;
		sub_info.z_pos = -0.001f;
		wcscpy(sub_info.field, L"mg_coat22700a.img");
		mAvatarSubTable.insert(std::make_pair(sub_info.id, std::vector<AvatarSubInfo>()));
		mAvatarSubTable[sub_info.id].push_back(sub_info);

		sub_info.id = 6004;
		sub_info.z_pos = -0.001f;
		wcscpy(sub_info.field, L"mg_coat22700b.img");
		mAvatarSubTable[sub_info.id].push_back(sub_info);
		
		sub_info.id = 6004;
		sub_info.z_pos = -0.001f;
		wcscpy(sub_info.field, L"mg_coat22700c.img");
		mAvatarSubTable[sub_info.id].push_back(sub_info);


		sub_info.id = 6004;
		sub_info.z_pos = -0.001f;
		wcscpy(sub_info.field, L"mg_coat22700d.img");
		mAvatarSubTable[sub_info.id].push_back(sub_info);


		sub_info.id = 6005;
		sub_info.z_pos = -0.001f;
		wcscpy(sub_info.field, L"mg_coat26100a.img");
		mAvatarSubTable.insert(std::make_pair(sub_info.id, std::vector<AvatarSubInfo>()));
		mAvatarSubTable[sub_info.id].push_back(sub_info);

		sub_info.id = 6005;
		sub_info.z_pos = -0.001f;
		wcscpy(sub_info.field, L"mg_coat26100b.img");
		mAvatarSubTable[sub_info.id].push_back(sub_info);

		sub_info.id = 6005;
		sub_info.z_pos = -0.001f;
		wcscpy(sub_info.field, L"mg_coat26100c.img");
		mAvatarSubTable[sub_info.id].push_back(sub_info);


		sub_info.id = 6005;
		sub_info.z_pos = -0.001f;
		wcscpy(sub_info.field, L"mg_coat26100d.img");
		mAvatarSubTable[sub_info.id].push_back(sub_info);

		sub_info.id = 6005;
		sub_info.z_pos = -0.001f;
		wcscpy(sub_info.field, L"mg_coat26100x.img");
		mAvatarSubTable[sub_info.id].push_back(sub_info);

		//hair
		sub_info.id = 6010;
		sub_info.z_pos = -0.002f;
		wcscpy(sub_info.field, L"mg_hair20200a.img");
		mAvatarSubTable.insert(std::make_pair(sub_info.id, std::vector<AvatarSubInfo>()));
		mAvatarSubTable[sub_info.id].push_back(sub_info);

		sub_info.id = 6010;
		sub_info.z_pos = -0.002f;
		wcscpy(sub_info.field, L"mg_hair20200b.img");
		mAvatarSubTable[sub_info.id].push_back(sub_info);

		sub_info.id = 6011;
		sub_info.z_pos = -0.002f;
		wcscpy(sub_info.field, L"mg_hair23100d.img");
		mAvatarSubTable[sub_info.id].push_back(sub_info);

		sub_info.id = 6011;
		sub_info.z_pos = -0.002f;
		wcscpy(sub_info.field, L"mg_hair23100a.img");
		mAvatarSubTable.insert(std::make_pair(sub_info.id, std::vector<AvatarSubInfo>()));
		mAvatarSubTable[sub_info.id].push_back(sub_info);

		sub_info.id = 6011;
		sub_info.z_pos = -0.002f;
		wcscpy(sub_info.field, L"mg_hair23100b.img");
		mAvatarSubTable[sub_info.id].push_back(sub_info);

		sub_info.id = 6011;
		sub_info.z_pos = -0.002f;
		wcscpy(sub_info.field, L"mg_hair23100d.img");
		mAvatarSubTable[sub_info.id].push_back(sub_info);

		//neck
		sub_info.id = 6012;
		sub_info.z_pos = -0.003f;
		wcscpy(sub_info.field, L"mg_neck20000c.img");
		mAvatarSubTable.insert(std::make_pair(sub_info.id, std::vector<AvatarSubInfo>()));
		mAvatarSubTable[sub_info.id].push_back(sub_info);

		sub_info.id = 6012;
		sub_info.z_pos = -0.003f;
		wcscpy(sub_info.field, L"mg_neck20000d.img");
		mAvatarSubTable[sub_info.id].push_back(sub_info);

		sub_info.id = 6012;
		sub_info.z_pos = -0.003f;
		wcscpy(sub_info.field, L"mg_neck20000e.img");
		mAvatarSubTable[sub_info.id].push_back(sub_info);

		sub_info.id = 6012;
		sub_info.z_pos = -0.003f;
		wcscpy(sub_info.field, L"mg_neck20000x.img");
		mAvatarSubTable[sub_info.id].push_back(sub_info);


		sub_info.id = 6013;
		sub_info.z_pos = -0.003f;
		wcscpy(sub_info.field, L"mg_neck23300c.img");
		mAvatarSubTable.insert(std::make_pair(sub_info.id, std::vector<AvatarSubInfo>()));
		mAvatarSubTable[sub_info.id].push_back(sub_info);

		sub_info.id = 6013;
		sub_info.z_pos = -0.003f;
		wcscpy(sub_info.field, L"mg_neck23300d.img");
		mAvatarSubTable[sub_info.id].push_back(sub_info);

		sub_info.id = 6013;
		sub_info.z_pos = -0.003f;
		wcscpy(sub_info.field, L"mg_neck23300e.img");
		mAvatarSubTable[sub_info.id].push_back(sub_info);

		sub_info.id = 6013;
		sub_info.z_pos = -0.003f;
		wcscpy(sub_info.field, L"mg_neck23300x.img");
		mAvatarSubTable[sub_info.id].push_back(sub_info);

		//pants
		sub_info.id = 6014;
		sub_info.z_pos = 0.0f;
		wcscpy(sub_info.field, L"mg_pants20700a.img");
		mAvatarSubTable.insert(std::make_pair(sub_info.id, std::vector<AvatarSubInfo>()));
		mAvatarSubTable[sub_info.id].push_back(sub_info);

		sub_info.id = 6014;
		sub_info.z_pos = -0.001f;
		wcscpy(sub_info.field, L"mg_pants20700d.img");
		mAvatarSubTable[sub_info.id].push_back(sub_info);

		sub_info.id = 6015;
		sub_info.z_pos = 0.0f;
		wcscpy(sub_info.field, L"mg_pants23700d.img");
		mAvatarSubTable.insert(std::make_pair(sub_info.id, std::vector<AvatarSubInfo>()));
		mAvatarSubTable[sub_info.id].push_back(sub_info);

#pragma endregion


	}

	ItemManager::~ItemManager()
	{
	}

	void ItemManager::Initialize()
	{
		ItemTextureLoad();
	}

	void ItemManager::SetInventoryItem(std::shared_ptr<GameObject> inven, std::shared_ptr<GameObject> player)
	{
		int user_id = player->GetComponent<PlayerScript>()->GetUserInfo()->id;
		std::vector<OwnItemInfo>& ownList = mOwnItemTable[user_id];


		std::shared_ptr<ScrollRect> scrollRect = inven->GetChild<ScrollRect>()->GetComponent<ScrollRect>();
		std::shared_ptr<GameObject> content = scrollRect->GetContent();

		std::vector<std::shared_ptr<GameObject>> slotList = content->GetChilds();
		Vector3 slotScale = slotList[0]->GetComponent<Transform>()->scale;
		int slot_index = 0;
		for (auto own : ownList)
		{
			int itemID = own.id;
			int count = own.count; // text로 출력

			ItemInfo& item = mItemTable[itemID];

			std::shared_ptr<GameObject> cursor = manager::InputManager::GetInstance()->GetCursor();
			std::shared_ptr<roka::Image> object = object::Instantiate<roka::Image>();
			std::shared_ptr<ItemScript> script = object->AddScript<ItemScript>();
			script->SetUseOwner(player);
			script->SetItem(itemID);
			script->SetMode(cursor, EItemModeType::Icon);
			object->SetName(item.name);

			std::shared_ptr<Transform> tf = object->GetComponent<Transform>();
			tf->scale = slotScale;
			slotList[slot_index]->AddChild(object);
			slot_index++;
		}
	}

	const ItemInfo& ItemManager::GetItemInfo(std::shared_ptr<GameObject> caster, int id)
	{
		static ItemInfo sItemInfo = {};
		std::shared_ptr<PlayerScript> player = caster->GetComponent<PlayerScript>();
		if (player == nullptr)
			return sItemInfo;
		const int user_id = player->GetUserInfo()->id;
		if (UseOwnItem(user_id, id) == false)
			return sItemInfo;

		return GetItemInfo(id);
	}

	const ItemInfo& ItemManager::GetItemInfo(int id)
	{
		static roka::ItemInfo info = { -1 };
		auto itr = mItemTable.find(id);
		if (itr == mItemTable.end())
			return info;

		return itr->second;
	}

	const AvatarPartInfo& ItemManager::GetAvatarPartInfo(int id)
	{
		auto itr = mAvatarPartTable.find(id);
		return itr->second;
	}

	bool ItemManager::UseItem(std::shared_ptr<GameObject> caster, int id)
	{
		std::shared_ptr<PlayerScript> player = caster->GetComponent<PlayerScript>();
		if (player == nullptr)
			return false;
		const int user_id = player->GetUserInfo()->id;
		if (UseOwnItem(user_id, id) == false)
			return false;

		const ItemInfo& item = GetItemInfo(id);

		switch (item.item_type)
		{
		case (UINT)EItemType::Expendables:
			UseExpendablesItem(caster, id);
			break;
		case (UINT)EItemType::AvatarPart:
			const AvatarPartInfo& part = GetAvatarPartInfo(item.reference_key);
			UseAvatarPartItem(caster, id, part.part_type);
			break;
		}
	}

	bool ItemManager::UseOwnItem(int user_id, int item_id)
	{
		auto itr = mOwnItemTable.find(user_id);
		if (itr == mOwnItemTable.end())
			return false;

		for (auto& list : mOwnItemTable)
		{
			std::vector<OwnItemInfo>& items = list.second;
			for (auto item : items)
			{
				if (item.id == item_id && item.count != 0)
				{
					return true;
				}
			}
		}

		return false;
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

			switch (info.expendables_type)
			{
			case (UINT)EExpendablesType::HPRecovery:
				player->Recovery(info.value);
				break;
			}
			flag = true;

		}

		if (flag == true)
			return true;

		return false;
	}

	bool ItemManager::UseAvatarPartItem(std::shared_ptr<GameObject> caster, int avatar_id, int part_type)
	{
		std::shared_ptr<PlayerScript> player = caster->GetComponent<PlayerScript>();
		if (player == nullptr)
			return false;
		std::shared_ptr<GameObject> avatarObj = caster->GetChild<AvatarScript>();
		std::shared_ptr<AvatarScript> avatar = avatarObj->GetComponent<AvatarScript>();
		bool flag = false;
		int a = 0;
		size_t size = 0;
		std::shared_ptr<GameObject> Parent = object::Instantiate<GameObject>();
		std::shared_ptr<Transform> tf = Parent->GetComponent<Transform>();
		std::shared_ptr<Transform> pTf = caster->GetComponent<Transform>();
		Vector3 pos = pTf->position;
		//아바타 바꾸는 함수 호출
		size = mAvatarSubTable[avatar_id].size();
		std::wstring find_part;

	

		for (int i = 0; i < size; i++)
		{
			std::shared_ptr<GameObject> Part = object::Instantiate<GameObject>(prefab::Prefabs[L"AniObject"]);
			if (part_type == (UINT)EAvatarParts::Weapon)
			{

			}
			else
			{
				std::shared_ptr<SkinPartScript> skin = Part->AddComponent<SkinPartScript>();
				switch (part_type)
				{
				case (UINT)EAvatarParts::Hair:
					find_part = L"mgHair";
					break;
				case (UINT)EAvatarParts::Cap:
					find_part = L"mgCap";
					break;
				case (UINT)EAvatarParts::Coat:
					find_part = L"mgCoat";
					break;
				case (UINT)EAvatarParts::Neck:
					find_part = L"mgNeck";
					break;
				case (UINT)EAvatarParts::Pants:
					find_part = L"mgPants";
					break;
				}
				Vector3 pos2 = Vector3::Zero;
				std::shared_ptr<Transform> partTf = Part->GetComponent<Transform>();
				pos2.z = mAvatarSubTable[avatar_id][i].z_pos;
				partTf->position = pos2;
				Part->SetName(find_part + std::to_wstring(i));
				skin->Create(find_part, mAvatarSubTable[avatar_id][i].field);
				Parent->AddChild(Part);
				Parent->SetName(find_part);
			}

		}

		std::shared_ptr<GameObject> Find = avatarObj->GetChild(find_part);
		tf->scale = caster->GetComponent<Transform>()->scale;
		tf->position = -pos;
		if (Find != nullptr)
		{
			avatarObj->SwapRemoveChild(Find, Parent);
		}
		else
		{
			avatarObj->InsertChild(Parent, (UINT)part_type - 1);
		}
		
		avatar->RegisterPart((EAvatarParts)part_type, Parent);

		avatar->PlayPartsMotion();
		return true;
	}

	void ItemManager::ItemTextureLoad()
	{
		std::shared_ptr<NPK> npk = Resources::Find<NPK>(L"item");

		std::shared_ptr<Texture> texture = npk->CreateAtlas(L"field_material.img", 0, 3, L"ItemField");
		texture = npk->CreateAtlas(L"icon_material.img", 0, 2, L"ItemIcon");
	}

}
