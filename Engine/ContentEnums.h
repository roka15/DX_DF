#pragma once

namespace roka::enums
{
	enum class ECharacterClassType
	{
		None,
		Mage,
		End,
	};

	enum class EPlayerState
	{
		None,
		Idle,
		Walk,
		Run,
		NomalAtk,
		OnePlay,
		Jump,
		JumpHold,
		JumpRun,
		FallDown,
		Landing,
		Stun,
		Stagger,
		Down,
		Standing,
		Skill,
	
		
		End,
	};
	enum class EStunState
	{
		None,
		Stagger=1,
		Down=2,
		HardStagger=4,
		HardDown=8,
		End,
	};
	enum class EPlayerSkillType
	{
		None,
		NormalAtk,
		End,
	};
	enum class EAttackType
	{
		None,
		Straight,
		TargetPos,
		RandomPos,
		End,
	};
	enum class ESkillType
	{
		None,
		Buff,
		DeBuff,
		Attack,
		End,
	};
	
	enum class EAvatarParts
	{
		None,
		Weapon,
		Base,
		Face,
		Hair,
		Cap,
		Coat,
		Neck,
		Pants,
		Belt,
		Shoes,
		End,
	};
	
	enum class EPortalType
	{
		None,
		Direct,
		Select,
		End,
	};

	enum class EMapType
	{
		None,
		SeriaRoom,
		PlayTestScene,
		End,
	};
}