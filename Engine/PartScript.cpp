#include "PartScript.h"
#include "GameObject.h"
#include "Resources.h"
#include "MeshRenderer.h"
namespace roka
{
	PartScript::PartScript() :Script(EScriptType::Part),
		mPartType(EAvatarParts::None)
	{
	}
	PartScript::PartScript(const PartScript& ref) : Script(ref),
		mPartType(ref.mPartType)
	{
	}
	void PartScript::Copy(Component* src)
	{
		Script::Copy(src);
		PartScript* source = dynamic_cast<PartScript*>(src);
		if (source == nullptr)
			return;
		mPartType = source->mPartType;
	}
	PartScript::~PartScript()
	{
	}
	void PartScript::Initialize()
	{
		std::shared_ptr<MeshRenderer> mr = owner->GetComponent<MeshRenderer>();

		std::shared_ptr<Material> material = std::make_shared<Material>();
		material->shader = Resources::Find<Shader>(L"AnimationShader");
		material->render_mode = ERenderMode::Transparent;
		mr->material = material;
	}
	void PartScript::Update()
	{
	}
	void PartScript::LateUpdate()
	{
	}
	void PartScript::Render()
	{
	}
}