#pragma once
#include <DirectXMath.h>

struct CB_VS_vertexshader
{
	//float xOffset = 0;//4byte//16bytes ������ ����
	//float yOffset = 0;//4byte
	DirectX::XMMATRIX mat;//��ȯ���
};
struct CB_PS_pixelshader
{
	float alpha = 1.0f;
};