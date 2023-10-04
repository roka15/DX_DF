#pragma once
#include "Application.h"
namespace roka
{
    class TileMapToolApplication :
        public Application
    {
	public:
		TileMapToolApplication();
		virtual ~TileMapToolApplication() {}
		virtual void Run();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();
		virtual void Release();
		virtual void Destroy();

	
	private:
		std::wstring mNPKKey;
    };
}


