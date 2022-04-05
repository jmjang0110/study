#pragma once
class CCore
	: public CSingleton<CCore>
{

	SINGLE(CCore);
private:
	HWND m_hwnd;
	POINT m_ptResolution;



public:

	int init(HWND _hwnd, POINT _ptResolution);
	void progress();
	HWND GetMainHwnd() { return m_hwnd; }


};

