struct PS_INPUT
{
	float4 inpos : SV_POSITION;
	float2 inTexCol : TEXCOORD;
};

Texture2D objTexture : TEXTURE : register(t0);
SamplerState objSamplerState : SAMPLER : register(s0);

float4 main(PS_INPUT input) : SV_TARGET
{
	float3 pixelColor = objTexture.Sample(objSamplerState, input.inTexCol);
	return float4(pixelColor, 1.0f);
}