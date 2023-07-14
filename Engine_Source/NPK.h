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
		

		Vector2 GetPos(std::wstring name, UINT index);
		Vector2 GetSize(std::wstring name, UINT index);
		Vector2 GetCanvasSize(std::wstring name,UINT index);
	private:
		static roka::file::NPKSystem mNPKSystem;
		std::map<std::string, roka::file::CSVInfo*> mCsvs;
		std::map<std::string, roka::file::PackInfo*> mPacks;
	};
}


