#include "Graphics.h"

bool Graphics::Initialize(HWND hwnd, int width, int height)
{
    this->windowWidth = width;
    this->windowHeight = height;
    this->fpsTimer.Start();

    if (!InitializeDirectX(hwnd))
        return false;

    if (!InitializeShaders())
        return false;

	if (!InitializeScene())
		return false;

    return true;
}

void Graphics::RenderFrame()
{
    float bgcolor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    this->deviceContext->ClearRenderTargetView(this->renderTargetView.Get(), bgcolor);
    this->deviceContext->ClearDepthStencilView(this->depthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

    this->deviceContext->IASetInputLayout(this->vertexshader.GetInputLayout());
    this->deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    this->deviceContext->RSSetState(this->rasterizerState.Get());
    this->deviceContext->OMSetDepthStencilState(this->depthStencilState.Get(), 0);

    this->deviceContext->PSSetSamplers(0, 1, this->samplerState.GetAddressOf());

    this->deviceContext->VSSetShader(vertexshader.GetShader(), NULL, 0);
    this->deviceContext->PSSetShader(pixelshader.GetShader(), NULL, 0);

    UINT offset = 0;

    //Update Constant Buffer
    XMMATRIX world = XMMatrixIdentity();//월드변환행렬

    //static DirectX::XMVECTOR eyePos = DirectX::XMVectorSet(0.0f, 0.0f, -2.0f, 0.0f);//카메라 위치
    //
    //DirectX::XMFLOAT3 eyePosFloat3;
    //DirectX::XMStoreFloat3(&eyePosFloat3, eyePos);//값을 eyeposfloat에 저장
    //eyePosFloat3.y += 0.01f;
    //eyePos = DirectX::XMLoadFloat3(&eyePosFloat3);//값을 eyeposfloat에서 로드

    //static DirectX::XMVECTOR lookAtPos = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);//보는 방향
    //static DirectX::XMVECTOR upVector = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);//UP벡터
    //DirectX::XMMATRIX viewMatrix = DirectX::XMMatrixLookAtLH(eyePos, lookAtPos, upVector);
    //float fovDegrees = 90.0f;
    //float fovRadians = (fovDegrees / 360.0f) * DirectX::XM_2PI;
    //float aspectRatio = static_cast<float>(this->windowWidth) / static_cast<float>(this->windowHeight);
    //float nearZ = 0.1f;
    //float farZ = 1000.0f;
    //DirectX::XMMATRIX projectionMatrix = DirectX::XMMatrixPerspectiveFovLH(fovRadians, aspectRatio, nearZ, farZ);


    //camera.AdjustPosition(0.01f,0.0f,0.0f);
    //camera.SetLookAtPos(XMFLOAT3(0.0f, 0.0f, 0.0f));//카메라가 보는 타켓 위치설정
    constantBuffer.data.mat = world * camera.GetViewMatrix() * camera.GetProjectionMatrix();
    constantBuffer.data.mat = DirectX::XMMatrixTranspose(constantBuffer.data.mat);//행렬 연산을 위해서 행렬 전치 column format

    if (!constantBuffer.ApplyChanges())
        return;
    this->deviceContext->VSSetConstantBuffers(0, 1, this->constantBuffer.GetAddressOf());


    //사각형 그리기
    this->deviceContext->PSSetShaderResources(0, 1, this->myTexture.GetAddressOf());
    this->deviceContext->IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), vertexBuffer.StridePtr(), &offset);
    this->deviceContext->IASetIndexBuffer(indiciesBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
    this->deviceContext->DrawIndexed(indiciesBuffer.BufferSize(), 0, 0);

    //Drow Text
    static int fpsCounter = 0;
    static std::string fpsString = "FPS : 0";
    fpsCounter++;
    if(fpsTimer.GetMilisecondsElapsed() > 1000.0f)
    {
        fpsString = "FPS : " + std::to_string(fpsCounter);
        fpsCounter = 0;
        fpsTimer.Restart();
    }
    spriteBatch->Begin();
    spriteFont->DrawString(spriteBatch.get(), StringConverter::StringToWide(fpsString).c_str(), DirectX::XMFLOAT2(0, 0), DirectX::Colors::White, 0.0f, DirectX::XMFLOAT2(0, 0), DirectX::XMFLOAT2(1.0f, 1.0f));
    spriteBatch->End();


    this->swapChain->Present(0, NULL);
}

