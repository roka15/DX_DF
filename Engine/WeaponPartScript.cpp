#include "WeaponPartScript.h"

#include "NPK.h"
#include "GameObject.h"
#include "Resources.h"
#include "Texture.h"
#include "RokaTime.h"
#include "Prefab.h"
#include "Object.h"
#include "AnimationObjectPool.h"

#include "Animator.h"
#include "MeshRenderer.h"

namespace roka
{
	WeaponPartScript::WeaponPartScript():PartScript(EScriptType::PartWeapon)
	{
	}
	WeaponPartScript::WeaponPartScript(const WeaponPartScript& ref):PartScript(ref),
		mNpkKey(ref.mNpkKey),
		mPackKey(ref.mPackKey)
	{
	}
	void WeaponPartScript::Copy(Component* src)
	{
		WeaponPartScript* source = dynamic_cast<WeaponPartScript*>(src);
		if (source == nullptr)
			return;
		mNpkKey = source->mNpkKey;
		mPackKey = source->mPackKey;
	}
	void WeaponPartScript::Initialize()
	{
		PartScript::Initialize();
	}
	void WeaponPartScript::Update()
	{
		PartScript::Update();
	}
	void WeaponPartScript::LateUpdate()
	{
		PartScript::LateUpdate();
	}
	void WeaponPartScript::Render()
	{
		PartScript::Render();
	}
	void WeaponPartScript::Idle()
	{
		PartScript::Idle();
		mSubObject.lock()->PlayAnimation(L"Idle",true);
	}
	void WeaponPartScript::Walk()
	{
		PartScript::Walk();
		mSubObject.lock()->PlayAnimation(L"Walk", true);
	}
	void WeaponPartScript::Run()
	{
		PartScript::Run();
		mSubObject.lock()->PlayAnimation(L"Run", true);
	}
	void WeaponPartScript::Jump()
	{
		PartScript::Jump();
		mSubObject.lock()->PlayAnimation(L"Jump", false);
	}
	void WeaponPartScript::Fall()
	{
		PartScript::Fall();
		mSubObject.lock()->PlayAnimation(L"Fall", false);
	}
	void WeaponPartScript::JumpDash()
	{
		PartScript::JumpDash();
		mSubObject.lock()->PlayAnimation(L"JumpDash", true);
	}
	void WeaponPartScript::JumpHold()
	{
		PartScript::JumpHold();
		mSubObject.lock()->PlayAnimation(L"JumpHold", false);
	}
	void WeaponPartScript::NormalAtk()
	{
		PartScript::NormalAtk();
		mSubObject.lock()->PlayAnimation(L"NormalAtk", true);
	}
	void WeaponPartScript::Stagger()
	{
		PartScript::Stagger();
		mSubObject.lock()->PlayAnimation(L"Stagger", false);
	}
	void WeaponPartScript::Down()
	{
		PartScript::Down();
		mSubObject.lock()->PlayAnimation(L"Down", false);
	}
	void WeaponPartScript::Standing()
	{
		PartScript::Standing();
		mSubObject.lock()->PlayAnimation(L"Standing", false);
	}
	void WeaponPartScript::Landing()
	{
		PartScript::Landing();
		mSubObject.lock()->PlayAnimation(L"Landing", false);
	}
	void WeaponPartScript::SetEvent()
	{
		std::shared_ptr<Animation> animation;
		std::shared_ptr<Animator> ani = owner->GetComponent<Animator>();
		animation = ani->FindAnimation(L"Down");
		{
			Animation::AnimationEvent TimeEvent = {};
			TimeEvent.mTime = 0.25f * 2;
			TimeEvent.mNormalFunc = std::bind(&WeaponPartScript::Stop, this);
		}
		ani->CompleteEvent(L"NormalAtk") = std::bind(&WeaponPartScript::NormalAtkCompleteEvent, this);
		ani->EndEvent(L"NormalAtk") = std::bind(&WeaponPartScript::NormalAtkEndEvent, this);
	}
	void WeaponPartScript::Create(std::wstring npk, std::wstring pack)
	{
		mPartType = EAvatarParts::Weapon;
		mNpkKey = npk;
		mPackKey = pack;
		std::shared_ptr<NPK> weapon_npk = Resources::Find<NPK>(npk);
		if (weapon_npk == nullptr)
			return;

		std::shared_ptr<Animator> ani = owner->GetComponent<Animator>();
		float speed = 0.1f;

		std::shared_ptr<Texture> texture1 = weapon_npk->CreateAtlas(pack, 0, 22, L"mg_broom7200d_01");
		ani->Create(texture1,L"Idle", 0, 10, 0.2f);
		ani->Create(texture1, L"Run", 0, 10, 0.05f);
		ani->Create(texture1, L"Jump", 11, 21, speed);

		std::shared_ptr<Texture> texture2 = weapon_npk->CreateAtlas(pack, 109, 136, L"mg_broom7200d_02");
		ani->Create(texture2, L"NormalAtk", 0, 19, 0.05f);
		ani->Create(texture2, L"Down", 21, 26, 0.25f);
		
		std::shared_ptr<Texture> texture3 = weapon_npk->CreateAtlas(pack, 178, 180, L"mg_broom7200d_03");
		ani->Create(texture3, L"JumpDash", 0, 2, speed);
	}
	void WeaponPartScript::CreateSubObject()
	{
		std::shared_ptr<GameObject> subObject = manager::ObjectPoolManager<AnimationObjectPool,GameObject>::GetInstance()->GetPool(L"AniObject")->Spawn();
		std::shared_ptr<Animator> sub_ani = subObject->GetComponent<Animator>();
		std::wstring npk = mNpkKey;
		std::wstring pack = mPackKey;

		std::shared_ptr<NPK> weapon_npk = Resources::Find<NPK>(npk);
		if (weapon_npk == nullptr)
			return;

		int index = mPackKey.rfind(L".img");
		pack = pack.substr(0, index-1);
		pack += L"c.img";

		std::shared_ptr<Texture> texture1 = weapon_npk->CreateAtlas(pack, 109, 136, L"mg_broom7200c_02");
		sub_ani->Create(texture1, L"NormalAtk", 0, 19, 0.05f);

		owner->AddChild(subObject);
		mSubObject = sub_ani;
	}
	void WeaponPartScript::NormalAtkStartEvent()
	{
		std::shared_ptr<Animator> ani = owner->GetComponent<Animator>();
		std::shared_ptr<Animator> subAni = mSubObject.lock();
		ani->CompleteStart();
		subAni->CompleteStart();
	}
	void WeaponPartScript::NormalAtkCompleteEvent()
	{
		/*std::shared_ptr<Animator> ani = owner->GetComponent<Animator>();
		std::shared_ptr<Animator> subAni = mSubObject.lock();
		ani->CompleteStop();
		subAni->CompleteStop();
		Time::CallBackTimerInfo callBack = {};
		callBack.endTime = 0.045f;
		Time::RequestEvent(callBack, std::bind(&WeaponPartScript::NormalAtkStartEvent,this));*/
	}
	void WeaponPartScript::NormalAtkEndEvent()
	{
		mSubObject.lock()->ActiveAnimationNull();
	}
	void WeaponPartScript::Right()
	{
		PartScript::Right();
		std::shared_ptr<GameObject> subObj = mSubObject.lock()->owner->GetSharedPtr();
		std::shared_ptr<MeshRenderer> mr = subObj->GetComponent<MeshRenderer>();
		mr->material->shader = Resources::Find<Shader>(L"AnimationShader");
	}
	void WeaponPartScript::Left()
	{
		PartScript::Left();
		std::shared_ptr<GameObject> subObj = mSubObject.lock()->owner->GetSharedPtr();
		std::shared_ptr<MeshRenderer> mr = subObj->GetComponent<MeshRenderer>();
		mr->material->shader = Resources::Find<Shader>(L"VerticalInverterAnimationShader");
	}
	void WeaponPartScript::Stop()
	{
		std::shared_ptr<Animator> ani = owner->GetComponent<Animator>();
		ani->Stop();
		std::shared_ptr<Animator> subAni = mSubObject.lock();
		subAni->Stop();
	}
	void WeaponPartScript::Start()
	{
		std::shared_ptr<Animator> ani = owner->GetComponent<Animator>();
		ani->Play();
		std::shared_ptr<Animator> subAni = mSubObject.lock();
		subAni->Play();
	}
}