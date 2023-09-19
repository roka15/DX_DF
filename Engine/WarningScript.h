#pragma once
#include "Script.h"
namespace roka
{
    class WarningScript :
        public Script
    {
    protected:
        WarningScript();
        WarningScript(const WarningScript& ref);
        virtual void Copy(Component* src);
    public:
        virtual ~WarningScript() {}

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Render() override;

        void SetTarget(std::shared_ptr<GameObject> target) { mTarget = target; }
        void SetWarningSize(Vector3 size);
        void SetWarningCenter(Vector3 center) { mWarningCenter = center; }
        void SetPos(Vector3 pos) { mPos = pos; }
        void SetActiveTime(double time) { mActiveTime = time; }
        Vector3 GetPos() { return mPos; }
    private:
        friend class FactoryBase;
        friend class ScriptFactory;
    private:
        std::weak_ptr<GameObject> mTarget;
        Vector3 mWarningCenter;
        Vector3 mPos;
        double mActiveTime;
        double mTime;
    };
}


