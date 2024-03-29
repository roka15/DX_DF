#pragma once
#include "SingleTon.h"
#include "ContentEnums.h"
namespace roka
{
	class ISkill;
}
namespace roka::manager
{
	class SkillManager :
		public Singleton<SkillManager>
	{
	private:
		SkillManager() {}
	public:
		virtual ~SkillManager() {};
		void Initialize();
		void Release();

		ISkill* Find(roka::enums::ECharacterClassType type,std::wstring name);
		ISkill* Find(std::wstring name,roka::enums::EMonsterType type);
	private:
		friend class Singleton<SkillManager>;
	private:
		std::map<roka::enums::ECharacterClassType, std::map<std::wstring, ISkill*>> mSkillInfos;
		std::map<roka::enums::EMonsterType, std::map<std::wstring, ISkill*>> mMonsterSkillInfos;
	};
}


