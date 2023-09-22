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
	float2 UV = AniLeftTop + (ViewSize * In.UV);

	if (UV.x < AniLeftTop.x || UV.x > AniLeftTop.x + AniSize.x
		|| UV.y < AniLeftTop.y || UV.y > AniLeftTop.y + AniSize.y)
		discard;

	color = atlasTexture.Sample(pointSampler, UV);



	float4 lightColor = float4(0.2f, 0.2f, 0.2f, 1.0f);

	for (int i = 0; i < 2; i++)
	{
		CalculateLight2D(lightColor, In.WorldPos, i);
	}

	color *= lightColor;
	if (color.x != 0.0f && color.y != 0.0f && color.z != 0.0f&&color.w !=1.0f)
	{
		color.w = alpha;
	}

	color.xyz *= alpha;

	return color;
}