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
	iFlag = D3D11_CREATE_DEVICE_DEBUG; // Ư�� directx �Լ� ȣ���� �� ���â�� ���. 
#endif


	D3D_FEATURE_LEVEL iFeatureLevel = D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_11_0;
	// �׷��� ������ 
	// D3D_DRIVER_TYPE_HARDWARE : GPU �� �ϰڴ�. 
	// D3D_DRIVER_TYPE_SOFTWARE : CPU �� �ϰڴ�. 
	HRESULT hr = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_HARDWARE
	, 0, iFlag, nullptr, 0, D3D11_SDK_VERSION
	, m_pDevice.GetAddressOf(), &iFeatureLevel, m_pDeviceContext.GetAddressOf());



	if (FAILED(hr))
	{
		MessageBox(nullptr, L"��ġ �ʱ�ȭ ����üũ ����", L"���� �ʱ�ȭ ����", MB_OK);
		return E_FAIL;
	}


	// pQuality �� 1 �̾�� dx library ���ø��� �ȴٴ� ���̴�. 
	// dx11 �� ���� �� �ִ� �ּ� ����� Ȯ���ϴ� ���̴�. 
	UINT iQuality = 0;

	m_pDevice->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM,
		4, &iQuality);

	if (0 == iQuality)
	{
		MessageBox(nullptr, L"��Ƽ���� ����üũ ����", L"���� �ʱ�ȭ ����", MB_OK);
		return E_FAIL;
	}


	// SwapChain ���� 
	if (FAILED(CreateSawpChain()))
	{
		MessageBox(nullptr, L"����ü�� ����üũ ����", L"���� �ʱ�ȭ ����", MB_OK);
		return E_FAIL;
	}

	// View ���� 
	if (FAILED(CreateView()))
	{
		MessageBox(nullptr, L"�� ����üũ ����", L"���� �ʱ�ȭ ����", MB_OK);
		return E_FAIL;
	}


	// Render Target View , DepthStencil View ���� ( ��ġ�� �˸���. )
	// Rendering �������� Device Context �� �̿� 
	// m_RTV :  �׸��׸� ������ 
	// Render �� ��� ���� �� ��� ���� ���� ���� 
	m_pDeviceContext->OMSetRenderTargets(1, m_RTV.GetAddressOf(), m_DSV.Get());



	// ViewPort // Window �� ��� ��� �Ұ��� ( window ���� ���� )
	// �����쿡 ��µ� ������ ��ġ ���� 
	m_tViewPort.TopLeftX = 0;
	m_tViewPort.TopLeftY = 0;

	m_tViewPort.Width = (UINT)m_vRenderResolution.x;
	m_tViewPort.Height = (UINT)m_vRenderResolution.y;

	m_tViewPort.MinDepth = 0;
	m_tViewPort.MaxDepth = 1;

	// �����쿡 ��� â(������) ũ��� ��ġ�� �����Ѵ�. 
	m_pDeviceContext->RSSetViewports(1, &m_tViewPort);
	







	return S_OK;

}



