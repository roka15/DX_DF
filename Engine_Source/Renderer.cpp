#include "Renderer.h"

namespace roka::renderer
{
	std::vector<Vertex> vertexs;
	std::vector<UINT> indexs;

	Shader* shader = nullptr;
	Mesh* mesh = nullptr;
	roka::graphics::ConstantBuffer* constantBuffer = nullptr;

	void SetupState()
	{
		// Input layout ���� ���� ������ �Ѱ�����Ѵ�.
		D3D11_INPUT_ELEMENT_DESC arrLayout[2] = {};

		//ù��° ��� ���� ����(Vertex)
		arrLayout[0].AlignedByteOffset = 0; // ���� offet
		arrLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT; // float3
		arrLayout[0].InputSlot = 0;//��ϵ� vertex buffer / index buffer�� ���� ������ �� ���° buffer�� �� ������.
		arrLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayout[0].SemanticName = "POSITION";//hlsl �ĺ�
		arrLayout[0].SemanticIndex = 0;//������ semantic�̸��� ���� �Է°��� ������ ���� index
		//�ι�° ��� ���� ����(Color)
		arrLayout[1].AlignedByteOffset = 12;// ���� offset
		arrLayout[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;//float4
		arrLayout[1].InputSlot = 0;
		arrLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayout[1].SemanticName = "COLOR";
		arrLayout[1].SemanticIndex = 0;

		roka::graphics::GetDevice()->CreateInputLayout(arrLayout, 2
			, shader->GetVSCode(), shader->GetInputLayoutAddressOf());
	}
	void LoadBuffer()
	{
		mesh = new Mesh();
		mesh->CreateVertexBuffer(vertexs.data(), vertexs.size());
		mesh->CreateIndexBuffer(indexs.data(), indexs.size());

		//constant buffer
		constantBuffer = new roka::graphics::ConstantBuffer(ECBType::Transform);
		constantBuffer->Create(sizeof(Vector4));
		Vector4 pos(0.0f, 0.0f, 0.0f, 1.0f);
		constantBuffer->SetData(&pos);
		constantBuffer->Bind(EShaderStage::VS);
	}
	void LoadShader()
	{
		shader = new Shader();
		shader->Create(EShaderStage::VS, L"TriangleVS.hlsl", "main");
		shader->Create(EShaderStage::PS, L"TrianglePS.hlsl", "main");
	}
	void Initialize()
	{
		/* �ﰢ��
		vertexs[0].pos = {0.0f,0.5f,0.0f};
		vertexs[0].color = { 1.0f,0.0f,0.0f,1.0f };
		vertexs[1].pos = { 0.5f,-0.5f,0.0f };
		vertexs[1].color = { 0.0f,1.0f,0.0f,1.0f };
		vertexs[2].pos = { -0.5f,-0.5f,0.0f };
		vertexs[2].color = { 0.0f,0.0f,1.0f,1.0f };
		*/
		// �ε��� ���� ���� https://koreanfoodie.me/727

		/* �簢��*/
		vertexs.resize(4);

		vertexs[0].pos = { -0.25f, -0.25f, 0.0f };
		vertexs[0].color = { 1.0f,0.0f,0.0f,1.0f };
		vertexs[1].pos = { -0.25f, +0.25f, 0.0f };
		vertexs[1].color = { 0.0f,1.0f,0.0f,1.0f };
		vertexs[2].pos = { +0.25f, -0.25f, 0.0f };
		vertexs[2].color = { 0.0f,0.0f,1.0f,1.0f };
		vertexs[3].pos = { +0.25f, +0.25f, 0.0f };
		vertexs[3].color = { 0.0f,1.0f,0.0f,1.0f };


		indexs.push_back(0);
		indexs.push_back(1);
		indexs.push_back(2);
		indexs.push_back(2);
		indexs.push_back(1);
		indexs.push_back(3);
		

		/* ������

		vertexs.resize(4);

		vertexs[0].pos = { 0.0f, 0.5f, 0.0f };
		vertexs[0].color = { 1.0f,0.0f,0.0f,1.0f };
		vertexs[1].pos = { 0.5f, 0.0f, 0.0f };
		vertexs[1].color = { 0.0f,1.0f,0.0f,1.0f };
		vertexs[2].pos = { -0.5f, 0.0f, 0.0f };
		vertexs[2].color = { 0.0f,0.0f,1.0f,1.0f };
		vertexs[3].pos = { 0.0f, -0.5f, 0.0f };
		vertexs[3].color = { 0.0f,1.0f,0.0f,1.0f };


		indexs.push_back(0);
		indexs.push_back(1);
		indexs.push_back(2);
		indexs.push_back(2);
		indexs.push_back(1);
		indexs.push_back(3);
	   */

	   /* ��ٸ� ��
	   vertexs.resize(5);

	   vertexs[0].pos = { -0.5f, -0.5f, 0.0f };
	   vertexs[0].color = { 1.0f,0.0f,0.0f,1.0f };
	   vertexs[1].pos = { -0.25f, 0.5f, 0.0f };
	   vertexs[1].color = { 0.0f,1.0f,0.0f,1.0f };
	   vertexs[2].pos = { 0.0f, -0.5f, 0.0f };
	   vertexs[2].color = { 0.0f,0.0f,1.0f,1.0f };
	   vertexs[3].pos = { 0.25f, 0.5f, 0.0f };
	   vertexs[3].color = { 0.0f,1.0f,0.0f,1.0f };
	   vertexs[4].pos = { 0.5f, -0.5f, 0.0f };
	   vertexs[4].color = { 1.0f,0.0f,0.0f,1.0f };

	   indexs.push_back(0);
	   indexs.push_back(1);
	   indexs.push_back(2);
	   indexs.push_back(2);
	   indexs.push_back(1);
	   indexs.push_back(3);
	   indexs.push_back(2);
	   indexs.push_back(3);
	   indexs.push_back(4);
	   */
	   /* ���׶��

		float radius = 0.1f;
		float sin = 0.0f;
		float cos = 0.0f;

		Vertex center = {};
		center.pos.x = 0.0f;
		center.pos.y = 0.0f;
		center.color = { 1.0f,0.0f,1.0f,1.0f };
		vertexs.push_back(center);

		Vertex v = {};
	
		//360 = 2pi
		for (int i = 0; i < 360; i++)
		{
			if (i > 0)
			{
				if (i == 359)
				{
					indexs.push_back(0);
					indexs.push_back(1);
					indexs.push_back(359);
				}
				else
				{
					indexs.push_back(0);
					indexs.push_back(i + 1);
					indexs.push_back(i);
				}
			}
			
			v.pos.x = center.pos.x + radius * std::cosf(Deg2Rad((float)i))/2.0f;
			v.pos.y = center.pos.y + radius * std::sinf(Deg2Rad((float)i));
			v.color = { 1.0f,0.0f,1.0f,1.0f };
			vertexs.push_back(v);
		}
       */
		
 

		
		
		LoadBuffer();
		LoadShader();
		SetupState();
	}
	void Release()
	{
		delete mesh;
		delete shader;
		delete constantBuffer;
	}
}
