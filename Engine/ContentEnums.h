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