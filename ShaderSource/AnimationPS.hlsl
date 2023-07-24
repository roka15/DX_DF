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
	float4 Color : COLOR;
	float2 UV : TEXCOORD;
};


float4 main(VSOut In) : SV_TARGET
{
	float4 color = (float4) 1.0f;
	//color = atlasTexture.Sample(pointSampler, In.UV);
	float2 diff = (ViewSize - AniSize) / 2.0f;
	float2 UV = AniLeftTop + (ViewSize * In.UV);

	/*if (UV.x < AniLeftTop.x || UV.x > AniLeftTop.x + AniSize.x
		|| UV.y < AniLeftTop.y || UV.y > AniLeftTop.y + AniSize.y)
		discard;*/

	color = atlasTexture.Sample(pointSampler, UV);

	return color;
}