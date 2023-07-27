#pragma once
#include "Script.h"
namespace roka
{
    class Slot :
        public Script
    {
    public:
        virtual void Initialize() override;
        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Render() override;
    private:

    };

}


