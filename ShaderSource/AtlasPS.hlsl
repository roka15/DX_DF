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

	if (UV.x < LeftTop.x+Offset.x|| UV.x >= LeftTop.x +Offset.x+ Size.x
		|| UV.y < LeftTop.y+Offset.y || UV.y >= LeftTop.y +Offset.y+ Size.y)
		discard;
	
	color = atlasTexture.Sample(pointSampler, UV);



	float4 lightColor = float4(0.2f, 0.2f, 0.2f, 1.0f);

	for (int i = 0; i < 2; i++)
	{
		CalculateLight2D(lightColor, In.WorldPos, i);
	}

	color *= lightColor;
	
	if ((!(flag&0x1))&& (flag&0x2))// oneone ==false && change alpha ==true
	{
		if (color.x != 0.0f && color.y != 0.0f && color.z != 0.0f)
		{
			color.w = alpha;
		}
	}


	color.xyz *= alpha;

	return color;
}