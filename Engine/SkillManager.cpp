#include "SkillManager.h"

#include "MgNormalAtk.h"

#include "SpiderNormalAtk.h"
namespace roka::manager
{
	void SkillManager::Initialize()
	{
#pragma region player character skill
		ISkill* normalAttack = new MgNormalAtk();
		mSkillInfos.insert(std::make_pair(roka::enums::ECharacterClassType::Mage, std::map<std::wstring, ISkill*>()));
		mSkillInfos[roka::enums::ECharacterClassType::Mage].insert(std::make_pair(L"NormalAtk", normalAttack));
#pragma endregion
#pragma region monster skill
		ISkill* skill = new SpiderNormalAtk();
		mMonsterSkillInfos.insert(std::make_pair(roka::enums::EMonsterType::Spider, std::map<std::wstring, ISkill*>()));
		mMonsterSkillInfos[roka::enums::EMonsterType::Spider].insert(std::make_pair(L"Skill01", skill));
#pragma endregion	
	}
	void SkillManager::Release()
	{
		for (auto& character : mSkillInfos)
		{
			for (auto& skill : character.second)
			{
				ISkill* skillPtr = skill.second;
				delete skillPtr;
				skill.second = nullptr;
			}
		}
		for (auto& monster : mMonsterSkillInfos)
		{
			for (auto& skill : monster.second)
			{
				ISkill* skillPtr = skill.second;
				delete skillPtr;
				skill.second = nullptr;
			}
		}
		mSkillInfos.clear();
		mMonsterSkillInfos.clear();
	}
	ISkill* SkillManager::Find(roka::enums::ECharacterClassType type, std::wstring name)
	{
		auto itr = mSkillInfos.find(type);
		if (itr == mSkillInfos.end())
			return nullptr;
		auto itr2 = mSkillInfos[type].find(name);
		if (itr2 == mSkillInfos[type].end())
			return nullptr;

		ISkill* result = itr2->second;
		
		return result;
	}
	ISkill* SkillManager::Find(std::wstring name, roka::enums::EMonsterType type)
	{
		auto itr = mMonsterSkillInfos.find(type);
		if (itr == mMonsterSkillInfos.end())
			return nullptr;
		auto itr2 = mMonsterSkillInfos[type].find(name);
		if (itr2 == mMonsterSkillInfos[type].end())
			return nullptr;

		ISkill* result = itr2->second;

		return result;
	}
}