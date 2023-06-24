#pragma once
#include "Entity.h"

namespace roka
{
	class Resource
	{
	public:
		Resource(roka::enums::EResourceType type);
		virtual ~Resource();

		virtual HRESULT Load(const std::wstring& path) = 0;

		const std::wstring& GetKey() { return mKey; }
		const std::wstring& GetPath() { return mPath; }
		void SetKey(const std::wstring& key) { mKey = key; }
		void SetPath(const std::wstring& path) { mPath = path; }

		enums::EResourceType GetType() { return mType; }
		GET_PROPERTY(GetType) enums::EResourceType type;
	private:
		std::wstring mKey;
		std::wstring mPath;
		const roka::enums::EResourceType mType;
	};
}
