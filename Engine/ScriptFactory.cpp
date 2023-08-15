#include "ScriptFactory.h"
#include "CameraScript.h"
#include "GridScript.h"
#include "MoveScript.h"
#include "PlayerScript.h"
#include "AvatarScript.h"
#include "PartScript.h"
#include "SkillScript.h"
#include "WeaponScript.h"
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
		mFactories[EScriptType::Weapon] = [](Script* script)
		{
			WeaponScript* ss = dynamic_cast<WeaponScript*>(script);
			return std::shared_ptr<WeaponScript>(new WeaponScript(*ss));
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