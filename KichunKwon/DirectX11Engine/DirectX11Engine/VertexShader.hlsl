cbuffer myBuffer : register(b0)
{
	float4x4 mat;//��ĺ�ȯ
};

struct VS_INPUT 
{
	float3 inpos : POSITION;
	float2 inTexCol : TEXCOORD;
};

struct VS_OUTPUT
{
	float4 outpos : SV_POSITION;
	float2 outTexCol : TEXCOORD;
};

VS_OUTPUT main( VS_INPUT input)
{
	VS_OUTPUT output;
	output.outpos = mul(float4(input.inpos, 1.0f), mat);
	output.outTexCol = input.inTexCol;
	return output;
}