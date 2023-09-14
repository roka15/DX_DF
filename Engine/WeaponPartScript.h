#pragma once
#include "PartScript.h"
namespace roka
{
	class WeaponPartScript :
		public PartScript
	{
	protected:
		WeaponPartScript();
		WeaponPartScript(const WeaponPartScript& ref);
		virtual void Copy(Component* src);
	public:
		virtual ~WeaponPartScript() {};

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void Idle()override;
		virtual void Walk()override;
		virtual void Run()override;
		virtual void Jump()override;
		virtual void Fall()override;
		virtual void JumpDash()override;
		virtual void JumpHold()override;
		virtual void NormalAtk()override;
		virtual void Stagger()override;
		virtual void Down()override;
		virtual void Standing()override;
		virtual void Landing()override;

		virtual void SetEvent()override;
		virtual void Create(std::wstring npk, std::wstring pack)override;
		virtual void CreateSubObject();

		virtual void NormalAtkStartEvent();
		virtual void NormalAtkCompleteEvent();
		virtual void NormalAtkEndEvent();

		virtual void Stop();
		virtual void Start();
	private:
		friend class FactoryBase;
		friend class ScriptFactory;
	protected:
		std::wstring mNpkKey;
		std::wstring mPackKey;
		std::weak_ptr<class Animator> mSubObject;
	};

}

