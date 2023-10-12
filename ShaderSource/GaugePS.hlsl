#include "globals.hlsli"

struct VSIn
{
	float3 Pos : POSITION;
	float4 Color : COLOR;
	float2 UV : TEXCOORD;
};

struct VSOut
{
	float4 Pos : SV_Position;
	float3 WorldPos : POSITION;
	float4 Color : COLOR;
	float2 UV : TEXCOORD;
};


float4 main(VSOut In) : SV_TARGET
{
	float4 color = (float4) 1.0f;
	//color = atlasTexture.Sample(pointSampler, In.UV);
	float2 UV = LeftTop + (ViewSize * In.UV);

	if (UV.x < LeftTop.x + Offset.x || UV.x >= LeftTop.x + Offset.x + Size.x
		|| UV.y < LeftTop.y + Offset.y || UV.y >= LeftTop.y + Offset.y + Size.y)
		discard;

	color = atlasTexture.Sample(pointSampler, UV);



	float4 lightColor = float4(0.2f, 0.2f, 0.2f, 1.0f);

	for (int i = 0; i < 2; i++)
	{
		CalculateLight2D(lightColor, In.WorldPos, i);
	}

	color *= lightColor;

	if (Gaugetype == 1)
	{
		float damage = Gaugeratio;

		if (damage < 0.0)
			damage *= -1;

		// 데미지 * 0.65 / 100 하기.
		float result = saturate(damage * 0.65 / maxGauge);

		if (UV.y <= result)
			color.a = 0.0f;
	}
	

	return color;
}