#pragma once
#include "Script.h"
namespace roka
{
    class ChangeSizeOverTime :
        public Script
    {
    protected:
        ChangeSizeOverTime();
        ChangeSizeOverTime(const ChangeSizeOverTime& ref);
        virtual void Copy(Component* src);
    public:
        virtual ~ChangeSizeOverTime() {}
        virtual void Initialize()override;
        virtual void Update() override;
   
        void SetOffset(Vector3 offset) { mOffset = offset; }
        void SetAlphaType(EAlphaType type) { mAlphaType = type; }
        void SetAlphaOffset(float alpha) { mAlpha = alpha; }
        void EndTime(double time) { mEndTime = time; }
        std::function<void()>& SetEndEvent() { return mEndEvent; }
    private:
        friend class FactoryBase;
        friend class ScriptFactory;
    protected:
        Vector3 mOffset;
        float mAlpha;
        EAlphaType mAlphaType;
        double mCurTime;
        double mEndTime;
        std::function<void()> mEndEvent;
    };
}


