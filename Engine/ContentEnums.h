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
		FallDown,
		NomalAtk,
		OnePlay,
		Jump,
		JumpHold,
		JumpRun,
		Stun,
		Standing,
		Skill,
		
		End,
	};
	enum class EStunState
	{
		None,
		Stagger,
		Down,
		HardStagger,
		HardDown,
		End,
	};

	enum class EAvatarParts
	{
		None,
		Base,
		Face,
		Hair,
		Cap,
		Coat,
		Neck,
		Pants,
		Belt,
		Shoes,
		Weapon,
		End,
	};
}