#include "GaugeManager.h"
#include "GameObject.h"
#include "GaugeScript.h"
namespace roka
{
    void GaugeManager::RegisterGaugeObject(EGaugeType type, std::shared_ptr<GameObject> obj)
    {
        mGaugeObjects.insert(std::make_pair(type, obj));
    }
    void GaugeManager::UseGauge(EGaugeType type,float damage, float max)
    {
        auto itr = mGaugeObjects.find(type);
        
        if (itr == mGaugeObjects.end()) return;

        if (itr->second.expired() == true)
            return;
        itr->second.lock()->GetComponent<GaugeScript>()->Add(max,damage);
    }
}