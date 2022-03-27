#pragma once
#include "CEntity.h"


class CScene :
    public CEntity
{
private:
    class CLayer*       m_arrLayer[MAX_LAYER];

    
public:
    CScene();
    ~CScene();


};

