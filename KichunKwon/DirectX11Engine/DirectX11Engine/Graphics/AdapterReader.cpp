#include "AdapterReader.h"

std::vector<AdapterData> AdapterReader::adapters;

std::vector<AdapterData> AdapterReader::GetAdaptders()
{
	if (adapters.size() > 0)return adapters;

	Microsoft::WRL::ComPtr<IDXGIFactory> pFactory;

	//DXGIFactory °´Ã¼ »ý¼º
	HRESULT hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)pFactory.GetAddressOf());
	if (FAILED(hr)) {
		ErrorLogger::Log(hr, "Failed to create DXGIFactory for enumerating adapters.");
		exit(-1);
	}

	IDXGIAdapter* pAdapter;
	UINT index = 0;
	while (SUCCEEDED(pFactory->EnumAdapters(index, &pAdapter)))
	{
		adapters.push_back(AdapterData(pAdapter));
		index += 1;
	}
	return adapters;
}

AdapterData::AdapterData(IDXGIAdapter* pAdapter)
{
	this->pAdapter = pAdapter;
	HRESULT hr = pAdapter->GetDesc(&this->description);
	if (FAILED(hr))
	{
		ErrorLogger::Log(hr, "Failed to Get Description for IDXGIAdapter.");
	}
}
