#pragma once
#include "CEntity.h"
class CComponent :
    public CEntity
{
private:
    const COMPONENT_TYPE         m_eComType; // �ڽ��� Ÿ���� ���� 
    class CGameObject*           m_pOwner;

public:
    virtual void update() {};
    virtual void lateupdate() {};
    virtual void finalupdate() = 0; // �ݵ�� �����϶�. 
    virtual void render() {};

public:
    COMPONENT_TYPE GetType() { return m_eComType; }

    

public:
    CComponent(COMPONENT_TYPE _eType);
    virtual ~CComponent();

    friend class CGameObject;


};

