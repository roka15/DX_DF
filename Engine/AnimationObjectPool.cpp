#include "AnimationObjectPool.h"
#include "Resources.h"
#include "GameObject.h"
#include "MeshRenderer.h"
namespace roka
{
	std::shared_ptr<GameObject> pool::AnimationObjectPool::Spawn(std::wstring key)
	{
		std::shared_ptr<GameObject> object
			= ObjectPoolManager<AnimationObjectPool, GameObject>::Spawn(key);
		std::shared_ptr<MeshRenderer> mesh = object->GetComponent<MeshRenderer>();
		std::shared_ptr<Material> material = nullptr;
		if (object->GetName().compare(L"AniObject") == 0 || object->GetName().compare(L"ColAniObject") == 0)
		{
			material = Resources::Find<Material>(L"DefaultAniMaterial");
		}
		else if (object->GetName().compare(L"AniEftObject") == 0 || object->GetName().compare(L"ColAniEftObject") == 0)
		{
			material = Resources::Find<Material>(L"DefaultEffectAniMaterial");
		}
		mesh->material->Copy(material.get());

		return object;
	}

}
