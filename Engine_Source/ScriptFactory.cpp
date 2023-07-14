#include "ScriptFactory.h"
#include "CameraScript.h"
#include "GridScript.h"
#include "MoveScript.h"
namespace roka
{
	std::map<EScriptType, std::function<std::shared_ptr<Script>(Script*)>> ScriptFactory::mFactories;
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
	}
	std::shared_ptr<Script> ScriptFactory::CreateNCopyComponent(Script* script)
	{
		EScriptType type = script->script_type;
		std::shared_ptr<Script> newScript = mFactories[type](script);
		return newScript;
	}
}