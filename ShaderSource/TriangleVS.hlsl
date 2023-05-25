

struct VSIn
{
	float3 pos:POSITION;
	float4 color:COLOR;
};
struct VSOut
{
	float4 pos:SV_POSITION;
	float4 color:COLOR;
};

VSOut main( VSIn In )
{
	VSOut outData = (VSOut)0.0f;
	outData.pos = float4(In.pos, 1.0f);
	outData.color = In.color;

	return outData;
}