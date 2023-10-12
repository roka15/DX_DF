#pragma once
#include "SingleTon.h"
namespace roka
{
	class GameObject;
	enum class EGaugeType
	{
		PlayerHP,
		PlayerMP,
		NormalMonsterHP,
	};
	class GaugeManager :
		public Singleton<GaugeManager>
	{
	public:
		void RegisterGaugeObject(EGaugeType type, std::shared_ptr<GameObject> obj);
		void UseGauge(EGaugeType type, float damage, float max);
		
	private:
		std::map<EGaugeType, std::weak_ptr<GameObject>> mGaugeObjects;
	};
}


