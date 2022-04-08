#pragma once
#include "CEntity.h"
#include "CGameObject.h"

#define GET_OTHER_COMPONENT(Type) C##Type* Type() { return GetOwner()->Type();}

class CComponent :
    public CEntity
{
private:
    const COMPONENT_TYPE         m_eComType; // 자신의 타입을 저장 
    class CGameObject*           m_pOwner;

public:
    virtual void start() {};
    virtual void update() {};
    virtual void lateupdate() {};
    virtual void finalupdate() = 0; // 반드시 구현하라. 
    virtual void render() {};

public:
    COMPONENT_TYPE GetType() { return m_eComType; }
    CGameObject* GetOwner() { return m_pOwner; }

    GET_OTHER_COMPONENT(Transform)
    GET_OTHER_COMPONENT(MeshRender)
    GET_OTHER_COMPONENT(Collider2D)

    CComponent* Clone() = 0;


public:
    CComponent(COMPONENT_TYPE _eType);
    virtual ~CComponent();

    friend class CGameObject;


};