bool Graphics::InitializeDirectX(HWND hwnd)
{
    std::vector<AdapterData> adapters = AdapterReader::GetAdaptders();

    if (adapters.size() < 1)
    {
        ErrorLogger::Log("No IDXGI Adapters found.");
        return false;
    }

    DXGI_SWAP_CHAIN_DESC scd;
    ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

    scd.BufferDesc.Width = this->windowWidth;
    scd.BufferDesc.Height = this->windowHeight;
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

    //Describe Depth/Stencil Buffer
    D3D11_TEXTURE2D_DESC depthStencilDesc;
    depthStencilDesc.Width = this->windowWidth;
    depthStencilDesc.Height = this->windowHeight;
    depthStencilDesc.MipLevels = 1;
    depthStencilDesc.ArraySize = 1;
    depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    depthStencilDesc.SampleDesc.Count = 1;
    depthStencilDesc.SampleDesc.Quality = 0;
    depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
    depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    depthStencilDesc.CPUAccessFlags = 0;
    depthStencilDesc.MiscFlags = 0;

    hr = this->device->CreateTexture2D(&depthStencilDesc, NULL, this->depthStencilBuffer.GetAddressOf());
    if (FAILED(hr)) {
        ErrorLogger::Log(hr, "Failed to create depth stencil buffer.");
        return false;
    }

    hr = this->device->CreateDepthStencilView(this->depthStencilBuffer.Get(), NULL, this->depthStencilView.GetAddressOf());
	if (FAILED(hr)) {
		ErrorLogger::Log(hr, "Failed to create depth stencil view.");
		return false;
	}

    this->deviceContext->OMSetRenderTargets(1, this->renderTargetView.GetAddressOf(), this->depthStencilView.Get());

    //create depth stencil state
    D3D11_DEPTH_STENCIL_DESC depthStencilStateDesc;
    ZeroMemory(&depthStencilStateDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));

    depthStencilStateDesc.DepthEnable = true;
    depthStencilStateDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
    depthStencilStateDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS_EQUAL;

    hr = this->device->CreateDepthStencilState(&depthStencilStateDesc, this->depthStencilState.GetAddressOf());
    if (FAILED(hr)) {
		ErrorLogger::Log(hr, "Failed to create depth stencil state.");
		return false;
    }

    //Create viewport
    D3D11_VIEWPORT viewport;
    ZeroMemory(&viewport, sizeof(viewport));

    viewport.TopLeftX = 0;
    viewport.TopLeftY = 0;
    viewport.Width = this->windowWidth;
    viewport.Height = this->windowHeight;
    viewport.MinDepth = 0.0f;
    viewport.MaxDepth = 1.0f;

    this->deviceContext->RSSetViewports(1, &viewport);

    //Create Rasterizer State
    D3D11_RASTERIZER_DESC rasterizerDesc;
    ZeroMemory(&rasterizerDesc, sizeof(D3D11_RASTERIZER_DESC));

    rasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;//일반 렌더링
    rasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_BACK;//뒷면 제거
    rasterizerDesc.FrontCounterClockwise = FALSE;//반시계 방향
    hr = this->device->CreateRasterizerState(&rasterizerDesc, this->rasterizerState.GetAddressOf());
    if (FAILED(hr)) {
        ErrorLogger::Log(hr, "Failed to create rasterizer state.");
        return false;
    }

	//Font Initialize
	spriteBatch = std::make_unique<DirectX::SpriteBatch>(this->deviceContext.Get());
	spriteFont = std::make_unique<DirectX::SpriteFont>(this->device.Get(), L"Data\\Fonts\\comic_sans_ms_16.spritefont");

    D3D11_SAMPLER_DESC sampDesc;
    ZeroMemory(&sampDesc, sizeof(sampDesc));
    sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
    sampDesc.MinLOD = 0;
    sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
    hr = this->device->CreateSamplerState(&sampDesc, this->samplerState.GetAddressOf());
    if (FAILED(hr))
    {
		ErrorLogger::Log(hr, "Failed to create sampler state.");
		return false;
    }


    return true;
}

bool Graphics::InitializeShaders()
{
    std::wstring shaderfolder = L"";
#pragma region DetermineShaderPath
    if (IsDebuggerPresent() == TRUE)
    {
#ifdef _DEBUG //디버그 모드
    #ifdef _WIN64
        shaderfolder = L"..\\x64\\Debug\\";
    #else
        shaderfolder = L"..\\Debug\\";
    #endif
    #else
    #ifdef _WIN64
		shaderfolder = L"..\\x64\\Release\\";
    #else
		shaderfolder = L"..\\Release\\";
    #endif
#endif // _DEBUG //디버그 모드
    }

	D3D11_INPUT_ELEMENT_DESC layout[] = {
		{"POSITION", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"TEXCOORD", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA, 0}
	};

	UINT numElements = ARRAYSIZE(layout);

    if (!vertexshader.Initialize(this->device, shaderfolder + L"VertexShader.cso", layout, numElements))
        return false;

	if (!pixelshader.Initialize(this->device, shaderfolder + L"PixelShader.cso"))
		return false;


    return true;
}

bool Graphics::InitializeScene()
{
    Vertex v[] =
    {
        Vertex(-0.5f, -0.5f, 0.0f, 0.0f, 1.0f),//bl [0]
		Vertex(-0.5f, 0.5f, 0.0f, 0.0f, 0.0f),//tl  [1]
		Vertex(0.5f, 0.5f, 0.0f, 1.0f, 0.0f),//tr   [2]
        Vertex(0.5f, -0.5f, 0.0f, 1.0f, 1.0f),//br  [3]
    };

	//Load Vertex Data
	HRESULT hr = this->vertexBuffer.Initialize(this->device.Get(), v, ARRAYSIZE(v));
	if (FAILED(hr)) {
		ErrorLogger::Log(hr, "Failed to Create vertex buffer.");
		return false;
	}

    DWORD indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    //Load Index Data
    hr = this->indiciesBuffer.Initialize(this->device.Get(), indices, ARRAYSIZE(indices));
    if (FAILED(hr)) {
		ErrorLogger::Log(hr, "Failed to Create indices buffer.");
		return false;
	}

    //Load Texture
    hr = DirectX::CreateWICTextureFromFile(this->device.Get(), L"Data\\Textures\\Earth.jpg", nullptr, myTexture.GetAddressOf());
	if (FAILED(hr)) {
		ErrorLogger::Log(hr, "Failed to Create wic texture from file.");
		return false;
	}

    //Initialize Constant Buffer(s)
    hr = this->constantBuffer.Initialize(this->device.Get(), this->deviceContext.Get());
    if (FAILED(hr)) {
		ErrorLogger::Log(hr, "Failed to Create constant buffer.");
		return false;
	}

    camera.SetPosition(0.0f, 0.0f, -2.0f);
    camera.SetProjectionValues(90.0f, static_cast<float>(windowWidth) / static_cast<float>(windowHeight), 0.1f, 1000.0f);
    
    
    return true;
}