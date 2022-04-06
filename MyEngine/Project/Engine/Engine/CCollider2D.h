#pragma once
#include "CComponent.h"

enum class COLLIDER2D_TYPE
{
    BOX, 
    CIRCLE,
    
};
class CCollider2D :
    public CComponent
{
private:
    COLLIDER2D_TYPE     m_eColliderType;
        
    Vec2                m_vOffsetPos;   // 오브젝트로 부터의 충돌체의 상대 거리 
    Vec2                m_vOffSetScale; // 오브젝트 크기로 부터 충돌체의 배율 

public:
    void SetCollider2DType(COLLIDER2D_TYPE _type){m_eColliderType = _type; }
    void SetOffsetPos(Vec2 _vOffsetPos) { m_vOffsetPos = _vOffsetPos; }
    void SetOffsetScale(Vec2 _vOffsetScale) { m_vOffSetScale = _vOffsetScale; }

public:
    virtual void finalupdate() override;
    void render();


public:
    CCollider2D();
    ~CCollider2D();


};

