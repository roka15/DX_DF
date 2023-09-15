#pragma once
#include "MyResource.h"
#include "Shader.h"
#include "Texture.h"
namespace roka::graphics
{
	class Material : public Resource
	{
	public:
		Material();
		Material(const Material& ref);
		~Material();

		virtual HRESULT Load(const std::wstring& path)override;

		void Binds();
		void Clear();

		void SetShader(std::shared_ptr<Shader> shader) { mShader = shader; }
		void SetTexture(std::shared_ptr<Texture> texture) { mTexture = texture; }
		void SetRenderMode(ERenderMode mode) { mMode = mode; }

		std::shared_ptr<Shader> GetShader() { return mShader; }
		std::shared_ptr<Texture> GetTexture() { return mTexture; }
		ERenderMode GetRenderMode() { return mMode; }
		bool IsNullTexture() { return mTexture == nullptr; }
		
		PROPERTY(GetShader,SetShader) std::shared_ptr<Shader> shader;
		PROPERTY(GetTexture,SetTexture) std::shared_ptr<Texture> texture;
		
		PROPERTY(GetRenderMode, SetRenderMode) ERenderMode render_mode;

	private:
		std::shared_ptr<Shader> mShader;
		std::shared_ptr <Texture> mTexture;
		ERenderMode mMode;
	};
}


