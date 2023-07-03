#pragma once
#include "RokaEngine.h"
#include "RokaGraphicDevice_Dx11.h"
#include "Mesh.h"
#include "Shader.h"
#include "ConstantBuffer.h"
#include "Camera.h"
using namespace roka::math;
using namespace roka::graphics;
namespace roka::renderer
{
	struct Vertex
	{
		Vector3 pos;
		Vector4 color;
		Vector2 uv;
	};

	CBUFFER(TransformCB, CBSLOT_TRANSFORM)
	{
		Matrix mWorld;
		Matrix mView;
		Matrix mProjection;
	};

	extern std::vector<Vertex> vertexs;
	extern std::vector<UINT> indexs;
	extern roka::graphics::ConstantBuffer* constantBuffer[(UINT)ECBType::End];
	extern Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerStates[(UINT)ESamplerType::End];
	extern Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizerStates[(UINT)ERSType::End];
	extern Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthstencilStates[(UINT)EDSType::End];
	extern Microsoft::WRL::ComPtr<ID3D11BlendState> blendStates[(UINT)EBSType::End];
	extern std::vector<roka::Camera*> cameras;

	void Initialize();
	void Render();
	void Release();
}
