#pragma once
#define MAXITEMNAME 255
#define MAXITEMSTR 500
namespace roka
{
	enum class EItemType
	{
		NONE,
		Expendables,//�Ҹ�ǰ
		Part,//part�� state ���� = ��� ����
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

	/* ��� - 
	1.item info���� item type�� ���� ���� table�� �޶�����.
	2.���� ���̺��� item �� id�� �ܷ�Ű�� ��� �ִ�.
	3.���� ���̺� item id�� �ְ� �˻��Ǵ� ȿ������ ��� �����Ѵ�.
	
	ex) ü�� + �̼�
    item table = id : 1000 | name : ȣ���� ����� ���� 
	expendables table = 
	Ʃ��: id:3000 - ü��
	      id:3001 - �̼�
    �Ӽ� : id: 3000 | �ܷ�Ű : 1000 | expendablesType : HPRecovery | value : 30
	�Ӽ� : id: 3001 | �ܷ�Ű : 1000 | expendablesType : SpeedBuff | value : 10

	select * from expendables where foreignkey == 1000;
	�ϸ� ���Ͱ��� ������ �ΰ� �˻��� ��.
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
		unsigned int expendables_type;//������ Ÿ��
		float value; // ������ ������
	};
	
	struct AvatarPartInfo
	{
		unsigned int id;
		unsigned int part_type; // ���� Ÿ��.
	};

	struct AvatarSubInfo
	{
		unsigned int id;
		wchar_t field[MAXITEMSTR];
		float z_pos;
	};


	//�� ������ slot �����͵� �Բ� ���̴°� ������ �ֳ��ϸ� ������ ���� �ѵ� ��ġ�� �ִ� ���Կ� �״�� ��ġ�� �ֱ� ����.
	//������ �ð� ��� ����
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