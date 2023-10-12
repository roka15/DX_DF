#pragma once
#include "Script.h"
namespace roka
{
	class GaugeScript :
		public Script
	{
	protected:
		GaugeScript();
		GaugeScript(const GaugeScript& ref);
		virtual void Copy(Component* src);
	public:
		virtual ~GaugeScript() {}

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void Add(float max,float damage);
		
		void Bind();
	private:
		friend class FactoryBase;
		friend class ScriptFactory;

		float mRatio;
		const float mRatioValue;
		float mMax;
		float mDamage;
		bool mbSign;
		bool mbStart;
	};

}

