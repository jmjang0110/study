#pragma once
#include "CComponent.h"
class CCamera :
    public CComponent
{
private:
    Matrix      m_matView;
    Matrix      m_matProj;


public:
    virtual void finalupdate() override;

public:
    CCamera();
    ~CCamera();
};

