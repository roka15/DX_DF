#include "Shader.h"
#include "Renderer.h"
namespace roka
{
	Shader::Shader()
		:Resource(enums::EResourceType::Shader)
		,mInputLayout(nullptr)
		,mTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST)
		,mRsType(ERSType::SolidBack)
		,mDsType(EDSType::LessEqual)
		,mBsType(EBSType::AlphaBlend)
	{
	}
	Shader::~Shader()
	{
		mInputLayout->Release();
	}
	HRESULT Shader::Load(const std::wstring& path)
	{
		return E_NOTIMPL;
	}
	bool Shader::Create(const EShaderStage stage, const std::wstring& fileName, const std::string& funcName)
	{
		std::filesystem::path shaderPath
			= std::filesystem::current_path().parent_path();
		shaderPath += L"\\ShaderSource\\";

		std::filesystem::path fullPath(shaderPath.c_str());
		fullPath += fileName;

		ID3DBlob* errorBlob = nullptr;
		if (stage == EShaderStage::VS)
		{
			graphics::GetDevice()->CompileFromfile(fullPath, funcName, "vs_5_0", mVSBlob.GetAddressOf());
			graphics::GetDevice()->CreateVertexShader(mVSBlob->GetBufferPointer(),mVSBlob->GetBufferSize(),mVS.GetAddressOf());
		}
		else if (stage == EShaderStage::PS)
		{
			graphics::GetDevice()->CompileFromfile(fullPath, funcName, "ps_5_0", mPSBlob.GetAddressOf());
			graphics::GetDevice()->CreatePixelShader(mPSBlob->GetBufferPointer(), mPSBlob->GetBufferSize(), mPS.GetAddressOf());
		}
		return false;
	}
	void Shader::Binds()
	{
		//정점 정보들 설정
		graphics::GetDevice()->BindPrimitiveTopology(mTopology);
		graphics::GetDevice()->BindInputLayout(mInputLayout);//셰이더 코드에 입력되는 정점 개체들의 정보.
		
		graphics::GetDevice()->BindVertexShader(mVS.Get());
		graphics::GetDevice()->BindPixelShader(mPS.Get());

		Microsoft::WRL::ComPtr<ID3D11RasterizerState> rsState = renderer::rasterizerStates[(UINT)mRsType];
		Microsoft::WRL::ComPtr<ID3D11DepthStencilState> dsState = renderer::depthstencilStates[(UINT)mDsType];
		Microsoft::WRL::ComPtr<ID3D11BlendState> bsState = renderer::blendStates[(UINT)mBsType];
		graphics::GetDevice()->BindRasterizerState(rsState.Get());
		graphics::GetDevice()->BindDepthStencilState(dsState.Get());
		graphics::GetDevice()->BindBlendState(bsState.Get());
	}
}