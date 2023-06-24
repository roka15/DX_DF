#include "Renderer.h"
#include "Resources.h"
#include "Texture.h"
#include "Material.h"
namespace roka::renderer
{
	using namespace roka::graphics;
	std::vector<Vertex> vertexs;
	std::vector<UINT> indexs;

	ConstantBuffer* constantBuffer[(UINT)ECBType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerStates[(UINT)ESamplerType::End];
	void SetupState()
	{
		// Input layout ���� ���� ������ �Ѱ�����Ѵ�.
		D3D11_INPUT_ELEMENT_DESC arrLayout[3] = {};

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

		arrLayout[2].AlignedByteOffset = 28;
		arrLayout[2].Format = DXGI_FORMAT_R32G32_FLOAT;
		arrLayout[2].InputSlot = 0;
		arrLayout[2].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayout[2].SemanticName = "TEXCOORD";
		arrLayout[2].SemanticIndex = 0;

		std::shared_ptr<Shader> shader = roka::Resources::Find<Shader>(L"TriangleShader");
		GetDevice()->CreateInputLayout(arrLayout, 3
			, shader->GetVSCode(), shader->GetInputLayoutAddressOf());

		shader = roka::Resources::Find<Shader>(L"SpriteShader");
		GetDevice()->CreateInputLayout(arrLayout, 3
			, shader->GetVSCode(), shader->GetInputLayoutAddressOf());

		//Sampler State
		D3D11_SAMPLER_DESC desc = {};
		desc.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		desc.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		desc.AddressW = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		desc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;

		GetDevice()->CreateSampler(&desc,samplerStates[(UINT)ESamplerType::Point].GetAddressOf());
		GetDevice()->BindSampler(EShaderStage::PS, 0, samplerStates[(UINT)ESamplerType::Point].GetAddressOf());
		desc.Filter = D3D11_FILTER_ANISOTROPIC;
		GetDevice()->CreateSampler(&desc, samplerStates[(UINT)ESamplerType::Anisotropic].GetAddressOf());
		GetDevice()->BindSampler(EShaderStage::PS, 1, samplerStates[(UINT)ESamplerType::Anisotropic].GetAddressOf());
	}
	void LoadBuffer()
	{
		std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
		mesh->CreateVertexBuffer(vertexs.data(), vertexs.size());
		mesh->CreateIndexBuffer(indexs.data(), indexs.size());
		Resources::Insert(L"RectMesh", mesh);

		//constant buffer
		constantBuffer[(UINT)ECBType::Transform] = new roka::graphics::ConstantBuffer(ECBType::Transform);
		constantBuffer[(UINT)ECBType::Transform]->Create(sizeof(TransformCB));
		/*Vector4 pos(0.0f, 0.0f, 0.0f, 1.0f);
		constantBuffer->SetData(&pos);
		constantBuffer->Bind(EShaderStage::VS);*/
	}
	void LoadShader()
	{
		std::shared_ptr<Shader> shader = std::make_shared<Shader>();
		shader->Create(EShaderStage::VS, L"TriangleVS.hlsl", "main");
		shader->Create(EShaderStage::PS, L"TrianglePS.hlsl", "main");
		roka::Resources::Insert(L"TriangleShader", shader);

		std::shared_ptr<Shader>  spriteShdaer = std::make_shared<Shader>();
		spriteShdaer->Create(EShaderStage::VS, L"SpriteVS.hlsl", "main");
		spriteShdaer->Create(EShaderStage::PS, L"SpritePS.hlsl", "main");
		roka::Resources::Insert(L"SpriteShader", spriteShdaer);
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"Link", L"..\\Resources\\Texture\\Link.png");
			std::shared_ptr<Material> spriteMaterial = std::make_shared<Material>();
			spriteMaterial->shader = spriteShdaer;
			spriteMaterial->texture = texture;
			Resources::Insert(L"SpriteMaterial", spriteMaterial);
		}
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"Smile", L"..\\Resources\\Texture\\Smile.png");
			std::shared_ptr<Material> spriteMaterial = std::make_shared<Material>();
			spriteMaterial->shader = spriteShdaer;
			spriteMaterial->texture = texture;
			Resources::Insert(L"SpriteMaterial02", spriteMaterial);
		}
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
		vertexs[0].uv = { 0.0f,1.0f};//uv ��ǥ ����� ��ĭ�� �ٷ��� ��ǥ�� �ٸ�.

		vertexs[1].pos = { -0.25f, +0.25f, 0.0f };
		vertexs[1].color = { 0.0f,1.0f,0.0f,1.0f };
		vertexs[1].uv = { 0.0f,0.0f };

		vertexs[2].pos = { +0.25f, -0.25f, 0.0f };
		vertexs[2].color = { 0.0f,0.0f,1.0f,1.0f };
		vertexs[2].uv = { 1.0f,1.0f };

		vertexs[3].pos = { +0.25f, +0.25f, 0.0f };
		vertexs[3].color = { 0.0f,1.0f,0.0f,1.0f };
		vertexs[3].uv = { 1.0f,0.0f };


		indexs.push_back(0);
		indexs.push_back(1);
		indexs.push_back(2);
		indexs.push_back(2);
		indexs.push_back(1);
		indexs.push_back(3);
		
		/*graphics::Texture* texture
			= Resources::Load<Texture>(L"Smile", L"..\\Resources\\Texture\\Smile.png");

		texture
			= Resources::Load<Texture>(L"Link", L"..\\Resources\\Texture\\Link.png");

		texture->BindShader(EShaderStage::PS, 0);*/
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
		for (ConstantBuffer* buff : constantBuffer)
		{
			if (buff == nullptr)
				continue;

			delete buff;
			buff = nullptr;
		}
	}
}
