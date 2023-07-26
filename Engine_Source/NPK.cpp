#include "NPK.h"
#include "RokaGraphicDevice_Dx11.h"
#include "Resources.h"

namespace roka
{
	roka::file::NPKSystem NPK::mNPKSystem;
	using namespace graphics;

	NPK::NPK() :Resource(enums::EResourceType::NPK)
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
		std::wstring key = GetKey();
		std::wstring texture_name = key + name + L"Texture" + std::to_wstring(index);
		std::shared_ptr<Texture> texture = Resources::Find<Texture>(texture_name);
		if (texture != nullptr)
			return texture;
		return nullptr;
	}

	std::shared_ptr<Texture> NPK::Create(std::wstring name, UINT index)
	{
		std::wstring key = GetKey();
		std::wstring texture_name = key + name + L"Texture" + std::to_wstring(index);

		auto itr = mCsvs.find(roka::file::ws2s(name));
		roka::file::CSVInfo* csv = itr->second;
		std::shared_ptr<Texture> texture;
		texture = std::make_shared<Texture>();

		roka::file::PackInfo* pack = mPacks[roka::file::ws2s(name)];
		file::CSVInfo use_csv = {};
		file::PackInfo use_pack = {};
		use_csv.canvas.push_back(csv->canvas[index]);
		use_csv.name = csv->name;
		use_csv.pos.push_back(csv->pos[index]);
		use_csv.size.push_back(csv->size[index]);
		use_pack.name = pack->name;
		file::FileInfo* fileData = new file::FileInfo(*(pack->binbuf[index]));
		use_pack.binbuf.push_back(fileData);

		texture->Create(&use_csv, &use_pack);

		Resources::Insert(texture_name, texture);

		return texture;
	}

	std::shared_ptr<Texture> NPK::CreateAtlas(std::wstring pack_name, UINT start_index, UINT end_index, std::wstring set_name)
	{
		std::wstring key = GetKey();
		std::wstring texture_name = set_name + L"AtlasTexture";
		file::CSVInfo csv = {};
		file::PackInfo pack = {};
		auto csv_itr = mCsvs.find(file::ws2s(pack_name));
		auto pack_itr = mPacks.find(file::ws2s(pack_name));
		int count = end_index - start_index;

		for (int i = start_index; i < end_index; i++)
		{
			csv.canvas.push_back(csv_itr->second->canvas[i]);
			csv.name = csv_itr->second->name;
			csv.pos.push_back(csv_itr->second->pos[i]);
			csv.size.push_back(csv_itr->second->size[i]);
			pack.name = pack_itr->second->name;
			file::FileInfo* fileData = new file::FileInfo(*(pack_itr->second->binbuf[i]));
			pack.binbuf.push_back(fileData);
		}

		std::shared_ptr<Texture> texture = std::make_shared<Texture>();
		texture->Create(&csv, &pack);

		Resources::Insert(texture_name, texture);
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
		Vector2 CanvasSize = {};

		CanvasSize.x = mCsvs[roka::file::ws2s(name)]->canvas[index].first;
		CanvasSize.y = mCsvs[roka::file::ws2s(name)]->canvas[index].second;

		return CanvasSize;
	}
	Vector2 NPK::GetAddCanvasSize(std::wstring name, UINT start_index, UINT end_index)
	{
		Vector2 size = {};

		auto itr = mCsvs.find(file::ws2s(name));
		if (itr == mCsvs.end())
			return Vector2(0, 0);

		for (int i = start_index; i <= end_index; i++)
		{
			size.x += itr->second->canvas[i].first;
			size.y += itr->second->canvas[i].second;
		}
		return size;
	}
}