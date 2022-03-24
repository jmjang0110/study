#include "pch.h"
#include "CCore.h"

#include "CKeyMgr.h"
#include "CPathMgr.h"
#include "CTimeMgr.h"

#include "Temp.h"
#include "CDevice.h"


CCore::CCore()
	: m_hwnd(nullptr)
	, m_ptResolution()
{

}

CCore::~CCore()
{
	TestRelease();

}

int CCore::init(HWND _hwnd, POINT _ptResolution)
{
	RECT rt = { 0,0,_ptResolution.x, _ptResolution.y };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);
	SetWindowPos(_hwnd, nullptr, 10, 10, rt.right - rt.left, rt.bottom - rt.top, 0);

	m_hwnd = _hwnd;
	m_ptResolution = _ptResolution;

	//===============
	// Manager ÃÊ±âÈ­
	//===============
	CPathMgr::GetInst()->init();
	if (FAILED(CDevice::GetInst()->init(m_hwnd, Vec2((float)m_ptResolution.x, (float)m_ptResolution.y))))
	{
		return E_FAIL;
	}
	CKeyMgr::GetInst()->init();
	CTimeMgr::GetInst()->init();
	


	TestInit();


	return S_OK;
}

void CCore::progress()
{
	// 1. Update
	CTimeMgr::GetInst()->update();
	CKeyMgr::GetInst()->update();
	TestUpdate();

	// 2. Rendering
	TestRender();

}
