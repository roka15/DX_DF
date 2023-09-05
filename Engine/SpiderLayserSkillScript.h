#pragma once
#include "LayserSkillScript.h"
namespace roka
{
    class SpiderLayserSkillScript :
        public LayserSkillScript
    {
    protected:
        SpiderLayserSkillScript();
        SpiderLayserSkillScript(const SpiderLayserSkillScript& ref);
        void Copy(Component* src);
    public:
        virtual ~SpiderLayserSkillScript() {}

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Render() override;

        virtual void OnCollisionEnter(std::shared_ptr<Collider2D> other)override;
        virtual void OnCollisionStay(std::shared_ptr<Collider2D> other)override;
        virtual void OnCollisionExit(std::shared_ptr<Collider2D> other)override;

        virtual void Play();
        virtual void Exit();

        virtual void Start()override;
        virtual void Middle() override;
        virtual void End()override;
    private:
        friend class FactoryBase;
        friend class ScriptFactory;
    private:
    };
}


