#pragma once
#include "CScript.h"

class CPlayerScript :
    public CScript
{
private:
    Ptr<CPrefab> m_pMissilePrefab;
    float m_fSpeed;

public:
    
    virtual void start();  // Player �� Scene �� ������ �� �ؾ��� ���� ���´�. 
    virtual void update();
    virtual void lateupdate();
  
    CLONE(CPlayerScript);

public:
    CPlayerScript();
    ~CPlayerScript();

};

