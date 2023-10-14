#include "CollisionManager.h"
#include "SceneManager.h"

#include "Collider2D.h"
#include "Transform.h"
#include "RokaTime.h"
#include "Camera.h"
namespace roka
{
	std::bitset<LAYER_MAX>  CollisionManager::mMatrix[LAYER_MAX] = {};
	std::map<UINT64, bool> CollisionManager::mCollisionMap = {};
	std::queue<std::pair<std::shared_ptr<Collider2D>, std::shared_ptr<Collider2D>>> CollisionManager::mExitRequest;
	bool CollisionManager::mbBreak;
	double CollisionManager::mTime;

	void CollisionManager::Initialize()
	{
	}
	void CollisionManager::Update()
	{
		mTime += Time::DeltaTime();

		for (UINT column = 0; column < (UINT)ELayerType::End; column++)
		{
			for (UINT row = 0; row < (UINT)ELayerType::End; row++)
			{
				if (mMatrix[column][row] == true)
				{
					LayerCollision((ELayerType)column, (ELayerType)row);
					if (mbBreak)
					{
						mbBreak = false;
						return;
					}
				}
			}
		}
	}
	void CollisionManager::LateUpdate()
	{
		while (mExitRequest.empty() == false)
		{
			std::pair<std::shared_ptr<Collider2D>, std::shared_ptr<Collider2D>> value
				= mExitRequest.front();
			mExitRequest.pop();
			std::shared_ptr<Collider2D> left = value.first;
			std::shared_ptr<Collider2D> right = value.second;

			ColliderID id = {};
			id.left = left->GetColliderID();
			id.right = right->GetColliderID();

			std::map<UINT64, bool>::iterator itr
				= mCollisionMap.find(id.id);

			if (itr == mCollisionMap.end())
				return;
			if (itr->second == false)
				return;

			itr->second = false;
			left->OnCollisionExit(right);
			right->OnCollisionExit(left);
		}

	}
	void CollisionManager::LayerCollision(ELayerType left, ELayerType right)
	{
		Scene* scene = SceneManager::GetActiveScene();

		std::vector<std::shared_ptr<GameObject>> lefts
			= SceneManager::FindGameObjects(left);
		std::vector<std::shared_ptr<GameObject>> rights
			= SceneManager::FindGameObjects(right);

		std::vector<std::shared_ptr<Collider2D>> leftCols = {};
		std::vector<std::shared_ptr<Collider2D>> rightCols = {};

		for (std::shared_ptr<GameObject>& leftObj : lefts)
		{
			FindCollider(leftObj, leftCols);
			if (leftCols.size() == 0)
				continue;

			for (std::shared_ptr<GameObject>& rightObj : rights)
			{
				if (leftObj == rightObj)
					continue;

				FindCollider(rightObj, rightCols);
				if (rightCols.size() == 0)
					continue;

				for (int i = 0; i < leftCols.size(); i++)
				{
					for (int j = 0; j < rightCols.size(); j++)
					{
						ColliderCollision(leftCols[i], rightCols[j]);
						if (mbBreak)
							return;
					}
				}
				rightCols.clear();
			}
			leftCols.clear();
		}
	}
	void CollisionManager::ColliderCollision(std::shared_ptr<Collider2D> left, std::shared_ptr<Collider2D> right)
	{
		ColliderID id = {};
		id.left = left->GetColliderID();
		id.right = right->GetColliderID();

		ELayerType leftType = left->owner->layer_type;
		ELayerType RightType = right->owner->layer_type;

		std::map<UINT64, bool>::iterator itr
			= mCollisionMap.find(id.id);
		if (itr == mCollisionMap.end())
		{
			mCollisionMap.insert(std::make_pair(id.id, false));
			itr = mCollisionMap.find(id.id);
		}

		if (Intersect(left, right))
		{
			if (itr->second == false)
			{
				if (left->owner->active != GameObject::EState::Active ||
					right->owner->active != GameObject::EState::Active)
					return;
				left->OnCollisionEnter(right);
				right->OnCollisionEnter(left);
				left->time = mTime;
				right->time = mTime;
				if (mbBreak)
					return;
			}
			else
			{
				if (left->owner->active != GameObject::EState::Active ||
					right->owner->active != GameObject::EState::Active)
				{
					left->OnCollisionExit(right);
					right->OnCollisionExit(left);
					itr->second = false;
					return;
				}
				left->OnCollisionStay(right);
				right->OnCollisionStay(left);
				left->time = mTime;
				right->time = mTime;
				if (mbBreak)
					return;
			}
			itr->second = true;
		}
		else
		{
			if (itr->second == true)
			{
				left->OnCollisionExit(right);
				right->OnCollisionExit(left);
			}
			itr->second = false;
		}
	}
	bool CollisionManager::CollisionCheck(std::shared_ptr<Collider2D> left, std::shared_ptr<Collider2D> right)
	{
		ColliderID id = {};
		id.left = left->collider_id;
		id.right = right->collider_id;
		if (mCollisionMap.find(id.id) != mCollisionMap.end())
			return mCollisionMap[id.id];
		return false;
	}
	bool CollisionManager::Intersect(std::shared_ptr<Collider2D> left, std::shared_ptr<Collider2D> right)
	{
		if (left->owner->GetName().compare(L"ScrollView") == 0 ||
			right->owner->GetName().compare(L"ScrollView") == 0)
			int a = 0;
		Vector3 LocalPos[4] =
		{
			Vector3{-0.5f,0.5f,0.0f},
			Vector3{0.5f,0.5f,0.0f},
			Vector3{0.5f,-0.5f,0.0f},
			Vector3{-0.5f,-0.5f,0.0f}
		};
		Vector3 Axis[4] = {};

		std::shared_ptr<Transform> leftTf = left->owner->GetComponent<Transform>();
		std::shared_ptr<Transform> rightTf = right->owner->GetComponent<Transform>();

		Matrix scale = Matrix::CreateScale(leftTf->GetLocalScale() * left->size);
		Matrix rotation = Matrix::CreateRotationX(leftTf->rotation.x);
		rotation *= Matrix::CreateRotationY(leftTf->rotation.y);
		rotation *= Matrix::CreateRotationZ(left->GetRotation() + leftTf->rotation.z);
		Matrix position = Matrix::CreateTranslation(leftTf->GetLocalPosition() + left->center);
		Matrix parentMat = {};
		Matrix leftMat = scale * rotation * position;
		if (left->owner->parent != nullptr)
		{
			parentMat = left->owner->parent->GetComponent<Transform>()->GetMatrix();
			leftMat *= parentMat;
		}
		scale = Matrix::CreateScale(rightTf->GetLocalScale() * right->size);
		rotation = Matrix::CreateRotationX(rightTf->rotation.x);
		rotation *= Matrix::CreateRotationY(rightTf->rotation.y);
		rotation *= Matrix::CreateRotationZ(right->GetRotation() + rightTf->rotation.z);
		position = Matrix::CreateTranslation(rightTf->GetLocalPosition() + right->center);
		
		Matrix rightMat = scale * rotation * position;
		if (right->owner->parent != nullptr)
		{
			parentMat = right->owner->parent->GetComponent<Transform>()->GetMatrix();
			rightMat *= parentMat;
		}
	

		//Matrix scale = Matrix::CreateScale(leftTf->scale);
		//Matrix rotation = Matrix::CreateRotationX(leftTf->rotation.x);
		//rotation *= Matrix::CreateRotationY(leftTf->rotation.y);
		//rotation *= Matrix::CreateRotationZ(left->GetRotation() + leftTf->rotation.z);
		//Matrix position;
		//position.Translation(leftTf->position);
		//Matrix leftMat = scale * rotation * position;

		//scale = Matrix::CreateScale(rightTf->scale);
		//rotation = Matrix::CreateRotationX(rightTf->rotation.x);
		//rotation *= Matrix::CreateRotationY(rightTf->rotation.y);
		//rotation *= Matrix::CreateRotationZ(right->GetRotation() + rightTf->rotation.z);
		//position.Translation(rightTf->position);
		//Matrix rightMat = scale * rotation * position;

		

		//Vector3 leftScale = Vector3(left->size.x, left->size.y, 1.0f);
		//Vector3 leftOffset = Vector3(left->center.x * leftTf->scale.x, left->center.y * leftTf->scale.y, 0.0f);
		//Matrix finalLeft = Matrix::CreateScale(leftScale);
		//if (leftTf->rotation.z != 0.0f)
		//{
		//	Vector3 tempOffset = leftOffset;
		//	tempOffset.x = (leftOffset.x * cos(leftTf->rotation.z)) - (leftOffset.y * sin(leftTf->rotation.z));
		//	tempOffset.y = (leftOffset.x * sin(leftTf->rotation.z)) + (leftOffset.y * cos(leftTf->rotation.z));
		//	leftOffset = tempOffset;
		//}
		///*	leftTranslate += leftOffset;
		//	leftMat = Matrix::CreateTranslation(leftTranslate);*/
		//finalLeft *= leftMat;

		//Vector3 rightScale = Vector3(right->size.x, right->size.y, 1.0f);
		//Vector3 rightOffset = Vector3(right->center.x * rightTf->scale.x, right->center.y * rightTf->scale.y, 0.0f);
		//Matrix finalRight = Matrix::CreateScale(rightScale);
		//if (rightTf->rotation.z != 0.0f)
		//{
		//	Vector3 tempOffset = rightOffset;
		//	tempOffset.x = (rightOffset.x * cos(rightTf->rotation.z)) - (rightOffset.y * sin(rightTf->rotation.z));
		//	tempOffset.y = (rightOffset.x * sin(rightTf->rotation.z)) + (rightOffset.y * cos(rightTf->rotation.z));
		//	rightOffset = tempOffset;
		//}
		///*rightTranslate += rightOffset;
		//rightMat = Matrix::CreateTranslation(rightTranslate);*/
		//finalRight *= rightMat;

	/*	Axis[0] = Vector3::Transform(LocalPos[1], finalLeft);
		Axis[1] = Vector3::Transform(LocalPos[3], finalLeft);
		Axis[2] = Vector3::Transform(LocalPos[1], finalRight);
		Axis[3] = Vector3::Transform(LocalPos[3], finalRight);

		Axis[0] -= Vector3::Transform(LocalPos[0], finalLeft);
		Axis[1] -= Vector3::Transform(LocalPos[0], finalLeft);
		Axis[2] -= Vector3::Transform(LocalPos[0], finalRight);
		Axis[3] -= Vector3::Transform(LocalPos[0], finalRight);*/

		/*for (size_t i = 0; i < 4; i++)
		{
			Axis[i].z = 0.0f;
		}

		Vector3 leftpos = {};
		Vector3 rightpos = {};
		if (leftTf->owner->GetName().compare(L"LayserObject") == 0
			|| rightTf->owner->GetName().compare(L"LayserObject") == 0)
			int a = 0;
		leftpos = leftTf->position + leftOffset;
		rightpos = rightTf->position + rightOffset;
		Vector3 vc = leftpos - rightpos;
		vc.z = 0.0f;

		Vector3 centerDir = vc;
		for (size_t i = 0; i < 4; i++)
		{
			Vector3 vA = Axis[i];
			float projDistance = 0.0f;
			for (size_t j = 0; j < 4; j++)
			{
				projDistance += fabsf(Axis[j].Dot(vA) / 2.0f);
			}
			float temp = centerDir.Dot(vA);
			if (projDistance < fabsf(centerDir.Dot(vA)))
				return false;
		}*/

		Axis[0] = Vector3::Transform(LocalPos[1], leftMat);
		Axis[1] = Vector3::Transform(LocalPos[3], leftMat);
		Axis[2] = Vector3::Transform(LocalPos[1], rightMat);
		Axis[3] = Vector3::Transform(LocalPos[3], rightMat);

		Axis[0] -= Vector3::Transform(LocalPos[0], leftMat);
		Axis[1] -= Vector3::Transform(LocalPos[0], leftMat);
		Axis[2] -= Vector3::Transform(LocalPos[0], rightMat);
		Axis[3] -= Vector3::Transform(LocalPos[0], rightMat);

		for (size_t i = 0; i < 4; i++)
		{
			Axis[i].z = 0.0f;
		}
		Vector3 leftpos = {leftMat._41,leftMat._42,leftMat._43};
		Vector3 rightpos = { rightMat._41,rightMat._42,rightMat._43 };
		Vector3 vc = leftpos - rightpos;
		vc.z = 0.0f;
		Vector3 centerDir = vc;
		for (size_t i = 0; i < 4; i++)
		{
			Vector3 vA = Axis[i];
			float projDistance = 0.0f;
			for (size_t j = 0; j < 4; j++)
			{
				projDistance += fabsf(Axis[j].Dot(vA) / 2.0f);
			}
			float temp = centerDir.Dot(vA);
			if (projDistance < fabsf(centerDir.Dot(vA)))
				return false;
		}
		
		return true;
	}
	std::vector<std::shared_ptr<GameObject>> CollisionManager::GetCollisionObjects(std::shared_ptr<GameObject>& obj)
	{
		std::vector<std::shared_ptr<GameObject>> objs;

		ELayerType layerType = obj->layer_type;
		std::shared_ptr<Collider2D> collider = obj->GetComponent<Collider2D>();
		if (collider == nullptr)
			return objs;

		for (UINT row = 0; row < (UINT)ELayerType::End; row++)
		{
			if (row == (UINT)layerType)
				continue;
			if ((UINT)layerType < row)
			{
				if (mMatrix[row][(UINT)layerType] == true)
				{
					std::vector<std::shared_ptr<GameObject>> vec = SceneManager::FindGameObjects((ELayerType)row);
					for (auto itr : vec)
					{
						std::vector<std::shared_ptr<Collider2D>> cols = {};
						FindCollider(itr, cols);
						for (auto col : cols)
						{
							bool flag = false;
							flag = CollisionCheck(col, collider);
							if (flag)
							{
								objs.push_back(col->owner->GetSharedPtr());
							}
						}

					}
				}
			}
			else
			{
				if (mMatrix[(UINT)layerType][row] == true)
				{
					std::vector<std::shared_ptr<GameObject>> vec = SceneManager::FindGameObjects((ELayerType)row);
					for (auto itr : vec)
					{
						std::vector<std::shared_ptr<Collider2D>> cols = {};
						FindCollider(itr, cols);
						for (auto col : cols)
						{
							bool flag = false;
							flag = CollisionCheck(collider, col);
							if (flag)
							{
								objs.push_back(col->owner->GetSharedPtr());
							}
						}

					}

				}
			}
		}
		std::sort(objs.begin(), objs.end(), CompareReverseZSort);
		return objs;
	}
	void CollisionManager::DisableCollision(std::shared_ptr<Collider2D> left, std::shared_ptr<Collider2D> right)
	{
		mExitRequest.push(std::make_pair(left, right));
	}
	void CollisionManager::SetLayer(ELayerType left, ELayerType right, bool enable)
	{
		UINT row = -1;
		UINT col = -1;
		UINT iLeft = (UINT)left;
		UINT iRight = (UINT)right;

		if (iLeft <= iRight)
		{
			row = iLeft;
			col = iRight;
		}
		else
		{
			row = iRight;
			col = iLeft;
		}
		mMatrix[col][row] = enable;
	}
	void CollisionManager::Clear()
	{
		mMatrix->reset();
		mCollisionMap.clear();
	}
	void CollisionManager::FindCollider(std::shared_ptr<GameObject> obj, std::vector<std::shared_ptr<Collider2D>>& cols)
	{
		std::shared_ptr<Collider2D> col = obj->GetComponent<Collider2D>();
		if (col != nullptr && col->is_active == true)
			cols.push_back(col);

		int cnt = obj->GetChildCont();
		if (cnt == 0)
			return;
		std::vector<std::shared_ptr<GameObject>> objs = obj->GetChilds();
		for (int i = 0; i < cnt; i++)
		{
			FindCollider(objs[i], cols);
		}

		return;
	}
	void CollisionManager::RegisterID(std::shared_ptr<Collider2D> left, std::shared_ptr<Collider2D> right)
	{
		//portal 이동 후 Scene 이동했을 때 다음 포탈 위에서 스폰될 것이기 때문에 과는 미리 enter 상태로 만들어 두기.
		ColliderID id = {};
		id.left = left->GetColliderID();
		id.right = right->GetColliderID();

		std::map<UINT64, bool>::iterator itr
			= mCollisionMap.find(id.id);
		if (itr == mCollisionMap.end())
		{
			mCollisionMap.insert(std::make_pair(id.id, false));
			itr = mCollisionMap.find(id.id);
		}
		itr->second = true;
		left->OnCollisionStay(right);
		right->OnCollisionStay(left);
	}
	void CollisionManager::DeleteID()
	{
		mbBreak = true;
		mCollisionMap.clear();
	}
}
