#pragma once
#include "CEntity.h"
class CLayer :
    public CEntity
{

private:
    vector<class CGameObject*> m_vecRoot;

public:
    void start();
    void update();
    void lateupdate();
    void finalupdate();

    void render();

public:
    void AddObject(CGameObject* _pObj);

    CLONE(CLayer)

public:
    CLayer();
    ~CLayer();


};

