#include "pch.h"
#include "CCollider2D.h"
#include "CConstBuffer.h"
#include "CDevice.h"
#include "CResMgr.h"
#include "CGameObject.h"
#include "CTransform.h"

CCollider2D::CCollider2D()
	: CComponent(COMPONENT_TYPE::COLLIDER2D)
	, m_eColliderType(COLLIDER2D_TYPE::BOX)
	, m_vOffsetPos(Vec2(0.f, 0.f))
	, m_vOffSetScale(Vec2(1.f, 1.f))
	
{
	// Collider 2D 모양에 맞는 메쉬 참조
	SetCollider2DType(m_eColliderType);

	// Collider 2D 전용 재질 참조 
	m_pMtrl = CResMgr::GetInst()->FindRes<CMaterial>(L"Collider2DMtrl");


}

CCollider2D::~CCollider2D()
{
}


void CCollider2D::SetCollider2DType(COLLIDER2D_TYPE _type)
{
	m_eColliderType = _type;

	if (COLLIDER2D_TYPE::BOX == m_eColliderType)
	{
		//m_pMesh = CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh_LineStrip");
		m_pMesh = CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh");

	}
	else if (COLLIDER2D_TYPE::CIRCLE== m_eColliderType)
	{
		m_pMesh = CResMgr::GetInst()->FindRes<CMesh>(L"CircleMesh");


	}

}

void CCollider2D::finalupdate()
{
	Matrix matTrans = XMMatrixTranslation(m_vOffsetPos.x, m_vOffsetPos.y, 0.f);
	Matrix matScale = XMMatrixScaling(m_vOffSetScale.x, m_vOffSetScale.y, 1.f);
	m_matColWorld = matScale * matTrans;

	Vec3 vObjScale = Transform()->GetWorldScale();
	Matrix matObjScaleInv = XMMatrixInverse(nullptr, XMMatrixScaling(vObjScale.x, vObjScale.y, vObjScale.z));

	// 충돌체 상대행렬 * 오브젝트 월드 크기 역행렬(크기^-1) * 오브젝트 월드 행렬(크기 * 회전 * 이동)
	m_matColWorld = m_matColWorld * matObjScaleInv * Transform()->GetWorldMat();


}

void CCollider2D::UpdateData()
{
	g_transform.matWorld = m_matColWorld;
	g_transform.matWV = g_transform.matWorld * g_transform.matView;
	g_transform.matWVP = g_transform.matWV * g_transform.matProj;

	CConstBuffer* p_CB = CDevice::GetInst()->GetCB(CB_TYPE::TRANSFORM);
	p_CB->SetData(&g_transform, sizeof(tTransform));
	p_CB->UpdateData();



}

void CCollider2D::render()
{

	UpdateData();
	m_pMtrl->UpdateData();
	m_pMesh->render();
}


