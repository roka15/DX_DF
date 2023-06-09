#include "Material.h"

roka::graphics::Material::Material()
	:Resource(enums::EResourceType::Material)
	, mShader(nullptr)
	, mTexture(nullptr)
	, mMode(ERenderMode::Opaque)
{
}

roka::graphics::Material::~Material()
{
}

HRESULT roka::graphics::Material::Load(const std::wstring& path)
{
	return E_NOTIMPL;
}

void roka::graphics::Material::Binds()
{
	if (mTexture != nullptr)
		mTexture->BindShader(EShaderStage::PS, 0);
	if (mShader != nullptr)
		mShader->Binds();
}

void roka::graphics::Material::Clear()
{
	mTexture->Clear();
}
