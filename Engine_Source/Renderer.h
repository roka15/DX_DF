#pragma once
#include "RokaEngine.h"
#include "RokaGraphicDevice_Dx11.h"

using namespace roka::math;
namespace roka::renderer
{
	struct Vertex
	{
		Vector3 pos;
		Vector4 color;
	};

	extern std::vector<Vertex> vertexs;
	extern std::vector<UINT> indexs;
	extern ID3D11InputLayout* triangleLayout;
	extern ID3D11Buffer* triangleBuffer;
	extern ID3D11Buffer* indexBuffer;
	extern ID3D11Buffer* constantBuffer;
	extern ID3DBlob* errorBlob;
	extern ID3DBlob* triangleVSBlob;
	extern ID3D11VertexShader* triangleVSShader;
	extern ID3DBlob* trianglePSBlob;
	extern ID3D11PixelShader* trianglePSShader;

	void Initialize();
}
