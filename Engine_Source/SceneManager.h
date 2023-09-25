#pragma once
#include "Scene.h"
namespace roka
{
	class GameObject;
	class SceneManager
	{
	public:
		static void Initialize();
		static void Update();
		static void LateUpdate();
		static void Render();
		static void Release();
		static void Destroy();

		template <typename T>
		static bool CreateScene(std::wstring name)
		{
			T* scene = new T();

			std::map<std::wstring, Scene*>::iterator iter
				= mScenes.find(name);

			if (iter != mScenes.end())
				return false;

			mScenes.insert(std::make_pair(name, scene));
			scene->SetName(name);
			mActiveScene = scene;
			scene->Initialize();
			return true;
		}
		static Scene* GetActiveScene() { return mActiveScene; }
		static Scene* LoadScene(std::wstring name);
		static Scene* LoadScene(ESceneType type);
		static void AddGameObject(enums::ELayerType type, std::shared_ptr<GameObject> obj);
		static void DontDestroy(std::shared_ptr<GameObject> obj);
		static std::shared_ptr<GameObject> FindGameObject(std::wstring key);
		static std::shared_ptr<GameObject> FindGameObject(enums::ELayerType type, std::wstring key);
		static std::vector<std::shared_ptr<GameObject>> FindGameObjects(enums::ELayerType type);
		static std::vector<std::shared_ptr<GameObject>> GetGameObjects();
		static std::vector<std::shared_ptr<GameObject>> GetGameObjects(const std::bitset<(UINT)enums::ELayerType::End>& layerMask);
	private:
		static Scene* mActiveScene;
		static std::map<std::wstring, Scene*> mScenes;
	};

}

