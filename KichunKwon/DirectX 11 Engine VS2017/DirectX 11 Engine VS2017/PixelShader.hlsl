struct PS_INPUT
{
	float4 inpos : SV_POSITION;
	float3 incolor : COLOR;
};

float4 main(PS_INPUT input) : SV_TARGET
{
	return float4(input.incolor, 1.0f);
}