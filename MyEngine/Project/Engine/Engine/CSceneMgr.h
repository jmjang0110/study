#pragma once


class CSceneMgr
	: public CSingleton<CSceneMgr>
{

	// Singleton ��ü�� CSceneMgr ���� �Ҹ��ڿ� ���� �� �� �ְ� friend ����
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

