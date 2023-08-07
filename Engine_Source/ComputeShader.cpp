#include "ComputeShader.h"
#include "RokaGraphicDevice_Dx11.h"

namespace roka::graphics
{
	ComputeShader::ComputeShader()
		:Resource(enums::EResourceType::ComputeShader)
	{
	}
	ComputeShader::~ComputeShader()
	{
	}
	bool ComputeShader::Create(const std::wstring& name, const std::string& methodName)
	{
		std::filesystem::path  shaderPath = std::filesystem::current_path().parent_path();
		shaderPath += L"\\ShaderSource\\";

		std::filesystem::path fullPath(shaderPath.c_str());
		fullPath += name;

		ID3DBlob* errorBlob = nullptr;
		GetDevice()->CompileFromfile(fullPath, methodName, "cs_5_0", mCSBlob.GetAddressOf());
		GetDevice()->CreateComputeShader(mCSBlob.Get(), mCSBlob->GetBufferSize(), mCS.GetAddressOf());

		return true;
	}
}