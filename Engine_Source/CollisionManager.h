#pragma once
#include "RokaEngine.h"

namespace roka
{
	using namespace enums;
#define LAYER_MAX (UINT)ELayerType::End
	
	class Collider2D;
	class GameObject;
	class CollisionManager
	{
	public:
		union ColliderID
		{
			struct
			{
				UINT left;
				UINT right;
			};
			UINT64 id;
		};

		static void Initialize();
		static void Update();
		static void LayerCollision(ELayerType left, ELayerType right);
		static void ColliderCollision(std::shared_ptr<Collider2D> left, std::shared_ptr<Collider2D> right);
		static bool Intersect(std::shared_ptr<Collider2D> left, std::shared_ptr<Collider2D> right);

		static void DisableCollision(std::shared_ptr<Collider2D> left, std::shared_ptr<Collider2D> right);
		static void SetLayer(ELayerType left, ELayerType right, bool enable);
		static void Clear();
		static double GetColliderTimer() { return mTime; }
		static void FindCollider(std::shared_ptr<GameObject> obj,std::vector<std::shared_ptr<Collider2D>>& cols);
	private:
		static std::bitset<LAYER_MAX> mMatrix[LAYER_MAX];
		static std::map<UINT64, bool> mCollisionMap;
		static double mTime;
	};

}

