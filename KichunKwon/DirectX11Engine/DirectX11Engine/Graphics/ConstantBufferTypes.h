#pragma once
#include <DirectXMath.h>

struct CB_VS_vertexshader
{
	//float xOffset = 0;//4byte//16bytes 단위로 적제
	//float yOffset = 0;//4byte
	DirectX::XMMATRIX mat;//변환행렬
};
struct CB_PS_pixelshader
{
	float alpha = 1.0f;
};