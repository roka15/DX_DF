#pragma once
#include "RokaEngine.h"
#include "SingleTon.h"
namespace roka
{
	class GameObject;
	class DontDestroyOnLoad : public Singleton<DontDestroyOnLoad>
	{
	protected:
		DontDestroyOnLoad();
	public:
		~DontDestroyOnLoad() {}
		void Initialize();
		void Update();
		void LateUpdate();
		void Destroy();
		void Release();
		
		void AddGameObject(std::shared_ptr<GameObject> obj) { mGameObjects.push_back(obj); }
		std::shared_ptr<GameObject> FindGameObject(std::wstring name);
		std::vector<std::shared_ptr<GameObject>> GetGameObjects();
		std::vector<std::shared_ptr<GameObject>> FindGameObjects(enums::ELayerType type);
	private:
		friend class Singleton<DontDestroyOnLoad>;
		std::vector<std::shared_ptr<GameObject>> mGameObjects;
	};
}


