#pragma once
#define MAXITEMNAME 255
#define MAXITEMSTR 500
namespace roka
{
	enum class EItemType
	{
		NONE,
		Expendables,//소모품
		Part,//part형 state 변동 = 장비 파츠
		AvatarPart,//avatar part
		END,
	};
	enum class EItemRankType
	{
		NONE,
		Normal,
		Rare,
		Legend,
		END,
	};
	enum class EExpendablesType
	{
		HPRecovery,
		SpeedBuff,
	};

	/* 사용 - 
	1.item info에서 item type에 따라 관찰 table이 달라진다.
	2.관찰 테이블은 item 의 id를 외래키로 들고 있다.
	3.관찰 테이블에 item id를 넣고 검색되는 효과들을 모두 적용한다.
	
	ex) 체력 + 이속
    item table = id : 1000 | name : 호랑이 기운이 쑥쑥 
	expendables table = 
	튜플: id:3000 - 체력
	      id:3001 - 이속
    속성 : id: 3000 | 외래키 : 1000 | expendablesType : HPRecovery | value : 30
	속성 : id: 3001 | 외래키 : 1000 | expendablesType : SpeedBuff | value : 10

	select * from expendables where foreignkey == 1000;
	하면 위와같이 정보가 두개 검색될 것.
	*/
	struct ItemInfo
	{
		int id;
		unsigned int item_type;
		unsigned int rank;
		wchar_t name[MAXITEMNAME];
		double cooltime;
		wchar_t field[MAXITEMSTR];
		int field_index;
		wchar_t icon[MAXITEMSTR];
		int icon_index;
		wchar_t desc[MAXITEMSTR];
		int reference_key;
	};

	struct ExpendablesInfo
	{
		unsigned int id;
		unsigned int foreignkey;
		unsigned int expendables_type;//아이템 타입
		float value; // 아이템 증감량
	};
	
	struct AvatarPartInfo
	{
		unsigned int id;
		unsigned int part_type; // 파츠 타입.
	};

	struct AvatarSubInfo
	{
		unsigned int id;
		wchar_t field[MAXITEMSTR];
		float z_pos;
	};


	//이 정보는 slot 정보와도 함께 엮이는게 좋을듯 왜냐하면 게임을 껐다 켜도 위치해 있던 슬롯에 그대로 위치해 있기 때문.
	//하지만 시간 없어서 생략
	struct UserItemInfo
	{
		int OwnItemInfoTableKey;
	};

	struct OwnItemInfo
	{
		unsigned int id;
		unsigned int count;
	};

	
}



//userTable -> ownTable -> Item Table