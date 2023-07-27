#pragma once
#include "RokaInclude.h"

using namespace roka::enums;

namespace roka::info
{
	struct UserInfo
	{
		std::wstring party_name; // 모험단 명
		std::wstring id;
		std::wstring pw;
		int character_cnt;
	};
	struct CharacterInfo
	{
		std::wstring name;
		int fame;//명성
		int fatigue;//피로도
		ECharacterClassType character_class_type;

		//avatar
		std::wstring base_skin_avatar;
		std::wstring face_avatar;
		std::wstring hair_avatar;
		std::wstring cap_avatar;
		std::wstring coat_avatar;
		std::wstring neck_avatar;
		std::wstring pants_avatar;
		std::wstring belt_avatar;
		std::wstring shoes_avatar;
		std::wstring weapon_avatar;
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

		const std::wstring& GetPartyName() { return mUserInfo->party_name; }
		const std::wstring& GetName() { return mCharacterInfo->name; }
		const int& GetFame() { return mCharacterInfo->fame; }
		const int& GetFatigue() { return mCharacterInfo->fatigue; }
		const ECharacterClassType& GetClassType() { return mCharacterInfo->character_class_type; }
		
		const std::wstring& GetBaseAvatar() { return mCharacterInfo->base_skin_avatar; }

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

