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

namespace roka
{
	class Sprite;
	using namespace math;
}
namespace roka::graphics
{
	class Texture :public Resource
	{
	public:
		Texture();
		~Texture();

		virtual HRESULT Load(const std::wstring& path)override;
		void BindShaderResource(EShaderStage stage, UINT startSlot);
		void BindUnorderedAccessViews(UINT slot);
		void ClearUnorderedAccessViews(UINT slot);

		bool Create(UINT width, UINT height, DXGI_FORMAT format, UINT bindFlags);
		void Create(const file::PackInfo* packs);
		void Clear();

		size_t GetWidth() { return mDesc.Width; }
		size_t GetHeight() { return mDesc.Height; }

		void SetDesc(D3D11_TEXTURE2D_DESC& desc) { mDesc = desc; }
		D3D11_SHADER_RESOURCE_VIEW_DESC GetViewDesc() { return mSRVDesc; }
		Microsoft::WRL::ComPtr<ID3D11Texture2D>& GetTexture() { return mTexture; }
		void SetTexture(Microsoft::WRL::ComPtr<ID3D11Texture2D> texture) { mTexture = texture; }

		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> GetRTV() { return mRTV; }
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> GetSRV() { return mSRV; }
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView> GetDSV() { return mDSV; }
		Microsoft::WRL::ComPtr<ID3D11UnorderedAccessView> GetUAV() { return mUAV; }

		void SetRTV(Microsoft::WRL::ComPtr<ID3D11RenderTargetView> rtv) { mRTV = rtv; }
		void SetDSV(Microsoft::WRL::ComPtr<ID3D11DepthStencilView> dsv) { mDSV = dsv; }

		void AddSprite(Sprite sprite);
		const Sprite GetSprite(int index);
		const Sprite GetSprite();
		size_t GetSpriteSize();
		void SetCurSpriteIndex(size_t index) { mCurSpriteIndex = index; }

		void SpriteRatioValue(Vector2 ratio);
		SET_PROPERTY(SetDesc) D3D11_TEXTURE2D_DESC desc;
		GET_PROPERTY(GetView) D3D11_SHADER_RESOURCE_VIEW_DESC view_desc;
		GET_PROPERTY(GetTexture) Microsoft::WRL::ComPtr<ID3D11Texture2D> texture;
	protected:
		void CreateCanvasBaseTexture();
		std::shared_ptr<Texture> CreateTexture(void* data, size_t size);
		void CombineTextures(std::vector<std::shared_ptr<Texture>> textures);
	private:
		std::vector<Sprite> mSprites;
		ScratchImage mImage;
		size_t mCurSpriteIndex;
		Microsoft::WRL::ComPtr<ID3D11Texture2D> mTexture;
	
		D3D11_SHADER_RESOURCE_VIEW_DESC mSRVDesc;
		D3D11_TEXTURE2D_DESC mDesc;

		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mSRV;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> mRTV;
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView> mDSV;
		Microsoft::WRL::ComPtr<ID3D11UnorderedAccessView> mUAV;
	};
}


