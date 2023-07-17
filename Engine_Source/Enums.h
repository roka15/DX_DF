#pragma once

namespace roka::enums
{
	enum class EComponentType
	{
		None,
		Transform,
		Particle,
		MeshRenderer,
		Script,
		Camera,
		Image,
		Collider,
		End,
	};
	enum class EScriptType
	{
		None,
		Camera,
		Grid,
        Move,
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
		Grid,
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
	enum class EFactoryType
	{
		Component,
		Script,
		End,
	};
	enum class EColliderType
	{
		Rect,
		Circle,
		Sphere,
		Cube,
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
