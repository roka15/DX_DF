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
#define CBSLOT_MATERIAL 1
#define CBSLOT_GRID 2
#define CBSLOT_ANIMATION 3
#define CBSLOT_GAUGE 4


namespace roka
{
	class GameObject;
}
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
		Atlas,
		Gauge,
		End
	};
	enum class ESamplerType
	{
		Linear,
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
	enum class ESRVType
	{
		None,
		End,
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
	class DebugMesh
	{
	public:
		enums::EColliderType type;
		math::Vector3 position;
		math::Vector3 rotation;
		math::Vector3 scale;

		std::shared_ptr<GameObject> parent;

		float radius;
		float duration;
		float time;
		math::Vector4 color;
		RECT viewPortRect;
	};
	struct LightAttribute
	{
		math::Vector4 color;
		math::Vector4 position;
		math::Vector4 direction;

		enums::ELightType type;
		float radius;
		float angle;
		int pad;
	};
}

