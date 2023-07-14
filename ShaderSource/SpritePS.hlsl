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
    //return In.Color;
    float4 color = (float4)0.0f;
   
    color = albedoTexture.Sample(pointSampler, In.UV);
    return color;
}