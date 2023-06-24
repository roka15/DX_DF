#pragma once
#include <wrl.h>
#include <d3d11.h>
#include <d3dcompiler.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

#define CB_GETBINDSLOT(name) __CBUFFERBINDSLOT__##name##__
#define CBUFFER(name,slot) static const int CB_GETBINDSLOT(name)=slot; struct alignas(16) name

#define CBSLOT_TRANSFORM 0


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
	End
};
enum class ESamplerType
{
	Point,
	Anisotropic,
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