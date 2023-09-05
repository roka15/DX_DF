#pragma once
#include "SkillScript.h"

namespace roka
{
    class LayserSkillScript :
        public SkillScript
    {
    protected:
        LayserSkillScript();
        LayserSkillScript(EScriptType type);
        LayserSkillScript(const LayserSkillScript& ref);
        void Copy(Component* src);
    public:
        virtual ~LayserSkillScript();

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Render() override;

        virtual void OnCollisionEnter(std::shared_ptr<Collider2D> other) {}
        virtual void OnCollisionStay(std::shared_ptr<Collider2D> other) {}
        virtual void OnCollisionExit(std::shared_ptr<Collider2D> other) {}

        virtual void Play();
        virtual void Exit();

        virtual void Start()override {}
        virtual void Middle()override {}
        virtual void End()override {}
    private:
        friend class FactoryBase;
        friend class ScriptFactory;
    protected:
        Vector3 mLayserSize;
        Vector3 mLayserSpawnPos;

        std::shared_ptr<GameObject> mLayserObj;
    };
}



