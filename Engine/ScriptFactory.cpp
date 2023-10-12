#include "ScriptFactory.h"
#include "CameraScript.h"
#include "GridScript.h"
#include "MoveScript.h"
#include "TargetMoveScript.h"
#include "PlayerScript.h"

#include "AvatarScript.h"
#include "PartScript.h"
#include "WeaponPartScript.h"
#include "SkinPartScript.h"
#include "WarningScript.h"

#include "MonsterScript.h"
#include "NormalMonsterScript.h"
#include "SpiderMonsterScript.h"
#include "NamedMonsterScript.h"
#include "TairangMonsterScript.h"

#include "ChangeSizeOverTime.h"
#include "GaugeScript.h"

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
		mFactories[EScriptType::PartWeapon] = [](Script* script)
		{
			WeaponPartScript* ps = dynamic_cast<WeaponPartScript*>(script);
			return std::shared_ptr<WeaponPartScript>(new WeaponPartScript(*ps));
		};
		mFactories[EScriptType::PartSkin] = [](Script* script)
		{
			SkinPartScript* ps = dynamic_cast<SkinPartScript*>(script);
			return std::shared_ptr<SkinPartScript>(new SkinPartScript(*ps));
		};
		mFactories[EScriptType::Warning] = [](Script* script) {
			WarningScript* gs = dynamic_cast<WarningScript*>(script);
			return std::shared_ptr<WarningScript>(new WarningScript(*gs));
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
		mFactories[EScriptType::ChangeSizeOverTime] = [](Script* script)
		{
			ChangeSizeOverTime* cs = dynamic_cast<ChangeSizeOverTime*>(script);
			return std::shared_ptr<ChangeSizeOverTime>(new ChangeSizeOverTime(*cs));
		};
		mFactories[EScriptType::Gauge] = [](Script* script)
		{
			GaugeScript* cs = dynamic_cast<GaugeScript*>(script);
			return std::shared_ptr<GaugeScript>(new GaugeScript(*cs));
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