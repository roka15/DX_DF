#include "NPK.h"
#include "RokaGraphicDevice_Dx11.h"
#include "Resources.h"

namespace roka
{
	roka::file::NPKSystem NPK::mNPKSystem;
	using namespace graphics;

	NPK::NPK():Resource(enums::EResourceType::NPK)
	{
	}
	NPK::~NPK()
	{
		for (auto& csv : mCsvs)
		{
			delete csv.second;
			csv.second = nullptr;
		}

		for (auto& pack : mPacks)
		{
			delete pack.second;
			pack.second = nullptr;
		}
	}
	HRESULT NPK::Load(const std::wstring& path)
	{
		mNPKSystem.ReadNPK(roka::file::ws2s(path), mCsvs, mPacks);
		return S_OK;
	}
	std::shared_ptr<Texture> NPK::GetTexture(std::wstring name, UINT index)
	{
		auto itr = mCsvs.find(roka::file::ws2s(name));
		roka::file::CSVInfo* csv = itr->second;
		std::wstring key = GetKey();
		std::wstring texture_name = key + name + L"Texture" + std::to_wstring(index);
		std::shared_ptr<Texture> texture = Resources::Find<Texture>(texture_name);
		if (texture != nullptr)
			return texture;
		
		texture = std::make_shared<Texture>();
	
		roka::file::PackInfo* pack = mPacks[roka::file::ws2s(name)];
		char* binaryImage = pack->binbuf[index]->buffer;

		texture->Create(binaryImage,pack->binbuf[index]->length,csv,index);
		
		Resources::Insert(texture_name,texture);

		return texture;
	}

	Vector2 NPK::GetPos(std::wstring name, UINT index)
	{
		std::pair<int, int> value = mCsvs[roka::file::ws2s(name)]->pos[index];
		return Vector2(value.first, value.second);
	}
	Vector2 NPK::GetSize(std::wstring name, UINT index)
	{
		std::pair<int, int> value = mCsvs[roka::file::ws2s(name)]->size[index];
		return Vector2(value.first, value.second);
	}

	Vector2 NPK::GetCanvasSize(std::wstring name, UINT index)
	{
		std::pair<int, int> value = mCsvs[roka::file::ws2s(name)]->canvas[index];
		return Vector2(value.first, value.second);
	}
}