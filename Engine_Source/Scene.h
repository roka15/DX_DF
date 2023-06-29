#pragma once
#include "Entity.h"
#include "Layer.h"
#include "SceneSector.h"
namespace roka
{
	class Scene : public Entity
	{
	public:
		Scene(ESceneType type);
		virtual ~Scene();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		virtual void OnExit();
		virtual void OnEnter();

		virtual void Loading();
		void AddGameObject(ELayerType type, GameObject* gameObj);
		GameObject* FindGameObject(ELayerType type,std::wstring name);
	protected:
		SceneSector* GetSector() { return mActiveSector; }
		void SetSector(SceneSector* sector) { 
			mActiveSector = sector; 
		}
		PROPERTY(GetSector, SetSector) SceneSector* sector;
	private:
		std::vector<Layer> mLayers;
		ESceneType mType;
		SceneSector* mActiveSector;
	};

}

