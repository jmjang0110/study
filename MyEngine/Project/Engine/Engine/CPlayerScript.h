#pragma once
#include "CScript.h"

class CPlayerScript :
    public CScript
{
private:
    float m_fSpeed;

public:
    
    virtual void start();  // Player �� Scene �� ������ �� �ؾ��� ���� ���´�. 
    virtual void update();
    virtual void lateupdate();
  
    
public:
    CPlayerScript();
    ~CPlayerScript();

};

