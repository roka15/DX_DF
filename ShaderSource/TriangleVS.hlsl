#include "Globals.hlsli"

struct VSIn
{
	float3 pos:POSITION;
	float4 color:COLOR; 
	float2 UV:TEXCOORD;
};
struct VSOut
{
	float4 pos:SV_POSITION;
	float4 color:COLOR;
	float2 UV:TEXCOORD;
};

VSOut main( VSIn In )
{
	VSOut outData = (VSOut)0.0f;
	outData.pos = float4(In.pos, 1.0f);
	/*outData.pos.x += Pos.x;
	outData.pos.y += Pos.y;*/

	outData.UV = In.UV;
	outData.color = In.color;
	return outData;
}