#pragma once
#include "RokaEngine.h"
#include "RokaGraphicDevice_Dx11.h"
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

	CBUFFER(GridCB, CBSLOT_GRID)
	{
		Vector4 CameraPos;
		Vector2 CameraScale;
		Vector2 Resolution;
	};

	extern roka::graphics::ConstantBuffer* constantBuffer[(UINT)ECBType::End];
	extern Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerStates[(UINT)ESamplerType::End];
	extern Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizerStates[(UINT)ERSType::End];
	extern Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthstencilStates[(UINT)EDSType::End];
	extern Microsoft::WRL::ComPtr<ID3D11BlendState> blendStates[(UINT)EBSType::End];
	extern std::vector<std::shared_ptr<roka::Camera>> cameras;
	extern std::shared_ptr<roka::Camera> MainCamera;
	extern std::vector<DebugMesh> debugMeshs;

	void Initialize();
	void Render();
	void Release();
	void PushDebugMeshAttribute(DebugMesh mesh);
}
