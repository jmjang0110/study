#include "pch.h"
#include "CRes.h"



CRes::CRes()
{
}

CRes::~CRes()
{
}


bool CRes::CheckFail(HRESULT _hr)
{
	if (FAILED(_hr))
	{
		int iErr = GetLastError();
		wchar_t szText[256] = {};
		wsprintf(szText, L"Error Code : %d", iErr);
		MessageBox(nullptr, szText, L"Texture Loading Fail!! ", MB_OK);

		return true;

	}
	return false;

}