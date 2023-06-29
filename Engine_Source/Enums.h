#pragma once

namespace roka::enums
{
	enum class EComponentType
	{
		None,
		Transform,
		Mesh,
		Particle,
		MeshRenderer,
		Script,
		Camera,
		End,
	};

	enum class ESceneType
	{
		DefaultVillage,
		AnotherVillage,
		Dungeon,
		End,
	};
	enum class ELayerType
	{
		BackObject,
		Player,
		Monster,
		FrontObject,
		UI,
		End,
	};
	
	enum class EResourceType
	{
		Mesh,
		Shader,
		Material,
		Texture,
		NPK,
		End,
	};

	enum class EDir4Type
	{
		LEFT,
		RIGHT,
		UP,
		DOWN
	};
}
