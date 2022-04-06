#pragma once

class CGameObject;

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

	CScene* GetCurScene() { return m_pCurScene; }

	void SpawnObject(CGameObject* _pSpawnObject, Vec3 _vWorldPos, 
		wstring _strName, UINT _iLayerIdx);
	void SpawnObject(CGameObject* _pSpawnObject, UINT _iLayerIdx);

	void AddChild(CGameObject* _pParent, CGameObject* pchildObject);


public:
	void init();
	void progress();
	void render();


};

