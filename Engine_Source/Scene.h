#pragma once
#include "Entity.h"
#include "Layer.h"
#include "SceneSector.h"
namespace roka
{
	class Scene : public Entity
	{
	public:
		Scene(enums::ESceneType type);
		virtual ~Scene();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();
		virtual void Destroy();

		virtual void OnExit();
		virtual void OnEnter();

		virtual void Loading();
		void AddGameObject(enums::ELayerType type, std::shared_ptr<GameObject> gameObj);
		std::shared_ptr<GameObject> FindGameObject(enums::ELayerType type,std::wstring name);

		template <typename T>
		std::vector<T*> FindObjectsOfType()
		{
			std::vector<T*> FindObjs = {};
			for (Layer& layer : mLayers)
			{
				auto objs = layer->GetGameObjects();

				for (std::shared_ptr<GameObject> obj : objs)
				{
					T* find = dynamic_cast<T*>(obj);
					if (find == nullptr)
						continue;

					FindObjs.push_back(find);
				}
			}
			return FindObjs;
		}

		Layer& GetLayer(enums::ELayerType type) { return mLayers[(UINT)type]; }

	protected:
		SceneSector* GetSector() { return mActiveSector; }
		void SetSector(SceneSector* sector) { 
			mActiveSector = sector; 
		}
		PROPERTY(GetSector, SetSector) SceneSector* sector;
	private:
		std::vector<Layer> mLayers;
		enums::ESceneType mType;
		SceneSector* mActiveSector;
	};

}

