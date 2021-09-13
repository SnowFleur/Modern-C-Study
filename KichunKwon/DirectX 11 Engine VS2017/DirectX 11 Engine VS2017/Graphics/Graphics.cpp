#include "Graphics.h"

bool Graphics::Initialize(HWND hwnd, int width, int height)
{
    if (!InitializeDirectX(hwnd, width, height))
        return false;

    if (!InitializeShaders())
        return false;


    return true;
}

void Graphics::RenderFrame()
{
    float bgcolor[] = { 0.0f, 0.0f, 1.0f, 1.0f };
    this->deviceContext->ClearRenderTargetView(this->renderTargetView.Get(), bgcolor);
    this->swapChain->Present(1, NULL);
}

bool Graphics::InitializeDirectX(HWND hwnd, int width, int height)
{
    std::vector<AdapterData> adapters = AdapterReader::GetAdaptders();

    if (adapters.size() < 1)
    {
        ErrorLogger::Log("No IDXGI Adapters found.");
        return false;
    }

    DXGI_SWAP_CHAIN_DESC scd;
    ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

    scd.BufferDesc.Width = width;
    scd.BufferDesc.Height = height;
    scd.BufferDesc.RefreshRate.Numerator = 60;
    scd.BufferDesc.RefreshRate.Denominator = 1;
    scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    scd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    scd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

    scd.SampleDesc.Count = 1;
    scd.SampleDesc.Quality = 0;

    scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    scd.BufferCount = 1;//스크린 버퍼 갯수
    scd.OutputWindow = hwnd;
    scd.Windowed = TRUE;
    scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    
    HRESULT hr;
    hr = D3D11CreateDeviceAndSwapChain(
        adapters[0].pAdapter, //IDXGI adapter
        D3D_DRIVER_TYPE_UNKNOWN,
        NULL, //소프트웨어 드라이버 type
        NULL, //flag Runtime layer
        NULL, //Feature levels array
        0,    //of feature levels in array
        D3D11_SDK_VERSION,
        &scd, //swapchain description
        this->swapChain.GetAddressOf(), //SwapChain Address
        this->device.GetAddressOf(),    //Device Address
        NULL, //Supported feature level
        this->deviceContext.GetAddressOf()); // DeviceContext Address

    if (FAILED(hr))
    {
        ErrorLogger::Log(hr, "Failed to create device and SwapChain.");
        return false;
    }

    Microsoft::WRL::ComPtr<ID3D11Texture2D> BackBuffer;
    hr = this->swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(BackBuffer.GetAddressOf()));
    if (FAILED(hr))
    {
        ErrorLogger::Log(hr, "GetBuffer Failed.");
        return false;
    }

    hr = this->device->CreateRenderTargetView(BackBuffer.Get(), NULL, this->renderTargetView.GetAddressOf());
	if (FAILED(hr))
	{
		ErrorLogger::Log(hr, "Failed Create RenderTargetView.");
		return false;
	}

    this->deviceContext->OMSetRenderTargets(1, this->renderTargetView.GetAddressOf(), NULL);


    return true;
}

bool Graphics::InitializeShaders()
{
    D3D11_INPUT_ELEMENT_DESC layout[] = {
        {"POSITION", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA, 0}
    };

    UINT numElements = ARRAYSIZE(layout);

    HRESULT hr = this->device->CreateInputLayout(layout, numElements, vertex_shader_buffer->GetBufferPointer(), vertex_shader_buffer->GetBufferSize(), this->inputLayout.GetAddressOf());
	if (FAILED(hr))
	{
		ErrorLogger::Log(hr, "Failed Create Input layout.");
		return false;
	}

    return true;
}
