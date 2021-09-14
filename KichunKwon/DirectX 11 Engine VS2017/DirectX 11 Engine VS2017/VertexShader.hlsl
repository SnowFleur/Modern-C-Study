struct VS_INPUT 
{
	float3 inpos : POSITION;
	float3 incolor : COLOR;
};

struct VS_OUTPUT
{
	float4 outpos : SV_POSITION;
	float3 outcolor : COLOR;
};

VS_OUTPUT main( VS_INPUT input)
{
	VS_OUTPUT output;
	output.outpos = float4(input.inpos, 1.0f);
	output.outcolor = input.incolor;
	return output;
}