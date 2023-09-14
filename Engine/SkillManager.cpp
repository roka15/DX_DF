#include "SkillManager.h"

#include "MgNormalAtk.h"
namespace roka::manager
{
	void SkillManager::Initialize()
	{
		ISkill* normalAttack = new MgNormalAtk();
		mSkillInfos.insert(std::make_pair(roka::enums::ECharacterClassType::Mage, std::map<std::wstring, ISkill*>()));
		mSkillInfos[roka::enums::ECharacterClassType::Mage].insert(std::make_pair(L"NormalAtk", normalAttack));
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
		mSkillInfos.clear();
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
}