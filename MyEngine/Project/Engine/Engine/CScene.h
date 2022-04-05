#pragma once
#include "CEntity.h"


class CScene :
    public CEntity
{
private:
    class CLayer*       m_arrLayer[MAX_LAYER];

public:
    void start();
    void update();
    void lateupdate();
    void finalupdate();

    void render();

public:
    void SetLayerName(int _iLayerIdx, const wstring& _strName);
    void AddObject(class CGameObject* _pObj, const wstring& _strLayerName); 
    void AddObject(class CGameObject* _pObj, int _iLayerIdx);   
    CLayer* GetLayer(int _iIdx) { assert(_iIdx < 0 || MAX_LAYER <= _iIdx); return m_arrLayer[_iIdx]; }

private:
    int GetLayerIdxFromName(const wstring& _strName);

    CLONE(CScene)

public:
    CScene();
    ~CScene();


};

