#pragma once
#include "PartScript.h"
namespace roka
{
    class WeaponScript :
        public PartScript
    {
    private:
        WeaponScript();
        WeaponScript(const WeaponScript& ref);
        void Copy(Component* src);
    public:
        ~WeaponScript();

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Render() override;

        virtual void PlayPartMotion(std::wstring name, bool flag)override;

        virtual void CreateAni(std::wstring npk_name, std::wstring pack_name, std::wstring set_name, UINT start, UINT end, float duration)override;
     
        
        void RegisterSubPart(std::shared_ptr<GameObject> obj) { mSubPart = obj; }
    private:
        friend class FactoryBase;
        friend class ScriptFactory;

        std::weak_ptr<GameObject> mSubPart;
    };

}


