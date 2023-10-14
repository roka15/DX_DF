#pragma once
#include "RokaInclude.h"

using namespace roka::enums;
#define MAX_NAME 10
#define MAX_ID 10
#define MAX_AVATAR 255
#define MAX_SKILLNAME 255
namespace roka::info
{
	struct UserInfo
	{
		unsigned int index;
		wchar_t party_name[MAX_NAME]; // 모험단 명
		wchar_t id[MAX_ID];

		int character_cnt;
	};
	struct CharacterInfo
	{
		wchar_t  name[MAX_NAME];
		int fame;//명성
		int fatigue;//피로도
		ECharacterClassType character_class_type;

		//avatar
		wchar_t base_skin_avatar[MAX_AVATAR];
		wchar_t face_avatar[MAX_AVATAR];
		wchar_t hair_avatar[MAX_AVATAR];
		wchar_t cap_avatar[MAX_AVATAR];
		wchar_t coat_avatar[MAX_AVATAR];
		wchar_t neck_avatar[MAX_AVATAR];
		wchar_t pants_avatar[MAX_AVATAR];
		wchar_t belt_avatar[MAX_AVATAR];
		wchar_t shoes_avatar[MAX_AVATAR];
		wchar_t weapon_avatar1[MAX_AVATAR];
		wchar_t weapon_avatar2[MAX_AVATAR];
	};
	struct KeysInfo
	{
		UINT right;
		UINT left;
		UINT up;
		UINT down;
		UINT jump;
		UINT quick_standing;
		UINT normalAtk;
		UINT skill1;
		UINT inven;
		UINT pickup;
	};
	struct SkillNameInfo
	{
		wchar_t skill1_name[MAX_SKILLNAME];
	};
	class User
	{
	public:
		User();
		User(const User& ref);
		void Copy(User* ref);
		~User();

		void Initialize(); //나중에 로그인 성공시 db 가져온 정보 세팅해주기
		void Release();

		const int GetID()const { return mUserInfo->index; }

		const std::wstring& GetPartyName()const { return std::wstring(mUserInfo->party_name); }
		const std::wstring& GetName()const { return std::wstring(mCharacterInfo->name); }
		const int& GetFame()const { return mCharacterInfo->fame; }
		const int& GetFatigue()const { return mCharacterInfo->fatigue; }
		const ECharacterClassType& GetClassType()const { return mCharacterInfo->character_class_type; }
		
		std::wstring GetBaseAvatar()const { return std::wstring(mCharacterInfo->base_skin_avatar); }
		std::wstring GetWeaponAvatar1()const { return std::wstring(mCharacterInfo->weapon_avatar1); }
		std::wstring GetWeaponAvatar2()const { return std::wstring(mCharacterInfo->weapon_avatar2); }

		const UINT& GetRightKey()const { return mKeysInfo->right; }
		const UINT& GetLeftKey()const { return mKeysInfo->left; }
		const UINT& GetUpKey()const { return mKeysInfo->up; }
		const UINT& GetDownKey()const { return mKeysInfo->down; }
		const UINT& GetNormalAtkKey()const { return mKeysInfo->normalAtk; }
		const UINT& GetJumpKey()const { return mKeysInfo->jump; }
		const UINT& GetSkillKey01()const { return mKeysInfo->skill1; }
		const UINT& GetInvenKey()const { return mKeysInfo->inven; }
		const UINT& GetPickUp()const { return mKeysInfo->pickup; }

		void SetBaseAvatar(std::wstring name) { wcscpy(mCharacterInfo->base_skin_avatar,name.c_str()); }
		void SetWeaponAvatar1(std::wstring name) { wcscpy(mCharacterInfo->weapon_avatar1, name.c_str()); }
		void SetWeaponAvatar2(std::wstring name) { wcscpy(mCharacterInfo->weapon_avatar2, name.c_str()); }

		const std::wstring& GetKeySkillName(UINT input)const {return mSkillNames.find(input)->second;}

		GET_PROPERTY(GetID) int id;
		GET_PROPERTY(GetPartyName) std::wstring party_name;
		GET_PROPERTY(GetName) std::wstring name;
		GET_PROPERTY(GetFame) int fame;
		GET_PROPERTY(GetFatigue) int fatigue;
		GET_PROPERTY(GetClassType) ECharacterClassType class_type;

		PROPERTY(GetBaseAvatar,SetBaseAvatar) std::wstring base_avartar;
		PROPERTY(GetWeaponAvatar1,SetWeaponAvatar1) std::wstring weapon_avatar1;
		PROPERTY(GetWeaponAvatar2,SetWeaponAvatar2) std::wstring weapon_avatar2;

		GET_PROPERTY(GetRightKey) UINT right_key;
		GET_PROPERTY(GetLeftKey) UINT left_key;
		GET_PROPERTY(GetUpKey) UINT up_key;
		GET_PROPERTY(GetDownKey) UINT down_key;
		GET_PROPERTY(GetNormalAtkKey) UINT normalAtk_key;
		GET_PROPERTY(GetJumpKey) UINT jump_key;
		GET_PROPERTY(GetSkillKey01) UINT skill01_key;
		GET_PROPERTY(GetInvenKey) UINT inven_key;
		GET_PROPERTY(GetPickUp) UINT pickup_key;

	private:
		std::unique_ptr<UserInfo> mUserInfo;
		std::unique_ptr<CharacterInfo> mCharacterInfo;
		std::unique_ptr<KeysInfo> mKeysInfo;
		std::map<UINT, std::wstring> mSkillNames;
		//나중에 socket 통신 객체 소유.
	};
}

