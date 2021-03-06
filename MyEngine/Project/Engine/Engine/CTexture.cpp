#include "pch.h"
#include "CTexture.h"



#include "CDevice.h"


CTexture::CTexture()
{

}

CTexture::~CTexture()
{
	m_Image.GetPixels();

}



int CTexture::Load(const wstring& _strFilePath)
{

	// Texture File 을 SystemMem 에 로드한다. 
	wchar_t szExt[25] = {}; // 확장자 명 
	_wsplitpath_s(_strFilePath.c_str(), nullptr, 0, nullptr, 0, nullptr, 0, szExt, 25);


	HRESULT hr = S_OK;
	int iErr = 0;


	if (!wcscmp(szExt, L".dds") || !wcscmp(szExt, L".DDS"))
	{
		hr = LoadFromDDSFile(_strFilePath.c_str(), DDS_FLAGS_NONE, nullptr, m_Image);
		
	}

	else if (!wcscmp(szExt, L".tga") || !wcscmp(szExt, L".TGA"))
	{
		hr = LoadFromTGAFile(_strFilePath.c_str(), nullptr, m_Image);

	}

	else // WIC ( .png / .jpg / .jpeg / .bmp ... )
	{
		hr = LoadFromWICFile(_strFilePath.c_str(), WIC_FLAGS_NONE, nullptr, m_Image);

	}

	if (CheckFail(hr))
		return E_FAIL;



	// System Memory에 불려와진 픽셀 데이터를 GPU 에 보낸다. 
	//DEVICE->CreateTexture2D();
	//DEVICE->CreateShaderResourceView(); 
	// 원래는 불러서 해야할 것들을 CreateShaderResourceView(); 가 해준다. 


	hr = CreateShaderResourceView(DEVICE, m_Image.GetImages(), m_Image.GetImageCount(),
		m_Image.GetMetadata(), m_pSRV.GetAddressOf());

	if (CheckFail(hr))
		return E_FAIL;


	//m_pSRV->GetResource();;// 이 쉐이더 리소스 뷰가 어떤 Texture 를 관리하는지 
	m_pSRV->GetResource((ID3D11Resource**)m_pTex2D.GetAddressOf());

	return S_OK;
}

void CTexture::UpdateData(int _PipelineStage, int _iRegisterNum)
{
	// Binding 시킨다. // 해당 쉐이더 시점에 바인딩 시킨다 .
	if (_PipelineStage & (int)PIPELINE_STAGE::VS)
		CONTEXT->VSSetShaderResources(_iRegisterNum, 1, m_pSRV.GetAddressOf());

	if (_PipelineStage & (int)PIPELINE_STAGE::HS)
		CONTEXT->HSSetShaderResources(_iRegisterNum, 1, m_pSRV.GetAddressOf());

	if (_PipelineStage & (int)PIPELINE_STAGE::DS)
		CONTEXT->DSSetShaderResources(_iRegisterNum, 1, m_pSRV.GetAddressOf());

	if (_PipelineStage & (int)PIPELINE_STAGE::GS)
		CONTEXT->GSSetShaderResources(_iRegisterNum, 1, m_pSRV.GetAddressOf());

	if (_PipelineStage & (int)PIPELINE_STAGE::PS)
		CONTEXT->PSSetShaderResources(_iRegisterNum, 1, m_pSRV.GetAddressOf());

}
