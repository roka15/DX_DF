#include "Renderer.h"

namespace roka::renderer
{
	Vertex vertexs[3] = {};
	ID3D11Buffer* triangleBuffer = nullptr;
	ID3DBlob* errorBlob = nullptr;
	ID3DBlob* triangleVSBlob = nullptr;
	ID3D11VertexShader* triangleVSShader = nullptr;
	ID3DBlob* trianglePSBlob = nullptr;
	ID3D11PixelShader* trianglePSShader = nullptr;

	void SetupState()
	{

	}
	void LoadBuffer()
	{
		D3D11_BUFFER_DESC triangleDesc = {};
		triangleDesc.ByteWidth = sizeof(Vertex) * 3;
		triangleDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
		triangleDesc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
		triangleDesc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;

		D3D11_SUBRESOURCE_DATA data;
		data.pSysMem = vertexs;
		roka::graphics::GetDevice()->CreateBuffer(&triangleBuffer, &triangleDesc, &data);
	}
	void LoadShader()
	{
		roka::graphics::GetDevice()->CreateShader();
	}
	void Initialize()
	{
		vertexs[0].pos = {0.0f,0.5f,1.0f};
		vertexs[0].color = { 1.0f,0.0f,0.0f,1.0f };
		vertexs[1].pos = { 0.5f,-0.5f,1.0f };
		vertexs[1].color = { 0.0f,1.0f,0.0f,1.0f };
		vertexs[2].pos = { -0.5f,-0.5f,1.0f };
		vertexs[2].color = { 0.0f,0.0f,1.0f,1.0f };

		SetupState();
		LoadBuffer();
		LoadShader();
	}
}
