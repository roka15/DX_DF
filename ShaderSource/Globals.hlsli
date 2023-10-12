
cbuffer Transform : register(b0)
{
	row_major matrix WorldMatrix;
	row_major matrix ViewMatrix;
	row_major matrix ProjectionMatrix;
}
cbuffer Material : register(b1)
{
	float4 Color;
}
cbuffer Grid : register(b2)
{
	float4 CameraPosition;
	float2 CameraScale;
	float2 Resolution;
}
cbuffer Altlas : register(b3)
{
	float2 LeftTop;
	float2 Size;
	float2 Offset;
	float2 ViewSize;
	float1 alpha;
	int flag;
	float2 padding;
}

cbuffer Gauge : register(b4)
{
	int Gaugetype;
	float damage;
	float maxGauge;
	float Gaugeratio;
}
struct LightAttribute
{
	float4 color;
	float4 position;
	float4 direction;
	
	uint type;
	float radius;
	float angle;
	int pad;
};




StructuredBuffer<LightAttribute> lightsAttribute : register(t13);

Texture2D albedoTexture:register(t0);
Texture2D atlasTexture:register(t12);
SamplerState pointSampler : register(s0); 
SamplerState anisotropicSampler : register(s1);
SamplerState LinearSampler : register(s2);

void CalculateLight2D(in out float4 lightColor, float3 position, int idx)
{
	if (lightsAttribute[idx].type == 0)
	{
		lightColor += lightsAttribute[idx].color;
	}
	else if (lightsAttribute[idx].type == 1)
	{
		float length = distance(position.xy, lightsAttribute[idx].position.xy);

		if (length < lightsAttribute[idx].radius)
		{
			float ratio = 1.0f - (length / lightsAttribute[idx].radius);
			lightColor += lightsAttribute[idx].color * ratio;
		}
	}

}
