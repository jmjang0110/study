#pragma once
/*
	Device 
		-	 GPU 를 컨트롤 하는 기능을 담당한다. 
*/



class CDevice
	: public CSingleton<CDevice>
{
	SINGLE(CDevice)
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


	ComPtr<ID3D11RasterizerState>	m_arrRS[(UINT)RS_TYPE::END];
	ComPtr<ID3D11DepthStencilState> m_arrDS[(UINT)DS_TYPE::END];
	class CConstBuffer*				m_arrCB[(UINT)CB_TYPE::END];


	ComPtr<ID3D11SamplerState>		m_arrSam[2];


public:
	int init(HWND _hwnd, Vec2 _vRenderResolution);

	void Present() { m_pSwapChain->Present(0, 0); }
	void ClearTarget();

	ComPtr<ID3D11Device> GetDevice() { return m_pDevice;}
	ComPtr<ID3D11DeviceContext> GetDeviceContext() { return m_pDeviceContext; }
	ComPtr<ID3D11DepthStencilState> GetDS(DS_TYPE _eType) { return m_arrDS[(UINT)_eType]; }
	// return Rasterizer State 
	ComPtr<ID3D11RasterizerState> GetRS(RS_TYPE _eType) { return m_arrRS[(UINT)_eType]; }
	// return Constant Buffer 
	CConstBuffer* GetCB(CB_TYPE _eType) { return m_arrCB[(UINT)_eType]; }
	// return Render Resolution
	Vec2 GetRenderResolution() { return m_vRenderResolution; }



private:
	int CreateSawpChain();
	int CreateView();
	int CreateRasterizerState();
	int CreateDepthStencilState();
	int CreateConstBuffer();
	void CreateSamplerState();



};

