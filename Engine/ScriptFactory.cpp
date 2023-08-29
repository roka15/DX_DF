#include "ScriptFactory.h"
#include "CameraScript.h"
#include "GridScript.h"
#include "MoveScript.h"
#include "TargetMoveScript.h"
#include "PlayerScript.h"

#include "AvatarScript.h"
#include "PartScript.h"
#include "SkillScript.h"
#include "MonsterSkillScript.h"
#include "WeaponScript.h"
#include "HitBoxScript.h"
#include "PortalScript.h"

#include "MonsterScript.h"
#include "NormalMonsterScript.h"
#include "SpiderMonsterScript.h"
#include "NamedMonsterScript.h"
#include "TairangMonsterScript.h"
namespace roka
{
	void ScriptFactory::Initialize()
	{
		mFactories[EScriptType::Camera] = [](Script* script){
			CameraScript* cs = dynamic_cast<CameraScript*>(script);
			return std::shared_ptr<CameraScript>(new CameraScript(*cs));
		};
		mFactories[EScriptType::Grid] = [](Script* script) {
			GridScript* gs = dynamic_cast<GridScript*>(script);
			return std::shared_ptr<GridScript>(new GridScript(*gs));
		};
		mFactories[EScriptType::Move] = [](Script* script) {
			MoveScript* ms = dynamic_cast<MoveScript*>(script);
			return std::shared_ptr<MoveScript>(new MoveScript(*ms));
		};
		mFactories[EScriptType::TargetMove] = [](Script* script) {
			TargetMoveScript* ts = dynamic_cast<TargetMoveScript*>(script);
			return std::shared_ptr<TargetMoveScript>(new TargetMoveScript(*ts));
		};
		mFactories[EScriptType::Player] = [](Script* script)
		{
			PlayerScript* ps = dynamic_cast<PlayerScript*>(script);
			return std::shared_ptr<PlayerScript>(new PlayerScript(*ps));
		};
		mFactories[EScriptType::Avatar] = [](Script* script)
		{
			AvatarScript* ps = dynamic_cast<AvatarScript*>(script);
			return std::shared_ptr<AvatarScript>(new AvatarScript(*ps));
		};
		mFactories[EScriptType::Part] = [](Script* script)
		{
			PartScript* ps = dynamic_cast<PartScript*>(script);
			return std::shared_ptr<PartScript>(new PartScript(*ps));
		};
		mFactories[EScriptType::Part] = [](Script* script)
		{
			PartScript* ps = dynamic_cast<PartScript*>(script);
			return std::shared_ptr<PartScript>(new PartScript(*ps));
		};
		mFactories[EScriptType::SkillBase] = [](Script* script)
		{
			SkillScript* ss = dynamic_cast<SkillScript*>(script);
			return std::shared_ptr<SkillScript>(new SkillScript(*ss));
		};
		mFactories[EScriptType::SkillMonster] = [](Script* script)
		{
			MonsterSkillScript* ss = dynamic_cast<MonsterSkillScript*>(script);
			return std::shared_ptr<MonsterSkillScript>(new MonsterSkillScript(*ss));
		};
		mFactories[EScriptType::Weapon] = [](Script* script)
		{
			WeaponScript* ss = dynamic_cast<WeaponScript*>(script);
			return std::shared_ptr<WeaponScript>(new WeaponScript(*ss));
		};
		mFactories[EScriptType::HitBox] = [](Script* script)
		{
			HitBoxScript* hs = dynamic_cast<HitBoxScript*>(script);
			return std::shared_ptr<HitBoxScript>(new HitBoxScript(*hs));
		};
		mFactories[EScriptType::Portal] = [](Script* script)
		{
			PortalScript* hs = dynamic_cast<PortalScript*>(script);
			return std::shared_ptr<PortalScript>(new PortalScript(*hs));
		};
		
		mFactories[EScriptType::NormalMonster] = [](Script* script)
		{
			NormalMonsterScript* hs = dynamic_cast<NormalMonsterScript*>(script);
			return std::shared_ptr<NormalMonsterScript>(new NormalMonsterScript(*hs));
		};
		mFactories[EScriptType::SpiderMonster] = [](Script* script)
		{
			SpiderMonsterScript* hs = dynamic_cast<SpiderMonsterScript*>(script);
			return std::shared_ptr<SpiderMonsterScript>(new SpiderMonsterScript(*hs));
		};
		mFactories[EScriptType::NamedMonster] = [](Script* script)
		{
			NamedMonsterScript* hs = dynamic_cast<NamedMonsterScript*>(script);
			return std::shared_ptr<NamedMonsterScript>(new NamedMonsterScript(*hs));
		};
		mFactories[EScriptType::TairangMonster] = [](Script* script)
		{
			TairangMonsterScript* hs = dynamic_cast<TairangMonsterScript*>(script);
			return std::shared_ptr<TairangMonsterScript>(new TairangMonsterScript(*hs));
		};
	}
	std::shared_ptr<Component> ScriptFactory::CreateNCopy(Component* comp)
	{
		Script* script = dynamic_cast<Script*>(comp);
		if (script == nullptr)
			return nullptr;
		EScriptType type = script->script_type;

		std::shared_ptr<Script> newScript = mFactories[type](script);
		return newScript;
	}
}