int CDevice::CreateSawpChain()
{
	DXGI_SWAP_CHAIN_DESC desc = {};
	
	desc.BufferCount = 1;									// * 1�� �־��ָ� �˾Ƽ� 2���� �����. 
	desc.BufferDesc.Width = (UINT)m_vRenderResolution.x;	// * �ػ� ���� width / Height 
	desc.BufferDesc.Height = (UINT)m_vRenderResolution.y;
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;	// * Pixel �ϳ��� �����Ʈ �޸����� ��� �����Ǿ� �ִ��� ( Pixel �ϳ� 32bit/��8bit(1Byte) )
	desc.BufferDesc.RefreshRate.Denominator = 1;
	desc.BufferDesc.RefreshRate.Numerator = 60;		// 60hz �� ����
	desc.BufferDesc.Scaling = DXGI_MODE_SCALING::DXGI_MODE_SCALING_UNSPECIFIED;
	desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER::DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED; // ��ĵ���� ��� ���� ( �⺻��� ���� - �� �˾Ƽ�)
	
	
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.Flags = 0;
	desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD; // BackBuffer �� ���������� ����� �����. 

	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;

	desc.OutputWindow = m_hwnd; // Front BUffer�� ��� ������ �ϴ��� �������� ���� 
	desc.Windowed = true;

	// 
	ComPtr<IDXGIDevice> pDXGIDevice = nullptr;
	ComPtr<IDXGIAdapter> pDXGIAdapter = nullptr;
	ComPtr<IDXGIFactory> pDXGIFactory= nullptr;

	// __uuidof : ������ �� Ŭ������ GUID ��ȯ 
	// QueryInterface  :  Device �� IDXGIDevice�� ���̵� ���� Ŭ������ �������Ѽ� ������ �Լ� 
	// (void**)�� ��� �Ѵ�. 
	m_pDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)pDXGIDevice.GetAddressOf());
	pDXGIDevice->GetParent(__uuidof(IDXGIAdapter), (void**)pDXGIAdapter.GetAddressOf());
	pDXGIAdapter->GetParent(__uuidof(IDXGIFactory), (void**)pDXGIFactory.GetAddressOf());



	// Swap Chain

	pDXGIFactory->CreateSwapChain(m_pDevice.Get(), &desc, m_pSwapChain.GetAddressOf());

	if (nullptr == m_pSwapChain)
	{
		return E_FAIL;
	}

	return S_OK;
}

int CDevice::CreateView()
{

	/*
	SwapChain : ���� ����ؾ� �� ���� �����ϱ�?
	Render Target View : ���� �˷��帮�ڽ��ϴ�..



	// RTV �� SwapChain �� ������ �ִ� ���۸� ����Ų��. 
	// SwapChain ----------> Buffer <----------- RTV
	// SwapChain �� RTV �� ���ؼ� Buffer�� ��ġ�� �˸���. 


	// RTV �� ��ġ�� �׸��� �׸� ������ �Դϴ� ��� ��ġ���� �˷����Ѵ�. 
	// ���� RTV �� SwapChain �� ���� ���۸� �����Ѿ��Ѵ�. 
	//( Swap Chain �� ������ �ִ� ����(���� Ÿ�� ����)�� �����ϴ� ���� 
	// Render Target ( front buffer , Back Buffer )
	// �̰��� �������� �� Render Target View �� �ʿ��ϴ� .


	// pBuffer �� SwapChain �� ����ִ� ���۸� ������ ���� 
	// pBuffer �� Render Target View �� ������ �Ѵ�. 
	*/




	// ==============  R T V [ Render Target View ] ============== ���� 
	ComPtr<ID3D11Texture2D> pBuffer = nullptr;
	m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)pBuffer.GetAddressOf()); // Render Target Buffer �� ������ �´�.
	m_pDevice->CreateRenderTargetView(pBuffer.Get(), nullptr, m_RTV.GetAddressOf());

	if (nullptr == m_RTV)
		return E_FAIL;

	//  ============== D S V [ Depth Stencil View ] ============== ���� 
	D3D11_TEXTURE2D_DESC desc = {};

	desc.Width = (UINT)m_vRenderResolution.x;
	desc.Height = (UINT)m_vRenderResolution.y;
	desc.MipLevels = 0; // Mip TExture 
	desc.ArraySize = 1; // Texture �� ������ �����ִ� ��� ���� �� ������ �����. 

	desc.CPUAccessFlags = 0;
	desc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_DEPTH_STENCIL;
	desc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
	desc.MiscFlags = 0;


	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;

	desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT; // ( Depth 3byte Stencil 1byte )


	m_pDevice->CreateTexture2D(&desc, nullptr, m_pDepthStencilTartget.GetAddressOf());
	
	if (nullptr == m_pDepthStencilTartget)
		return E_FAIL;

	m_pDevice->CreateDepthStencilView(m_pDepthStencilTartget.Get(), nullptr, m_DSV.GetAddressOf());
	if (nullptr == m_DSV)
		return E_FAIL;


	return S_OK;
}



void CDevice::ClearTarget()
{
	
	m_pDeviceContext->ClearRenderTargetView(m_RTV.Get(), Vec4(0.f,0.f,0.f,1.f));
	m_pDeviceContext->ClearDepthStencilView(m_DSV.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.f, 0);



}


