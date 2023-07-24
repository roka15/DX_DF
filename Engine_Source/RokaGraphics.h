#pragma once
#include <wrl.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <Shlwapi.h>
#include <wincodec.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib,"Shlwapi.lib")

#include "Enums.h"
#include "RokaMath.h"

#define CB_GETBINDSLOT(name) __CBUFFERBINDSLOT__##name##__
#define CBUFFER(name,slot) static const int CB_GETBINDSLOT(name)=slot; struct alignas(16) name

#define CBSLOT_TRANSFORM 0
#define CBSLOT_GRID 2
#define CBSLOT_ANIMATION 3

namespace roka::graphics
{
	enum class EShaderStage
	{
		VS,
		HS,
		DS,
		GS,
		PS,
		CS,
		End
	};
	enum class ECBType
	{
		Transform,
		Material,
		Grid,
		Animation,
		End
	};
	enum class ESamplerType
	{
		Point,
		Anisotropic,
		End,
	};
	enum class ERSType
	{
		SolidFront,
		SolidBack,
		SolidNone,
		WireFrameNone,
		End
	};
	enum class EDSType
	{
		Less,
		LessEqual,
		Greater,
		NoWirte,
		None,
		End
	};
	enum class EBSType
	{
		Default,
		AlphaBlend,
		OneOne,
		End
	};
	enum class ERenderMode
	{
		Opaque,
		CutOut,
		Transparent,
		End,
	};
	enum class EChannelType
	{
		C8,
		C16,
		C24,
		C32,
		None,
	};
	struct GpuBuffer
	{
		Microsoft::WRL::ComPtr<ID3D11Buffer> buffer;
		D3D11_BUFFER_DESC desc;
		GpuBuffer()
			: buffer(nullptr)
			, desc{}
		{

		}
		virtual ~GpuBuffer() = default;
	};
	struct DebugMesh
	{
		enums::EColliderType type;
		math::Vector3 position;
		math::Vector3 rotation;
		math::Vector3 scale;

		float radius;
		float duration;
		float time;
	};
}

