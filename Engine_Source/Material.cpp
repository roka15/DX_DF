#include "Material.h"
#include "Resources.h"
roka::graphics::Material::Material()
	:Resource(enums::EResourceType::Material)
	, mShader(nullptr)
	, mTexture(nullptr)
	, mMode(ERenderMode::Opaque)
{
}

roka::graphics::Material::Material(const Material& ref) :Resource(ref)
{
	std::wstring key;
	mMode = ref.mMode;
	if (ref.mShader != nullptr)
	{
		key = ref.mShader->GetKey();
		if (key.size() != 0)
		{
			mShader = Resources::Find<Shader>(key);
		}
	}

	if (ref.mTexture != nullptr)
	{
		key = ref.mTexture->GetKey();
		if (key.size() != 0)
		{
			mTexture = Resources::Find<Texture>(key + L"AtlasTexture");
		}
	}

}

roka::graphics::Material::~Material()
{
}

void roka::graphics::Material::Copy(Material* src)
{
	std::wstring key;
	Material* source = dynamic_cast<Material*>(src);
	if (source == nullptr)
		return;
	
	mMode = source->mMode;

	if (src->mShader != nullptr)
	{
		key = src->mShader->GetKey();
		if (key.size() != 0)
		{
			mShader = Resources::Find<Shader>(key);
		}
	}

	if (src->mTexture != nullptr)
	{
		key = src->mTexture->GetKey();
		if (key.size() != 0)
		{
			mTexture = Resources::Find<Texture>(key + L"AtlasTexture");
		}
	}
}

HRESULT roka::graphics::Material::Load(const std::wstring& path)
{
	return E_NOTIMPL;
}

void roka::graphics::Material::Binds(bool atlas)
{
	if (mTexture != nullptr && atlas == false)
	{
		mTexture->BindShaderResource(EShaderStage::PS, 0);
	}
	if (mShader != nullptr)
		mShader->Binds();
}

void roka::graphics::Material::Clear()
{
	mTexture->Clear();
}
