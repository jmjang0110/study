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

	// Texture File �� SystemMem �� �ε��Ѵ�. 
	wchar_t szExt[25] = {}; // Ȯ���� �� 
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



	// System Memory�� �ҷ����� �ȼ� �����͸� GPU �� ������. 
	//DEVICE->CreateTexture2D();
	//DEVICE->CreateShaderResourceView(); 
	// ������ �ҷ��� �ؾ��� �͵��� CreateShaderResourceView(); �� ���ش�. 


	hr = CreateShaderResourceView(DEVICE, m_Image.GetImages(), m_Image.GetImageCount(),
		m_Image.GetMetadata(), m_pSRV.GetAddressOf());

	if (CheckFail(hr))
		return E_FAIL;


	//m_pSRV->GetResource();;// �� ���̴� ���ҽ� �䰡 � Texture �� �����ϴ��� 
	m_pSRV->GetResource((ID3D11Resource**)m_pTex2D.GetAddressOf());

	return S_OK;
}
