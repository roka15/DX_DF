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
		Cursor,
		ScrollRect,
		GroupLayout,
		GridLayout,
		AudioSource,
		AudioListener,
		Text,
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
		PartWeapon,
		PartSkin,
		Weapon,
		Monster,
		NormalMonster,
		SpiderMonster,
		NamedMonster,
		TairangMonster,
		Warning,
		ChangeSizeOverTime,
		Gauge,
		Slot,
		Item,
		End,
	};

	enum class ELayerType
	{
		Grid,
		BackObject,
		Item,
		Skill,
		Player,
		Monster,
		FrontObject,
		Light,
		Portal,
		Raycast,
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
		AudioClip,
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
	enum class EAlphaType
	{
		None,
		FadeIn,
		FadeOut,
		End,
	};
	enum class EApplicationType
	{
		Main,
		TileTool,
		End,
	};
	enum class GaugeType
	{
		None,
		Virtical,
		Horizontal,
		End,
	};
	enum class EUIType
	{
		None,
		Slot,
		Item,
		End,
	};
}
