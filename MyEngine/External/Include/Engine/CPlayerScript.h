#pragma once
#include "CScript.h"

class CPlayerScript :
    public CScript
{
private:
    Ptr<CPrefab> m_pMissilePrefab;
    float m_fSpeed;

public:
    
    virtual void start();  // Player 가 Scene 에 스폰될 때 해야할 일을 적는다. 
    virtual void update();
    virtual void lateupdate();
  
    CLONE(CPlayerScript);

public:
    CPlayerScript();
    ~CPlayerScript();

};

