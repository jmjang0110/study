#pragma once


class CSceneMgr
{
	SINGLE(CSceneMgr)
private:
	class CScene* m_pCurScene;

public:
	void init();
	void progress();
	void render();


};

