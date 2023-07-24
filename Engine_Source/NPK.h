#pragma once
#include "MyResource.h"
#include "RokaGraphics.h"
#include "Texture.h"


namespace roka
{
	using namespace roka::math;
	class NPK :public Resource
	{
	public:
		NPK();
		~NPK();
		virtual HRESULT Load(const std::wstring& path)override;

		typedef roka::graphics::Texture Texture;
		std::shared_ptr<Texture> GetTexture(std::wstring name, UINT index);
		std::shared_ptr<Texture> Create(std::wstring name, UINT index);
		std::shared_ptr<Texture> CreateAtlas(std::wstring pack_name,UINT start_index, UINT end_index,std::wstring set_name);

		Vector2 GetPos(std::wstring name, UINT index);
		Vector2 GetSize(std::wstring name, UINT index);
		Vector2 GetCanvasSize(std::wstring name,UINT index);

		Vector2 GetAddCanvasSize(std::wstring name, UINT start_index, UINT end_index);
	private:
		static roka::file::NPKSystem mNPKSystem;
		std::map<std::string, roka::file::CSVInfo*> mCsvs;
		std::map<std::string, roka::file::PackInfo*> mPacks;
	};
}


