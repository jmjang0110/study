#include "pch.h"
#include "CGraphicsShader.h"

#include "CPathMgr.h"
#include "CDevice.h"

#ifdef _DEBUG
UINT g_iFlag = D3DCOMPILE_DEBUG;
#else
UINT g_iFlag = 0;

#endif

vector<D3D11_INPUT_ELEMENT_DESC> CGraphicsShader::g_vecLayout;


CGraphicsShader::CGraphicsShader()
	: m_eRSType(RS_TYPE::CULL_BACK)
	, m_eTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST)
{
}

CGraphicsShader::~CGraphicsShader()
{
}




int CGraphicsShader::CreateVertexShader(const wstring& _strRrelativePath, const string& _strFunc)
{
	// Vertex Compile 
	//					[  Vertex Shader Compile  ] 
	wstring strContentPath = CPathMgr::GetInst()->GetContentPath();
	HRESULT hr = D3DCompileFromFile(wstring(strContentPath + _strRrelativePath).c_str(), nullptr
		, D3D_COMPILE_STANDARD_FILE_INCLUDE, _strFunc.c_str(), "vs_5_0", g_iFlag, 0
		, m_VSBlob.GetAddressOf(), m_VSBlob.GetAddressOf()); // (VS_Test)L"" 안붙이고 1byte 로 전달 

	if (FAILED(hr))
	{
		MessageBoxA(nullptr, (char*)m_ErrBlob->GetBufferPointer(), "Vertex Shader Compile Failed!! ", MB_OK);
		return E_FAIL;
	}
	// Compile 된 코드로 Vertex Shader 객체 만들기 
	// Compile 완료된 Vertex Shader 의 시작 주소를 전달 : Blob안에 있음  
	if (FAILED(DEVICE->CreateVertexShader(m_VSBlob->GetBufferPointer(), m_VSBlob->GetBufferSize(),
		nullptr, m_VS.GetAddressOf())))
	{
		return E_FAIL;

	}

	if (FAILED(DEVICE->CreateInputLayout(g_vecLayout.data(), (UINT)g_vecLayout.size()
		, m_VSBlob->GetBufferPointer(), m_VSBlob->GetBufferSize()
		, m_InputLayout.GetAddressOf())))
	{
		return E_FAIL;

	}


	return S_OK;

}

int CGraphicsShader::CreatePixelShader(const wstring& _strRrelativePath, const string& _strFunc)
{

	// Pixel Compile 
	//					[  Pixel Shader Compile  ] 
	wstring strContentPath = CPathMgr::GetInst()->GetContentPath();
	HRESULT hr = D3DCompileFromFile(wstring(strContentPath + _strRrelativePath).c_str(), nullptr
		, D3D_COMPILE_STANDARD_FILE_INCLUDE, _strFunc.c_str(), "ps_5_0", g_iFlag, 0
		, m_PSBlob.GetAddressOf(), m_PSBlob.GetAddressOf()); // (VS_Test)L"" 안붙이고 1byte 로 전달 

	if (FAILED(hr))
	{
		MessageBoxA(nullptr, (char*)m_ErrBlob->GetBufferPointer(), "Pixel Shader Compile Failed!! ", MB_OK);
		return E_FAIL;
	}
	// Compile 된 코드로 Vertex Shader 객체 만들기 
	// Compile 완료된 Vertex Shader 의 시작 주소를 전달 : Blob안에 있음  
	if (FAILED(DEVICE->CreatePixelShader(m_PSBlob->GetBufferPointer(), m_PSBlob->GetBufferSize(),
		nullptr, m_PS.GetAddressOf())))
	{
		return E_FAIL;

	}

	return S_OK;

}

void CGraphicsShader::UpdateData()
{
	// 내부구조 전달 
	CONTEXT->IASetInputLayout(m_InputLayout.Get());
	CONTEXT->IASetPrimitiveTopology(m_eTopology);


	// 아래 Shader 들은 사용하겠다. 
	// HS DS GS 등 안쓰더라도 값을 null 을 넣어주어야 한다.
	// 각 Mesh 마다 shader 들이 있는데 
	// Mesh마다 쓰는 shader 들이 다를 수 있다. 
	// 그런데 이전에 쓴 Shader 정보가 남아있기 때문에 항상 
	// 안쓰더라도 Null 값을 넣어 주어야한다.

	CONTEXT->VSSetShader(m_VS.Get(), 0, 0); // 이 정점들을 어떤 쉐이더를 사용할 것인지를 선택한다. 
	CONTEXT->HSSetShader(m_HS.Get(), 0, 0);
	CONTEXT->DSSetShader(m_DS.Get(), 0, 0);
	CONTEXT->GSSetShader(m_GS.Get(), 0, 0);
	CONTEXT->PSSetShader(m_PS.Get(), 0, 0);


	CONTEXT->RSSetState(CDevice::GetInst()->GetRS(m_eRSType).Get());

}

void CGraphicsShader::AddScalarParamInfo(const wstring& _strDesc, SCALAR_PARAM _eParamType)
{
	m_vecScalarParamInfo.push_back(tScalarParamInfo{ _strDesc, _eParamType });

}

void CGraphicsShader::AddtexParamInfo(const wstring& _strDesc, TEX_PARAM _eParamType)
{
	m_VecTexParamInfo.push_back(tTexrParamInfo{ _strDesc ,_eParamType });

}



void CGraphicsShader::AddInputLayout(D3D11_INPUT_ELEMENT_DESC _desc)
{
	g_vecLayout.push_back(_desc);

}
