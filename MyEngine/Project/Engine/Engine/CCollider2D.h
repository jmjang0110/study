#pragma once
#include "CComponent.h"
#include "CMaterial.h"
#include "CMesh.h"


enum class COLLIDER2D_TYPE
{
    BOX, 
    CIRCLE,
    
};
class CCollider2D :
    public CComponent
{
private:
    Matrix              m_matColWorld;

    COLLIDER2D_TYPE     m_eColliderType;
        
    Vec2                m_vOffsetPos;   // 오브젝트로 부터의 충돌체의 상대 거리 

    Vec2                m_vOffSetScale; // 오브젝트 크기로 부터 충돌체의 배율 

    Ptr<CMesh>          m_pMesh;          // 충돌체 모양 
    Ptr<CMaterial>      m_pMtrl;        // 충돌체 렌더링 제질 

public:
    void SetCollider2DType(COLLIDER2D_TYPE _type);
    void SetOffsetPos(Vec2 _vOffsetPos) { m_vOffsetPos = _vOffsetPos; }
    void SetOffsetScale(Vec2 _vOffsetScale) { m_vOffSetScale = _vOffsetScale; }

public:
    virtual void finalupdate() override;
    virtual void UpdateData() override;
    void render();

    CLONE(CCollider2D)

public:
    CCollider2D();
    ~CCollider2D();


};

