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
		MessageBox(nullptr, L"장치 초기화 레벨체크 실패", L"엔진 초기화 실패", MB_OK);
		return E_FAIL;
	}


	// pQuality 가 1 이어야 dx library 샘플링이 된다는 것이다. 
	// dx11 을 돌릴 수 있는 최소 사양을 확인하는 것이다. 
	UINT iQuality = 0;

	m_pDevice->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM,
		4, &iQuality);

	if (0 == iQuality)
	{
		MessageBox(nullptr, L"멀티샘플 레벨체크 실패", L"엔진 초기화 실패", MB_OK);
		return E_FAIL;
	}


	// SwapChain 생성 
	if (FAILED(CreateSawpChain()))
	{
		MessageBox(nullptr, L"스왑체인 레벨체크 실패", L"엔진 초기화 실패", MB_OK);
		return E_FAIL;
	}

	// View 생성 
	if (FAILED(CreateView()))
	{
		MessageBox(nullptr, L"뷰 레벨체크 실패", L"엔진 초기화 실패", MB_OK);
		return E_FAIL;
	}


	// Render Target View , DepthStencil View 전달 ( 장치에 알린다. )
	// Rendering 관련으로 Device Context 를 이용 
	// m_RTV :  그림그릴 목적지 
	// Render 시 출력 버퍼 및 출력 깊이 버퍼 지정 
	m_pDeviceContext->OMSetRenderTargets(1, m_RTV.GetAddressOf(), m_DSV.Get());



	// ViewPort // Window 상 어디에 띄게 할건지 ( window 에서 영역 )
	// 윈도우에 출력될 버퍼의 위치 설정 
	m_tViewPort.TopLeftX = 0;
	m_tViewPort.TopLeftY = 0;

	m_tViewPort.Width = (UINT)m_vRenderResolution.x;
	m_tViewPort.Height = (UINT)m_vRenderResolution.y;

	m_tViewPort.MinDepth = 0;
	m_tViewPort.MaxDepth = 1;

	// 윈도우에 띄울 창(렌더링) 크기와 위치를 세팅한다. 
	m_pDeviceContext->RSSetViewports(1, &m_tViewPort);
	







	return S_OK;

}



int CDevice::CreateSawpChain()
{
	DXGI_SWAP_CHAIN_DESC desc = {};
	
	desc.BufferCount = 1;									// * 1을 넣어주면 알아서 2장을 만든다. 
	desc.BufferDesc.Width = (UINT)m_vRenderResolution.x;	// * 해상도 정보 width / Height 
	desc.BufferDesc.Height = (UINT)m_vRenderResolution.y;
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;	// * Pixel 하나가 몇바이트 메모리인지 어떻게 구성되어 있는지 ( Pixel 하나 32bit/각8bit(1Byte) )
	desc.BufferDesc.RefreshRate.Denominator = 1;
	desc.BufferDesc.RefreshRate.Numerator = 60;		// 60hz 로 설정
	desc.BufferDesc.Scaling = DXGI_MODE_SCALING::DXGI_MODE_SCALING_UNSPECIFIED;
	desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER::DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED; // 스캔라인 방식 설정 ( 기본방식 설정 - 니 알아서)
	
	
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.Flags = 0;
	desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD; // BackBuffer 에 이전프레임 장면을 지운다. 

	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;

	desc.OutputWindow = m_hwnd; // Front BUffer를 어디에 보내야 하는지 목적값을 저장 
	desc.Windowed = true;

	// 
	ComPtr<IDXGIDevice> pDXGIDevice = nullptr;
	ComPtr<IDXGIAdapter> pDXGIAdapter = nullptr;
	ComPtr<IDXGIFactory> pDXGIFactory= nullptr;

	// __uuidof : 고유한 각 클래스의 GUID 반환 
	// QueryInterface  :  Device 가 IDXGIDevice의 아이디를 가진 클래스를 생성시켜서 얻어오는 함수 
	// (void**)로 줘야 한다. 
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
	SwapChain : 내가 출력해야 할 버퍼 누굽니까?
	Render Target View : 제가 알려드리겠습니다..



	// RTV 는 SwapChain 이 가지고 있는 버퍼를 가리킨다. 
	// SwapChain ----------> Buffer <----------- RTV
	// SwapChain 은 RTV 를 통해서 Buffer를 장치에 알린다. 


	// RTV 가 장치의 그림을 그릴 목적지 입니다 라고 장치한테 알려야한다. 
	// 따라서 RTV 는 SwapChain 이 만들어낸 버퍼를 가리켜야한다. 
	//( Swap Chain 이 가지고 있는 버퍼(렌더 타겟 버퍼)를 전달하는 역할 
	// Render Target ( front buffer , Back Buffer )
	// 이것을 전달해줄 때 Render Target View 가 필요하다 .


	// pBuffer 에 SwapChain 이 들고있는 버퍼를 가지고 오고 
	// pBuffer 에 Render Target View 를 만들어야 한다. 
	*/




	// ==============  R T V [ Render Target View ] ============== 생성 
	ComPtr<ID3D11Texture2D> pBuffer = nullptr;
	m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)pBuffer.GetAddressOf()); // Render Target Buffer 를 가지고 온다.
	m_pDevice->CreateRenderTargetView(pBuffer.Get(), nullptr, m_RTV.GetAddressOf());

	if (nullptr == m_RTV)
		return E_FAIL;

	//  ============== D S V [ Depth Stencil View ] ============== 생성 
	D3D11_TEXTURE2D_DESC desc = {};

	desc.Width = (UINT)m_vRenderResolution.x;
	desc.Height = (UINT)m_vRenderResolution.y;
	desc.MipLevels = 0; // Mip TExture 
	desc.ArraySize = 1; // Texture 가 여러개 뭉쳐있는 경우 있을 수 있으니 몇개인지. 

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


