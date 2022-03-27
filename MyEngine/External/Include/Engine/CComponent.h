#pragma once
#include "CEntity.h"
#include "CGameObject.h"

#define GET_OTHER_COMPONENT(Type) C##Type* Type() { return GetOwner()->Type();}

class CComponent :
    public CEntity
{
private:
    const COMPONENT_TYPE         m_eComType; // �ڽ��� Ÿ���� ���� 
    class CGameObject*           m_pOwner;

public:
    virtual void start() {};
    virtual void update() {};
    virtual void lateupdate() {};
    virtual void finalupdate() = 0; // �ݵ�� �����϶�. 
    virtual void render() {};

public:
    COMPONENT_TYPE GetType() { return m_eComType; }
    CGameObject* GetOwner() { return m_pOwner; }

    GET_OTHER_COMPONENT(Transform);
    GET_OTHER_COMPONENT(MeshRender);


public:
    CComponent(COMPONENT_TYPE _eType);
    virtual ~CComponent();

    friend class CGameObject;


};
