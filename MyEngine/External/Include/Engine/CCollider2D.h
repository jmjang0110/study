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
        
    Vec2                m_vOffsetPos;   // ������Ʈ�� ������ �浹ü�� ��� �Ÿ� 

    Vec2                m_vOffSetScale; // ������Ʈ ũ��� ���� �浹ü�� ���� 

    Ptr<CMesh>          m_pMesh;          // �浹ü ��� 
    Ptr<CMaterial>      m_pMtrl;        // �浹ü ������ ���� 

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

