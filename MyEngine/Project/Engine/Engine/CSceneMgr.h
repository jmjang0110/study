#pragma once


class CSceneMgr
	: public CSingleton<CSceneMgr>
{

	// Singleton 객체가 CSceneMgr 생성 소멸자에 접근 할 수 있게 friend 선언
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

	CScene* GetCurScene() { return m_pCurScene; }
};

