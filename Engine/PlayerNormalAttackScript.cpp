#include "PlayerNormalAttackScript.h"

#include "Input.h"
#include "RokaTime.h"
namespace roka
{
	PlayerNormalAttackScript::PlayerNormalAttackScript():SkillScript(EScriptType::SkillPlayerNormalAtk),
		mConditionSec(0.5)
	{
		mStunType = EStunState::Stagger;
		mAtkIndex = -1;
		mKeyDownTime = 0.0;
	}
	PlayerNormalAttackScript::PlayerNormalAttackScript(EScriptType type):SkillScript(type),
		mConditionSec(0.5)
	{
		mStunType = EStunState::Stagger;
		mAtkIndex = -1;
		mKeyDownTime = 0.0;
	}
	PlayerNormalAttackScript::PlayerNormalAttackScript(const PlayerNormalAttackScript& ref):SkillScript(ref),
		mConditionSec(0.5)
	{
		mStunType = EStunState::Stagger;
		mAtkIndex = -1;
		mKeyDownTime = 0.0;
	}
	void PlayerNormalAttackScript::Copy(Component* src)
	{
		PlayerNormalAttackScript* source = dynamic_cast<PlayerNormalAttackScript*>(src);
		if (source == nullptr)
			return;
		mStunType = EStunState::Stagger;
		mAtkIndex = -1;
		mKeyDownTime = 0.0;
	}
	void PlayerNormalAttackScript::Initialize()
	{
		SkillScript::Initialize();
	}
	void PlayerNormalAttackScript::Update()
	{
		SkillScript::Update();
		mCurTime = Time::DeltaTime();
		if (mAtkIndex != -1)
		{
			if (Input::GetKeyUp(EKeyCode::X))
			{
				mKeyDownTime = mCurTime;
			}
			if (Input::GetKeyDown(EKeyCode::X))
			{
				if (mCurTime - mKeyDownTime > mConditionSec)
				{
					mAtkIndex = 0;
				}
			}
		}
	}
	void PlayerNormalAttackScript::LateUpdate()
	{
		SkillScript::LateUpdate();
	}
	void PlayerNormalAttackScript::Render()
	{
		SkillScript::Render();
	}
	void PlayerNormalAttackScript::Play()
	{
		SkillScript::Play();
		mAtkIndex = 0;
		mAtkFunc[mAtkIndex]();
	}
	void PlayerNormalAttackScript::Exit()
	{
		SkillScript::Exit();
		mAtkIndex = -1;
	}
}