#include "NormalMonsterScript.h"
#include "GameObject.h"

#include "Transform.h"
#include "Collider2D.h"
#include "Animator.h"

#include "SkillScript.h"
namespace roka
{
    NormalMonsterScript::NormalMonsterScript():MonsterScript(EScriptType::NormalMonster)
    {
    }
    NormalMonsterScript::NormalMonsterScript(EScriptType type):MonsterScript(type)
    {
    }
    NormalMonsterScript::NormalMonsterScript(EScriptType type, const UINT ActiveSkillStateMaxCnt, const Vector2 LeftColCenter, const Vector2 RightColCenter, const Vector2 LeftShooterPos, const Vector2 RightShooterPos, const Vector2 SkillSize, const Vector2 SkillColCenter) : MonsterScript(type,ActiveSkillStateMaxCnt, LeftColCenter, RightColCenter)
    {
    }
    NormalMonsterScript::NormalMonsterScript(const NormalMonsterScript& ref):MonsterScript(ref)
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
    }
    void NormalMonsterScript::SetTargetPos(Vector2& outDir, Vector2& outTargetPos)
    {
    }
    void NormalMonsterScript::LeftSetting()
    { 
        MonsterScript::LeftSetting();
    }
    void NormalMonsterScript::RightSetting()
    {  
        MonsterScript::RightSetting();
    }
  
}