#pragma once
#include "MyResource.h"
#include "RokaGraphics.h"

#include "../External/DirectXTex/Include/DirectXTex.h"
#include "../External/DirectXTex/Include/DirectXTex.inl"

#ifdef _DEBUG
#pragma comment(lib,"..\\External\\DirectXTex\\Lib\\Debug\\DirectXTex.lib")
#else
#pragma comment(lib,"..\\External\\DirectXTex\\Lib\\Release\\DirectXTex.lib")
#endif

namespace roka::graphics
{
	class Texture :public Resource
	{
	public:
		Texture();
		~Texture();

		virtual HRESULT Load(const std::wstring& path)override;
		void BindShader(EShaderStage stage, UINT startSlot);

		void Create(void* data,size_t size);
		void Clear();

		void SetDesc(D3D11_TEXTURE2D_DESC& desc) { mDesc = desc; }
		SET_PROPERTY(SetDesc) D3D11_TEXTURE2D_DESC desc;
		D3D11_SHADER_RESOURCE_VIEW_DESC GetViewDesc() { return mSRVDesc; }
		GET_PROPERTY(GetView) D3D11_SHADER_RESOURCE_VIEW_DESC view_desc;
		Microsoft::WRL::ComPtr<ID3D11Texture2D> GetTexture() { return mTexture; }
		GET_PROPERTY(GetTexture) Microsoft::WRL::ComPtr<ID3D11Texture2D> texture;
	private:
		ScratchImage mImage;
		Microsoft::WRL::ComPtr<ID3D11Texture2D> mTexture;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mSRV;
		D3D11_SHADER_RESOURCE_VIEW_DESC mSRVDesc;
		D3D11_TEXTURE2D_DESC mDesc;
	};
}


