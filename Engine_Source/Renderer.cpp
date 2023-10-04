#include "Renderer.h"
#include "GameObject.h"
#include "Resources.h"
#include "Texture.h"
#include "Material.h"
#include "Mesh.h"
#include "Shader.h"
#include "StructBuffer.h"
#include "PaintShader.h"
#include "Light.h"


namespace roka::renderer
{
	using namespace roka::graphics;
	
	ConstantBuffer* constantBuffer[(UINT)ECBType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerStates[(UINT)ESamplerType::End];

	Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizerStates[(UINT)ERSType::End];
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthstencilStates[(UINT)EDSType::End];
	Microsoft::WRL::ComPtr<ID3D11BlendState> blendStates[(UINT)EBSType::End];

	std::vector<std::shared_ptr<GameObject>> lights = {};
	StructBuffer* lightsBuffer = nullptr;
	
	std::vector<std::shared_ptr<roka::Camera>> cameras = {};
	std::shared_ptr<roka::Camera> MainCamera = nullptr;

	std::vector<DebugMesh> debugMeshs = {};
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

		shader = roka::Resources::Find<Shader>(L"VerticalInverterShader");
		GetDevice()->CreateInputLayout(arrLayout, 3
			, shader->GetVSCode(), shader->GetInputLayoutAddressOf());

		shader = roka::Resources::Find<Shader>(L"GridShader");
		GetDevice()->CreateInputLayout(arrLayout, 3
			, shader->GetVSCode(), shader->GetInputLayoutAddressOf());

		shader = roka::Resources::Find<Shader>(L"EffectShader");
		GetDevice()->CreateInputLayout(arrLayout, 3
			, shader->GetVSCode(), shader->GetInputLayoutAddressOf());

		shader = roka::Resources::Find<Shader>(L"EffectAtlasShader");
		GetDevice()->CreateInputLayout(arrLayout, 3
			, shader->GetVSCode(), shader->GetInputLayoutAddressOf());

		shader = roka::Resources::Find<Shader>(L"DebugShader");
		GetDevice()->CreateInputLayout(arrLayout, 3
			, shader->GetVSCode(), shader->GetInputLayoutAddressOf());

		shader = roka::Resources::Find<Shader>(L"AtlasShader");
		GetDevice()->CreateInputLayout(arrLayout, 3
			, shader->GetVSCode(), shader->GetInputLayoutAddressOf());
		
		shader = roka::Resources::Find<Shader>(L"VerticalInverterAtlasShader");
		GetDevice()->CreateInputLayout(arrLayout, 3
			, shader->GetVSCode(), shader->GetInputLayoutAddressOf());

		shader = roka::Resources::Find<Shader>(L"VerticalInverterEftAtlasShader");
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
	void LoadMesh()
	{
		std::vector<Vertex> vertexes = {};
		std::vector<UINT> indexes = {};

		vertexes.resize(4);
		/* 사각형*/
		
		vertexes[0].pos = Vector3(-0.5f, 0.5f, 0.0f);
		vertexes[0].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		vertexes[0].uv = Vector2(0.0f, 0.0f);

		vertexes[1].pos = Vector3(0.5f, 0.5f, 0.0f);
		vertexes[1].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		vertexes[1].uv = Vector2(1.0f, 0.0f);

		vertexes[2].pos = Vector3(0.5f, -0.5f, 0.0f);
		vertexes[2].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		vertexes[2].uv = Vector2(1.0f, 1.0f);

		vertexes[3].pos = Vector3(-0.5f, -0.5f, 0.0f);
		vertexes[3].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		vertexes[3].uv = Vector2(0.0f, 1.0f);

		indexes.push_back(0);
		indexes.push_back(1);
		indexes.push_back(2);
		indexes.push_back(0);
		indexes.push_back(2);
		indexes.push_back(3);

		std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
		mesh->CreateVertexBuffer(vertexes.data(), vertexes.size());
		mesh->CreateIndexBuffer(indexes.data(), indexes.size());
		Resources::Insert(L"RectMesh", mesh);


		std::shared_ptr<Mesh> rectDebug = std::make_shared<Mesh>();
		rectDebug->CreateVertexBuffer(vertexes.data(), vertexes.size());
		rectDebug->CreateIndexBuffer(indexes.data(), indexes.size());
		Resources::Insert(L"DebugRect", rectDebug);

		vertexes.clear();
		indexes.clear();
	   /* 원 */
		Vertex center = {};
		center.pos = Vector3(0.0f, 0.0f, 0.0f);
		center.color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		vertexes.push_back(center);

		int iSlice = 40;
		float fRadius = 0.5f;
		float fTheta = XM_2PI / (float)iSlice;

		for (int i = 0; i < iSlice; ++i)
		{
			center.pos = Vector3(fRadius * cosf(fTheta * (float)i)
				, fRadius * sinf(fTheta * (float)i)
				, 0.0f);
			center.color = Vector4(0.0f, 1.0f, 0.0f, 1.f);
			vertexes.push_back(center);
		}

		for (int i = 0; i < vertexes.size() - 2; ++i)
		{
			indexes.push_back(i + 1);
		}
		indexes.push_back(1);

		std::shared_ptr<Mesh> circleDebug = std::make_shared<Mesh>();
		Resources::Insert(L"DebugCircle", circleDebug);
		circleDebug->CreateVertexBuffer(vertexes.data(), vertexes.size());
		circleDebug->CreateIndexBuffer(indexes.data(), indexes.size());

#pragma region another 
		/* 삼각형
				vertexs[0].pos = {0.0f,0.5f,0.0f};
				vertexs[0].color = { 1.0f,0.0f,0.0f,1.0f };
				vertexs[1].pos = { 0.5f,-0.5f,0.0f };
				vertexs[1].color = { 0.0f,1.0f,0.0f,1.0f };
				vertexs[2].pos = { -0.5f,-0.5f,0.0f };
				vertexs[2].color = { 0.0f,0.0f,1.0f,1.0f };
				*/
				// 인덱스 버퍼 사용법 https://koreanfoodie.me/727


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

#pragma endregion
	}
	void LoadBuffer()
	{
		//constant buffer
		constantBuffer[(UINT)ECBType::Transform] = new roka::graphics::ConstantBuffer(ECBType::Transform);
		constantBuffer[(UINT)ECBType::Transform]->Create(sizeof(TransformCB));

		constantBuffer[(UINT)ECBType::Material] = new roka::graphics::ConstantBuffer(ECBType::Material);
		constantBuffer[(UINT)ECBType::Material]->Create(sizeof(MaterialCB));

		constantBuffer[(UINT)ECBType::Grid] = new roka::graphics::ConstantBuffer(ECBType::Grid);
		constantBuffer[(UINT)ECBType::Grid]->Create(sizeof(GridCB));

		constantBuffer[(UINT)ECBType::Atlas] = new roka::graphics::ConstantBuffer(ECBType::Atlas);
		constantBuffer[(UINT)ECBType::Atlas]->Create(sizeof(AtlasCB));

		lightsBuffer = new StructBuffer();
		lightsBuffer->Create(sizeof(LightAttribute), 2, ESRVType::None);
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

		std::shared_ptr<Shader>  v_inversterShdaer = std::make_shared<Shader>();
		v_inversterShdaer->Create(EShaderStage::VS, L"VerticalInverterVS.hlsl", "main");
		v_inversterShdaer->Create(EShaderStage::PS, L"SpritePS.hlsl", "main");
		roka::Resources::Insert(L"VerticalInverterShader", v_inversterShdaer);

		std::shared_ptr<Shader> gridShader = std::make_shared<Shader>();
		gridShader->Create(EShaderStage::VS, L"GridVS.hlsl", "main");
		gridShader->Create(EShaderStage::PS, L"GridPS.hlsl", "main");
		roka::Resources::Insert(L"GridShader", gridShader);

		std::shared_ptr<Shader> effectShader = std::make_shared<Shader>();
		effectShader->Create(EShaderStage::VS, L"SpriteVS.hlsl", "main");
		effectShader->Create(EShaderStage::PS, L"SpritePS.hlsl", "main");
		effectShader->bsstate = EBSType::OneOne;
		roka::Resources::Insert(L"EffectShader", effectShader);

		
		std::shared_ptr<Shader> effectAniShader = std::make_shared<Shader>();
		effectAniShader->Create(EShaderStage::VS, L"AtlasVS.hlsl", "main");
		effectAniShader->Create(EShaderStage::PS, L"AtlasPS.hlsl", "main");
		effectAniShader->bsstate = EBSType::OneOne;
		roka::Resources::Insert(L"EffectAtlasShader", effectAniShader);

		std::shared_ptr<Shader> debugShader = std::make_shared<Shader>();
		debugShader->Create(EShaderStage::VS, L"DebugVS.hlsl", "main");
		debugShader->Create(EShaderStage::PS, L"DebugPS.hlsl", "main");
		debugShader->SetTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		debugShader->SetRSState(ERSType::WireFrameNone);
		roka::Resources::Insert(L"DebugShader", debugShader);

		std::shared_ptr<Shader> animationShader = std::make_shared<Shader>();
		animationShader->Create(EShaderStage::VS, L"AtlasVS.hlsl", "main");
		animationShader->Create(EShaderStage::PS, L"AtlasPS.hlsl", "main");
		animationShader->SetKey(L"AtlasShader");
		roka::Resources::Insert(L"AtlasShader", animationShader);

		std::shared_ptr<Shader> animationinverterShader = std::make_shared<Shader>();
		animationinverterShader->Create(EShaderStage::VS, L"VerticalInverterVS.hlsl", "main");
		animationinverterShader->Create(EShaderStage::PS, L"AtlasPS.hlsl", "main");
		animationinverterShader->SetKey(L"VerticalInverterAtlasShader");
		roka::Resources::Insert(L"VerticalInverterAtlasShader", animationinverterShader);

		std::shared_ptr<Shader> animationinverterEftShader = std::make_shared<Shader>();
		animationinverterEftShader->Create(EShaderStage::VS, L"VerticalInverterVS.hlsl", "main");
		animationinverterEftShader->Create(EShaderStage::PS, L"AtlasPS.hlsl", "main");
		animationinverterEftShader->bsstate = EBSType::OneOne;
		animationinverterShader->SetKey(L"VerticalInverterEftAtlasShader");
		roka::Resources::Insert(L"VerticalInverterEftAtlasShader", animationinverterEftShader);
	
		std::shared_ptr<PaintShader> paintShader = std::make_shared<PaintShader>();
		paintShader->Create(L"PaintCS.hlsl", "main");
		Resources::Insert(L"PaintShader", paintShader);
	}
	void LoadTexture()
	{
		std::shared_ptr<Texture> uavTexture = std::make_shared<Texture>();
		uavTexture->Create(1024, 1024, DXGI_FORMAT_R8G8B8A8_UNORM, D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS);
		Resources::Insert(L"PaintTexture", uavTexture);
	}
	void LoadMaterial()
	{
		std::shared_ptr<Shader>  spriteShdaer = Resources::Find<Shader>(L"SpriteShader");
		std::shared_ptr<Shader>  v_inversterShdaer = Resources::Find<Shader>(L"VerticalInverterShader");
		std::shared_ptr<Shader> gridShader = Resources::Find<Shader>(L"GridShader");
		std::shared_ptr<Shader> effectShader = Resources::Find<Shader>(L"EffectShader");
		std::shared_ptr<Shader> debugShader = Resources::Find<Shader>(L"DebugShader");

		{
			{
				std::shared_ptr<Material> spriteMaterial = std::make_shared<Material>();
				spriteMaterial->shader = spriteShdaer;
				Resources::Insert(L"SpriteMaterial", spriteMaterial);
			}

		}
		{
			std::shared_ptr<Material> material = std::make_shared<Material>();
			material->shader = debugShader;
			Resources::Insert(L"DebugMaterial", material);
		}
#pragma region grid material
		{
			std::shared_ptr<Material> spriteMaterial = std::make_shared<Material>();
			spriteMaterial->shader = gridShader;
			Resources::Insert(L"GridMaterial", spriteMaterial);
		}
#pragma endregion

#pragma region paint material
		{	
			std::shared_ptr<Texture> texture = Resources::Find<Texture>(L"PaintTexture");
			std::shared_ptr<Material> material = std::make_shared<Material>();
			material->shader = spriteShdaer;
			material->SetTexture(texture);
			material->render_mode = ERenderMode::Transparent;
			Resources::Insert(L"PaintMaterial", material);
		}
#pragma endregion
	}
	void Initialize()
	{
		LoadMesh();
		LoadBuffer();
		LoadShader();
		
		SetupState();
		LoadTexture();
		LoadMaterial();
	}
	void BindLights()
	{
		std::vector<LightAttribute> lightsAttributes = {};
		for (std::shared_ptr<GameObject>& obj : lights)
		{
			std::shared_ptr<Light> light = obj->GetComponent<Light>();
			LightAttribute attribute = light->GetAttribute();
			lightsAttributes.push_back(attribute);
		}

		lightsBuffer->SetData(lightsAttributes.data(), lightsAttributes.size());
		lightsBuffer->Bind(EShaderStage::VS, 13);
		lightsBuffer->Bind(EShaderStage::PS, 13);
	}
	void Render()
	{
		BindLights();

		for (std::shared_ptr<Camera> camera : cameras)
		{
			if (camera == nullptr)
				continue;

			camera->Render();
		}
		cameras.clear();
		lights.clear();
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
		cameras.clear();
		MainCamera.reset();

		lights.clear();
		delete lightsBuffer;
		lightsBuffer = nullptr;
	}
	void PushDebugMeshAttribute(DebugMesh mesh)
	{
		debugMeshs.push_back(mesh);
	}
}
