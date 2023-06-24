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
		~Material();

		virtual HRESULT Load(const std::wstring& path)override;

		void Binds();
		void Clear();

		void SetShader(std::shared_ptr<Shader> shader) { mShader = shader; }
		void SetTexture(std::shared_ptr<Texture> texture) { mTexture = texture; }

		SET_PROPERTY(SetShader) std::shared_ptr<Shader> shader;
		SET_PROPERTY(SetTexture) std::shared_ptr<Texture> texture;
		
	private:
		std::shared_ptr<Shader> mShader;
		std::shared_ptr <Texture> mTexture;
	};
}


