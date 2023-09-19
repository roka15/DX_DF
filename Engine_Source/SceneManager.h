#pragma once
#include "Scene.h"
namespace roka
{
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
	private:
		static Scene* mActiveScene;
		static std::map<std::wstring, Scene*> mScenes;
	};

}

