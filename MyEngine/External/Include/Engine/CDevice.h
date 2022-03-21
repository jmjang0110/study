#pragma once
/*
	Device 
		-	 GPU 를 컨트롤 하는 기능을 담당한다. 


*/
class CDevice
{
	SINGLE(CDevice);
private:

	HWND							m_hwnd;			// Main window Handle
	Vec2							m_vRenderResolution;	// Rendering 해상도 

	ComPtr<ID3D11Device>			m_pDevice;				// GPU 메모리 기능 제어
	ComPtr<ID3D11DeviceContext>		m_pDeviceContext;		// GPU Rendering 기능 제어 

	ComPtr<IDXGISwapChain>			m_pSwapChain;
	ComPtr<ID3D11Texture2D>			m_pRenderTarget;
	ComPtr<ID3D11Texture2D>			m_pDepthStencilTartget;

	ComPtr<ID3D11RenderTargetView>	m_RTV;
	ComPtr<ID3D11DepthStencilView>	m_DSV;

	D3D11_VIEWPORT					m_tViewPort;
	DXGI_SWAP_CHAIN_DESC			m_tSwapChainDesc;


public:
	int init(HWND _hwnd, Vec2 _vRenderResolution);

	void Present() { m_pSwapChain->Present(0, 0); }
	void ClearTarget();


private:
	int CreateSawpChain();
	int CreateView();


};

