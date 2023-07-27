#include "User.h"
#include "Input.h"
namespace roka::info
{
	User::User():
		mUserInfo(std::make_unique<UserInfo>()),
		mCharacterInfo(std::make_unique<CharacterInfo>()),
		mKeysInfo(std::make_unique<KeysInfo>())
	{
	}
	User::User(const User& ref)
	{
		memcpy(mUserInfo.get(), ref.mUserInfo.get(), sizeof(UserInfo));
		memcpy(mCharacterInfo.get(), ref.mCharacterInfo.get(), sizeof(CharacterInfo));
		memcpy(mKeysInfo.get(), ref.mKeysInfo.get(), sizeof(KeysInfo));
	}
	void User::Copy(User* src)
	{
		memcpy(mUserInfo.get(), src->mUserInfo.get(), sizeof(UserInfo));
		memcpy(mCharacterInfo.get(), src->mCharacterInfo.get(), sizeof(CharacterInfo));
		memcpy(mKeysInfo.get(), src->mKeysInfo.get(), sizeof(KeysInfo));
	}
	User::~User()
	{
	}
	void User::Initialize()
	{
		mUserInfo->party_name = L"코딩노예람";
		mUserInfo->id = L"1234";
		mUserInfo->pw = L"1234";
		mUserInfo->character_cnt = 1;

		mCharacterInfo->name = L"로카";
		mCharacterInfo->fame = 1000;
		mCharacterInfo->fatigue = 156;
		mCharacterInfo->character_class_type = ECharacterClassType::Mage;

		mCharacterInfo->base_skin_avatar = L"mg_body80500.img";

		mKeysInfo->right = (UINT)EKeyCode::RIGHT;
		mKeysInfo->left = (UINT)EKeyCode::LEFT;
		mKeysInfo->up = (UINT)EKeyCode::UP;
		mKeysInfo->down = (UINT)EKeyCode::DOWN;
	}
	void User::Release()
	{
	}
}