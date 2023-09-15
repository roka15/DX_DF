#pragma once
#include "NormalMonsterScript.h"
namespace roka
{
    class SpiderMonsterScript :
        public NormalMonsterScript
    {
    protected:
        SpiderMonsterScript();
        SpiderMonsterScript(const SpiderMonsterScript& ref);
        virtual void Copy(Component* src)override;
    public:
        ~SpiderMonsterScript() {}

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Render() override;


        virtual void Ready()override;
        virtual void Idle()override;
        virtual void Move()override;
        virtual void Attack()override;
  

        virtual void SetTargetPos(Vector2& outDir, Vector2& outTargetPos)override;

        virtual void LeftSetting()override;
        virtual void RightSetting()override;

    private:
        friend class FactoryBase;
        friend class ScriptFactory;
    private:
    };
}

