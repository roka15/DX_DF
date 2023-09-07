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
		Avatar,
		Part,
		SkillBase,
		SkillLayser,
		SkillSpiderLayser,
		SkillDelayCollider,
		SkillTairangType01,
		SkillMonster,
		Weapon,
		HitBox,
		Monster,
		NormalMonster,
		SpiderMonster,
		NamedMonster,
		TairangMonster,
		Portal,
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
		Skill,
		Player,
		Monster,
		FrontObject,
		Light,
		Portal,
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
