#include "GaugeScript.h"
#include "Renderer.h"
namespace roka
{
	GaugeScript::GaugeScript() :Script(EScriptType::Gauge),
		mRatioValue(0.1f),
		mRatio(0.0f),
		mMax(0.0f),
		mDamage(0.0f)
	{
	}
	GaugeScript::GaugeScript(const GaugeScript& ref) :Script(ref),
		mRatioValue(0.1f)
	{
	}
	void GaugeScript::Copy(Component* src)
	{
		GaugeScript* source = dynamic_cast<GaugeScript*>(src);
		if (source == nullptr)
			return;
	}
	void GaugeScript::Initialize()
	{
	}
	void GaugeScript::Update()
	{

		if (mDamage < 0)
		{
			if (mRatio >= mDamage)
				mRatio -= mRatioValue;
		}
		else
		{
			if (mRatio <= mDamage)
				mRatio += mRatioValue;
		}

	}
	void GaugeScript::LateUpdate()
	{
	}
	void GaugeScript::Render()
	{
	}
	void GaugeScript::Add(float max, float damage)
	{
		mMax = max;
		mDamage += damage;
	}
	void GaugeScript::Bind()
	{
		if (mDamage == 0.0 && mMax == 0.0)
			return;
		ConstantBuffer* cb = renderer::constantBuffer[(UINT)ECBType::Gauge];
		renderer::GaugeCB data = {};
		data.damage = mDamage;
		data.maxGauge = mMax;
		data.ratio = mRatio;
		data.type = (UINT)GaugeType::Virtical;
		cb->SetData(&data);
		cb->Bind(EShaderStage::PS);
	}
}