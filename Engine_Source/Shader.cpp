#include "Shader.h"

namespace roka
{
	Shader::Shader()
		:mInputLayout(nullptr),
		mTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST)
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
		//���� ������ ����
		graphics::GetDevice()->BindPrimitiveTopology(mTopology);
		graphics::GetDevice()->BindInputLayout(mInputLayout);//���̴� �ڵ忡 �ԷµǴ� ���� ��ü���� ����.
		
		graphics::GetDevice()->BindVertexShader(mVS.Get());
		graphics::GetDevice()->BindPixelShader(mPS.Get());
	}
}