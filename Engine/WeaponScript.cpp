#include "WeaponScript.h"
#include "GameObject.h"

#include "Animator.h"
roka::WeaponScript::WeaponScript():PartScript()
{
}

roka::WeaponScript::WeaponScript(const WeaponScript& ref):PartScript(ref)
{
}

void roka::WeaponScript::Copy(Component* src)
{
	Script::Copy(src);
}

roka::WeaponScript::~WeaponScript()
{
}

void roka::WeaponScript::Initialize()
{
	PartScript::Initialize();
}

void roka::WeaponScript::Update()
{
}

void roka::WeaponScript::LateUpdate()
{
}

void roka::WeaponScript::Render()
{
}

void roka::WeaponScript::PlayPartMotion(std::wstring name, bool flag)
{
	std::shared_ptr<Animator> ani = owner->GetComponent<Animator>();
	ani->PlayAnimation(name, flag);

	ani = mSubPart.lock()->GetComponent<Animator>();
	ani->PlayAnimation(name, flag);
}

void roka::WeaponScript::CreateAni(std::wstring npk_name, std::wstring pack_name, std::wstring set_name, UINT start, UINT end, float duration)
{
	size_t pos = pack_name.find(L".img", 0);
	if (pos == std::wstring::npos)
	{
		return;
	}
	std::wstring weapon_key1 = pack_name;
	pos = pos - 1;
	pack_name.erase(pos);
	pack_name.insert(pos, L"c");
	std::wstring weapon_key2 = pack_name;

	PartScript::CreateAni(npk_name, weapon_key1, set_name, start, end, duration);

	std::shared_ptr<Animator> ani = mSubPart.lock()->GetComponent<Animator>();
	ani->Create(npk_name, weapon_key2, set_name, start, end, duration);
}
