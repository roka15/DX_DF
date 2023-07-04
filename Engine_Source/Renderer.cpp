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

	Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizerStates[(UINT)ERSType::End];
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthstencilStates[(UINT)EDSType::End];
	Microsoft::WRL::ComPtr<ID3D11BlendState> blendStates[(UINT)EBSType::End];

	std::vector<roka::Camera*> cameras = {};
	void SetupState()
	{
#pragma region InputLayout
		// Input layout 정점 구조 정보를 넘겨줘야한다.
		D3D11_INPUT_ELEMENT_DESC arrLayout[3] = {};

		//첫번째 요소 정보 정의(Vertex)
		arrLayout[0].AlignedByteOffset = 0; // 시작 offet
		arrLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT; // float3
		arrLayout[0].InputSlot = 0;//등록된 vertex buffer / index buffer가 여럿 존재할 때 몇번째 buffer를 쓸 것인지.
		arrLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayout[0].SemanticName = "POSITION";//hlsl 식별
		arrLayout[0].SemanticIndex = 0;//동일한 semantic이름을 가진 입력값의 구분을 위한 index
		//두번째 요소 정보 정의(Color)
		arrLayout[1].AlignedByteOffset = 12;// 시작 offset
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
#pragma endregion
#pragma region SamplerState
		//Sampler State
		D3D11_SAMPLER_DESC Samplerdesc = {};
		Samplerdesc.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		Samplerdesc.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		Samplerdesc.AddressW = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		Samplerdesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;

		GetDevice()->CreateSamplerState(&Samplerdesc, samplerStates[(UINT)ESamplerType::Point].GetAddressOf());
		GetDevice()->BindSampler(EShaderStage::PS, 0, samplerStates[(UINT)ESamplerType::Point].GetAddressOf());
		Samplerdesc.Filter = D3D11_FILTER_ANISOTROPIC;
		GetDevice()->CreateSamplerState(&Samplerdesc, samplerStates[(UINT)ESamplerType::Anisotropic].GetAddressOf());
		GetDevice()->BindSampler(EShaderStage::PS, 1, samplerStates[(UINT)ESamplerType::Anisotropic].GetAddressOf());
#pragma endregion
#pragma region RasterizerState
		D3D11_RASTERIZER_DESC RasterDesc = {};
		RasterDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_FRONT;
		RasterDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
		GetDevice()->CreateRasterizerState(&RasterDesc, rasterizerStates[(UINT)ERSType::SolidFront].GetAddressOf());
		
		RasterDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
		RasterDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_BACK;
		GetDevice()->CreateRasterizerState(&RasterDesc, rasterizerStates[(UINT)ERSType::SolidBack].GetAddressOf());

		RasterDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
		RasterDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
		GetDevice()->CreateRasterizerState(&RasterDesc, rasterizerStates[(UINT)ERSType::SolidNone].GetAddressOf());
		
		RasterDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
		RasterDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_WIREFRAME;
		GetDevice()->CreateRasterizerState(&RasterDesc, rasterizerStates[(UINT)ERSType::WireFrameNone].GetAddressOf());

#pragma endregion 
#pragma region DepthStencilState
		D3D11_DEPTH_STENCIL_DESC DepthStencilDesc = {};
		DepthStencilDesc.DepthEnable = true;
		DepthStencilDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS;
		DepthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
		DepthStencilDesc.StencilEnable = false;
		GetDevice()->CreateDepthStencilState(&DepthStencilDesc, depthstencilStates[(UINT)EDSType::Less].GetAddressOf());
		
		DepthStencilDesc.DepthEnable = true;
		DepthStencilDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS_EQUAL;
		DepthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
		DepthStencilDesc.StencilEnable = false;

		GetDevice()->CreateDepthStencilState(&DepthStencilDesc, depthstencilStates[(UINT)EDSType::LessEqual].GetAddressOf());

		DepthStencilDesc.DepthEnable = true;
		DepthStencilDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_GREATER;
		DepthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
		DepthStencilDesc.StencilEnable = false;
		GetDevice()->CreateDepthStencilState(&DepthStencilDesc, depthstencilStates[(UINT)EDSType::Greater].GetAddressOf());
		
		DepthStencilDesc.DepthEnable = true;
		DepthStencilDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS;
		DepthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ZERO;
		DepthStencilDesc.StencilEnable = false;
		GetDevice()->CreateDepthStencilState(&DepthStencilDesc, depthstencilStates[(UINT)EDSType::NoWirte].GetAddressOf());

		DepthStencilDesc.DepthEnable = false;
		DepthStencilDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS;
		DepthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ZERO;
		DepthStencilDesc.StencilEnable = false;

		GetDevice()->CreateDepthStencilState(&DepthStencilDesc, depthstencilStates[(UINT)EDSType::None].GetAddressOf());
#pragma endregion
#pragma region Blend State
		D3D11_BLEND_DESC BlendDesc = {};
		blendStates[(UINT)EBSType::Default] = nullptr;

		//alpha blend
		BlendDesc.AlphaToCoverageEnable = false;
		BlendDesc.IndependentBlendEnable = false;
		BlendDesc.RenderTarget[0].BlendEnable = true;
		BlendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		BlendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		BlendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		BlendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		BlendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		BlendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		BlendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

		GetDevice()->CreateBlendState(&BlendDesc, blendStates[(UINT)EBSType::AlphaBlend].GetAddressOf());

		BlendDesc.AlphaToCoverageEnable = false;
		BlendDesc.IndependentBlendEnable = false;
		BlendDesc.RenderTarget[0].BlendEnable = true;
		BlendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		BlendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
		BlendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
		BlendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

		GetDevice()->CreateBlendState(&BlendDesc, blendStates[(UINT)EBSType::OneOne].GetAddressOf());
#pragma endregion
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
			{
				std::shared_ptr<Material> spriteMaterial = std::make_shared<Material>();
				spriteMaterial->shader = spriteShdaer;
				Resources::Insert(L"SpriteMaterial", spriteMaterial);
			}
#pragma region seria room material
			{
				std::shared_ptr<Material> spriteMaterial = std::make_shared<Material>();
				spriteMaterial->shader = spriteShdaer;
				Resources::Insert(L"BGMaterial", spriteMaterial);
			}
			
			{
				std::shared_ptr<Material> spriteMaterial = std::make_shared<Material>();
				spriteMaterial->shader = spriteShdaer;
				Resources::Insert(L"FrontObjMaterial01", spriteMaterial);
			}
			{
				std::shared_ptr<Material> spriteMaterial = std::make_shared<Material>();
				spriteMaterial->shader = spriteShdaer;
				Resources::Insert(L"FrontObjMaterial02", spriteMaterial);
			}

			{
				std::shared_ptr<Material> spriteMaterial = std::make_shared<Material>();
				spriteMaterial->shader = spriteShdaer;
				Resources::Insert(L"FlowerMaterial01", spriteMaterial);
			}
			{
				std::shared_ptr<Material> spriteMaterial = std::make_shared<Material>();
				spriteMaterial->shader = spriteShdaer;
				Resources::Insert(L"FlowerMaterial02", spriteMaterial);
			}
			{
				std::shared_ptr<Material> spriteMaterial = std::make_shared<Material>();
				spriteMaterial->shader = spriteShdaer;
				Resources::Insert(L"LeafMaterial01", spriteMaterial);
			}
			{
				std::shared_ptr<Material> spriteMaterial = std::make_shared<Material>();
				spriteMaterial->shader = spriteShdaer;
				Resources::Insert(L"LeafMaterial02", spriteMaterial);
			}
			{
				std::shared_ptr<Material> spriteMaterial = std::make_shared<Material>();
				spriteMaterial->shader = spriteShdaer;
				Resources::Insert(L"LeafMaterial03", spriteMaterial);
			}
			{
				std::shared_ptr<Material> spriteMaterial = std::make_shared<Material>();
				spriteMaterial->shader = spriteShdaer;
				Resources::Insert(L"GateMaterial01", spriteMaterial);
			}
			{
				std::shared_ptr<Material> spriteMaterial = std::make_shared<Material>();
				spriteMaterial->shader = spriteShdaer;
				Resources::Insert(L"GateMaterial02", spriteMaterial);
			}
			{
				std::shared_ptr<Texture> texture
					= Resources::Load<Texture>(L"HudBase", L"..\\Resources\\Texture\\hudbase.png");
				std::shared_ptr<Material> spriteMaterial = std::make_shared<Material>();
				spriteMaterial->shader = spriteShdaer;
				spriteMaterial->texture = texture;
				Resources::Insert(L"HudBaseMaterial01", spriteMaterial);
			}
			{
				std::shared_ptr<Texture> texture
					= Resources::Load<Texture>(L"HudBase2", L"..\\Resources\\Texture\\hudbase2.png");
				std::shared_ptr<Material> spriteMaterial = std::make_shared<Material>();
				spriteMaterial->shader = spriteShdaer;
				spriteMaterial->texture = texture;
				Resources::Insert(L"HudBaseMaterial02", spriteMaterial);
			}
			{
				std::shared_ptr<Texture> texture
					= Resources::Load<Texture>(L"HPBase", L"..\\Resources\\Texture\\hpui.png");
				std::shared_ptr<Material> spriteMaterial = std::make_shared<Material>();
				spriteMaterial->shader = spriteShdaer;
				spriteMaterial->texture = texture;
				Resources::Insert(L"HPBaseMaterial01", spriteMaterial);
			}
			{
				std::shared_ptr<Texture> texture
					= Resources::Load<Texture>(L"MPBase", L"..\\Resources\\Texture\\mpui.png");
				std::shared_ptr<Material> spriteMaterial = std::make_shared<Material>();
				spriteMaterial->shader = spriteShdaer;
				spriteMaterial->texture = texture;
				Resources::Insert(L"MPBaseMaterial01", spriteMaterial);
			}
			{
				std::shared_ptr<Texture> texture
					= Resources::Load<Texture>(L"HPFilter", L"..\\Resources\\Texture\\hpfilterui.png");
				std::shared_ptr<Material> spriteMaterial = std::make_shared<Material>();
				spriteMaterial->shader = spriteShdaer;
				spriteMaterial->texture = texture;
				Resources::Insert(L"HPFilterMaterial01", spriteMaterial);
			}
			{
				std::shared_ptr<Texture> texture
					= Resources::Load<Texture>(L"MPFilter", L"..\\Resources\\Texture\\mpfilterui.png");
				std::shared_ptr<Material> spriteMaterial = std::make_shared<Material>();
				spriteMaterial->shader = spriteShdaer;
				spriteMaterial->texture = texture;
				Resources::Insert(L"MPFilterMaterial01", spriteMaterial);
			}
			{
				std::shared_ptr<Texture> texture
					= Resources::Load<Texture>(L"SkillQuickSlot", L"..\\Resources\\Texture\\skillslot.png");
				std::shared_ptr<Material> spriteMaterial = std::make_shared<Material>();
				spriteMaterial->shader = spriteShdaer;
				spriteMaterial->texture = texture;
				Resources::Insert(L"SkillQuickSlotMaterial01", spriteMaterial);
			}
			{
				std::shared_ptr<Texture> texture
					= Resources::Load<Texture>(L"ExpBar", L"..\\Resources\\Texture\\expbar.png");
				std::shared_ptr<Material> spriteMaterial = std::make_shared<Material>();
				spriteMaterial->shader = spriteShdaer;
				spriteMaterial->texture = texture;
				Resources::Insert(L"ExpBarMaterial01", spriteMaterial);
			}
			{
				std::shared_ptr<Texture> texture
					= Resources::Load<Texture>(L"MoreSkillBtn", L"..\\Resources\\Texture\\moreskill.png");
				std::shared_ptr<Material> spriteMaterial = std::make_shared<Material>();
				spriteMaterial->shader = spriteShdaer;
				spriteMaterial->texture = texture;
				Resources::Insert(L"MoreSkillBtnMaterial01", spriteMaterial);
			}
			{
				std::shared_ptr<Texture> texture
					= Resources::Load<Texture>(L"SkillChangeBtn", L"..\\Resources\\Texture\\skillchange.png");
				std::shared_ptr<Material> spriteMaterial = std::make_shared<Material>();
				spriteMaterial->shader = spriteShdaer;
				spriteMaterial->texture = texture;
				Resources::Insert(L"SkillChangeBtnMaterial01", spriteMaterial);
			}
			{
				std::shared_ptr<Texture> texture
					= Resources::Load<Texture>(L"PlayerTexture", L"..\\Resources\\Texture\\player.png");
				std::shared_ptr<Material> spriteMaterial = std::make_shared<Material>();
				spriteMaterial->shader = spriteShdaer;
				spriteMaterial->texture = texture;
				Resources::Insert(L"PlayerTextureMaterial01", spriteMaterial);
			}
			{
				std::shared_ptr<Texture> texture
					= Resources::Load<Texture>(L"SeriaTexture", L"..\\Resources\\Texture\\seria.png");
				std::shared_ptr<Material> spriteMaterial = std::make_shared<Material>();
				spriteMaterial->shader = spriteShdaer;
				spriteMaterial->texture = texture;
				Resources::Insert(L"SeriaTextureMaterial01", spriteMaterial);
			}
			{
				std::shared_ptr<Texture> texture
					= Resources::Load<Texture>(L"GoldBox", L"..\\Resources\\Texture\\goldbox.png");
				std::shared_ptr<Material> spriteMaterial = std::make_shared<Material>();
				spriteMaterial->shader = spriteShdaer;
				spriteMaterial->texture = texture;
				Resources::Insert(L"GoldBoxMaterial01", spriteMaterial);
			}
#pragma endregion
		}
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"Smile", L"..\\Resources\\Texture\\Smile.png");
			std::shared_ptr<Material> spriteMaterial = std::make_shared<Material>();
			spriteMaterial->shader = spriteShdaer;
			spriteMaterial->texture = texture;
			spriteMaterial->SetRenderMode(ERenderMode::Transparent);
			Resources::Insert(L"SpriteMaterial02", spriteMaterial);
		}
	}
	void Initialize()
	{
		/* 삼각형
		vertexs[0].pos = {0.0f,0.5f,0.0f};
		vertexs[0].color = { 1.0f,0.0f,0.0f,1.0f };
		vertexs[1].pos = { 0.5f,-0.5f,0.0f };
		vertexs[1].color = { 0.0f,1.0f,0.0f,1.0f };
		vertexs[2].pos = { -0.5f,-0.5f,0.0f };
		vertexs[2].color = { 0.0f,0.0f,1.0f,1.0f };
		*/
		// 인덱스 버퍼 사용법 https://koreanfoodie.me/727

		/* 사각형*/
		vertexs.resize(4);

		vertexs[0].pos = { -0.25f, -0.25f, 0.0f };
		vertexs[0].color = { 1.0f,0.0f,0.0f,1.0f };
		vertexs[0].uv = { 0.0f,1.0f };//uv 좌표 참고로 불칸과 다렉은 좌표가 다름.

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
		/* 마름모

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

	   /* 사다리 꼴
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
	   /* 동그라미

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
	void Render()
	{
		for (Camera* camera : cameras)
		{
			if (camera == nullptr)
				continue;

			camera->Render();
		}
		cameras.clear();
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
