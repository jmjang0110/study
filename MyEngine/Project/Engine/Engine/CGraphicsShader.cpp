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
		, m_VSBlob.GetAddressOf(), m_VSBlob.GetAddressOf()); // (VS_Test)L"" �Ⱥ��̰� 1byte �� ���� 

	if (FAILED(hr))
	{
		MessageBoxA(nullptr, (char*)m_ErrBlob->GetBufferPointer(), "Vertex Shader Compile Failed!! ", MB_OK);
		return E_FAIL;
	}
	// Compile �� �ڵ�� Vertex Shader ��ü ����� 
	// Compile �Ϸ�� Vertex Shader �� ���� �ּҸ� ���� : Blob�ȿ� ����  
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
		, m_PSBlob.GetAddressOf(), m_PSBlob.GetAddressOf()); // (VS_Test)L"" �Ⱥ��̰� 1byte �� ���� 

	if (FAILED(hr))
	{
		MessageBoxA(nullptr, (char*)m_ErrBlob->GetBufferPointer(), "Pixel Shader Compile Failed!! ", MB_OK);
		return E_FAIL;
	}
	// Compile �� �ڵ�� Vertex Shader ��ü ����� 
	// Compile �Ϸ�� Vertex Shader �� ���� �ּҸ� ���� : Blob�ȿ� ����  
	if (FAILED(DEVICE->CreatePixelShader(m_PSBlob->GetBufferPointer(), m_PSBlob->GetBufferSize(),
		nullptr, m_PS.GetAddressOf())))
	{
		return E_FAIL;

	}

	return S_OK;

}

void CGraphicsShader::UpdateData()
{
	// ���α��� ���� 
	CONTEXT->IASetInputLayout(m_InputLayout.Get());
	CONTEXT->IASetPrimitiveTopology(m_eTopology);


	// �Ʒ� Shader ���� ����ϰڴ�. 
	// HS DS GS �� �Ⱦ����� ���� null �� �־��־�� �Ѵ�.
	// �� Mesh ���� shader ���� �ִµ� 
	// Mesh���� ���� shader ���� �ٸ� �� �ִ�. 
	// �׷��� ������ �� Shader ������ �����ֱ� ������ �׻� 
	// �Ⱦ����� Null ���� �־� �־���Ѵ�.

	CONTEXT->VSSetShader(m_VS.Get(), 0, 0); // �� �������� � ���̴��� ����� �������� �����Ѵ�. 
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
