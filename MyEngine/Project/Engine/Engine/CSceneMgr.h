#pragma once

class CGameObject;

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

