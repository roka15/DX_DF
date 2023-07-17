#pragma once
#include "RokaGraphicDevice_Dx11.h"
#include "MyResource.h"
#include "RokaGraphics.h"
namespace roka
{
	using namespace graphics;
	class Shader :
		public Resource
	{
	public:
		Shader();
		~Shader();
		
		virtual HRESULT Load(const std::wstring& path)override;
		bool Create(const EShaderStage stage, const std::wstring& fileName, const std::string& funcName);
		void Binds();

		ID3DBlob* GetVSCode()
		{
			return mVSBlob.Get();
		}
		ID3D11InputLayout* GetInputLayout()
		{
			return mInputLayout;
		}
		ID3D11InputLayout** GetInputLayoutAddressOf()
		{
			return &mInputLayout;
		}

	
		void SetRSState(ERSType type) { mRsType = type; }
		void SetDSState(EDSType type) { mDsType = type; }
		void SetBSState(EBSType type) { mBsType = type; }
	    
		void SetTopology(D3D11_PRIMITIVE_TOPOLOGY topology) { mTopology = topology; }
		

		SET_PROPERTY(SetRSState) ERSType rsstate;
		SET_PROPERTY(SetDSState) EDSType dsstate;
		SET_PROPERTY(SetBSState) EBSType bsstate;
		
		SET_PROPERTY(SetTopology) D3D11_PRIMITIVE_TOPOLOGY topology;
	private:
		ID3D11InputLayout* mInputLayout;
		D3D11_PRIMITIVE_TOPOLOGY mTopology;

		Microsoft::WRL::ComPtr<ID3DBlob> mVSBlob;
		Microsoft::WRL::ComPtr<ID3DBlob> mHSBlob;
		Microsoft::WRL::ComPtr<ID3DBlob> mDSBlob;
		Microsoft::WRL::ComPtr<ID3DBlob> mGSBlob;
		Microsoft::WRL::ComPtr<ID3DBlob> mPSBlob;

		Microsoft::WRL::ComPtr<ID3D11VertexShader> mVS;
		Microsoft::WRL::ComPtr<ID3D11HullShader> mHS;
		Microsoft::WRL::ComPtr<ID3D11DomainShader> mDS;
		Microsoft::WRL::ComPtr<ID3D11GeometryShader> mGS;
		Microsoft::WRL::ComPtr<ID3D11PixelShader> mPS;

		ERSType mRsType;
		EDSType mDsType;
		EBSType mBsType;
	};
}


