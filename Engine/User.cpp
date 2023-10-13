#include "User.h"
#include "Input.h"
namespace roka::info
{
	User::User() :
		mUserInfo(std::make_unique<UserInfo>()),
		mCharacterInfo(std::make_unique<CharacterInfo>()),
		mKeysInfo(std::make_unique<KeysInfo>())
	{
	}
	User::User(const User& ref)
	{
		mUserInfo = std::make_unique<UserInfo>();
		mCharacterInfo = std::make_unique<CharacterInfo>();
		mKeysInfo = std::make_unique<KeysInfo>();
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
		mUserInfo->index = 1;
		wcscpy(mUserInfo->party_name,L"코딩노예람");
		wcscpy(mUserInfo->id, L"1234");
		mUserInfo->character_cnt = 1;

		wcscpy(mCharacterInfo->name, L"로카");
		mCharacterInfo->fame = 1000;
		mCharacterInfo->fatigue = 156;
		mCharacterInfo->character_class_type = ECharacterClassType::Mage;
		//mg_body0019.img
		//mg_body80500.img
		wcscpy(mCharacterInfo->base_skin_avatar,L"mg_body80500.img");
		wcscpy(mCharacterInfo->weapon_avatar1, L"mg_broom7200d.img");
		wcscpy(mCharacterInfo->weapon_avatar2, L"mg_broom7200c.img");

		mKeysInfo->right = (UINT)EKeyCode::RIGHT;
		mKeysInfo->left = (UINT)EKeyCode::LEFT;
		mKeysInfo->up = (UINT)EKeyCode::UP;
		mKeysInfo->down = (UINT)EKeyCode::DOWN;
		mKeysInfo->jump = (UINT)EKeyCode::SPACE;
		mKeysInfo->quick_standing = (UINT)EKeyCode::C;
		mKeysInfo->normalAtk = (UINT)EKeyCode::X;
		mKeysInfo->skill1 = (UINT)EKeyCode::F;

		mSkillNames.insert(std::make_pair(mKeysInfo->skill1, L"mageAntiGravity"));
	}
	void User::Release()
	{
	}
	
}