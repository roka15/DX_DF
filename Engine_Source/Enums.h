#pragma once

namespace roka::enums
{
	enum class EComponentType
	{
		None,
		Transform,
		Particle,
		Image,
		MeshRenderer,
		Animator,
		Script,
		Camera,
		Collider,
		Rigidbody,
		Light,
		End,
	};
	enum class EScriptType
	{
		None,
		Camera,
		Grid,
        Move,
		TargetMove,
		Player,
		Monster,
		Avatar,
		Part,
		SkillBase,
		Weapon,
		HitBox,
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
		Light,
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
		Animation,
		ComputeShader,
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
	enum class ELightType
	{
		Directional,
		Point,
		Spot,
		End,
	};
}
