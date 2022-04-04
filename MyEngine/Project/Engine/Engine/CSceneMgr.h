#pragma once


class CSceneMgr
	: CSingleton<CSceneMgr>
{

	friend class CSingleton<CSceneMgr>;
private:
	CSceneMgr();
	~CSceneMgr();


private:
	class CScene* m_pCurScene;

public:
	void init();
	void progress();
	void render();

public:
	CSceneMgr()
	{

	}
	virtual ~CSceneMgr()
	{

	}
};

