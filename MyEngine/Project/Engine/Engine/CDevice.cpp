#include "pch.h"
#include "CDevice.h"

CDevice::CDevice()
{

}

CDevice::~CDevice()
{


}

int CDevice::init(HWND _hwnd, Vec2 _vRenderResolution)
{
	m_hwnd = _hwnd;
	m_vRenderResolution = _vRenderResolution;


	UINT iFlag = 0;


#ifdef _DEBUG
	iFlag = D3D11_CREATE_DEVICE_DEBUG; // 특정 directx 함수 호출하 때 출력창에 쏜다. 
#endif


	D3D_FEATURE_LEVEL iFeatureLevel = D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_11_0;
	// 그래픽 연산을 
	// D3D_DRIVER_TYPE_HARDWARE : GPU 가 하겠다. 
	// D3D_DRIVER_TYPE_SOFTWARE : CPU 가 하겠다. 
	HRESULT hr = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_HARDWARE
	, 0, iFlag, nullptr, 0, D3D11_SDK_VERSION
	, m_pDevice.GetAddressOf(), &iFeatureLevel, m_pDeviceContext.GetAddressOf());



	if (FAILED(hr))
	{
		return E_FAIL;
	}

	
	return S_OK;

}
