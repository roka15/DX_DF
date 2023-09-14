#include "MageNormalAttackScript.h"

#include "Input.h"
#include "RokaTime.h"
#include "GameObject.h"

#include "Animator.h"
#include "MeshRenderer.h"
#include "Transform.h"
#include "Collider2D.h"

#include "AvatarScript.h"

namespace roka
{
	MageNormalAttackScript::MageNormalAttackScript():PlayerNormalAttackScript(EScriptType::SkillMageNormalAtk)
	{
	}
	MageNormalAttackScript::MageNormalAttackScript(const MageNormalAttackScript& ref):PlayerNormalAttackScript(ref)
	{
	}
	void MageNormalAttackScript::Copy(Component* src)
	{
		MageNormalAttackScript* source = dynamic_cast<MageNormalAttackScript*>(src);
		if (source == nullptr)
			return;
	}
	void MageNormalAttackScript::Initialize()
	{
		PlayerNormalAttackScript::Initialize();

	

	}
	void MageNormalAttackScript::Update()
	{
		PlayerNormalAttackScript::Update();
	}
	void MageNormalAttackScript::LateUpdate()
	{
		PlayerNormalAttackScript::LateUpdate();
	}
	void MageNormalAttackScript::Render()
	{
		PlayerNormalAttackScript::Render();
	}
	void MageNormalAttackScript::Play()
	{
		PlayerNormalAttackScript::Play();
	}
	void MageNormalAttackScript::Exit()
	{
		PlayerNormalAttackScript::Exit();
	}
	void MageNormalAttackScript::Start()
	{
	}
	void MageNormalAttackScript::Middle()
	{
	}
	void MageNormalAttackScript::End()
	{
	}
}