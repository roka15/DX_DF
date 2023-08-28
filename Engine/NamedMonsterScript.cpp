#include "NamedMonsterScript.h"
#include "Application.h"
#include "Camera.h"
#include "GameObject.h"
#include "Transform.h"
extern roka::Application application;
namespace roka
{
	NamedMonsterScript::NamedMonsterScript() :MonsterScript(EScriptType::NamedMonster)
	{
	}
	NamedMonsterScript::NamedMonsterScript(EScriptType type) : MonsterScript(type)
	{
	}
	NamedMonsterScript::NamedMonsterScript(const NamedMonsterScript& ref)
	{
	}
	void NamedMonsterScript::Copy(Component* src)
	{
		MonsterScript::Copy(src);
		NamedMonsterScript* source = dynamic_cast<NamedMonsterScript*>(src);
		if (source == nullptr)
			return;

	}
	void NamedMonsterScript::Initialize()
	{
		MonsterScript::Initialize();
	}
	void NamedMonsterScript::Update()
	{
		MonsterScript::Update();
	}
	void NamedMonsterScript::LateUpdate()
	{
		MonsterScript::LateUpdate();
	}
	void NamedMonsterScript::Render()
	{
		MonsterScript::Render();
	}
	void NamedMonsterScript::OnCollisionEnter(std::shared_ptr<Collider2D> other)
	{
		MonsterScript::OnCollisionEnter(other);
	}
	void NamedMonsterScript::OnCollisionStay(std::shared_ptr<Collider2D> other)
	{
		MonsterScript::OnCollisionStay(other);
	}
	void NamedMonsterScript::OnCollisionExit(std::shared_ptr<Collider2D> other)
	{
		MonsterScript::OnCollisionExit(other);
	}
	void NamedMonsterScript::Ready()
	{
		MonsterScript::Ready();
	}
	void NamedMonsterScript::Idle()
	{
		MonsterScript::Idle();
	}
	void NamedMonsterScript::Move()
	{
		MonsterScript::Move();
	}
	void NamedMonsterScript::Attack()
	{
		MonsterScript::Attack();
		size_t count = mSkillStartList.size();
		if (count == 0)
			return;
		int index = 0;
		//test 끝나면 풀기
		/*while (1)
		{
			index = rand() % count;
			if (mBeforSkillIndex != index)
			{
				mBeforSkillIndex = index;
				break;
			}
		}*/

		mSkillStartList[index]();
	}
	void NamedMonsterScript::SetTargetPos(Vector2& outDir, Vector2& outTargetPos)
	{
		Vector3 targetPos = mTarget.lock()->GetComponent<Transform>()->position;
		Vector3 myPos = owner->GetComponent<Transform>()->position;
		Vector3 FinalTargetPos = {};

		UINT AspectRatioX = application.GetWidth();
		UINT AspectRatioY = application.GetHeight();
		float DirX = 0.0f;
		float DirY = 0.0f;
		while (1)
		{
			Vector2 Distance = { targetPos.x - myPos.x,targetPos.y - myPos.y };


			FinalTargetPos.x = myPos.x + Distance.x;
			FinalTargetPos.y = myPos.y + Distance.y;

			Distance.Normalize();

			DirX = Distance.x;
			DirY = Distance.y;

			if (Distance.x == 0.0f)
			{
				DirX = 0.0f;
			}
			if (Distance.y == 0.0f)
			{
				DirY = 0.0f;
			}

			if (Distance.x < 0.0f)
			{
				FinalTargetPos.x += 0.4f;
			}
			else if (Distance.x > 0.0f)
			{
				FinalTargetPos.x -= 0.4f;
			}

			Viewport view;
			view.width = AspectRatioX;
			view.height = AspectRatioY;
			view.x = 0;
			view.y = 0;
			view.minDepth = 0.0f;
			view.maxDepth = 1.0f;

			Vector3 projectPos = view.Project(FinalTargetPos, Camera::GetGpuProjectionMatrix(), Camera::GetGpuViewMatrix(), Matrix::Identity);

			if (projectPos.x > AspectRatioX ||
				projectPos.x < 0.0f ||
				projectPos.y >AspectRatioY ||
				projectPos.y < 0.0f)
			{
				continue;
			}
			else
				break;
		}
		outDir = Vector2(DirX, DirY);
		outTargetPos = Vector2(FinalTargetPos.x, FinalTargetPos.y);
	}
	void NamedMonsterScript::RegisterSkillFunc(std::function<void()> func)
	{
		mSkillStartList.push_back(func);
	}
}