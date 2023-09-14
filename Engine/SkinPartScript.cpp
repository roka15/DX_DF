#include "SkinPartScript.h"

#include "NPK.h"
#include "GameObject.h"
#include "Resources.h"
#include "Texture.h"
#include "RokaTime.h"

#include "Animator.h"

namespace roka
{
    SkinPartScript::SkinPartScript():PartScript(EScriptType::PartSkin)
    {
    }
    SkinPartScript::SkinPartScript(const SkinPartScript& ref):PartScript(ref)
    {
    }
    void SkinPartScript::Copy(Component* src)
    {
        SkinPartScript* source = dynamic_cast<SkinPartScript*>(src);
        if (source == nullptr)
            return;
    }
    void SkinPartScript::Initialize()
    {
        PartScript::Initialize();
    }
    void SkinPartScript::Update()
    {
        PartScript::Update();
    }
    void SkinPartScript::LateUpdate()
    {
        PartScript::LateUpdate();
    }
    void SkinPartScript::Render()
    {
        PartScript::Render();
    }
    void SkinPartScript::JumpDash()
    {
        std::shared_ptr<Animator> ani = owner->GetComponent<Animator>();
        ani->PlayAnimation(L"Run",true);
    }
    void SkinPartScript::SetEvent()
    {
        std::shared_ptr<Animator> ani = owner->GetComponent<Animator>();
        ani->CompleteEvent(L"Landing") = std::bind(&SkinPartScript::NextState, this);
        ani->CompleteEvent(L"Down") = std::bind(&SkinPartScript::DownDelayEvent, this);
        ani->CompleteEvent(L"Standing") = std::bind(&SkinPartScript::StandingCompleteEvent, this);
        ani->CompleteEvent(L"Fall") = std::bind(&SkinPartScript::DisableMove, this);
        ani->CompleteEvent(L"Landing") = std::bind(&SkinPartScript::EnableMove, this);

        std::shared_ptr<Animation> animation;
        animation = ani->FindAnimation(L"Down");
        {
            Animation::AnimationEvent TimeEvent = {};
            TimeEvent.mTime = 0.4 * 2;
            TimeEvent.mNormalFunc = std::bind(&SkinPartScript::Stop, this);
        }
    }
    void SkinPartScript::Create(std::wstring npk, std::wstring pack)
    {
        mPartType = EAvatarParts::Base;
        std::shared_ptr<NPK> skin_npk = Resources::Find<NPK>(npk);
        if (skin_npk == nullptr)
            return;
        std::shared_ptr<Animator> ani = owner->GetComponent<Animator>();
        float speed = 0.05f;
        std::shared_ptr<Texture> idle_texture = skin_npk->CreateAtlas(pack, 0, 14, L"MgBaseIdleWalk");
        ani->Create(idle_texture, L"Idle", 10, 14, 0.3f);
        ani->Create(idle_texture, L"Walk", 0, 10, speed);
        std::shared_ptr<Texture> run_texture = skin_npk->CreateAtlas(pack, 18, 22, L"MgBaseRun");
        ani->Create(run_texture, L"Run", 0, 4, speed);
        std::shared_ptr<Texture> normalatk_texture = skin_npk->CreateAtlas(pack, 109, 128, L"MgBaseNormalAtk");
        ani->Create(normalatk_texture, L"NormalAtk", 0, 19, speed);
        std::shared_ptr<Texture> jump_texture = skin_npk->CreateAtlas(pack, 76, 87, L"MgBaseJump");
        ani->Create(jump_texture, L"Jump", 0, 4, speed);
        ani->Create(jump_texture, L"Fall", 4, 7, speed);
        ani->Create(jump_texture, L"Landing", 9, 11, speed);
        std::shared_ptr<Texture> stun_texter = skin_npk->CreateAtlas(pack, 128, 135, L"MgBaseStun");
        ani->Create(stun_texter, L"Stagger", 0,3, 0.1f);
        ani->Create(stun_texter, L"Down", 2, 7, 0.4f);
        std::shared_ptr<Texture> skill_texture = skin_npk->CreateAtlas(pack, 45, 75, L"MgBaseSkillPart1");
        std::shared_ptr<Texture> skill_texture2 = skin_npk->CreateAtlas(pack, 75, 105, L"MgBaseSkillPart2");
        std::shared_ptr<Texture> skill_texture3 = skin_npk->CreateAtlas(pack, 105, 114, L"MgBaseSkillPart3");
        ani->Create(skill_texture, L"Standing", 8, 9, 0.5f);


        std::shared_ptr<Animation> animation = ani->FindAnimation(L"NormalAtk");
        animation->RegisterFrameEvent(L"NextState", 4);
        animation->RegisterFrameEvent(L"NextState", 9);
        animation->RegisterFrameEvent(L"NextState", 18);
    }
}