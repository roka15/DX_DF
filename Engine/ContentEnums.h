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
		Nonne,
		Idle,
		Walk,
		Run,
		FallDown,
		NomalAtk,
		OnePlay,
		Jump,
		JumpHold,
		JumpRun,
		Skill,
		
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