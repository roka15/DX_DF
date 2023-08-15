#pragma once
#include "RokaInclude.h"

using namespace roka::enums;
#define MAX_NAME 10
#define MAX_ID 10
#define MAX_AVATAR 255
namespace roka::info
{
	struct UserInfo
	{
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

		const std::wstring& GetPartyName() { return std::wstring(mUserInfo->party_name); }
		const std::wstring& GetName() { return std::wstring(mCharacterInfo->name); }
		const int& GetFame() { return mCharacterInfo->fame; }
		const int& GetFatigue() { return mCharacterInfo->fatigue; }
		const ECharacterClassType& GetClassType() { return mCharacterInfo->character_class_type; }
		
		std::wstring GetBaseAvatar() { return std::wstring(mCharacterInfo->base_skin_avatar); }
		std::wstring GetWeaponAvatar1() { return std::wstring(mCharacterInfo->weapon_avatar1); }
		std::wstring GetWeaponAvatar2() { return std::wstring(mCharacterInfo->weapon_avatar2); }

		const UINT& GetRightKey() { return mKeysInfo->right; }
		const UINT& GetLeftKey() { return mKeysInfo->left; }
		const UINT& GetUpKey() { return mKeysInfo->up; }
		const UINT& GetDownKey() { return mKeysInfo->down; }


		GET_PROPERTY(GetPartyName) std::wstring party_name;
		GET_PROPERTY(GetName) std::wstring name;
		GET_PROPERTY(GetFame) int fame;
		GET_PROPERTY(GetFatigue) int fatigue;
		GET_PROPERTY(GetClassType) ECharacterClassType class_type;

		GET_PROPERTY(GetBaseAvatar) std::wstring base_avartar;
		GET_PROPERTY(GetWeaponAvatar1) std::wstring weapon_avatar1;
		GET_PROPERTY(GetWeaponAvatar2) std::wstring weapon_avatar2;

		GET_PROPERTY(GetRightKey) UINT right_key;
		GET_PROPERTY(GetLeftKey) UINT left_key;
		GET_PROPERTY(GetUpKey) UINT up_key;
		GET_PROPERTY(GetDownKey) UINT down_key;

	private:
		std::unique_ptr<UserInfo> mUserInfo;
		std::unique_ptr<CharacterInfo> mCharacterInfo;
		std::unique_ptr<KeysInfo> mKeysInfo;
		//나중에 socket 통신 객체 소유.
	};
}

