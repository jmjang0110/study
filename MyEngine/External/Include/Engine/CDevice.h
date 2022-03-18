#pragma once
/*
	Device 
		-	 GPU �� ��Ʈ�� �ϴ� ����� ����Ѵ�. 


*/
class CDevice
{
	SINGLE(CDevice);
private:

	HWND							m_hwnd;			// Main window Handle
	Vec2							m_vRenderResolution;	// Rendering �ػ� 

	ComPtr<ID3D11Device>			m_pDevice;
	ComPtr<ID3D11DeviceContext>		m_pDeviceContext;

	ComPtr<IDXGISwapChain>			m_pSwapChain;
	ComPtr<ID3D11Texture2D>			m_pRenderTarget;
	ComPtr<ID3D11Texture2D>			m_pDepthStencilTartget;

	ComPtr<ID3D11RenderTargetView>	m_RTV;
	ComPtr<ID3D11DepthStencilView>	m_DSV;

	D3D11_VIEWPORT					m_tViewPort;
	DXGI_SWAP_CHAIN_DESC			m_tSwapChainDesc;


public:
	int init(HWND _hwnd, Vec2 _vRenderResolution);



};

