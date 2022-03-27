#pragma once
#include "CEntity.h"
class CLayer :
    public CEntity
{

private:
    vector<class CGameObject*> m_vecRoot;


public:
    CLayer();
    ~CLayer();


};

