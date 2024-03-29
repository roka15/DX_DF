#include "SpiderMonsterScript.h"

#include "GameObject.h"
#include "Animator.h"
#include "MeshRenderer.h"
#include "Collider2D.h"
#include "Transform.h"
#include "Camera.h"
#include "NPK.h"

#include "TargetMoveScript.h"


#include "Resources.h"
#include "Application.h"
#include "RokaTime.h"


extern roka::Application application;
namespace roka
{
	SpiderMonsterScript::SpiderMonsterScript() :NormalMonsterScript(
		EScriptType::SpiderMonster,
		4, 
		Vector2(0.085f, -0.1f),
		Vector2(-0.05f, -0.1f), 
		Vector2(-2.15f, 0.025f),
		Vector2(2.15f, 0.025f),
		Vector2(3.0f, 0.05f),
		Vector2(8.5f, 0.025f))
	{
	}
	SpiderMonsterScript::SpiderMonsterScript(const SpiderMonsterScript& ref) : NormalMonsterScript(ref)
	{
	}
	void SpiderMonsterScript::Copy(Component* src)
	{
		NormalMonsterScript::Copy(src);
		SpiderMonsterScript* source = dynamic_cast<SpiderMonsterScript*>(src);
	}
	void SpiderMonsterScript::Initialize()
	{
		mMonsterType = EMonsterType::Spider;
		NormalMonsterScript::Initialize();

		std::shared_ptr<Animator> ani = owner->GetComponent<Animator>();
		std::shared_ptr<NPK> npk = Resources::Find<NPK>(L"monster");
		std::shared_ptr<Texture> texture1 = npk->CreateAtlas(L"web_spider_z.img",0,28,L"MonsterSpiderZ01");
		ani->Create(texture1,L"Idle", 0, 5, 0.2f);
		ani->Create(texture1,L"Walk", 5, 13, 0.2f);
		std::shared_ptr<Texture> texture2 = npk->CreateAtlas(L"web_spider_z.img", 28, 50, L"MonsterSpiderZ02");
		ani->Create(texture2, L"Skill01", 0, 19, 0.1f);

		std::shared_ptr<Animation> animation = ani->FindAnimation(L"Skill01");
		animation->RegisterFrameEvent(L"SpawnEffect01", 11);
		animation->RegisterFrameEvent(L"DeSpawnEffect01", 17);
		animation->RegisterFrameEvent(L"NextState", 18);
		Idle();
	}
	void SpiderMonsterScript::Update()
	{
		NormalMonsterScript::Update();
	}
	void SpiderMonsterScript::LateUpdate()
	{
		NormalMonsterScript::LateUpdate();
	}
	void SpiderMonsterScript::Render()
	{
		NormalMonsterScript::Render();
	}
	void SpiderMonsterScript::Ready()
	{
		NormalMonsterScript::Ready();
	}
	void SpiderMonsterScript::Idle()
	{
		NormalMonsterScript::Idle();
		std::shared_ptr<Animator> ani = owner->GetComponent<Animator>();
		ani->PlayAnimation(L"web_spider_Idle", true);
	}
	void SpiderMonsterScript::Move()
	{
		std::shared_ptr<Animator> ani = owner->GetComponent<Animator>();
		ani->PlayAnimation(L"web_spider_Walk", true);
		NormalMonsterScript::Move();
	}
	void SpiderMonsterScript::Attack()
	{
		NormalMonsterScript::Attack();
	}
	void SpiderMonsterScript::SetTargetPos(Vector2& outDir, Vector2& outTargetPos)
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
			Vector2 Distance = { (float)(rand() % AspectRatioX),(float)(rand() % AspectRatioY) };
			if (Distance.x < AspectRatioX / 2.0f)
				Distance.x *= -1;
			if (Distance.y < AspectRatioY / 2.0f)
				Distance.y *= -1;

			Distance.x /= AspectRatioX / 2.0f;
			Distance.y /= AspectRatioY / 2.0f;

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
				projectPos.y < 400.0f)
			{
				continue;
			}
			else
				break;
		}
		outDir = Vector2(DirX, DirY);
		outTargetPos = Vector2(FinalTargetPos.x, FinalTargetPos.y);
	}
	void SpiderMonsterScript::LeftSetting()
	{
		NormalMonsterScript::LeftSetting();
	}
	void SpiderMonsterScript::RightSetting()
	{
		NormalMonsterScript::RightSetting();
	}
}