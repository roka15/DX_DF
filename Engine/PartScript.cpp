#include "PartScript.h"
#include "GameObject.h"
#include "Resources.h"
#include "Texture.h"
#include "MeshRenderer.h"
#include "Animator.h"

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
	void PartScript::PlayPartMotion(std::wstring name, bool flag)
	{
		std::shared_ptr<Animator> ani = owner->GetComponent<Animator>();
		ani->PlayAnimation(name, flag);
	}
	void PartScript::PlayPartSprite(std::wstring name, int index)
	{
		std::shared_ptr<Animator> ani = owner->GetComponent<Animator>();
		ani->PlayAniSprite(name, index);
	}
	void PartScript::CreateAni(std::wstring npk_name, std::wstring pack_name, std::wstring set_name, UINT start, UINT end, float duration)
	{
		std::shared_ptr<Animator> ani = owner->GetComponent<Animator>();
		ani->Create(npk_name, pack_name, set_name, start, end, duration);
	}
	void PartScript::CreateAni(std::shared_ptr<Texture> atlas, std::wstring set_name, UINT start, UINT end, float duration)
	{
		std::shared_ptr<Animator> ani = owner->GetComponent<Animator>();
		ani->Create(atlas,set_name, start, end, duration);
	}
	void PartScript::ConnectAnimations(std::wstring prev_name, std::wstring next_name)
	{
		std::shared_ptr<Animator> ani = owner->GetComponent<Animator>();
		GameObject* Owner = owner;
		ani->CompleteEvent(prev_name) = std::bind([Owner,next_name]()->void
			{
				Owner->GetComponent<Animator>()->PlayAnimation(next_name, false);
			});
	}
	void PartScript::ConnectEvent(UINT type,std::wstring name,std::function<void()> func)
	{
		std::shared_ptr<Animator> ani = owner->GetComponent<Animator>();
		ani->GetEvent((Animator::EAniEventType)type, name) = func;
	}
	void PartScript::Right()
	{
		std::shared_ptr<MeshRenderer> mr = owner->GetComponent<MeshRenderer>();
		mr->material->shader = Resources::Find<Shader>(L"AnimationShader");
	}
	void PartScript::Left()
	{
		std::shared_ptr<MeshRenderer> mr = owner->GetComponent<MeshRenderer>();
		mr->material->shader = Resources::Find<Shader>(L"VerticalInverterAnimationShader");
	}
	void PartScript::Stop()
	{
		std::shared_ptr<Animator> ani = owner->GetComponent<Animator>();
		ani->Stop();
	}
	void PartScript::Start()
	{
		std::shared_ptr<Animator> ani = owner->GetComponent<Animator>();
		ani->Play();
	}
	void PartScript::NextSprite()
	{
		std::shared_ptr<Animator> ani = owner->GetComponent<Animator>();
		ani->NextSprite();
	}
}