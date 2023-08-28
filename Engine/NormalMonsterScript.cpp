#include "NormalMonsterScript.h"
#include "GameObject.h"

#include "Transform.h"
#include "Collider2D.h"
#include "Animator.h"
namespace roka
{
    NormalMonsterScript::NormalMonsterScript():MonsterScript(EScriptType::NormalMonster)
    {
    }
    NormalMonsterScript::NormalMonsterScript(EScriptType type):MonsterScript(type)
    {
    }
    NormalMonsterScript::NormalMonsterScript(EScriptType type, const UINT ActiveSkillStateMaxCnt, const Vector2 LeftColCenter, const Vector2 RightColCenter, const Vector2 LeftShooterPos, const Vector2 RightShooterPos, const Vector2 SkillSize, const Vector2 SkillColCenter) : MonsterScript(type,ActiveSkillStateMaxCnt, LeftColCenter, RightColCenter),
        mLeftShooterPos(LeftShooterPos),
        mRightShooterPos(RightShooterPos),
        mSkillSize(SkillSize),
        mSkillColCenter(SkillColCenter)
    {
    }
    NormalMonsterScript::NormalMonsterScript(const NormalMonsterScript& ref):MonsterScript(ref),
        mLeftShooterPos(ref.mLeftShooterPos),
        mRightShooterPos(ref.mRightShooterPos),
        mSkillSize(ref.mSkillSize),
        mSkillColCenter(ref.mSkillColCenter)
    {
    }
    void NormalMonsterScript::Copy(Component* src)
    {
        MonsterScript::Copy(src);
        NormalMonsterScript* source = dynamic_cast<NormalMonsterScript*>(src);
    }
    void NormalMonsterScript::Initialize()
    {
        MonsterScript::Initialize();
    }
    void NormalMonsterScript::Update()
    {
        MonsterScript::Update();
    }
    void NormalMonsterScript::LateUpdate()
    {
        MonsterScript::LateUpdate();
    }
    void NormalMonsterScript::Render()
    {
        MonsterScript::Render();
    }
    void NormalMonsterScript::OnCollisionEnter(std::shared_ptr<Collider2D> other)
    {
        MonsterScript::OnCollisionEnter(other);
    }
    void NormalMonsterScript::OnCollisionStay(std::shared_ptr<Collider2D> other)
    {
        MonsterScript::OnCollisionStay(other);
    }
    void NormalMonsterScript::OnCollisionExit(std::shared_ptr<Collider2D> other)
    {
        MonsterScript::OnCollisionExit(other);
    }
    void NormalMonsterScript::Ready()
    {
        MonsterScript::Ready();
    }
    void NormalMonsterScript::Idle()
    {
        MonsterScript::Idle();
    }
    void NormalMonsterScript::Move()
    {
        MonsterScript::Move();
    }
    void NormalMonsterScript::Attack()
    {
        MonsterScript::Attack();
        Skill01();
    }
    void NormalMonsterScript::SetTargetPos(Vector2& outDir, Vector2& outTargetPos)
    {
    }
    void NormalMonsterScript::LeftSetting()
    { 
        MonsterScript::LeftSetting();

        std::shared_ptr<GameObject> skill = owner->GetChild(L"skill01");
        std::shared_ptr<Transform> tf = skill->GetComponent<Transform>();
        Vector3 pos = tf->position;
        float z = tf->position.z;
        tf->position = Vector3(mLeftShooterPos.x, mLeftShooterPos.y, z);
        std::shared_ptr<Collider2D>skill_col = skill->GetComponent<Collider2D>();
        Vector2 skill_colCenter = skill_col->center;
        skill_colCenter.x = -mSkillColCenter.x;
        skill_col->center = skill_colCenter;
    }
    void NormalMonsterScript::RightSetting()
    {
        MonsterScript::RightSetting();

        std::shared_ptr<GameObject> skill = owner->GetChild(L"skill01");
        std::shared_ptr<Transform> tf = skill->GetComponent<Transform>();
        float z = tf->position.z;
        tf->position = Vector3(mRightShooterPos.x, mRightShooterPos.y, z);
        std::shared_ptr<Collider2D>skill_col = skill->GetComponent<Collider2D>();
        Vector2 skill_colCenter = skill_col->center;
        skill_colCenter.x = mSkillColCenter.x;
        skill_col->center = skill_colCenter;
    }
    void NormalMonsterScript::Skill01()
    {
    }
}