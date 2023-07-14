#include "Globals.hlsli"

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
	   float4 color = albedoTexture.Sample(anisotropicSampler, In.UV);
	   if (color.x == 0.0f && color.y == 0.0f && color.z == 0.0f && color.w == 1.0f)
	   {
		   color.w = 0.0f;
	   }
	   else if (abs(color.x - color.y) <= 0.6f && abs(color.x - color.z) <= 0.6f)
	   {
		   if (color.x != 1.0f && color.y != 1.0f && color.z != 1.0f
			   && color.x <= 0.3)
		   {
			   color.x = 1.0f;
			   color.y = 1.0f;
			   color.z = 1.0f;
			   color.w = 0.05f;
		   }
	   }
	 /*  float4 result = color + In.Color;
	   result = saturate(result);*/
	  
		return color;
}