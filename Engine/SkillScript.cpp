#include "SkillScript.h"

namespace roka
{
    SkillScript::SkillScript():Script(EScriptType::SkillBase)
    {
    }
    SkillScript::SkillScript(const SkillScript& ref):Script(ref)
    {
        mStunType = ref.mStunType;
    }
    void SkillScript::Copy(Component* src)
    {
        SkillScript* source = dynamic_cast<SkillScript*>(src);
        mStunType = source->mStunType;
    }
    void SkillScript::Initialize()
    {
    }
    void SkillScript::Update()
    {
    }
    void SkillScript::LateUpdate()
    {
    }
    void SkillScript::Render()
    {
    }
}